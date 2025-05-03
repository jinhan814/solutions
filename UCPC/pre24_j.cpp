#include <bits/stdc++.h>
using namespace std;

using i64 = long long;

auto sol = [](int n, string s) {
	i64 res = 0;
	vector buc(0, 0);
	for (int i = 0; i < n; i++) {
		if (s[i] == 'H') continue;
		if (buc.size() && buc.back() + i & 1) {
			res += i - buc.back();
			buc.pop_back();
		}
		else buc.push_back(i);
	}
	return buc.size() ? -1LL : res;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int tc; cin >> tc;
	while (tc--) {
		int n; cin >> n;
		string s; cin >> s;
		cout << sol(n, s) << '\n';
	}
}