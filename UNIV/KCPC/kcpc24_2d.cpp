#include <bits/stdc++.h>
using namespace std;

constexpr int mod = 1e9 + 7;

using i64 = long long;

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n, m; cin >> n >> m;
	vector adj(n + 1, vector(0, 0));
	for (int i = 0; i < m; i++) {
		int a, b; cin >> a >> b;
		adj[a].push_back(b);
		adj[b].push_back(a);
	}
	i64 res = 0;
	vector c(n + 1, 0);
	for (int i = 1; i <= n; i++) {
		for (int j : adj[i]) for (int k : adj[j]) if (k != i) res += c[k]++;
		for (int j : adj[i]) for (int k : adj[j]) c[k] = 0;
	}
	cout << res / 4 % mod << '\n';
}