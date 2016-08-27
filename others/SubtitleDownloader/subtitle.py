#!/usr/bin/python
# coding: UTF-8
# Author: David
# Email: youchen.du@gmail.com
# Created: 2016-08-27 14:12
# Last modified: 2016-08-27 17:35
# Filename: subtitle.py
# Description:
import urllib2
import urllib
import cookielib
import json
import sys
import os
import re
from multiprocessing import Pool

DEBUG = False

DOWNLOAD_PATH = os.environ['HOME']+'/Downloads/'

login_url = 'http://www.zimuzu.tv/User/Login/ajaxlogin'
index_url = 'http://www.zimuzu.tv/'
search_url = 'http://www.zimuzu.tv/search?keyword='


href_title_pat = re.compile('<em>字幕</em>[\w\W]*?<a href="(.*?)">([\w\W]*?)</a>')
tag_pat = re.compile('<.*?>')
pages_pat = re.compile('class="pages[\w\W]*?</div>')
pagenum_pat = re.compile('page=(.*?)&')
download_pat = re.compile('subtitle-links[\w\W]*?字幕下载[\w\W]*?href="(.*?)"[\w\W]*?>(.*?)<')



def login(username=None, password=None):
    if not username:
        username = raw_input('请输入字幕组网站(www.zimuzu.tv)的用户名: ')
    if not password:
        password = raw_input('请输入帐号%s的密码: ' % username)
    parameters = {
        'account': username,
        'password': password,
        'remember': 1,
        'url_back': index_url}
    post_data = urllib.urlencode(parameters)
    html = urlopen(login_url, post_data)
    jd = json.loads(html)
    print jd['info']
    return jd['status']


def init():
    cj = cookielib.CookieJar()
    opener = urllib2.build_opener(urllib2.HTTPCookieProcessor(cj))
    urllib2.install_opener(opener)


def urlopen(url, post_data=None):
    req = urllib2.Request(url, post_data)
    req.add_header('User-Agent', 'Mozilla/5.0 (Macintosh; Intel Mac OS X 10_11_6) AppleWebKit/601.7.7 (KHTML, like Gecko) Version/9.1.2 Safari/601.7.7')
    resp = urllib2.urlopen(req)
    return resp.read()


def get_subtitles_data(html):
    data = map(lambda x: (x[0], re.sub(tag_pat, '', x[1])),
               href_title_pat.findall(html))
    return data


def get_max_page_num(html):
    pages_html = ''.join(pages_pat.findall(html))
    pagenums = pagenum_pat.findall(pages_html)
    if pagenums:
        pagenums = map(lambda x: int(x), pagenums)
        max_page_num = max(pagenums)
    else:
        max_page_num = 1
    return max_page_num


def download(title, url):
    print '正在下载: %s' % title
    data = urlopen(url)
    file_type = url.rsplit('.', 1)[-1]
    file_name = title.rsplit('.', 1)[0].rstrip('.')
    with open(DOWNLOAD_PATH+file_name+'.'+file_type, 'wb') as f:
        f.write(data)
    print '下载完毕: %s' % title


def print_progress(percent, words='当前进度: %s| %d%%'):
    sys.stdout.flush()
    percent = int(percent)
    progress = '['+'='*(percent-1)+'>'+' '*(100-percent)+']'
    sys.stdout.write((words % (progress, percent))+'\r')


def search(query):
    query = query.replace(' ', '+')
    print_progress(0)
    html = urlopen(search_url+query)
    subtitles = get_subtitles_data(html)
    max_page = get_max_page_num(html)
    if max_page > 1:
        for i in xrange(2, max_page+1):
            print_progress(100.0*i/(max_page+1))
            html = urlopen(search_url+query+'&page='+str(i))
            _subtitles = get_subtitles_data(html)
            subtitles += _subtitles
    print_progress(100)
    print
    item_cnts = len(subtitles)
    if item_cnts > 1:
        for idx, (url, title) in enumerate(subtitles):
            print '[', idx+1, ']', title
        while True:
            choice = input('找到多个匹配项，请输入序号确认(0退出):')
            if choice == 0:
                exit(0)
            elif 1 <= choice <= item_cnts:
                break
            else:
                print '无效选项，请重新输入!'
        tar_href = subtitles[choice-1][0]
    else:
        tar_href = subtitles[0][0]
    html = urlopen(index_url+tar_href)
    data = download_pat.findall(html)
    pool.apply_async(download, args=(data[0][1], data[0][0]))


pool = Pool()

def main():
    init()
    while not login():
        continue
    while True:
        if DEBUG:
            query = '疑犯追踪 S04 E13'
        else:
            try:
                query = raw_input("请输入搜索内容(q退出):")
            except EOFError:
                break
        search(query)
    pool.close()
    pool.join()

if __name__ == '__main__':
    main()
