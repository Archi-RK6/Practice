#ifndef PROJECT
#define PROJECT

#include <iostream>
#include <string>
#include "task.hpp"
#include <vector>
using namespace std;

class Project 
{
private:
	std::vector<Task> project;
public:
	int get_size() {return project.size();};
	Task get_task(int i) {return project[i];};
	void new_task(Task task_n);
	void find_est_eft();
	void find_lst_lft();
	void find_slk();
	void find_critical_path();
};
#endif
