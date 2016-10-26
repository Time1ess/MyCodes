#!/usr/bin/python
# coding: UTF-8
# Author: David
# Email: youchen.du@gmail.com
# Created: 2016-10-21 09:18
# Last modified: 2016-10-23 10:26
# Filename: crawl.py
# Description:
import urllib2
import redis
import re
import jieba
import jieba.analyse
import string
import time

from urllib import basejoin
from lxml import etree
from multiprocessing.dummy import Pool, Lock
from Queue import Queue, Empty


urls = ['http://www.dlut.edu.cn']
download_queue = Queue()
map(lambda x: download_queue.put(x), urls)
domain = urls[0].split('.', 1)[-1]
r1 = re.compile(r'<script.*?</script>', re.I | re.M | re.S)
r2 = re.compile(r'<style.*?</style>', re.I | re.M | re.S)
r3 = re.compile(r'<!--.*?-->',  re.I | re.M | re.S)
r4 = re.compile(r'<meta.*?>',  re.I | re.M | re.S)
r5 = re.compile(r'<ins.*?</ins>',  re.I | re.M | re.S)
r6 = re.compile(r'^\s+$',  re.M | re.S)
r7 = re.compile(r'\n+', re.M | re.S)
r8 = re.compile(r'\r+', re.M | re.S)
r9 = re.compile(r'[%s]' % string.punctuation)


r = redis.StrictRedis()
r.flushall()
pool = Pool()
lock = Lock()
jieba_lock = Lock()
cnt = 0


def clean(content):
    content = r1.sub('', content)
    content = r2.sub('', content)
    content = r3.sub('', content)
    content = r4.sub('', content)
    content = r5.sub('', content)
    return content


def post_clean(content):
    content = r6.sub('', content)
    content = r7.sub('', content)
    content = r8.sub('', content)
    content = r9.sub('', content)
    return content


def extract(content, topK=10):
    jieba_lock.acquire()
    try:
        seg_list = jieba.analyse.extract_tags(content, topK=topK)
    except Exception:
        return []
    jieba_lock.release()
    return seg_list


def log(*msg):
    lock.acquire()
    global cnt
    for m in msg:
        if isinstance(m, list) or isinstance(m, tuple):
            for _m in m:
                print '%-10s' % _m[:10],
        else:
            print m,
    cnt += 1
    print 'Visited:', cnt
    lock.release()


def parse(url):
    try:
        req = urllib2.Request(url)
        req.add_header('User-agent', 'Mozilla 5.10')
        content = urllib2.urlopen(req, timeout=2).read()
        content = unicode(content, 'utf-8')
        content = clean(content)
    except urllib2.URLError:
        return []
    tree = etree.HTML(content)
    seg_list = extract(post_clean(''.join(tree.xpath(
        '//p//text()|//strong//text()|'
        '//span//text()|//a//text()|//li//text()'))))
    log('URL: %-60s|' % url[:60],
        seg_list,
        'Remains:'+str(download_queue.qsize()))

    n_urls = map(lambda x: basejoin(url, x), tree.xpath('//a/@href'))
    n_urls = filter(lambda x: x.startswith('http'), n_urls)
    n_urls = filter(lambda x: x.split('.', 1)[1].startswith(domain), n_urls)
    ret_urls = []
    for url in n_urls:
        if r.get(url) is not None:
            continue
        else:
            r.set(url, 1)
            ret_urls.append(url)
    return ret_urls


def update_download_queue(urls):
    map(lambda x: download_queue.put(x), urls)


def crawl():
    while True:
        try:
            pool.apply_async(func=parse,
                             args=(download_queue.get(block=True, timeout=5),),
                             callback=update_download_queue)
        except Empty:
            print 'Empty, wakeup in 2 seconds'
            time.sleep(2)
    pool.close()
    pool.join()

if __name__ == '__main__':
    crawl()
