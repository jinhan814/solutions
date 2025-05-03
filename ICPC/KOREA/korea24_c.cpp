#include <bits/stdc++.h>
using namespace std;

using i16 = short;

struct node {
	i16 sz, v[4];
	i16* begin() { return v; }
	i16* end() { return v + sz; }
	void push(i16 x) {
		if (sz == 4) return;
		for (int i = 0; i < sz; i++) if (v[i] == x) return;
		v[sz++] = x;
	}
	void push(node& val) {
		for (i16 x : val) push(x);
	}
};

bool f(node& a, node& b, node& c, node& d) {
	for (i16 x : a) for (i16 y : b) {
		if (x == y) continue;
		for (i16 z : c) {
			if (x == z || y == z) continue;
			for (i16 k : d) {
				if (x == k || y == k || z == k) continue;
				return 1;
			}
		}
	}
	return 0;
}

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n, k; cin >> n >> k;
	vector v(n, vector(n, i16{}));
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) cin >> v[i][j];
	}
	vector d(n + 1, vector(n, node{}));
	for (int i = n - 1; i >= 2; i--) {
		for (int j = 0; j < n; j++) {
			d[i][j].push(d[i + 1][j]);
			if (v[i][j]) d[i][j].push(v[i][j]);
		}
	}
	vector u(n, node{});
	vector ru(n + 1, node{}), rd(n + 1, node{});
	int res = 0;
	for (int i = 0; i < n - 2; i++) {
		for (int j = 0; j < n; j++) {
			if (v[i][j]) u[j].push(v[i][j]);
		}
		for (int j = n - 1; j >= 2; j--) {
			ru[j] = u[j];
			rd[j] = d[i + 2][j];
			ru[j].push(ru[j + 1]);
			rd[j].push(rd[j + 1]);
		}
		node lu{}, ld{};
		for (int j = 0; j < n - 2; j++) {
			lu.push(u[j]);
			ld.push(d[i + 2][j]);
			if (v[i + 1][j + 1]) continue;
			if (f(lu, ld, ru[j + 2], rd[j + 2])) res++;
		}
	}
	cout << res << '\n';
}