#!/usr/bin/python
# coding: UTF-8
# Author: David
# Email: youchen.du@gmail.com
# Created: 2016-04-23 14:42
# Last modified: 2016-04-23 14:42
# Filename: encrypt.py
# Description:
from random import shuffle
from copy import deepcopy
import sys

DEVIDE = '**^$&$$^&'
END = '%^$&#*'


def encrypt(in_name, ):
    fin = open(in_name, 'rb')
    fout = open('en_'+in_name, 'wb')
    code = open('cipher', 'wb')
    before = set()
    data = ''
    for line in fin.readlines():
        for ch in line:
            before.add(ch)
            data += ch
    fin.close()
    before = list(before)
    after = deepcopy(before)
    shuffle(after)
    mmap = {before[i]: after[i] for i in range(len(before))}
    for key, value in mmap.items():
        code.write(key+DEVIDE+value+END)
    code.close()
    for elem in data:
        fout.write(mmap.get(elem, elem))
    fout.close()


def decrypt(in_name, cipher_name):
    mmap = {}
    code = open(cipher_name, 'rb')
    codes = ''
    for elem in code.readlines():
        codes += elem
    cipher = codes.split(END)
    cipher = map(lambda x: x.split(DEVIDE), cipher)
    for item in cipher:
        if len(item) == 2:
            mmap[item[1]] = item[0]
    fin = open(in_name, 'rb')
    fout = open('de_'+in_name, 'wb')
    for line in fin.readlines():
        for ch in line:
            fout.write(mmap.get(ch, ch))
    fin.close()
    fout.close()

fin = fout = cipher = None

try:
    fin = sys.argv[1]
    cipher = sys.argv[2]
except Exception, e:
    pass
assert fin is not None
if not cipher:  # encrypt
    encrypt(fin)
else:  # decrypt
    decrypt(fin, cipher)
exit(0)
