#!/usr/local/bin/python3
# coding: UTF-8
# Author: David
# Email: youchen.du@gmail.com
# Created: 2017-04-03 11:06
# Last modified: 2017-04-03 11:12
# Filename: test.py
# Description:
import threading
import time

import redis


conn = redis.Redis()


def publisher(n):
    time.sleep(1)
    for i in range(n):
        conn.publish('channel', i)
        time.sleep(1)


def run_pubsub():
    threading.Thread(target=publisher, args=(3,)).start()
    pubsub = conn.pubsub()
    pubsub.subscribe(['channel'])
    count = 0
    for item in pubsub.listen():
        print(item)
        count += 1
        if count == 4:
            pubsub.unsubscribe()
        elif count == 5:
            break


if __name__ == '__main__':
    run_pubsub()

