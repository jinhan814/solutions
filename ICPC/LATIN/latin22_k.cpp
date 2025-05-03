#include <bits/stdc++.h>
using namespace std;

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n; cin >> n;
	int k = n > 1 ? __lg(n - 1) + 1 : 0;
	vector buc(k, vector(0, pair(0, 0)));
	for (int bit = 0; bit < k; bit++) {
		for (int i = 1; i <= 100; i++) {
			buc[bit].push_back({ i, 100 });
			if (i & 1) continue;
			for (int j = 1; j <= 99; j++) buc[bit].push_back({ i, j });
		}
		for (int i = 0; i <= n - 2; i++) {
			if (~i >> bit & 1) continue;
			int x = i / 99 * 2 + 1, y = i % 99 + 1;
			buc[bit].push_back({ x, y });
		}
	}
	cout << k << '\n';
	for (auto v : buc) {
		cout << v.size();
		for (auto [x, y] : v) cout << ' ' << x << ' ' << y;
		cout << '\n';
	}
}