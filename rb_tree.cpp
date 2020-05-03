#include<iostream>
struct Node {
    int value;
    Node* par = nullptr;
    Node* left = nullptr;
    Node* right = nullptr;
    int colour;
};

class Tree {
 private:
    Node* root = nullptr;
    int count = 0;

 public:
    bool find(const int& key) const {
        Node* buf = root;
        while (buf) {
            if (buf->value == key) {
                return true;
            } else if (buf->value > key) {
                buf = buf->left;
            } else {
                buf = buf->right;
            }
        }
        return false;
    }
    void counter() {
        std::cout << count << "\n";
    }
    void LeftRotate(Node* x) {
        auto y = x->right;
        x->right = y->left;
        if (y->left != nullptr) {
            y->left->par = x;
        }
        y->par = x->par;
        if (x->par == nullptr) {
            root = y;
        } else {
            if (x == x->par->left) {
                x->par->left = y;
            } else {
                x->par->right = y;
            }
        }
        y->left = x;
        x->par = y;
    }
    void RightRotate(Node* x) {
        auto y = x->left;
        x->left = y->right;
        if (y->right != nullptr) {
            y->right->par = x;
        }
        y->par = x->par;
        if (x->par == nullptr) {
            root = y;
        } else {
            if (x == x->par->right) {
                x->par->right = y;
            } else {
                x->par->left = y;
            }
        }
        y->right = x;
        x->par = y;
    }
    void balance(Node* x) {
        x->colour = 1;
        while (x->par != nullptr && x != root && x->par->colour == 1) {
            if (x->par == x->par->par->left) {
                auto y = x->par->par->right;
                if (y != nullptr && y->colour == 1) {
                    x->par->colour = 0;
                    y->colour = 0;
                    x->par->par->colour = 1;
                    x = x->par->par;
                } else {
                    if (x == x->par->right) {
                        x = x->par;
                        LeftRotate(x);
                    }
                    x->par->colour = 0;
                    x->par->par->colour = 1;
                    RightRotate(x->par->par);
                }
            } else {
                auto y = x->par->par->left;
                if (y != nullptr && y->colour == 1) {
                    x->par->colour = 0;
                    y->colour = 0;
                    x->par->par->colour = 1;
                    x = x->par->par;
                } else {
                    if (x == x->par->left) {
                        x = x->par;
                        RightRotate(x);
                    }
                    x->par->colour = 0;
                    x->par->par->colour = 1;
                    LeftRotate(x->par->par);
                }
            }
        }
        root->colour = 0;
    }


    void insert(const int& key) {
        if (root == nullptr) {
            Node* r_node = new Node;
            r_node->value = key;
            r_node->colour = 0;
            root = r_node;
            ++count;
        } else {
            Node* cur = root;
            while (cur) {
                if (cur->value == key) {
                    return;
                } else if (cur->value < key) {
                    if (cur->right == nullptr) {
                        Node* new_node = new Node;
                        new_node->value = key;
                        new_node->colour = 1;
                        new_node->par = cur;
                        cur->right = new_node;
                        ++count;
                        balance(new_node);
                        return;
                    } else {
                        cur = cur->right;
                    }
                } else {
                    if (cur->left == nullptr) {
                        Node* new_node = new Node;
                        new_node->value = key;
                        new_node->colour = 1;
                        new_node->par = cur;
                        cur->left = new_node;
                        ++count;
                        balance(new_node);
                        return;
                    } else {
                        cur = cur->left;
                    }
                }
            }
        }
    }
    void Print(Node* el) {
        std::cout << el->value << " ";
        if (el->left != nullptr) {
            std::cout << el->left->value << " ";
        } else {
            std::cout << "null ";
        }
        if (el->right != nullptr) {
            std::cout << el->right->value << " ";
        } else {
            std::cout << "null ";
        }
        if (el->colour == 0) {
            std::cout << "B ";
        } else {
            std::cout << "R ";
        }
        std::cout << "\n";
        if (el->left != nullptr) {
            Print(el->left);
        }
        if (el->right != nullptr) {
            Print(el->right);
        }
    }
    void ShowTree() {
        if (count != 0) {
            Print(root);
        }
    }
};

int main() {
    int n;
    std::cin >> n;
    Tree rb;
    for (int count = 0; count < n; ++count) {
        int com, key;
        std::cin >> com >> key;
        if (com == 0) {
            rb.insert(key);
        } else {
            if (rb.find(key)) {
                std::cout << "Yes\n";
            } else {
                std::cout << "No\n";
            }
        }
    }
    rb.counter();
    rb.ShowTree();
    return 0;
}
