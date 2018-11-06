#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include<iostream>
#include <fstream>
using namespace std;

int main() {
	srand((unsigned)time(NULL));
	int a = 0, b = 0, c = 0, d = 0, e = 0, f = 0, i = 0;
	double r;
	ofstream wrt;
	wrt.open("result.txt");
	int u[10001];
	for (int t = 0; t < 10001; t++) {
		u[t] = 0;
	}
	for (int t = 0; t < 100000; t++) {
		i = 0;
		a = 0;
		b = 0;
		c = 0;
		d = 0;
		while (a*b*c == 0) {
			r = rand()*100.0 / RAND_MAX;
			if (r <= 2) {
				a = 1;
			}
			else if (r <= 4.5) {
				b = 1;
			}
			else if (r <= 7) {
				c = 1;
			}
			i++;
		}
		*(u + i) += 1;
		cout << t << "\t" << i << "\n" << endl;
	}
	for (int t = 0; t < 10001; t++) {
		wrt << t << "\t" << u[t] << "\n";
	}
	wrt.close();
}