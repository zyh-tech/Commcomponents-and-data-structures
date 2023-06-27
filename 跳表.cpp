#include<iostream>
#include<vector>
#include<random>

using namespace std;

constexpr int MAX_LEVEL = 32;    //跳表的最大层数

//生成下一层索引的概率，该参数决定了跳表中上一层相对于下一层的数据量大小
constexpr double P_FACTOR = 0.25;   

class SkiplistNode{
public:
    int val;
    vector<SkiplistNode*> forward;
    SkiplistNode(int _val,int _maxLevel = MAX_LEVEL):
    val(_val),forward(_maxLevel,nullptr){};
};

class Skiplist{
private:
    SkiplistNode* head;             //跳表的头节点
    int level;                      //跳表的最大层数
    mt19937 gen{random_device{}()}; //使用random_device{}随即种子产生mt19937随机数
    uniform_real_distribution<double> dis;      //均匀分布
public:
    Skiplist():head(new SkiplistNode(-1)),level(0),dis(0,1){};

    int randomLevel(){
        int lv = 1;
        while(dis(gen) < P_FACTOR && lv < MAX_LEVEL){
            lv++;
        }
        return lv;
    }

    bool search(int target){
        SkiplistNode* cur = this->head;
        for(int i=level-1; i>=0; i--){
            while(cur->forward[i] && cur->forward[i]->val < target){
                cur = cur->forward[i];
            }
        }
        cur = cur->forward[0];
        if(cur && cur->val == target) return true;
        else return false;
    }

    void add(int num){
        vector<SkiplistNode*> update(MAX_LEVEL,head);
        SkiplistNode* cur = this->head;
        for(int i=level-1; i>=0; i--){
            while(cur->forward[i] && cur->forward[i]->val < num){
                cur = cur->forward[i];
            }
            update[i] = cur;
        }

        int lv = randomLevel();
        level = max(level,lv);
        SkiplistNode* newNode = new SkiplistNode(num,lv);

        for(int i=0; i<lv; i++){
            newNode->forward[i] = update[i]->forward[i];
            update[i]->forward[i] = newNode;
        }
    }

    bool erase(int num){
        vector<SkiplistNode*> update(MAX_LEVEL,nullptr);
        SkiplistNode* cur = this->head;
        for(int i=level-1; i>=0; i--){
            while(cur->forward[i] && cur->forward[i]->val < num){
                cur = cur->forward[i];
            }
            update[i] = cur;
        }
        cur = cur->forward[0];
        if(cur == nullptr || cur->val != num) return false;

        for(int i=0; i<level; i++){
            if(update[i]->forward[i] != cur) break;
            update[i]->forward[i] = cur->forward[i];
        }
        delete cur;
        //删除完成后要更新树的层数
        while(level > 1 && head->forward[level-1] == nullptr){
            level--;
        }
        return true;
    }
};

int main(){
    Skiplist* skiplist =new Skiplist();
    skiplist->add(1);
    skiplist->add(2);
    skiplist->add(3);
    cout << skiplist->search(0) << endl;   // 返回 false
    
    skiplist->add(4);
    skiplist->search(1);   // 返回 true
     cout << skiplist->search(1) << endl;;

    skiplist->erase(0);    // 返回 false，0 不在跳表中
    skiplist->erase(1);    // 返回 true

    skiplist->search(1);   // 返回 false，1 
     cout << skiplist->search(1) << endl;;

    return 0;
}



/*
constexpr int MAX_LEVEL = 32;   //跳表的最大层数
constexpr double P_FACTOR = 0.25;    //生成每一层索引的概率

class SkiplistNode{
public:
    int val;
    vector<SkiplistNode*> forward;    //节点中存放值和一组next指针
    SkiplistNode(int _val,int _maxLevel = MAX_LEVEL):val(_val),forward(_maxLevel,nullptr){};
};

class Skiplist{
private:
    SkiplistNode* head;        //跳表的头节点
    int level;                 //跳表的最大层数
    mt19937 gen{random_device{}()};   //使用random_device{}随即种子产生mt19937随机数
    uniform_real_distribution<double> dis;      //均匀分布

public:
    //头节点的值为-1，层数是最高层，Skiplist初始层数是0，
    Skiplist():head(new SkiplistNode(-1)),level(0),dis(0,1){};

    //该函数用于随机获取新插入的值的索引的层数
    int randomLevel(){
        int lv = 1;
        //dis(gen)将随机数gen均匀落在均匀分布（0，1）内
        while(dis(gen) < P_FACTOR && lv < MAX_LEVEL) lv++;
        return lv;
    }

    //跳表的查找
    bool search(int target){
        SkiplistNode* cur = this->head;
        //从高层到低层搜索，每一层都搜索到下一个节点的值大于等于目标值时停止
        for(int i=level-1; i>=0; i--){
            while(cur->forward[i] && cur->forward[i]->val < target){
                cur = cur->forward[i];
            }
        }
        //循环结束后cur应该是最底层的目标值的前一个位置
        cur = cur->forward[0];
        if(cur && cur->val == target) return true;
        else return false;
    }

    //跳表的插入
    void add(int num){
        //update记录的是查找插入位置的过程中每一层的最后一个搜索节点，
        //记录下来，因为插入的时候需要更新这些节点的指针
        vector<SkiplistNode*> update(MAX_LEVEL,head);
        SkiplistNode* cur = this->head;
        for(int i=level-1; i>=0; i--){
            while(cur->forward[i] && cur->forward[i]->val < num){
                cur = cur->forward[i];
            }
            update[i] = cur;
        }
        
        int lv = randomLevel();   //随即获取当前要插入的节点中指针的层数
        level = max(level,lv);    //更新当前跳表的最大层数
        SkiplistNode* newNode = new SkiplistNode(num,lv);

        //插入过程，需要维护0-lv-1层
        for(int i=0; i<lv; i++){
            newNode->forward[i] = update[i]->forward[i];
            update[i]->forward[i] = newNode;
        }
    }

    //删除跳表中某个元素
    bool erase(int num){
        vector<SkiplistNode*> update(MAX_LEVEL,nullptr);
        SkiplistNode* cur = this->head;
        for(int i=level-1; i>=0; i--){
            while(cur->forward[i] && cur->forward[i]->val < num){
                cur = cur->forward[i];
            }
            update[i] = cur;
        }
        cur = cur->forward[0];
        if(cur == nullptr || cur->val != num) return false;

        for(int i=0; i<level; i++){
            if(update[i]->forward[i] != cur) break;
            update[i]->forward[i] = cur->forward[i];
        }
        delete cur;
        //删除完成后要更新树的层数
        while(level > 1 && head->forward[level-1] == nullptr) level--;
        return true;
    }
};
*/