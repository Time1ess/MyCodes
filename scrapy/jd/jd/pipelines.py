#!/usr/local/bin/python3
# coding: UTF-8
# Author: David
# Email: youchen.du@gmail.com
# Created: 2017-02-17 08:32
# Last modified: 2017-02-17 14:39
# Filename: pipelines.py
# Description:
# -*- coding: utf-8 -*-

# Define your item pipelines here
#
# Don't forget to add your pipeline to the ITEM_PIPELINES setting
# See: http://doc.scrapy.org/en/latest/topics/item-pipeline.html
import re
import os

from scrapy.exceptions import DropItem

from jd.items import ShoeCommentItem, ShoeDetailItem

val_indices = {'_id': 0, 'iid': 1, 'uid': 2, 'creation_time': 3, 'score': 4,
               'user_province': 5, 'user_level': 6, 'color': 7, 'size': 8}
detail_indices = {'iid': 0, 'name': 1, 'shop': 2, 'scores': 3}


class JdPipeline(object):
    def process_item(self, item, spider):
        return item


class ShoeDetailPipeline(object):
    seen_ids = set()

    @classmethod
    def from_crawler(cls, crawler):
        pipe = cls()
        if not os.path.exists('shoe_details.csv'):
            return pipe
        pat = re.compile('^\d+?,')
        with open('shoe_details.csv', 'r') as f:
            for line in f:
                iid = pat.findall(line)
                if iid:
                    pipe.seen_ids.add(iid[0])
        return pipe

    def process_item(self, item, spider):
        if not isinstance(item, ShoeDetailItem):
            return item

        iid = item['iid']
        if iid in self.seen_ids:
            raise DropItem('{} detail have been processed.'.format(iid))
        self.seen_ids.add(iid)

        key_values = list(item.items())
        key_values.sort(key=lambda x: detail_indices[x[0]])
        values = [str(val) for key, val in key_values]
        with open('shoe_details.csv', 'a') as f:
            f.write(','.join(values)+'\n')
        return item


class ShoeCommentPipeline(object):
    seen_ids = set()

    @classmethod
    def from_crawler(cls, crawler):
        pipe = cls()
        if not os.path.exists('shoe_comments.csv'):
            return pipe
        pat = re.compile('^\d+?,')
        with open('shoe_comments.csv', 'r') as f:
            for line in f:
                _id = pat.findall(line)
                if _id:
                    pipe.seen_ids.add(_id[0])
        return pipe

    def process_item(self, item, spider):
        if not isinstance(item, ShoeCommentItem):
            return item

        _id = item['_id']
        if _id in self.seen_ids:
            raise DropItem('{} Have been processed.'.format(_id))
        self.seen_ids.add(_id)

        key_values = list(item.items())
        key_values.sort(key=lambda x: val_indices[x[0]])
        values = [str(val) for key, val in key_values]
        with open('shoe_comments.csv', 'a') as f:
            f.write(','.join(values)+'\n')
        return item
