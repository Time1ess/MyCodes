#!/usr/local/bin/python3
# coding: UTF-8
# Author: David
# Email: youchen.du@gmail.com
# Created: 2017-02-19 12:10
# Last modified: 2017-02-19 15:50
# Filename: utils.py
# Description:
import re
import time
import sys

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


class TimeProfile:
    def __enter__(self):
        self.s = time.time()

    def __exit__(self, *args, **kwargs):
        e = time.time()
        print('[Time Cost]: --> {:5.2f}s <-- '.format(e-self.s))
