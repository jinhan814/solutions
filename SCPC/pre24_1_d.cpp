#include <bits/stdc++.h>
using namespace std;

auto sol = [](int n, int m, auto a, auto b) {
	sort(a.begin(), a.end());
	sort(b.begin(), b.end());
	int pl = 0, pr = n - 1;
	while (pl < n && abs(a[pl] - b[pl]) <= m) pl++;
	while (pr >= 0 && abs(a[pr] - b[pr]) <= m) pr--;
	int ret = -1;
	for (int i = 1, j = 0; i < n; i++) {
		if (abs(a[i - 1] - b[i]) > m) j = i;
		while (j < i && abs(a[i] - b[j]) > m) j++;
		if (i < pr) continue;
		if (j > pl) continue;
		int val = abs(a[i] - b[j]);
		if (val <= m) ret = max(ret, val);
	}
	for (int i = n - 2, j = n - 1; i >= 0; i--) {
		if (abs(a[i + 1] - b[i]) > m) j = i;
		while (i < j && abs(a[i] - b[j]) > m) j--;
		if (i > pl) continue;
		if (j < pr) continue;
		int val = abs(a[i] - b[j]);
		if (val <= m) ret = max(ret, val);
	}
	return ret;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int tc; cin >> tc;
	for (int tc_num = 1; tc_num <= tc; tc_num++) {
		int n, m; cin >> n >> m;
		vector a(n, 0), b(n, 0);
		for (int i = 0; i < n; i++) cin >> a[i];
		for (int i = 0; i < n; i++) cin >> b[i];
		cout << "Case #" << tc_num << '\n';
		cout << sol(n, m, a, b) << '\n';
	}
}