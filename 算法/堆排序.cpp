#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;


//将数组arr下表为i的元素进行调整，使得满足大顶堆
void heapfy(vector<int>& arr, int len, int i){
    int largest = i;
    int lson = i*2+1;
    int rson = i*2+2;
    if(lson < len && arr[largest] < arr[lson]){
        largest = lson;
    }
    if(rson < len && arr[largest] < arr[rson]){
        largest = rson;
    }
    if(largest != i){
        swap(arr[largest],arr[i]);
        heapfy(arr,len,largest);
    }
}

//堆排序函数，传入要排序的数组以及其长度
void heap_sort(vector<int>& arr, int len) {
    //初始化，i从最后一个父节点开始调整，建立堆
    for (int i = len / 2 - 1; i >= 0; i--)
        heapfy(arr, len, i);

    //先将第一个元素和已经排好的元素前一位做交换，再从新调整(刚调整的元素之前的元素)，直到排序完毕
    for (int i = len - 1; i > 0; i--) {
        swap(arr[0], arr[i]);
        heapfy(arr, i, 0);
    }
}

int main() {
    vector<int> arr = { 3, 5, 3, 0, 8, 6, 1, 5, 8, 6, 2, 4, 9, 4, 7, 0, 1, 8, 9, 7, 3, 1, 2, 5, 9, 7, 4, 0, 2, 6 };
    int len = arr.size();
    heap_sort(arr, len);
    for (int i = 0; i < len; i++)
        cout << arr[i] << ' ';
    cout << endl;
    return 0;
}