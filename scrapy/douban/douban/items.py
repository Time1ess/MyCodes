#!/usr/bin/python
# coding: UTF-8
# Author: David
# Email: youchen.du@gmail.com
# Created: 2016-10-03 08:50
# Last modified: 2016-10-03 20:32
# Filename: items.py
# Description:
# -*- coding: utf-8 -*-

# Define here the models for your scraped items
#
# See documentation in:
# http://doc.scrapy.org/en/latest/topics/items.html

import scrapy


class DoubanMovieItem(scrapy.Item):
    # define the fields for your item here like:
    # name = scrapy.Field()
    name = scrapy.Field()
    director = scrapy.Field()
    screen_writter = scrapy.Field()
    actors = scrapy.Field()
    category = scrapy.Field()
    country = scrapy.Field()
    language = scrapy.Field()
    release_date = scrapy.Field()
    runtime = scrapy.Field()
    aliases = scrapy.Field()
    IMDB = scrapy.Field()
    score = scrapy.Field()
