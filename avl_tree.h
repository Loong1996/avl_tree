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

#ifndef AVL_TREE_H_
#define AVL_TREE_H_

#include <algorithm>

namespace avl {

template<class TKey, class TComp = std::less<TKey> >
class Tree {
public:
    typedef TKey KeyType;
    struct Node {
        TKey  key;
        Node* left;
        Node* right;
        int   height;
        Node(const TKey& _key) : key(_key), left(nullptr), right(nullptr), height(1) { 
        }
    };

private:
    TComp key_comp_;
    Node* root_;

public:
    Tree() : root_(nullptr) { }

    const Node* Root() const { return root_; }

    void Insert(const TKey& key) {
        root_ = this->InsertUtil(root_, key);
    }

    void Erase(const TKey& key) {
        root_ = this->RemoveUtil(root_, key);
    }

    const Node* Find(const TKey& key) {
        return this->FindUtil(root_, key);
    }

    bool IsExist(const TKey& key) {
        return (nullptr != this->Find(key));
    }

private:
    // get tree height
    int GetHeight(Node* head) {
        return (nullptr == head)? 0 : head->height;
    }

    //       X(head)                Y(new_head)
    //      / \                    / \
    //     Y   C       ----->     A   X
    //    / \                        / \
    //   A   B                      B   C
    Node* RightRotation(Node* head) {
        Node* new_head = head->left;
        head->left = new_head->right;
        new_head->right = head;
        head->height = 1 + std::max(this->GetHeight(head->left), this->GetHeight(head->right));
        new_head->height = 1 + std::max(this->GetHeight(new_head->left), this->GetHeight(new_head->right));
        return new_head;
    }

    //       X(head)                 C(new_head)
    //      / \                     / \
    //     Y   C       ----->      X   B
    //        / \                 / \
    //       A   B               Y   A
    Node* LeftRotation(Node* head) {
        Node* new_head = head->right;
        head->right = new_head->left;
        new_head->left = head;
        head->height = 1 + std::max(this->GetHeight(head->left), this->GetHeight(head->right));
        new_head->height = 1 + std::max(this->GetHeight(new_head->left), this->GetHeight(new_head->right));
        return new_head;
    }

    Node* Rotation(Node* head) {
        if (nullptr == head) {
            return nullptr;
        }

        int bf = this->GetHeight(head->left) - this->GetHeight(head->right);
        if (bf > 1) {
            Node* child = head->left;
            if (this->GetHeight(child->left) > this->GetHeight(child->right)) {
                // Left-Left imbalance
                return this->RightRotation(head);
            } else {
                // Left-Right imbalance
                head->left = this->LeftRotation(head->left);
                return this->RightRotation(head);
            }
        } else if (bf < -1) {
            Node* child = head->right;
            if (this->GetHeight(child->right) > this->GetHeight(child->left)) {
                // Right-Right imbalance
                return this->LeftRotation(head);
            } else {
                // Right-Left imbalance
                head->right = this->RightRotation(head->right);
                return this->LeftRotation(head);
            }
        }

        return head;
    }

    const Node* FindUtil(Node* head, const TKey& key) {
        if (nullptr == head) {
            return nullptr;
        }

        if (key_comp_(key, head->key)) {
            return this->FindUtil(head->left, key);
        } else if (key_comp_(head->key, key)) {
            return this->FindUtil(head->right, key);
        }

        return head;
    }

    Node* InsertUtil(Node* head, const TKey& key) {
        if (nullptr == head) {
            return new Node(key);
        }

        if (key_comp_(key, head->key)) {
            head->left = this->InsertUtil(head->left, key);
        } else if (key_comp_(head->key, key)) {
            head->right = this->InsertUtil(head->right, key);
        } else {
            // Return the head directly when encountering duplicate keys
            return head;
        }

        head->height = 1 + std::max(this->GetHeight(head->left), this->GetHeight(head->right));
        return this->Rotation(head);
    }

    Node* RemoveUtil(Node* head, const TKey& key) {
        if (nullptr == head) {
            return nullptr;
        }

        if (key_comp_(key, head->key)) {
            head->left = this->RemoveUtil(head->left, key);
        } else if (key_comp_(head->key, key)) {
            head->right = this->RemoveUtil(head->right, key);
        } else {
            if (head->right == nullptr) {
                Node* left = head->left;
                delete head;
                head = left;
            } else if (head->left == nullptr) {
                Node* right = head->right;
                delete head;
                head = right;
            } else {
                Node* successor = head->right;
                while (successor->left != nullptr) successor = successor->left;
                head->key = successor->key;
                head->right = this->RemoveUtil(head->right, head->key);
            }
        }

        if (head == nullptr) {
            return nullptr;
        }

        head->height = 1 + std::max(this->GetHeight(head->left), this->GetHeight(head->right));
        return this->Rotation(head);
    }
};

} // end namespace avl

#endif // AVL_TREE_H_