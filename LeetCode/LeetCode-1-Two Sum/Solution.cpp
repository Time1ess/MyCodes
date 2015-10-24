//Method One:Unorder_map
//#include <vector>
//#include <unordered_map>
//using namespace std;
//class Solution {
//public:
//	vector<int> twoSum(vector<int> &numbers, int target)
//	{
//		unordered_map<int, int>hash;
//		vector<int>ans;
//		for (int i = 0; i < numbers.size(); i++)
//		{
//			int NumberToFind = target - numbers[i];
//			if (hash.find(NumberToFind) != hash.end())
//			{
//				ans.push_back(hash[NumberToFind] + 1);
//				ans.push_back(i + 1);
//				return ans;
//			}
//			hash[numbers[i]] = i;
//		}
//		return ans;
//	};
//};

//Method Two:hash table
#include <vector>
#include <map>
using namespace std;
class Solution{
public:
	vector<int> twoSum(vector<int> &numbers, int target)
	{
		map<int, int>hash;
		vector<int>ans;
		for (int i = 0; i<numbers.size() - 1; i++)
		{
			int NumberToFind = target - numbers[i];
			if (hash.find(NumberToFind) != hash.end())
			{
				ans.push_back(i + 1);
				ans.push_back(hash[NumberToFind] + 1);
				return ans;
			}
			hash[numbers[i]] = i;
		}
		return ans;
	}
};
