#!/usr/local/bin/python3
# coding: UTF-8
# Author: David
# Email: youchen.du@gmail.com
# Created: 2017-05-09 13:37
# Last modified: 2017-05-09 13:39
# Filename: date_with_call_later.py
# Description:
import asyncio
import datetime


def display_date(loop, endtime):
    print(datetime.datetime.now())
    if loop.time() + 1.0 < endtime:
        loop.call_later(1, display_date, loop, endtime)
    else:
        loop.stop()


loop = asyncio.get_event_loop()
endtime = loop.time() + 5
loop.call_later(1, display_date, loop, endtime)
loop.run_forever()
loop.close()
