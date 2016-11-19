#!/usr/bin/python
# coding: UTF-8
# Author: David
# Email: youchen.du@gmail.com
# Created: 2016-11-16 10:28
# Last modified: 2016-11-19 13:19
# Filename: NewsSpider.py
# Description:
import scrapy
import json
import random
import time
import re
import requests

from scrapy.loader import ItemLoader

from TouTiaoSpider.items import *
from TouTiaoSpider.tools import *

USER_DELAY = False


class NewsSpider(scrapy.Spider):
    name = "NewsSpider"
    allowed_domains = ["toutiao.com"]
    base_url = 'http://www.toutiao.com'
    start_urls = (
        'http://www.toutiao.com/api/article/feed/?'+gen_payload(),
    )

    def parse(self, response):
        data_flag = True
        try:
            js = json.loads(response.body)
        except Exception:
            data_flag = False
        if data_flag and js['message'] == 'success':
            for di in js['data']:
                il = ItemLoader(item=NewsItem())
                il.add_value('chinese_tag', di.get('chinese_tag'))
                il.add_value('media_avatar_url', di.get('media_avatar_url'))
                il.add_value('article_genre', di.get('article_genre'))
                il.add_value('tag_url', di.get('tag_url'))
                il.add_value('title', di.get('title'))
                il.add_value('behot_time', di.get('behot_time'))
                il.add_value('source_url', di.get('source_url'))
                il.add_value('source', di.get('source'))
                il.add_value('comments_count', di.get('comments_count'))
                il.add_value('image_url', di.get('image_url'))
                il.add_value('group_id', di.get('group_id'))
                il.add_value('media_url', di.get('media_url'))
                yield il.load_item()
                if 'article' in di.get('article_genre'):
                    source_url = di.get('source_url', None)
                    if source_url:
                        article_url = self.base_url+source_url
                        r = requests.get(article_url, allow_redirects=False)
                        redirected_url = r.headers['Location']
                        request = scrapy.Request(
                            redirected_url,
                            callback=self.parse_news)
                        request.meta['group_id'] = di.get('group_id', '0')
                        yield request
        if response.status != 200:
            time.sleep(random.randint(10, 50))
        feed_url = 'http://www.toutiao.com/api/article/feed/?'+gen_payload()
        yield scrapy.Request(feed_url, callback=self.parse)

    def parse_news(self, response):
        if response.status == 200:
            to_group_id = response.meta['group_id']
            url = response.url
            ac = response.xpath('//div[@id="article-main"]')
            title = ac.xpath('.//h1[@class="article-title"]/text()')
            title = title.extract_first(default='')
            info = ac.xpath('.//div[@class="articleInfo"]')
            source = info.xpath('.//span[@class="src"]/text()')
            source = source.extract_first(default='')
            source = source.strip('\n\t ')
            ctime = info.xpath('.//span[@class="time"]/text()')
            ctime = ctime.extract_first(default='')
            contents = ac.xpath('.//p/text()').extract()
            contents = map(lambda x: re.sub(r'<.*?>', '', x), contents)
            text = '\n'.join(contents)
            labels = ac.xpath('.//a[@class="label-link"]/text()').extract()

            il = ItemLoader(item=ArticleItem())
            il.add_value('to_group_id', to_group_id)
            il.add_value('url', url)
            il.add_value('title', title)
            il.add_value('source', source)
            il.add_value('ctime', ctime)
            il.add_value('text', text)
            il.add_value('labels', labels)
            yield il.load_item()
        else:
            return
