#include <bits/stdc++.h>
using namespace std;

constexpr double PI = 3.1415926535;

auto sol = [] {
	int l = -(1 << 30), r = 1 << 30;
	for (int i = 1; i < 100000; i++) {
		int x = -(1 << 30) + i;
		if (sin(l) < sin(x)) l = x;
	}
	for (int i = 1; i < 100000; i++) {
		int x = (1 << 30) - i;
		if (sin(r) < sin(x)) r = x;
	}
	vector buc(0, 0);
	while (buc.size() < 50'000) {
		if (sin(l) < sin(r)) {
			buc.push_back(r);
			int opt = -1;
			for (int i = 1; i < 250; i++) {
				int j = r - PI * i;
				if (sin(r) < sin(j)) continue;
				if (opt == -1 || sin(opt) < sin(j)) opt = j;
			}
			r = opt;
		}
		else {
			buc.push_back(l);
			int opt = -1;
			for (int i = 1; i < 250; i++) {
				int j = l + PI * i;
				if (sin(l) < sin(j)) continue;
				if (opt == -1 || sin(opt) < sin(j)) opt = j;
			}
			l = opt;
		}
	}
	return buc;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n; cin >> n;
	auto res = sol();
	for (int i = 0; i < n; i++) cout << res[i] << '\n';
}