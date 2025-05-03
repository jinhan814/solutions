#include <bits/stdc++.h>
using namespace std;

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n; cin >> n;
	vector v(1 << 20, vector(0, string{}));
	for (int i = 0; i < n; i++) {
		int x; cin >> x;
		v[x].push_back(to_string(x));
	}

	if (n == 1 && v[1].size()) {
		cout << 1 << '\n';
		return 0;
	}

	while (v[1].size() >= 2) {
		if (v[2].size() >= 2) {
			for (int i = 0; i < 2; i++) {
				v[3].push_back(v[2].back() + "+1");
				v[1].pop_back();
				v[2].pop_back();
			}
		}
		else {
			v[1].pop_back();
			v[1].pop_back();
			v[2].push_back("1+1");
		}
	}

	if (v[1].size()) {
		int p = 2;
		while (v[p].empty()) p++;
		v[p + 1].push_back(v[p].back() + "+1");
		v[1].pop_back();
		v[p].pop_back();
	}

	bool flag = 0;
	for (auto& buc : v) for (auto& s : buc) {
		if (flag) cout << '*';
		cout << '(' << s << ')';
		flag = 1;
	}
	cout << '\n';
}