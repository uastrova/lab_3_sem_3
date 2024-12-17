//
// Created by User on 17.12.2024.
//

#ifndef LAB3_RBTREE_H
#define LAB3_RBTREE_H

#include <iostream>
#include <memory>
#include <string>
#include <functional>
#include <list>
#include <iomanip>

enum Color { RED, BLACK };

template <typename Key, typename Data>
struct Node {
    Key key;
    Color color;
    std::list<Data> dataList;
    Node* left;
    Node* right;
    Node* parent;

    Node(const Key& k, const Data& data)
            : key(k), color(RED), left(nullptr), right(nullptr), parent(nullptr) {
        dataList.push_back(data);
    }
};

template <typename Key, typename Data>
class RedBlackTree {
private:
    Node<Key, Data>* root;
    Node<Key, Data>* nil;

    void leftRotate(Node<Key, Data>* x) {
        Node<Key, Data>* y = x->right;
        x->right = y->left;
        if (y->left != nil) {
            y->left->parent = x;
        }
        y->parent = x->parent;
        if (x->parent == nil) {
            root = y;
        } else if (x == x->parent->left) {
            x->parent->left = y;
        } else {
            x->parent->right = y;
        }
        y->left = x;
        x->parent = y;
    }

    void rightRotate(Node<Key, Data>* x) {
        Node<Key, Data>* y = x->left;
        x->left = y->right;
        if (y->right != nil) {
            y->right->parent = x;
        }
        y->parent = x->parent;
        if (x->parent == nil) {
            root = y;
        } else if (x == x->parent->right) {
            x->parent->right = y;
        } else {
            x->parent->left = y;
        }
        y->right = x;
        x->parent = y;
    }

    void insertFixup(Node<Key, Data>* z) {
        while (z->parent->color == RED) {
            if (z->parent == z->parent->parent->left) {
                Node<Key, Data>* y = z->parent->parent->right;
                if (y->color == RED) {
                    z->parent->color = BLACK;
                    y->color = BLACK;
                    z->parent->parent->color = RED;
                    z = z->parent->parent;
                } else {
                    if (z == z->parent->right) {
                        z = z->parent;
                        leftRotate(z);
                    }
                    z->parent->color = BLACK;
                    z->parent->parent->color = RED;
                    rightRotate(z->parent->parent);
                }
            } else {
                Node<Key, Data>* y = z->parent->parent->left;
                if (y->color == RED) {
                    z->parent->color = BLACK;
                    y->color = BLACK;
                    z->parent->parent->color = RED;
                    z = z->parent->parent;
                } else {
                    if (z == z->parent->left) {
                        z = z->parent;
                        rightRotate(z);
                    }
                    z->parent->color = BLACK;
                    z->parent->parent->color = RED;
                    leftRotate(z->parent->parent);
                }
            }
        }
        root->color = BLACK;
    }

    void transplant(Node<Key, Data>* u, Node<Key, Data>* v) {
        if (u->parent == nil) {
            root = v;
        } else if (u == u->parent->left) {
            u->parent->left = v;
        } else {
            u->parent->right = v;
        }
        v->parent = u->parent;
    }



    void deleteFixup(Node<Key, Data>* x) {
        while (x != root && x->color == BLACK) {
            if (x == x->parent->left) {
                Node<Key, Data>* w = x->parent->right;
                if (w->color == RED) {
                    w->color = BLACK;
                    x->parent->color = RED;
                    leftRotate(x->parent);
                    w = x->parent->right;
                }
                if (w->left->color == BLACK && w->right->color == BLACK) {
                    w->color = RED;
                    x = x->parent;
                } else {
                    if (w->right->color == BLACK) {
                        w->left->color = BLACK;
                        w->color = RED;
                        rightRotate(w);
                        w = x->parent->right;
                    }
                    w->color = x->parent->color;
                    x->parent->color = BLACK;
                    w->right->color = BLACK;
                    leftRotate(x->parent);
                    x = root;
                }
            } else {
                Node<Key, Data>* w = x->parent->left;
                if (w->color == RED) {
                    w->color = BLACK;
                    x->parent->color = RED;
                    rightRotate(x->parent);
                    w = x->parent->left;
                }
                if (w->right->color == BLACK && w->left->color == BLACK) {
                    w->color = RED;
                    x = x->parent;
                } else {
                    if (w->left->color == BLACK) {
                        w->right->color = BLACK;
                        w->color = RED;
                        leftRotate(w);
                        w = x->parent->left;
                    }
                    w->color = x->parent->color;
                    x->parent->color = BLACK;
                    w->left->color = BLACK;
                    rightRotate(x->parent);
                    x = root;
                }
            }
        }
        x->color = BLACK;
    }

