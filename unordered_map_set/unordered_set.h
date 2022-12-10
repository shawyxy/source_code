#pragma once
#include "HashTable.h"
namespace xy
{
    template<class K, class Hash = HashFunc<K>>
    class unordered_set
    {
        struct SetKeyOfT
        {
            const K& operator()(const K& key)
            {
                return key;
            }
        };
    public:
        typedef typename HashTable<K, K, SetKeyOfT>::iterator iterator; // ���������    
        
        iterator begin()
        {
            return _ht.begin();
        }
        iterator end()
        {
            return _ht.end();
        }
        // ���뺯��
        pair<iterator, bool> insert(const K& key)
        {
            return _ht.Insert(key);
        }
        // ɾ������
        void erase(const K& key)
        {
            _ht.Erase(key);
        }
        // ���Һ���
        iterator find(const K& key)
        {
            return _ht.Find(key);
        }
    private:
        HashTable<K, K, SetKeyOfT> _ht;
    };

    void test_set()
    {
        unordered_set<int> s;
        s.insert(2);
        s.insert(3);
        s.insert(1);
        s.insert(2);
        s.insert(5);

        unordered_set<int>::iterator it = s.begin();
        //auto it = s.begin();
        while (it != s.end())
        {
            cout << *it << " ";
            ++it;
        }
        cout << endl;
    }
}
