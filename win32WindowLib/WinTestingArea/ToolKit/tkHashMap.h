// ################################################################## //
// ##							HASH MAP   						   ## //
// ##															   ## //
// ##			By Mitchell Jenkins - 2017 June 21 - AIE		   ## //
// ################################################################## //
#pragma once
#include "tkString.h"
#include "tkLinkedList.h"

namespace tk {
	namespace std {
		/* ---- HASH MAP ---- */
		template<typename T> class HashMap {
		
		public:
			/* DEFAULT CONSTRUCTOR */
			HashMap() {}
			/* DEFAULT DECONSTRUCTOR */
			~HashMap() {}

			/* ---- ADD ----
			Adds a map to the hash map
			#param key - The key used to access the value in the future
			#param value - The value that will be assigned to the key*/
			void Add(tk::String key, T value) {
				m_key.push_back(Hash(key));
				m_value.push_back(value);
			}

			/* ---- REMOVE ----
			Deletes a map
			#param key - The key the value that will be deleted*/
			void Remove(tk::String key) {
				int index = m_key.find_i(Hash(key));
				m_key.erase(index);
				m_value.erase(index);
			}

			/* ---- GET ----
			Returns the value assigned to the key
			#param key - The key used to get the value
			#return T& - The value assigned to the key*/
			T& Get(tk::String key) {
				return m_value.find(m_key.find_i(Hash(key)));
			}

			/* ---- PRINT ----
			Prints the Hash Map to console*/
			void print() {
				printf("Values: "); m_value.print();
				printf("Keys: "); m_key.print();
			}

			/* ---- HASH ----
			Gets the hash of the key
			#param key - the key for the hash
			#return u_int - the hash for the key*/
			unsigned int Hash (tk::String key) {
				unsigned int hash = 0, x = 0;
				for (unsigned int i = 0; (int)i < key.length(); i++) {
					hash = (hash << 4) + key.data[i];
					if ((x = hash & 0xF0000000L) != 0) {
						hash ^= (x >> 24);
						hash &= ~x;
					}
				} return (hash & 0x7FFFFFFF);
			}
		private:
			LinkedList<T> m_value;
			LinkedList<UINT> m_key;
		};

	}
}