#include <bits/stdc++.h>
using namespace std;

constexpr int mod = 1e9 + 7;
constexpr int thres = 1400;
using i64 = long long;

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n, m; cin >> n >> m;
	vector e(m, pair(0, 0));
	vector type(n + 1, 0);
	vector adj(n + 1, vector(2, vector(0, 0)));
	for (auto& [a, b] : e) {
		cin >> a >> b;
		type[a]++;
		type[b]++;
	}
	for (int i = 1; i <= n; i++) {
		type[i] = type[i] > thres;
	}
	for (auto [a, b] : e) {
		adj[a][type[b]].push_back(b);
		adj[b][type[a]].push_back(a);
	}
	vector v(6, 0LL);
	vector c(n + 1, 0);
	for (int i = 1; i <= n; i++) {
		if (!type[i]) continue;
		for (int x : adj[i][0]) c[x] = 1;
		for (int x : adj[i][1]) c[x] = 1;
		for (int j = 1; j <= n; j++) {
			if (j == i) continue;
			i64 a = 0, b = 0;
			for (int x : adj[j][0]) a += c[x];
			for (int x : adj[j][1]) b += c[x];
			if (type[j]) {
				v[2] += a * (a - 1) >> 1;
				v[5] += b * (b - 1) >> 1;
			}
			else {
				v[1] += a * (a - 1) >> 1;
				v[3] += a * b;
				v[4] += b * (b - 1) >> 1;
			}
		}
		for (int x : adj[i][0]) c[x] = 0;
		for (int x : adj[i][1]) c[x] = 0;
	}
	for (int i = 1; i <= n; i++) {
		if (type[i]) continue;
		for (int j : adj[i][0]) for (int k : adj[j][0]) if (k != i) v[0] += c[k]++;
		for (int j : adj[i][0]) for (int k : adj[j][0]) c[k] = 0;
	}
	i64 res = v[0] / 4 + v[1] + v[2] / 2 + v[3] / 2 + v[4] + v[5] / 4;
	cout << res % mod << '\n';
}