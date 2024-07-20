#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

int main() {
	fastio;
	int N; cin >> N;
	while (N--) {
		int n, m; cin >> n >> m;
		int a = 0, b = 0;
		for (int i = 0; i < m; i++) {
			int x, y; cin >> x >> y;
			a = max(a, x);
			b = max(b, y);
		}
		if (a + b > n) cout << "IMPOSSIBLE" << '\n';
		else cout << string(a, 'R') << string(n - a, 'W') << '\n';
	}
}