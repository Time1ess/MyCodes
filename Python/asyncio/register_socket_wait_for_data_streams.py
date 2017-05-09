#!/usr/local/bin/python3
# coding: UTF-8
# Author: David
# Email: youchen.du@gmail.com
# Created: 2017-05-09 18:25
# Last modified: 2017-05-09 18:29
# Filename: register_socket_wait_for_data_streams.py
# Description:
import asyncio
try:
    from socket import socketpair
except ImportError:
    from asyncio.windows_utils import socketpair


async def wait_for_data(loop):
    rsock, wsock = socketpair()
    reader, writer = await asyncio.open_connection(sock=rsock, loop=loop)
    loop.call_later(1, wsock.send, 'abc'.encode())

    data = await reader.read(100)

    print('Received:', data.decode())
    writer.close()

    wsock.close()


loop = asyncio.get_event_loop()
loop.run_until_complete(wait_for_data(loop))
loop.close()
