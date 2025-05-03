#include <bits/stdc++.h>
using namespace std;

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int h, m; cin >> h >> m; m += 60 * h;
	int n; cin >> n;
	int res = 0;
	for (int i = 0; i < n; i++) {
		int a, b; cin >> a >> b; a = min(a, m);
		res += a * b, m -= a;
	}
	cout << res << '\n';
}