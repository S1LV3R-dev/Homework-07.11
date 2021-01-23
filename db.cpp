#include "db.h"
#include <fstream>
#include <bits/stdc++.h>

ostream& operator << (ostream& out, const st& st) {
    out << st.lastname << " " << st.name << " " << st.ph << " " << st.mail << " " << st.birthday;
    return out;
}

istream& operator >> (istream& in, st& st) {
    cout << "Surname: ";in.getline(st.lastname, 32);
    cout << "Name: ";in.getline(st.name, 16);
    cout << "Phone: ";in.getline(st.ph, 16);
    cout << "Mail: ";in.getline(st.mail, 32);
    cout << "Date of birth(DD.MM.YYYY): ";in.getline(st.birthday,12);
    return in;
}

bool operator < (const st& l, const st& r) {
    return strcmp(l.lastname, r.lastname) < 0;
}

bool cmpBirth(const st& l, const st& r) {
    int ld=0,lm=0,ly=0,rd=0,rm=0,ry=0;
    ld=(l.birthday[0]-48)*10+(l.birthday[1]-48);
    lm=(l.birthday[3]-48)*10+(l.birthday[4]-48);
    ly=(l.birthday[6]-48)*1000+(l.birthday[7]-48)*100+(l.birthday[8]-48)*10+(l.birthday[9]-48);
    
    rd=(r.birthday[0]-48)*10+(r.birthday[1]-48);
    rm=(r.birthday[3]-48)*10+(r.birthday[4]-48);
    ry=(r.birthday[6]-48)*1000+(r.birthday[7]-48)*100+(r.birthday[8]-48)*10+(r.birthday[9]-48);
    
    if(ly<ry) return true;
    if(ly==ry && lm<rm) return true;
    if(ly==ry && lm==rm && ld<rd) return true;
    return false;
}

bool cmpDays(const st& l, const st& r) {
    int ld=0,lm=0,rd=0,rm=0;
    ld=(l.birthday[0]-48)*10+(l.birthday[1]-48);
    lm=(l.birthday[3]-48)*10+(l.birthday[4]-48);
    
    rd=(r.birthday[0]-48)*10+(r.birthday[1]-48);
    rm=(r.birthday[3]-48)*10+(r.birthday[4]-48);
    
    if(lm<rm) return true;
    if(lm==rm && ld<rd) return true;
    return false;
}

bool cmpLastname(const st& l, const st& r) {
    int result = strcmp(l.lastname, r.lastname);
    if (result < 0)
        return true;
    if (result == 0)
        return strcmp(l.name, r.name) < 0;
    return false;
}

int addRec(DB& db) {
    st* tmp = new st[db.cnt + 1];
    for (int i = 0; i < db.cnt; ++i) {
        tmp[i] = db.stud[i];
    }
    if (db.stud)
        delete[] db.stud;
    db.stud = tmp;

    cin >> db.stud[db.cnt];
    ++db.cnt;
    cout << "Contact succesfully added!"<<endl;
    return db.cnt;
}

int findName(const DB& db) {
    cout << "Contact lastname: ";
    char tmp[32];
    cin >> tmp; cin.ignore();
    int index;
    for (index = 0; index < db.cnt; ++index) {
    	int result = strcmp(tmp, db.stud[index].lastname);
        if (result == 0)
    	{
        	cout << db.stud[index] << endl;
    		return index;
		}
    }
    cout << "There are no any contact with lastname " << tmp << " in db" << endl;
    return -1;
}

int findPhone(const DB& db) {
    cout << "Contact phone number: ";
    char tmp[32];
    cin >> tmp; cin.ignore();
    int index;
    for (index = 0; index < db.cnt; ++index) {
    	int result = strcmp(tmp, db.stud[index].ph);
        if (result == 0)
    	{
        	cout << db.stud[index] << endl;
    		return index;
		}
    }
    cout << "There are no any contact with phone number " << tmp << " in db" << endl;
    return -1;
}

void exportdb(const DB& db) {
    char fname[256];
    cout << "Database file name [contacts.txt]: ";
    cin.getline(fname, 256);
    if (strlen(fname) < 1)
        strcpy(fname, "contacts.txt");
    ofstream outFile;
    outFile.open(fname);
    if (!outFile) {
        cout << "Can not open file " << fname << endl;
        return;
    }
    for (int i = 0; i < db.cnt; ++i) {
        outFile << db.stud[i] <<"  "<< endl;
    }
    outFile.close();
    cout << "Contacts succesfully exported to "<<fname<<endl;
}

void sortByLastname(DB& db) {
    SRT(db.stud, db.cnt, cmpLastname);
    cout << "Database sorted by Surname" << endl;
}

void sortByBirth(DB& db) {
    SRT(db.stud, db.cnt, cmpBirth);
    cout << "Database sorted by date of birth" << endl;
}

void sortByDays(DB& db) {
    SRT(db.stud, db.cnt, cmpDays);
    time_t now = time(0);
	tm *ltm = localtime(&now);
	int ld=0,lm=0,k=0;
	ld=ltm->tm_mday;
	lm=ltm->tm_mon;
    for(int i=0;i<db.cnt;++i)
	{
		int rd=0,rm=0;
		rd=(db.stud[i].birthday[0]-48)*10+(db.stud[i].birthday[1]-48);
    	rm=(db.stud[i].birthday[3]-48)*10+(db.stud[i].birthday[4]-48);
    	if(ld<=rd&&lm<=rm)
    	{
    		k=i;
    		break;
		}
	}
	int l=0;
	st* tmp = new st[db.cnt];
    for (int i = k; i < db.cnt; ++i) {
        tmp[l++] = db.stud[i];
    }
    for(int i=0;i<k;++i)
    {
    	tmp[l++] = db.stud[i];
	}
    if (db.stud)
        delete[] db.stud;
    db.stud = tmp;
	
    cout << "Database sorted by days until date of birth" << endl;
}

void delRec(DB& db) {
    int index = findName(db);
    if (index < 0) {
        return;
    }
    cout << "Are you sure? (Y/N) ";
    char ch[128];
    cin.getline(ch, 128);
    if (ch[0] == 'Y' || ch[0] == 'y') {
        for (int i = index + 1; i < db.cnt; ++i) {
            db.stud[i - 1] = db.stud[i];
        }
        --db.cnt;
    }
    cout<<"Contact succesfully deleted!"<<endl;
}
