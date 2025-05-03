#include <bits/stdc++.h>
using namespace std;

constexpr int mod = 1'000'003;

auto aho_corasick = [](const auto& v) {
	int m = 1'000, sz = 0; // m = O(\sum{s_i})
	vector flag(m, 0);
	vector nxt(m, array<int, 26>{});
	for (const string& s : v) {
		int p = 0;
		for (char c : s) {
			if (!nxt[p][c - 'a']) nxt[p][c - 'a'] = ++sz;
			p = nxt[p][c - 'a'];
		}
		flag[p] = 1;
	}
	vector fail(m, 0);
	deque q(0, 0);
	for (int x : nxt[0]) if (x) q.push_back(x);
	while (q.size()) {
		int p = q.front(); q.pop_front();
		for (int i = 0; i < 26; i++) {
			if (!nxt[p][i]) continue;
			int x = fail[p];
			while (x && !nxt[x][i]) x = fail[x];
			fail[nxt[p][i]] = nxt[x][i];
			q.push_back(nxt[p][i]);
		}
	}
	return tuple(flag, nxt, fail);
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int a, b, n; cin >> a >> b >> n;
	vector v(n, string{});
	for (int i = 0; i < n; i++) cin >> v[i];

	sort(v.begin(), v.end());
	v.erase(unique(v.begin(), v.end()), v.end());
	vector nv(0, string{});
	for (int i = 0; i < n; i++) {
		bool flag = 0;
		for (int j = 0; j < n; j++) if (i != j && v[i].find(v[j]) != -1) flag = 1;
		if (!flag) nv.push_back(v[i]);
	}

	auto [flag, nxt, fail] = aho_corasick(nv);
	auto get_nxt = [&](int p, char c) {
		while (p && !nxt[p][c - 'a']) p = fail[p];
		return nxt[p][c - 'a'];
	};

	vector dp(flag.size(), vector(b + 1, vector(1 << 3, -1)));
	auto dfs = [&](const auto& self, int p, int len, int s) -> int {
		if (len > b || flag[p]) return 0;
		int& ret = dp[p][len][s];
		if (ret != -1) return ret;
		ret = a <= len && len <= b && (s == 7);
		for (int i = 0; i < 26; i++) { // lowercase
			int np = get_nxt(p, 'a' + i);
			int nlen = len + 1;
			int ns = s | 1;
			int res = self(self, np, nlen, ns);
			ret += res;
			if (ret >= mod) ret -= mod;
		}
		for (int i = 0; i < 26; i++) { // uppercase
			int np = get_nxt(p, 'a' + i);
			int nlen = len + 1;
			int ns = s | 2;
			int res = self(self, np, nlen, ns);
			ret += res;
			if (ret >= mod) ret -= mod;
		}
		for (int i = 0; i < 10; i++) { // digit
			int np = 0;
			if (i == 0) np = get_nxt(p, 'o');
			if (i == 1) np = get_nxt(p, 'i');
			if (i == 3) np = get_nxt(p, 'e');
			if (i == 5) np = get_nxt(p, 's');
			if (i == 7) np = get_nxt(p, 't');
			int nlen = len + 1;
			int ns = s | 4;
			int res = self(self, np, nlen, ns);
			ret += res;
			if (ret >= mod) ret -= mod;
		}
		return ret;
	};
	cout << dfs(dfs, 0, 0, 0) << '\n';
}