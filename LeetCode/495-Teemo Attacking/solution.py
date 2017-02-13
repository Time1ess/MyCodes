#!/usr/local/bin/python3
# coding: UTF-8
# Author: David
# Email: youchen.du@gmail.com
# Created: 2017-02-13 10:35
# Last modified: 2017-02-13 10:35
# Filename: solution.py
# Description:
class Solution(object):
    def findPoisonedDuration(self, timeSeries, duration):
        """
        :type timeSeries: List[int]
        :type duration: int
        :rtype: int
        """
        result = 0
        if not timeSeries:
            return result
        last = timeSeries[0]
        result += duration
        for now in timeSeries[1:]:
            overlapped = now - last - duration
            if overlapped < 0:
                result += overlapped
            result += duration
            last = now
        return result
