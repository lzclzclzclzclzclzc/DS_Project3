#include <iostream>
#include <vector>
#include <chrono>
#include <cmath>

using namespace std;
using namespace chrono;

// 顺序查找
int sequentialSearch(const vector<int>& data, int key, int& count) {
    for (int i = 0; i < data.size(); ++i) {
        ++count;
        if (data[i] == key)
            return i;
    }
    return -1;
}

// 折半查找（二分查找）
int binarySearch(const vector<int>& data, int key, int& count) {
    int left = 0, right = data.size() - 1;
    while (left <= right) {
        ++count;
        int mid = left + (right - left) / 2;
        if (data[mid] == key)
            return mid;
        else if (data[mid] < key)
            left = mid + 1;
        else
            right = mid - 1;
    }
    return -1;
}

// 斐波那契查找
int fibonacciSearch(const vector<int>& data, int key, int& count) {
    int n = data.size();
    int fibMm2 = 0;
    int fibMm1 = 1;
    int fibM = fibMm1 + fibMm2;

    while (fibM < n) {
        fibMm2 = fibMm1;
        fibMm1 = fibM;
        fibM = fibMm1 + fibMm2;
    }

    int offset = -1;

    while (fibM > 1) {
        ++count;
        int i = min(offset + fibMm2, n - 1);
        if (data[i] < key) {
            fibM = fibMm1;
            fibMm1 = fibMm2;
            fibMm2 = fibM - fibMm1;
            offset = i;
        } else if (data[i] > key) {
            fibM = fibMm2;
            fibMm1 = fibMm1 - fibMm2;
            fibMm2 = fibM - fibMm1;
        } else {
            return i;
        }
    }

    if (fibMm1 && offset + 1 < n && data[offset + 1] == key) {
        ++count;
        return offset + 1;
    }

    return -1;
}

// 生成有序数据
vector<int> generateOrderedData(int size) {
    vector<int> data(size);
    for (int i = 0; i < size; ++i)
        data[i] = i * 2; // 保证不重复
    return data;
}

// 测试函数
void testSearchAlgorithms(int size) {
    vector<int> data = generateOrderedData(size);

    long long seqCount = 0, binCount = 0, fibCount = 0;
    auto seqStart = high_resolution_clock::now();
    for (int key : data) {
        int count = 0;
        sequentialSearch(data, key, count);
        seqCount += count;
    }
    auto seqEnd = high_resolution_clock::now();

    auto binStart = high_resolution_clock::now();
    for (int key : data) {
        int count = 0;
        binarySearch(data, key, count);
        binCount += count;
    }
    auto binEnd = high_resolution_clock::now();

    auto fibStart = high_resolution_clock::now();
    for (int key : data) {
        int count = 0;
        fibonacciSearch(data, key, count);
        fibCount += count;
    }
    auto fibEnd = high_resolution_clock::now();

    auto seqTime = duration_cast<milliseconds>(seqEnd - seqStart).count();
    auto binTime = duration_cast<milliseconds>(binEnd - binStart).count();
    auto fibTime = duration_cast<milliseconds>(fibEnd - fibStart).count();

    cout << "\nData Size: " << size << endl;
    cout << "Sequential Search: Total comparisons = " << seqCount << ", Time = " << seqTime << " ms" << endl;
    cout << "Binary Search: Total comparisons = " << binCount << ", Time = " << binTime << " ms" << endl;
    cout << "Fibonacci Search: Total comparisons = " << fibCount << ", Time = " << fibTime << " ms" << endl;

}

int main() {
    vector<int> sizes = {4, 40, 400, 4000, 40000, 400000, 4000000, 40000000};

    for (int size : sizes) {
        testSearchAlgorithms(size);
    }

    return 0;
}
