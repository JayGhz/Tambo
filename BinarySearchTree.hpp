#include "Libreries.hpp"

template <class T>
class BinarySearchTree {
private:
    template <class Generic>
    class Node {
    public:
        Generic data;
        Node<Generic> *left;
        Node<Generic> *right;

        Node(Generic data = NULL, Node<Generic> *left = nullptr, Node<Generic> *right = nullptr)
            : data(data), left(left), right(right) {}
    };

    Node<T> *root;
    function<int(T, T)> compare;
    size_t tree_size;

    void _insert(Node<T>*& node, T data) {
        if (node == nullptr) {
            node = new Node<T>(data);
            tree_size++;
        } else {
            if (compare(data, node->data) < 0) {
                _insert(node->left, data);
            } else {
                _insert(node->right, data);
            }
        }
    }

    void _reiterate(Node<T> *node, function<void(T)> func) {
        if (node != nullptr) {
            _reiterate(node->left, func);
            func(node->data);
            _reiterate(node->right, func);
        }
    }

    void _clear(Node<T>*& node) {
        if (node != nullptr) {
            _clear(node->left);
            _clear(node->right);
            delete node;
            node = nullptr;
        }
        tree_size = 0;
    }

    void _remove(Node<T>*& node, T data) {
        if (node == nullptr) {
            return;
        }
        if (compare(data, node->data) < 0) {
            _remove(node->left, data);
        } else if (compare(data, node->data) > 0) {
            _remove(node->right, data);
        } else {
            if (node->left == nullptr && node->right == nullptr) {
                delete node;
                node = nullptr;
            } else if (node->left == nullptr) {
                Node<T>* temp = node;
                node = node->right;
                delete temp;
            } else if (node->right == nullptr) {
                Node<T>* temp = node;
                node = node->left;
                delete temp;
            } else {
                Node<T>* temp = node->right;
                while (temp->left != nullptr) {
                    temp = temp->left;
                }
                node->data = temp->data;
                _remove(node->right, temp->data);
            }
            tree_size--;
        }
    }

    size_t _size(Node<T>* node) {
        if (node == nullptr) {
            return 0;
        }
        return 1 + _size(node->left) + _size(node->right);
    }

    Node<T>* _find(Node<T>* node, T data) {
        while (node != nullptr) {
            if (compare(data, node->data) == 0) {
                return node;
            } else if (compare(data, node->data) < 0) {
                node = node->left;
            } else {
                node = node->right;
            }
        }
        return nullptr;
    }

public:
    BinarySearchTree(function<int(T, T)> comp) : root(nullptr), tree_size(0), compare(comp) {}

    ~BinarySearchTree() {
        _clear(root);
    }

    void insert(T data) {
        _insert(root, data);
    }

    void remove(T data) {
        _remove(root, data);
    }

    void reiterate(function<void(T)> func) {
        _reiterate(root, func);
    }

    void clear() {
        _clear(root);
    }

    bool empty() {
        return root == nullptr;
    }

    size_t size() {
        return tree_size;
    }

    Node<T>* find(T data) {
        return _find(root, data);
    }
};