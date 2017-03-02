#!/usr/local/bin/python3
# coding: UTF-8
# Author: David
# Email: youchen.du@gmail.com
# Created: 2017-03-02 09:30
# Last modified: 2017-03-02 09:31
# Filename: solution2.py
# Description:
class Solution(object):
    def countDigitOne(self, n):
        """
        :type n: int
        :rtype: int
        """
        if n <= 0:
            return 0
        l = 0
        r = n
        x = 1
        ans = 0
        while r:
            l = r % 10
            r = r / 10
            ans += r * x
            if l == 1:
                ans += n % x + 1
            elif l > 1:
                ans += x
            x *= 10
        return ans
