#!/usr/local/bin/python3
# coding: UTF-8
# Author: David
# Email: youchen.du@gmail.com
# Created: 2017-05-09 18:12
# Last modified: 2017-05-09 18:18
# Filename: tcp_echo_client_streams.py
# Description:
import asyncio


async def tcp_echo_client(message, loop):
    reader, writer = await asyncio.open_connection('127.0.0.1', 8888,
                                                   loop=loop)
    print('Send: {!r}'.format(message))
    writer.write(message.encode())
    
    data = await reader.read(100)
    print('Received: {!r}'.format(data.decode()))

    print('Close the socket')
    writer.close()


message = 'Hello World!'
loop = asyncio.get_event_loop()
loop.run_until_complete(tcp_echo_client(message, loop))
loop.close()
