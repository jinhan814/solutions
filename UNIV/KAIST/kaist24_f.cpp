#include <bits/stdc++.h>
using namespace std;

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int tc; cin >> tc;
	while (tc--) {
		int n; cin >> n;
		int res = 0;
		for (int i = 0; i < n; i++) {
			int x; cin >> x;
			if (i == 0) continue;
			if (x == 111) res ^= 2;
			if (x == 110 || x == 11) res ^= 1;
		}
		cout << (!res ? "Nono" : "Yesyes") << '\n';
	}
}