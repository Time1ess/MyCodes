#!/usr/bin/python
# coding: UTF-8
# Author: David
# Email: youchen.du@gmail.com
# Created: 2016-10-29 19:34
# Last modified: 2016-11-01 11:19
# Filename: manager.py
# Description:
__metaclass__ = type
import socket
import sys
import time
import traceback
import hashlib
from multiprocessing.dummy import Pool, Lock
from threading import Thread
from random import randint

DEBUG = False
BUF_SIZE = 4096


class _Messenger:
    def __init__(self, msg_port=9000, port_range=10):
        self._base_port = 9000
        self._msg_port = msg_port
        self._port_range = 10
        self._mp = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
        self._mp.bind(('0.0.0.0', msg_port))
        self._mp.settimeout(3)

    def receive_msg(self):
        """
        Messenger is responsible for receiving all requests.
        And all requests should be handled by Manager.
        """
        while True:
            try:
                msg, addr = self._mp.recvfrom(BUF_SIZE)
                if msg == 'ACK ACK' or msg == 'ACK REJ':
                    # print msg, 'IGNORE'
                    continue
                print '[MSG]:', msg, addr
                ret, addr = yield (msg, addr)
                print '\t\t[RET]:', ret, addr
                self._mp.sendto(ret, addr)
            except socket.timeout:
                continue
            except Exception:
                break
        yield ('TER', None)

    def send_msg(self, msg, msg_port=None, host='<broadcast>'):
        if not msg_port:
            ports = [self._base_port+i for i in xrange(self._port_range)]
        else:
            ports = [msg_port]
        sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
        sock.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
        sock.setsockopt(socket.SOL_SOCKET, socket.SO_BROADCAST, 1)
        sock.bind(('', 0))
        for port in ports:
            broad_addr = (host, port)
            sock.sendto(msg, broad_addr)

    def terminate(self):
        self._mp.close()


class _FileMasterSession:
    def __init__(self, remote, filename, put_session):
        self._target_host = remote
        # self._md5 = hashlib.md5()
        # self._md5.update(filename)
        # self._filename = self._md5.hexdigest()+'.'+filename.split('.')[-1]
        self._filename = 'server' + filename
        self._PS = put_session

    def __call__(self, sock, *args):
        print 'File transmission begin:', self._filename, self._target_host
        if self._PS:
            open_type = 'wb'
        else:
            open_type = 'rb'
        try:
            while True:
                client, addr = sock.accept()
                if addr[0] != self._target_host:
                    client.send('REJ PUT 301 Source host doesn\'t match')
                    client.close()
                else:
                    with open(self._filename, open_type) as f:
                        # If session is put session then receive bytes.
                        if self._PS:
                            fbts = client.recv(BUF_SIZE)
                            while fbts:
                                f.write(fbts)
                                fbts = client.recv(BUF_SIZE)
                        else:
                            fbts = f.read(BUF_SIZE)
                            while fbts:
                                client.send(fbts)
                                fbts = f.read(BUF_SIZE)
                    break
        except socket.timeout:
            print 'File master session timeout.'
            pass
        except Exception:
            if DEBUG:
                print traceback.print_exc()
        else:
            print 'File transmission end:', self._filename, self._target_host
        finally:
            sock.close()


class _FileSlaveSession:
    def __call__(self, host, port, file_path, put_session):
        if put_session:
            open_type = 'rb'
        else:
            open_type = 'wb'
        try:
            sock = socket.socket()
            sock.settimeout(10)
            sock.connect((host, port))
            with open(file_path, open_type) as f:
                if put_session:
                    fbts = f.read(BUF_SIZE)
                    while fbts:
                        sock.send(fbts)
                        fbts = f.read(BUF_SIZE)
                else:
                    fbts = sock.recv(BUF_SIZE)
                    while fbts:
                        f.write(fbts)
                        fbts = sock.recv(BUF_SIZE)
        except socket.timeout:
            print 'File slave session timeout.'
            pass
        except Exception:
            if DEBUG:
                print traceback.print_exc()
        finally:
            sock.close()


