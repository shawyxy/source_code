//
// Created by 肖越 on 2022/10/25.
//
#pragma once
#include <iostream>
#include <vector>
#define nullptr NULL

using namespace std;
// 定义结点类
template<class K>
struct BSTreeNode
{
    K _key;                     // 值
    BSTreeNode* _left;          // 左孩子结点
    BSTreeNode* _right;         // 右孩子结点
    BSTreeNode(const K& key)    // 构造函数
    :_key(key)
    , _left(nullptr)
    , _right(nullptr)
    {}
};

// 定义二叉搜索树类
template<class K>
class BSTree
{
    typedef BSTreeNode<K> Node;
public:
    // 构造函数
    BSTree()
    :_root(nullptr)
    {}
    // 拷贝构造函数
    BSTree(const BSTree<K>& t)
    {
        _root = _Copy(t._root);
    }
    // 析构函数
    ~BSTree()
    {
        _Destory(_root);
        _root = nullptr;
    }
    // operator= 重载
    BSTree<K>& operator=(BSTree<K>& t)
    {
        swap(t._root, _root);
        return *this;
    }

    // 删除函数
    bool Erase(const K& key)
    {
        Node* parent = nullptr;                 // 由于需要链接，所以要保存父结点的位置
        Node* cur = _root;                      // 当前结点

        while(cur)
        {
            if(cur->_key > key)                 // 要删除的结点的值小于当前结点的值
            {                                   // 说明要删除的结点在当前结点的左子树
                parent = cur;                   // 更新父结点
                cur = cur->_left;               // 更新cur
            }
            else if(cur->_key < key)            // 要删除的结点的值大于当前结点的值
            {                                   // 说明要删除的结点在当前结点的右子树
                parent = cur;
                cur = cur->_right;
            }
            else                                // 此时找到了要删除的结点
            {
                if(cur->_left == nullptr)       // 1. 待删除结点的左子树为空
                {
                    if(cur == _root)            // 待删除结点为根结点
                        _root = cur->_right;    // 将右子树作为新树
                    else                        // 待删除结点不为根结点，将待删除结点的父结点更新到当前结点
                    {
                        if(cur == parent->_left)// 待删除结点为父结点的左孩子
                            parent->_left = cur->_right;// 将左孩子的右子树链接到父结点的左孩子上
                        else if(cur == parent->_right)// 待删除结点为父结点的右孩子
                            parent->_right = cur->_right;// 将左孩子的右子树链接到父结点的右孩子上
                    }
					delete cur;					// 释放结点资源
					return true;				// 表示删除成功
                }
                else if(cur->_right == nullptr) // 2. 待删除结点的右子树为空，步骤相同
                {
                    if(cur == _root)
                        _root = cur->_left;
                    else
                    {
                        if(cur == parent->_left)
                            parent->_left = cur->_left;
                        else if(cur == parent->_right)
                            parent->_right = cur->_left;
                    }
					delete cur;					// 释放结点资源
					return true;				// 表示删除成功
                }
                else                        // 3. 待删除结点左右子树均不为空，使用替换法
                {
                    Node* Max = cur->_left; // 记录待删除结点左子树的最右边的结点，也就是最大结点
                    Node* MaxParent = cur;  // 记录最大结点的父结点

                    while(Max->_right)
                    {
                        MaxParent = Max;
                        Max = Max->_right;
                    }
                                            // 找到待删除结点的左子树的最右节点
                                            // 将最右结点的值替换给待删除的结点的值
                    cur->_key = Max->_key;
                                            // 替换结点可能有一个或没有孩子，有也只可能是右孩子
                                            // 替换以后，待删除结点变为替换结点
                    if(Max == MaxParent->_right)// 待删除结点（替换结点）是父结点的左孩子
                        MaxParent->_right = Max->_left;
                    else if(Max == MaxParent->_left)
                        MaxParent->_left = Max->_right;
                        
                    delete Max;             // 清理替换结点
                }
                return true;
            }
        }
        return false;// 上面的循环中没有找到
    }

    // 递归删除函数
    bool EraseR(const K& key)
    {
        return _EraseR(key, _root);
    }


