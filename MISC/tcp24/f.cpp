#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

int main() {
	fastio;
	int n; cin >> n;
	while (n--) {
		string s; cin >> s;
		if (s == "BdnaDars") cout << "Enough!" << '\n';
		else cout << "OK" << '\n';
	}
}