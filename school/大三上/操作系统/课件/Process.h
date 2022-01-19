#ifndef _PROCESS_
#define _PROCESS_
enum STATUS {RUNNING,BLOCKED,READY};
enum PRIORITY {LOW,NORMAL,HIGH};
struct ProcessNode
{
	int pid;
	enum STATUS status;
	enum PRIORITY priority;
	struct ProcessNode* next;
};
void input_processes();
void output_processes();
void FCFS_Scheduling();
#endif