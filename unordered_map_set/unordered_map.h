#include "HashTable.h"
namespace xy
{
	template<class K, class V, class Hash = HashFunc<K>>
	class unordered_map
	{
		struct MapKeyOfT
		{
			const K& operator()(const pair<K, V>& kv)
			{
				return kv.first;
			}
		};
	public:
		typedef typename HashTable<K, pair<K, V>, MapKeyOfT>::iterator iterator;

		iterator begin()
		{
			return _ht.begin();
		}
		iterator end()
		{
			return _ht.end();
		}
		//插入函数
		pair<iterator, bool> insert(const pair<K, V>& kv)
		{
			return _ht.Insert(kv);
		}
		//删除函数
		void erase(const K& key)
		{
			_ht.Erase(key);
		}
		//查找函数
		iterator find(const K& key)
		{
			return _ht.Find(key);
		}
		//赋值运算符重载
		V& operator[](const K& key)
		{
			pair<iterator, bool> ret = insert(make_pair(key, V()));
			iterator it = ret.first;
			return it->second;
		}
	private:
		HashTable<K, pair<K, V>, MapKeyOfT> _ht;
	};

	void test_map()
	{
		unordered_map<string, string> dict;
		dict.insert(make_pair("left", "左边"));
		dict.insert(make_pair("left", "离开"));
		dict.insert(make_pair("right", "右边"));
		dict.insert(make_pair("right", "正确"));
		dict.insert(make_pair("people", "人"));

		unordered_map<string, string>::iterator it = dict.begin();
		while (it != dict.end())
		{
			cout << it->first << ":" << it->second << endl;
			++it;
		}
		cout << endl;

		unordered_map<string, int> countMap;
		string arr[] = { "香蕉", "苹果", "香蕉", "橘子", "葡萄", "苹果"};
		for (auto e : arr)
		{
			countMap[e]++;
		}

		for (auto& kv : countMap)
		{
			cout << kv.first << ":" << kv.second << endl;
		}
	}
}
