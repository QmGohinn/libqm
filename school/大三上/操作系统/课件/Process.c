#include "Process.h"
struct ProcessNode* running_head=0;
struct ProcessNode* running_tail=0;
struct ProcessNode* blocked_head=0;
struct ProcessNode* blocked_tail=0;
struct ProcessNode* ready_head=0;
struct ProcessNode* ready_tail=0;
void ready_insert(struct ProcessNode* p);
void blocked_insert(struct ProcessNode*p);
void running_insert(struct ProcessNode*p);
void list_insert(struct ProcessNode** head, struct ProcessNode** tail, struct ProcessNode* p);
int exist(struct ProcessNode*p);
int list_exist(struct ProcessNode* head, struct ProcessNode* p);
void insert_process(struct ProcessNode* p);
void input_one_process();
void list_print(struct ProcessNode* head);
void insert_process(struct ProcessNode* p)
{
	if(p==0)
	{
		printf("error! you can't insert an empty process!\n");
		return;
	}
	if(exist(p))
	{
		printf("there is already a process with the same ID in the system\n");
		return;
	}
	if(!(p->priority==LOW||p->priority==NORMAL||p->priority==HIGH))
	{
		printf("error! the process priority is invalid!\n");
		return;
	}
	switch(p->status)
	{
	case(RUNNING):
			 running_insert(p);
	         break;
	case(BLOCKED):
			blocked_insert(p);
			break;
	case(READY):
			ready_insert(p);
			break;
	default:
		    printf("error! the process status is invalid!\n");
			break;
	}
		
}
void running_insert(struct ProcessNode*p)
{
	if(running_head)
	{
		printf("error! there is a process in running already!");
		return;
	}
	list_insert(&running_head,&running_tail,p);
}
void blocked_insert(struct ProcessNode*p)
{
	list_insert(&blocked_head,&blocked_tail,p);
}
void ready_insert(struct ProcessNode* p)
{
	list_insert(&ready_head,&ready_tail,p);
}
void list_insert(struct ProcessNode** head, struct ProcessNode** tail, struct ProcessNode* p)
{
	if(*head==0)
	{
		*head=*tail=p;
		p->next=0;
	}
	else
	{
		(*tail)->next=p;
		p->next=0;
		*tail=p;
	}
}
int exist(struct ProcessNode* p)
{
	if(list_exist(running_head,p))
		return 1;
	if(list_exist(blocked_head,p))
		return 1;
	if(list_exist(ready_head,p))
		return 1;
	return 0;
}
int list_exist(struct ProcessNode* head, struct ProcessNode* p)
{
	struct ProcessNode* temp;
	temp=head;
	while(temp)
	{
		if(temp->pid==p->pid)
			return 1;
		temp=temp->next;
	}
	return 0;
}
void input_one_process()
{
	struct ProcessNode* p=malloc(sizeof(struct ProcessNode));
	char temp;
	printf("please input the ID of the process (an integer)\n");
	scanf("%d%c",&(p->pid),&temp); // temp is used to clear up the buffer
	printf("please input the status of the process: 0-running;1-blocked;2-ready\n");
	scanf("%d%c",&(p->status),&temp);
	printf("please input the priority of the process: 0-low;1-normal;2-high\n");
	scanf("%d%c",&(p->priority),&temp);
	insert_process(p);
}
void input_processes()
{
	char c;
	char temp;
GETINPUT:	printf("please input continue or not: y-yes; n-not\n");
	scanf("%c",&c); // this is the real input
	scanf("%c",&temp); // to clear up the buffer
	switch(c)
	{
	case 'y':
		{
			input_one_process();
			goto GETINPUT;
		}
	case 'n':
		break;
	default:
		{
			printf("the input is not valid. please try another\n");
			goto GETINPUT;
		}
	}
}
void output_processes()
{
	printf("the running process information:\n");
	list_print(running_head);
	printf("the blocked processes information:\n");
	list_print(blocked_head);
	printf("the ready processes information:\n");
	list_print(ready_head);
}
void list_print(struct ProcessNode* head)
{
	struct ProcessNode* temp=head;
	while(temp)
	{
		printf("ProcessID: %d; ProcessPriority: %d\n",temp->pid,temp->priority);
		temp=temp->next;
	}
}
void FCFS_Scheduling()
{
	int count=0;
	struct ProcessNode* temp=ready_head;
	if(ready_head==0)
	{
		printf("there is no process to be scheduled\n");
		return;
	}
	printf("the sheduling order under FCFS is as follows:\n");
	while(temp)
	{
		printf("Scheduling order %d: ProcessID %d\n",++count,temp->pid);
		temp=temp->next;
	}
}