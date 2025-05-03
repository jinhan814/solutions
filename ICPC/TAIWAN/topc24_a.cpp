#include <bits/stdc++.h>
using namespace std;

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n; cin >> n;
	int mx = 0;
	vector v(0, 0);
	for (int i = 0; i < n; i++) {
		string s; cin >> s;
		int x; cin >> x;
		if (s == "pig") mx = max(mx, x);
		else v.push_back(x);
	}
	auto res = 1LL * mx;
	for (int x : v) if (x < mx) res += x;
	cout << res << '\n';
}