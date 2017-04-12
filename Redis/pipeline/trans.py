#!/usr/local/bin/python3
# coding: UTF-8
# Author: David
# Email: youchen.du@gmail.com
# Created: 2017-04-03 11:21
# Last modified: 2017-04-03 11:26
# Filename: trans.py
# Description:
import time
import threading

import redis


conn = redis.Redis()


def trans():
    pipeline = conn.pipeline()
    pipeline.incr('trans:')
    time.sleep(.1)
    pipeline.incr('trans:', -1)
    print(pipeline.execute()[0])


for i in range(3):
    threading.Thread(target=trans).start()
time.sleep(.5)
