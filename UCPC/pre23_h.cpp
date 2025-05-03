#include <bits/stdc++.h>
using namespace std;

auto calc = [](string s) {
	vector res(0, tuple(0, 0, ' ', ' '));
	auto f = [&](int i) {
		res.push_back({ 1, i, s[i - 1], s[i] });
		s[i - 1] = 'R' ^ 'G' ^ 'B' ^ s[i - 1] ^ s[i];
		s.erase(s.begin() + i);
	};
	auto g = [&](int i, char x, char y) {
		res.push_back({ 2, i, x, y });
		s[i - 1] = x;
		s.insert(s.begin() + i, y);
	};
	for (int i = 1; i < s.size();) {
		if (i == 0 || s[i - 1] == s[i]) i++;
		else f(i--);
	}
	while (s.size() > 2) {
		g(3, "RG"[s[0] == 'R'], "BG"[s[0] == 'B']);
		f(2);
		f(1);
		f(1);
	}
	if (s.size() == 2 && s[0] != 'R') {
		g(2, "BG"[s[0] == 'B'], 'R');
		f(1);
	}
	res.push_back({ s[0], s.size() > 1 ? s[1] : 0, 0, 0 });
	return res;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	string a; cin >> a >> a;
	string b; cin >> b >> b;
	auto ra = calc(a);
	auto rb = calc(b);
	if (ra.back() != rb.back()) return cout << -1 << '\n', 0;
	ra.pop_back();
	for (int i = rb.size() - 2; i >= 0; i--) {
		auto [t, a, b, c] = rb[i];
		ra.push_back({ t ^ 3, a, b, c });
	}
	cout << ra.size() << '\n';
	for (auto [t, a, b, c] : ra) {
		if (t == 1) cout << 1 << ' ' << a << ' ' << a + 1 << '\n';
		else cout << 2 << ' ' << a << ' ' << b << ' ' << c << '\n';
	}
}