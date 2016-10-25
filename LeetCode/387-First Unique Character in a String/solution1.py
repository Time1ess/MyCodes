#!/usr/bin/python
# coding: UTF-8
# Author: David
# Email: youchen.du@gmail.com
# Created: 2016-10-25 10:38
# Last modified: 2016-10-25 10:38
# Filename: solution1.py
# Description:
class Solution(object):
    def firstUniqChar(self, s):
        """
        :type s: str
        :rtype: int
        """
        for idx, k in enumerate(s):
            if s.find(k) == s.rfind(k):
                return idx
        return -1
