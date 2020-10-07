#include<vector>
#include<iostream>
#include <algorithm>
#include<cmath>
class RSQ {
private:
    std::vector<long long> T;

public:
    long long n;
    RSQ(std::vector<long long> list) {
        long long gr = pow(2, (long long)(log(list.size()) / log(2)) + 1) - list.size();
        for (long long i = 0; i < gr; ++i) {
            list.push_back(0);
        }
        n = list.size();
        T.resize(4 * n);
        for (long long i = n - 1; i <= 2 * n - 2; ++i) {
            T[i] = list[i - n + 1];
        }
        for (long long i = n - 2; i >= 0; --i) {
            T[i] = T[left(i)] + T[right(i)];
        }
    }
    long long parent(long long v) {
        return (v - 1) / 2;
    }
    long long left(long long v) {
        return 2 * v + 1;
    }
    long long right(long long v) {
        return 2 * v + 2;
    }
    void update(long long v, long long i, long long x, long long il, long long ir) {
        if (i >= ir || i < il) {
            return;
        }
        if (v == i + n - 1) {
            T[v] = x;
            return;
        }
        long long im = (il + ir) / 2;
        update(left(v), i, x, il, im);
        update(right(v), i, x, im, ir);
        T[v] = T[left(v)] + T[right(v)];
    }
    long long sum(long long v, long long ql, long long qr, long long il, long long ir) {
        if (ir <= ql || qr <= il) {
            return 0;
        }
        if (ql <= il && ir <= qr) {
            return T[v];
        }
        long long im = (il + ir) / 2;
        return sum(left(v), ql, qr, il, im) + sum(right(v), ql, qr, im, ir);
    }
};





int main() {
    long long n, q;
    std::cin >> n;
    std::vector<long long> A;
    long long num;
    for (long long i = 0; i < n; ++i) {
        std::cin >> num;
        A.push_back(num);
    }
    std::cin >> q;
    RSQ a(A);
    long long t, l, r;
    for (long long i = 0; i < q; ++i) {
        std::cin >> t >> l >> r;
        if (t == 1) {
            r += 1;
            std::cout << a.sum(0, l, r, 0, a.n) << "\n";
        } else if (t == 2) {
                a.update(0, l, r, 0, a.n);
        }
    }
    return 0;
}
