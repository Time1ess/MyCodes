#!/usr/local/bin/python3
# coding: UTF-8
# Author: David
# Email: youchen.du@gmail.com
# Created: 2017-01-11 20:58
# Last modified: 2017-01-13 10:47
# Filename: pipelines.py
# Description:
# -*- coding: utf-8 -*-

# Define your item pipelines here
#
# Don't forget to add your pipeline to the ITEM_PIPELINES setting
# See: http://doc.scrapy.org/en/latest/topics/item-pipeline.html
import scrapy
import re

from RenRen.items import UserInfo
from scrapy.exceptions import DropItem


class RenrenPipeline(object):
    uids = set()

    @classmethod
    def from_crawler(cls, crawler):
        pipe = cls()
        pat = re.compile('^\d+? ')
        with open('user_infos.txt', 'r') as f:
            for line in f:
                uid = pat.findall(line)
                if uid:
                    pipe.uids.add(uid[0])
        return pipe

    def process_item(self, item, spider):
        if isinstance(item, UserInfo):
            if item['iid'] in self.uids:
                raise DropItem('Item seen: %s'.format(item['iid']))
            self.uids.add(item['iid'])
            with open('user_infos.txt', 'a') as f:
                f.write('%s %s %s\n' % (item['iid'], item['name'],
                                        item['info']))
        return item
