class Solution(object):
    def majorityElement(self, nums):
        """
        :type nums: List[int]
        :rtype: int
        """
        from collections import Counter
        k=Counter(nums)
        return k.most_common()[0][0]
        
