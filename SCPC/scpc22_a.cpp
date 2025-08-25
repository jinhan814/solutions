#include <bits/stdc++.h>
using namespace std;

auto sol = [](int n, auto v) {
	sort(v.begin(), v.end());
	vector buc(0, pair(0., 0));
	for (int i = 0, j = 0; i < n; i = j) {
		while (j < n && abs(v[i] - v[j]) < 1e-9) j++;
		buc.push_back(pair(v[i], j - i));
	}
	vector p(buc.size() + 1, 0.);
	for (int i = 0; i < buc.size(); i++) {
		p[i + 1] = p[i] + buc[i].second;
	}
	double ret = 0, mn = 1e9, mx = -1e9;
	for (int i = 0; i < buc.size(); i++) {
		ret = max(ret, buc[i].first - p[i] / n + mx);
		mn = min(mn, p[i] / n - buc[i].first);
		mx = max(mx, p[i + 1] / n - buc[i].first);
		ret = max(ret, p[i + 1] / n - buc[i].first - mn);
	}
	return ret;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	cout << fixed << setprecision(20);
	int tc; cin >> tc;
	for (int tc_num = 1; tc_num <= tc; tc_num++) {
		int n; cin >> n;
		vector v(n, 0.);
		for (int i = 0; i < n; i++) cin >> v[i];
		cout << "Case #" << tc_num << '\n';
		cout << sol(n, v) << '\n';
	}
}