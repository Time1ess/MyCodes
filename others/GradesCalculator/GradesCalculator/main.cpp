#include <string>
#include <iostream>
#include <fstream>
using namespace std;


struct stu
{
	string name;
	int id;
	string data;
};

int main()
{
	ifstream fin1,fin2;
	ofstream fout;
	fin1.open("first.csv");
	stu first[69], second[71];
	int i = 0;
	while (i<69)
	{
		fin1 >> first[i].name;
		fin1 >> first[i].id;
		getline(fin1, first[i].data);
		i++;
	}
	i = 0;
	fin1.close();
	fin2.open("second.csv");
	while (i < 71)
	{
		fin2 >> second[i].name;
		fin2 >> second[i].id;
		getline(fin2, second[i].data);
		i++;
	}
	fin2.close();
	int j;
	for (i = 0; i < 69; i++)
	{
		for (j = 0; j < 71; j++)
		{
			if (first[i].id == second[j].id)
			{
				first[i].data += second[j].data;
				break;
			}
		}
	}
	fout.open("open.csv");
	for (i = 0; i < 69; i++)
		fout << first[i].name << " " << first[i].id << first[i].data << endl;
	fout.close(); 
	return 0;
}