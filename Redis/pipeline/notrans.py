#!/usr/local/bin/python3
# coding: UTF-8
# Author: David
# Email: youchen.du@gmail.com
# Created: 2017-04-03 11:18
# Last modified: 2017-04-03 11:21
# Filename: notrans.py
# Description:
import time
import threading

import redis

conn = redis.Redis()


def notrans():
    print(conn.incr('notrans:'))
    time.sleep(.1)
    conn.incr('notrans:', -1)


for i in range(3):
    threading.Thread(target=notrans).start()
time.sleep(.5)


