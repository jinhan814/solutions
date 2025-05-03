#include <bits/stdc++.h>
using namespace std;

auto sol = [](int n, auto v) {
	int res = 0;
	vector cnt(5, 0);
	for (int i = 0; i < n; i++) {
		res += v[i] / 5 * 5;
		cnt[v[i] % 5]++;
	}
	while (cnt[3] && cnt[4]) {
		cnt[3]--;
		cnt[4]--;
		res += 5;
	}
	while (cnt[3] >= 2) {
		cnt[3] -= 2;
		res += 5;
	}
	while (cnt[4] >= 3) {
		cnt[4] -= 3;
		res += 10;
	}
	res += cnt[3] * 3;
	res += cnt[4] * 4;
	return res;
};

auto conv = [](int n) {
	string a = to_string(n / 100);
	string b = to_string(n % 100);
	while (b.size() < 2) b = "0" + b;
	return a + "." + b;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n; cin >> n;
	vector v(n, 0);
	for (int i = 0; i < n; i++) {
		string s; cin >> s;
		s.erase(s.end() - 3);
		v[i] = stoi(s);
	}
	cout << conv(sol(n, v)) << '\n';
}