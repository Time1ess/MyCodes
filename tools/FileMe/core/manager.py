#!/usr/bin/python
# coding: UTF-8
# Author: David
# Email: youchen.du@gmail.com
# Created: 2016-10-29 19:34
# Last modified: 2016-10-31 11:06
# Filename: manager.py
# Description:
__metaclass__ = type
import socket
import traceback
import random
import hashlib
from multiprocessing.dummy import Pool
from threading import Thread

DEBUG = True
BUF_SIZE = 4096


class _Messenger:
    def __init__(self, msg_port=9000, port_range=10):
        self._base_port = 9000
        self._msg_port = msg_port
        self._port_range = 10
        self._mp = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
        self._mp.bind(('0.0.0.0', msg_port))

    def receive_msg(self):
        """
        Messenger is responsible for receiving all requests.
        And all requests should be handled by Manager.
        """
        while True:
            msg, addr = self._mp.recvfrom(BUF_SIZE)
            if msg == 'ACK ACK' or msg == 'ACK REJ':
                # print msg, 'IGNORE'
                continue
            print '[MSG]:', msg, addr
            ret, addr = yield (msg, addr)
            print '\t\t[RET]:', ret, addr
            self._mp.sendto(ret, addr)

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


class _FileDownloadSession:
    def __init__(self, remote, filename):
        self._target_host = remote
        self._md5 = hashlib.md5()
        self._md5.update(filename)
        self._filename = self._md5.hexdigest()+'.'+filename.split('.')[-1]

    def __call__(self, sock, *args):
        try:
            while True:
                client, addr = sock.accept()
                if addr[0] != self._target_host:
                    client.send('REJ PUT 301 Source host doesn\'t match')
                    client.close()
                else:
                    with open(self._filename, 'wb') as f:
                        data = client.recv(BUF_SIZE)
                        while data:
                            f.write(data)
                            data = client.recv(BUF_SIZE)
                    break
        except Exception:
            print traceback.print_exc()
        finally:
            sock.close()


class _FileUploadSession:
    def __call__(self, host, port, file_path):
        try:
            sock = socket.socket()
            sock.connect((host, port))
            with open(file_path, 'rb') as f:
                fbts = f.read(BUF_SIZE)
                while fbts:
                    sock.send(fbts)
                    fbts = f.read(BUF_SIZE)
        except Exception:
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

    def __call__(self, *args):
        print 'Maintain Session Manager.'
        if self._wq:
            args = self._wq.pop(0)
            args[0](*args[1:])
        self._curs -= 1

    def _get_session(self):
        pass

    def get_session(self):
        pass

    def _put_session(self, local, remote_ip, msg_port, port,
                     filename, force, delayed):
        fds = _FileDownloadSession(remote_ip, filename)
        while True:
            try:
                sock = socket.socket()
                sock.bind((local, port))
                sock.listen(1)
            except Exception, e:
                print traceback.print_exc()
                if e.errno == 48 and force:
                    return (401, port)
                elif e.errno == 48 and not force:
                    port = random.randint(10000, 15000)
                else:
                    return (403, port)
            else:
                break
        try:
            self._pl.apply_async(fds, args=(sock,), callback=self)
        except Exception, e:
            print traceback.print_exc()
        if delayed:
            # Should notify local:msg_port that session has been created.
            msg = self._tm._spt_m(remote_ip, port, filename)
            self._tm.notify(msg, remote_ip)
        self._curs += 1
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

    def feed_get_session(self):
        pass

    def _feed_put_session(self, host, port, file_path):
        fus = _FileUploadSession()
        self._pl.apply_async(fus, args=(host, port, file_path), callback=self)
        return 500

    def feed_put_session(self, host, port, file_path):
        if self._curs >= self._maxs:
            self._wq.append((self._feed_put_session, host, port, file_path))
        else:
            return self._feed_put_session(host, port, file_path)
        return 502

    def terminate(self):
        self._pl.close()
        self._pl.terminate()
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
        self.known_hosts = {}  # <host:msg_port>
        self.send_msg = self._messenger.send_msg
        self.receive_msg = self._messenger.receive_msg
        self.file_paths = {}
        self._main_thread = Thread(target=self.run)
        self._main_thread.setDaemon(True)
        self._main_thread.start()

    def run(self):
        messenger = self.receive_msg()
        reg_msg = 'REG %s %s' % (self._host_ip, self._msg_port)
        self.send_msg(reg_msg)
        msg, addr = messenger.next()
        while True:
            ret, addr = self.handle_msg(msg, addr[0], addr[1])
            msg, addr = messenger.send((ret, addr))

    def notify(self, msg, host):
        port = self.known_hosts.get(host, None)
        if not port:
            print 'Host %s is down.' % (host,)
        self.send_msg(msg, port, host)

    def _rej_m(self, mtype, code, reason):
        ret = 'REJ %s %s %s' % (mtype, code, reason)
        return ret

    def _ack_m(self, cmd):
        return 'ACK %s' % (cmd,)

    def _reg(self, target_host, host, port):  # Register a host
        if target_host == self._host_ip and not DEBUG:
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
            self.known_hosts[host] = int(port)
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
        port = self.known_hosts.pop(host, None)
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
            self.known_hosts[sender_host] = msg_port
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
        else:
            return self._rej_m(
                mtype='PUT',
                code=str(code),
                reason='placeholder')

    def _spt_m(self, host, port, filename):  # SPT message
        msg = 'SPT %s %s %s' % (host, port, filename)
        return msg

    def _spt(self, host, port, filename):
        port = int(port)
        try:
            file_path = self.file_paths.pop((host, filename))
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
                reason='placeholder')

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
        if mtype != 'REG' and not self.known_hosts.get(sender_host, None):
            msg = self._rej_m(mtype, '001', 'Invalid host')
            return (msg, (sender_host, sender_port))
        elif mtype == 'REG':
            msg = self._reg(margs[1], sender_host, margs[2])
            port = self.known_hosts.get(sender_host, sender_port)
            return (msg, (sender_host, port))
        elif mtype == 'URE':
            msg, port = self._ure(margs[1], sender_host, sender_port)
            return (msg, (sender_host, port))
        elif mtype == 'PUT':
            msg = self._put(margs, sender_host, sender_port)
        elif mtype == 'GET':
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
            pass
        elif mtype == 'CGT':
            pass
        elif mtype == 'DLY':
            pass
        else:
            msg = 'REJ 002 Unknown reason'
        port = self.known_hosts.get(sender_host)
        return (msg, (sender_host, port))

    def put(self, file_path, host, port, force=False):
        """
        Send local file to the remote host.
        """
        msg_port = self.known_hosts.get(host)
        file_name = file_path.rsplit('/', 1)[-1]
        msg = 'PUT -h %s -p %s -f %s' % (host, port, file_name)
        if force:
            msg += ' -F'
        self.file_paths[(host, file_name)] = file_path
        self.send_msg(msg, msg_port, host)

    def get(self, file_name, host):
        """
        Request file from a remote host.
        """
        pass

    def terminate(self):
        ure_msg = 'URE %s' % (self._host_ip)
        self.send_msg(ure_msg)
        self._messenger.terminate()
        self._manager.terminate()


def test(port=9000):
    m = TransferManager(port)
    while True:
        c = raw_input("Input:")
        if not c:
            break
        elif port != 9000:
            pass
    m.terminate()
    return 0

if __name__ == '__main__':
    port = input('Port:')
    test(port)
