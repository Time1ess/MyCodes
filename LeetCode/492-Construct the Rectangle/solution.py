#!/usr/local/bin/python3
# coding: UTF-8
# Author: David
# Email: youchen.du@gmail.com
# Created: 2017-02-13 13:58
# Last modified: 2017-02-13 13:59
# Filename: solution.py
# Description:
class Solution(object):
    def constructRectangle(self, area):
        """
        :type area: int
        :rtype: List[int]
        """
        from math import sqrt
        for f1 in range(int(sqrt(area)), 0, -1):
            if area % f1 == 0:
                return [area/f1, f1]