class _SessionManager:
    def __init__(self, transfermanager, session_count):
        self._tm = transfermanager
        self._maxs = session_count
        self._curs = 0
        self._wq = []
        self._pl = Pool()
        self._lock = Lock()

    def __call__(self, *args):
        # print 'Maintain Session Manager.'
        self._lock.acquire()
        self._curs -= 1
        self._lock.release()
        if self._wq:
            args = self._wq.pop(0)
            args[0](*args[1:])

    def _get_session(self, local, remote_ip, msg_port, port,
                     filename, force, delayed):
        fms = _FileMasterSession(remote_ip, filename, False)
        while True:
            try:
                sock = socket.socket()
                sock.bind((local, port))
                sock.listen(1)
            except Exception, e:
                if DEBUG:
                    print traceback.print_exc()
                if e.errno == 48 and force:
                    return (401, port)
                elif e.errno == 48 and not force:
                    port = randint(10000, 15000)
                else:
                    return (603, port)
            else:
                break
        try:
            self._lock.acquire()
            self._pl.apply_async(fms, args=(sock,),
                                 callback=self)
            self._curs += 1
            self._lock.release()
        except Exception, e:
            if DEBUG:
                print traceback.print_exc()
            pass
        if delayed:
            # Should notify local:msg_port that session has been created.
            msg = self._tm._sgt_m(remote_ip, port, filename)
            self._tm.notify(msg, remote_ip)
        return (600, port)

    def get_session(self, local, remote, msg_port, port, filename, force):
        if self._curs >= self._maxs:
            self._wq.append(
                (self._get_session, local, remote,
                 msg_port, port, filename, force, True))
        else:
            return self._get_session(
                local, remote, msg_port, port, filename, force, False)
        return (402, port)

    def _put_session(self, local, remote_ip, msg_port, port,
                     filename, force, delayed):
        fms = _FileMasterSession(remote_ip, filename, True)
        while True:
            try:
                sock = socket.socket()
                sock.bind((local, port))
                sock.listen(1)
            except Exception, e:
                if DEBUG:
                    print traceback.print_exc()
                if e.errno == 48 and force:
                    return (401, port)
                elif e.errno == 48 and not force:
                    port = randint(10000, 15000)
                else:
                    return (403, port)
            else:
                break
        try:
            self._lock.acquire()
            self._pl.apply_async(fms, args=(sock,),
                                 callback=self)
            self._curs += 1
            self._lock.release()
        except Exception, e:
            if DEBUG:
                print traceback.print_exc()
            pass
        if delayed:
            # Should notify local:msg_port that session has been created.
            msg = self._tm._spt_m(remote_ip, port, filename)
            self._tm.notify(msg, remote_ip)
        return (400, port)

    def put_session(self, local, remote, msg_port, port, filename, force):
        if self._curs >= self._maxs:
            self._wq.append(
                (self._put_session, local, remote,
                 msg_port, port, filename, force, True))
        else:
            return self._put_session(
                local, remote, msg_port, port, filename, force, False)
        return (402, port)

    def _feed_get_session(self, host, port, file_path):
        fss = _FileSlaveSession()
        self._lock.acquire()
        self._pl.apply_async(fss, args=(host, port, file_path, False),
                             callback=self)
        self._curs += 1
        self._lock.release()
        return 600

    def feed_get_session(self, host, port, file_path):
        if self._curs >= self._maxs:
            self._wq.append((self._feed_get_session, host, port, file_path))
        else:
            return self._feed_get_session(host, port, file_path)
        return 502

    def _feed_put_session(self, host, port, file_path):
        fss = _FileSlaveSession()
        self._lock.acquire()
        self._pl.apply_async(fss, args=(host, port, file_path, True),
                             callback=self)
        self._curs += 1
        self._lock.release()
        return 500

    def feed_put_session(self, host, port, file_path):
        if self._curs >= self._maxs:
            self._wq.append((self._feed_put_session, host, port, file_path))
        else:
            return self._feed_put_session(host, port, file_path)
        return 502

    def terminate(self):
        self._lock.acquire()
        self._pl.close()
        self._pl.terminate()
        self._lock.release()
        self._pl.join()


