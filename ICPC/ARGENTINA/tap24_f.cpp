#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

int main() {
	fastio;
	int n; cin >> n;
	vector v(n, 0);
	for (int i = 0; i < n; i++) cin >> v[i];
	int res = 0;
	for (int i = 0; i < n; i++) {
		res += v[i] ? 1 : -1;
		if (i > 1 && v[i - 2] == 1 && v[i - 1] == 1 && v[i] == 1) res++;
	}
	cout << res << '\n';
}