#pragma once

#include "list.h"

namespace dank {
	template<typename K, typename D>
	struct FD_MAP_PAIR {
		K key;
		D data;
	};

	template<typename K, typename D>
	class Map {
	private:
		List<D> data;
		List<K> keys;

		inline D& Add(K key) {
			keys.Push_back(key);

			size_t size = keys.GetSize();
			data.Resize(size);

			return data[size - 1];
		}

	public:
		Map(unsigned int size = 0) {
			data.Reserve(size);
			keys.Reserve(size);
		}

		~Map() {

		}

		inline Map<K, D>& operator=(const Map<K, D>& map) {
			data = map.data;
			keys = map.keys;
			return *this;
		}

		inline void Reserve(unsigned int size) {
			data.Reserve(size);
			keys.Reserve(size);
		}

		inline void Remove(K key) {
			size_t index = keys.Find(key);
			if (index == (uint_t)-1) return;

			keys.RemoveIndex(index);
			data.RemoveIndex(index);
		}

		inline D& operator[](K key) {
			size_t loc = keys.Find(key);
			if (loc != (uint_t)-1) {
				return data[loc];
			}

			return Add(key);
		}

		inline void Add(K key, D item) {

			data << item;
			keys << key;
		}

		inline D Retrieve(K key) const {
			size_t index = keys.Find(key);

			if (index == (size_t)-1) return D();

			return data.Get(index);
		}

		inline void Clear() { data.Clear(); keys.Clear(); }

		inline uint_t GetItems() const { return keys.GetSize(); }

		inline List<K> GetKeyList() const { return keys; }
		inline List<D> GetDataList() const { return data; }

		inline FD_MAP_PAIR<K, D> GetPair(size_t index) { return { keys[index], data[index] }; }
	};
}