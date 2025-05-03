#include <bits/stdc++.h>
using namespace std;

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n, m, k; cin >> n >> m >> k;
	vector adj(n + 1, vector(0, 0));
	for (int i = 0; i < m; i++) {
		int a, b; cin >> a >> b;
		adj[a].push_back(b);
		adj[b].push_back(a);
	}

	vector d(n + 1, -1), q(0, 0);
	for (int i = 0; i < k; i++) {
		int x; cin >> x;
		d[x] = 0;
		q.push_back(x);
	}

	vector c(n + 1, 0);
	for (int x = 1; q.size(); x++) {
		vector nq(0, 0);
		for (int i : q) for (int j : adj[i]) {
			if (++c[j] < 2 || d[j] != -1) continue;
			nq.push_back(j);
			d[j] = x;
		}
		q.swap(nq);
	}
	cout << d[1] << '\n';
}