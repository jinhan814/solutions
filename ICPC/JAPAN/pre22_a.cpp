#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

int main() {
	fastio;
	while (1) {
		int n; cin >> n;
		if (!n) break;
		vector v(n, 0);
		for (int i = 0; i < n; i++) cin >> v[i];
		int res = 0;
		for (int i = 1; i < n - 1; i++) {
			if (v[i] > max(v[i - 1], v[i + 1])) res++;
		}
		cout << res << '\n';
	}
}