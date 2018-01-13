#!/usr/bin/python
# coding: UTF-8
# Author: David
# Email: youchen.du@gmail.com
# Created: 2016-09-27 10:58
# Last modified: 2016-09-27 13:35
# Filename: downloader.py
# Description:
import urllib2
import urllib
from multiprocessing.dummy import Pool
import re
import os

os.mkdir('math')
os.chdir('math')

base_url = 'http://202.118.65.49'

pool = Pool()

def download(url):
    name = url.rsplit('/', 1)[-1]
    url = urllib.quote(url)
    url = url.replace('%3A', ':')
    print 'URL: ', url
    with open(name, 'wb') as f:
        data = urllib2.urlopen(url).read()
        f.write(data)


def process_page(url):
    data = urllib2.urlopen(url).read()
    pat = re.compile(r'href="(.*?)"')
    files = pat.findall(data)
    files = filter(lambda x: x.endswith('.pdf'), files)
    files = map(lambda x: base_url+x, files)
    pool.map_async(download, files)

def process_base(url):
    print 'Start Downloading.'
    data = urllib2.urlopen(url).read()
    pat = re.compile(r'href=[\'|"](.*?)[\'|"]')
    urls = pat.findall(data)
    urls = filter(lambda x: 'id=' in x and 'bh=' in x, urls)
    urls = map(lambda x: base_url+'/'+x, urls)
    for url in urls:
        process_page(url)
    pool.close()
    pool.join()
    print 'Downloaded.'

process_base('http://202.118.65.49/wlzy_1.aspx?bh=002')
