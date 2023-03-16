#include <cstdio>
#include <cmath>

using namespace std;

int c[22];
int main() {
	int n, m;
	scanf("%d %d", &n, &m);
	c[0] = 1;
	for(int i = 1; i <= n; ++i) {
		scanf("%d", &c[i]);
		c[i] *= c[i-1];
	}
	int b, back = 0;
	for(int i = 1; i <= n; ++i) {
		b = (m%c[i] - back)/c[i-1];
		printf("%d ", b);
	}
	return 0;
}