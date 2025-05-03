#include <bits/stdc++.h>
using namespace std;

auto sol = [](int n, string s) {
	vector cnt(3, 0);
	for (char c : s) cnt[c - 65]++;
	int ab = n - cnt[2], ac = n - cnt[1], bc = n - cnt[0];
	if (ab < 0 || ac < 0 || bc < 0) return vector(0, pair(0, 0));
	vector res(0, pair(0, 0));
	vector c(2 * n, 0);
	for (int i = 0, j = 0; i < 2 * n && bc; i++) {
		if (s[i] != 'B') continue;
		if (j < i) j = i;
		while (j < 2 * n && s[j] != 'C') j++;
		if (j >= 2 * n) return vector(0, pair(0, 0));
		res.push_back({ i, j });
		c[j++] = 1;
		bc--;
	}
	for (int i = 2 * n - 1, j = 2 * n - 1; i >= 0 && ab; i--) {
		if (s[i] != 'B') continue;
		if (j > i) j = i;
		while (j >= 0 && s[j] != 'A') j--;
		if (j < 0) return vector(0, pair(0, 0));
		res.push_back({ j, i });
		c[j--] = 1;
		ab--;
	}
	for (int i = 0, j = 0; i < 2 * n && ac; i++) {
		if (s[i] != 'A' || c[i]) continue;
		if (j < i) j = i;
		while (j < 2 * n && (s[j] != 'C' || c[j])) j++;
		if (j >= 2 * n) return vector(0, pair(0, 0));
		res.push_back({ i, j });
		j++;
		ac--;
	}
	for (auto& [a, b] : res) a++, b++;
	return res;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n; cin >> n;
	string s; cin >> s;
	auto res = sol(n, s);
	if (res.empty()) {
		cout << "NO" << '\n';
	}
	else {
		cout << "YES" << '\n';
		for (auto [a, b] : res) cout << a << ' ' << b << '\n';
	}
}