class TransferManager:
    """
    A manager to handle file transfer.
    """
    def __init__(self, msg_port=9000, session_count=10):
        """
        msg_port should be a range and every time udp msg should be
        sent from each port.
        """
        self._exit_flag = False
        self._msg_port = msg_port
        self._host_ip = socket.gethostbyname(socket.gethostname())
        self._messenger = _Messenger(msg_port)
        self._manager = _SessionManager(self, session_count)
        self._known_hosts = {}  # <host:msg_port>
        self.send_msg = self._messenger.send_msg
        self.receive_msg = self._messenger.receive_msg
        self._file_paths = {}
        self._main_thread = Thread(target=self.run)
        self._main_thread.setDaemon(True)
        self._main_thread.start()
        time.sleep(0.2)

    def run(self):
        messenger = self.receive_msg()
        reg_msg = 'REG %s %s' % (self._host_ip, self._msg_port)
        self.send_msg(reg_msg)
        msg, addr = messenger.next()
        while True:
            ret, addr = self.handle_msg(msg, addr[0], addr[1])
            msg, addr = messenger.send((ret, addr))
            if msg == 'TER':
                break

    def notify(self, msg, host):
        port = self._known_hosts.get(host, None)
        if not port:
            print 'Host %s is down.' % (host,)
        self.send_msg(msg, port, host)

    def _rej_m(self, mtype, code, reason):
        ret = 'REJ %s %s %s' % (mtype, code, reason)
        return ret

    def _ack_m(self, cmd):
        return 'ACK %s' % (cmd,)

    def _reg(self, target_host, host, port):  # Register a host
        port = int(port)
        if target_host == self._host_ip and self._msg_port == port:
            return self._rej_m(
                mtype='REG',
                code='101',
                reason='Local host should not be registered.')
        elif target_host != host:
            return self._rej_m(
                mtype='REG',
                code='102',
                reason='Host ip doesn\'t match.')
        elif target_host == host:
            self._known_hosts[host] = port
            srg_msg = self._srg_m(self._msg_port)
            return srg_msg

    def _srg_m(self, port):  # SRG message
        msg = 'SRG %s' % (port,)
        return msg

    def _ure(self, target_host, host, port):  # Unregister a host
        if target_host != host:
            return self._rej_m(
                mtype='URE',
                code='201',
                reason='Invalid operation'), port
        port = self._known_hosts.pop(host, None)
        if not port:
            return self._rej_m(
                mtype='URE',
                code='001',
                reason='Invalid host'), port
        else:
            return self._ack_m('URE'), port

    def _srg(self, msg_port, sender_host):  # Server Register
        msg_port = int(msg_port)
        if sender_host != self._host_ip or msg_port != self._msg_port:
            self._known_hosts[sender_host] = msg_port
        return self._ack_m('SRG')

    def _put(self, args, sender_host, msg_port):  # Put a file
        host = args[args.index('-h')+1]
        if host != self._host_ip:
            return self._rej_m(
                mtype='PUT',
                code='301',
                reason='PUT: Target host doesn\'t match')
        port = int(args[args.index('-p')+1])
        filename = args[args.index('-f')+1]
        force = '-F' in args
        code, port = self._manager.put_session(
            self._host_ip, sender_host,
            msg_port, port, filename, force)
        if code == 400:
            return self._spt_m(sender_host, port, filename)
        elif code == 402:
            return self._delay_m('PUT', sender_host, filename)
        elif code == 401:
            return self._rej_m(
                mtype='PUT',
                code=str(code),
                reason='Port has been used')
        else:
            return self._rej_m(
                mtype='PUT',
                code=str(code),
                reason='Unknown Reason in master put session')

    def _spt_m(self, host, port, filename):  # SPT message
        msg = 'SPT %s %s %s' % (host, port, filename)
        return msg

    def _spt(self, host, port, filename):
        port = int(port)
        try:
            file_path = self._file_paths.pop((host, filename, 'PUT'))
        except KeyError:
            return self._rej_m(
                mtype='SPT',
                code='501',
                reason='No such file session with this host')
        code = self._manager.feed_put_session(host, port, file_path)
        if code == 500:
            return self._ack_m('SPT')
        elif code == 502:
            return self._delay_m('SPT', host, filename)
        else:
            return self._rej_m(
                mtype='SPT',
                code=str(code),
                reason='Local session pool has full, waitting')

    def _sgt(self, host, port, filename):
        port = int(port)
        try:
            file_path = self._file_paths.pop((host, filename, 'GET'))
        except KeyError:
            return self._rej_m(
                mtype='SGT',
                code='501',
                reason='No such file session with this host')
        code = self._manager.feed_get_session(host, port, file_path)
        if code == 600:
            return self._ack_m('SGT')
        elif code == 502:
            return self._delay_m('SGT', host, filename)
        else:
            return self._rej_m(
                mtype='SGT',
                code=str(code),
                reason='Local session pool has full, waitting')

    def _get(self, args, sender_host, msg_port):  # Put a file
        host = args[args.index('-h')+1]
        if host != self._host_ip:
            return self._rej_m(
                mtype='PUT',
                code='301',
                reason='PUT: Target host doesn\'t match')
        port = int(args[args.index('-p')+1])
        filename = args[args.index('-f')+1]
        force = '-F' in args
        code, port = self._manager.get_session(
            self._host_ip, sender_host,
            msg_port, port, filename, force)
        if code == 600:
            return self._sgt_m(sender_host, port, filename)
        elif code == 402:
            return self._delay_m('GET', sender_host, filename)
        elif code == 401:
            return self._rej_m(
                mtype='GET',
                code=str(code),
                reason='Port has been used')
        else:
            return self._rej_m(
                mtype='GET',
                code=str(code),
                reason='Unknown Reason in master get session')

    def _sgt_m(self, host, port, filename):  # SGT message
        msg = 'SGT %s %s %s' % (host, port, filename)
        return msg

    def _delay_m(self, mtype, host, filename):  # DLY message
        msg = 'DLY %s %s %s' % (mtype, host, filename)
        return msg

    def handle_msg(self, msg, sender_host, sender_port):
        """
        Handle message.
        """
        msg = msg.strip('\r\n')
        margs = msg.split(' ')
        mtype = margs[0]
        if (mtype != 'REG' and mtype != 'SRG') and \
                not self._known_hosts.get(sender_host, None):
            msg = self._rej_m(mtype, '001', 'Invalid host')
            return (msg, (sender_host, sender_port))
        elif mtype == 'REG':
            msg = self._reg(margs[1], sender_host, margs[2])
            port = self._known_hosts.get(sender_host, sender_port)
            return (msg, (sender_host, port))
        elif mtype == 'URE':
            msg, port = self._ure(margs[1], sender_host, sender_port)
            return (msg, (sender_host, port))
        elif mtype == 'PUT':
            msg = self._put(margs, sender_host, sender_port)
        elif mtype == 'GET':
            msg = self._get(margs, sender_host, sender_port)
            pass
        elif mtype == 'ACK':
            msg = self._ack_m('ACK')
        elif mtype == 'REJ':
            msg = self._ack_m('REJ')
        elif mtype == 'SRG':
            msg = self._srg(margs[1], sender_host)
        elif mtype == 'SPT':
            msg = self._spt(*margs[1:])
        elif mtype == 'SGT':
            msg = self._sgt(*margs[1:])
        elif mtype == 'CGT':
            pass
        elif mtype == 'DLY':
            # Respond to DLY SPT or DLY SGT
            # Release waiting socket
            msg = self._ack_m('DLY')
        else:
            msg = self._rej_m(
                mtype=mtype,
                code='002',
                reason='Unknown reason')
        port = self._known_hosts.get(sender_host)
        return (msg, (sender_host, port))

    def put(self, file_path, host, port, force=False):
        """
        Send local file to the remote host.
        """
        msg_port = self._known_hosts.get(host, None)
        if msg_port is None:
            print 'No such host is known.'
            return False
        file_name = file_path.rsplit('/', 1)[-1]
        msg = 'PUT -h %s -p %s -f %s' % (host, port, file_name)
        if force:
            msg += ' -F'
        # TODO: pop file_path if server reject the request
        self._file_paths.setdefault((host, file_name, 'PUT'), file_path)
        self.send_msg(msg, msg_port, host)

    def terminal_put(self, cmd):
        args = cmd.split(' ')
        host = args[args.index('-h')+1]
        port = int(args[args.index('-p')+1])
        file_path = args[args.index('-f')+1]
        force = '-F' in args
        self.put(file_path, host, port, force)

    def get(self, file_name, host, port, force=False, file_path=None):
        """
        Request file from a remote host.
        """
        msg_port = self._known_hosts.get(host, None)
        if msg_port is None:
            print 'No such host is known.'
            return False
        # TODO: file_path validation
        msg = 'GET -h %s -p %s -f %s' % (host, port, file_name)
        if force:
            msg += ' -F'
        if not file_path:
            file_path = file_name
        if DEBUG:
            file_path.replace('server', 'client')
        # TODO: pop file_path if server reject the request
        self._file_paths.setdefault((host, file_name, 'GET'), file_path)
        self.send_msg(msg, msg_port, host)

    def terminal_validation(self, cmd):
        """
        Validate the command get from terminal.
        """
        if cmd.startswith('PUT'):
            self.terminal_put(cmd)
        elif cmd.startswith('GET'):
            self.terminal_get(cmd)

    def terminal_get(self, cmd):
        args = cmd.split(' ')
        host = args[args.index('-h')+1]
        port = int(args[args.index('-p')+1])
        file_path = args[args.index('-f')+1]
        file_name = file_path.rsplit('/')[-1]
        force = '-F' in args
        self.get(file_name, host, port, force, file_path)

    def terminate(self):
        time.sleep(1)
        while self._manager._curs > 0:
            print 'Session Not ended.'
            time.sleep(1)
        ure_msg = 'URE %s' % (self._host_ip)
        for host, port in self._known_hosts.iteritems():
            self.send_msg(ure_msg, port, host)
        self._messenger.terminate()
        self._manager.terminate()


