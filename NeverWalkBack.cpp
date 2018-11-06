#include<stdio.h>
#include<set>
#include<iostream>
#include <fstream>
#include<cstdlib>
#include<ctime>
#include <cstring>
using namespace std;

int drct(int x, int y, int n, set<long> loc);
int ptd(int s, int n);

int main() {
	srand((unsigned)time(NULL));
	ofstream write,write2;
	write.open("trytime.txt");
	char filename0[] = "path\\";
	char filetime[10];
	char filezero[10] = "0000000";
	int x = 0, y = 1, n = 20000, successtime = 0;
	long dir = 0;
	set<long> loc;
	for (int trytime = 1; trytime <= 10000; trytime++) {
		loc.insert(0);
		loc.insert(1);
		char filename[100] = "\0";
		strcat_s(filename, filename0);
		_itoa_s(trytime,filetime,10);
		strncat_s(filename,filezero,5-strlen(filetime));
		strcat_s(filename,filetime);
		strcat_s(filename, ".txt");
//		cout << filename << endl;
		write2.open(filename);
		write2 << 0 << "\t" << 0 << "\n";
		while (x < n / 2 - 1 && y < n / 2 - 1 && x > -n / 2 + 1 && y > -n / 2 + 1) {
//			cout << x << "\t" << y << "\n" << endl;
			write2 << x << "\t" << y << "\n";
			dir = drct(x, y, n, loc);
			if (dir == 0) {
				cout << "you died\n" << x << "\t" << y << "\t" << loc.size() << "\t" << trytime << "\t" << successtime <<"\n"<< endl;
				write << x << "\t" << y << "\t" << loc.size() << "\t" << trytime << "\t" << successtime << "\td\n";
				break;
			}
			else {
				x = floor((9999.0 + dir) / n);
				y = dir - x * n;
				loc.insert(dir);
			}
		}
		if (dir != 0) {
			successtime += 1;
			cout << "you win\n" << x << "\t" << y << "\t" << loc.size() << "\t" << trytime << "\t" << successtime << endl;
			write << x << "\t" << y << "\t" << loc.size()<< "\t" << trytime << "\t" << successtime<<"\ts\n";
		}
		loc.clear();
		x = 0;
		y = 1;
		write2.close();
	}
}

int drct(int x,int y, int n, set<long> loc) {
	long pxy;
	pxy = x*n + y;
	int nextd = 0;
	int p[4];
	int pod = 4;
	int i = 0;
	for (i = 0; i < 4; i++) {
		p[i] = i+1;
	}
	while (pod > 0) {
		i = rand() % 4;
		if (p[i] == 0) {
			continue;
		}
		else if (loc.find(pxy + ptd(p[i],n)) == loc.end()) {
			nextd = pxy + ptd(p[i], n);
			break;
		}
		else {
			p[i] = 0;
			pod -= 1;
		}
	}
	if (pod == 0) {
		nextd = 0;
	}
	return nextd;
}

int ptd(int s, int n) {
	int t = 0;
	if (s == 1) {
		t = 1;
	}
	else if(s==2){
		t = n;
	}
	else if (s == 3) {
		t = -1;
	}
	else if(s == 4){
		t = -n;
	}
	return t;
}