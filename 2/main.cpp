#include <iostream>
#include <vector>
#include <chrono>
#include <windows.h>
#include "Node.h"
#include "BST_Node_Deletion.h"
using namespace std;
using namespace std::chrono;

// 比较次数统计
int comparison_count = 0;



// 测试接口
void testDeletion(string method_name,
                  TreeNode* (*deleteFunc)(TreeNode*, int),
                  const vector<int>& insert_data,
                  const vector<int>& delete_data,
                  bool use_parent = false,
                  bool is_with_parent_method = false) {
    TreeNode* root = nullptr;
    for (int val : insert_data) root = insert(root, val, use_parent);

    comparison_count = 0;
    auto start = high_resolution_clock::now();

    if (is_with_parent_method) {
        for (int val : delete_data) {
            TreeNode* node = find(root, val);
            root = deleteWithParent(root, node);
        }
    } else {
        for (int val : delete_data) {
            root = deleteFunc(root, val);
        }
    }

    auto end = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(end - start).count();

    cout << method_name << ":\n";
    cout << "  比较次数: " << comparison_count << endl;
    cout << "  删除耗时: " << duration << " 微秒\n\n";
}

// 主函数
int main() {
    SetConsoleCP(CP_UTF8); // 输入
    SetConsoleOutputCP(CP_UTF8); // 输出
    vector<int> insert_data = {50, 30, 70, 20, 40, 60, 80, 100, 400, 200, 500, 600};
    vector<int> delete_data = {20, 30, 50, 500};

    testDeletion("1. 标准递归删除", deleteRecursive, insert_data, delete_data);
    testDeletion("2. 非递归删除", deleteIterative, insert_data, delete_data);
    testDeletion("3. Hibbard 删除法", deleteHibbard, insert_data, delete_data);
    testDeletion("4. 父指针辅助删除", nullptr, insert_data, delete_data, true, true);

    return 0;
}
