#pragma once
#include <iostream>
using namespace std;
namespace xy
{
    //定义适配器Container
    template<class T, class Container = deque<T>>//这里的deque可以设置自己想要的结构,比如vector或list
            class stack{
            public:
                void push(const T& x)
                {
                    _con.push_back(x);
                }
                void pop()
                {
                    _con.pop_back();
                }
                T& top()
                {
                    return _con.back();
                }
                const T& top() const
                {
                    return _con.back();
                }
                bool empty()
                {
                    return _con.empty();
                }
                const size_t size() const
                {
                    return _con.size();
                }
                void swap(stack<T, Container>& st)
                {
                    std::swap(st._con);
                }
            private:
                Container _con;//定义成员变量
            };
    /////// __TEST__ ////////
    void test1()
    {
        stack<int> st;
        st.push(1);
        st.push(2);
        st.push(3);
        st.push(4);
        st.push(5);
        cout << "size:" << st.size() << endl;
        while(!st.empty())
        {
            cout << st.top() << " ";
            st.pop();
        }
        cout << endl;
    }
}