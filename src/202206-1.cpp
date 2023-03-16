#include <cstdio>
#include <cmath>

using namespace std;

int sum[1003];

int main () {
	int n;
	double avg = 0, da = 0, fa = 0;
	scanf("%d", &n);
	for(int i = 0; i < n; ++i) {
		scanf("%d", &sum[i]);
		avg += sum[i];
	}
	avg /= (double)n;
	for(int i = 0; i < n; ++i) {
		da += (sum[i]-avg) * (sum[i]-avg);
	}
	da /= (double)n;
	da = sqrt(da);
	for(int i = 0; i < n; ++i) {
		fa = (sum[i]-avg)/da;
		printf("%.16lf\n", fa);
	}
	return 0;
}