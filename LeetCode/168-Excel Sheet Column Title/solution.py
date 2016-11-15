#!/usr/bin/python
# coding: UTF-8
# Author: David
# Email: youchen.du@gmail.com
# Created: 2016-11-15 21:42
# Last modified: 2016-11-15 21:42
# Filename: solution.py
# Description:
class Solution(object):
    def convertToTitle(self, n):
        """
        :type n: int
        :rtype: str
        """
        ret = ''
        while n > 0:
            r = n % 26
            if r == 0:
                ret = 'Z' + ret
                n = n/26 - 1
            else:
                ret = chr(ord('A')+r-1)+ret
                n /= 26
        return ret
