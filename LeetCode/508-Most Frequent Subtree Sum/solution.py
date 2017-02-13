#!/usr/local/bin/python3
# coding: UTF-8
# Author: David
# Email: youchen.du@gmail.com
# Created: 2017-02-13 10:22
# Last modified: 2017-02-13 10:22
# Filename: solution.py
# Description:
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
        from collections import defaultdict
        d = defaultdict(int)
        self.subtree_sum(root, d);
        result = []
        for new_idx, new_cnt in d.items():
            if not result:
                result = [(new_cnt, new_idx)]
            else:
                old_cnt, old_idx = result[0]
                if new_cnt > old_cnt:
                    result = [(new_cnt, new_idx)]
                elif new_cnt == old_cnt:
                    result.append((new_cnt, new_idx))
        return [val for cnt, val in result]
    
    def subtree_sum(self, root, d):
        if root is None:
            return 0
        s = root.val+self.subtree_sum(root.left, d)+\
            self.subtree_sum(root.right, d)
        d[s] += 1
        return s
