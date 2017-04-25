#!/usr/local/bin/python3
# coding: UTF-8
# Author: David
# Email: youchen.du@gmail.com
# Created: 2017-04-25 14:45
# Last modified: 2017-04-25 15:22
# Filename: counter.py
# Description:
import time
import bisect

import redis


PRECISION = [1, 5, 60, 300, 3600, 18000, 86400]


def update_counter(conn, name, count=1, now=None):
    now = now or time.time()
    pipe = conn.pipeline()
    for prec in PRECISION:
        pnow = int(now / prec) * prec
        hash_name = '{}:{}'.format(prec, name)
        pipe.zadd('known:', hash_name, 0)
        pipe.zincrby('count:' + hash_name, pnow, count)
    pipe.execute()


def get_counter(conn, name, precision):
    hash_name = '{}:{}'.format(precision, name)
    data = conn.hgetall('count:' + hash_name)
    rets = []
    for key, val in data.items():
        rets.append((int(key), int(val)))
    rets.sort()
    return rets


QUIT = False
SAMPLE_COUNT = 50


def clean_counter(conn):
    pipe = conn.pipeline(True)
    passes = 0
    while not QUIT:
        start = time.time()
        index = 0
        while index < conn.zcard('known:'):
            hash_names = conn.zrange('known:', index, index)
            index += 1
            if not hash_names:
                break
            hash_name = hash_names[0]
            prec = int(hash_name.partition(b':')[0])
            bprect = int(prec // 60) or 1
            if passes % bprec:
                continue

            cutoff = time.time() - SAMPLE_COUNT * prec
            hkey = 'count:' + hash_name
            samples = [int(key) for key in conn.hkeys(hkey)]
            samples.sort()
            remove = bisect.bisect_right(samples, cutoff)

            if remove:
                conn.hdel(hkey, *samples[:remove])
                if remove == len(samples):
                    try:
                        pipe.watch(hkey)
                        if not pipe.hlen(hkey):
                            pipe.multi()
                            pipe.zrem('known:', hash_name)
                            pipe.execute()
                            index -= 1
                        else:
                            pipe.unwatch()
                    except redis.exceptions.WatchError:
                        pass
        passes += 1
        duration = min(int(time.time() - start) + 1, 60)
        time.sleep(max(60 - duration, 1))
