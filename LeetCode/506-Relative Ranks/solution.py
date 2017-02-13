#!/usr/local/bin/python3
# coding: UTF-8
# Author: David
# Email: youchen.du@gmail.com
# Created: 2017-02-13 14:15
# Last modified: 2017-02-13 14:39
# Filename: solution.py
# Description:
class Solution(object):
    def findRelativeRanks(self, nums):
        """
        :type nums: List[int]
        :rtype: List[str]
        """
        ranks = list(range(1, len(nums)+1))
        ranks = [str(r) for r in ranks]
        ranks[:3] = ["Gold Medal", "Silver Medal", "Bronze Medal"]
        nis = [(num, idx) for idx, num in enumerate(nums)]
        nis.sort(key=lambda x: x[0], reverse=True)
        results = [None]*len(nums)
        for _idx, (num, idx) in enumerate(nis):
            results[idx] = ranks[_idx]
        return results
