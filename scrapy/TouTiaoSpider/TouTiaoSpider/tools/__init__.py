#!/usr/bin/python
# coding: UTF-8
# Author: David
# Email: youchen.du@gmail.com
# Created: 2016-11-16 10:31
# Last modified: 2016-11-16 17:54
# Filename: __init__.py
# Description:
import time


def get_now_stamp():
    stamp = int(time.time())
    return stamp

def gen_payload(category='__all__', utm_source='toutiao',
                widen=1, 
                _as='A16538021BBC03A',
                _cp='582B8C40E39A0E1'):
    max_behot_time = max_behot_time_tmp = get_now_stamp()
    payload = {
        'category': category, 'utm_source': utm_source,
        'widen': widen, 'max_behot_time': max_behot_time,
        'max_behot_time_tmp': max_behot_time_tmp,
        'as': _as, '_cp': _cp}
    payload_str = ''
    for key, value in payload.iteritems():
        payload_str += '%s=%s&' % (key, value)
    return payload_str
