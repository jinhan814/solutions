#include <bits/stdc++.h>
using namespace std;

auto sol = [](int n, auto adj) {
	vector par(n + 1, 0), dep(n + 1, 0);
	vector q(1, 1), leaf(0, 0);
	while (q.size()) {
		int x = q.back(); q.pop_back();
		if (adj[x].size() == 1) leaf.push_back(x);
		for (int nx : adj[x]) {
			if (nx == par[x]) continue;
			par[nx] = x;
			dep[nx] = dep[x] + 1;
			q.push_back(nx);
		}
	}
	int d = (leaf.size() + 1) / 2;
	vector buc(d, vector(0, 0));
	for (int i = 0; i < d; i++) {
		int a = leaf[i];
		int b = leaf[i + leaf.size() / 2];
		vector res(0, 0);
		while (a != b) {
			if (dep[a] >= dep[b]) buc[i].push_back(a), a = par[a];
			else res.push_back(b), b = par[b];
		}
		buc[i].push_back(a);
		while (res.size()) {
			buc[i].push_back(res.back());
			res.pop_back();
		}
	};
	vector res(n + 1, vector(d, 0));
	vector c(n + 1, 0);
	for (int i = 0; i < buc[0].size(); i++) {
		res[buc[0][i]][0] = i;
		c[buc[0][i]] = 1;
	}
	for (int k = 1; k < d; k++) {
		int i = 0, j = buc[k].size() - 1;
		while (!c[buc[k][i]]) i++;
		while (!c[buc[k][j]]) j--;
		while (i > 0) {
			res[buc[k][i - 1]] = res[buc[k][i]];
			res[buc[k][i - 1]][k]++;
			c[buc[k][i - 1]] = 1;
			i--;
		}
		while (j < buc[k].size() - 1) {
			res[buc[k][j + 1]] = res[buc[k][j]];
			res[buc[k][j + 1]][k]--;
			c[buc[k][j + 1]] = 1;
			j++;
		}
	}
	return pair(d, res);
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n; cin >> n;
	vector adj(n + 1, vector(0, 0));
	for (int i = 1; i < n; i++) {
		int a, b; cin >> a >> b;
		adj[a].push_back(b);
		adj[b].push_back(a);
	}
	auto [d, res] = sol(n, adj);
	cout << d << '\n';
	for (int i = 1; i <= n; i++) {
		for (int j = 0; j < d; j++) cout << res[i][j] << ' ';
		cout << '\n';
	}
}