#include <bits/stdc++.h>
using namespace std;

int main() {
	cin.tie(0)->sync_with_stdio(0);
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