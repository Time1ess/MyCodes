#!/usr/bin/python
# coding: UTF-8
# Author: David
# Email: youchen.du@gmail.com
# Created: 2016-07-30 18:09
# Last modified: 2016-08-01 15:12
# Filename: crawl_test.py
# Description:
import searchengine
crawler = searchengine.crawler()
crawler.delete_index_tables()
crawler.create_index_tables()
pages = ['http://www.tangowithdjango.com']
crawler.crawl(pages, depth=3)
