#include <bits/stdc++.h>
using namespace std;

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n, m; cin >> n >> m;
	vector adj(n + 1, vector(0, 0));
	for (int i = 1; i < n; i++) {
		int a, b; cin >> a >> b;
		adj[a].push_back(b);
		adj[b].push_back(a);
	}

	vector q(m, 0), d(n + 1, -1), dp(n + 1, 0);
	for (int i = 0; i < m; i++) {
		cin >> q[i];
		d[q[i]] = 0;
		dp[q[i]] = 1;
	}
	for (int i = 0; q.size(); i++) {
		vector nq(0, 0);
		for (int x : q) {
			for (int nxt : adj[x]) {
				if (d[nxt] == -1 || d[nxt] == i + 1) dp[nxt] += dp[x];
				if (d[nxt] == -1) d[nxt] = i + 1, nq.push_back(nxt);
			}
		}
		q.swap(nq);
	}

	int p = -1;
	for (int i = 1; i <= n; i++) if (dp[i] == m) p = i;
	if (p == -1) cout << "NO" << '\n';
	else cout << "YES" << '\n' << p << '\n';
}