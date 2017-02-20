#!/usr/local/bin/python3
# coding: UTF-8
# Author: David
# Email: youchen.du@gmail.com
# Created: 2017-02-19 12:10
# Last modified: 2017-02-20 14:14
# Filename: utils.py
# Description:
import time
import sys
import logging
import subprocess

from logging import debug


logging.basicConfig(
    level=logging.INFO,
    format=('%(asctime)s %(filename)-25s[line:%(lineno)4d] '
            '%(levelname)-8s %(message)-30s'),
    datefmt='%m-%d-%Y %H:%M:%S',
    stream=sys.stdout)

colors = ['粉', '红', '蓝', '橙', '白', '黑', '紫', '绿', '灰', '黄',
          '棕', '米', '银', '香槟', '裸', '咖啡', '卡其', '金', '铅',
          '兰', '咖', '驼', '枪', '栗', '古铜', '桔', '蜜蜡',
          '铁锈', '沙', '花', '橘', '藏', '青', '杏', '月', '褐', '墨绿']


def read_lineno(fname):
    ret = subprocess.check_output(['wc', '-l', fname]).decode('utf-8')
    cnt = ret.strip(' ').split(' ')[0]
    return int(cnt)


class LinesIndicator:

    def _out(self, msg):
        sys.stdout.flush()
        sys.stdout.write(msg)

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
