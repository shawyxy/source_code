#pragma once
const int PRIMECOUNT = 28;
// 定义结点类
template<class T>
struct HashNode
{
    T _data;                    // 保存数据
    HashNode<T>* _next;         // 后继指针
    HashNode(const T& data)     // 结点构造函数
        :_data(data)
        , _next(nullptr)
    {}
};
// 哈希函数
template<class K>
struct HashFunc
{
    size_t operator()(const K& key)
    {
        return (size_t)key;
    }
};
// 模板的特化
template<>
struct HashFunc<string>
{
    size_t operator()(const string& s)
    {
        size_t value = 0;
        for (auto ch : s)
        {
            value = value * 131 + ch;
        }
        return value;
    }
};

// 前置声明
template<class K, class T, class KeyOfT, class Hash>
class HashTable;

//正向迭代器
template<class K, class T, class KeyOfT, class Hash = HashFunc<K>>
struct __HTIterator
{
    typedef HashNode<T> Node;                         // 哈希结点类型
    typedef HashTable<K, T, KeyOfT, Hash> HT;         // 哈希表类型
    typedef __HTIterator<K, T, KeyOfT, Hash> Self;    // 正向迭代器类型

    Node* _node;            //结点指针
    HT* _pht;               //哈希表的地址

    // 构造函数
    __HTIterator(Node* node, HT* pht)
        :_node(node)
        , _pht(pht)
    {}
    T& operator*()
    {
        return _node->_data;
    }
    T* operator->()
    {
        return &_node->_data;
    }
    bool operator!=(const Self& s) const
    {
        return _node != s._node;
    }

    bool operator==(const Self& s) const
    {
        return _node == s._node;
    }
    // 前置++
    Self& operator++()
    {
        if (_node->_next)                   // 当前结点不是哈希桶的最后一个结点
        {
            _node = _node->_next;           // 迭代
        }
        else                                // 当前结点是哈希桶的最后一个结点
        {
            KeyOfT kot;
            Hash hash;
            size_t index = hash(kot(_node->_data)) % _pht->_table.size(); // 得到当前哈希桶的下标
            index++;                                                      // 下标+1
            while (index < _pht->_table.size())                           // 遍历哈希表中所有哈希桶
            {
                if (_pht->_table[index])                                  // 当前哈希桶不为空
                {
                    _node = _pht->_table[index];
                    return *this;                                         // 更新结点指针并返回
                }
                index++;                                                  // 当前哈希表为空，往后找
            }
            _node = nullptr;                                              // 上一个是空桶
        }
        return *this;
    }
};
template<class K, class T, class KeyOfT, class Hash = HashFunc<K>>
class HashTable
{
    typedef HashNode<T> Node;

