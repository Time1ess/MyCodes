#!/usr/local/bin/python3
# coding: UTF-8
# Author: David
# Email: youchen.du@gmail.com
# Created: 2017-02-16 20:21
# Last modified: 2017-02-17 14:52
# Filename: shoes.py
# Description:
# -*- coding: utf-8 -*-
import re
import json

import scrapy

from scrapy.spiders import Spider
from scrapy.http import Request

from jd.items import ShoeCommentItem, ShoeDetailItem

shoe_list_url = 'https://search.jd.com/Search?keyword=鞋&enc=utf-8&page={}'
comment_url_api = 'https://club.jd.com/comment/productPageComments.action?productId={}&score=0&sortType=5&page={}&pageSize=10&isShadowSku=0'
num_pat = re.compile('(\d*?)')


class ShoesSpider(Spider):
    name = 'shoes'
    allowed_domains = ['jd.com']
    start_urls = [shoe_list_url.format(page) for page in range(1, 101)]

    def parse(self, response):
        item_urls = response.xpath('//li[@class="gl-item"]/div')
        for item_xpath in item_urls:
            url = item_xpath.xpath('div[@class="p-img"]/a'
                                   '/@href').extract_first()
            if not url or 'ccc-x' in url:
                continue
            iid = url[url.rfind('/')+1:-5]
            detail_url = 'http:' + url
            yield Request(
                detail_url,
                callback=self.parse_detail,
                meta={'iid': iid})
            yield Request(
                comment_url_api.format(iid, 1),
                callback=self.parse_comment,
                meta={'page': 1, 'iid': iid})

    def parse_detail(self, response):
        iid = int(response.meta['iid'])
        name = response.xpath('//div[@class="sku-name"]'
                              '/text()').extract_first()
        xpath_aside = response.xpath('//div[@class="aside"]')
        shop = xpath_aside.xpath('//div[@class="mt"]/'
                                 'h3/a/@title').extract_first()
        scores = xpath_aside.xpath('//div[@class="mc"]/div/'
                                   'a//text()').extract()
        scores = [s for s in scores if s.strip('\n ')][::2]

        sd = ShoeDetailItem(iid=iid, name=name, shop=shop,
                            scores='|'.join(scores))
        yield sd

    def parse_comment(self, response):
        iid = response.meta['iid']
        page = int(response.meta['page'])
        try:
            json_data = json.loads(response.text)
        except Exception as e:
            json_data = {}
            json_data['comments'] = []

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
            meta={'page': page+1, 'iid': iid})