    // 插入函数
    bool Insert(const K& key)
    {
        if(_root == nullptr)                // 插入一个空树
        {                                   // 插入的数作为根结点的值
            _root = new Node(key);
            return true;
        }
                                            // 树不为空
        Node* parent = nullptr;
        Node* cur = _root;
        while(cur)                          // 迭代，让cur找nullptr
        {
            if(key == cur->_key)            //插入结点和当前结点的值相同
            {
                return false;
            }
            else if(key < cur->_key)        // 插入结点的值小于当前结点的值
            {
                parent = cur;               // 保存父结点
                cur = cur->_left;           // 更新cur
            }
            else if(key > cur->_key)        // 插入结点的值大于当前结点的值
            {
                parent = cur;               // 保存父结点
                cur = cur->_right;          // 更新cur
            }
        }
                                            // 此时，cur已经走到空结点，parent是它的父结点
                                            // 链接新结点和父结点
        cur = new Node(key);                // 创建新结点，放在cur的位置
        if(key > parent->_key)              // 插入结点的值大于父结点的值
        {
            parent->_right = cur;
        }
        else if(key < parent->_key)         // 插入结点的值大于父结点的值
        {
            parent->_left = cur;
        }
        return true;
    }
    // 递归插入函数
    bool InsertR(const K& key)
    {
        return _InsertR(key, _root);
    }

    // 查找函数
    Node* Find(const K& key)
    {
        Node* cur = _root;
        while(cur)
        {
            if(key < cur->_key)
                cur = cur->_left;
            else if(key > cur->_key)
                cur = cur->_right;
            else
                return cur;
        }
        return nullptr;
    }
    Node* FindR(const K& key)
    {
        return _FindR(key, _root);
    }
    // 中序遍历
    void InOrder()
    {
        _InOrder(_root);
        cout << endl;
    }

private:
    // 拷贝构造子函数
    Node* _Copy(Node* root)
    {
        if(root == nullptr)
            return nullptr;
        
        Node* newnode = new Node(root->_key);
        newnode->_left = root->_left;
        newnode->_right = root->_right;
        return newnode;
    }
    // 递归删除子函数
    bool _EraseR(const K& key, Node* root)
    {
        if(root == nullptr)                 // 空树
            return false;

        Node* cur = root;

        if(key < cur->_key)                 // 待删除结点的值小于当前结点的值
            return _EraseR(key, cur->_left);// 走左子树
        else if(key > cur->_key)            // 同理
            return _ERaseR(key, cur->right);
        else                                // 待删除结点的值等于当前结点的值->找到待删除结点
        {
            Node* Del = cur;                // 保存待删除结点Del，稍后要delete
            if(cur->_left == nullptr)       // Del的左子树为空
                cur = cur->_right;
            else if(cur->_right = nullptr)  // Del的右子树为空
                cur = cur->_left;
            else                            // Del的左右子树都不为空
            {
                Node* Max = cur->_left;
                while(Max->_right)          // 找左子树的最右结点，也即是左子树的最大结点
                {
                    Max = Max->_right;
                }
                cur->_key = Max->_key;      // 替换
                return _EraseR(key, cur->_right);
            }
            delete Del;
            return true;
        }
    }
    // 递归插入子函数
    bool _InsertR(const K& key, Node*& root) // 注意这里必须传引用，否则最后链接不上
    {
        if(root == nullptr)
        {
            root = new Node(key);            // 插入的树为空
            return true;
        }
                                             // 插入的树不为空
        if(key < root->_key)
            return _InsertR(key, root->_left);
        else if(key < root->_key)
            return _InsertR(key, root->_right);
        else
            return false;
    }
    // 递归查找子函数
    Node* _FindR(const K& key, Node* root)
    {
        if(root == nullptr)// 树为空
            return nullptr;
        
        if(key < root->_key)
            return _FindR(key, root->_left);
        else if(key > root->_key)
            return _FindR(key, root->_right);
        else
            return root;
    }
    // 递归中序遍历子函数
    void _InOrder(const Node* root)
    {
        if(root == nullptr)
            return;
        
        _InOrder(root->_left);
        cout << root->_key << " ";
        _InOrder(root->_right);
    }
    // 析构子函数
    void _Destory(Node* root)
    {
        if(root == nullptr)
            return;
        
        _Destory(root->_left);
        _Destory(root->_right);
        delete root;
    }
private:
    Node* _root = nullptr;
};