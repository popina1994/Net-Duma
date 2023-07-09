#pragma once
#include <vector>
#include <list>
#include <exception>
#include <stdexcept>


template <typename K, typename V>
class MultiMap
{
	std::vector<std::list<std::pair<K, V>>> m_vBuckets;
public:
	MultiMap(int cap): m_vBuckets(cap)
	{

	}

	void insertValue(const K& key, const V& val)
	{
		int hashValue = std::hash<K>()(key) % m_vBuckets.size();
		m_vBuckets[hashValue].push_back({ key, val });
	}

	V& getValue(K keySearch)
	{
		int hashValue = std::hash<K>()(keySearch) %m_vBuckets.size();
		auto lBucket = m_vBuckets[hashValue];
		for (const auto& [key, val] : lBucket)
		{
			if (key == keySearch)
			{
				return lBucket[key];
			}
		}
		throw std::invalid_argument("No element");
	}

	void eraseKey(const K& keySearch)
	{
		int hashValue = std::hash<K>()(keySearch) % m_vBuckets.size();
		auto lBucket = m_vBuckets[hashValue];
		for (auto it = lBucket.begin(); it != lBucket.end(); it++)
		{
			if (it->first == keySearch)
			{
				lBucket.erase(it);
				return; 
			}
		}
		return 0;
	}
};

