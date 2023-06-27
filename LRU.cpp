/*
最近最久未使用的置换算法
*/

#include<iostream>
#include<unordered_map>

using namespace std;

//使用双向链表+哈希表实现
struct DLinkedNode{
    int key,val;
    DLinkedNode* pre,* next;
    DLinkedNode():key(0),val(0),pre(nullptr),next(nullptr){};
    DLinkedNode(int key_,int val_):key(key_),val(val_),pre(nullptr),next(nullptr){};
};

class LRUCache {
    int capacity;
    int size;
    DLinkedNode *head;
    DLinkedNode *tail;
    unordered_map<int,DLinkedNode*> cacahe;
public:
    LRUCache(int capacity) {
        this->capacity = capacity;
        size = 0;
        head = new DLinkedNode();
        tail = new DLinkedNode();
        head->next = tail;
        tail->pre = head;
    }

    //需要实现几个函数：
    //1.删除节点函数
    void removeNode(DLinkedNode* node){
        node->pre->next = node->next;
        node->next->pre = node->pre;
    }
    
    //2 将一个节点加入到头部
    void AddToHead(DLinkedNode* node){
        node->next = head->next;
        node->pre = head;
        head->next->pre = node;
        head->next = node;
    }

    //3.将一个链表中的节点移动到头部
    void moveToHead(DLinkedNode* node){
        removeNode(node);
        AddToHead(node);
    }

    //4.删除链表尾部的节点
    DLinkedNode* removeTail(){
        DLinkedNode* res = tail->pre;
        removeNode(res);
        return res;
    }

    int get(int key) {
        if(!cacahe.count(key)){
            //如果不存在，返回-1
            return -1;
        }else{
            DLinkedNode* res = cacahe[key];
            moveToHead(res);
            return res->val;
        }
    }
    
    void put(int key, int value) {
        if(!cacahe.count(key)){
            //如果不存在，则需要创建
            DLinkedNode* node = new DLinkedNode(key,value);
            AddToHead(node);
            cacahe[key] = node;
            size++;
            if(size > capacity){
                DLinkedNode* tailNode = removeTail();
                cacahe.erase(tailNode->key);
                delete tailNode;
                size--;
            }
        }else{
            DLinkedNode* node = cacahe[key];
            node->val = value;
            moveToHead(node);
        }
    }
};


int main(){
    int capacity = 10;

    LRUCache* obj = new LRUCache(capacity);
    obj->put(1,10);
    int param_1 = obj->get(1);
    
    return 0;
}
