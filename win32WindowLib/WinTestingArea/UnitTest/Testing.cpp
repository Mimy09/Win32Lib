#include "Testing.h"

Testing::Testing() {
	/* Linked List Init */
	

	/* Tree Init */
	m_tkTree.Insert(1);
	m_tkTree.Insert(2);
	m_tkTree.Insert(3);
	m_tkTree.Insert(4);
	m_tkTree.Insert(5);

	/* Object Pool Init */
	m_tkObjectPool.AddObject(1);
	m_tkObjectPool.AddObject(2);
	m_tkObjectPool.AddObject(3);

	LinkedListTesting();
	HashMapTesting();

	std::cout << "############ All Passed ############\n";
}
Testing::~Testing() {}

void Testing::LinkedListTesting() {
	std::cout << "############ Started Linked List ############\n";
	m_tkLinkedList.push_back(1);
	m_tkLinkedList.push_back(2);
	m_tkLinkedList.push_back(3);

	m_stdLinkedList.push_back(1);
	m_stdLinkedList.push_back(2);
	m_stdLinkedList.push_back(3);

	std::cout << "Linked List :: Added {1, 2, 3}\n";

	for (int i = 0; i < m_tkLinkedList.size(); i++)
		if (m_tkLinkedList[i] != m_stdLinkedList[i]) TK_EXCEPTION("Linked List");
	
	std::cout << "Linked List :: Passed\n";

	m_tkLinkedList.erase(1);
	m_stdLinkedList.erase(m_stdLinkedList.begin() + 1);
	
	std::cout << "Linked List :: Deleted at pos 1\n";

	for (int i = 0; i < m_tkLinkedList.size(); i++)
		if (m_tkLinkedList[i] != m_stdLinkedList[i]) TK_EXCEPTION("Linked List");

	std::cout << "Linked List :: Passed\n";

	m_tkLinkedList.insert(m_tkLinkedList.find_n(m_tkLinkedList.front() + 1), 2);
	m_tkLinkedList.insert(m_tkLinkedList.find_n(m_tkLinkedList.front()), 0);
	m_stdLinkedList.insert(m_stdLinkedList.begin() + 1, 2);
	m_stdLinkedList.insert(m_stdLinkedList.begin(), 0);

	std::cout << "Linked List :: Added 2 at pos 1\n";
	std::cout << "Linked List :: Added 0 at pos 0\n";

	for (int i = 0; i < m_tkLinkedList.size(); i++)
		if (m_tkLinkedList[i] != m_stdLinkedList[i]) TK_EXCEPTION("Linked List");

	std::cout << "Linked List :: Passed\n";

	tk::std::LinkedList<int> m_tkLinkedList_temp;
	m_tkLinkedList_temp.push_back(3);
	m_tkLinkedList_temp.push_back(2);
	m_tkLinkedList_temp.push_back(1);
	m_tkLinkedList_temp.push_back(0);
	m_tkLinkedList = m_tkLinkedList_temp;

	m_stdLinkedList.clear();
	m_stdLinkedList.push_back(3);
	m_stdLinkedList.push_back(2);
	m_stdLinkedList.push_back(1);
	m_stdLinkedList.push_back(0);

	std::cout << "Linked List :: Copyed new {3, 2, 1, 0}\n";

	for (int i = 0; i < m_tkLinkedList.size(); i++)
		if (m_tkLinkedList[i] != m_stdLinkedList[i]) TK_EXCEPTION("Linked List");

	std::cout << "############ Passed Linked List ############\n\n";
}

void Testing::HashMapTesting() {
	std::cout << "############ Started Hash Map ############\n";

	m_tkHashMap.Add("One", 1);
	std::cout << "Linked List :: Added {'One', 1}\n";
	m_tkHashMap.Add("Two", 2);
	std::cout << "Linked List :: Added {'Two', 2}\n";
	m_tkHashMap.Add("Three", 3);
	std::cout << "Linked List :: Added {'Three', 3}\n";

	if (m_tkHashMap.Get("One") != 1) TK_EXCEPTION("Failed Getting One");
	if (m_tkHashMap.Get("Two") != 2) TK_EXCEPTION("Failed Getting Two");
	if (m_tkHashMap.Get("Three") != 3) TK_EXCEPTION("Failed Getting Three");

	std::cout << "Linked List :: Passed\n";

	m_tkHashMap.Remove("Two");

	std::cout << "############ Passed Linked List ############\n\n";
}

void Testing::TreeTesting() {
}

void Testing::ObjectPoolTesting() {
}
