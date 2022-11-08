#include "BinarySearchTree.h"
/////////////////__TEST__//////////////////
void BSTreeInserTest()
{
    BSTree<int> t;
    vector<int> a = { 8, 3, 1, 10, 6, 4, 7, 14, 13, 4, 3 ,4 };
    // 非递归插入
    for(auto e : a)
    {
        t.Insert(e);
    }
    t.InOrder();
    cout << endl;
    // 递归插入
    for(auto e : a)
    {
        t.InsertR(e);
    }
    t.InOrder();
    cout << endl;
}
void BSTreeEraseTest()
{
    BSTree<int> t;
    vector<int> a = { 8, 3, 1, 10, 6, 4, 7, 14, 13, 4, 3 ,4 };
    // 非递归插入
    for(auto e : a)
    {
        t.Insert(e);
    }
    t.InOrder();
    cout << endl;

    // 删除 8
    t.Erase(8);
    t.InOrder();
    cout << endl;
    // 删除 13
    t.Erase(13);
    t.InOrder();
    cout << endl;
    // 删除 14
    t.Erase(14);
    t.InOrder();
    cout << endl;
    // 删除 4
    t.Erase(4);
    t.InOrder();
    cout << endl;
    // 删除 3 // error
    t.Erase(3);
    t.InOrder();
    cout << endl;

    // 递归插入
    BSTree<int> t1;
    // 插入
    for(auto e : a)
    {
        t1.Insert(e);
    }
    t1.InOrder();
    cout << endl;

    // 删除 8
    t1.Erase(8);
    t1.InOrder();
    cout << endl;
    // 删除 13
    t1.Erase(13);
    t1.InOrder();
    cout << endl;
    // 删除 14
    t1.Erase(14);
    t1.InOrder();
    cout << endl;
    // 删除 4
    t1.Erase(4);
    t1.InOrder();
    cout << endl;
    // 删除 3 // error
    t1.Erase(3);
    t1.InOrder();
    cout << endl;
}
void BSTreeFindTest()
{
    BSTree<int> t;
    vector<int> a = { 8, 3, 1, 10, 6, 4, 7, 14, 13, 4, 3 ,4 };
    // 非递归插入
    for(auto e : a)
    {
        t.Insert(e);
    }
    t.InOrder();
    cout << endl;

    cout << t.Find(3)->_key << endl;
    cout << t.Find(8)->_key << endl;
    //cout << t.Find(20)->_key << endl;
    cout << t.Find(13)->_key << endl;

    // 递归查找
    cout << "----------------------" << endl;
    cout << t.FindR(3)->_key << endl;
    cout << t.FindR(1)->_key << endl;
    cout << t.FindR(7)->_key << endl;
    cout << t.FindR(14)->_key << endl;


}
void BSTreeConstructorTest()
{
    BSTree<int> t;
    vector<int> a = { 8, 3, 1, 10, 6, 4, 7, 14, 13, 4, 3 ,4 };
    // 非递归插入
    for(auto e : a)
    {
        t.Insert(e);
    }
    t.InOrder();
    cout << endl;
    // 测试拷贝构造
    BSTree<int> t1(t);
    for(auto e : a)
    {
        t1.Insert(e);
    }
    t1.InOrder();
    cout << endl;
    // 测试operator=
    BSTree<int> t2 = t;
    for(auto e : a)
    {
        t2.Insert(e);
    }
    t2.InOrder();
    cout << endl;
}
int main()
{
    //BSTreeInserTest();
    //BSTreeEraseTest();
    //BSTreeFindTest();
    BSTreeConstructorTest();
    return 0;
}
