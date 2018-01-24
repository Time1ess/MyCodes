#include <iostream>
#include <vector>
#include <queue>

using namespace std;


class Solution
{
public:
    double AverageWaitingTime(vector<int> arrive, vector<int> process, unsigned int serving_cnt=4)
    {
        int size = arrive.size();
        if(size <= 4)
            return 0;
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> waitings, servings;
        for(int i = 0; i < size; i++)
            waitings.push(make_pair(arrive[i], process[i]));
        int global_time = 0;
        double total_waiting_time = 0;
        while(!waitings.empty())
        {
            pair<int, int> next_customer, finished_customer;
            next_customer = waitings.top();
            waitings.pop();
            if(servings.size() == serving_cnt)
            {
                finished_customer = servings.top();
                servings.pop();
                cout<<finished_customer.first<<" "<<finished_customer.second<<endl;
                global_time = max(global_time, finished_customer.first);
                total_waiting_time += finished_customer.second;
                servings.push(make_pair(global_time + next_customer.second,  // Finish serving time
                                        max(0, global_time - next_customer.first))); // Waiting time
            }
            else
                servings.push(make_pair(next_customer.first + next_customer.second,  // Finish serving time
                                        0)); // Waiting time
        }
        while(!servings.empty())
        {
            pair<int, int> finished_customer = servings.top();
            servings.pop();
            total_waiting_time += finished_customer.second;
        }
        double ans = total_waiting_time / size;
        return ans;
    }
};


int main()
{
    vector<int> arrive{0, 1, 2, 3, 6};
    vector<int> process{7, 9, 8, 5, 5};
    Solution sol;
    cout<<sol.AverageWaitingTime(arrive, process)<<endl;
    return 0;
}
