#!/usr/bin/python
# coding: UTF-8
# Author: David
# Email: youchen.du@gmail.com
# Created: 2016-11-16 10:28
# Last modified: 2016-11-16 16:09
# Filename: LinksJson.py
# Description:
# -*- coding: utf-8 -*-
import scrapy
import json

from scrapy.loader import ItemLoader

from TouTiaoSpider.items import *
from TouTiaoSpider.tools import *


class LinksJsonSpider(scrapy.Spider):
    name = "LinksJson"
    allowed_domains = ["toutiao.com"]
    start_urls = (
        'http://www.toutiao.com/api/article/feed/?'+gen_payload(),
    )

    def parse(self, response):
        js = json.loads(response.body)
        if js['message'] == 'success':
            for di in js['data']:
                il = ItemLoader(item=NewsItem())
                il.add_value('chinese_tag', di.get('chinese_tag'))
                il.add_value('media_avatar_url', di.get('media_avatar_url'))
                il.add_value('article_genre', di.get('article_genre'))
                il.add_value('tag_url', di.get('tag_url'))
                il.add_value('title', di.get('title'))
                il.add_value('middle_mode', di.get('middle_mode'))
                il.add_value('gallary_image_count',
                             di.get('gallary_image_count'))
                il.add_value('image_list', di.get('image_list'))
                il.add_value('more_mode', di.get('more_mode'))
                il.add_value('behot_time', di.get('behot_time'))
                il.add_value('source_url', di.get('source_url'))
                il.add_value('source', di.get('source'))
                il.add_value('hot', di.get('hot'))
                il.add_value('is_feed_ad', di.get('is_feed_ad'))
                il.add_value('comments_count', di.get('comments_count'))
                il.add_value('has_gallery', di.get('has_gallery'))
                il.add_value('single_mode', di.get('single_mode'))
                il.add_value('image_url', di.get('image_url'))
                il.add_value('group_id', di.get('group_id'))
                il.add_value('is_diversion_page', di.get('is_diversion_page'))
                il.add_value('media_url', di.get('media_url'))
                yield il.load_item()
        if js['has_more'] is True:
            pass
