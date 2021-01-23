#ifndef __DB__
#define __DB__
#include<bits/stdc++.h>
using namespace std;

struct st{
	char lastname[32]; 
	char name[16];
	char ph[16];
	char mail[32]; 
	char birthday[12];
};

struct DB{
	int cnt;
	st* stud;
};

ostream& operator << (ostream& out, const st& st);
istream& operator >> (istream& in, st& st);

bool operator < (const st& l, const st& r);
bool cmpBirth(const st& l, const st& r);
bool cmpLastname(const st& l, const st& r);
bool cmpDays(const st& l, const st& r);

int addRec(DB& db);
int findRec(const DB& db);
int findName(const DB& db);
int findPhone(const DB& db);
void delRec(DB& db);

void saveDB(const DB& db);
void exportDB(const DB& db);
void sortByLastname(DB& db);
void sortByBirth(DB& db);
void sortByDays(DB& db);

template <typename T>
void SRT(T* M, int n, bool (*comparator)(const T&, const T&)) {
    for (int j = 0; j < n - 1; ++j) {
        int k = j;
        for (int i = k + 1; i < n; ++i){
            if (comparator(M[i], M[k]))
                k = i;
        }
        if (j < k) {
            std::swap(M[k], M[j]);
        }
    }
}
#endif