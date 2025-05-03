#include <bits/stdc++.h>
using namespace std;

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int N; cin >> N;
	while (N--) {
		int n, k; cin >> n >> k;
		int res = 0, x;
		while (n--) cin >> x, res |= x;
		cout << res << '\n';
	}
}