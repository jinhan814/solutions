#include <bits/stdc++.h>
using namespace std;

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n; cin >> n;
	vector a(n, 0), b(n, 0);
	for (int i = 0; i < n; i++) cin >> a[i];
	for (int i = 0; i < n; i++) cin >> b[i];
	sort(a.begin(), a.end());
	sort(b.begin(), b.end());

	vector dp1(n, 0);
	for (int i = 1, pre = 0; i < n; i++) {
		pre = max(pre, abs(a[i - 1] - b[i - 1]));
		dp1[i] = min(pre, max(dp1[i - 1], abs(a[i - 1] - b[i])));
	}
	for (int i = n - 2, suf = 0; i >= 0; i--) {
		suf = max(suf, abs(a[i + 1] - b[i + 1]));
		dp1[i] = max(dp1[i], suf);
	}

	vector dp2(n, 0);
	for (int i = n - 2, suf = 0; i >= 0; i--) {
		suf = max(suf, abs(a[i + 1] - b[i + 1]));
		dp2[i] = min(suf, max(dp2[i + 1], abs(a[i + 1] - b[i])));
	}
	for (int i = 1, pre = 0; i < n; i++) {
		pre = max(pre, abs(a[i - 1] - b[i - 1]));
		dp2[i] = max(dp2[i], pre);
	}

	int p = -1, opt = 1 << 30;
	for (int i = 0; i < n; i++) {
		int val = min(dp1[i], dp2[i]);
		if (opt > val) p = i, opt = val;
	}
	cout << a[p] << '\n';
}