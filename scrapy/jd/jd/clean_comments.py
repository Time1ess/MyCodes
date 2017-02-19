#!/usr/local/bin/python3
# coding: UTF-8
# Author: David
# Email: youchen.du@gmail.com
# Created: 2017-02-18 16:56
# Last modified: 2017-02-19 17:50
# Filename: clean_comments.py
# Description:
import os

from logging import info, debug

from utils import colors, nonsense_pat, num_pat, LinesIndicator, read_lineno


COMMENTS_FILENAME = 'shoe_comments.csv'
PREFIX = 'data'
keys = ['_id', 'iid', 'uid', 'creation_time', 'score', 'user_province',
        'user_level', 'color', 'size']


def extract(fname=COMMENTS_FILENAME, prefix=PREFIX):
    """
    Construct data dict from data file.
    """
    info('Extract from comments file')
    data = []
    full_path = os.path.join(prefix, fname)
    line_cnt = read_lineno(full_path)
    indicate = LinesIndicator(line_cnt, title='Extract Comments')
    with open(full_path, 'r') as f:
        for line in f:
            indicate()
            vals = line.strip('\n').split(',')
            if len(vals) != 9:
                continue
            vals[4] = float(vals[4])
            data.append({key: val for key, val in zip(keys, vals)})
        indicate(0)
    line_cnt = len(data)

    clean_colors(data, line_cnt)
    clean_sizes(data, line_cnt)

    return data, line_cnt


def clean_colors(data, line_cnt):
    info('Clean colors')
    indicate = LinesIndicator(line_cnt, title='Clean colors')
    for record in data:
        indicate()
        origin_color = record['color']
        record['_color'] = origin_color
        origin_color = nonsense_pat.sub('', origin_color)
        record['color'] = []
        for color in colors:
            if color in origin_color:
                record['color'].append(color)
    indicate(0)


def clean_sizes(data, line_cnt):
    info('Clean sizes')
    indicate = LinesIndicator(line_cnt, title='Clean sizes')
    for record in data:
        indicate()
        size = record['size']
        record['_size'] = size
        res = [float(x) for x in num_pat.findall(size)]
        for x in res:
            if 15 <= x <= 50:
                record['size'] = x
                break
        else:
            record['size'] = 0
    indicate(0)


if __name__ == '__main__':
    extract('small_comments.csv')
