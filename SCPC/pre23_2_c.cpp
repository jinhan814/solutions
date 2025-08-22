#include <bits/stdc++.h>
using namespace std;

auto sol = [](int n, int m, int k, auto v) {
	vector l(n, 0), r(n, 0);
	for (int i = 0, j = 0; i < n; i = j) {
		while (j < n && v[i] == v[j]) j++;
		for (int p = i; p < j; p++) l[p] = i, r[p] = j - 1;
	}
	vector f(n, 0);
	for (int i = 0; i < n - 1; i++) {
		if (v[i + 1] != 1) continue;
		f[i] = min(r[i + 1] - i, k);
	}
	vector dp(n, 1);
	for (int i = 1; i < n; i++) {
		if (v[i - 1] != 1) continue;
		dp[i] += min(i - l[i - 1], k);
	}
	for (int iter = 2; iter <= m; iter++) {
		vector mx(n, 0);
		deque buc(0, pair(0, 0));
		for (int i = 0, p = -1; i < n; i++) {
			mx[i] = dp[i] + f[i];
			if (i) mx[i] = max(mx[i], mx[i - 1]);
			while (buc.size() && buc.back().first <= dp[i] - i) buc.pop_back();
			buc.push_back(pair(dp[i] - i, i));
			int len = v[i - 1] != 1 ? 0 : i - l[i - 1];
			int val = min(len, k);
			while (p < i) {
				int j = p + 1;
				if (len >= k ?
					j + f[j] < i - k :
					r[j + 1] < i - len - 2 ||
					j + f[j] < i - len - 2 ||
					i - len - 1 - j > k) p++;
				else break;
			}
			if (p >= 0) {
				dp[i] = max(dp[i], mx[p] + val + 1);
			}
			if (p + 1 < i) {
				while (buc[0].second < p + 1) buc.pop_front();
				dp[i] = max(dp[i], buc[0].first + i);
			}
		}
	}
	int ret = 0;
	for (int i = 0; i < n; i++) ret = max(ret, dp[i] + f[i]);
	return ret;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int tc; cin >> tc;
	for (int tc_num = 1; tc_num <= tc; tc_num++) {
		int n; cin >> n;
		vector v(n, 0);
		for (int i = 0; i < n; i++) cin >> v[i];
		int m, k; cin >> m >> k;
		cout << "Case #" << tc_num << '\n';
		cout << sol(n, m, k, v) << '\n';
	}
}