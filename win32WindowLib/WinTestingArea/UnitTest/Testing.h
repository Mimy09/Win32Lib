#pragma once
#include <iostream>
#include <tkexception.h>

/* ---- TK LIBRARY ---- */
#include <tkObjectPool.h>
#include <tkLinkedList.h>
#include <tkHashMap.h>
#include <tkTree.h>
/* ---- STD LIBRARY ---- */
#include <vector>

class Testing {
public:
	Testing();
	~Testing();
	

private:
	void LinkedListTesting();
	void HashMapTesting();
	void TreeTesting();
	void ObjectPoolTesting();

	/* ---- TK LIBRARY ---- */
	tk::std::LinkedList<int> m_tkLinkedList;
	tk::std::HashMap<int> m_tkHashMap;
	tk::std::Tree<int> m_tkTree;
	tk::std::ObjectPool<int> m_tkObjectPool;

	/* ---- STD LIBRARY ---- */
	std::vector<int> m_stdLinkedList;
};
