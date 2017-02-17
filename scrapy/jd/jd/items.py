#!/usr/local/bin/python3
# coding: UTF-8
# Author: David
# Email: youchen.du@gmail.com
# Created: 2017-02-17 08:24
# Last modified: 2017-02-17 08:32
# Filename: items.py
# Description:
# -*- coding: utf-8 -*-

# Define here the models for your scraped items
#
# See documentation in:
# http://doc.scrapy.org/en/latest/topics/items.html

import scrapy


class ShoeCommentItem(scrapy.Item):
    # define the fields for your item here like:
    # name = scrapy.Field()
    _id = scrapy.Field()
    iid = scrapy.Field()
    uid = scrapy.Field()
    creation_time = scrapy.Field()
    score = scrapy.Field()
    user_province = scrapy.Field()
    user_level = scrapy.Field()
    color = scrapy.Field()
    size = scrapy.Field()
