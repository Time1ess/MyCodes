#!/usr/local/bin/python3
# coding: UTF-8
# Author: David
# Email: youchen.du@gmail.com
# Created: 2016-12-08 19:40
# Last modified: 2016-12-08 19:40
# Filename: solution.py
# Description:
# Definition for an interval.
# class Interval(object):
#     def __init__(self, s=0, e=0):
#         self.start = s
#         self.end = e
import bisect

class Solution(object):
    def findRightInterval(self, intervals):
        """
        :type intervals: List[Interval]
        :rtype: List[int]
        """
        l = sorted((e.start, i) for i, e in enumerate(intervals))
        res = []
        for k in intervals:
            r = bisect.bisect_left(l, (k.end,))
            res.append(l[r][1] if r < len(l) else -1)
        return res
