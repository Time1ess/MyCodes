#!/usr/bin/python
# coding: UTF-8
# Author: David
# Email: youchen.du@gmail.com
# Created: 2016-09-17 11:09
# Last modified: 2016-09-17 11:09
# Filename: solution.py
# Description:
class Solution(object):
    def countBits(self, num):
        """
        :type num: int
        :rtype: List[int]
        """
        f = [0]*(num+1)
        if num == 0:
            return f
        f[0] = 0
        f[1] = 1
        cnt = 1
        idx = 2
        while idx < num+1:
            cnt *= 2
            tmp = idx
            while idx < tmp+cnt and idx < num+1:
                f[idx] = f[idx-tmp]+1
                idx += 1
        return f
