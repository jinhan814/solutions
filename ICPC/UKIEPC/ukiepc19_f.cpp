#include <bits/stdc++.h>
using namespace std;

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n, k; cin >> n >> k;
	vector v(n, 0);
	for (int i = 0; i < n; i++) cin >> v[i];
	sort(v.begin(), v.end());
	int res = 0;
	for (int l = 0, r = n - 1; l <= r; res++) {
		if (l < r && v[l] + v[r] <= k) l++;
		r--;
	}
	cout << res << '\n';
}