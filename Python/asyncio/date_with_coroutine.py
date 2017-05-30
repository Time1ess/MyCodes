#!/usr/local/bin/python3
# coding: UTF-8
# Author: David
# Email: youchen.du@gmail.com
# Created: 2017-05-09 13:53
# Last modified: 2017-05-09 13:59
# Filename: date_with_coroutine.py
# Description:
import asyncio
import datetime


async def display_date(loop):
    endtime = loop.time() + 5
    while True:
        print(datetime.datetime.now())
        if loop.time() + 1 >= endtime:
            break
        await asyncio.sleep(1)


loop = asyncio.get_event_loop()
loop.run_until_complete(display_date(loop))
loop.close()
