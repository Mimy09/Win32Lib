#include "Testing.h"

Testing::Testing() {
	/* Linked List Init */
	

	/* Tree Init */
	m_tkTree.Insert(1);
	m_tkTree.Insert(2);
	m_tkTree.Insert(3);
	m_tkTree.Insert(4);
	m_tkTree.Insert(5);

	/* Hash Map Init */
	m_tkHashMap.Add("One", 1);
	m_tkHashMap.Add("Two", 2);
	m_tkHashMap.Add("Three", 3);

	/* Object Pool Init */
	

	LinkedListTesting();
}
Testing::~Testing() {}

void Testing::LinkedListTesting() {
	/* Linked List Test */
	m_tkLinkedList.push_back(1);
	m_tkLinkedList.push_back(2);
	m_tkLinkedList.push_back(3);

	m_stdLinkedList.push_back(1);
	m_stdLinkedList.push_back(2);
	m_stdLinkedList.push_back(3);

	for (int i = 0; i < m_tkLinkedList.size(); i++)
		if (m_tkLinkedList[i] != m_stdLinkedList[i]) TK_EXCEPTION("Linked List");
	
	m_tkLinkedList.erase(1);
	m_stdLinkedList.erase(m_stdLinkedList.begin() + 1);
	
	for (int i = 0; i < m_tkLinkedList.size(); i++)
		if (m_tkLinkedList[i] != m_stdLinkedList[i]) TK_EXCEPTION("Linked List");

	m_tkLinkedList.insert(m_tkLinkedList.find(m_tkLinkedList.front()), 2);
	m_stdLinkedList.insert(m_stdLinkedList.begin() + 1, 2);

	for (int i = 0; i < m_tkLinkedList.size(); i++)
		if (m_tkLinkedList[i] != m_stdLinkedList[i]) TK_EXCEPTION("Linked List");


}