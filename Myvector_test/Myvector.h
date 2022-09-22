//
// Created by 肖越 on 2022/9/17.
//

#ifndef INC_22_9_17_VECTOR1_MYVECTOR_H
#define INC_22_9_17_VECTOR1_MYVECTOR_H

#endif //INC_22_9_17_VECTOR1_MYVECTOR_H
#pragma once
#include <iostream>
#include <assert.h>
using namespace std;

namespace xy {
    template<class T>
    class vector {
    public:
        //vector的空间是由指针维护的
        typedef T* iterator;
        typedef const T* const_iterator;
        //实际上STL中并没有,这里是为了方便打印
        void Print()
        {
            for(size_t i = 0; i < size(); i++)
            {
                cout << _start[i] << " ";
            }
            cout << endl;
        }
        //迭代器
        iterator begin() {
            return _start;
        }

        iterator end() {
            return _finish;
        }

        //const
        const_iterator begin() const {
            return _start;
        }

        const_iterator end() const {
            return _finish;
        }

        size_t size() const {
            return _finish - _start;
        }

        size_t capacity() const {
            return _end_of_storage - _start;
        }

        bool empty() {
            return capacity() == size();
        }

        T &operator[](size_t pos) {
            assert(pos < size());
            return _start[pos];
        }

        const T &operator[](size_t pos) const {
            assert(pos < size());
            return _start[pos];
        }

        T &front() {
            return *_start;
        }

        const T &front() const {
            return *_start;
        }

        T &back() {
            return *(_finish - 1);
        }

        const T &back() const {
            return *(_finish - 1);
        }

        vector<T> &operator=(vector<T> &v) {
            swap(v);
            return *this;
        }

        void swap(vector<T> &v) {
            std::swap(v._start, _start);
            std::swap(v._finish, _finish);
            std::swap(v._end_of_storage, _end_of_storage);
        }

        //构造函数
        //1.无参
        //由于初始化的重要性,使用初始化列表
        vector()
                : _start(nullptr)
                , _finish(nullptr)
                , _end_of_storage(nullptr)
                {}

        //2.有参
        //v2(v1)
        //传统写法
//        vector(const vector<T>& v)
//                :_start(nullptr)
//                , _finish(nullptr)
//                , _end_of_storage(nullptr)
//        {
//            _start = new T[v.size()];//开相同大小的内存
//            //memcpy(_start, v._start, v.size());
//            for(size_t i = 0; i < v.size(); i++)//拷贝数据
//            {
//                _start[i] = v._start[i];
//            }
//            _finish = _start + v.size();
//            _end_of_storage = _start + v.capacity();
//        }
        //v2(v1)
        //新写法1
        vector(const vector<T>& v)
                : _start(nullptr)
                , _finish(nullptr)
                , _end_of_storage(nullptr) {
            vector<T> tmp = v;
            swap(tmp);
        }

        //构造n个val值
//        vector(size_t n, const T &val = T())//这里的T()是T类型的默认构造
//                : _start(nullptr), _finish(nullptr), _end_of_storage(nullptr) {
//            reserve(n);
//            for (size_t i = 0; i < n; i++) {
//                _start[i] = val;
//            }
//        }
        vector(int n, const T& val = T())
                :_start(nullptr)
                , _finish(nullptr)
                , _end_of_storage(nullptr)
        {
            _start = new T[n];
            _finish = _start;
            _end_of_storage = _start + n;
            //对申请的空间初始化
            for (int i = 0; i < n; i++)
            {
                *_finish++ = val;
            }
        }

        //任意容器的迭代器区间构造
        template<class InputIterator>
        vector(InputIterator begin, InputIterator end)
                :_start(nullptr)
                , _finish(nullptr)
                , _end_of_storage(nullptr)
        {
            while (begin < end)
            {
                push_back(*begin);
                begin++;
            }
        }

        //析构函数
        ~vector() {
            assert(_start);

            delete[] _start;
            _start = nullptr;
            _finish = nullptr;
            _end_of_storage = nullptr;
        }

        void reserve(size_t n) {
            size_t len = size();
            if (n > capacity())//空间不够就扩容
            {
                T *tmp = new T[n];
                for (size_t i = 0; i < len; i++) {
                    tmp[i] = _start[i];
                }
                delete[] _start;//释放原空间

                //更新新空间的成员变量
                _start = tmp;
                _finish = _start + len;
                _end_of_storage = _start + n;
            }

        }

        void resize(size_t n, const T &val) {
            //1.要修改的容量小于当前元素个数
            if (n < size()) {
                _finish = _start + n;//将个数更新到第n个
                return;
            }
            //2.大于容量,扩容
            if (n > capacity()) {
                reserve(n);
            }
            //3.介于两者之间,直接增加size且尾插n个元素
            iterator begin = _finish;
            _finish = _start + n;
            while (begin < _finish) {
                *begin = val;
                begin++;
            }
        }

        iterator insert(iterator pos, const T &x) {

            assert(pos <= _finish);

            if (size() == capacity())//扩容
            {
                size_t newCapacity = (capacity() == 0) ? 4 : (capacity() * 2);
                reserve(newCapacity);

                //更新pos
                pos = _start + size();
            }
            //挪动数据
            iterator end = _finish - 1;
            while (end >= pos) {
                *(end + 1) = *end;
                end--;
            }
            *pos = x;//插入
            _finish++;//更新长度
            return pos;//返回插入的位置的迭代器
        }

        void push_back(const T &x) {
            insert(end(), x);
        }

        void pop_back() {
            assert(_finish > _start);
            _finish--;
        }

        //返回值是要删除的位置
        iterator erase(iterator pos) {
            iterator end = pos + 1;
            while (end >= pos) {
                *(end + 1) = *end;
                end--;
            }

            _finish--;

            return pos;
        }

    private:
        iterator _start;//元素开始(结合图示)
        iterator _finish;//元素末尾
        iterator _end_of_storage;//容量的末尾
    };
}

