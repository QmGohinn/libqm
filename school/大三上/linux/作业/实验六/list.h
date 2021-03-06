#ifndef _LINUX_LIST_H
#define _LINUX_LIST_H

void prefetch(const void *x){;}
void prefetchw(const void *x){;}

struct list_head{

struct list_head *next,*prev; 

};

#define LIST_HEAD_INIT(name){&(name),&(name)}
#define LIST_HEAD(name) 
	struct list_head name=LIST_HEAD_INIT(name)
#define INIT_LIST_HEAD(ptr)do{

(ptr)->next=(ptr);(ptr)->prev=(ptr);



}while(0)

static void_list_add(struct list_head *new,struct list_head *prev,struct list_head *next){

next->prev=new;
new->next=next;
new->prev=prev;
prev->next=new;

}
static void list_add(struct list_head *new,struct list_head *head){

_list_add(new,head,head->next);

}
static void list_add_tail(struct list_head *new,struct list_head *head){

_list_add(new,head->prev,head);

}

static void _list_del(struct list_head *prev,struct list_head *next){


next->prev=prev;

prev->next=next;

}
static void list_del(struct list_head *entry){

_list_del(entry->prev,entry->next);

entry->next=(void *)0;

entry->prev=(void *)0;

}

static void list_del_init(struct list_head *entry){

_list_del(entry->prev,entry->next);

INIT_LIST_HEAD(entry);

}

static void list_move(struct list_head *list,struct list_head *head){
_list_del(list->prev,list->next);
list_add(list,head);

}

static void list_move_tail(struct list_head *list,struct list_head *head){

_list_del(list->prev,list->next);

list_add_tail(list,head);
}

static int list_empty(struct list_head *head){

return head->next==head;

}
static void _list_splice(struct list_head *list, struct list_head *head){

struct list_head *first=list->next;
struct list_head *last=list->prev;
struct list_head *at=head->next;

first->prev=head;
head->next=first;
last->next=at;
at->prev=last;

}
static void list_splice(struct list_head *list,struct list_head *head){

if(!list_empty(list))
	_list_splice(list,head);

}
static void list_splice_init(struct list_head *list,struct list_head *head){

if(!list_empty(list)){
_list_splice(list,head);
INIT_LIST_HEAD(list);

}
}
#define list_entry(ptr,type,member)
	((type *)((char *)(ptr)-(unsigned long)(&((type *)0)->member)))
#define list_for_each(pos,head)
	for(pos=(head)->next,prefetch(pos->next);pos!=(head);pos=pos->next,prefetch(pos->next))
#define list_for_each_prev(pos,head)
	for(pos=(head)->prev,prefetch(pos->prev);pos!=(head);pos=pos->prev,prefetch(pos->prev))
#define list_for_each_safe(pos,n,head)
	for(pos=(head)->next,n=pos->next;pos!=(head);pos=n,n=pos->next)
#define list_for_each_entry(pos,head,member)
	for(pos=list_entry((head)->next,typeof(*pos),member),prefetch(pos->member.next);
 	&pos->member!=(head);pos=list_entry(pos->member.next,typeof(*pos),member),prefetch( pos->member.next ))
#define list_for_each_entry_safe(pos,n,head,member)
	for(pos=list_entry((head)->next,typeof(*pos),member),n=list_entry(pos->member.next,typeof(*pos),member);
 	&pos->member!=(head);pos=n,n=list_entry(n->member.next,typeof(*n),member))
#define list_for_each_entry_continue(pos,head,member)
	for(pos=list_entry(pos->member.next,typeof(*pos),member),prefetch(pos->member.next);
 	&pos->member!=(head);pos=list_entry(pos->member.next,typeof(*pos),member),prefetch(pos->member.next))
#endif






