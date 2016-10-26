#!/usr/bin/python
# coding: UTF-8
# Author: David
# Email: youchen.du@gmail.com
# Created: 2016-10-26 10:42
# Last modified: 2016-10-26 10:42
# Filename: solution2.py
# Description:
class Solution(object):
    def readBinaryWatch(self, num):
        """
        :type num: int
        :rtype: List[str]
        """
        return ['%d:%02d' %(h, m)
                for h in xrange(12) for m in xrange(60)
                if (bin(h)+bin(m)).count('1') == num]
