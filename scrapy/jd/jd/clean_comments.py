#!/usr/local/bin/python3
# coding: UTF-8
# Author: David
# Email: youchen.du@gmail.com
# Created: 2017-02-18 16:56
# Last modified: 2017-02-19 15:56
# Filename: clean_comments.py
# Description:
import os

from utils import colors, nonsense_pat, num_pat


COMMENTS_FILENAME = 'shoe_comments.csv'
PREFIX = 'data'
keys = ['_id', 'iid', 'uid', 'creation_time', 'score', 'user_province',
        'user_level', 'color', 'size']


def extract(fname=COMMENTS_FILENAME, prefix=PREFIX):
    """
    Construct data dict from data file.
    """
    data = {}
    with open(os.path.join(prefix, fname), 'r') as f:
        for line in f:
            vals = line.strip('\n').split(',')
            if len(vals) != 9:
                continue
            vals[4] = float(vals[4])
            data[vals[0]] = {key: val for key, val in zip(keys, vals)}

    clean_colors(data)
    clean_sizes(data)

    return data


def clean_colors(data):
    for record in data.values():
        origin_color = record['color']
        record['_color'] = origin_color
        origin_color = nonsense_pat.sub('', origin_color)
        record['color'] = []
        for color in colors:
            if color in origin_color:
                record['color'].append(color)


def clean_sizes(data):
    for record in data.values():
        size = record['size']
        record['_size'] = size
        res = [float(x) for x in num_pat.findall(size)]
        for x in res:
            if 15 <= x <= 50:
                record['size'] = x
                break
        else:
            record['size'] = 0


if __name__ == '__main__':
    extract('small_comments.csv')
