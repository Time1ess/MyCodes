#!/usr/local/bin/python3
# coding: UTF-8
# Author: David
# Email: youchen.du@gmail.com
# Created: 2017-02-19 12:10
# Last modified: 2017-02-19 17:46
# Filename: utils.py
# Description:
import re
import time
import sys
import logging
import subprocess

from logging import info, debug

logging.basicConfig(
    level=logging.INFO,
    format=('%(asctime)s %(filename)-25s[line:%(lineno)4d] '
        '%(levelname)-8s %(message)s'),
    datefmt='%m-%d-%Y %H:%M:%S',
    stream=sys.stdout)

colors = ['粉', '红', '蓝', '橙', '白', '黑', '紫', '绿', '灰', '黄',
          '棕', '米', '银', '香槟', '裸', '咖啡', '卡其', '金', '铅',
          '兰', '咖', '驼', '枪', '栗', '古铜', '桔', '蜜蜡',
          '铁锈', '沙', '花', '橘', '藏', '青', '杏', '月', '褐', '墨绿']
nonsense_words = ['货到付款', '随机色', '如图', '赠品勿拍',
                  '支持', '赠品', '赠']
nonsense_pat = re.compile('|'.join(nonsense_words)+'|[a-zA-Z0-9\-]')
male_words = ['男', 'man', 'male', 'boy']
female_words = ['女', 'woman', 'female', 'girl']
cross_words = ['woman', 'female']
num_pat = re.compile('(\d+(?:\d|\.)\d*)')

def _out(msg):
    sys.stdout.flush()
    sys.stdout.write(msg)


def read_lineno(fname):
    ret = subprocess.check_output(['wc', '-l', fname]).decode('utf-8')
    cnt = ret.strip(' ').split(' ')[0]
    return int(cnt)


class TimeProfile:
    def __enter__(self):
        self.s = time.time()
        info('[Time Cost Profile]')

    def __exit__(self, *args, **kwargs):
        e = time.time()
        info('[Time Cost]: --> {:5.2f}s <-- '.format(e-self.s))


class LinesIndicator:
    def __init__(self, max_lines, chunk=1e5,
                 log_fmt='>>> Processed:{:>10d}/{:>10d}, Remaining: {:>5d}s',
                 title='LinesIndicator', to_log=False):
        if chunk < 0:
            raise ValueError('Chunk size should be positive')
        self._lineno = 0
        self._max_lines = max_lines
        self._chunk = chunk
        self._log_fmt = log_fmt + '\r'
        self._to_log = to_log
        self._title = title
        if to_log:
            self._out = debug
        else:
            self._out = _out
        self._stime = time.time()

    def __call__(self, *args):
        self._lineno += 1
        if not args and self._lineno % self._chunk == 0:
            elapsed = time.time() - self._stime
            r = int((self._max_lines-self._lineno) * elapsed / self._lineno)
            output = self._log_fmt.format(self._lineno, self._max_lines, r)
            self._out('{:25s} {}'.format(self._title, output))
        elif args:
            if not self._to_log:
                sys.stdout.flush()
