#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

auto suffix_array = [](const string& s) {
	const int n = s.size();
	vector v(n, 0);
	iota(v.begin(), v.end(), 0);
	sort(v.begin(), v.end(), [&](int i, int j) {
		string a = s.substr(i);
		string b = s.substr(j);
		return a < b;
	});
	return v;
};

auto lcp_array = [](const string& s, const auto& sa) {
	const int n = s.size();
	vector v(n, 0);
	for (int i = 1; i < n; i++) {
		int a = sa[i - 1];
		int b = sa[i];
		while (a < n && b < n && s[a] == s[b]) a++, b++, v[i]++;
	}
	return v;
};

struct segtree {
	segtree(int n) : sz(1 << __lg(n - 1) + 1), tree(sz << 1, -1) {}
	void update(int i, int x) {
		tree[i |= sz] = x;
		while (i >>= 1) tree[i] = max(tree[i << 1], tree[i << 1 | 1]);
	}
	int query(int l, int r) const {
		int ret = -1;
		for (l |= sz, r |= sz; l <= r; l >>= 1, r >>= 1) {
			if (l & 1) ret = max(ret, tree[l++]);
			if (~r & 1) ret = max(ret, tree[r--]);
		}
		return ret;
	}
private:
	int sz;
	vector<int> tree;
};

auto sol = [](string s) {
	const int n = s.size();
	const auto sa = suffix_array(s);
	const auto lcp = lcp_array(s, sa);

	vector rsa(n, 0);
	vector lo(n, vector(n + 1, 0));
	vector hi(n, vector(n + 1, 0));
	for (int i = 0; i < n; i++) {
		rsa[sa[i]] = i;
		lo[i][0] = 0;
		hi[i][0] = n - 1;
	}
	for (int s = 1; s <= n; s++) {
		lo[0][s] = 0;
		for (int i = 1; i < n; i++) {
			lo[i][s] = i;
			if (lcp[i] >= s) lo[i][s] = lo[i - 1][s];
		}
		hi[n - 1][s] = n - 1;
		for (int i = n - 2; i >= 0; i--) {
			hi[i][s] = i;
			if (lcp[i + 1] >= s) hi[i][s] = hi[i + 1][s];
		}
	}

	vector st(n, segtree(n));
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (sa[j] > i) continue;
			st[i].update(j, sa[j]);
		}
	}

	vector dp(n, vector(n + 1, 1));
	int res = n + 1;
	for (int i = 0; i < n; i++) {
		for (int s = 1; i < n - s + 1; s++) {
			if (i < s) break;
			int l = lo[rsa[i]][s];
			int r = hi[rsa[i]][s];
			int x = st[i - s].query(l, r);
			if (x != -1) dp[i][s] = dp[x][s] + 1;
			res = min(res, n - (s - 1) * dp[i][s] + s);
		}
	}
	return res;
};

int main() {
	fastio;
	string s; cin >> s;
	cout << sol(s) << '\n';
}