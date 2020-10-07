/*At your disposal is a list of taxi orders for the next day. You need to minimize the number of taxi cars required to fulfill all orders.
For simplicity, we assume that the city plan is a square grid. The address in the city will be denoted by a pair of integers: x-coordinate and y-coordinate. 
The time required to get from the point with the address (a, b) to the point (c, d) is |ac| + |bd| minutes. 
A taxi car can fulfill another order, either if it is its first order of the day, or it manages to arrive at the starting point from 
the previous destination at least a minute before the specified deadline.
*/

#include<iostream>
#include<map>
#include<string>
#include<vector>
#include<set>
std::vector<std::vector<int>> gr;
std::vector<int> matching;
std::vector<int> used;

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

struct Order {
    int a = 0, b = 0, c = 0, d = 0;
    std::string st;
    int time = 0;
    int dist = 0;
    void Dist() {
        dist = abs(a - c) + abs(b - d);
    }
    void Time() {
        time = (st[0] - '0') * 600 + (st[1] - '0') * 60 + (st[3] - '0') * 10 + (st[4] - '0');
    }
};





int main() {
    int k;
    std::cin >> k;
    matching.assign(k, -1);
    std::vector<Order> orders;
    for (int i = 0; i < k; ++i) {
        Order ord;
        std::cin >> ord.st >> ord.a >> ord.b >> ord.c >> ord.d;
        ord.Dist();
        ord.Time();
        orders.push_back(ord);
    }
    for (int i = 0; i < k; ++i) {
        gr.emplace_back();
        for (int j = 0; j < k; ++j) {
            if (i != j) {
                if (orders[j].time >= orders[i].time + orders[i].dist + abs(orders[j].a - orders[i].c) +
                    abs(orders[j].b - orders[i].d) + 1) {
                    gr[i].push_back(j);
                }
            }
        }
    }
    for (int i = 0; i < k; ++i) {
        used.assign(k, 0);
        kuhn(i);
    }
    int count = 0;
    for (int i = 0; i < k; ++i) {
        if (matching[i] == -1) {
            ++count;
        }
    }
    std::cout << count << "\n";
    return 0;
}
