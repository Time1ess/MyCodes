#!/usr/local/bin/python3
# coding: UTF-8
# Author: David
# Email: youchen.du@gmail.com
# Created: 2016-12-09 15:03
# Last modified: 2016-12-09 15:03
# Filename: solution.py
# Description:
class Solution(object):
    def findMinArrowShots(self, points):
        """
        :type points: List[List[int]]
        :rtype: int
        """
        cnt = 0
        if not points:
            return cnt
        points.sort(key=lambda x: (x[0], x[1]))
        end = points[0][1]
        cnt += 1
        for p in points[1:]:
            if p[0] <= end and p[1] < end:
                end = p[1]
            elif p[0] > end:
                end = p[1]
                cnt += 1
        return cnt
