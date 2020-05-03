#include<algorithm>
#include<iostream>
#include<vector>
#include<string>

struct Node {
    int num;
    int key;
    int left = -1;
    int right = -1;
    std::string color;
};
int min, max, length;
int checker = 0;
std::vector<Node> tree;
// проверяем все поддерево каждого элемента
void find_max(Node& el) {
    if (el.key > max) {
        max = el.key;
    }
    if (el.left != -1) {
        find_max(tree[el.left]);
    }
    if (el.right != -1) {
        find_max(tree[el.right]);
    }
}

void find_min(Node& el) {
    if (el.key < min) {
        min = el.key;
    }
    if (el.left != -1) {
        find_max(tree[el.left]);
    }
    if (el.right != -1) {
        find_max(tree[el.right]);
    }
}

void find_length(Node& el, int len) {
    if (el.left == -1) {
        if (length == 0) {
            length = len;
        } else if (length != len) {
            checker = 1;
        }
    }
    if (el.right == -1) {
        if (length == 0) {
            length = len;
        } else if (length != len) {
            checker = 1;
        }
    }
    if (el.left != -1) {
        if (tree[el.left].color == "B") {
            int new_len = len + 1;
            find_length(tree[el.left], new_len);
        } else {
            find_length(tree[el.left], len);
        }
    }
    if (el.right != -1) {
        if (tree[el.right].color == "B") {
            int new_len = len + 1;
            find_length(tree[el.right], new_len);
        } else {
            find_length(tree[el.right], len);
        }
    }
}


bool check(Node& el) {
    // для начала проверим что у красного родителя черные дети и выполняется усл поиска
    // нахдим максимум справа и минимум слева и сравниваем с корнем
    min = el.key;
    max = el.key;
    if (el.left != -1) {
        find_max(tree[el.left]);
        if (max > el.key) {
            return false;
        }
    }
    if (el.right != -1) {
        find_min(tree[el.right]);
        if (min < el.key) {
            return false;
        }
    }
    // теперь ищем черную высоту
    length = 0;
    checker = 0;
    find_length(el, 0);
    if (checker == 1) {
        return false;
    }
    return true;
}

int main() {
    int n, root;
    std::cin >> n >> root;
    if (n == 0) {
        std::cout << "YES";
    } else {
        tree.resize(n);
        for (int count = 0; count < n; ++count) {
            int num, key;
            std::string left, right, color;
            std::cin >> num >> key >> left >> right >> color;
            Node el;
            el.num = num - 1;
            el.key = key;
            el.color = color;
            if (left == "null") {
                el.left = -1;
            } else {
                el.left = atoi(left.c_str()) - 1;
            }
            if (right == "null") {
                el.right = -1;
            } else {
                el.right = atoi(right.c_str()) - 1;
            }
            tree[num - 1] = el;
        }
        int key = 1;
        if (tree[root - 1].color == "R") {
            std::cout << "NO";
            key = 0;
        } else {
            for (size_t id = 0; id < tree.size(); ++id) {
                if (!check(tree[id])) {
                    std::cout << "NO";
                    key = 0;
                    break;
                }
                if (tree[id].color == "R") {
                    if (tree[id].left != -1 && tree[tree[id].left].color == "R") {
                        std::cout << "NO";
                        key = 0;
                        break;
                    } else if (tree[id].right != -1 && tree[tree[id].right].color == "R") {
                        std::cout << "NO";
                        key = 0;
                        break;
                    }
                }
            }
        }
        if (key == 1) {
            std::cout << "YES";
        }
    }
    return 0;
}
