#include <bits/stdc++.h>
using namespace std;

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n, k; cin >> n >> k;
	vector adj(n + 1, vector(0, 0));
	for (int i = 1; i < n; i++) {
		int a, b; cin >> a >> b;
		adj[a].push_back(b);
		adj[b].push_back(a);
	}

	vector mn(n + 1, 1 << 30);  // min selected subtree node distance
	vector smn(n + 1, 1 << 30); // second min
	vector mx(n + 1, 0);        // max un-selected subtree node depth

	auto dfs = [&](const auto& self, int cur, int prv) -> int {
		int res = 0;
		if (prv) adj[cur].erase(ranges::find(adj[cur], prv));
		for (int nxt : adj[cur]) res += self(self, nxt, cur);
		for (int nxt : adj[cur]) {
			if (smn[cur] > mn[nxt] + 1) smn[cur] = mn[nxt] + 1;
			if (mn[cur] > smn[cur]) swap(mn[cur], smn[cur]);
		}
		if (mn[cur] <= k) mx[cur] = -1;
		for (int nxt : adj[cur]) {
			if (mx[nxt] == -1) continue;
			int d = mn[nxt] + 1 != mn[cur] ? mn[cur] : smn[cur];
			if (mx[nxt] + 1 <= k - d) continue;
			mx[cur] = max(mx[cur], mx[nxt] + 1);
		}
		if (mx[cur] == k || cur == 1 && mx[cur] >= 0) {
			mn[cur] = smn[cur] = 0;
			mx[cur] = -1;
			res++;
		}
		return res;
	};

	int res = dfs(dfs, 1, 0);
	cout << res << '\n';
}