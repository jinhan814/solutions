#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

int main() {
	fastio;
	int N; cin >> N;
	while (N--) {
		int n, k; cin >> n >> k;
		int res = 0, x;
		while (n--) cin >> x, res |= x;
		cout << res << '\n';
	}
}