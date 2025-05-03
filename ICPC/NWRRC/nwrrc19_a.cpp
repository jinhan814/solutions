#include <bits/stdc++.h>
using namespace std;

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int a, b, c; cin >> a >> b >> c;
	int res = (c - a - 1) / (b - a);
	cout << 2 * res + 1 << '\n';
}