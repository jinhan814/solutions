#include <bits/stdc++.h>
using namespace std;

auto get_fail = [](const string& s) {
	vector f(s.size(), 0);
	for (int i = 1, j = 0; i < s.size(); i++) {
		while (j && s[i] != s[j]) j = f[j - 1];
		if (s[i] == s[j]) f[i] = ++j;
	}
	return f;
};

auto kmp = [](const string& s, const string& t) {
	vector ret(0, 0), f = get_fail(t);
	for (int i = 0, j = 0; i < s.size(); i++) {
		while (j && s[i] != t[j]) j = f[j - 1];
		if (s[i] == t[j] && ++j == t.size()) {
			ret.push_back(i - j + 1);
			j = f[j - 1];
		}
	}
	return ret;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n; cin >> n;
	vector v(n, string{});
	for (int i = 0; i < n; i++) cin >> v[i];
	string s; cin >> s;

	vector dp1(s.size(), 0);
	for (const auto& t : v) {
		auto f = get_fail(s + t);
		int i = f.size() - 1;
		while (f[i]) {
			i = f[i] - 1;
			if (i < s.size()) dp1[i] = 1;
		}
	}

	vector dp2(s.size(), 0);
	for (const auto& t : v) {
		auto f = get_fail(t + s);
		int i = f.size() - 1;
		while (f[i]) {
			i = f[i] - 1;
			if (i < s.size()) dp2[s.size() - 1 - i] = 1;
		}
	}

	vector buc(s.size(), vector(0, 0));
	for (int i = 0; i < n; i++) {
		auto res = kmp(s, v[i]);
		for (int j : res) buc[j].push_back(v[i].size());
	}

	vector dp = dp1;
	for (int i = 0; i < s.size(); i++) {
		if (i && !dp[i - 1]) continue;
		for (int x : buc[i]) dp[i + x - 1] = 1;
	}

	bool res = 0;
	for (int i = 0; i < s.size(); i++) {
		if (!dp[i]) continue;
		if (i + 1 < s.size() && !dp2[i + 1]) continue;
		res = 1;
	}
	cout << (res ? "YES" : "NO") << '\n';
}