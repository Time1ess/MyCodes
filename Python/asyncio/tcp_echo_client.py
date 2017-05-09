#!/usr/local/bin/python3
# coding: UTF-8
# Author: David
# Email: youchen.du@gmail.com
# Created: 2017-05-09 16:29
# Last modified: 2017-05-09 16:49
# Filename: tcp_echo_client.py
# Description:
import asyncio


class EchoClientProtocol(asyncio.Protocol):
    def __init__(self, message, loop):
        self.message = message;
        self.loop = loop

    def connection_made(self, transport):
        transport.write(self.message.encode())
        print('Data send: {!r}'.format(self.message))

    def data_received(self, data):
        print('Data received: {!r}'.format(data.decode()))

    def connection_lost(self, exc):
        print('The server closed to connection')
        print('Stop the event loop')
        self.loop.stop()


loop = asyncio.get_event_loop()
message = 'Hello World!'
coro = loop.create_connection(lambda: EchoClientProtocol(message, loop),
                              '127.0.0.1', 8888)
loop.run_until_complete(coro)
loop.run_forever()
loop.close()
