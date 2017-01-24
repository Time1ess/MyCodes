#!/usr/local/bin/python3
# coding: UTF-8
# Author: David
# Email: youchen.du@gmail.com
# Created: 2017-01-12 07:58
# Last modified: 2017-01-24 11:03
# Filename: visualize.py
# Description:
import re
import os
import pickle
import sys
import matplotlib.pyplot as plt

from collections import defaultdict, namedtuple
from functools import partial

from matplotlib.backends.backend_pdf import PdfPages

data_file = 'users_infos.dat'
start_year = 2012
FORCE_REGEN = False


iid_name_pat = re.compile('^(\d+?)\s+(.*?) ')
sex_pat = re.compile('性别：(.*?) ')
birth_pat = re.compile('生日：(\d*)[年|后](\d*)月(\d*)日 ')
sign_pat = re.compile(' (.*?)座')
hometown_pat = re.compile('家乡：(.*?) (.*?) ')
last_online_pat = re.compile('最后登录：(\d*?)年(\d*?)月(\d*?)日 (\d*?):(\d*?)')

Person = namedtuple('Person', ['iid', 'name', 'sex', 'year', 'month', 'day',
                               'pro', 'city', 'lyear', 'lmonth', 'lday',
                               'lhour', 'lminute'])


def _print(users, prop):
    for user in users:
        print(getattr(user, prop))


def get(line, pat, n=1):
    d = pat.findall(line)
    if d:
        return d[0]
    return '' if n == 1 else ['']*n


def get_users():
    users = []
    with open('user_infos.txt') as f:
        idx = 0
        for line in f:
            idx += 1
            if idx % 50000 == 0:
                sys.stdout.flush()
                sys.stdout.write('Total read : {0:10} lines.\r'.format(idx))
            line = line.strip('\r\n')
            find = iid_name_pat.findall(line)
            if find:
                iid, name = find[0]
                sex = get(line, sex_pat)
                year, month, day = get(line, birth_pat, 3)
                pro, city = get(line, hometown_pat, 2)
                lyear, lmonth, lday, lhour, lminute = get(line, last_online_pat, 5)

                ud = [iid, name, sex, year, month, day, pro, city, lyear,
                      lmonth, lday, lhour, lminute]
                if not any(ud[2:]):
                    continue
                person = Person(*ud)
                users.append(person)
    sys.stdout.flush()
    return users


