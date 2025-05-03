#include <bits/stdc++.h>
using namespace std;

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n, k; cin >> n >> k;
	string s; cin >> s;

	vector c1(n + 1, 0), c2(n + 1, 0);
	for (int i = 0, x = 0; i < 2 * n; i++) {
		x += s[i] & 1 ? 1 : -1;
		if (x > 0) c1[x]++;
		if (x < 0) c2[-x]++;
	}

	vector a(n + 1, 0LL), b(n + 1, 0LL);
	for (int i = n - 1; i >= 0; i--) {
		a[i] = a[i + 1] + c1[i + 1];
		b[i] = b[i + 1] + c2[i + 1];
		if (i > 1) c1[i - 1] += c1[i + 1], c2[i - 1] += c2[i + 1];
	}

	auto res = 1LL << 60;
	for (int i = 0; i <= k; i++) res = min(res, a[i] + b[k - i]);
	cout << res << '\n';
}