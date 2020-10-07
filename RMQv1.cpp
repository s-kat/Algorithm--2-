// Minimum element greater than X on the segment, with element change
#include<vector>
#include<iostream>
#include <algorithm>
#include<cmath>
#include<set>
class RSQ {
private:
    std::vector<std::vector<long long>> T1;
    std::vector<std::multiset<long long>> T;

public:
    long long n;
    RSQ(std::vector<long long> list) {
        long long gr = pow(2, (long long)(log(list.size()) / log(2)) + 1) - list.size();
        for (long long i = 0; i < gr; ++i) {
            list.push_back(0);
        }
        n = list.size();
        T1.resize(4 * n);
        T.resize(4 * n);
        for (long long i = n - 1; i <= 2 * n - 2; ++i) {
            std::vector<long long> buf;
            buf.push_back(list[i - n + 1]);
            T1[i] = buf;
        }
        for (long long i = n - 2; i >= 0; --i) {
            std::vector<long long> buf;
            std::merge(T1[left(i)].begin(), T1[left(i)].end(), T1[right(i)].begin(), T1[right(i)].end(), std::back_inserter(buf));
            T1[i] = buf;
        }
        for (size_t i = 0; i < T1.size(); ++i) {
            std::multiset<long long> buf;
            buf.insert(T1[i].begin(), T1[i].end());
            T[i] = buf;
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
    long long sum(long long v, long long ql, long long qr, long long l, long long r, long long k) {
        auto m = (l + r) / 2;
        if (l > qr || r < ql) {
            return 100000000000ll;
        }
        if (l > r) {
            return 100000000000ll;
        }
        if (l >= ql && r <= qr) {
            auto el = T[v].upper_bound(k);
            if (el != T[v].end()) {
                return *el;
            } else {
                return 100000000000ll;
            }
        }
        return std::min(sum(left(v), ql, qr, l, m, k),
            sum(right(v), ql, qr, m + 1, r, k));
    }
    void update(long long v, long long ind, long long l, long long r, long long x, long long old) {
        T[v].erase(T[v].find(old));
        T[v].insert(x);
        if (l != r) {
            auto m = (l + r) / 2;
            if (ind <= m) {
                update(left(v), ind, l, m, x, old);
            } else {
                update(right(v), ind, m + 1, r, x, old);
            }
        }
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
    long long com, t, l, r, ind, x;
    for (long long i = 0; i < q; ++i) {
        std::cin >> com;
        if (com == 1) {
            std::cin >> l >> r >> t;
            auto ans = a.sum(0, l, r, 0, a.n - 1, t);
            if (ans != 100000000000ll) {
                std::cout << ans << "\n";
            } else {
                std::cout << "NONE\n";
            }
        } else {
            std::cin >> ind >> x;
            a.update(0, ind, 0, a.n - 1, x, A[ind]);
            A[ind] = x;
        }
    }
    return 0;
}
