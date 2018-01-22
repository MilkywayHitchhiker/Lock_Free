#pragma once
#include"LockFreeMemoryPool.h"

template <class DATA>
class CStack_LF
{
public:

	struct st_NODE
	{
		DATA	Data;
		st_NODE *pNext;
	};

	struct st_TOP_NODE
	{
		st_NODE *pTopNode;
		__int64 iUniqueNum;
	};

public:

	/////////////////////////////////////////////////////////////////////////
	// ������
	//
	// Parameters: ����.
	// Return: ����.
	/////////////////////////////////////////////////////////////////////////
	CStack_LF ()
	{
		_lUseSize = 0;
		_iUniqueNum = 0;

		_pTop = (st_TOP_NODE *)_aligned_malloc(sizeof(st_TOP_NODE), 16);
		_pTop->pTopNode = NULL;
		_pTop->iUniqueNum = 0;

		_pMemoryPool = new CMemoryPool<st_NODE>(0);
	}

	/////////////////////////////////////////////////////////////////////////
	// �ı���
	//
	// Parameters: ����.
	// Return: ����.
	/////////////////////////////////////////////////////////////////////////
	virtual		~CStack_LF ()
	{
		st_NODE *pNode;
		while (_pTop->pTopNode != NULL)
		{
			pNode = _pTop->pTopNode;
			_pTop->pTopNode = _pTop->pTopNode->pNext;
			free(pNode);
		}
	}

	/////////////////////////////////////////////////////////////////////////
	// ���� ������� �뷮 ���.
	//
	// Parameters: ����.
	// Return: (int)������� �뷮.
	/////////////////////////////////////////////////////////////////////////
	long			GetUseSize(void){ return _lUseSize; }

	/////////////////////////////////////////////////////////////////////////
	// �����Ͱ� ����°� ?
	//
	// Parameters: ����.
	// Return: (bool)true, false
	/////////////////////////////////////////////////////////////////////////
	bool			isEmpty(void)
	{
		if (_pTop->pTopNode == NULL)
			return true;

		return false;
	}


	/////////////////////////////////////////////////////////////////////////
	// CPacket ������ ����Ÿ ����.
	//
	// Parameters: (DATA)����Ÿ.
	// Return: (bool) true, false
	/////////////////////////////////////////////////////////////////////////
	bool			Push(DATA Data)
	{
		st_NODE *pNode = _pMemoryPool->Alloc();
		st_TOP_NODE pPreTopNode;
		__int64 iUniqueNum = InterlockedIncrement64(&_iUniqueNum);

		do {
			pPreTopNode.iUniqueNum = _pTop->iUniqueNum;
			pPreTopNode.pTopNode = _pTop->pTopNode;

			pNode->Data = Data;
			pNode->pNext = _pTop->pTopNode;
		} while (!InterlockedCompareExchange128((volatile LONG64 *)_pTop, iUniqueNum, (LONG64)pNode, (LONG64 *)&pPreTopNode));
		_lUseSize += sizeof(pNode);

		return true;
	}

	/////////////////////////////////////////////////////////////////////////
	// ����Ÿ ���� ������.
	//
	// Parameters: (DATA *) ���� ������ �־��� ������
	// Return: (bool) true, false
	/////////////////////////////////////////////////////////////////////////
	bool			Pop(DATA *pOutData)
	{
		st_TOP_NODE pPreTopNode;
		st_NODE *pNode;
		__int64 iUniqueNum = InterlockedIncrement64(&_iUniqueNum);

		do
		{
			pPreTopNode.pTopNode = _pTop->pTopNode;
			pPreTopNode.iUniqueNum = _pTop->iUniqueNum;

			pNode = _pTop->pTopNode;
		} while (!InterlockedCompareExchange128((volatile LONG64 *)_pTop, iUniqueNum, (LONG64)_pTop->pTopNode->pNext, (LONG64 *)&pPreTopNode));
		_lUseSize -= sizeof (pNode);

		*pOutData = pPreTopNode.pTopNode->Data;
		_pMemoryPool->Free(pNode);
		return true;
	}

private:
	CMemoryPool_LF<st_NODE>		*_pMemoryPool;
	st_TOP_NODE				*_pTop;

	__int64					_iUniqueNum;

	long						_lUseSize;
};