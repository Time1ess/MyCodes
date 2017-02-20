#!/usr/local/bin/python3
# coding: UTF-8
# Author: David
# Email: youchen.du@gmail.com
# Created: 2017-02-20 11:29
# Last modified: 2017-02-20 15:31
# Filename: extracters.py
# Description:
import os

from logging import info

from utils import read_lineno, LinesIndicator
from cleaners import DetailCleaner, BaseCleaner


class BaseExtracter:
    cleaner = BaseCleaner

    @classmethod
    def extract(cls, *args, **kwargs):
        raise NotImplementedError('Not Implemented.')


class CommentExtracter(BaseExtracter):
    keys = ['_id', 'iid', 'uid', 'creation_time', 'score', 'user_province',
            'user_level', 'color', 'size']

    @classmethod
    def extract(cls, fname, prefix='data', cleaner=None):
        if cleaner is None:
            cleaner = cls.cleaner()
        else:
            cleaner = cleaner()

        info('Extract from comments file')
        data = []
        full_path = os.path.join(prefix, fname)
        line_cnt = read_lineno(full_path)
        indicate = LinesIndicator(line_cnt, title='Extract Comments')
        clean = cleaner.clean
        with open(full_path, 'r') as f:
            for line in f:
                indicate()
                vals = line.strip('\n').split(',')
                if len(vals) != 9:
                    continue
                vals[4] = float(vals[4])
                d = {key: val for key, val in zip(cls.keys, vals)}
                clean(d)
                data.append(d)
            indicate(0)
        line_cnt = len(data)

        return data, line_cnt


class DetailExtracter(BaseExtracter):
    keys = ['id', 'name', 'shop', 'scores']
    cleaner = DetailCleaner

    @classmethod
    def extract(cls, fname='shoe_details.csv', prefix='data', cleaner=None):
        """
        Construct data dict from data file.
        """
        if cleaner is None:
            cleaner = cls.cleaner()
        else:
            cleaner = cleaner()

        info('Extract from details file')
        data = {}
        full_path = os.path.join(prefix, fname)
        line_cnt = read_lineno(full_path)
        indicate = LinesIndicator(line_cnt, title='Extract details')
        clean = cleaner.clean
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
                    d = {key: val for key, val in zip(cls.keys, vals)}
                    clean(d)
                    data[vals[0]] = d
            indicate(0)
        line_cnt = len(data)
        return data, line_cnt
