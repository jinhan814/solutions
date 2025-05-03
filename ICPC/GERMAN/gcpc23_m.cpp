#include <bits/stdc++.h>
using namespace std;

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n; cin >> n;

	auto f = [](int a, int b, int c) {
		if (a == -1 || b == -1) return -1;
		if (c == 0) return a + b;
		if (c == 1) return a - b;
		if (c == 2) return a * b;
		if (c == 3) return b && a % b == 0 ? a / b : -1;
	};

	auto check = [&](int a, int b, int c) -> bool {
		for (int k = 0; k < 6; k++) {
			if (a == n || b == n || c == n) return 0;
			for (int i = 0; i < 4; i++) {
				if (f(a, b, i) == n) return 0;
				if (f(a, c, i) == n) return 0;
				if (f(b, c, i) == n) return 0;
				for (int j = 0; j < 4; j++) {
					if (f(f(a, b, i), c, j) == n) return 0;
					if (f(a, f(b, c, i), j) == n) return 0;
				}
			}
			swap(a, k & 1 ? b : c);
		}
		return 1;
	};

	for (int a = 1; a <= 100; a++) {
		for (int b = a + 1; b <= 100; b++) {
			for (int c = b + 1; c <= 100; c++) {
				if (!check(a, b, c)) continue;
				cout << a << ' ' << b << ' ' << c << '\n';
				return 0;
			}
		}
	}
}