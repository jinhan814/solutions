#include <bits/stdc++.h>
using namespace std;

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n; cin >> n;
	int a = (n - 1) % 14 % 12;
	int b = (a & 1 ? 1 : 2) + (n - 1) / 14;
	vector s{ "baby", "sukhwan", "very", "cute", "in", "bed" };
	if (~a & 2) cout << s[a + 1 >> 1];
	else {
		cout << "tu";
		while (b && b < 5) cout << "ru", b--;
		if (b > 4) cout << "+ru*" << b;
	}
}