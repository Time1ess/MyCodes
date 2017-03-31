#!/usr/local/bin/python3
# coding: UTF-8
# Author: David
# Email: youchen.du@gmail.com
# Created: 2017-03-31 15:52
# Last modified: 2017-03-31 17:19
# Filename: profiles.py
# Description:
import time
import random

import redis

from server import update_token
from server import cache_request, slow_callback


def report(reports):
    print('Performance:')
    for r in reports:
        print('\t\t', r)


def profile_update_token(conn):
    token = 'test_token'
    user = 'test_user'
    item = 'test_item'
    LOOPS = 10000

    start = time.time()
    for _ in range(LOOPS):
        update_token(conn, token, user, item)
    end = time.time()
    elapsed = end - start
    fmt = ('Performance: {} loops, {:.3f} seconds in total, '
           '{} times in a second')
    reports = [fmt.format(LOOPS, elapsed, int(LOOPS / elapsed))]
    report(repors)


def profile_cache_request(conn):
    requests = [str(x) for x in range(5)]
    hit_cache = 0
    LOOPS = 200
    start = time.time()
    for _ in range(LOOPS):
        request = random.choice(requests)
        response = cache_request(conn, request, slow_callback)
        if response.endswith('(cache)'):
            hit_cache += 1
    end = time.time()

    cache_fmt = '{} loops, {} hits in cache, cache rate {:.2%}.'
    time_fmt = '{:.3f} seconds in total'
    cache_report = cache_fmt.format(LOOPS, hit_cache, hit_cache / LOOPS)
    time_report = time_fmt.format(end-start)
    reports = [cache_report, time_report]
    report(reports)


if __name__ == '__main__':
    conn = redis.Redis(decode_responses=True)
    # profile_update_token(conn)
    profile_cache_request(conn)
