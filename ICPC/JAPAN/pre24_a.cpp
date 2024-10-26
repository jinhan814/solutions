#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

int main() {
	fastio;
	while (1) {
		int n; cin >> n;
		if (!n) break;
		int res = 0;
		while (n--) {
			int x; cin >> x;
			if (res + x <= 300) res += x;
		}
		cout << res << '\n';
	}
}