def test_put(port):
    m = TransferManager(port, 2)
    host = socket.gethostbyname(socket.gethostname())
    filenames = [
        '[APTX4869][CONAN][817][720P][AVC_AAC][CHS](59D42DBF).mp4',
        '[APTX4869][CONAN][818][720P][AVC_AAC][CHS](2FCED262).mp4',
        '[APTX4869][CONAN][819][720P][AVC_AAC][CHS](0B98AFC4).mp4',
        '[APTX4869][CONAN][820][720P][AVC_AAC][CHS](B8255B71).mp4']
    cmd_fmt = 'PUT -h %s -p %s -f /Users/youchen/Movies/%s'
    cmds = [cmd_fmt % (host, 10000+randint(0, 0), x) for x
            in filenames]
    for cmd in cmds:
        m.terminal_put(cmd)
    return 0


def test_get(port):
    m = TransferManager(port, 2)
    host = socket.gethostbyname(socket.gethostname())
    filenames = [
        '[APTX4869][CONAN][817][720P][AVC_AAC][CHS](59D42DBF).mp4',
        '[APTX4869][CONAN][818][720P][AVC_AAC][CHS](2FCED262).mp4',
        '[APTX4869][CONAN][819][720P][AVC_AAC][CHS](0B98AFC4).mp4',
        '[APTX4869][CONAN][820][720P][AVC_AAC][CHS](B8255B71).mp4']
    cmd_fmt = 'GET -h %s -p %s -f %s'
    cmds = [cmd_fmt % (host, 10000+randint(0, 0), x) for x
            in filenames]
    for cmd in cmds:
        m.terminal_get(cmd)
    return 0


