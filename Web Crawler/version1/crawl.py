#!/usr/bin/python
# coding: UTF-8
# Author: David
# Email: youchen.du@gmail.com
# Created: 2016-10-21 09:18
# Last modified: 2016-10-21 20:07
# Filename: crawl.py
# Description:
import urllib2
import redis

import sys
from urllib import basejoin
from lxml import etree


urls = ['http://www.dlut.edu.cn']
domain = 'dlut.edu.cn'


r = redis.StrictRedis()
r.flushall()


def parse(url):
    sys.stdout.flush()
    sys.stdout.write('URL: '+url[:210])
    sys.stdout.write(' '*(210-len(url))+'Remains: '+str(len(urls))+'\r\n')
    try:
        content = urllib2.urlopen(url, timeout=2).read()
    except urllib2.URLError:
        return []
    tree = etree.HTML(content)
    new_urls = map(lambda x: basejoin(url, x), tree.xpath('//a/@href'))
    new_urls = filter(lambda x: x.startswith('http'), new_urls)
    new_urls = filter(lambda x: x.split('.', 1)[1].startswith(domain), new_urls)
    ret_urls = []
    for url in new_urls:
        if r.get(url) is not None:
            continue
        else:
            r.set(url, 1)
            ret_urls.append(url)
    return ret_urls


def crawl():
    global urls
    while urls:
        url = urls[0]
        del urls[0]
        new_urls = parse(url)
        urls.extend(new_urls)

if __name__ == '__main__':
    crawl()
