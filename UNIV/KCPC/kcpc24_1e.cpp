#include <bits/stdc++.h>
using namespace std;

constexpr int thres = 300;

using i64 = long long;

auto sol = [](int n, int m, int q, const auto& qu) {
	vector cnt(m + 1, 0), buc(0, 0);
	for (auto [t, a, b] : qu) {
		if (t != 1) continue;
		if (++cnt[a] == thres) buc.push_back(a);
	}
	vector res(0, 0LL);
	vector v(n + 1, 0LL), acc(m + 1, 0LL);
	vector c(m + 1, unordered_set{ 0 });
	for (auto [t, a, b] : qu) {
		if (t == 1) {
			if (c[a].count(b)) c[a].erase(b), v[b] += acc[a];
			else c[a].insert(b), v[b] -= acc[a];
		}
		else if (t == 2) {
			if (cnt[a] < thres) for (int i : c[a]) v[i] += b;
			else acc[a] += b;
		}
		else {
			i64 x = v[a];
			for (int i : buc) if (c[i].count(a)) x += acc[i];
			res.push_back(x);
		}
	}
	return res;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n, m, q; cin >> n >> m >> q;
	vector qu(q, array{ 0, 0, 0 });
	for (auto& [t, a, b] : qu) {
		cin >> t >> a;
		if (t < 3) cin >> b;
	}
	auto res = sol(n, m, q, qu);
	for (i64 x : res) cout << x << '\n';
}