#include <bits/stdc++.h>
using namespace std;

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n; cin >> n;
	while (n--) {
		string s; cin >> s;
		int res = 0;
		for (int i = 0; i < s.size() - 1 - i; i++) {
			int a = s[i];
			int b = s[s.size() - 1 - i];
			res += abs(a - b);
		}
		cout << res << '\n';
	}
}