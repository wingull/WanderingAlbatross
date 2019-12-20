#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <iostream>
using namespace std;

const int pofagent[7] = {9,9,9,9,9,9,9};

class doc
{
public:
    int id;
    int loc[2];
    int clue[7];
    int nof;
    int frd[50];
    int mtt;
    int agent[7];
    int who;

    void reg(int);
    int meeting();
    int findclue();
    void print();
    int R();
    int G();
    int B();
};


void doc::reg(int i)
{
    id = i;
    loc[0] = i / 100;
    loc[1] = i - loc[0] * 100;
    for (int t = 0; t < 7; t++)
    {
        clue[t] = 0;
        if (rand() < RAND_MAX/10*pofagent[t]) {
            agent[t] = 1;
        }
        else {
            agent[t] = 0;
        }

    }
    nof = 0;
    for (int t = 0; t < 50; t++)
    {
            frd[t] = 10000;
    }
    mtt = 0;
    who = rand() % 7;
}

int doc::meeting() {
    int m = 1;
    if (mtt) {
        mtt -= 1;
        return 0;
    }
    for (int t = 0; t < 7; t++)
    {
        m *= clue[t];
    }
    if (m) {
        for (int t = 0; t < 7; t++)
        {
            clue[t] -= 1;
        }
        mtt = 3;
        return 1;
    }
    else {
        return 0;        
    }
}

int doc::findclue() {
    int tmp, c;
    if (agent[who]) {
        tmp = rand() % 12;
        if (tmp >= 6) {
            c = who;
        }
        else if (tmp < who) {
            c = tmp;
        }
        else {
            c = tmp + 1;
        }
    }
    else {
        c = rand() % 7;
        if (rand() % 50 == 0) {
            agent[who] = 1;
        }
    }
    if ((clue[c] == 0 || c == who) && clue[c] < 3) {
        clue[c] += 1;
        return 7;
    }
    else {
        return c;
    }
}

void doc::print()
{
    cout << "id = "<<id <<"\nloc = "<<*loc<<" "<<*(loc+1)<<"\nclue: "<< endl;
    for (int t = 0; t < 7; t++)
    {
        cout << clue[t] <<" "<<agent[t]<< endl;
    }
    cout <<"nof: "<< nof<<"\nfriend: " << endl;
   for (int t = 0; t < nof; t++)
    {
        cout << frd[t] << endl;
    }
}

int doc::R()
{
    int R = 255;
    if (mtt > 0) {
        return 255;
    }
    if (clue[0] == 0) {
        R -= 255;
    }
    if (clue[1] == 0) {
        R -= 170;
    }
    if (clue[5] == 0) {
        R -= 170;
    }
    if (clue[6] == 0) {
        R -= 127;
    }
    return (abs(R)+R)/2;
}

int doc::G()
{
    int G = 255;
    if (mtt > 0) {
        return 255;
    }
    if (clue[1] == 0) {
        G -= 170;
    }
    if (clue[2] == 0) {
        G -= 255;
    }
    if (clue[3] == 0) {
        G -= 170;
    }

    if (clue[6] == 0) {
        G -= 127;
    }
    return (abs(G) + G) / 2;
}

int doc::B()
{
    int B = 255;
    if (mtt > 0) {
        return 255;
    }
    if (clue[3] == 0) {
        B -= 170;
    }
    if (clue[4] == 0) {
        B -= 255;
    }
    if (clue[5] == 0) {
        B -= 170;
    }
    if (clue[6] == 0) {
        B -= 127;
    }
    return (abs(B) + B) / 2;
}

int makefriend(doc& doc1, doc& doc2)
{
    if (doc1.nof >= 50 || doc2.nof >= 50 || doc1.id == doc2.id)
    {
        return 0;
    }
    else
    {
        for (int t = 0; t < doc1.nof; t++)
        {
            if (doc1.frd[t] == doc2.id)
            {
                return 0;
            }
        }
        doc1.frd[doc1.nof] = doc2.id;
        doc2.frd[doc2.nof] = doc1.id;
        doc1.nof += 1;
        doc2.nof += 1;
        return 1;
    }
}

double distance(doc doc1, doc doc2)
{
    int d;
    d = (doc1.loc[0] - doc2.loc[0]) * (doc1.loc[0] - doc2.loc[0]) + (doc1.loc[1] - doc2.loc[1]) * (doc1.loc[1] - doc2.loc[1]);
    return d;
}

void interchange(doc& doc1, doc& doc2)
{
    int p[2];
    p[0] = doc1.loc[0];
    p[1] = doc1.loc[1];
    doc1.loc[0] = doc2.loc[0];
    doc1.loc[1] = doc2.loc[1];
    doc2.loc[0] = p[0];
    doc2.loc[1] = p[1];
}

int findthevaluableclue(doc doc1, doc doclist[])
{
    int cluetmp[7], num = 0, highest = 0, v;
    for (int n = 0; n < 7; n++) {
        cluetmp[n] = 0;
    }
    for (int n = 0; n < 7; n++) {
        for (int i = 0; i < doc1.nof; i++) {
            if (doclist[doc1.frd[i]].clue[n]==0) {
                cluetmp[n] += 1;
            }
        }
    }
    for (int n = 0; n < 7; n++) {
        if (cluetmp[n] > cluetmp[num]) {
            num = 1;
            highest = cluetmp[n];
        }
        else if (cluetmp[n] == cluetmp[num]) {
            num += 1;
        }
    }
    v = rand() % 7;
    while(cluetmp[v] < highest) {
        v = rand() % 7;
    }
    return v;
}

int findwhoneedit(int c, doc doc1, doc doclist[]) {
    for (int n = 0; n < doc1.nof;n++) {
        if (doclist[doc1.frd[n]].clue[c] == 0) {
            return doc1.frd[n];
        }
    }
    return doc1.id;
}

void giveclue(int c, doc& doc1) {
    if (doc1.clue[c] < 5) {
        doc1.clue[c] += 1;
    }
}

void annealing(int time, doc doclist[]) {
    int id1, id2, toc = 0;
    double d = 0, dold, dnew, T=100000;
    for (int i = 0; i < time; i++) {
        dold = 0;
        dnew = 0;
        id1 = rand() % 10000;
        id2 = rand() % 10000;

        for (int n = 0; n < 50; n++) {
            dold += distance(doclist[id1], doclist[doclist[id1].frd[n]])+ distance(doclist[id2], doclist[doclist[id2].frd[n]]);
        }
        interchange(doclist[id1], doclist[id2]);
        for (int n = 0; n < 50; n++) {
            dnew += distance(doclist[id1], doclist[doclist[id1].frd[n]]) + distance(doclist[id2], doclist[doclist[id2].frd[n]]);
        }

        if (exp((dold - dnew) / T) > (double)rand() / RAND_MAX) {
            T *= 0.99999;
            toc += 1;
        }
        else {
            interchange(doclist[id1], doclist[id2]);
        }
        if (i % 100000 == 0) {
            d = 0;
            for (int i = 0; i < 10000; i++) {
                for (int j = 0; j < 50; j++) {
                    d += distance(doclist[i], doclist[doclist[i].frd[j]]);
                }
            }
            cout << sqrt(d / 500000) <<" "<<toc<<" "<<i<<endl;
        }
    }
}