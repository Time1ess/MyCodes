// Author: David
// Email: youchen.du@gmail.com
// Created: 2017-03-29 14:01
// Last modified: 2017-03-29 14:49
// Filename: solution.cpp
// Description:
#include <iostream>
#include <cassert>

using namespace std;

class PieSorting
{
    public:
        PieSorting()
        {
            cake_cnt = 0;
            max_swap = 0;
        }

        ~PieSorting()
        {
            if(cake_array != NULL)
                delete cake_array;
            if(swap_array != NULL)
                delete swap_array;
            if(reverse_array != NULL)
                delete reverse_array;
            if(reverse_info_array != NULL)
                delete reverse_info_array;
        }

        void run(int *cake_array, int cake_cnt)
        {
            init(cake_array, cake_cnt);
            this->search_cnt = 0;
            search(0);
        }

        void init(int *cake_array, int cake_cnt)
        {
            assert(cake_array != NULL);
            assert(cake_cnt > 0);

            this->cake_cnt = cake_cnt;
            this->cake_array = new int[cake_cnt];
            assert(this->cake_array != NULL);
            for(int i=0; i < cake_cnt; i++)
                this->cake_array[i] = cake_array[i];
            
            this->max_swap = upper_bound(cake_cnt);

            this->swap_array = new int[this->max_swap + 1];
            assert(this->swap_array != NULL);
            
            this->reverse_array = new int[cake_cnt];
            for(int i=0; i < cake_cnt; i++)
                this->reverse_array[i] = cake_array[i];

            this->reverse_info_array = new int[max_swap];
        }

        void search(int step)
        {
            int i, estimate;
            this->search_cnt++;
            estimate = lower_bound(this->reverse_array, this->cake_cnt);
            if(step + estimate > this->max_swap)
                return;

            if(is_sorted(this->reverse_array, this->cake_cnt))
            {
                if(step < this->max_swap)
                {
                    this->max_swap = step;
                    for(i = 0; i < this->cake_cnt; i++)
                        this->swap_array[i] = this->reverse_info_array[i];
                }
                return;
            }

            for(i=1; i < this->cake_cnt; i++)
            {
                reverse(0, i);
                this->reverse_info_array[step] = i;
                search(step+1);
                reverse(0, i);
            }
        }

        int upper_bound(int cake_cnt)
        {
            return cake_cnt * 2;
        }

        int lower_bound(int *cake_array, int cake_cnt)
        {
            int t, cnt = 0;
            for(int i=1; i < cake_cnt; i++)
            {
                t = cake_array[i] - cake_array[i-1];
                if((t == 1) || (t == -1))
                {
                }
                else
                    cnt++;
            }
            return cnt;
        }

        bool is_sorted(int *cake_array, int cake_cnt)
        {
            for(int i=1; i < cake_cnt; i++)
            {
                if(cake_array[i-1] > cake_array[i])
                    return false;
            }
            return true;
        }

        void reverse(int s, int e)
        {
            assert(e > s);
            for(int i=s, j=e; i < j; i++, j--)
                swap(this->reverse_array[i], this->reverse_array[j]);
        }

        void output()
        {
            for(int i=0; i < this->max_swap; i++)
                printf("%d ", this->swap_array[i]);

            printf("\n |Search Times| : %d\n", this->search_cnt);
            printf("Total Swap times = %d\n", this->max_swap);
        }

    private:
        int *cake_array;
        int cake_cnt;
        int max_swap;

        int *swap_array;
        int *reverse_array;
        int *reverse_info_array;
        int search_cnt;
};

int main()
{
    int cakes[] = {3,2,1,6,5,4,9,8,7,0};
    cout<<"Original cakes: ";
    for(auto x: cakes)
        cout<<x<<" ";
    cout<<endl;
    PieSorting pie;
    pie.run(cakes, 10);
    pie.output();
    return 0;
}
