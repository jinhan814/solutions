#include <bits/stdc++.h>
using namespace std;

auto sol = [](int n, int m, auto v) {
	vector c(n + 1, 0), rev(n + 1, 0), cnt(n + 1, 0);
	for (int i = 1; i <= n; i++) c[i] = rev[i] = i;
	for (int i = 1; i < m; i++) {
		int a = v[i - 1], b = v[i];
		cnt[rev[b]]++;
		swap(c[rev[a]], c[rev[b]]);
		swap(rev[a], rev[b]);
	}
	vector res(0, 0);
	for (int i = 1; i <= n; i++) if (i != v[0]) res.push_back(i);
	sort(res.begin(), res.end(), [&](int i, int j) { return cnt[i] > cnt[j]; });
	auto acc = 0LL;
	for (int i = 0; i < n - 1; i++) acc += cnt[res[i]] * (i + 1);
	return pair(acc, res);
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n, m; cin >> n >> m;
	vector v(m, 0);
	for (int i = 0; i < m; i++) cin >> v[i];
	auto [acc, res] = sol(n, m, v);
	cout << acc << '\n';
	for (int x : res) cout << x << ' ';
	cout << '\n';
}