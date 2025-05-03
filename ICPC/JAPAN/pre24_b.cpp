#include <bits/stdc++.h>
using namespace std;

int main() {
	cin.tie(0)->sync_with_stdio(0);
	while (1) {
		int n; cin >> n;
		if (!n) break;
		vector a(n, 0), b(n, 0);
		for (int i = 0; i < n; i++) cin >> a[i];
		for (int i = 0; i < n; i++) cin >> b[i];
		int res = 0, prv = 0;
		for (int i = 0; i < n; i++) {
			if (i) a[i] += a[i - 1], b[i] += b[i - 1];
			if (a[i] == b[i]) continue;
			int cur = a[i] > b[i] ? 1 : 2;
			if (prv && prv != cur) res++;
			prv = cur;
		}
		cout << res << '\n';
	}
}