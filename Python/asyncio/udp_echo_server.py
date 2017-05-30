#!/usr/local/bin/python3
# coding: UTF-8
# Author: David
# Email: youchen.du@gmail.com
# Created: 2017-05-09 16:44
# Last modified: 2017-05-09 16:50
# Filename: udp_echo_server.py
# Description:
import asyncio

class EchoServerProtocol(asyncio.DatagramProtocol):
    def connection_made(self, transport):
        self.transport = transport

    def datagram_received(self, data, addr):
        message = data.decode()
        print('Received {!r} from {}'.format(message, addr))
        print('Send {!r} to {}'.format(message, addr))
        self.transport.sendto(data, addr)

loop = asyncio.get_event_loop()
print('Starting UDP server')
listen = loop.create_datagram_endpoint(
    EchoServerProtocol, local_addr=('127.0.0.1', 9999))
transport, protocol = loop.run_until_complete(listen)

try:
    loop.run_forever()
except KeyboardInterrupt:
    pass

transport.close()
loop.close()
