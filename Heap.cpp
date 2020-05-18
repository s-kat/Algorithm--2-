#include<iostream>
#include<vector>


class Heap {
private:
    size_t size = 0;
    std::vector<long long> h;
public:
    Heap() {
        size = 0;
    }
    size_t Left(size_t i) {
        return 2 * i + 1;
    }
    size_t Right(size_t i) {
        return 2 * i + 2;
    }
    size_t Parent(size_t i) {
        return (i - 1) / 2;
    }
    void Heapify_up(size_t i) {
        while (i > 0 && h[i] > h[Parent(i)]) {
            auto buf = h[i];
            h[i] = h[Parent(i)];
            h[Parent(i)] = buf;
            i = Parent(i);
        }
    }
    void Insert(long long k) {
        size += 1;
        h.push_back(k);
        Heapify_up(size - 1);
    }
    void Heapify_down(size_t i) {
        auto l = Left(i);
        auto r = Right(i);
        size_t child;
        if (l < size) {
            if (r < size && h[r] > h[l]) {
                child = r;
            } else {
                child = l;
            }
            if (h[child] > h[i]) {
                auto buf = h[i];
                h[i] = h[child];
                h[child] = buf;
                Heapify_down(child);
            }
        }
    }
    void Extract() {
        std::cout << h[0] << "\n";
        h[0] = h[size - 1];
        h.pop_back();
        size -= 1;
        Heapify_down(0);
    }
};


int main() {
    int n, com, key;
    Heap a;
    std::cin >> n;
    for (int i = 0; i < n; ++i) {
        std::cin >> com;
        if (com == 0) {
            std::cin >> key;
            a.Insert(key);
        } else {
            a.Extract();
        }
    }
    return 0;
}