def test_all(port):
    m = TransferManager(port, 2)
    host = socket.gethostbyname(socket.gethostname())
    filenames = [
        '[APTX4869][CONAN][817][720P][AVC_AAC][CHS](59D42DBF).mp4',
        '[APTX4869][CONAN][818][720P][AVC_AAC][CHS](2FCED262).mp4',
        '[APTX4869][CONAN][819][720P][AVC_AAC][CHS](0B98AFC4).mp4',
        '[APTX4869][CONAN][820][720P][AVC_AAC][CHS](B8255B71).mp4']
    cmd_fmt = 'PUT -h %s -p %s -f /Users/youchen/Movies/%s'
    cmds = [cmd_fmt % (host, 10000+randint(0, 0), x) for x
            in filenames]
    for cmd in cmds:
        m.terminal_put(cmd)

    cmd_fmt = 'GET -h %s -p %s -f %s'
    cmds = [cmd_fmt % (host, 10000+randint(0, 0), x) for x
            in filenames]
    for cmd in cmds:
        m.terminal_get(cmd)
    return 0


def test(port=9000):
    if port == 9000:
        m = TransferManager(port, 2)
    elif port == 9001:
        test_put(port)
    elif port == 9002:
        test_get(port)
    elif port == 9003:
        test_all(port)
    else:
        print 'Unknown usage.'
    raw_input()
    print 'terminated.'


def main(port=9100):
    if len(sys.argv) == 1:
        print 'Usage:'
        print '\tPUT -h host_ip -p port_num -f file_path [-F]'
        print '\tGET -h host_ip -p port_num -f file_name [-F]'
        print 'Note:'
        print '\t -h : Specify which host ip to PUT or GET'
        print '\t -p : Specify which port to PUT or GET'
        print '\t -f : Specify which file to PUT OR GET'
        print '\t -F : Specify whether to use force mode.'
        print '\t        Force to use specified port_num,'
        print '\t        rejected when port_num is used.'
    else:
        cmd = ' '.join(sys.argv[1:])
        m = TransferManager(port, 1)
        m.terminal_validation(cmd)
        m.terminate()


if __name__ == '__main__':
    is_server = False
    if len(sys.argv) == 2:
        is_server = sys.argv[1] == 'SERVER'
    if DEBUG or is_server:
        if len(sys.argv) == 3:
            port = int(sys.argv[2])
        else:
            port = input('Port:')
        test(port)
    else:
        main()
