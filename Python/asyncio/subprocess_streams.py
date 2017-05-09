#!/usr/local/bin/python3
# coding: UTF-8
# Author: David
# Email: youchen.du@gmail.com
# Created: 2017-05-09 18:43
# Last modified: 2017-05-09 18:51
# Filename: subprocess_streams.py
# Description:
import asyncio
import asyncio.subprocess
import sys


async def get_date():
    code = 'import datetime; print(datetime.datetime.now())'
    
    create = asyncio.create_subprocess_exec(sys.executable, '-c', code,
                                            stdout=asyncio.subprocess.PIPE)

    proc = await create

    data = await proc.stdout.readline()
    line = data.decode('ascii').rstrip()

    await proc.wait()
    return line


if sys.platform == 'win32':
    loop = asyncio.ProactorEventLoop()
    asyncio.set_event_loop(loop)
else:
    loop = asyncio.get_event_loop()

date = loop.run_until_complete(get_date())
print('Current date: {}'.format(date))
loop.close()
