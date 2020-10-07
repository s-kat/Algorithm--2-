/*
Mitya knows m boys and n girls and wants to invite some of them to his birthday party. 
He knows which girls each young man is familiar with, and which young men each girl is familiar with. 
He wants to make sure that everyone invited is familiar with all the invited people of the opposite sex, 
while inviting as many of his acquaintances as possible
*/
#include<iostream>
#include<map>
#include<string>
#include<vector>
#include<set>
std::vector<std::vector<int>> gr;
std::vector<int> matching;
std::vector<int> used;
std::vector<int> left;
std::vector<int> right;

bool kuhn(int v) {
    if (used[v] == 1) {
        return 0;
    }
    used[v] = 1;
    for (const auto& el : gr[v]) {
        int to = el - 1;
        if (matching[to] == -1 || kuhn(matching[to]) == 1) {
            matching[to] = v;
            return 1;
        }
    }
    return 0;
}

void dfs(int v) {
    if (left[v] == 1) {
        return;
    }
    left[v] = 1;
    for (auto& el : gr[v]) {
        int to = el - 1;
        if (right[to] == 0) {
            right[to] = 1;
            if (matching[to] != -1) {
                dfs(matching[to]);
            }
        }
    }
}





int main() {
    int n, m, k;
    std::cin >> k;
    for (int sets = 0; sets < k; ++sets) {
        std::cin >> n >> m;
        gr.clear();
        matching.assign(m, -1);
        int a;
        for (int i = 0; i < n; ++i) {
            gr.emplace_back();
            std::set<int> buf;
            while (std::cin >> a) {
                if (a != 0) {
                    buf.insert(a);
                } else {
                    break;
                }
            }
            size_t ind = 0;
            for (int j = 1; j <= m; ++j) {
                if (buf.find(j) == buf.end()) {
                    gr.back().push_back(j);
                }
            }
        }


        for (int i = 0; i < n; ++i) {
            used.assign(n, 0);
            kuhn(i);
        }
        // Построили максимальное паросочетание в дополнении графа 

        std::set<int> not_free;
        for (const auto& el : matching) {
            if (el != -1) {
                not_free.insert(el);
            }
        }
        left.assign(n, 0);
        right.assign(m, 0);
        for (int i = 0; i < n; ++i) {
            if (not_free.find(i) == not_free.end()) {
                dfs(i);
            }
        }



        std::set<int> men;
        std::set<int> women;
        for (int i = 0; i < n; ++i) {
            if (left[i] == 0) {
                men.insert(i);
            }
        }
        for (int i = 0; i < m; ++i) {
            if (right[i] == 1) {
                women.insert(i);
            }
        }


        std::cout << m + n - men.size() - women.size() << "\n";
        std::cout << n - men.size() << " " << m - women.size() << "\n";



        for (int i = 0; i < n; ++i) {
            if (men.find(i) == men.end()) {
                std::cout << i + 1 << " ";
            }
        }
        std::cout << "\n";
        for (int i = 0; i < m; ++i) {
            if (women.find(i) == women.end()) {
                std::cout << i + 1 << " ";
            }
        }
        std::cout << "\n";
    }
    return 0;
}
