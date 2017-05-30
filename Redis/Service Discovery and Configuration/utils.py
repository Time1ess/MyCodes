#!/usr/local/bin/python3
# coding: UTF-8
# Author: David
# Email: youchen.du@gmail.com
# Created: 2017-05-04 15:51
# Last modified: 2017-05-04 16:08
# Filename: utils.py
# Description:
import time
import json
import functools


LAST_CHECKED = None
IS_UNDER_MAINTENANCE = False


def is_under_maintenance(conn):
    global LAST_CHECKED, IS_UNDER_MAINTENANCE

    if not LAST_CHECKED or LAST_CHECKED < time.time() - 1:
        LAST_CHECKED = time.time()
        IS_UNDER_MAINTENANCE = bool(conn.get('is-under-maintenance'))
    return IS_UNDER_MAINTENANCE


def set_config(conn, ktype, component, config):
    conn.set(
        'config:{}:{}'.format(ktype, component),
        json.dumps(config))


CONFIGS = {}
CHECKED = {}


def get_config(conn, ktype, component, wait=1):
    key = 'config:{}:{}'.format(ktype, component)

    if not CHECKED.get(key) or CHECKED.get(key) < time.time() - wait:
        CHECKED[key] = time.time()
        config = json.loads(conn.get(key) or '{}')
        old_config = CONFIGS.get(key)

        if old_config != config:
            CONFIGS[key] = config

    return CONFIGS.get(key)


REDIS_CONNECTIONS = {}


def redis_connection(component, wait=1):
    config_connection = redis.Redis(decode_responses=True)
    key = 'config:redis:' + component
    def wrapper(function):
        @functools.wraps(function)
        def call(*args, **kwargs):
            old_config = CONFIGS.get(key, object())
            config = get_config(
                config_connection, 'redis', component, wait)

            if config != old_config:
                REDIS_CONNECTIONS[key] = redis.Redis(**config)

            return function(REDIS_CONNECTIONS.get(key), *args, **kwargs)
        return call
    return wrapper


@redis_connection('logs')
def log_recent(conn, app, message):
    pass

# log_recent('main', 'User 235 logged in')
