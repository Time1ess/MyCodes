#!/usr/local/bin/python3
# coding: UTF-8
# Author: David
# Email: youchen.du@gmail.com
# Created: 2017-05-09 13:50
# Last modified: 2017-05-09 13:52
# Filename: hello_coroutine.py
# Description:
import asyncio


async def hello_world():
    print('Hello World!')


loop = asyncio.get_event_loop()
loop.run_until_complete(hello_world())
loop.close()
