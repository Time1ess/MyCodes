#!/usr/local/bin/python3
# coding: UTF-8
# Author: David
# Email: youchen.du@gmail.com
# Created: 2017-05-09 18:34
# Last modified: 2017-05-09 18:51
# Filename: subprocess_transport_protocol.py
# Description:
import asyncio
import sys


class DateProtocol(asyncio.SubprocessProtocol):
    def __init__(self, exit_future):
        self.exit_future = exit_future
        self.output = bytearray()

    def pipe_data_received(self, fd, data):
        self.output.extend(data)

    def process_exited(self):
        self.exit_future.set_result(True)


async def get_date(loop):
    code = 'import datetime; print(datetime.datetime.now())'
    exit_future = asyncio.Future(loop=loop)

    create = loop.subprocess_exec(lambda: DateProtocol(exit_future),
                                   sys.executable, '-c', code,
                                   stdin=None, stderr=None)
    transport, protocol = await create

    await exit_future

    transport.close()

    data = bytes(protocol.output)
    return data.decode('ascii').rstrip()


if sys.platform == 'win32':
    loop = asyncio.ProactorEventLoop()
else:
    loop = asyncio.get_event_loop()

date = loop.run_until_complete(get_date(loop))
print('Current date: {}'.format(date))
loop.close()
