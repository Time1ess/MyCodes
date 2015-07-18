#include <iostream>
#include <cmath>
#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;

char letters[15];
int value[15],target;
void process(int len)
{
	int a,b,c,d,e;
	for(a=0;a<len;a++)
		for(b=0;b<len;b++)
			if(a!=b)
				for(c=0;c<len;c++)
					if(a!=c&&b!=c)
						for(d=0;d<len;d++)
							if(a!=d&&b!=d&&c!=d)
								for(e=0;e<len;e++)
									if(a!=e&&b!=e&&c!=e&&d!=e)
										if(int(value[a]-pow(value[b],2.0)
												+pow(value[c],3.0)
												-pow(value[d],4.0)
												+pow(value[e],5.0))
												==target)
										{
											printf("%c%c%c%c%c\n",value[a]
													+'A'-1,value[b]+'A'-1,value[c]+'A'-1,value[d]+'A'-1,value[e]+'A'-1);
											return;
										}
	printf("no solution\n");
}
bool compare(int a,int b)
{
	return a>b;
}
int main()
{
	int i;
	while(~scanf("%d %s",&target,letters))
	{
		if(target==0&&strcmp(letters,"END")==0)
		{
			return 0;
		}
		i=0;
		while(letters[i])
		{
			value[i]=letters[i]-'A'+1;
			i++;
		}
		sort(value,value+i,compare);
		process(i);
	}
	return 0;
}
