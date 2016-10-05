#!/usr/bin/python
# coding: UTF-8
# Author: David
# Email: youchen.du@gmail.com
# Created: 2016-10-03 08:21
# Last modified: 2016-10-03 14:22
# Filename: middlewares.py
# Description:
__metaclass__ = type
from random import choice


class RandomUserAgent:
    def __init__(self, agents):
        self.agents = agents

    @classmethod
    def from_crawler(cls, crawler):
        return cls(crawler.settings.getlist('USER_AGENTS'))

    def process_request(self, request, spider):
        request.headers.setdefault('User-Agent', choice(self.agents))

