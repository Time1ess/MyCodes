#!/usr/local/bin/python3
# coding: UTF-8
# Author: David
# Email: youchen.du@gmail.com
# Created: 2017-02-13 09:54
# Last modified: 2017-02-13 09:54
# Filename: solution2.py
# Description:
# Definition for a binary tree node.
# class TreeNode(object):
#     def __init__(self, x):
#         self.val = x
#         self.left = None
#         self.right = None

class Solution(object):
    def findFrequentTreeSum(self, root):
        """
        :type root: TreeNode
        :rtype: List[int]
        """
        if root is None:
            return []
        from collections import Counter
        c = Counter()
        def sub_sum(root):
            if root is None:
                return 0
            s = root.val+sub_sum(root.left)+sub_sum(root.right)
            c[s] += 1
            return s
        s = root.val+sub_sum(root.left)+sub_sum(root.right)
        c[s] += 1
        mc_key, mc_cnt = c.most_common(1)[0]
        return [key for key, cnt in c.items() if cnt == mc_cnt]