    void deleteNode(Node<Key, Data>* z) {
        Node<Key, Data>* y = z;
        Node<Key, Data>* x;
        Color yOriginalColor = y->color;
        if (z->left == nil) {
            x = z->right;
            transplant(z, z->right);
        } else if (z->right == nil) {
            x = z->left;
            transplant(z, z->left);
        } else {
            y = minimum(z->right);
            yOriginalColor = y->color;
            x = y->right;
            if (y->parent == z) {
                x->parent = y;
            } else {
                transplant(y, y->right);
                y->right = z->right;
                y->right->parent = y;
            }
            transplant(z, y);
            y->left = z->left;
            y->left->parent = y;
            y->color = z->color;
        }
        if (yOriginalColor == BLACK) {
            deleteFixup(x);
        }
        delete z;
    }

    Node<Key, Data>* minimum(Node<Key, Data>* x) const {
        while (x->left != nil) {
            x = x->left;
        }
        return x;
    }

public:
    RedBlackTree() {
        nil = new Node<Key, Data>(Key(), Data());
        nil->color = BLACK;
        root = nil;
    }

    ~RedBlackTree() {
        clear(root);
        delete nil;
    }

    Node<Key, Data>* getRoot() const {
        return root;
    }

    Node<Key, Data>* getNil() const {
        return nil;
    }

    void insert(const Key& key, const Data& data) {
        Node<Key, Data>* z = new Node<Key, Data>(key, data);
        Node<Key, Data>* y = nil;
        Node<Key, Data>* x = root;
        while (x != nil) {
            y = x;
            if (key < x->key) {
                x = x->left;
            } else {
                x = x->right;
            }
        }
        z->parent = y;
        if (y == nil) {
            root = z;
        } else if (key < y->key) {
            y->left = z;
        } else {
            y->right = z;
        }
        z->left = nil;
        z->right = nil;
        z->color = RED;
        insertFixup(z);
    }

    void remove(const Key& key) {
        Node<Key, Data>* z = find(key);
        if (z != nil) {
            deleteNode(z);
        }
    }

    Node<Key, Data>* find(const Key& key) const {
        Node<Key, Data>* x = root;
        while (x != nil) {
            if (key == x->key) {
                return x;
            } else if (key < x->key) {
                x = x->left;
            } else {
                x = x->right;
            }
        }
        return nil;
    }

//    void printInOrder(Node<Key, Data>* node) const {
//        if (node != nil) {
//            printInOrder(node->left);
//            std::cout << node->key << " : ";
//            for (const auto& data : node->dataList) {
//                std::cout << data << " ";
//            }
//            std::cout << std::endl;
//            printInOrder(node->right);
//        }
//    }
//
//    void print() const { printInOrder(root); }

    void clear(Node<Key, Data>* node) {
        if (node != nil) {
            clear(node->left);
            clear(node->right);
            delete node;
        }
    }
};

#define COUNT 10

template <typename Key, typename Data>
void __rb_2D(const RedBlackTree<Key, Data>& tree, Node<Key, Data>* node, size_t space) {
    if (node == tree.getNil()) { // Используем nil для проверки на конец ветви
        return;
    }

    space += COUNT;

    // Печать правой поддерева
    __rb_2D(tree, node->right, space);

    // Отступы
    std::cout << "\n\n";
    for (size_t i = COUNT; i < space; ++i) {
        std::cout << " ";
    }

    // Печать ключа с цветом
    if (node->color == RED) {
        std::cout << "\033[31m"; // Красный цвет
    } else {
        std::cout << "\033[90m"; // Серый цвет
    }
    std::cout << node->key; // Печатаем ключ узла
    std::cout << "\033[0m"; // Сброс цвета

    // Печать левого поддерева
    __rb_2D(tree, node->left, space);
}

template <typename Key, typename Data>
void printTree(const RedBlackTree<Key, Data>& tree) {
    __rb_2D(tree, tree.getRoot(), 0);
}


#endif //LAB3_RBTREE_H
