#include "10_1951220_伊啸.h"
#include <ctime>
#include <iostream>

using namespace std;

int quick_counter = 0; //快速排序计数器
int heap_counter = 0; //堆排序计数器
int merge_counter = 0; //归并排序计数器
int main()
{
    test();
    system("pause");
    return 0;
}

void test()
{
    cout << "**                 排序算法比较                   **" << endl;
    cout << "====================================================" << endl;
    cout << "**                 1 --- 冒泡排序                 **" << endl;
    cout << "**                 2 --- 选择排序                 **" << endl;
    cout << "**                 3 --- 直接插入排序             **" << endl;
    cout << "**                 4 --- 希尔排序                 **" << endl;
    cout << "**                 5 --- 快速排序                 **" << endl;
    cout << "**                 6 --- 堆排序                   **" << endl;
    cout << "**                 7 --- 归并排序                 **" << endl;
    cout << "**                 8 --- 基数排序                 **" << endl;
    cout << "**                 9 --- 退出程序                 **" << endl;
    cout << "====================================================" << endl;
    cout << endl;
    cout << "请输入要产生随机数的个数：";
    int numbers, option;
    while (1) {
        cin >> numbers;
        if (cin.good() == false || numbers <= 0) {
            cout << "输入错误!请重新输入随机数个数：";
            while (getchar() != '\n')
                ;
            cin.clear();
        }
        else {
            break;
        }
    }
    datalist DataList(numbers);
    while (1) {
        srand((unsigned int)time(NULL));
        for (int i = 0; i < numbers; i++) {
            DataList.operator[](i) = rand() % numbers; //随机生成numbers个数
        }
        clock_t start, stop;
        double duration;
        cout << "请选择排序算法：";
        cin >> option;
        switch (option) {
        case 1:
            start = clock();
            DataList.BubbleSort();
            stop = clock();
            duration = ((double)(stop - start)) / CLK_TCK;
            cout << "冒泡排序所需时间：" << duration << endl;
            break;
        case 2:
            start = clock();
            DataList.SeletionSort();
            stop = clock();
            duration = ((double)(stop - start)) / CLK_TCK;
            cout << "选择排序所需时间：" << duration << endl;
            break;
        case 3:
            start = clock();
            DataList.InsertSort();
            stop = clock();
            duration = ((double)(stop - start)) / CLK_TCK;
            cout << "直接插入排序所需时间：" << duration << endl;
            break;
        case 4:
            start = clock();
            DataList.ShellSort();
            stop = clock();
            duration = ((double)(stop - start)) / CLK_TCK;
            cout << "希尔插入排序所需时间：" << duration << endl;
            break;
        case 5:
            start = clock();
            DataList.QuickSort(0, numbers - 1);
            stop = clock();
            duration = ((double)(stop - start)) / CLK_TCK;
            cout << "快速排序比较次数：" << quick_counter << endl;
            cout << "快速排序所需时间：" << duration << endl;
            break;
        case 6: {
            MaxHeap Heap(numbers);
            for (int i = 0; i < numbers; i++) {
                Heap.operator[](i) = rand() % numbers;
            }
            start = clock();
            Heap.HeapSort();
            stop = clock();
            duration = ((double)(stop - start)) / CLK_TCK;
            cout << "堆排序比较次数：" << heap_counter << endl;
            cout << "堆排序所需时间：" << duration << endl;
            break;
        }
        case 7:
            start = clock();
            DataList.MergeSort(0, numbers - 1);
            stop = clock();
            duration = ((double)(stop - start)) / CLK_TCK;
            cout << "归并排序比较次数：" << merge_counter << endl;
            cout << "归并排序所需时间：" << duration << endl;
            break;
        case 8: {
            start = clock();
            DataList.RadixSort();
            stop = clock();
            duration = ((double)(stop - start)) / CLK_TCK;
            cout << "基数排序比较次数：" << 0 << endl;
            cout << "基数排序所需时间：" << duration << endl;
            break;
        }
        case 9:
            return;
        default:
            cout << "输入选项错误！请输入1-9中的一个数字，选择排序算法：";
            break;
        }
    }
}
datalist::datalist(int maxSize)
    : maxsize(maxSize)
{
    arr = new int[maxSize];
    if (arr == NULL) {
        cerr << "内存分配失败!" << endl;
        exit(1);
    }
}
int datalist::Partition(const int low, const int high)
{
    int pivotpos = low;
    int pivot = arr[low];
    for (int i = low + 1; i <= high; i++) {
        if (++quick_counter && arr[i] < pivot) {
            pivotpos++;
            if (pivotpos != i) {
                Swap(arr[i], arr[pivotpos]); //交换下标为i和pivotpos的元素
            }
        }
    }
    arr[low] = arr[pivotpos];
    arr[pivotpos] = pivot; ////交换下标为low和pivotpos的元素
    return pivotpos;
}
void datalist::Merge(int left, int mid, int right)
{ //合并两组有序元素，一组下标从left到mid，另一组下标从mid+1到right
    int* assist_arr = new int[right + 1]; //辅助数组
    for (int i = 0; i <= right; i++)
        assist_arr[i] = 0; //初始化辅助数组
    for (int i = left; i <= right; i++)
        assist_arr[i] = arr[i];
    int t = left;
    int s1 = left;
    int s2 = mid + 1;
    while (s1 <= mid && s2 <= right) {
        if (++merge_counter && s1 < right && assist_arr[s1] > assist_arr[s2])
            arr[t++] = assist_arr[s2++];
        else if (s1 < right)
            arr[t++] = assist_arr[s1++];
    }
    while (s1 <= mid) //将多余的数组元素并入新数组
        arr[t++] = assist_arr[s1++];
    while (s2 <= right)
        arr[t++] = assist_arr[s2++];
    delete[] assist_arr;
    return;
}
void datalist::BubbleSort()
{ //冒泡排序
    long long count = 0;
    bool exchange;
    for (int i = 1; i < maxsize; i++) {
        exchange = false;
        for (int j = maxsize - 1; j >= i; j--) {
            if (++count && arr[j - 1] > arr[j]) {
                Swap(arr[j - 1], arr[j]);
                exchange = true;
            }
        }
        if (exchange == false) { //冒泡排序的优化，如果有一次循环未交换元素，则直接结束函数
            cout << "冒泡排序比较次数：" << count << endl;
            return;
        }
    }
    cout << "冒泡排序比较次数：" << count << endl;
    return;
}
void datalist::SeletionSort()
{ //选择排序
    long long count = 0;
    for (int i = 0; i < maxsize - 1; i++) {
        int min = arr[i];
        for (int j = i + 1; j < maxsize; j++) {
            if (++count && arr[j] < min) {
                Swap(arr[j], min);
            }
        }
    }
    cout << "选择排序比较次数：" << count << endl;
    return;
}
void datalist::InsertSort()
{ //插入排序
    long long count = 0;
    for (int i = 1; i < maxsize; i++) {
        int temp = arr[i];
        int j = i - 1;
        if (arr[i] < arr[j]) {
            do {
                arr[j + 1] = arr[j];
                j--;
            } while (j >= 0 && ++count && temp < arr[j]);
            arr[j + 1] = temp;
        }
    }
    cout << "直接插入排序比较次数：" << count << endl;
    return;
}
void datalist::ShellSort()
{ //希尔排序
    int gap = maxsize, count = 0;
    do {
        gap = gap / 3 + 1;
        for (int i = gap; i < maxsize; i++) {
            int temp = arr[i];
            int j = i - gap;
            if (arr[i] < arr[j]) {
                do {
                    arr[j + gap] = arr[j];
                    j -= gap;
                } while (j >= 0 && ++count && temp < arr[j]);
                arr[j + gap] = temp;
            }
        }
    } while (gap > 1);
    cout << "希尔插入排序比较次数：" << count << endl;
}
void datalist::QuickSort(const int left, const int right)
{ //快速排序
    if (left < right) {
        int pivotpos = Partition(left, right);
        QuickSort(left, pivotpos - 1);
        QuickSort(pivotpos + 1, right);
    }
    return;
}
void datalist::MergeSort(const int left, const int right)
{ //归并排序
    if (left >= right)
        return;
    int mid = (left + right) / 2;
    MergeSort(left, mid);
    MergeSort(mid + 1, right);
    Merge(left, mid, right);
    return;
}

