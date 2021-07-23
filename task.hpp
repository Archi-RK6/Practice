#ifndef TASK
#define TASK

#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Task 
{
private:
	string name;    // наименование задачи 
	int comp_time;  // время выполнения   
	std::vector<std::string> prev; // предшественники
	int est;
	int eft;
	int lst;
	int lft;
	int slk;
	std::vector<int> prev_index;
	std::vector<int> next_index;
	int output;
public:
	Task(vector <string>&);
	void new_prev_i(int);
	void new_next_i(int);
	 
	int& get_est() {return est;};
	int& get_eft() {return eft;};
	int& get_lst() {return lst;};
	int& get_lft() {return lft;};
	int& get_slk() {return slk;};
	int& get_output() {return output;};
	
	string get_name1() {return name;};
	int get_comp_time1() {return comp_time;}; 
	int get_q1() {return prev.size();}; 
	string get_prev1(int i) {return prev[i];};
	int get_prev_index1(int pi) {return prev_index[pi];};
	int get_next_index1(int ni) {return next_index[ni];};
	int get_next_q1() {return next_index.size();};
	int get_est1() {return est;};
	int get_eft1() {return eft;};
	int get_lst1() {return lst;};
	int get_lft1() {return lft;};
	int get_slk1() {return slk;};
	int get_output1() {return output;};	
}; 				

#endif
