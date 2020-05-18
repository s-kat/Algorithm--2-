#include<vector>
#include<iostream>
#include<queue>

int main() {
    int n, s, f;
    std::cin >> n >> s >> f;
    s -= 1;
    f -= 1;
    std::vector<std::vector<long long>> table;
    long long num;
    for (int i = 0; i < n; ++i) {
        std::vector<long long> r;
        for (int j = 0; j < n; ++j) {
            std::cin >> num;
            r.push_back(num);
        }
        table.push_back(r);
    }



    std::priority_queue<std::pair<long long, int>> d;
    std::vector<long long> dist (n, std::numeric_limits<long long>::max());
    dist[s] = 0;
    d.push({ 0, s });
    while (!d.empty()) {
        auto el = d.top();
        d.pop();
        long long ind = el.second;
        for (int i = 0; i < n; ++i) {
            if (table[ind][i] != -1 && table[ind][i] + el.first < dist[i]) {
                dist[i] = table[ind][i] + el.first;
                d.push({ dist[i], i });
            }
        }
    }
    if (dist[f] != std::numeric_limits<long long>::max()) {
        std::cout << dist[f];
    } else {
        std::cout << -1;
    }
    return 0;
}
