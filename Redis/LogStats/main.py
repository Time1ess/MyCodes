#!/usr/local/bin/python3
# coding: UTF-8
# Author: David
# Email: youchen.du@gmail.com
# Created: 2017-05-03 21:06
# Last modified: 2017-05-03 21:32
# Filename: main.py
# Description:
import random
import time
import uuid

from datetime import datetime

import redis


def update_stats(conn, context, ktype, value, timeout=5):
    destination = 'stats:{}:{}'.format(context, ktype)
    start_key = '{}:start'.format(destination)
    pipe = conn.pipeline()
    end = time.time() + timeout
    while time.time() < end:
        try:
            pipe.watch(start_key)
            now = datetime.utcnow().timetuple()
            hour_start = datetime(*now[:4]).isoformat()

            existing = pipe.get(start_key)
            pipe.multi()
            if existing and existing < hour_start:
                pipe.rename(destination, '{}:last'.format(destination))
                pipe.rename(start_key, '{}:pstart'.format(destination))
                pipe.set(start_key, hour_start)
            elif not existing:
                pipe.set(start_key, hour_start)

            tkey1 = str(uuid.uuid4())
            tkey2 = str(uuid.uuid4())
            pipe.zadd(tkey1, 'min', value)
            pipe.zadd(tkey2, 'max', value)
            pipe.zunionstore(destination, [destination, tkey1],
                             aggregate='min')
            pipe.zunionstore(destination, [destination, tkey2],
                             aggregate='max')
            pipe.delete(tkey1, tkey2)
            pipe.zincrby(destination, 'count')
            pipe.zincrby(destination, 'sum', value)
            pipe.zincrby(destination, 'sumsq', value * value)

            return pipe.execute()[-3:]
        except redis.exceptions.WatchError:
            continue


def get_stats(conn, context, ktype):
    key = 'stats:{}:{}'.format(context, ktype)
    data = dict(conn.zrange(key, 0, -1, withscores=True))
    data['average'] = data['sum'] / data['count']
    numerator = data['sumsq'] - data['sum'] ** 2 / data['count']
    data['stddev'] = (numerator / (data['count'] - 1 or 1)) ** 0.5
    return data


def main():
    # You may want to set hour_start from now[:4] to now[:6]
    # in update_stats to test the function
    conn = redis.Redis(decode_responses=True)
    conn.flushdb()
    start = time.time()
    for i in range(10):
        tick = time.time()
        for _ in range(100):
            val = random.random() * (tick - start)  # Range grows with time
            update_stats(conn, 'random', 'rand', val)
        stats = list(get_stats(conn, 'random', 'rand').items())
        stats.sort(key=lambda x: x[0])
        print(stats)
        time.sleep(1.5)

if __name__ == '__main__':
    main()
