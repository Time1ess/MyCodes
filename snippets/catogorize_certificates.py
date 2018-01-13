import os
import re
import shutil
import os.path as osp

from collections import defaultdict

import xlrd


data = xlrd.open_workbook('20170727092647964.xls')
table = data.sheets()[0]
nrows = table.nrows
school = ''
schools = set()
teacher_school = {}
for row in range(3, nrows):
    _school = table.row(row)[1].value
    school = _school if _school else school
    teacher = table.row(row)[2].value
    teacher_school[teacher] = school
    schools.add(school)


base = '证书'
files = [(f, re.split(r'[-.]', f)) for f in os.listdir(base)]


target = '证书分类'
if osp.exists(target):
    shutil.rmtree(target)
os.mkdir(target)

for fname, (uid, province, name, ext) in files:
    school = teacher_school[name]
    src = osp.join(base, fname)
    dst = osp.join(target, school)
    if not osp.exists(dst):
        os.mkdir(dst)
    shutil.copy(src, dst)
