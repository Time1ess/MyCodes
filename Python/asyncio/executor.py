#!/usr/local/bin/python3
# coding: UTF-8
# Author: David
# Email: youchen.du@gmail.com
# Created: 2017-05-09 19:18
# Last modified: 2017-05-09 19:28
# Filename: executor.py
# Description:
import asyncio
import time

from concurrent.futures import ProcessPoolExecutor


executor = ProcessPoolExecutor()
loop = asyncio.get_event_loop()
loop.set_default_executor(executor)


def slow_computing():
    endtime = time.time() + 10
    ret = 0
    while True:
        if time.time() > endtime:
            break
        ret += 1
        print('Slow computing in another process...')
        time.sleep(3)
    return ret


async def print_time():
    for i in range(10):
        print('>>>', time.time())
        await asyncio.sleep(0.8)


coro = loop.run_in_executor(None, slow_computing)
loop.run_until_complete(asyncio.gather(
    coro,
    print_time()))
print(coro.result())
loop.close()
