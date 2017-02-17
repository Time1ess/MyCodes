#!/usr/bin/python
# coding: UTF-8
# Author: David
# Email: youchen.du@gmail.com
# Created: 2016-11-16 15:09
# Last modified: 2017-02-17 09:11
# Filename: middlewares.py
# Description:
__metaclass__ = type
import random
import base64

from .agents import AGENTS
from .proxies import PROXIES


class RandomUserAgentMiddleware():
    @classmethod
    def from_crawler(cls, crawler):
        return cls()

    def process_request(self, request, spider):
        agent = random.choice(AGENTS)
        request.headers.setdefault('User-Agent', agent)


class ProxyMiddleware():
    def process_request(self, request, spider):
        proxy = random.choice(PROXIES)
        request.meta['proxy'] = proxy
