#include <bits/stdc++.h>
using namespace std;

auto factor = [](int n) {
	vector res(0, pair(0, 0));
	for (int i = 2; i * i <= n; i++) {
		if (n % i) continue;
		int cnt = 0;
		while (n % i == 0) n /= i, cnt++;
		res.push_back({ i, cnt });
	}
	if (n > 1) res.push_back({ n, 1 });
	return res;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n; cin >> n;
	auto v = factor(n);
	cout << v.size() << '\n';
	for (auto [x, _] : v) cout << 1 << ' ' << n / x << '\n';
}