#!/usr/bin/python
# coding: UTF-8
# Author: David
# Email: youchen.du@gmail.com
# Created: 2016-10-29 19:34
# Last modified: 2016-11-08 09:21
# Filename: manager.py
# Description: The Core of FileMe
__metaclass__ = type
import socket
import sys
import time

from threading import Thread

from settings import *
from messenger import _Messenger
from sessions import _SessionManager


class TransferManager:
    """
    TransferManager is designed to handle file transfer.
    it contains a SessionManager and a Messenger.
    """
    def __init__(self, msg_port=9000, session_count=10):
        """
        Author: David
        Desc:
                Init TransferManager. Create a new thread to receive message
                and process it.
                known_hosts defines known hosts and its messenger port.
                file_paths defines jobs on this TransferManager waitting to
                be done.
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
        """
        Author: David
        Desc:
                Register itself at the beginning, then receive message and
                return response to its source continously.
        """
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
        """
        Author: David
        Desc:
                A shortcut for sending message to a known host.
        """
        port = self._known_hosts.get(host, None)
        if not port:
            print 'Host %s is down.' % (host,)
        self.send_msg(msg, port, host)

    def _rej_m(self, mtype, code, reason):
        """
        Author: David
        Desc:
                Generate rejected message.
        """
        ret = 'REJ %s %s %s' % (mtype, code, reason)
        return ret

    def _ack_m(self, cmd):
        """
        Author: David
        Desc:
                Generate acknowledged message.
        """
        return 'ACK %s' % (cmd,)

    def _reg(self, target_host, host, port):  # Register a host
        """
        Author: David
        Desc:
                Respond to register and verify it. send server register message
                to a host if it has been verified.
        """
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
        """
        Author: David
        Desc:
                Generate server register message.
        """
        msg = 'SRG %s' % (port,)
        return msg

    def _ure(self, target_host, host, port):  # Unregister a host
        """
        Author: David
        Desc:
                Respond to unregister message, verify its source
                before delete from known_hosts.
        """
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
        """
        Author: David
        Desc:
                Respond to server register message.
        """
        msg_port = int(msg_port)
        if sender_host != self._host_ip or msg_port != self._msg_port:
            self._known_hosts[sender_host] = msg_port
        return self._ack_m('SRG')

    def _put(self, args, sender_host, msg_port):  # Put a file
        """
        Author: David
        Desc:
                Respond to PUT message. Verify message source
                and message content, pass args to SessionManager
                and try to create new session, generate message and
                send to message source based on return code from
                SessionManager.
        """
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
        """
        Author: David
        Desc:
                Generate server put ready message.
        """
        msg = 'SPT %s %s %s' % (host, port, filename)
        return msg

    def _spt(self, host, port, filename):
        """
        Author: David
        Desc:
                Respond to server PUT ready message. Verify the job content
                first, reject if no related file job in local job queue.
        """
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
        """
        Author: David
        Desc:
                Respond to server GET ready message. Verify the job content
                first, reject if no related file job in local job queue.

                [TODO]: Merge _sgt and _spt
        """
        port = int(port)
        try:
            file_path = self._file_paths.pop((host, filename, 'GET'))
        except KeyError:
            return self._rej_m(
                mtype='SGT',
                code='501',
                reason='No such file session with this host')
        code = self._manager.feed_get_session(host, port, file_path)
        if code == 700:
            return self._ack_m('SGT')
        elif code == 502:
            return self._delay_m('SGT', host, filename)
        else:
            return self._rej_m(
                mtype='SGT',
                code=str(code),
                reason='Local session pool has full, waitting')

    def _get(self, args, sender_host, msg_port):  # GET a file
        """
        Author: David
        Desc:
                Respond to GET message, FileMasterSession will be created
                if everything is fine, or request will be rejected.
        """
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
        """
        Author: David
        Desc:
                Generate server GET ready message.
        """
        msg = 'SGT %s %s %s' % (host, port, filename)
        return msg

    def _delay_m(self, mtype, host, filename):  # DLY message
        """
        Author: David
        Desc:
                Generate delay job message.
        """
        msg = 'DLY %s %s %s' % (mtype, host, filename)
        return msg

    def handle_msg(self, msg, sender_host, sender_port):
        """
        Author: David
        Desc:
                Parse the message received by Messenger, Call funcs
                based on its content, and return the reply to the right
                address.
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
        Author: David
        Desc:
                Request to send a file which is specified by file_path to
                host:port. If force is True, then port should not be changed
                by remote server and rejected message will be given, or port
                will be changed if remote port has been used.
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
        """
        Author: David
        Desc:
                Request to send a file based on terminal input. The inputs
                will be parsed into args and will be used by put method.
        """
        args = cmd.split(' ')
        host = args[args.index('-h')+1]
        port = int(args[args.index('-p')+1])
        file_path = args[args.index('-f')+1]
        force = '-F' in args
        self.put(file_path, host, port, force)

    def get(self, file_name, host, port, force=False, file_path=None):
        """
        Author: David
        Desc:
                Request to receive a file which is specified by file_name from
                host:port. If force is True, then port should not be changed
                by remote server and rejected message will be given, or port
                will be changed if remote port has been used. If file_path is
                given, then the recevied file will be saved with the specified
                path, else it will be saved at current working directory.
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

    def terminal_get(self, cmd):
        """
        Author: David
        Desc:
                Request to receive a file based on terminal input. The inputs
                will be parsed into args and will be used by get method.
        """
        args = cmd.split(' ')
        host = args[args.index('-h')+1]
        port = int(args[args.index('-p')+1])
        file_path = args[args.index('-f')+1]
        file_name = file_path.rsplit('/')[-1]
        force = '-F' in args
        self.get(file_name, host, port, force, file_path)

    def terminal_validation(self, cmd):
        """
        Author: David
        Desc:
                [TODO]:  Validate terminal inputs and pass the inputs to the
                right method.
        """
        if cmd.startswith('PUT'):
            self.terminal_put(cmd)
        elif cmd.startswith('GET'):
            self.terminal_get(cmd)

    def terminate(self):
        """
        Author: David
        Desc:
                Terminate the TransferManager. Before that, SessionManager
                should be terminated, and unregister message should be sent
                to all known_hosts, then the messenger will be terminated.
        """
        self._manager.terminate()
        ure_msg = 'URE %s' % (self._host_ip)
        for host, port in self._known_hosts.iteritems():
            self.send_msg(ure_msg, port, host)
        self._messenger.terminate()


def main(port=9100):
    """
    Author: David
    Desc:
            Interface to use terminal_get and terminal_put in terminal, Notice
            that everytime a terminal command on PUT or GET to transfer a
            file, the TransferManager will be instanced once, so it is not
            recommend to use in this way.

            [TODO]: Continous inputs support.
    """
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
        time.sleep(1)
        m.terminate()


if __name__ == '__main__':
    main()
