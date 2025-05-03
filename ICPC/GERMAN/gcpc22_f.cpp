#include <bits/stdc++.h>
using namespace std;

constexpr int thres = 250;

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n, m; cin >> n >> m;
	vector adj(n + 1, vector(0, 0));
	for (int i = 0; i < n; i++) {
		int a, b; cin >> a >> b;
	}
	for (int i = 0; i < m; i++) {
		int a, b; cin >> a >> b;
		adj[a].push_back(b);
		adj[b].push_back(a);
	}
	for (int i = 1; i <= n; i++) {
		ranges::sort(adj[i]);
	}

	vector buc(n + 1, vector(0, 0));
	for (int i = 1; i <= n; i++) {
		for (int j : adj[i]) {
			if (adj[j].size() <= thres) continue;
			buc[i].push_back(j);
		}
	}

	auto sol_3 = [&]() -> bool {
		bitset<100'001> c;
		for (int i = 1; i <= n; i++) {
			if (adj[i].size() > thres) continue;
			for (int j : adj[i]) c[j] = 1;
			for (int j : adj[i]) {
				if (adj[j].size() > thres) continue;
				for (int k : adj[j]) if (c[k]) return 1;
			}
			for (int j : adj[i]) c[j] = 0;
		}
		for (int i = 1; i <= n; i++) {
			if (adj[i].size() <= thres) continue;
			for (int j : adj[i]) c[j] = 1;
			for (int j : adj[i]) for (int k : adj[j]) if (c[k]) return 1;
			for (int j : adj[i]) c[j] = 0;
		}
		return 0;
	};

	auto sol_4 = [&]() -> bool {
		bitset<100'001> c;
		for (int i = 1; i <= n; i++) {
			if (adj[i].size() <= thres) continue;
			for (int j : adj[i]) c[j] = 1;
			for (int k = 1; k <= n; k++) {
				if (k == i || c[k]) continue;
				int cnt = 0;
				for (int x : adj[k]) if (c[x]) cnt++;
				if (cnt >= 2) return 1;
			}
			for (int j : adj[i]) c[j] = 0;
		}
		unordered_set s{ -1LL };
		for (int i = 1; i <= n; i++) {
			if (adj[i].size() > thres) continue;
			for (int j : adj[i]) {
				if (adj[j].size() > thres) continue;
				for (int k : adj[i]) {
					if (j >= k || adj[k].size() > thres) continue;
					auto val = 1LL * j << 30 | k;
					if (s.count(val)) return 1;
					s.insert(val);
				}
			}
		}
		return 0;
	};

	int res = sol_3() ? 3 : sol_4() ? 4 : 5;
	cout << res << '\n';
}