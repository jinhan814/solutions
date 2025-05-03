#include <bits/stdc++.h>
using namespace std;

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n, k; cin >> n >> k;
	vector v(n, 0);
	for (int i = 0; i < n; i++) cin >> v[i];

	vector occ(k + 1, 0);
	for (int i = 0; i < n; i++) occ[v[i]]++;

	vector c(k + 1, 0);
	int a = 0, b = 0;
	auto push = [&](int x) {
		if (!c[x]++) a++;
		if (c[x] == occ[x]) b++;
	};
	auto pop = [&](int x) {
		if (c[x] == occ[x]) b--;
		if (!--c[x]) a--;
	};

	int res = 1 << 30;
	for (int l = 0, r = 0; l < n;) {
		while (r <= l) push(v[r++]);
		while (r < n && a < k) push(v[r++]);
		if (a == k && !b) res = min(res, r - l);
		pop(v[l++]);
	}
	if (res >> 30) res = 0;
	cout << res << '\n';
}