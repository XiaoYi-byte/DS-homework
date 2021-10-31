#pragma once
#ifndef SORT_H_
#define SORT_H_

const int DefaultSize = 100;
const int radix = 10;
void test();

class datalist {
private:
	int* arr;
	int maxsize;
public:
	datalist(int maxSize = DefaultSize);//构造函数
	~datalist() { delete[]arr; }//析构函数
	void Swap(int& x, int& y) {//交换函数
		int temp = x;
		x = y;
		y = temp;
	}
	int& operator[](int i) {//获取数组中元素
		return arr[i];
	}
	int Partition(const int low, const int high);//快速排序调用的划分函数
	void Merge(int left, int mid, int right);//归并两个有序表
	void BubbleSort();//冒泡排序
	void SeletionSort();//选择排序
	void InsertSort();//插入排序
	void ShellSort();//希尔排序
	void QuickSort(const int left, const int right);//快速排序
	void MergeSort(const int left, const int right);//归并排序
	void RadixSort();//基数排序
};

class MaxHeap {
private:
	int* heap;
	int maxHeapSize;
	void siftDown(const int start, const int m);//调整成为最大堆
	void Swap(const int& i, const int& j) {//堆中元素交换函数
		int temp = heap[i];
		heap[i] = heap[j];
		heap[j] = temp;
	}
public:
	MaxHeap(int size = DefaultSize);//构造函数
	~MaxHeap() { delete[]heap; }//析构函数
	int& operator[](int i) {//取堆中元素
		return heap[i];
	}
	void HeapSort();//堆排序
};
#endif // !SORT_H_
#pragma once
