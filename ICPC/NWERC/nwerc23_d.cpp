#include <bits/stdc++.h>
using namespace std;

int main() {
	cin.tie(0)->sync_with_stdio(0);
	vector v(7, string{});
	for (int i = 0; i < 7; i++) cin >> v[i];
	int a, b; cin >> a >> b;

	auto calc = [&](int s) {
		int r = 0, c[24]{};
		for (int i = 0; i < 7; i++) {
			if (~s >> i & 1) continue;
			for (int j = 0; j < 24; j++) if (v[i][j] == '.') c[j]++;
			r++;
		}
		sort(c, c + 24, greater{});
		return r < a ? -1. : 1. * reduce(c, c + b) / (r * b);
	};

	double opt = 0;
	for (int s = 1; s < 1 << 7; s++) opt = max(opt, calc(s));
	cout << fixed << setprecision(20);
	cout << opt << '\n';
}