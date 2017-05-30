#!/usr/local/bin/python3
# coding: UTF-8
# Author: David
# Email: youchen.du@gmail.com
# Created: 2017-05-09 13:35
# Last modified: 2017-05-09 13:36
# Filename: hello_call_soon.py
# Description:
import asyncio


def hello_world(loop):
    print('Hello World')
    loop.stop()


loop = asyncio.get_event_loop()
loop.call_soon(hello_world, loop)
loop.run_forever()
loop.close()
