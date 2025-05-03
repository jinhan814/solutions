#include <bits/stdc++.h>
using namespace std;

auto sol = [](auto a, auto b) -> bool {
	auto rotate = [](const auto& v) {
		vector ret = v;
		for (int i = 0; i < 9; i++) {
			for (int j = 0; j < 9; j++)
				ret[i][j] = v[j][8 - i];
		}
		return ret;
	};

	auto trans = [](const auto& v) {
		vector ret = v;
		for (int i = 0; i < 9; i++) {
			for (int j = 0; j < 9; j++)
				ret[i][j] = v[j][i];
		}
		return ret;
	};

	auto check = [&](int lim) -> bool {
		vector ca(10, 0), cb(10, 0);
		int ta = 0, tb = 0;
		for (int i = 0; i < 9; i++) {
			for (int j = 0; j < lim; j++) {
				if (!b[j][i]) continue;
				if (ca[a[i][j]] ^ cb[b[j][i]]) return 0;
				if (!ca[a[i][j]]) ca[a[i][j]] = ++ta;
				if (!cb[b[j][i]]) cb[b[j][i]] = ++tb;
				if (ca[a[i][j]] != cb[b[j][i]]) return 0;
			}
		}
		return 1;
	};

	auto perm_col = [&](const auto& self, int x) -> bool {
		if (x == 4) return 1;
		if (x == 0) {
			if (self(self, x + 1)) return 1; // abc
			swap(b[3], b[6]); swap(b[4], b[7]); swap(b[5], b[8]);
			if (self(self, x + 1)) return 1; // acb
			swap(b[0], b[3]); swap(b[1], b[4]); swap(b[2], b[5]);
			if (self(self, x + 1)) return 1; // cab
			swap(b[3], b[6]); swap(b[4], b[7]); swap(b[5], b[8]);
			if (self(self, x + 1)) return 1; // cba
			swap(b[0], b[3]); swap(b[1], b[4]); swap(b[2], b[5]);
			if (self(self, x + 1)) return 1; // bca
			swap(b[3], b[6]); swap(b[4], b[7]); swap(b[5], b[8]);
			if (self(self, x + 1)) return 1; // bac
			swap(b[0], b[3]); swap(b[1], b[4]); swap(b[2], b[5]);
			return 0;
		}
		else {
			if (check(3 * x) && self(self, x + 1)) return 1; // abc
			swap(b[3 * (x - 1) + 1], b[3 * (x - 1) + 2]);
			if (check(3 * x) && self(self, x + 1)) return 1; // acb
			swap(b[3 * (x - 1) + 0], b[3 * (x - 1) + 1]);
			if (check(3 * x) && self(self, x + 1)) return 1; // cab
			swap(b[3 * (x - 1) + 1], b[3 * (x - 1) + 2]);
			if (check(3 * x) && self(self, x + 1)) return 1; // cba
			swap(b[3 * (x - 1) + 0], b[3 * (x - 1) + 1]);
			if (check(3 * x) && self(self, x + 1)) return 1; // bca
			swap(b[3 * (x - 1) + 1], b[3 * (x - 1) + 2]);
			if (check(3 * x) && self(self, x + 1)) return 1; // bac
			swap(b[3 * (x - 1) + 0], b[3 * (x - 1) + 1]);
			return 0;
		}
	};

	auto perm_row = [&](const auto& self, int x) -> bool {
		if (x == 4) return perm_col(perm_col, 0);
		if (x == 0) {
			if (self(self, x + 1)) return 1; // abc
			swap(a[3], a[6]); swap(a[4], a[7]); swap(a[5], a[8]);
			if (self(self, x + 1)) return 1; // acb
			swap(a[0], a[3]); swap(a[1], a[4]); swap(a[2], a[5]);
			if (self(self, x + 1)) return 1; // cab
			swap(a[3], a[6]); swap(a[4], a[7]); swap(a[5], a[8]);
			if (self(self, x + 1)) return 1; // cba
			swap(a[0], a[3]); swap(a[1], a[4]); swap(a[2], a[5]);
			if (self(self, x + 1)) return 1; // bca
			swap(a[3], a[6]); swap(a[4], a[7]); swap(a[5], a[8]);
			if (self(self, x + 1)) return 1; // bac
			swap(a[0], a[3]); swap(a[1], a[4]); swap(a[2], a[5]);
			return 0;
		}
		else {
			if (self(self, x + 1)) return 1; // abc
			swap(a[3 * (x - 1) + 1], a[3 * (x - 1) + 2]);
			if (self(self, x + 1)) return 1; // acb
			swap(a[3 * (x - 1) + 0], a[3 * (x - 1) + 1]);
			if (self(self, x + 1)) return 1; // cab
			swap(a[3 * (x - 1) + 1], a[3 * (x - 1) + 2]);
			if (self(self, x + 1)) return 1; // cba
			swap(a[3 * (x - 1) + 0], a[3 * (x - 1) + 1]);
			if (self(self, x + 1)) return 1; // bca
			swap(a[3 * (x - 1) + 1], a[3 * (x - 1) + 2]);
			if (self(self, x + 1)) return 1; // bac
			swap(a[3 * (x - 1) + 0], a[3 * (x - 1) + 1]);
			return 0;
		}
	};

	b = trans(b);
	for (int i = 0; i < 2; i++) {
		if (perm_row(perm_row, 0)) return 1;
		a = rotate(a);
	}
	return 0;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int tc; cin >> tc;
	while (tc--) {
		vector a(9, string{});
		vector b(9, string{});
		for (int i = 0; i < 9; i++) cin >> a[i];
		for (int i = 0; i < 9; i++) cin >> b[i];
		for (int i = 0; i < 9; i++) for (char& c : a[i]) c -= 48;
		for (int i = 0; i < 9; i++) for (char& c : b[i]) c -= 48;
		cout << (sol(a, b) ? "Yes" : "No") << '\n';
	}
}