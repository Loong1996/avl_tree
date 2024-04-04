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

#ifndef AVL_TREE_VIEW_H_
#define AVL_TREE_VIEW_H_

#include "avl_tree.h"
#include <assert.h>
#include <vector>

namespace avl {

template<class T>
class TreeView {
private:
    T& tree_;

public:
    TreeView(T& tree) : tree_(tree) {}

    void PrintPreOrder(std::vector<typename T::KeyType>& out) { this->PreOrderTraversal(tree_.Root(), out); }
    void PrintInOrder(std::vector<typename T::KeyType>& out) { this->InOrderTraversal(tree_.Root(), out); }
    void PrintPostOrder(std::vector<typename T::KeyType>& out) { this->PostOrderTraversal(tree_.Root(), out); }

    void PreOrderTraversal(const typename T::Node* node, std::vector<typename T::KeyType>& out) {
        if (nullptr == node) return;
        out.push_back(node->key);
        PreOrderTraversal(node->left, out);
        PreOrderTraversal(node->right, out);
    }

    void InOrderTraversal(const typename T::Node* node, std::vector<typename T::KeyType>& out) {
        if (nullptr == node) return;
        InOrderTraversal(node->left, out);
        out.push_back(node->key);
        InOrderTraversal(node->right, out);
    }

    void PostOrderTraversal(const typename T::Node* node, std::vector<typename T::KeyType>& out) {
        if (nullptr == node) return;
        PostOrderTraversal(node->left, out);
        PostOrderTraversal(node->right, out);
        out.push_back(node->key);
    }

    int GetRealHeight(const typename T::Node* node) {
        if (nullptr == node) return 0;
        int left_height = this->GetRealHeight(node->left) + 1;
        int right_height = this->GetRealHeight(node->right) + 1;
        int height = left_height > right_height ? left_height : right_height;
        assert(node->height == height);
        return height;
    }

    bool CheckBalance(const typename T::Node* node) {
        if (nullptr == node) return true;
        int bf = this->GetRealHeight(node->left) - this->GetRealHeight(node->right);
        if ((bf > 1) || (bf < -1)) {
            return false;
        }

        return this->CheckBalance(node->left) && this->CheckBalance(node->right);
    }

    bool CheckBalance() {
        return this->CheckBalance(tree_.Root());
    }
};

} // end namespace avl

#endif // AVL_TREE_VIEW_H_