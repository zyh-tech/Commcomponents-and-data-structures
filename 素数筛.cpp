#include<iostream>
#include<vector>

using namespace std;

int main(){

    //素数筛子提前求出所有1e6内的数字的最大质数因子
    int maxn = 1e6+1;
    vector<bool> vis(maxn,false);
    vector<int> prime(maxn,1);
    for(int i=2; i<=maxn; ++i){
        if(vis[i]) continue;
        prime[i] = i;
        for(int j=i+i; j<=maxn; j+=i){
            vis[j] = true;
            prime[j] = i;
        }
    }

    return 0;
    
}