#!/usr/local/bin/python3
# coding: UTF-8
# Author: David
# Email: youchen.du@gmail.com
# Created: 2017-05-09 16:51
# Last modified: 2017-05-09 16:55
# Filename: register_socket_wait_for_data.py
# Description:
import asyncio
try:
    from socket import socketpair
except ImportError:
    from asyncio.windows_utils import socketpair


class MyProtocol(asyncio.Protocol):
    def __init__(self, loop):
        self.transport = None
        self.loop = loop

    def connection_made(self, transport):
        self.transport = transport

    def data_received(self, data):
        print('Received:', data.decode())
        self.transport.close()

    def connection_lost(self, exc):
        loop.stop()


rsock, wsock = socketpair()
loop = asyncio.get_event_loop()

connect_coro = loop.create_connection(lambda: MyProtocol(loop), sock=rsock)
transport, protocol = loop.run_until_complete(connect_coro)

loop.call_later(1, wsock.send, 'abc'.encode())

loop.run_forever()
rsock.close()
wsock.close()
loop.close()
