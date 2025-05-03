#include <bits/stdc++.h>
using namespace std;

using i64 = long long;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int n; cin >> n;
    vector v(n + 1, 0);
    for (int i = 1; i <= n; i++) cin >> v[i], v[i] %= 3;

    auto dfs = [&](const auto& self, int l, int r) -> i64 {
        if (l == r) return 1;
        int mid = l + r >> 1;
        i64 res = self(self, l, mid) + self(self, mid + 1, r);
        vector cnt(3, vector(3, 0));
        for (int i = mid, a = 0, b = 0; i >= l; i--) {
            if (v[i] == 1) a = (a + 1) % 3;
            if (v[i] == 2) b = (b + 1) % 3;
            cnt[a][b]++;
        }
        for (int i = mid + 1, a = 0, b = 0; i <= r; i++) {
            if (v[i] == 1) a = (a + 1) % 3;
            if (v[i] == 2) b = (b + 1) % 3;
            for (int x = 0; x < 3; x++) for (int y = 0; y < 3; y++) {
                int t1 = (a + x) % 3;
                int t2 = (b + y) % 3;
                if (t1 + t2 <= 1) res += cnt[x][y];
            }
        }
        return res;
    };

    i64 res = dfs(dfs, 1, n);
    cout << res << '\n';
}