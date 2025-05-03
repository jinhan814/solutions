#include <bits/stdc++.h>
using namespace std;

auto sol = [](auto a, auto b) -> bool {
	auto parity = [](const auto& s) {
		int mask = 0;
		for (char c : s) mask ^= 1 << c - 'A';
		return mask;
	};
	auto conv = [](const auto& s) {
		string res;
		for (char c : s) {
			if (c == 'B') continue;
			if (res.size() && res.back() == c) res.pop_back();
			else res.push_back(c);
		}
		return res;
	};
	return parity(a) == parity(b) && conv(a) == conv(b);
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int N; cin >> N;
	while (N--) {
		string a, b; cin >> a >> b;
		cout << (sol(a, b) ? "YES" : "NO") << '\n';
	}
}