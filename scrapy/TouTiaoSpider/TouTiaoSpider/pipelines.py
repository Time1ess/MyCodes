#!/usr/bin/python
# coding: UTF-8
# Author: David
# Email: youchen.du@gmail.com
# Created: 2016-11-16 11:11
# Last modified: 2016-11-16 15:09
# Filename: pipelines.py
# Description:
# -*- coding: utf-8 -*-

# Define your item pipelines here
#
# Don't forget to add your pipeline to the ITEM_PIPELINES setting
# See: http://doc.scrapy.org/en/latest/topics/item-pipeline.html

from scrapy.exceptions import DropItem


class TouTiaoSpiderPipeline(object):
    def process_item(self, item, spider):
        if spider.name == "LinksJson":
            if 'ad' in item['article_genre']:
                raise DropItem('AD link')
        return item
