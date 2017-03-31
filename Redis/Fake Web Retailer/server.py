#!/usr/local/bin/python3
# coding: UTF-8
# Author: David
# Email: youchen.du@gmail.com
# Created: 2017-03-31 15:26
# Last modified: 2017-03-31 17:33
# Filename: server.py
# Description:
import time
import json


def check_token(conn, token):
    return conn.hget('login:', token)


def update_token(conn, token, user, item=None):
    timestamp = time.time()
    conn.hset('login:', token, user)
    conn.zadd('recent:', token, timestamp)
    if item:
        conn.zadd('viewed:' + token, item, timestamp)
        conn.zremrangebyrank('viewed:' + token, 0, -26)
        conn.zincrby('viewed:', item, -1)


QUIT = False
LIMIT = 10000000


def add_to_cart(conn, token, item, count):
    if count <= 0:
        conn.hrem('cart:' + token, item)
    else:
        conn.hset('cart:' + token, item, count)


def clean_sessions(conn):
    while not QUIT:
        size = conn.zcard('recent:')
        if size <= LIMIT:
            time.sleep(1)
            continue

        end_index = min(size - LIMIT, 100)
        tokens = conn.zrange('recent:', 0, end_index - 1)

        session_keys = []
        for token in tokens:
            session_keys.append('viewed:' + token)
            session_keys.append('cart:' + token)

        conn.delete(*session_keys)
        conn.hdel('login:', *tokens)
        conn.zrem('recent:', *tokens)


def extract_item_id(request):
    item_id = '0'
    return item_id


def is_dynamic(request):
    return False


def can_cache(conn, request):
    item_id = extract_item_id(request)
    if not item_id or is_dynamic(request):
        return False

    rank = conn.zrank('viewed:', item_id)
    return rank is not None and rank < 10000


def hash_request(request):
    return request


def slow_callback(request):
    time.sleep(0.1)
    return 'finish:' + request


def cache_request(conn, request, callback):
    if not can_cache(request):
        return callback(request)

    page_key = 'cache:' + hash_request(request)
    content = conn.get(page_key)

    if not content:
        content = callback(request)
        conn.setex(page_key, content, 1)
    else:
        content += '(cache)'

    return content


def schedule_row_cache(conn, row_id, delay):
    conn.zadd('delay:', row_id, delay)
    conn.zadd('schedule:', row_id, time.time())


def cache_rows(conn):
    while not QUIT:
        next_schedule = conn.zrange('schedule:', 0, 0, withscores=True)
        now = time.time()
        if not next_schedule or next_schedule[0][1] > now:
            time.sleep(0.05)
            continue

        row_id = next_schedule[0][0]
        delay = conn.zscore('delay:', row_id)
        if delay <= 0:
            conn.zrem('delay:', row_id)
            conn.zrem('schedule:', row_id)
            conn.delete('inv:' + row_id)

        def get_row(row_id):
            # Fake func
            return [row_id]

        row = get_row(row_id)
        conn.zadd('schedule:', row_id, now + delay)
        conn.set('inv:' + row_id, json.dumps(row))


def rescale_viewed(conn):
    while not QUIT:
        conn.zremrangebyrank('viewed:', 0, -20001)
        conn.zinterstore('viewed:', {'viewed:': .5})
        time.sleep(300)
