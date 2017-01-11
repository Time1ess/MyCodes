#!/usr/local/bin/python3
# coding: UTF-8
# Author: David
# Email: youchen.du@gmail.com
# Created: 2017-01-11 20:58
# Last modified: 2017-01-11 22:02
# Filename: pipelines.py
# Description:
# -*- coding: utf-8 -*-

# Define your item pipelines here
#
# Don't forget to add your pipeline to the ITEM_PIPELINES setting
# See: http://doc.scrapy.org/en/latest/topics/item-pipeline.html
import scrapy

from RenRen.items import UserInfo


class RenrenPipeline(object):
    uids = set()
    def process_item(self, item, spider):
        if isinstance(item, UserInfo):
            if item['iid'] in self.uids:
                return item
            self.uids.add(item['iid'])
            with open('user_infos.txt', 'a') as f:
                f.write('%s %s %s\n' % (item['iid'], item['name'],
                                        item['info']))
        return item
