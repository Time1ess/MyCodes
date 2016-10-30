#!/usr/bin/python
# coding: UTF-8
# Author: David
# Email: youchen.du@gmail.com
# Created: 2016-10-29 19:34
# Last modified: 2016-10-30 11:34
# Filename: manager.py
# Description:
__metaclass__ = type
import socket
import traceback


class _Messenger:
    def __init__(self, msg_port=9000, port_range=10):
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
            msg, addr = self._mp.recvfrom(4096)
            print '[MSG]:', msg, addr,
            ret, addr = yield (msg, addr)
            print '\t\t[RET]:', ret, addr
            self._mp.sendto(ret, addr)

    def send_msg(self, msg, msg_port=None):
        if not msg_port:
            ports = [self._msg_port+i for i in xrange(self._port_range)]
        else:
            ports = [msg_port]
        sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
        sock.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
        sock.setsockopt(socket.SOL_SOCKET, socket.SO_BROADCAST, 1)
        sock.bind(('', 0))
        for port in ports:
            broad_addr = ('<broadcast>', port)
            sock.sendto(msg, broad_addr)

    def terminate(self):
        self._mp.close()


class _TransferSession:
    pass


class _SessionManager:
    pass


class TransferManager:
    """
    A manager to handle file transfer.
    """
    def __init__(self, msg_port=9000, session_count=10):
        """
        msg_port should be a range and every time udp msg should be
        sent from each port.
        """
        self._msg_port = msg_port
        self._host_ip = socket.gethostbyname(socket.gethostname())
        self._messenger = _Messenger(msg_port)
        self._manager = _SessionManager()
        self.known_hosts = {}  # <host:msg_port>
        self.send_msg = self._messenger.send_msg
        self.receive_msg = self._messenger.receive_msg

    def run(self):
        messenger = self.receive_msg()
        reg_msg = 'REG %s %s' % (self._host_ip, self._msg_port)
        self.send_msg(reg_msg)
        msg, addr = messenger.next()
        while True:
            ret, addr = self.handle_msg(msg, addr[0], addr[1])
            msg, addr = messenger.send((ret, addr))

    def _rej(self, mtype, code, reason):
        ret = 'REJ %s %s %s' % (mtype, code, reason)
        return ret

    def _ack(self, cmd):
        return 'ACK %s' % (cmd,)

    def _reg(self, target_host, host, port):
        if target_host == self._host_ip:
            return self._rej(
                mtype='REG',
                code='1000',
                reason='Local host should not be registered.')
        elif target_host != host:
            return self._rej(
                mtype='REG',
                code='1001',
                reason='Host ip doesn\'t match.')
        elif target_host == host:
            self.known_hosts[host] = int(port)
            srg_msg = 'SRG %s' % (self._msg_port,)
            return srg_msg

    def _ure(self, target_host, host, port):
        if target_host != host:
            return self._rej(
                mtype='URE',
                code='2002',
                reason='Invalid operation'), port
        port = self.known_hosts.pop(host, None)
        if not port:
            return self._rej(
                mtype='URE',
                code='2001',
                reason='Invalid host'), port
        else:
            return self._ack('URE'), port

    def handle_msg(self, msg, sender_host, sender_port):
        """
        Handle message.
        """
        msg = msg.strip('\r\n')
        margs = msg.split(' ')
        mtype = margs[0]
        if mtype != 'REG' and not self.known_hosts.get(sender_host, None):
            msg = self._rej(mtype, '0001', 'Invalid host')
            return (msg, (sender_host, sender_port))
        elif mtype == 'REG':
            msg = self._reg(margs[1], sender_host, margs[2])
            port = self.known_hosts.get(sender_host, sender_port)
            return (msg, (sender_host, port))
        elif mtype == 'URE':
            msg, port = self._ure(margs[1], sender_host, sender_port)
            return (msg, (sender_host, port))
        elif mtype == 'PUT':
            pass
        elif mtype == 'GET':
            pass
        elif mtype == 'ACK':
            pass
        elif mtype == 'REJ':
            pass
        elif mtype == 'SRG':
            pass
        elif mtype == 'SPT':
            pass
        elif mtype == 'SGT':
            pass
        elif mtype == 'CGT':
            pass
        else:
            msg = 'REJ 0000 Unknown reason'
        port = self.known_hosts.get(host)
        return (msg, (host, port))

    def put(self, file_path, host, port, force=False):
        """
        Send local file to the remote host.
        """
        msg_port = self.known_hosts.get(host)
        file_name = file_path.rsplit('/', 1)[-1]
        msg = 'PUT -h %s -p %s %s' % (host, port, file_name)
        if force:
            msg += ' -f'
        self.send_msg(msg, host, msg_port)

    def get(self, file_name, host):
        """
        Request file from a remote host.
        """
        pass

    def terminate(self):
        ure_msg = 'URE %s' % (self._host_ip)
        self.send_msg(ure_msg)
        self._messenger.terminate()


def test():
    m = TransferManager(9000)
    try:
        m.run()
    except Exception, e:
        print 'Err:', e
        print traceback.print_exc()
    finally:
        m.terminate()
        return 0

if __name__ == '__main__':
    test()
