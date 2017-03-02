#!/usr/local/bin/python3
# coding: UTF-8
# Author: David
# Email: youchen.du@gmail.com
# Created: 2017-03-01 22:03
# Last modified: 2017-03-01 22:03
# Filename: solution.py
# Description:


class Solution(object):
    def countDigitOne(self, n):
        """
        :type n: int
        :rtype: int
        """
        if n <= 0:
            return 0
        elif n < 10:
            return 1
        from math import log10
        s = str(n)
        k = int(s[0])
        r = int(s[1:])
        m = int(log10(n))
        ones = 10 ** m
        cnt = k * self.countDigitOne(ones - 1) + self.countDigitOne(r)
        if n >= 2 * ones:
            cnt += ones
        else:
            cnt += n - ones + 1
        return cnt
