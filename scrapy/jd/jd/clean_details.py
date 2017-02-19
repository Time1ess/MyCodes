#!/usr/local/bin/python3
# coding: UTF-8
# Author: David
# Email: youchen.du@gmail.com
# Created: 2017-02-18 15:39
# Last modified: 2017-02-19 17:48
# Filename: clean_details.py
# Description:
import os

from logging import info, debug

from utils import male_words, female_words, cross_words, LinesIndicator
from utils import read_lineno


DETAIL_FILENAME = 'shoe_details.csv'
PREFIX = 'data'
keys = ['id', 'name', 'shop', 'scores']


def extract(fname=DETAIL_FILENAME, prefix=PREFIX):
    """
    Construct data dict from data file.
    """
    info('Extract from details file')
    data = {}
    full_path = os.path.join(prefix, fname)
    line_cnt = read_lineno(full_path)
    indicate = LinesIndicator(line_cnt, title='Extract details')
    with open(full_path, 'r') as f:
        for line in f:
            indicate()
            vals = line.strip('\n').split(',')
            vals[-1] = vals[-1].split('|')
            for idx in range(len(vals[-1])):
                try:
                    vals[-1][idx] = float(vals[-1][idx])
                except ValueError:
                    vals[-1][idx] = -1

            valid = True
            if len(vals) != 4 or any(x == 'None' for x in vals):
                valid = False
            if valid:
                data[vals[0]] = {key: val for key, val in zip(keys, vals)}
        indicate(0)

    line_cnt = len(data)
    find_sex_orient(data, line_cnt)
    return data, line_cnt


def find_sex_orient(data, line_cnt):
    info('Find sex orientation')
    male_shoes = 0
    female_shoes = 0
    neutral_shoes = 0

    indicate = LinesIndicator(line_cnt, title='Find sex')
    for record in data.values():
        indicate()
        male_count, female_count = 0, 0
        name = record['name'].lower()

        male_count = sum(name.count(word) for word in male_words)
        # 'man' in 'woman', so subtract it
        male_count -= sum(name.count(word) for word in cross_words)
        female_count = sum(name.count(word) for word in female_words)

        if male_count > female_count:
            record['sex'] = '男'
            male_shoes += 1
        elif female_count > male_count:
            record['sex'] = '女'
            female_shoes += 1
        else:
            record['sex'] = '中性'
            neutral_shoes += 1
    indicate(0)


if __name__ == '__main__':
    extract()
