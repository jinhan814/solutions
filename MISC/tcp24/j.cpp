#include <bits/stdc++.h>
using namespace std;

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n; cin >> n;
	vector a(n, 0), b(n, 0);
	for (int i = 0; i < n; i++) cin >> a[i];
	for (int i = 0; i < n; i++) cin >> b[i];

	vector buc(30, vector(0, 0));
	for (int bit = 0; bit < 30; bit++) {
		for (int i = 0; i < n; i++) {
			if (~b[i] >> bit & 1) continue;
			buc[bit].push_back(i);
		}
		buc[bit].push_back(n);
	}

	vector psum(n + 1, 0LL);
	for (int i = 0; i < n; i++) {
		psum[i + 1] = psum[i] + 1LL * a[i] * a[i];
	}

	auto calc = [&](int l, int r, int x) {
		int lo = l - 1, hi = r + 1;
		while (lo + 1 < hi) {
			int mid = lo + hi >> 1;
			if (psum[mid + 1] - psum[l] < 1LL * x * x) lo = mid;
			else hi = mid;
		}
		return lo;
	};

	vector pos(30, 0);
	auto res = 0LL;
	for (int i = 0; i < n; i++) {
		vector v(0, 0);
		for (int bit = 0; bit < 30; bit++) {
			int& j = pos[bit];
			while (buc[bit][j] < i) j++;
			v.push_back(buc[bit][j]);
		}
		sort(v.begin(), v.end());
		v.erase(unique(v.begin(), v.end()), v.end());
		for (int j = 0; j + 1 < v.size(); j++) {
			int l = v[j];
			int r = v[j + 1] - 1;
			int x = b[i] |= b[l];
			int k = calc(i, r, x);
			if (l <= k) res += k - l + 1;
		}
	}
	cout << res << '\n';
}