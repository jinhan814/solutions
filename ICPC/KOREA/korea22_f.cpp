#include <bits/stdc++.h>
using namespace std;

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n, q; cin >> n >> q;
	vector psum(n, 0);
	for (int i = 0, p = 0; i < n; i++) {
		int l, r; cin >> l >> r;
		if (i) psum[i] = psum[i - 1];
		if (p < l) psum[i] += l - p;
		p = max(p, r);
	}
	auto res = 0LL;
	for (int i = 0, p = 0; i < q; i++) {
		int x; cin >> x; --x;
		res += abs(psum[p] - psum[x]);
		p = x;
	}
	cout << res << '\n';
}