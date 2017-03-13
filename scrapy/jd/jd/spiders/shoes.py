#!/usr/local/bin/python3
# coding: UTF-8
# Author: David
# Email: youchen.du@gmail.com
# Created: 2017-02-16 20:21
# Last modified: 2017-03-13 19:20
# Filename: shoes.py
# Description:
# -*- coding: utf-8 -*-
import re
import json

import scrapy

from scrapy.spiders import Spider
from scrapy.http import Request

from jd.items import ShoeCommentItem, ShoeDetailItem

shoe_cates = [
    '女深口单鞋', '工装鞋', '女鞋', '正装鞋', '平底鞋', '平底女鞋',
    '功能鞋', '中跟单鞋', '女拖鞋', '凉鞋', '拖鞋', '帆布鞋', '人字拖',
    '马丁靴', '商务休闲鞋', '传统布鞋', '休闲鞋', '鞋', '棉鞋', '定制鞋',
    '男靴', '坡跟单鞋', '短靴', '雨鞋', '平板鞋', '尖头单鞋', '军靴', '女靴',
    '皮鞋', '小白鞋', '雪地靴', '女豆豆鞋', '妈妈鞋', '增高鞋', '劳保鞋',
    '豆豆鞋', '踝靴', '沙滩鞋', '鞋 女', '深口单鞋', '板鞋', '高帮鞋',
    '人字拖鞋', '内增高', '发光鞋', '运动鞋', '高跟鞋', '雨靴', '鞋 男',
    '乐福鞋', '内增高休闲鞋', '老人鞋', '男鞋', '平底单鞋', '浅口单鞋', '单鞋']
shoe_list_url = 'https://search.jd.com/Search?keyword={}&enc=utf-8&page={}'
comment_url_api = ('https://club.jd.com/comment/productPageComments.action?'
    'productId={}&score=0&sortType=5&page={}&pageSize=10&isShadowSku=0')
num_pat = re.compile('(\d*?)')


class ShoesSpider(Spider):
    name = 'shoes'
    allowed_domains = ['jd.com']
    start_urls = [shoe_list_url.format(cate, page) for cate in shoe_cates
                  for page in range(1, 101)]

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
                meta={'page': 1, 'iid': iid, 'retry': 0})

    def parse_detail(self, response):
        iid = int(response.meta['iid'])
        name = response.xpath('//div[@class="sku-name"]'
                              '/text()').extract_first().strip('\n ')
        xpath_aside = response.xpath('//div[@class="aside"]')
        shop = xpath_aside.xpath('//div[@class="mt"]/'
                                 'h3/a/@title').extract_first().strip('\n ')
        scores = xpath_aside.xpath('//div[@class="mc"]/div/'
                                   'a//text()').extract()
        scores = [s for s in scores if s.strip('\n ')][::2]

        sd = ShoeDetailItem(iid=iid, name=name, shop=shop,
                            scores='|'.join(scores))
        yield sd

    def parse_comment(self, response):
        iid = response.meta['iid']
        page = int(response.meta['page'])
        retry = int(response.meta['retry'])
        try:
            json_data = json.loads(response.text)
        except Exception as e:
            if retry < 10:
                yield Request(
                    comment_url_api.format(iid, page),
                    callback=self.parse_comment,
                    meta={'page': page, 'iid': iid, 'retry': retry+1})
            return

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
            meta={'page': page+1, 'iid': iid, 'retry': 0})
