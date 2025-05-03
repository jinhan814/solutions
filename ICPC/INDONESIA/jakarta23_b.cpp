#include <bits/stdc++.h>
using namespace std;

auto f = [](const string& s) {
	int a = 0, b = 0, p = 0;
	for (char c : s) { if (c & 1) p ^= 1; p ? a++ : b++; }
	return pair(a, b);
};

auto sol = [](const string& s, const string& t) -> bool {
	auto [a1, b1] = f(s);
	auto [a2, b2] = f(t);
	if (a1 == a2 && b1 == b2) return 1;
	if (b1 + 1 == a2 && a1 - 1 == b2) return 1;
	return 0;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int N; cin >> N;
	while (N--) {
		int n; cin >> n;
		string s, t; cin >> s >> t;
		cout << (sol(s, t) ? "YES" : "NO") << '\n';
	}
}