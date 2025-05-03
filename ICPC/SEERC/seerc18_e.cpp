#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int n, m, k; cin >> n >> m >> k;
    vector data(n, pair(0, 0));
    vector v(m, 0);
    for (auto& [x, y] : data) cin >> x >> y;
    for (int i = 0; i < m; i++) cin >> v[i];
    sort(data.begin(), data.end());

    vector idx(m, 0);
    iota(idx.begin(), idx.end(), 0);
    sort(idx.begin(), idx.end(), [&](int i, int j) { return v[i] < v[j]; });

    vector res(m, 0);
    for (int _ = 0; _ < 2; _++) {
        set s{ pair(-(1 << 30), 0)};
        for (int i = 0, l = 0, r = 0; i < m; i++) {
            while (r < n && data[r].first <= v[idx[i]]) {
                auto [x, y] = data[r++];
                s.insert({ x - y + k, r });
            }
            while (l < r && data[l].first < v[idx[i]] - k) {
                auto [x, y] = data[l++];
                if (s.count({ x - y + k, l })) s.erase({ x - y + k, l });
            }
            while (s.size() && s.begin()->first < v[idx[i]]) {
                s.erase(s.begin());
            }
            res[idx[i]] += s.size();
        }
        for (auto& [x, y] : data) x = -x;
        for (int& x : v) x = -x;
        reverse(data.begin(), data.end());
        reverse(idx.begin(), idx.end());
    }
    for (int i = 0; i < m; i++) {
        int x = v[idx[i]];
        auto lo = lower_bound(data.begin(), data.end(), pair(x, 0));
        auto hi = upper_bound(data.begin(), data.end(), pair(x, k));
        res[idx[i]] -= hi - lo;
    }

    for (int x : res) cout << x << '\n';
}