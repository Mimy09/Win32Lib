// ################################################################## //
// ##							HASH MAP   						   ## //
// ##															   ## //
// ##			By Mitchell Jenkins - 2017 June 21 - AIE		   ## //
// ################################################################## //
#pragma once
#include "tkString.h"
#include "tkLinkedList.h""

namespace tk {
	namespace std {
		template<typename T> class HashMap {
		
		public:
			HashMap() {}
			~HashMap() {}

			void Add(tk::String key, T value) {
				m_key.push_back(Hash(key));
				m_value.push_back(value);
			}

			void Remove(tk::String key) {
				int index m_key.FindValuePos(Hash(key));
				m_key.erase(index);
				m_value.erase(index);
			}

			T Get(tk::String key) {
				return m_value.find(m_key.find_i(Hash(key)));
			}

			unsigned int Hash (tk::String key) {
				unsigned int hash = 0, x = 0;
				for (unsigned int i = 0; i < key.length(); i++) {
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