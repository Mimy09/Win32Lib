#pragma once
#include <tkString.h>
#include <tkLinkList.h>

namespace tk {
	namespace std {
		template<typename T> class HashMap {
		
		public:
			HashMap() {}
			~HashMap() {}

			void Put(tk::String key, T value) {
				m_key.InsertEnd(Hash(key));
				m_value.InsertEnd(value);
			}

			T Get(tk::String key) {
				return m_value.Index(m_key.FindValuePos(Hash(key)));
			}

			unsigned int Hash (tk::String key) {
				/*
				unsigned int hash = 0;
				unsigned int ho = hash & 0xf8000000;

				for (int i = 0; i < str.length(); i++) {
					hash = hash << 5;
					hash = hash ^ (ho >> 27);
					hash = hash ^ str.data[i];
				} return hash;
				
				
				unsigned int hash = 0;
				for (unsigned int i = 0; i < str.length(); i++) {
					hash = (hash * 1313) + str.data[i];
				} return (hash & 0x7FFFFFFF);
				*/
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
			LinkList<T> m_value;
			LinkList<UINT> m_key;
		};

	}
}