#!/usr/local/bin/python3
# coding: UTF-8
# Author: David
# Email: youchen.du@gmail.com
# Created: 2017-05-09 13:39
# Last modified: 2017-05-09 13:44
# Filename: watch_descriptor_for_read_events.py
# Description:
import asyncio
try:
    from socket import socketpair
except ImportError:
    from asyncio.windows_utils import socketpair


rsock, wsock = socketpair()
loop = asyncio.get_event_loop()


def reader():
    data = rsock.recv(1024)
    print('Received:', data.decode())
    loop.remove_reader(rsock)
    loop.stop()


loop.add_reader(rsock, reader)
loop.call_soon(wsock.send, 'abc'.encode())
loop.run_forever()

rsock.close()
wsock.close()
loop.close()
