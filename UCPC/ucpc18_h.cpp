#include <bits/stdc++.h>
using namespace std;

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n; cin >> n;
	int mn = 1 << 30, mx = -(1 << 30);
	for (int i = 0; i < n; i++) {
		int x; cin >> x;
		mn = min(mn, x);
		mx = max(mx, x);
	}
	if (mx < 0) tie(mn, mx) = pair(-mx, -mn);
	if (mn < 0) cout << 0 << '\n';
	else cout << min(mn, mx - mn) << '\n';
}