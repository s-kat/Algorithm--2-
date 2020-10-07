// You need to find all occurrences of the string p in the string t as a substring, up to the possible mismatch of a single character.
#include<vector>
#include<iostream>
#include<string>
#include<algorithm>

std::vector<int> z(std::string S) {
    std::vector<int> z(S.size());
    int l = 0;
    int r = 0;
    for (size_t i = 1; i < S.size(); ++i) {
        if (i <= r) {
            if (i + z[i - l] <= r) {
                z[i] = z[i - l];
            } else {
                z[i] = r - i + 1;
            }
        }
        if (i > r) {
            while (i + z[i] < S.size() && S[z[i]] == S[i + z[i]]) {
                z[i] += 1;
            }
            if (z[i] > 0) {
                l = i;
                r = i + z[i] - 1;
            }
        } else {
            while (i + z[i] < S.size() && S[z[i]] == S[i + z[i]]) {
                z[i] += 1;
            }
            if (i + z[i] - 1 > r) {
                l = i;
                r = i + z[i] - 1;
            }
        }
    }
    return z;
}

int main() {
    std::string str1, str2;
    std::cin >> str1 >> str2;
    auto pr = z(str1 + "#" + str2);
    std::reverse(str1.begin(), str1.end());
    std::reverse(str2.begin(), str2.end());
    auto sf = z(str1 + "#" + str2);
    std::vector<size_t> ans;
    for (size_t i = str1.size() + 1; i < pr.size() - str1.size() + 1; ++i) {
        if (pr[i] + sf[pr.size() - i + 1] >= str1.size() - 1) {
            ans.push_back(i - str1.size());
        } 
    }
    std::cout << ans.size() << "\n";
    for (const auto& el : ans) {
        std::cout << el << " ";
    }
    std::cout << "\n";
    return 0;
}
