#!/usr/local/bin/python3
# coding: UTF-8
# Author: David
# Email: youchen.du@gmail.com
# Created: 2017-05-09 13:59
# Last modified: 2017-05-09 14:05
# Filename: chain_coroutines.py
# Description:
import asyncio


async def compute(x, y):
    print('Computing {} + {} ...'.format(x, y))
    await asyncio.sleep(1)
    return x + y


async def print_sum(x, y):
    result = await compute(x, y)
    print('{} + {} = {}'.format(x, y, result))


loop = asyncio.get_event_loop()
loop.run_until_complete(print_sum(1, 2))
loop.close()
