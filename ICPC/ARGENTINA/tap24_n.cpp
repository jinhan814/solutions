#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

int main() {
	fastio;
	int n; cin >> n;
	int mn = 1 << 30, mx = 0;
	for (int i = 0; i < n; i++) {
		int x; cin >> x;
		mn = min(mn, x);
		mx = max(mx, x);
	}
	cout << 1LL * (mx - mn) * (mx - mn) << '\n';
}