#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <fstream>
#include <sstream> 
#include "doc.h"
using namespace std;

int main() {
	srand(time(NULL));
	
	doc* doclist;
	doc* tmp = (doc*)malloc(sizeof(doc) * 10000);
	int* tmp2 = (int*)malloc(sizeof(int) * 30000);
	int* location;
	if (tmp == NULL || tmp2 == NULL) {
		printf("Error000:Alloc memory failure");
		exit(1);
	}
	doclist = tmp;
	location = tmp2;
	for (int i = 0; i < 10000; i++) {
		doclist[i].reg(i);
	}

/*	for (int i = 0; i < 1000000; i++) {
		makefriend(doclist[rand() % 10000], doclist[rand() % 10000]);
	}*/

	for (int i = 0; i < 10000; i++) {
		for (int j = -3; j < 4; j++) {
			for (int k = 0; k < 4; k++) {
					makefriend(doclist[i], doclist[(i + 100 * j + k)-(int)(floor((i + 100 * j + k)/10000.0)*10000)]);
			}
		}
	}

//	doclist[0].print();
//	annealing(10000000, doclist);
	int meetingtime = 0;
	int soc[7];
	string filename = "out.txt";
	ofstream fouttxt(filename);
	for (int t = 0; t < 10000; t++) {
		for (int c = 0; c < 7; c++) {
			soc[c] = 0;
		}

		for (int i = 0; i < 10000; i++) {
			doclist[i].who = findthevaluableclue(doclist[i], doclist);
			int c = doclist[i].findclue();
			if (c != 7) {
				giveclue(c, doclist[findwhoneedit(c, doclist[i], doclist)]);
			}
/*			meetingtime += */doclist[i].meeting();
			for (int c = 0; c < 7; c++) {
				if (doclist[i].clue[c] == 0) {
					soc[c] += 1;
				}
			}
			location[3 * (doclist[i].loc[0]*100+ doclist[i].loc[1])] = doclist[i].R();
			location[3 * (doclist[i].loc[0] * 100 + doclist[i].loc[1]) + 1] = doclist[i].G();
			location[3 * (doclist[i].loc[0] * 100 + doclist[i].loc[1]) + 2] = doclist[i].B();

		}
		if (t % 10 == 0) {
			string filename2 = "ppm\\" + to_string(t) + ".ppm";
			ofstream fout(filename2);
			fout << "P3\n" << 100 << " " << 100 << "\n255\n";
			for (int i = 0; i < 10000; i++) {
				fout << location[3 * i] << " " << location[3 * i + 1] << " " << location[3 * i + 2] << "\n";
			}
			fout.close();
		}

		cout << t << "\t" << "\t"<< soc[0]<<"\t" << soc[1] << "\t" << soc[2] << "\t" << soc[3] << "\t" << soc[4] << "\t" << soc[5] << "\t" << soc[6] << "\t" << endl;
		fouttxt << t << "\t" <<  "\t" << soc[0] << "\t" << soc[1] << "\t" << soc[2] << "\t" << soc[3] << "\t" << soc[4] << "\t" << soc[5] << "\t" << soc[6] << "\n";
		
	}
	fouttxt.close();
	free(doclist);
	free(location);
	return 0;
}