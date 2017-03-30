#!/usr/local/bin/python3
# coding: UTF-8
# Author: David
# Email: youchen.du@gmail.com
# Created: 2017-03-30 16:49
# Last modified: 2017-03-30 18:22
# Filename: core.py
# Description:
import re

import requests
from bs4 import BeautifulSoup as BS


def get_bath_data():

    bath_url = 'http://202.118.64.15/fabu/cardUserManager.do?method=queryTboxCount'
    res = requests.get(bath_url)
    html = res.text
    html = re.sub('<html>[\s\S]+?</html>', '', html, 1)
    html = html.strip('\t\r\n ')

    soup = BS(html, 'lxml')
    data = []
    item = []
    num_pat = re.compile('(\d+)')
    str_fmt = '总数: {:-3d}个 已使用: {:-3d}个 {}'

    def fmt(item):
        frac = item[1] / item[0]
        if frac <= 0.17:
            item[-1] = '还等什么，快去!'
        elif 0.17 < frac <= 0.2:
            item[-1] = '人数较多，三思!'
        else:
            item[-1] = '就这么算了吧。'
        return str_fmt.format(*item)

    for idx, td in enumerate(soup.find_all('td'), 1):
        d = td.get_text().strip()
        if idx % 4 == 1:
            d = d[:-1]
        else:
            d = int(num_pat.findall(d)[0])
        item.append(d)
        if idx % 4 == 0:
            data.append(item)
            item = []
    data = [(x[0], fmt(x[1:])) for x in data]

    return data


if __name__ == '__main__':
    print(get_bath_data())
