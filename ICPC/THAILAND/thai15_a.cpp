#include <bits/stdc++.h>
using namespace std;

auto sol = [](auto s) {
	string ret;
	auto f = [](char c) { return c < 58 ? c - 48 : c - 55; };
	for (int i = 0; i < s.size(); i += 2) {
		int a = f(s[i]);
		int b = f(s[i + 1]);
		ret.push_back(a << 4 | b);
	}
	return ret;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	string s;
	while (cin >> s) cout << sol(s) << '\n';
}