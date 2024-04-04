// MIT License
//
// Copyright (c) 2024 Loong email:1031313955@qq.com
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#include <map>
#include <vector>
#include <iostream>
#include "avl_tree.h"
#include "avl_tree_view.h"
#include "avl_tree_test.h"

#define TREE_KEY_TYPE int
struct TestData {
    std::vector<TREE_KEY_TYPE> inputs;
    std::vector<TREE_KEY_TYPE> pre_order;
    std::vector<TREE_KEY_TYPE> in_order;
    std::vector<TREE_KEY_TYPE> post_orfer;
    std::vector<TREE_KEY_TYPE> del_keys;
    std::vector<TREE_KEY_TYPE> del_ret_pre_order;
    std::vector<TREE_KEY_TYPE> del_ret_in_order;
    std::vector<TREE_KEY_TYPE> del_ret_post_orfer;
};

typedef std::vector<TestData> TestDataVec;

TestDataVec kTestDatas = {
    {
        {10, 20, 30},
        {20, 10, 30},
        {10, 20, 30},
        {10, 30, 20},
    },
    {
        {10, 5, 15, 3, 7, 12, 18},
        {10, 5, 3, 7, 15, 12, 18},
        {3, 5, 7, 10, 12, 15, 18},
        {3, 7, 5, 12, 18, 15, 10},
        {3, 7},
        {10, 5, 15, 12, 18},
        {5, 10, 12, 15, 18},
        {5, 12, 18, 15, 10},
    }
};

bool CheckVectorsEqual(const std::vector<TREE_KEY_TYPE>& v1, const std::vector<TREE_KEY_TYPE>& v2) {
    if (v1.size() != v2.size()) {
        return false;
    }

    for (size_t i = 0; i < v1.size(); ++i) {
        if (v1.at(i) != v2.at(i)) {
            return false;
        }
    }

    return true;
}

bool CheckOne(const TestData& data) {
    avl::Tree<TREE_KEY_TYPE> tree;
    avl::TreeView<avl::Tree<TREE_KEY_TYPE> > tree_view(tree);
    for (auto val : data.inputs) {
        tree.Insert(val);
        if (!tree_view.CheckBalance()) {
            return false;
        }

        if (!tree.IsExist(val)) {
            return false;
        }
    }

    if (!tree_view.CheckBalance()) {
        return false;
    }

    std::vector<TREE_KEY_TYPE> result;
    tree_view.PrintInOrder(result);
    if (!CheckVectorsEqual(result, data.in_order))
    {
        return false;
    }

    result.clear();
    tree_view.PrintPreOrder(result);
    if (!CheckVectorsEqual(result, data.pre_order))
    {
        return false;
    }

    result.clear();
    tree_view.PrintPostOrder(result);
    if (!CheckVectorsEqual(result, data.post_orfer))
    {
        return false;
    }

    if (data.del_keys.empty()) {
        return true;
    }

    for (auto val : data.del_keys) {
        tree.Erase(val);
        if (!tree_view.CheckBalance()) {
            return false;
        }

        if (tree.IsExist(val)) {
            return false;
        }
    }

    if (!tree_view.CheckBalance()) {
        return false;
    }

    result.clear();
    tree_view.PrintInOrder(result);
    if (!CheckVectorsEqual(result, data.del_ret_in_order))
    {
        return false;
    }

    result.clear();
    tree_view.PrintPreOrder(result);
    if (!CheckVectorsEqual(result, data.del_ret_pre_order))
    {
        return false;
    }

    result.clear();
    tree_view.PrintPostOrder(result);
    if (!CheckVectorsEqual(result, data.del_ret_post_orfer))
    {
        return false;
    }

    return true;
}

std::vector<int> kTestRand = {1, 3, 5, 10, 15, 50, 100, 200, 500, 1000, 1234};
bool RandCheck(int num) {
    if (num <= 0) return true;

    avl::Tree<TREE_KEY_TYPE> tree;
    avl::TreeView<avl::Tree<TREE_KEY_TYPE> > tree_view(tree);
    for (int i = 0; i < num; ++i) {
        tree.Insert(rand());
        if (!tree_view.CheckBalance()) {
            return false;
        }
    }

    std::vector<TREE_KEY_TYPE> result;
    tree_view.PrintInOrder(result);
    for (size_t i = 1; i < result.size(); ++i) {
        int v1 = result.at(i - 1);
        int v2 = result.at(i);
        if (v1 >= v2) {
            return false;
        }
    }

    return true;
}

int Test() {
    int cout = 0;
    for (auto& data : kTestDatas) {
        std::cout << "test data" << ++cout << ": ";
        if (!CheckOne(data)) {
            std::cout << "fail." << std::endl;
            return -1;
        }
        std::cout << "succ." << std::endl;
    }

    for (auto& num : kTestRand) {
        std::cout << "rand test num=" << num << ": ";
        if (!RandCheck(num)) {
            std::cout << "fail." << std::endl;
            return -1;
        }
        std::cout << "succ." << std::endl;
    }

    std::cout << "all test pass~~~" << std::endl;

    return 0;
}