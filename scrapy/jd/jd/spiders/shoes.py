#!/usr/local/bin/python3
# coding: UTF-8
# Author: David
# Email: youchen.du@gmail.com
# Created: 2017-02-16 20:21
# Last modified: 2017-02-17 08:54
# Filename: shoes.py
# Description:
# -*- coding: utf-8 -*-
import re
import json

import scrapy

from scrapy.spiders import Spider
from scrapy.http import Request

from jd.items import ShoeCommentItem

shoe_list_url = 'https://search.jd.com/Search?keyword=鞋&enc=utf-8&page={}'
comment_url_api = 'https://club.jd.com/comment/productPageComments.action?productId={}&score=0&sortType=5&page={}&pageSize=10&isShadowSku=0'
num_pat = re.compile('(\d*?)')


class ShoesSpider(Spider):
    name = 'shoes'
    allowed_domains = ['jd.com']
    start_urls = [shoe_list_url.format(page) for page in range(1, 101)]

    def parse(self, response):
        item_urls = response.xpath('//li[@class="gl-item"]//div'
                                   '[@class="p-img"]/a/@href').extract()
        item_urls = [x for x in item_urls if 'ccc-x' not in x]
        item_ids = [x[x.rfind('/')+1:-5] for x in item_urls]
        for iid in item_ids:
            yield Request(
                comment_url_api.format(iid, 1),
                callback=self.parse_comment,
                meta={'page': 1, 'iid': iid},
                priority=1)

    def parse_comment(self, response):
        iid = response.meta['iid']
        page = int(response.meta['page'])
        json_data = json.loads(response.text)
        if not json_data['comments']:
            return
        for cd in json_data['comments']:
            d = {}
            d['_id'] = cd['id']
            d['iid'] = cd['referenceId']
            d['uid'] = cd['guid']
            d['creation_time'] = cd['creationTime']
            d['score'] = cd['score']
            d['user_province'] = cd['userProvince']
            d['user_level'] = cd['userLevelName']
            d['color'] = cd['productColor']
            d['size'] = cd['productSize']
            sc = ShoeCommentItem(d)
            yield sc
        yield Request(
            comment_url_api.format(iid, page+1),
            callback=self.parse_comment,
            meta={'page': page+1, 'iid': iid},
            priority=1)
