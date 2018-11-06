#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include<iostream>
#include <fstream>
using namespace std;
#define TOTAL 1000000
#define PROB 0.02
#define RANDOM (rand()*(RAND_MAX+1)+rand())
#define RANDOM_MAX ((RAND_MAX+1)*(RAND_MAX+1))
#define MAXDRAW 10
#define PEOPLE 100000

int main() {
	srand((unsigned)time(NULL));
	int ttl = TOTAL, ssr = int(TOTAL*PROB),i,k;
	ofstream wrt;
	wrt.open("result.txt");
	int u1[10001], u2[10001],u3[10001];	//抽卡次数-人数
	int v[PEOPLE];	//PEOPLE人抽卡,记录每个人是否抽到
	int w[PEOPLE];	//记录每个人抽卡次数
	int x[1001]; //记录被抽空的卡池剩余非金皮
	int susnumber = 0; //抽中的人
	for (int t = 0; t < 10001; t++) {
		u1[t] = 0;	
		u2[t] = 0;
		u3[t] = 0;
		x[t] = 0;
	}
	for (int t = 0; t < PEOPLE; t++) {
		v[t] = 0;	
		w[t] = 0;
	}
	ttl = TOTAL;
	ssr = int(TOTAL*PROB);
	while(susnumber<PEOPLE) {	//最后几个非洲人好慢啊但是又不能去掉否则平均数有问题orz
		i = RANDOM % PEOPLE;	//随机一人抽卡
		if (i < PEOPLE*0.4) {	//分成3个类型，2/5随缘一抽，2/5没抽中时会连抽,1/5是头铁者一定要全部抽到为止
			k = 1;
		}
		else {
			k = 1 + (1 - v[i]) * (MAXDRAW - 1);
		}
		for (int n = 0; n < k; n++) {	//抽k次
			w[i]++;
			if (ttl == 0) {	//卡池是否空
				ttl = TOTAL;
				ssr = int(TOTAL*PROB);
			}
			if (double(RANDOM) / RANDOM_MAX < double(ssr) / ttl) {	//抽中
				if (ssr == 1) {	//检测空ssr池
					x[ttl - 1]++;
				}
				ttl--;
				ssr--;
				if (v[i] == 0) {	//第一次抽中
					v[i] = 1;
					susnumber++;
					cout << susnumber << endl;
					if (i < PEOPLE*0.4) {
						u1[w[i]] += 1; 
					}else if (i < PEOPLE*0.8) {
						u2[w[i]] += 1; 
					}else {
						u3[w[i]] += 1;
						break;
					}
				}
			}
			else {	//没抽中
				ttl--;
				if (i >= PEOPLE*0.8 && v[i] == 0) {
					n--;	//头铁者连抽
				}
			}

		}


	}

	for (int t = 0; t < 1001; t++) {
		wrt << t << "\t" << u1[t] << "\t" << u2[t]<<"\t" << u3[t] << "\t" << x[t] << "\n";
	}
	wrt.close();

	return 0;
}

