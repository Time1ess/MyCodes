#!/usr/local/bin/python3
# coding: UTF-8
# Author: David
# Email: youchen.du@gmail.com
# Created: 2017-05-09 14:24
# Last modified: 2017-05-09 14:31
# Filename: parallel_exceution_of_tasks.py
# Description:
import asyncio


async def factorial(name, number):
    f = 1
    for i in range(2, number+1):
        print('Task {}: Compute factorial ({})...'.format(name, i))
        await asyncio.sleep(1)
        f *= i
    print('Task {}: factorial({}) = {}'.format(name, number, f))


loop = asyncio.get_event_loop()
loop.run_until_complete(asyncio.gather(
    factorial('A', 2),
    factorial('B', 3),
    factorial('C', 4),
    factorial('D', 5),
))
loop.close()
