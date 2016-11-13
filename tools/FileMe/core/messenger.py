#!/usr/bin/python
# coding: UTF-8
# Author: David
# Email: youchen.du@gmail.com
# Created: 2016-11-08 09:05
# Last modified: 2016-11-13 18:29
# Filename: messenger.py
# Description:
__metaclass__ = type
import socket
import logging

from settings import *


class _Messenger:
    """
    Messenger is designed to receive and send message with other Messenger.
    UDP protocol is used.
    """
    def __init__(self, msg_port=9000, port_range=10):
        """
        Author: David
        Desc:
                msg_port defines which port to communicate with this
                messenger.  port_range defines the range of ports to send
                message to other messenger when port is not specified.
                A timeout is given to the socket so that messenger will
                not block when there is no other messengers connect to
                this messenger.
        """
        self._base_port = 9000
        self._msg_port = msg_port
        self._port_range = 10
        self._mp = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
        self._mp.bind(('0.0.0.0', msg_port))
        self._mp.settimeout(3)

    def receive_msg(self):
        """
        Author: David
        Desc:
                receive_msg returns a generator which will try to receive
                message, and will raise timeout error if reach the specified
                timeout. When a msg is received, it will be yield and hopes
                to receive a return message from its caller and sends to
                original sender.
        """
        while True:
            try:
                msg, addr = self._mp.recvfrom(BUF_SIZE)
                if msg == 'ACK ACK' or msg == 'ACK REJ':
                    # print msg, 'IGNORE'
                    continue
                print '[MSG]:', msg, addr
                ret, addr = yield (msg, addr)
                print '\t[RET]:', ret, addr
                self._mp.sendto(ret, addr)
            except socket.timeout:
                continue
            except Exception, e:
                if e.errno != 10054:
                    logging.error(e)
                continue
        yield ('TER', None)

    def send_msg(self, msg, msg_port=None, host='<broadcast>'):
        """
        Author: David
        Desc:
                send_msg will send given message to host:msg_port, when
                msg_port is not given, port_range which defines in __init__
                will be used.  when host is not given, the message will be
                broadcasted to all hosts in LAN.
        """
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
        """
        Author: David
        Desc:
                Close the Messenger socket.
        """
        self._mp.close()
