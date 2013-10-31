// Queue.h: interface for the Queue class.
//
//////////////////////////////////////////////////////////////////////

#include<windows.h>

#if !defined(AFX_QUEUE_H__306E8DC1_8632_11DB_BD29_0002442A51E7__INCLUDED_)
#define AFX_QUEUE_H__306E8DC1_8632_11DB_BD29_0002442A51E7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

struct QueueEntry
{	
	void		*data;
	QueueEntry	*next;
};

class Queue  
{
public:
	Queue();
	void *Peek();
	void Enqueue(void *data);
	void *Dequeue();
	unsigned long int get_count();
	bool is_empty();
	virtual ~Queue();	
private:
	CRITICAL_SECTION access;
	QueueEntry *start, *end;
	unsigned long int count;
	bool empty;
};

#endif // !defined(AFX_QUEUE_H__306E8DC1_8632_11DB_BD29_0002442A51E7__INCLUDED_)