MaxHeap::MaxHeap(int sz)
    : maxHeapSize(sz)
{
    heap = new int[sz];
    if (heap == NULL) {
        cerr << "堆内存分配失败！" << endl;
        exit(1);
    }
}
void MaxHeap::siftDown(const int start, const int m)
{ //调整成为最大堆
    int i = start;
    int j = 2 * i + 1;
    int temp = heap[i];
    while (j <= m) {
        if (j < m && ++heap_counter && heap[j] < heap[j + 1])
            j++;
        if (++heap_counter && temp < heap[j]) {
            heap[i] = heap[j];
            i = j;
            j = j * 2 + 1;
        }
        else
            break;
    }
    heap[i] = temp;
    return;
}
void MaxHeap::HeapSort()
{
    for (int i = (maxHeapSize - 2) / 2; i >= 0; i--)
        siftDown(i, maxHeapSize - 1);
    for (int i = maxHeapSize - 1; i >= 0; i--) {
        Swap(0, i); //交换堆顶和堆中最后一个元素
        siftDown(0, i - 1);
    }
}
void datalist::RadixSort()
{
    int* arrTemp = new int[maxsize];
    int iMax = arr[0];
    for (int i = 1; i < maxsize; i++) //找出最大值
    {
        if (arr[i] > iMax)
            iMax = arr[i];
    }
    int iDigitsNumber = 0; //求位数
    do {
        iMax /= radix;
        iDigitsNumber++;
    } while (iMax != 0);

    int iRadix = 1, iKey;
    int arrCount[radix];
    for (int i = 0; i < iDigitsNumber; i++) {
        for (int j = 0; j < radix; j++)
            arrCount[j] = 0; //初始化记录器
        for (int j = 0; j < maxsize; j++) {
            iKey = arr[j] / iRadix % radix; //记录每个键出现的次数
            arrCount[iKey]++;
        }
        for (int j = 1; j < radix; j++)
            arrCount[j] += arrCount[j - 1]; //把次数转化为位置 有1偏移
        for (int j = maxsize - 1; j >= 0; j--) //按键的顺序存入临时数组
        {
            iKey = arr[j] / iRadix % radix; //arrCount中存的是对应键的排序位置+1
            arrTemp[--arrCount[iKey]] = arr[j]; //因为有1偏移，所以要减一
        }
        for (int j = 0; j < maxsize; j++)
            arr[j] = arrTemp[j];
        iRadix *= radix;
    }
    delete[] arrTemp;
    return;
}