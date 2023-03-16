#include <cstdio>
#include <iostream>
#include <algorithm>
#include <map>
#include <set>
#include <vector>

using namespace std;
set<int> zones[1003];//每个区域的计算节点
multiset<int> nodes[1003];//每个计算节点上跑的应用

bool cmp (int x, int y) {
	if(nodes[x].size() != nodes[y].size()) {
		return nodes[x].size() < nodes[y].size();
	}
	return x < y;
}

void getNodes(set<int> &result, int nai, int pai) {
	//如果区域大小为0
	if(zones[nai].size() == 0) {
		return;
	}
	int flag = true;
	if(pai != 0) {
		for(int node: zones[nai]) {
			//如果当前区域上的某个计算节点找得到应用编号pai 或者 之前的应用编号为0
			if(nodes[node].find(pai) != nodes[node].end()) {
				flag = false;
				break;
			}
		}
	} else {
		flag = false;
	}
	if(flag) return;
	//如果当前可用区符合要求 添加所有节点
	for(int node: zones[nai]) {
		result.insert(node);
	}

}

int main () {
	int n, m, g;//计算节点数目 可用区数目 1-n 1-m 编号
	scanf("%d %d", &n, &m);
	for(int i = 1; i <= n; ++i) {
		int l;
		scanf("%d", &l);
		zones[l].insert(i);//第l个区域添加第i个计算节点
	}

	scanf("%d", &g);
	for(int i = 1; i <= g; ++i) {
		int fi, ai, nai, pai, paai, paari;
		scanf("%d %d %d %d %d %d", &fi, &ai, &nai, &pai, &paai, &paari);
  		
  		while(fi--) {
  			vector<int> result;//过滤完还剩下的节点
  			set<int> presult;
  			//nai 和 pai共同指定了可用的区域
  			//如果指定了区域 那么就在这个区域找满足条件的计算节点
  			if(nai > 0) {
  				getNodes(presult, nai, pai);
  			} else {
  				//在所有的找满足条件的
  				for(int i = 1; i <= m; ++i) {
  					getNodes(presult, i, pai);
  				}
  			}
  			//如果还指定了paai 那么我们就需要从result中删去一些节点
  			if(paai != 0) {
  				// 11 3 0 1 3 0
  				for(int node: presult) {
  					//如果没有冲突的话
  					if(nodes[node].find(paai) == nodes[node].end()) {
  						result.push_back(node);
  					}
  				}
  				//如果发现找不到不满足的节点
  				if(result.size() == 0) {
  					//如果可以不用管反亲和性的话
  					if(paari == 0) {
  						for(int node: presult) {
  							result.push_back(node);
  						}
  					}
  				}
  			} else {//没有指定 我们直接把这个当最后的结果
  				for(int node: presult) {
  					result.push_back(node);
  				}
  			}
  			//输出最后的结果
  			if(result.size() == 0) {
  				printf("0");
  			} else {
  				sort(result.begin(), result.end(), cmp);
  				printf("%d", result[0]);
  				//给计算节点分配计算任务
  				nodes[result[0]].insert(ai);
  			}
  			printf(" ");
  		}
  		printf("\n");


	}
	return 0;
}