//Code used with permission from Face (http://orbiter-forum.com/member.php?u=293)
//See http://orbiter-forum.com/showthread.php?p=338410&postcount=2 for more info

//Modifications to Face's code under Copyright (c) 2013 Christopher Johnstone(meson800)
//The MIT License - See ../../../LICENSE for more info

// Queue.cpp: implementation of the Queue class.
//
//////////////////////////////////////////////////////////////////////

#pragma unmanaged
#include "Queue.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Queue::Queue()
{
	start=0;
	end=0;
	count=0;
	empty=true;
	InitializeCriticalSection(&access);
}

Queue::~Queue()
{
	DeleteCriticalSection(&access);
	while(!empty) Dequeue();
}

void Queue::Enqueue(void *data)
{
	struct QueueEntry *entry;
	EnterCriticalSection(&access);		
		entry=new QueueEntry;
		entry->data=data;
		entry->next=0;
		if (start==0)
		{
			start=entry;			
			end=entry;		
		}
		else
		{
			start->next=entry;
			start=entry;
		}
		count++;
		empty=false;
	LeaveCriticalSection(&access);
}

void *Queue::Dequeue()
{
	EnterCriticalSection(&access);
		if (end==0)
		{
	LeaveCriticalSection(&access);
			return 0;
		}
		struct QueueEntry *entry;
		entry=end;
		end=entry->next;
		void *result=entry->data;
		delete entry;
		if (end==0)	start=0;
		if (--count==0) empty=true;
	LeaveCriticalSection(&access);
	return result;
}

void *Queue::Peek()
{
	EnterCriticalSection(&access);
		if (end==0)
		{
	LeaveCriticalSection(&access);
			return 0;
		}
		void *result=end->data;
	LeaveCriticalSection(&access);
	return result;
}

unsigned long int Queue::get_count()
{
	unsigned long int result;
	EnterCriticalSection(&access);
		result=count;
	LeaveCriticalSection(&access);
	return result;
}

bool Queue::is_empty()
{
	bool result;
	EnterCriticalSection(&access);
		result=empty;
	LeaveCriticalSection(&access);
	return result;
}