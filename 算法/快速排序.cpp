/*
算法设计
    （1）分解：

    先从数列中取出一个元素作为基准元素。一基准元素为标准，将问题分解为两个子序列，使小于或者等于基准元素的子序列在左侧，使大于基准元素的子序列在右侧。
    （2）治理 ：

    对两个子序列进行快速排序（递归快速排序）。
    （3）合并：

    将排好的两个子序列合并在一起，得到原问题的解。
    （4）基准元素的选取：

    ①：取第一个元素。(通常选取第一个元素)

    ②：取最后一个元素

    ③：取中间位置的元素

    ④：取第一个、最后一个、中间位置元素三者之中位数

    ⑤：取第一个和最后一个之间位置的随机数 k (low<=k<=hight)

     假设当前的待排序的序列为 R[low,hight] ， 其中 low<=hight。同时选取首元素为基准元素。

步骤一：选取首元素的第一个元素作为基准元素  pivot=R[low] ，i=low ，j=hight。

步骤二：从右向左扫描，找到小于等于 pivot 的数，如果找到，R[i] 和 R[j] 交换 ，i++。

步骤三：从左向右扫描，找到大于 pivot 的数，如果找到，R[i] 和 R[j] 交换，j--。

步骤四：重复 步骤二~步骤三，直到  j 与 i 的指针重合 返回位置 mid=i ，该位置的数正好是 pivot 元素。

*/


#include<vector>
#include<iostream>
using namespace std;

void quick_sort(vector<int>& a, int l, int r)
{
    if (l < r)
    {
        int i,j,x;

        i = l;
        j = r;
        x = a[i];
        while (i < j)
        {
            while(i < j && a[j] > x)
                j--; // 从右向左找第一个小于x的数
            if(i < j)
                swap(a[i++], a[j]);
            while(i < j && a[i] < x)
                i++; // 从左向右找第一个大于x的数
            if(i < j)
                swap(a[j--], a[i]);
        }
        //a[i] = x;
        quick_sort(a, l, i-1); /* 递归调用 */
        quick_sort(a, i+1, r); /* 递归调用 */
    }
}





void my_quick_sort(vector<int>& nums, int low, int high){

    if(low >= high) return;     //递归终点是数组长度为1

    int l,r,pivot;
    l = low;                    //左指针初始化为low
    r = high;                   //右指针初始化为high
    pivot = nums[l];            //区间左端点作为基准
    while(l < r){
        while(l < r && nums[r] > pivot){
            r--;                //从后向前找到第一个小于等于基准的位置
        }
        if(l < r) swap(nums[l++],nums[r]);
        while(l < r && nums[l] < pivot){
            l++;                //从前向后找到第一个大于等于基准的位置
        }
        if(l < r) swap(nums[l],nums[r--]);
    }
    my_quick_sort(nums,low,l-1);
    my_quick_sort(nums,l+1,high);
}


int main(){
    vector<int> a = {12,4,7,8,234,6,1,-2,9,4,7};
    my_quick_sort(a,0,a.size()-1);

    for(int& temp:a) cout << temp << endl;

    return 0;
}

