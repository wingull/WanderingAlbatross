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
	int u1[10001], u2[10001],u3[10001];	//�鿨����-����
	int v[PEOPLE];	//PEOPLE�˳鿨,��¼ÿ�����Ƿ�鵽
	int w[PEOPLE];	//��¼ÿ���˳鿨����
	int x[1001]; //��¼����յĿ���ʣ��ǽ�Ƥ
	int susnumber = 0; //���е���
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
	while(susnumber<PEOPLE) {	//��󼸸������˺����������ֲ���ȥ������ƽ����������orz
		i = RANDOM % PEOPLE;	//���һ�˳鿨
		if (i < PEOPLE*0.4) {	//�ֳ�3�����ͣ�2/5��Եһ�飬2/5û����ʱ������,1/5��ͷ����һ��Ҫȫ���鵽Ϊֹ
			k = 1;
		}
		else {
			k = 1 + (1 - v[i]) * (MAXDRAW - 1);
		}
		for (int n = 0; n < k; n++) {	//��k��
			w[i]++;
			if (ttl == 0) {	//�����Ƿ��
				ttl = TOTAL;
				ssr = int(TOTAL*PROB);
			}
			if (double(RANDOM) / RANDOM_MAX < double(ssr) / ttl) {	//����
				if (ssr == 1) {	//����ssr��
					x[ttl - 1]++;
				}
				ttl--;
				ssr--;
				if (v[i] == 0) {	//��һ�γ���
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
			else {	//û����
				ttl--;
				if (i >= PEOPLE*0.8 && v[i] == 0) {
					n--;	//ͷ��������
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

