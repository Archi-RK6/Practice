#include "task.hpp"
#include <stdlib.h>
#include <vector>
#include <string>

Task::Task(vector <string>& f_input)
{
	name = f_input[0];
	comp_time = atoi(f_input[1].c_str());
	for (int i = 2; i < f_input.size(); i++)	
	{
		prev.push_back(f_input[i]);
	}
	est = 0;        
	eft = 0;        
	lst = 0;                      
	lft = 0;        
	slk = 0;
	output=0;
}

void Task::new_prev_i(int pi)
{
	 prev_index.push_back(pi);
}

void Task::new_next_i(int ni)
{
	 next_index.push_back(ni);
}
