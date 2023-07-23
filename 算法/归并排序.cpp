/*
归并排序

1.问题分析
    归并排序是比较稳定的排序方法。它的基本思想是把待排序的元素分解成两个规模大致相等的子序列。如果不易分解，将得到的子序列继续分解，直到子序列中包含的元素个数为1。因为单个元素的序列本身就是有序的，此时便可以进行合并，从而得到一个完整的有序序列。
2.算法设计
    （1）分解：
    将待排序的元素分成大小大致一样的两个子序列。
    （2）治理：
    对两个子序列进行个并排序。
    （3）合并：
    将排好序的有序子序列进行合并，得到最终的有序序列。

步骤一：首先将待排序的元素分成大小大致相同的两个序列。

步骤二：再把子序列分成大小大致相同的两个子序列。

步骤三：如此下去，直到分解成一个元素停止，这时含有一个元素的子序列都是有序的。

步骤四：进行合并操作，将两个有序的子序列合并为一个有序序列，如此下去，直到所有的元素都合并为一个有序序列。

*/



#include<vector>
#include<iostream>
using namespace std;

void merge_sort_recursive(vector<int>& arr, vector<int>& reg, int start, int end) {
    if (start >= end)   return;
        
    int len = end - start, mid = (len >> 1) + start;
    int start1 = start, end1 = mid;
    int start2 = mid + 1, end2 = end;
    merge_sort_recursive(arr, reg, start1, end1);
    merge_sort_recursive(arr, reg, start2, end2);
    int k = start;
    while (start1 <= end1 && start2 <= end2)
        reg[k++] = arr[start1] < arr[start2] ? arr[start1++] : arr[start2++];
    while (start1 <= end1)
        reg[k++] = arr[start1++];
    while (start2 <= end2)
        reg[k++] = arr[start2++];
    for (k = start; k <= end; k++)
        arr[k] = reg[k];
}

void merge_sort(vector<int>& arr,int low, int high) {
    int len = high-low+1;
    vector<int> reg(len);
    merge_sort_recursive(arr, reg, 0, len-1);
}


int main(){
    //vector<int> a = {12,4,7,8,234,6,1,-2,9,4,7};
    vector<int> a = {1,4,2,57,-34,2 };
    merge_sort(a,0,a.size()-1);

    for(int& temp:a) cout << temp << endl;

    return 0;
}
