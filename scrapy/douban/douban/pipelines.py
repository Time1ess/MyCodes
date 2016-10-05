#!/usr/bin/python
# coding: UTF-8
# Author: David
# Email: youchen.du@gmail.com
# Created: 2016-10-03 14:22
# Last modified: 2016-10-03 20:31
# Filename: pipelines.py
# Description:
# -*- coding: utf-8 -*-

# Define your item pipelines here
#
# Don't forget to add your pipeline to the ITEM_PIPELINES setting
# See: http://doc.scrapy.org/en/latest/topics/item-pipeline.html
__metaclass__ = type
import MySQLdb
import MySQLdb.cursors
from scrapy.exceptions import DropItem


class DoubanPipeline(object):
    def process_item(self, item, spider):
        return item


class MovieItemMySQLPipeline(object):
    def __init__(self):
        self.conn = MySQLdb.connect(
            host='localhost', user='root', passwd='root',
            port=3306, db='scrapy', charset='utf8')
        self.curs = self.conn.cursor()

    @classmethod
    def from_crawler(cls, crawler):
        return cls()

    def process_item(self, item, spider):
        query = 'insert into DoubanMovieItem ('
        props = list(item.items())
        keys = map(lambda x: x[0], props)
        values = map(lambda x: x[1], props)
        query += ','.join(keys)
        query += ') values ("' + '","'.join(values) + '")'
        self.curs.execute(query)
        self.conn.commit()
        return item
