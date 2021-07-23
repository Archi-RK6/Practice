#include "task.hpp"
#include "project.hpp"
#include <vector>

void Project::new_task(Task task_n)
{
	project.push_back(task_n);
	for (int i = 0; i < project.size()-1; i++)
		for(int k=0; k < project[project.size()-1].get_q1(); k++)        
		{
			if(project[project.size()-1].get_prev1(k) == project[i].get_name1())
			{
				project[project.size()-1].new_prev_i(i);
				project[i].new_next_i(project.size()-1);
			}
		}			
}

void Project::find_est_eft ()
{
	project[0].get_eft() = project[0].get_comp_time1(); 
	int max=0;

	for (int i = 1; i < project.size(); i++)	
	{
		for(int k=0; k < project[i].get_q1(); k++)        
		{
			if(project[project[i].get_prev_index1(k)].get_eft1() >= max)
			{
				max=project[project[i].get_prev_index1(k)].get_eft1();
			}
		}
		project[i].get_est() = max;
		project[i].get_eft() = max + project[i].get_comp_time1();	
		max=0;	
	}
}


void Project::find_lst_lft ()
{
	project[project.size()-1].get_lft()=project[project.size()-1].get_eft1();
	project[project.size()-1].get_lst()=project[project.size()-1].get_lft1() - project[project.size()-1].get_comp_time1();
	int min = project[project.size()-1].get_lft1();
	project[project.size()-1].get_output()=1;
	
	for (int i = project.size()-2; i >=0; i--)
	{
		for(int k=0; k < project[i].get_next_q1(); k++)
		{
			if(project[project[i].get_next_index1(k)].get_lst1()<=min)
			{
				min = project[project[i].get_next_index1(k)].get_lst1();
				if (project[project[i].get_next_index1(k)].get_output1() == 1)
					project[i].get_output() = 1;
			}	
		}	
		if (min == project[project.size()-1].get_lft1())
			min = project[project.size()-1].get_eft1();;
		project[i].get_lft() = min;
		project[i].get_lst() = min - project[i].get_comp_time1();
		min = project[project.size()-1].get_lft1();
	}
}

void Project::find_slk()
{
	for (int i = 0; i < project.size(); i++)
	{
		project[i].get_slk() = project[i].get_lst1() - project[i].get_est1();
	}	
}

void Project::find_critical_path()
{
	for (int i = 0; i < project.size(); i++)
		if(project[i].get_output1() == 1)
			cout<<project[i].get_name1()<<endl;
}

