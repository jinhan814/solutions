#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

int main() {
	fastio;
	int tc; cin >> tc;
	while (tc--) {
		int n; cin >> n;
		if (n <= 5) cout << -1 << '\n';
		if (n == 6) cout << 3 << '\n' << 1 << ' ' << 3 << ' ' << 4 << '\n';
		if (n >= 7) cout << 4 << '\n' << 1 << ' ' << 3 << ' ' << n - 3 << ' ' << n - 2 << '\n';
	}
}