class Solution {
public:
    int magicalString(int n) {
        if(n <= 0)
            return 0;
        else if(n <= 3)
            return 1;
        else
        {
            bool current_is_one = true;
            int cnt = 1;
            queue<int> q;
            q.push(2);
            for(int i = 3; i <= n; i++)
            {
                int front = q.front();
                q.pop();
                if(front == 1)
                    cnt++;
                for(int k = 0; k < front; k++)
                    q.push((current_is_one ? 1 : 2));
                current_is_one = !current_is_one;
            }
            return cnt;
        }
    }
};
