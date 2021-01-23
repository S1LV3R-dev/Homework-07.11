#include "db.h"
#include "db.cpp"
#include <bits/stdc++.h>
#include <ctime>
using namespace std;

int menu(){
	int tmp;
	for (tmp = 0; tmp<20; tmp++)cout<<'*';
	cout<<"\n1. Add record\n2. Delete record\n3. Export database\n4. Sorting by surname\n5. Sorting by date of birth\n6. Sorting by days until birthday\n7. Find by surname\n8. Find by phone numbee\n0. Exit\n";
	cin >> tmp;
	cin.ignore();
	return tmp;
}

int main(){
	DB db;
	db.cnt = 0;
	db.stud = nullptr;
	int act = 10;
	do {
        act = menu();
        switch (act) {
	        case 1: addRec(db); break;
	        case 2: delRec(db); break;
	        case 3: exportdb(db); break;
	        case 4: sortByLastname(db); break;
	        case 5: sortByBirth(db); break;
	        case 6: sortByDays(db); break;
	        case 7: findName(db); break;
	        case 8: findPhone(db); break;
        }
    } while (act != 0);
    if (db.stud)
        delete[] db.stud;

    return 0;

}