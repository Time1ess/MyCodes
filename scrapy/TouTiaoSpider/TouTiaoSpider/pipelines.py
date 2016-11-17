#!/usr/bin/python
# coding: UTF-8
# Author: David
# Email: youchen.du@gmail.com
# Created: 2016-11-16 11:11
# Last modified: 2016-11-17 15:01
# Filename: pipelines.py
# Description:

# Define your item pipelines here
#
# Don't forget to add your pipeline to the ITEM_PIPELINES setting
# See: http://doc.scrapy.org/en/latest/topics/item-pipeline.html
__metaclass__ = type
import MySQLdb.cursors

from scrapy.exceptions import DropItem
from twisted.enterprise import adbapi

from TouTiaoSpider.items import NewsItem, ArticleItem


class CleanUpPipeline():
    seen_id = []

    def process_item(self, item, spider):
        if isinstance(item, NewsItem):
            if 'ad' in item['article_genre']:
                raise DropItem('Drop item due to AD link')
            return item
        elif isinstance(item, ArticleItem):
            gid = item.prop('to_group_id')
            if gid and gid not in self.seen_id:
                self.seen_id.append(gid)
                return item
            else:
                raise DropItem('Drop item due to no id or have seen it before')
        raise DropItem('Drop item due to reach end of pipeline')


class MySQLPipeline():
    def __init__(self, dbpool):
        self.dbpool = dbpool

    @classmethod
    def from_settings(cls, settings):
        dbparams = dict(
            host=settings['MYSQL_HOST'],
            db=settings['MYSQL_DBNAME'],
            user=settings['MYSQL_USER'],
            passwd=settings['MYSQL_PASS'],
            charset='utf8',
            cursorclass=MySQLdb.cursors.DictCursor,
            use_unicode=False,
        )
        dbpool = adbapi.ConnectionPool('MySQLdb', **dbparams)
        return cls(dbpool)

    def process_item(self, item, spider):
        if isinstance(item, NewsItem):
            query = self.dbpool.runInteraction(self._news_info_insert, item)
            query.addErrback(self._db_error, item, spider)
        if isinstance(item, ArticleItem):
            query = self.dbpool.runInteraction(self._article_insert, item)
            query.addErrback(self._db_error, item, spider)
        return item

    def _article_insert(self, tx, item):
        sql = u"insert into TouTiaoArticleItem(\
            to_group_id,url,title,source,ctime,\
            text,labels) values(\
            %s,%s,%s,%s,%s,\
            %s,%s)"
        params = (
            item.prop('to_group_id'), item.prop('url'),
            item.prop('title'), item.prop('source'),
            item.prop('ctime'), item.prop('text'),
            item.prop('labels', True))
        tx.execute(sql,params)

    def _news_info_insert(self, tx, item):
        sql = u"insert into TouTiaoNewsItem(\
            chinese_tag,media_avatar_url,article_genre,tag_url,\
            title,behot_time,source_url,source,comments_count,\
            image_url,group_id,media_url) values(\
            %s,%s,%s,%s,\
            %s,%s,%s,%s,%s,\
            %s,%s,%s)"
        params = (
            item.prop('chinese_tag'), item.prop('media_avatar_url'),
            item.prop('article_genre'), item.prop('tag_url'),
            item.prop('title'), item.prop('behot_time'),
            item.prop('source_url'), item.prop('source'), 
            item.prop('comments_count'), item.prop('image_url'),
            item.prop('group_id'), item.prop('media_url'))
        tx.execute(sql,params)

    def _db_error(self, failure, item, spider):
        pass
