#include <bits/stdc++.h>
using namespace std;

struct segtree {
	segtree(int n) : sz(1 << __lg(n - 1) + 1), tree(sz << 1, 1 << 30) {}
	void update(int l, int r, int x) {
		for (l |= sz, r |= sz; l <= r; l >>= 1, r >>= 1) {
			if (l & 1) tree[l] = min(tree[l], x), l++;
			if (~r & 1) tree[r] = min(tree[r], x), r--;
		}
	}
	int query(int i) const {
		int ret = tree[i |= sz];
		while (i >>= 1) ret = min(ret, tree[i]);
		return ret;
	}
private:
	int sz;
	vector<int> tree;
};

auto calc = [](const string& s) {
	const int n = s.size();
	vector z(n, 0); z[0] = n;
	for (int i = 1, l = -1, r = -1; i < n; i++) {
		if (i <= r) z[i] = min(r - i + 1, z[i - l]);
		while (i + z[i] < n && s[z[i]] == s[i + z[i]]) z[i]++;
		if (r < i + z[i] - 1) l = i, r = i + z[i] - 1;
	}
	return z;
};

auto sol = [](string s, string t) {
	auto z = calc(t + s);
	segtree dp(s.size() + 1);
	dp.update(0, 0, 0);
	for (int i = 0; i < s.size(); i++) {
		int val = dp.query(i);
		if (val >> 30) continue;
		int sz = min(z[i + t.size()], (int)t.size());
		dp.update(i + 1, i + sz, val + 1);
	}
	int ret = dp.query(s.size());
	if (ret >> 30) ret = -1;
	return ret;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int tc; cin >> tc;
	for (int tc_num = 1; tc_num <= tc; tc_num++) {
		string s, t; cin >> s >> t;
		cout << "Case #" << tc_num << '\n';
		cout << sol(s, t) << '\n';
	}
}