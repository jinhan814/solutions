#include <bits/stdc++.h>
using namespace std;

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int N; cin >> N;
	while (N--) {
		int n; cin >> n;
		double ang = (n - 2) * acos(-1) / n;
		double res = 1e4 / (1 - (1 - cos(ang)) / 2);
		cout << fixed << setprecision(5);
		cout << res << '\n';
	}
}