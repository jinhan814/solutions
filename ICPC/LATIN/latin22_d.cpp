#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

int main() {
	fastio;
	int n, x, y; cin >> n >> x >> y;
	for (int i = 0; i < n; i++) {
		char a, b; cin >> a >> b;
		if (a == 'Y' || !y) cout << "Y ", x--, y++;
		else cout << "N ";
		if (b == 'Y' || !x) cout << "Y\n", x++, y--;
		else cout << "N\n";
	}
}