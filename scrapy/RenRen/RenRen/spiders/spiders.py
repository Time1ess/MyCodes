#!/usr/local/bin/python3
# coding: UTF-8
# Author: David
# Email: youchen.du@gmail.com
# Created: 2017-01-11 18:54
# Last modified: 2017-01-16 08:24
# Filename: spiders.py
# Description:
import scrapy
import re
from PIL import Image
from tempfile import TemporaryFile

from RenRen.private_data import username, password
from RenRen.items import UserInfo


class RenRenSpider(scrapy.Spider):
    name = 'RenRen'
    allowed_domains = ['renren.com']
    login_url = 'http://3g.renren.com/login.do?autoLogin=true&&fx=0'
    friend_list_url = 'http://3g.renren.com/getfriendlist.do?f=all&id=%s'
    detail_url = 'http://3g.renren.com/details.do?id=%s'
    id_pat = re.compile('[?|&|;]{1}id=(.*?)&')
    href_name_pat = re.compile('href="(.*?)".*?alt="(.*?)"')

    def find_id(self, s):
        iid = self.id_pat.findall(s)
        if iid:
            iid = iid[0]
            return iid
        else:
            return 0

    def _login_request(self, username='', password='', capt=''):
        return scrapy.FormRequest(
                self.login_url,
                formdata={'email': username, 'password': password},
                callback=self.logged_in,
                dont_filter=True)

    def start_requests(self):
        return [self._login_request(username, password)]

    def parse(self, response):
        forbidden = response.xpath("//div[@class='error']").extract()
        if forbidden:
            return
        next_page = response.xpath(u"//div[@class='list']/div[@class='l']\
            /a[@title='下一页']/@href").extract_first()
        friends = response.xpath("//div[@class='list']//\
            a[@class='p']").extract()
        friends = [self.href_name_pat.findall(x)[0] for x in friends]

        # for each friend
        for url, name in friends:
            iid = self.find_id(url)
            # print('爬取对象: ', name)
            yield scrapy.Request(self.detail_url % iid,
                                 callback=self.parse_detail, priority=1)
            yield scrapy.Request(self.friend_list_url % iid)

        # if next friends list page exists
        if next_page:
            yield scrapy.Request(next_page, dont_filter=True)

    def parse_detail(self, response):
        iid = response.url[response.url.find('id')+3:]
        name = response.xpath("//div[@class='sec']//a/text()").extract_first()
        infos = response.xpath("//div[@class='list']//text()").extract()
        if infos:
            infos = infos[1:]
        infos = ' '.join(infos)
        iid = iid.encode('utf-8')
        name = name.encode('utf-8')
        infos = infos.encode('utf-8')
        yield UserInfo(iid=iid, name=name, info=infos)

    def captcha(self, response):
        with TemporaryFile() as f:
            f.write(response.body)
            img = Image.open(f)
            img.show()
            capt = input('验证码:')
            yield self._login_request(username, password, capt)

    def logged_in(self, response):
        capt = response.xpath("//div[@class='sec']//img/@src").extract_first()
        if False:
            # print('Captcha: ', capt)
            yield scrapy.Request(capt, callback=self.captcha, dont_filter=True)
            return
        else:
            # print('No captcha')
            pass
        href = response.xpath("//div[@class='sec nav']/a/@href").extract()[1]
        my_id = self.id_pat.findall(href)[0]
        yield scrapy.Request(self.friend_list_url % my_id, dont_filter=True)
