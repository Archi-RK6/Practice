#include <iostream>
#include <string> 
#include <fstream>
#include <vector>
#include "task.hpp"
#include "project.hpp"

using namespace std;

int main()
{
	setlocale(LC_ALL, "ru");
	
	string path = "input.txt";
	ifstream fin;
	fin.open(path);
	Project project;
			
	if (!fin.is_open())
	{
		cout<<"Ошибка открытия файла."<<endl;
	}
	else 
	{
		cout<<"Файл открыт."<<endl;
		std::string str;
		char str1;
		std::vector<std::string> f_input;
		
		while (!fin.eof())
		{
			str = "";
			fin >> str; 
			fin.get(str1);
			cout<<str;
			cout<<str1;	
			if (str !="")
			{		
				if (str1 != '\n')
					f_input.push_back(str);
				else
				{
					f_input.push_back(str);
					project.new_task(Task (f_input));
					f_input.clear();
				}
			}
		}		
	
	}

	project.find_est_eft();
	project.find_lst_lft();
	project.find_slk();
	
	for (int i = 0; i < project.get_size();i++)
	{	
		cout<<project.get_task(i).get_name1()<<endl;
		cout<<"est="<<project.get_task(i).get_est1()<<endl;
		cout<<"eft="<<project.get_task(i).get_eft1()<<endl;
		cout<<"lst="<<project.get_task(i).get_lst1()<<endl;
		cout<<"lft="<<project.get_task(i).get_lft1()<<endl;
		cout<<"slk="<<project.get_task(i).get_slk1()<<endl;
		cout<<endl;
				
	}
	
	cout<<"Задачи, принадлежашие критическим путям :"<<endl;
	project.find_critical_path();
	
	fin.close();
	return 0;
}