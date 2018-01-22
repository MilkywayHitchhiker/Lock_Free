#pragma once
#include"LockFreeMemoryPool.h"

struct DATA
{
	int Data;
	unsigned int Count;
};


class CQueue_LF
{
	struct LFQ_Node
	{
		DATA data;
		LFQ_Node *next;
	};
	struct SHead
	{
		LFQ_Node *head;
		unsigned __int64 Count;
	};
	struct Stail
	{
		LFQ_Node *tail;
		unsigned __int64 Count;
	};

	SHead *_pHead;
	Stail *_pTail;

	unsigned __int64 _UniqueTopCount;
	unsigned __int64 _UniqueTailCount;

public :
	CQueue_LF ()
	{
		_pTail = NULL;

		_pMemPool = new CMemoryPool_LF<LFQ_Node>(0);
	}
	~CQueue_LF ()
	{

	}


private :
	CMemoryPool_LF<LFQ_Node> *_pMemPool;

};