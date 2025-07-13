#include <bits/stdc++.h>
using namespace std;

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int a, b, c, d; cin >> a >> b >> c >> d;
	int res = a + b + c + d + 300;
	cout << (res <= 1800 ? "Yes" : "No") << '\n';
}