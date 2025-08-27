#include <bits/stdc++.h>
using namespace std;

struct union_find {
	union_find(int n) : p(n, -1) {}
	int find(int x) {
		return p[x] < 0 ? x : p[x] = find(p[x]);
	}
	int cnt(int x) {
		return -p[find(x)];
	}
	bool merge(int a, int b) {
		a = find(a);
		b = find(b);
		if (a == b) return 0;
		p[a] += p[b];
		p[b] = a;
		return 1;
	}
private:
	vector<int> p;
};

auto sol = [](int n, int m, string s, string t, auto adj) {
	union_find uf(n + 1);
	for (int i = 1; i <= n; i++) {
		for (int j : adj[i]) {
			if (s[i] != s[j]) continue;
			uf.merge(i, j);
		}
	}
	string ret(n + 1, '.');
	for (int i = 1; i <= n; i++) {
		if (s[i] != 'A' || t[i] != 'T' || uf.cnt(i) == 1) continue;
		ret[uf.find(i)] = 'A';
	}
	for (int i = 1; i <= n; i++) {
		if (s[i] != 'B' || t[i] != '.') continue;
		for (int j : adj[i]) {
			if (s[j] != 'B' || t[j] != '.') continue;
			ret[uf.find(i)] = 'B';
		}
	}
	vector g1(n + 1, vector(0, 0));
	vector g2(n + 1, vector(0, 0));
	vector deg(n + 1, 0);
	for (int i = 1; i <= n; i++) {
		if (ret[uf.find(i)] != '.') continue;
		for (int j : adj[i]) {
			if (s[i] == s[j] || ret[uf.find(j)] != '.') continue;
			g1[uf.find(i)].push_back(uf.find(j));
			if (s[i] == 'B' ^ t[i] == '.' && t[j] == '.') continue;
			g2[uf.find(j)].push_back(uf.find(i));
			deg[uf.find(i)]++;
		}
	}
	vector q(0, 0);
	for (int i = 1; i <= n; i++) {
		if (i != uf.find(i) || ret[i] != '.') continue;
		if (deg[i] == 0) q.push_back(i);
	}
	while (q.size()) {
		int cur = q.back(); q.pop_back();
		ret[cur] = 'A' ^ 'B' ^ s[cur];
		for (int nxt : g1[cur]) {
			if (ret[nxt] != '.') continue;
			ret[nxt] = ret[cur];
			for (int i : g2[nxt]) if (--deg[i] == 0) q.push_back(i);
		}
	}
	for (int i = 1; i <= n; i++) {
		if (ret[uf.find(i)] == '.') ret[uf.find(i)] = 'A';
		ret[i] = ret[uf.find(i)];
	}
	return ret;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int tc; cin >> tc;
	for (int tc_num = 1; tc_num <= tc; tc_num++) {
		int n, m; cin >> n >> m;
		string s(n + 1, 0), t(n + 1, 0);
		vector adj(n + 1, vector(0, 0));
		for (int i = 1; i <= n; i++) cin >> s[i];
		for (int i = 1; i <= n; i++) cin >> t[i];
		for (int i = 0; i < m; i++) {
			int a, b; cin >> a >> b;
			adj[a].push_back(b);
			adj[b].push_back(a);
		}
		string res = sol(n, m, s, t, adj);
		cout << "Case #" << tc_num << '\n';
		for (int i = 1; i <= n; i++) cout << res[i];
		cout << '\n';
	}
}