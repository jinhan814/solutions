#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

int main() {
	fastio;
	int tc; cin >> tc;
	while (tc--) {
		int n; cin >> n;
		auto res = (n / 2) * (n / 2 + 1LL);
		if (n & 1) res += n + 1 >> 1;
		cout << res << '\n';
	}
}