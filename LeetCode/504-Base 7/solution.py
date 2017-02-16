#!/usr/local/bin/python3
# coding: UTF-8
# Author: David
# Email: youchen.du@gmail.com
# Created: 2017-02-16 08:51
# Last modified: 2017-02-16 08:51
# Filename: solution.py
# Description:
class Solution(object):
    def convertToBase7(self, num):
        """
        :type num: int
        :rtype: str
        """
        if num > 0:
            sign = ''
        elif num < 0:
            sign = '-'
        else:
            return '0'
        digits = ''
        num = abs(num)
        while num != 0:
            num, m = int(num / 7), num % 7
            digits += str(m)
        return sign+digits[::-1]
