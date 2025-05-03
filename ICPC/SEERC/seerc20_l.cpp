#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int n; cin >> n;
    vector v(n, pair(0, 0));
    for (auto& [a, b] : v) cin >> a;
    for (auto& [a, b] : v) cin >> b;
    sort(v.begin(), v.end(), [](auto a, auto b) { return a.first + a.second > b.first + b.second; });

    auto check = [&](int k) -> bool {
        vector a(n, 0LL), b(n, 0LL);
        {
            auto acc = 0LL;
            priority_queue<int> pq1;
            priority_queue<int, vector<int>, greater<>> pq2;
            for (int i = 0; i < k - 1; i++) pq2.push(v[i].first), acc += v[i].first;
            for (int i = k - 1; i < n; i++) {
                pq2.push(v[i].first);
                acc += v[i].first;
                while (pq2.size() > k) {
                    auto x = pq2.top();
                    pq2.pop();
                    pq1.push(x);
                    acc -= x;
                }
                while (pq1.size() && pq2.size() && pq1.top() > pq2.top()) {
                    auto x = pq1.top(); pq1.pop();
                    auto y = pq2.top(); pq2.pop();
                    pq1.push(y);
                    pq2.push(x);
                    acc += x - y;
                }
                a[i] = acc;
            }
        }
        {
            auto acc = 0LL;
            priority_queue<int> pq1;
            priority_queue<int, vector<int>, greater<>> pq2;
            for (int i = n - 1; i > n - k; i--) pq1.push(v[i].second), acc += v[i].second;
            for (int i = n - k; i >= 0; i--) {
                pq1.push(v[i].second);
                acc += v[i].second;
                while (pq1.size() > k) {
                    auto x = pq1.top();
                    pq1.pop();
                    pq2.push(x);
                    acc -= x;
                }
                while (pq1.size() && pq2.size() && pq1.top() > pq2.top()) {
                    auto x = pq1.top(); pq1.pop();
                    auto y = pq2.top(); pq2.pop();
                    pq1.push(y);
                    pq2.push(x);
                    acc += y - x;
                }
                b[i] = acc;
            }
        }
        for (int i = k - 1; i < n - k; i++) if (a[i] >= b[i + 1]) return 1;
        return 0;
    };

    int lo = 0, hi = n;
    while (lo + 1 < hi) {
        int mid = lo + hi >> 1;
        if (check(mid)) lo = mid;
        else hi = mid;
    }
    cout << lo << '\n';
}