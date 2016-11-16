#!/usr/bin/python
# coding: UTF-8
# Author: David
# Email: youchen.du@gmail.com
# Created: 2016-11-16 11:11
# Last modified: 2016-11-16 17:04
# Filename: pipelines.py
# Description:
# -*- coding: utf-8 -*-

# Define your item pipelines here
#
# Don't forget to add your pipeline to the ITEM_PIPELINES setting
# See: http://doc.scrapy.org/en/latest/topics/item-pipeline.html

from scrapy.exceptions import DropItem


class TouTiaoSpiderPipeline(object):
    seen_id = []

    def process_item(self, item, spider):
        if spider.name == "LinksJson":
            if 'ad' in item['article_genre']:
                raise DropItem('Drop item due to AD link')
            if item['group_id'] and item['group_id'][0] not in self.seen_id:
                self.seen_id.append(item['group_id'][0])
                print 'News:', item['title'][0]
                return item
            else:
                raise DropItem('Drop item due to no id or have seen it before')
        raise DropItem('Drop item due to reach end of pipeline')
