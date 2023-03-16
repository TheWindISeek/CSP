#include <cmath>
#include <cstdio>
#include <algorithm>

using namespace std;


void print (int q[][8]) {
    for(int i = 0; i < 8; ++i) {
        for(int j = 0; j < 8; ++j) {
            printf("%d", q[i][j]);
            if(j != 7) {
                printf(" ");
            }
        }
        if(i != 7)
            printf("\n");
    }
}

void print (double q[][8]) {
    for(int i = 0; i < 8; ++i) {

        for(int j = 0; j < 8; ++j) {
            printf("%lf ", q[i][j]);
        }
        if(i != 7)
            printf("\n");
    }
}

double alpha(int u) {
    if(u == 0)
        return sqrt(0.5);
    return 1;
}

int main()
{
    const double PI = acos(-1);
    const double PI8 = PI/8.0;

    int q[8][8];//量化矩阵
    int m[8][8] = {0};//初始矩阵M
    double mt[8][8];//修改后的矩阵m'
    int mtt[8][8];

    int n, t;

    //读取量化矩阵
    for(int i = 0; i < 8; ++i) {
        for(int j = 0; j < 8; ++j) {
            scanf("%d", &q[i][j]);
        }
    }

    scanf("%d %d", &n, &t);
    for(int i = 0; i < 8; ++i) {
        for(int j = 0; j < 8; ++j) {
            m[i][j] = 0;
        }
    }


    int qq[64] = {0};
    for(int i = 0; i < n; ++i) {
        scanf("%d", &qq[i]);
    }

    int k = 0;
    for (int i = 0; i < 8; i ++ )
        if (i % 2 == 0)
        {
            for (int j = 0; j <= i; j ++ )
                m[i - j][j] = qq[k ++ ];
        }
        else
            for (int j = 0; j <= i; j ++ )
                m[j][i - j] = qq[k ++ ];

    for (int i = 8; i < 15; i ++ )
        if (i % 2 == 0)
            for (int j = i - 7; j <= 7; j ++ )
                m[i - j][j] = qq[k ++ ];
        else
            for (int j = i - 7; j <= 7; j ++ )
                m[j][i - j] = qq[k ++ ];


    /*
    //读取扫描数据
    int f = 1, s = 1;//小心越界
    int i = 0, j = 0;

    //这份代码没有考虑32位之后的情况 所以会出现错误
    for(int k = 0; k < n; ++k) {
        scanf("%d", &m[i][j]);
        //printf("\n输入:%d k:%d\n", m[i][j], k);
        if(i == 7 && j == 7) {//填充满矩阵
            break;
        }
        if(i == 0 && s) { //向右移动 方向反置
            f = 1;//方向向下
            ++j;
            s = 0;
        } else if(j == 0 && s) {
            f = 0;//方向向上
            ++i;//向下移动
            s = 0;
        } else {
            s = 1;
            if(f) { // 方向向下
                ++i;
                --j;
            } else {
                --i;
                ++j;
            }
        }
    }
*/

  // printf("\nt0\n");
  // print(m);
    if(t == 0){
        print(m);
        return 0;
    }

    for(int i = 0; i < 8; ++i) {
        for(int j = 0; j < 8; ++j) {
            m[i][j] = m[i][j] * q[i][j];
        }
    }

  // printf("\nt1\n");
  // print(m);
    if(t == 1){
        print(m);
        return 0;
    }

    //计算新矩阵 M'
    for(int i = 0; i < 8; ++i) {
        for(int j = 0; j < 8; ++j) {

            double sum = 0;
            for(int u = 0; u < 8; ++u) {
                for(int v = 0; v < 8; ++v) {
                    sum += alpha(u) * alpha(v)
                        * m[u][v]
                        * cos(PI8 * (double)(i+0.5) * (double)u)
                        * cos(PI8 * (double)(j+0.5) * (double)v);

                }
            }
            mt[i][j] = sum/4.0;
        }
    }



    for(int i = 0; i < 8; ++i) {
        for(int j = 0; j < 8; ++j) {
            int num = round(mt[i][j] + 128.0);
            if(num > 255) {
                num = 255;
            }
            if(num < 0) {
                num = 0;
            }
            mtt[i][j] = num;
        }
    }

 //   printf("\nt2\n");
    print(mtt);
    return 0;
}
