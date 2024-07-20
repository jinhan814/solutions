#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

int main() {
	fastio;
	int d, a, b; cin >> d >> a >> b;
	int t = (d + 1) * (d + 1) + 4 * (9 + a + b - d * (d + 1) / 2);
	double x = (-(d + 1) + sqrt(t)) / 2;
	int res = x * (x + 1) / 2 - 3 - b + 0.5;
	cout << res << '\n';
}