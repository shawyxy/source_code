#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
#include <list>
#include <vector>
#include <algorithm>
#include <assert.h>
using namespace std;

namespace xy {
    //定义结点结构体(也可以用类)
    template<class T>
    struct _list_node {
        //成员变量
        _list_node* _prev;
        _list_node* _next;
        T val;

        //成员函数
        _list_node(const T& x = T())
                : _prev(nullptr), _next(nullptr), val(x) {}
    };

    //用结构体封装不同类型的迭代器
    //由于list的内存不是连续的,但依然要用到++或--之类的操作
    //为了无感地使用这些操作符,需要重载
    template<class T, class Ref, class Ptr>
    struct _list_iterator {
        typedef _list_iterator<T, Ref, Ptr> Self;
        //返回引用类型
        typedef Ref reference;
        //返回指针类型
        typedef Ptr pointer;
        //定义结点
        typedef _list_node<T> Node;
        Node* _node;
        //迭代器的构造函数
        _list_iterator(Node* node)
                : _node(node) {}

        //重载运算符
        //判断头结点指针是否相同
        bool operator==(const Self& it) const {
            return _node == it._node;
        }

        bool operator!=(const Self& it) const {
            return _node != it._node;
        }
        //对于指针是解引用*访问数据,但是对于链表指针解引用访问的是
        //整个结点,所以返回结点的数据val
        reference operator*() {
            return _node->val;
        }

        //只有结构体指针,也就是自定义类型会使用"->"访问成员
        pointer operator->() {
            return &(operator*());//**返回数据成员的地址**
        }

        //前置++
        Self& operator++() {
            _node = _node->_next;
            return *this;
        }

        //后置++
        Self operator++(int) {
            Self ret(*this);
            _node = _node->_next;
            return ret;
        }

        //前置--
        Self& operator--() {
            _node = _node->_prev;
            return *this;
        }

        //后置--
        Self operator--(int) {
            Self tmp(*this);
            _node = _node->_prev;
            return tmp;
        }
    };

    //模拟实现list
    template<class T>
    class list {
    public:
        typedef _list_node<T> Node;//定义结点类型

        //迭代器
    public:
        typedef _list_iterator<T, T&, T*> iterator;
        typedef _list_iterator<T, const T&, const T*> const_iterator;
        //默认成员函数:
        //构造,析构,operator=
        list() {
            CreateHead();
        }

        //批量构造
        list(int n, const T& val = T()) {
            CreateHead();
            for (int i = 0; i < n; ++i)
                push_back(val);
        }

        //迭代器区间构造
        template<class Iterator>
        list(Iterator begin, Iterator end) {
            CreateHead();
            while (begin != end) {
                push_back(*begin);
                begin++;
            }
        }

        //template <class Iterator>
        //拷贝构造
        list(list<T>& ls) {
            CreateHead();
            list<T> tmp(ls.begin(), ls.end());
            swap(tmp);
        }

        //析构
        ~list() {
            clear();
            delete _head;
            _head = nullptr;
        }

        //重载operator=
        list<T>& operator=(list<T> ls) {
            swap(ls);
            return *this;
        }
        //迭代器相关
        iterator begin() {
            return iterator(_head->_next);
        }

        iterator end() {
            return iterator(_head);
        }

        const_iterator begin() const {
            return const_iterator(_head->_next);
        }

        const_iterator end() const {
            return const_iterator(_head);
        }

        //访问容器
        T& front() {
            return _head->val;
        }

        T& back() {
            return _head->_prev->val;
        }

        const T& front() const {
            return _head->val;
        }

        const T& back() const {
            return _head->_prev->val;
        }

        //插入和删除
        iterator insert(iterator pos, const T& x) {
            //prev (pos,newnode) cur
            assert(pos._node);
            Node* cur = pos._node;
            Node* prev = cur->_prev;
            Node* newnode = new Node(x);
            //prev<-->newnode
            prev->_next = newnode;
            newnode->_prev = prev;
            //newnode<-->cur
            newnode->_next = cur;
            cur->_prev = newnode;

            return iterator(newnode);//返回插入位置的迭代器
        }

