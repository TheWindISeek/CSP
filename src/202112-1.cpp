#include <cstdio>
#include <cstdlib>
#include <cmath>

using namespace std;

int a[202];

int main () {
	//n < N
	// 0 = a0 < a1 < a2 < ... < an < N
	//A = [a0, a1, ..., an]
	//f(x) 序列A中小于等于x的整数里最大的数的下标
	int n, N;
	int sum = 0;
	scanf("%d %d", &n, &N);
	for(int i = 1; i <= n; ++i) {
		scanf("%d", &a[i]);
	}
	for (int i = n; i > 0; --i)
	{
		sum += i * (N - a[i]);
		N = a[i];
	}
	printf("%d", sum);
	return 0;
}