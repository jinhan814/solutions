#include <bits/stdc++.h>
using namespace std;

auto sol_alt = [](string s) {
	const int n = s.size();
	int res1 = 0, res2 = 0;
	string t1(n, 0), t2(n, 0);
	for (int i = 0; i < n; i++) {
		t1[i] = i & 1 ? 48 : 49;
		t2[i] = i & 1 ? 49 : 48;
		if (s[i] != t1[i]) res1++;
		if (s[i] != t2[i]) res2++;
	}
	if (res1 > res2) {
		swap(res1, res2);
		swap(t1, t2);
	}
	return pair(res1, t1);
};

auto sol = [](int k, string s) {
	if (k == 2) return sol_alt(s);
	const int n = s.size();
	vector v(0, pair(0, 0));
	for (int l = 0, r = 0; l < n; l = r) {
		while (r < n && s[l] == s[r]) r++;
		v.push_back({ l, r - 1 });
	}
	int res = 0;
	for (auto [l, r] : v) {
		if (r - l + 1 < k) continue;
		l += k - 1;
		while (l < r) res++, s[l] ^= 1, l += k;
		if (l == r) res++, s[r - 1] ^= 1;
	}
	return pair(res, s);
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int k; cin >> k;
	string s; cin >> s;
	auto [res, t] = sol(k, s);
	cout << res << ' ' << t << '\n';
}