        void push_back(const T& x) {
            insert(end(), x);
        }

        void push_front(const T& x) {
            insert(begin(), x);
        }

        void pop_back() {
            erase(--end());
        }

        void pop_front() {
            erase(begin());
        }

        //交换函数
        void swap(list<int>& ls) {
            //xy::list<int> tmp = ls;//这里不能这样写，因为=重载也是调用swap的。
            std::swap(ls._head, _head);
        }

        iterator erase(iterator pos) {
            //prev del(pos) next
            Node* delNode = pos._node;
            Node* retNode = delNode->_next;

            //删除delNode
            delNode->_prev->_next = delNode->_next;
            delNode->_next->_prev = delNode->_prev;
            delete delNode;
            delNode = nullptr;
            //prev next
            return retNode;
        }

        //清除操作
        void clear() {
            //_head cur next
            Node* cur = _head->_next;
            while (cur != _head) {
                _head->_next = cur->_next;
                delete cur;
                cur = _head->_next;//这里的_head不能是cur,因为cur已经被释放了
            }
            //_head == cur  ----->  _head == _head->next
            _head->_next = _head->_prev = _head;
        }

        size_t size() {
            size_t count = 0;
            iterator it = begin();
            while (it != end()) {
                count++;
                it++;
            }

            return count;
        }

        //容量相关
        bool empty() {
            return begin() == end();
        }

        void resize(size_t newsize, const T& data = T()) {
            size_t oldsize = size();
            if (newsize <= oldsize) {
                // 有效元素个数减少到newsize
                while (newsize < oldsize) {
                    pop_back();
                    oldsize--;
                }
            }
            else {
                while (oldsize < newsize) {
                    push_back(data);
                    oldsize++;
                }
            }
        }

    private:
        Node* _head;//指向头结点的指针
        //把头结点初始化函数设为私有,然后让它作为默认构造函数的一部分
        void CreateHead() {
            _head = new Node;
            _head->_prev = _head;
            _head->_next = _head;
        };

    };

    //////////// __TEST__ /////////////
    // 打印
    template<class T>
    void PrintList(const list<T>& l)
    {
        auto it = l.begin();
        while (it != l.end())
        {
            cout << *it << " ";
            ++it;
        }

        cout << endl;
    }
    // 测试List的构造
    void test1()
    {
        xy::list<int> l1;
        xy::list<int> l2(10, 5);
        PrintList(l2);

        int array[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 0 };
        xy::list<int> l3(array, array + sizeof(array) / sizeof(array[0]));
        PrintList(l3);

        xy::list<int> l4(l3);
        PrintList(l4);

        l1 = l4;
        PrintList(l1);
    }

// PushBack()/PopBack()/PushFront()/PopFront()
    void test2()
    {
        // 测试PushBack与PopBack
        xy::list<int> l;
        l.push_back(1);
        l.push_back(2);
        l.push_back(3);
        PrintList(l);

        l.pop_back();
        l.pop_back();
        PrintList(l);

        l.pop_back();
        cout << l.size() << endl;

        // 测试PushFront与PopFront
        l.push_front(1);
        l.push_front(2);
        l.push_front(3);
        PrintList(l);

        l.pop_front();
        l.pop_front();
        PrintList(l);

        l.pop_front();
        cout << l.size() << endl;
    }

// 测试insert和erase
    void test3()
    {
        int array[] = { 1, 2, 3, 4, 5 };
        xy::list<int> l(array, array + sizeof(array) / sizeof(array[0]));

        auto pos = l.begin();
        l.insert(l.begin(), 0);
        PrintList(l);

        ++pos;
        l.insert(pos, 2);
        PrintList(l);

        l.erase(l.begin());
        l.erase(pos);
        PrintList(l);

        // pos指向的节点已经被删除，pos迭代器失效
        cout << *pos << endl;

        auto it = l.begin();
        while (it != l.end())
        {
            it = l.erase(it);
        }
        cout << l.size() << endl;
    }

}
