#!/usr/bin/python
# coding: UTF-8
# Author: David
# Email: youchen.du@gmail.com
# Created: 2016-10-02 10:01
# Last modified: 2016-10-02 10:01
# Filename: solution.py
# Description:
class Solution(object):
    def reconstructQueue(self, people):
        """
        :type people: List[List[int]]
        :rtype: List[List[int]]
        """
        people.sort(key=lambda x: (-x[0], x[1]))
        res = []
        for p in people:
            res.insert(p[1], p)
        return res;
