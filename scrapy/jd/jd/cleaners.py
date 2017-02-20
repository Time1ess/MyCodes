#!/usr/local/bin/python3
# coding: UTF-8
# Author: David
# Email: youchen.du@gmail.com
# Created: 2017-02-20 11:05
# Last modified: 2017-02-20 15:38
# Filename: cleaners.py
# Description:
import re
import types

from utils import colors


class BaseCleaner:
    nonsense_words = ['货到付款', '随机色', '如图', '赠品勿拍',
                      '支持', '赠品', '赠']
    nonsense_pat = re.compile('|'.join(nonsense_words)+'|[a-zA-Z0-9\-]')
    male_words = ['男', 'man', 'male', 'boy']
    female_words = ['女', 'woman', 'female', 'girl']
    cross_words = ['woman', 'female']

    def __init__(self):
        attrs = [getattr(self, x) for x in dir(self) if not x.startswith('_')
                 and x.startswith('clean_')]
        methods = [x for x in attrs if isinstance(x, types.MethodType)]
        self.washers = [method() for method in methods]
        for washer in self.washers:
            next(washer)  # fire generator

    def clean(self, record):
        for washer in self.washers:
            washer.send(record)


class ColorCleanerMixin(BaseCleaner):
    def clean_colors(self, *args, **kwargs):
        raise NotImplementedError("Not Implemented.")


class SizeCleanerMixin(BaseCleaner):
    def clean_sizes(self, *args, **kwargs):
        raise NotImplementedError("Not Implemented.")


class ColorCleaner(ColorCleanerMixin):
    def clean_colors(self):
        while True:
            record = yield
            origin_color = record['color']
            record['_color'] = origin_color
            origin_color = self.nonsense_pat.sub('', origin_color)
            record['color'] = []
            for color in colors:
                if color in origin_color:
                    record['color'].append(color)


class ShoeCleaner(ColorCleaner, SizeCleanerMixin):
    size_pat = re.compile('(\d+(?:\d|\.)\d*)')

    def clean_sizes(self):
        while True:
            record = yield
            size = record['size']
            record['_size'] = size
            res = [float(x) for x in self.size_pat.findall(size)]
            for x in res:
                if 15 <= x <= 50:
                    record['size'] = x
                    break
            else:
                record['size'] = 0


class DetailCleaner(BaseCleaner):
    int_pat = re.compile('(\d+)')
    non_int_pat = re.compile('(\D+)')
    size_pat = re.compile('([7-9][05][A-D]|[A-D][7-9][05])')

    def clean_sex(self):
        while True:
            record = yield
            male_count, female_count = 0, 0
            name = record['name'].lower()
            male_count = sum(name.count(word) for word in self.male_words)
            # 'man' in 'woman', so subtract it
            male_count -= sum(name.count(word) for word in self.cross_words)
            female_count = sum(name.count(word) for word in self.female_words)
            if male_count > female_count:
                record['sex'] = '男'
            elif female_count > male_count:
                record['sex'] = '女'
            else:
                record['sex'] = '中性'
