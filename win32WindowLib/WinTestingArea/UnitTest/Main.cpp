#include "Testing.h"
#include <tkLinkedList.h>

int main() {
	try {
		Testing t;

		tk::std::LinkedList<int> ll, ll2;
		ll.push_back(1);
		ll.push_back(2);
		ll.push_back(3);
		ll.push_back(4);
		ll.push_back(5);
		ll.push_back(6);
		ll.pop_back();
		ll.pop_back();
		ll.pop_back();

		ll2.push_back(3);
		ll2.push_back(2);
		ll2.push_back(1);

		ll = ll2;

		ll.erase(1);
		ll.insert(1, 2);

		system("pause>nul");
	} catch (tk::Exception e){
		e.msgWhat();
	
	}
	return 0;
}	