#include <cstdio>
#include <iostream>
#include <algorithm>
#include <map>
#include <set>
#include <vector>

using namespace std;
/*
	在选定计算节点后，该任务对计算节点的要求就不再被考虑
	即使新安排的计算任务使得此前已有的计算任务的要求被违反，也是合法的。

	计算任务必须在指定可用区上运行。
	计算任务必须和指定应用的计算任务在同一可用区上运行。
		该要求对计算任务可以运行的可用区添加了限制。
		不考虑该任务本身，一个可用区若运行有指定应用的任务，则满足要求。
	计算任务不能和指定应用的计算任务在同一个计算节点上运行。
		该要求对计算任务可以运行的计算节点添加了限制。
		一个计算节点若运行有指定应用的任务，则不满足要求。
		必须满足 尽量满足 必须二选一

	执行过程
		过滤过程
			先根据计算任务的要求 过滤所有满足要求的计算节点
			如果不存在 && 指定了计算任务反亲和性 && 尽量满足反亲和性
				去掉反亲和性
				过滤
				如果不存在
					return false
				如果存在
					return true
			不然
				return true
		排序过程
			将过滤后的节点按照 
				1.运行计算任务最少的节点
				2.编号最小的节点
*/

set<int> zones[1003];//每个区域的计算节点
multiset<int> nodes[1003];//每个计算节点上跑的应用

bool cmp (int x, int y) {
	//cout << "\tx:"<<x <<"\tnodes[x]:"<<nodes[x].size()<< "\ty:" << y << "\tnodes[y]:" << nodes[y].size()<<endl;
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
		/*
		fi 接连要启动的任务
		ai 表示fi个计算任务所属应用的编号 0< ai <=Amax
		nai 0 任意区域 >0 nai区
		pai 0 无所谓 >0 必须和pai在同一区 编号看之前的ai
		paai 0 没有 >0 不能和paai在一个计算节点上运行
		paari 0 尽量满足 1 必须满足
		*/
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
  			/*
  			//此时我们得到了满足了nai pai条件的计算节点
  			cout << "\n中间结果" << endl;
  			for(int i: presult) {
  				cout << i << endl;
  			}
  			cout << "以下为当前节点中的所有可能" << endl;
  			for(int node: presult) {
  				printf("%d ", node);
  				for(int i: nodes[node]) {
  					printf("%4d", i);
  				}
  				cout << endl;
  			}
  			cout << "\n中间结果输出完成" << endl;
  			*/
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
  			/*
	  		// 查看所有分区的应用数
	  		cout << endl;
	  		for(int i = 1; i <= m; ++i) {
	  			cout << "第"<<i<<"分区" << endl;
	  			for(int j: zones[i]) {
	  				cout << "\n节点"<< j << endl;
	  				for(int k: nodes[j]) {
	  					printf("%4d", k);
	  				}
	  			}
	  			cout << endl;
	  		}
	  		*/  			
  		}
  		printf("\n");


	}
	return 0;
}