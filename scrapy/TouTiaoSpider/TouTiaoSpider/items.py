#!/usr/bin/python
# coding: UTF-8
# Author: David
# Email: youchen.du@gmail.com
# Created: 2016-11-16 10:42
# Last modified: 2016-11-16 11:07
# Filename: items.py
# Description:
# -*- coding: utf-8 -*-

# Define here the models for your scraped items
#
# See documentation in:
# http://doc.scrapy.org/en/latest/topics/items.html

import scrapy


class NewsItem(scrapy.Item):
    chinese_tag = scrapy.Field()
    media_avatar_url = scrapy.Field()
    article_genre = scrapy.Field()
    tag_url = scrapy.Field()
    title = scrapy.Field()
    middle_mode = scrapy.Field()
    gallary_image_count = scrapy.Field()
    image_list = scrapy.Field()
    more_mode = scrapy.Field()
    behot_time = scrapy.Field()
    source_url = scrapy.Field()
    source = scrapy.Field()
    hot = scrapy.Field()
    is_feed_ad = scrapy.Field()
    comments_count = scrapy.Field()
    has_gallery = scrapy.Field()
    single_mode = scrapy.Field()
    image_url = scrapy.Field()
    group_id = scrapy.Field()
    is_diversion_page = scrapy.Field()
    media_url = scrapy.Field()
