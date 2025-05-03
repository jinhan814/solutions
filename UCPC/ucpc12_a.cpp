#include <bits/stdc++.h>
using namespace std;

struct erasable_heap {
	void push(int x) { pq.push(x); }
	void pop(int x) { buc.push(x); }
	bool empty() { return norm(), pq.empty(); }
	int top() { return norm(), pq.top(); }
private:
	priority_queue<int> pq, buc;
	void norm() {
		while (buc.size() && pq.top() == buc.top()) {
			pq.pop();
			buc.pop();
		}
	}
};

auto sol = [](int n, int k, auto a, auto b) {
	vector pq(10, erasable_heap{});
	int res = 0;
	for (int i = 0; i < n; i++) {
		pq[a[i]].push(b[i]);
		if (i >= k) pq[a[i - k]].pop(b[i - k]);
		int acc = 0;
		for (int x = 1; x <= 9; x++) {
			if (pq[x].empty()) { acc = 0; break; }
			acc += pq[x].top();
		}
		res = max(res, acc);
	}
	return res;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int tc; cin >> tc;
	while (tc--) {
		int n, k; cin >> n >> k;
		vector a(n, 0), b(n, 0);
		for (int i = 0; i < n; i++) cin >> a[i] >> b[i];
		cout << sol(n, k, a, b) << '\n';
	}
}