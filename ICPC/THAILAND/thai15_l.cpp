#include <bits/stdc++.h>
using namespace std;

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n; cin >> n;
	vector v(3, 0);
	for (int i = 0; i < n; i++) {
		for (int& x : v) { int t; cin >> t; x += t; }
		int mn = *min_element(v.begin(), v.end());
		if (mn < 30) { cout << "NO" << '\n'; continue; }
		for (int& x : v) x -= mn;
		cout << mn << '\n';
	}
}