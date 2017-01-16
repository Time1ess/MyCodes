#!/usr/local/bin/python3
# coding: UTF-8
# Author: David
# Email: youchen.du@gmail.com
# Created: 2017-01-12 07:58
# Last modified: 2017-01-14 17:19
# Filename: parse.py
# Description:
import re
from collections import defaultdict, namedtuple

iid_name_pat = re.compile('^(.*?) (.*?) ')
sex_pat = re.compile('性别：(.*?) ')
birth_pat = re.compile('生日：(\d*).*?(\d*).*?(\d*).*? ')
sign_pat = re.compile(' (.*?)座')
hometown_pat = re.compile('家乡：(.*?) (.*?) ')

Person = namedtuple('Person', ['iid', 'name', 'sex', 'year', 'month', 'day',
                               'pro', 'city'])

data = []

def get(line, pat, n=1):
    d = pat.findall(line)
    if d:
        return d[0]
    return '' if n == 1 else ['']*n

with open('user_infos.txt') as f:
    for line in f:
        line = line.strip('\r\n')
        find = iid_name_pat.findall(line)
        if find:
            iid, name = find[0]
            sex = get(line, sex_pat)
            year, month, day = get(line, birth_pat, 3)
            pro, city = get(line, hometown_pat, 2)

            person = Person(iid, name, sex, year, month, day, pro, city)
            data.append(person)