    // 将正向迭代器类声明为哈希表类的友元
    template<class K, class T, class KeyOfT, class Hash>
    friend struct __HTIterator;
public:
    typedef __HTIterator<K, T, KeyOfT, Hash> iterator;          // 定义迭代器

    
    iterator begin()
    {
        size_t i = 0;
        while (i < _table.size())                           // 遍历哈希表中所有哈希桶
        {
            if (_table[i])                                  // 当前哈希桶不为空
            {
                return iterator(_table[i], this);           // 返回桶地址和表地址构造的迭代器
            }
            i++;                                            // 下一个桶
        }
        return end();
    }
    iterator end()
    {
        return iterator(nullptr, this);                     // 返回桶地址和表地址构造的迭代器
    }
public:
    // 构造函数
    HashTable() = default; // 显式指定生成默认构造函数
    // 拷贝构造函数
    HashTable(const HashTable& ht)
    {
        _table.resize(ht._table.size());
        for (size_t i = 0; i < ht._table.size(); i++)
        {
            if (ht._table[i])
            {
                Node* cur = ht._table[i];
                while (cur)
                {
                    Node* copy = new Node(cur->_data);
                    copy->_next = _table[i];
                    _table[i] = copy;
                    cur = cur->_next;
                }
            }
        }
        _size = ht._size;
    }
    // 赋值运算符重载函数
    HashTable& operator=(HashTable ht)
    {
        _table.swap(ht._table);
        swap(_size, ht._size);
        return *this;
    }
    // 析构函数
    ~HashTable()
    {
        for (size_t i = 0; i < _table.size(); i++)
        {
            Node* cur = _table[i];
            while (cur)
            {
                Node* next = cur->_next;
                free(cur);
                cur = next;
            }
            _table[i] = nullptr;
        }
    }
    // 查找函数
    iterator Find(const K& key)
    {
        if(_table.size() == 0)
        {
            return end();
        }
        KeyOfT kot;
        Hash hash;
        size_t pos = hash(key) % _table.size();   // 得到下标值
        HashNode<T>* cur = _table[pos];     // 找到哈希桶首地址
        while (cur)                         // 遍历链表
        {
            if (kot(cur->_data) == key)
            {
                return iterator(cur, this);
            }
            cur = cur->_next;
        }
        return end();
    }
    // 插入函数
    pair<iterator, bool> Insert(const T& data)
    {
        KeyOfT kot;
        Hash hash;
        iterator ret = Find(kot(data));
        if(ret != end())                                    // 元素已经存在
        {
            return make_pair(ret, false);
        }

        // 扩容操作
        if(_size == _table.size())
        {
            size_t oldSize = _table.size();
//            size_t newSize = oldSize == 0 ? 10 : 2 * oldSize;
            size_t newSize = __stl_next_prime(oldSize);
            vector<Node*> newTable;                         // 建立新表
            newTable.resize(newSize);                       // 扩容
            for(size_t i = 0; i < oldSize; i++)             // 转移数据
            {
                Node* cur = _table[i];                      // 下标i对应的链表的首地址
                while(cur)
                {
                    Node* next = cur->_next;

                    size_t hashi = hash(kot(cur->_data)) % newSize;// 新下标值
                    cur->_next = newTable[hashi];           // 重新链接
                    newTable[hashi] = cur;

                    cur = next;                             // 链表向后迭代
                }
                _table[i] = nullptr;
            }
            _table.swap(newTable);                          // 替换新哈希表
        }

        // 头插元素
        size_t hashi = hash(kot(data)) % _table.size();
        Node* newnode = new Node(data);
        newnode->_next = _table[hashi];
        _table[hashi] = newnode;
        _size++;

        return make_pair(iterator(newnode, this), true);
    }
    // 删除函数
    bool Erase(const K& key)
    {
        size_t pos = key % _table.size();       // 得到key值对应的哈希桶下标
        Node* prev = nullptr;
        Node* cur = _table[pos];
        while (cur)
        {
            if(cur->_kv.first == key)           // 找到和key值对应的结点
            {
                if (prev == nullptr)            // 找到的结点在链表首部
                {
                    _table[pos] = cur->_next;   // 直接将头部往后移动一个单位
                }
                else                            // 找到的结点不在链表首部
                {
                    prev->_next = cur->_next;   // 直接跳过它即可
                }

                delete cur;                     // 释放结点资源
                _size--;                        // 更新计数器
                return true;
            }
            prev = cur;                         // 迭代
            cur = cur->_next;
        }
        return false;
    }
    // 打印函数
    void Print()
    {
        for (size_t i = 0; i < _table.size(); ++i)
        {
            Node* cur = _table[i];
            while(cur)
            {
                printf("[%d:%d]", i, cur->_kv.first);
                if(cur->_next)
                    printf("->");

                cur = cur->_next;
            }
            if(_table[i] == nullptr)
                printf("[%d:*] ", i);
            cout << endl;
        }
    }
    // 获取新哈希表素数长度
    inline size_t __stl_next_prime(size_t n)
    {
        static const size_t __stl_num_primes = 28;
        static const size_t __stl_prime_list[__stl_num_primes] =
        {
            53,         97,         193,       389,       769,
            1543,       3079,       6151,      12289,     24593,
            49157,      98317,      196613,    393241,    786433,
            1572869,    3145739,    6291469,   12582917,  25165843,
            50331653,   100663319,  201326611, 402653189, 805306457,
            1610612741, 3221225473, 4294967291
        };

        for (size_t i = 0; i < __stl_num_primes; ++i)
        {
            if (__stl_prime_list[i] > n)
            {
                return __stl_prime_list[i];
            }
        }

        return -1;
    }
private:
    vector<Node*> _table;       // 哈希表
    size_t _size = 0;           // 有效元素个数
};