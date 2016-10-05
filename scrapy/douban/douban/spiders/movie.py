#!/usr/bin/python
# coding: UTF-8
# Author: David
# Email: youchen.du@gmail.com
# Created: 2016-10-03 08:16
# Last modified: 2016-10-03 20:32
# Filename: movie.py
# Description:
# -*- coding: utf-8 -*-
import scrapy
from scrapy_splash import SplashRequest
from urllib import quote
from douban.items import DoubanMovieItem
import re


class MovieSpider(scrapy.Spider):
    name = "movie"
    allowed_domains = ["movie.douban.com"]
    start_urls = (
        'https://movie.douban.com/subject/25986180/',
    )

    def start_requests(self):
        for url in self.start_urls:
            yield SplashRequest(url, self.parse)

    def parse(self, response):
        # Parse the Movie Item
        try:
            yield self.parse_item(response)
        except IndexError:
            return
        # crawl related movies
        urls = response.xpath('//div[@id="recommendations"]//a/@href').extract()
        for url in urls:
            yield SplashRequest(url, self.parse)

    def parse_item(self, response):
        item = DoubanMovieItem()
        item['name'] = response.xpath('//span[@property="v:itemreviewed"]/text()').extract()[0]
        info = response.xpath('//div[@id="info"]').extract()[0]
        # staffs = info.xpath('./span/span[@class="attrs"]').extract()
        pat = re.compile('<.*?>')
        info = re.sub(pat, '', info).split('\n')
        info = map(lambda x: x.strip(' '), info)
        info = filter(lambda x: x != '', info)
        info = map(lambda x: x.split(':', 1), info)
        info = filter(lambda x: len(x) == 2, info)
        info_dict = dict(info)
        item['director'] = info_dict.get(u'导演', u'未知')
        item['actors'] = info_dict.get(u'主演', u'未知')
        item['release_date'] = info_dict.get(u'上映日期', u'未知')
        item['runtime'] = info_dict.get(u'片长', u'未知')
        item['score'] = response.xpath('//strong[@property="v:average"]/text()').extract()[0]
        item['screen_writter'] = info_dict.get(u'编剧', u'未知')
        item['category'] = info_dict.get(u'类型', u'未知')
        item['country'] = info_dict.get(u'制片国家/地区', u'未知')
        item['language'] = info_dict.get(u'语言', u'未知')
        item['aliases'] = info_dict.get(u'又名', u'未知')
        item['IMDB'] = info_dict.get(u'IMDb链接', u'未知')
        return item
