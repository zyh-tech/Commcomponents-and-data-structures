/*
最近最久未使用的置换算法
*/

#include<iostream>
#include<unordered_map>
#include<list>

using namespace std;

struct Node{
    int key, val, freq;
    Node(int _key, int _val, int _freq):
        key(_key),val(_val),freq(_freq){};
};

class LFUCache{
    int minfreq, capacity;
    unordered_map<int,list<Node>> freq_table;
    unordered_map<int,list<Node>::iterator> key_table;
public:
    LFUCache(int _capacity):capacity(_capacity){
        minfreq = 0;
        freq_table.clear();
        key_table.clear();
    }

    int get(int key){
        if(capacity == 0) return -1;
        auto it = key_table.find(key);
        if( it == key_table.end() ) return -1;
        list<Node>::iterator node = it->second;
        int val = node->val, freq = node->freq;
        //从之前的频率链表中删除
        freq_table[freq].erase(node);
        if( freq_table[freq].size() == 0 ){
            freq_table.erase(freq);
            if(minfreq == freq){
                minfreq += 1;
            }
        }
        //插入到freq+1链表中
        freq_table[freq+1].push_front(Node(key,val,freq+1));
        key_table[key] = freq_table[freq+1].begin();
        return val;
    }

    void put(int key, int value){
        if(capacity == 0) return;
        auto it = key_table.find(key);
        if( it == key_table.end() ){
            //如果不存在，需要创建新
            //创建之前先判断是否已到达容量上限
            if(key_table.size() == capacity){
                //淘汰使用频率最低链表中队尾
                auto out = freq_table[minfreq].back();
                key_table.erase(out.key);
                freq_table[minfreq].pop_back();
                if( freq_table[minfreq].size() ==0 ){
                    freq_table.erase(minfreq);
                }
            }
            //新创建数据，插入freq=1的链表
            freq_table[1].push_front(Node(key,value,1));
            key_table[key] = freq_table[1].begin();
            minfreq = 1;
        }else{
            //存在的话和get几乎一样，只是需要更新val
            list<Node>::iterator node = it->second;
            int freq = node->freq;
            //从之前的频率链表中删除
            freq_table[freq].erase(node);
            if( freq_table[freq].size() == 0 ){
                freq_table.erase(freq);
                if(minfreq == freq){
                    minfreq += 1;
                }
            }
            //插入到freq+1链表中
            freq_table[freq+1].push_front(Node(key,value,freq+1));
            key_table[key] = freq_table[freq+1].begin();
        }
    }
};