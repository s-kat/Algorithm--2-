#include<iostream>
#include<vector>
#include<string>

std::vector<long long> pref(std::string S) {
    std::vector<long long> pi(S.size());
    for (size_t i = 1; i < S.size(); ++i) {
        int k = pi[i - 1];
        while (S[k] != S[i] && k > 0) {
            k = pi[k - 1];
        }
        if (S[k] == S[i]) {
            pi[i] = k + 1;
        } else {
            pi[i] = 0;
        }
    }
    return pi;
}

int main() {
    std::vector<std::vector<long long>> kmp;
    long long n, k, a;
    std::string s;
    std::cin >> n >> a >> k >> s;
    auto pr = pref(s);
    for (size_t i = 0; i < s.size(); ++i) {
        kmp.emplace_back();
        for (char j = 97; j < a + 97; ++j) {
            if (i == 0) {
                if (j == s[i]) {
                    kmp[i].push_back(1);
                } else {
                    kmp[i].push_back(0);
                }
            } else if (j != s[i]) {
                kmp[i].push_back(kmp[pr[i - 1]][j - 97]);
            } else {
                kmp[i].push_back(i + 1);
            }
        }
    }

    long long max_route = 0;
    for (long long i = 0; i < s.size(); ++i) {
        for (long long j = 0; j < kmp[i].size(); ++j) {
            if (i - kmp[i][j] > max_route) {
                max_route = i - kmp[i][j];
            }
        }
    }
    long long ans = max_route * k + n;
    std::cout << ans;
    return 0;
}
