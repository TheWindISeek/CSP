#include <set>
#include <cstdio>
#include <map>
#include <iostream>
#include <vector>

using namespace std;
//当前程序还没有考虑更复杂的情况 即当前处于风险地区 但是之后又没有给你更多的信息了 这样的话 我们应该怎么去计算这些用户
//还有一种可能的情况就是当用户去过多个风险地区的时候
typedef struct info {
    int d, u, ri;
} info;
int main ()
{
    int n;
    int r, m, p;
    int d, u, ri;
    //读取数据
    map<int, pair<int, int> > risk;
    set<int> s;
    vector<info> before;//这样好像没有考虑用户去多个地方的情况
    scanf("%d", &n);
    for(int i = 0; i < n; ++i) {
        //读取风险地区数和漫游信息数
        scanf("%d %d", &r, &m);
        //读取风险地区
        for(int k = 0; k < r; ++k) {
            scanf("%d", &p);
            //如果已经度过了风险期
            if(risk[p].second == 0) {
                if(risk[p].first + 7 != i)
                    risk[p].first = i;//则从当前重新开始
            }
            //喜提7天套餐
            risk[p].second += 7;
        }
        s.clear();
        vector<info> vinfo(before);
        before.clear();
        for(const info &in : vinfo) {
          //  printf("in.ri:%d\nrisk[in.ri].second：%d\nin.d:%d\nrisk[in.ri].first:%d\nin.u:%d\n", in.ri, risk[in.ri].second, in.d, risk[in.ri].first,in.u);
            if(risk[in.ri].second > 0 && in.d >= risk[in.ri].first  && in.d > i-7) {
                s.insert(in.u);
                before.push_back(in);
            }
        }
        vinfo.clear();
      /*
        for(const info&in: before) {
            printf("之前还存在风险的地区为 %d %d %d\n", in.d, in.u, in.ri);
        }
        */
        //读取漫游信息
        for(int k = 0; k < m; ++k) {
            scanf("%d %d %d", &d, &u, &ri);
            if(risk[ri].second > 0 && d >= risk[ri].first && d > i-7) {
                s.insert(u);
                info in;
                in.d = d;
                in.u = u;
                in.ri = ri;
               // printf("当前插入的数据为%d %d %d\n", in.d, in.u, in.ri);
                before.push_back(in);
            }
        }
       /*
        for(const info&in: before) {
            printf("插入后的存在风险的地区为 %d %d %d\n", in.d, in.u, in.ri);
        }
        */
        //更新危险表
        for(auto &ris : risk) {
            //如果当前地区还存在着危险
            if(ris.second.second > 0) {
                --ris.second.second;//持续时间减少一天
            }
        }
       // printf("这是输出\n");
        //输出当前危险表
        printf("%d", i);
        for(int user : s) {
            printf(" %d", user);
        }
        printf("\n");
        //printf("输出结束\n");
    }
    return 0;
}
