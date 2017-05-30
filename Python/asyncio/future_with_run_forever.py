#!/usr/local/bin/python3
# coding: UTF-8
# Author: David
# Email: youchen.du@gmail.com
# Created: 2017-05-09 14:11
# Last modified: 2017-05-09 14:14
# Filename: future_with_run_forever.py
# Description:
import asyncio


async def slow_operation(future):
    print('Working...')
    await asyncio.sleep(1)
    future.set_result('Future is done!')


def got_result(future):
    print(future.result())
    loop.stop()


loop = asyncio.get_event_loop()
future = asyncio.Future()
asyncio.ensure_future(slow_operation(future))
future.add_done_callback(got_result)
try:
    print('Start run loop')
    loop.run_forever()
finally:
    loop.close()