def draw_losing_rate(users):
    f = plt.figure(dpi=100)

    # last_online
    cnts = defaultdict(partial(defaultdict, int))
    for user in users:
        if not user.lyear or not user.lmonth or not user.lday:
            continue
        if int(user.lyear) < 2012:
            continue
        cnts[int(user.lyear)][int(user.lmonth)] += 1

    values = []
    indices = []
    total_cnt = 0
    for year in range(2012, 2018):
        months = list(cnts[year].items())
        months.sort(key=lambda x: x[0])
        for month, cnt in months:
            total_cnt += cnt
            values.append(total_cnt)
            indices.append('{0}.{1}'.format(year, month))
    values = [1-x/total_cnt for x in values]
    iindices = range(1, len(values)+1)

    p4 = plt.subplot(111)
    p4.plot(iindices, values)
    p4.set_xlabel('最后上线时间')
    p4.set_ylabel('人数比')
    p4.set_title('人人网用户流失比例图(用户数:{0})'.format(total_cnt))
    p4.set_xlim((1, len(iindices)+1))
    r = range(1, len(indices)//5+1)
    p4.set_xticks([l*5 for l in r])
    p4.set_xticklabels(indices[::5])
    
    return f


def draw_birth(users):
    f = plt.figure(dpi=100)

    # birth - year
    year_cnt = defaultdict(int)
    for user in users:
        if not user.year:
            continue
        year_cnt[int(user.year)] += 1
    years = list(year_cnt.items())

    years = list(filter(lambda x: 1960 < x[0] < 2008, years))
    total_cnt = 0
    for year, cnt in years:
        total_cnt += cnt
    years = [(year, cnt) for year, cnt in years if cnt/total_cnt > 0.0005]

    indices = [year for year, cnt in years]
    values = [cnt for year, cnt in years]

    p1 = plt.subplot(221)
    p1.bar(indices, values)
    p1.set_xlabel('出生年份')
    p1.set_ylabel('人数')
    p1.set_title('人人网用户出生年份分布直方图(用户数:{0})'.format(total_cnt))

    # birth - month
    month_cnt = defaultdict(int)
    for user in users:
        if not user.month:
            continue
        month_cnt[int(user.month)] += 1
    months = list(month_cnt.items())

    months = list(filter(lambda x: 0 < x[0] < 13, months))
    total_cnt = 0
    for month, cnt in months:
        total_cnt += cnt

    indices = [month for month, cnt in months]
    values = [cnt for month, cnt in months]

    p2 = plt.subplot(222)
    p2.bar(indices, values)
    p2.set_xlabel('出生月份')
    p2.set_ylabel('人数')
    p2.set_title('人人网用户出生月份分布直方图(用户数:{0})'.format(total_cnt))
    p2.set_xlim((1, 13))
    r = range(1, 13)
    p2.set_xticks([l+0.4 for l in r])
    p2.set_xticklabels(([str(l) for l in r]))

    # birth - day
    day_cnt = defaultdict(int)
    for user in users:
        if not user.day:
            continue
        day_cnt[int(user.day)] += 1
    days = list(day_cnt.items())

    days = list(filter(lambda x: 0 < x[0] < 32, days))
    total_cnt = 0
    for day, cnt in days:
        total_cnt += cnt

    indices = [day for day, cnt in days]
    values = [cnt for day, cnt in days]

    p3 = plt.subplot(223)
    p3.bar(indices, values)
    p3.set_xlabel('出生日期')
    p3.set_ylabel('人数')
    p3.set_title('人人网用户出生日期分布直方图(用户数:{0})'.format(total_cnt))
    p3.set_xlim((1, 32))
    r = range(1, 32)
    p3.set_xticks([l+0.4 for l in r])
    p3.set_xticklabels(([str(l) for l in r]))

    # birth - sex
    male_cnt = 0
    female_cnt = 0
    for user in users:
        if not user.sex:
            continue
        if user.sex == '男':
            male_cnt += 1
        elif user.sex == '女':
            female_cnt += 1

    p4 = plt.subplot(224)
    p4.bar([1, 2], [male_cnt, female_cnt])
    p4.set_xlabel('性别')
    p4.set_ylabel('人数')
    p4.set_title('人人网用户性别分布直方图(用户数:{0})'.format(
        male_cnt+female_cnt))
    p4.set_xlim((1, 3))
    p4.set_xticks([1.4, 2.4])
    p4.set_xticklabels(['男', '女'])

    return f


def draw_geo(users):
    f = plt.figure(dpi=100)

    pros_cnt = defaultdict(int)
    for user in users:
        if not user.pro:
            continue
        pros_cnt[user.pro] += 1
    pros = list(pros_cnt.items())
    pros = list(filter(lambda x: x[1] > 20, pros))
    pros_cnt = defaultdict(int)
    total_cnt = sum(map(lambda x: x[1], pros))
    for pro, cnt in pros:
        if cnt/total_cnt > 0.005:
            pros_cnt[pro] += cnt
        else:
            pros_cnt['其他'] += cnt
    pros = list(pros_cnt.items())
    pros.sort(key=lambda x: x[1])

    labels = ['{0}({1})'.format(label, cnt) for label, cnt in pros]
    values = [cnt for _, cnt in pros]
    colors = ['red', 'green', 'cyan', 'white', 'yellowgreen',
              'lightskyblue', 'magenta', 'yellow']

    plt.pie(values, labels=labels, colors=colors, autopct='%3.1f%%')
    plt.axis('equal')
    plt.legend()

    return f


def main():
    if not FORCE_REGEN and os.path.exists(data_file):
        with open(data_file, 'rb') as f:
            users = pickle.load(f)
    else:
        users = get_users()
        with open(data_file, 'wb') as f:
            pickle.dump(users, f)

    print('Draw birth')
    f1 = draw_birth(users)
    print('Draw losing rate')
    f2 = draw_losing_rate(users)
    print('Draw geo')
    f3 = draw_geo(users)

    pp = PdfPages('results.pdf')
    pp.savefig(f1)
    pp.savefig(f2)
    pp.savefig(f3)
    pp.close()

    # plt.show()


if __name__ == '__main__':
    main()
