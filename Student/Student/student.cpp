/*
 *   ������Ʈ��:   Student Information Management System
 *   �ۼ��ڸ�:   �� #3
 *   �ۼ���¥:   2019.10.01
 */

#include <iostream>      //�������
#include <fstream>
#include <string>
#include <cstring>
#include <stdlib.h>
#include <iomanip>
using namespace std;
string FileName;      //�����̸�
void Menu() {      //���θ޴� ���
	cout << "1. Insertion" << endl;
	cout << "2. Search" << endl;
	cout << "3. Exit\n> ";
}
void SearchMenu() {      //��ġ�޴� ���
	cout << "- Search -" << endl;
	cout << "1. Search by name" << endl;
	cout << "2. Search by student ID (10 numbers)" << endl;
	cout << "3. Search by department name" << endl;
	cout << "4. Search by age" << endl;
	cout << "5. List all\n> ";
}

class Student {      //Student Ŭ����
public:
	char name[16];
	char ID[11];
	char age[4];
	char department[21];
	char tel[13];
};
class StudentDB {      //StudentDB Ŭ����
	Student students[100];
	int num;
public:
	void getAry();
	void insert();
	void search();
};

static string* split(string str, string strTok) {         //string �и��ϴ� �Լ�
	int cutAt;
	int index = 0;
	string* strResult = new string[5];
	while ((cutAt = str.find_first_of(strTok)) != str.npos) {
		if (cutAt > 0) {
			strResult[index++] = str.substr(0, cutAt);
		}
		str = str.substr(cutAt + 1);
	}
	if (str.length() > 0) {
		strResult[index++] = str.substr(0, cutAt);
	}
	return strResult;
}
static int compare(const void* a, const void* b)      //���Լ�
{
	return strcmp(((Student*)a)->name, ((Student*)b)->name);
}

void StudentDB::insert() {      //�л� ���� ���Ͽ� �߰� & array�� �߰��ϴ� �Լ�
	cout << "- Insertion -" << endl;
	cout << "Name ? ";
	cin.ignore(16, '\n');
	cin.getline(students[num].name, 16);
	cout << "Student ID ? ";
	char ID[11];
	bool overlap2;
	do {
		overlap2 = false;
		cin >> ID;
		for (int j = 0; j < num; j++)
			if (!strcmp(students[j].ID, ID))
				overlap2 = true;
		if (overlap2) {      //�й� �ߺ� ��:
			cout << "Error : Already inserted\n";
			cout << "Student ID ? ";
		}
		else
			strcpy_s(students[num].ID, ID);
	} while (overlap2);
	cout << "Age ? ";
	cin >> students[num].age;
	cout << "Department ? ";
	cin.ignore(20, '\n');
	cin.getline(students[num].department, 20);
	cout << "Tel ? ";
	cin >> students[num].tel;
	ofstream studentFile(FileName, std::ios_base::app);
	if (studentFile.is_open()) {      //�л� ���� ���Ͽ� �߰�
		studentFile << students[num].name << "/";
		studentFile << students[num].ID << "/";
		studentFile << students[num].age << "/";
		studentFile << students[num].department << "/";
		studentFile << students[num].tel << endl;
		num++;
	}
	else {
		cout << "error!";
	}
}
void StudentDB::getAry() {         //file���� �޾ƿͼ� students �迭�� �����ϴ� �Լ�
	int top = 0;
	string line;
	string* token = new string[5];
	ifstream istudentFile(FileName, std::ios_base::app);
	if (istudentFile.is_open()) {
		while (getline(istudentFile, line)) {
			token = split(line, "/");
			Student* s = new Student();
			strcpy_s(s->name, token[0].c_str());
			strcpy_s(s->ID, token[1].c_str());
			strcpy_s(s->age, token[2].c_str());
			strcpy_s(s->department, token[3].c_str());
			strcpy_s(s->tel, token[4].c_str());
			students[top] = *s;
			top++;
		}
	}
	else {
		cout << "error!";
	}
	num = top;
}
void StudentDB::search()      //array���� �л����� �˻�
{
	qsort(students, num, sizeof(students[0]), compare);      //array�� ���ĺ� ������ ����
	int menu = -1;
	while (menu != 1 && menu != 2 && menu != 3 && menu != 4 && menu != 5) {
		SearchMenu();
		cin >> menu;
		if (cin.fail()) {
			cin.clear();
			cout << "Wrong Input. Please enter again" << endl;
			continue;
		}
		switch (menu)
		{
		case 1:
			char name[16];
			cout << "Name keyword? ";
			cin.ignore(16, '\n');
			cin.getline(name, 16);
			cout.setf(ios::left);
			cout << setw(15) << "Name";
			cout << " " << setw(10) << "StudentID";
			cout << " " << setw(20) << "Dept";
			cout << " " << setw(3) << "Age";
			cout << " " << setw(12) << "Tel" << endl;
			for (int i = 0; i < 100; i++)
			{
				if (!strcmp(students[i].name, name))
				{
					cout << setw(15) << students[i].name;
					cout << " " << setw(10) << students[i].ID;
					cout << " " << setw(20) << students[i].department;
					cout << " " << setw(3) << students[i].age;
					cout << " " << setw(12) << students[i].tel << endl;
				}
			}
			break;
		case 2:
			char ID[11];
			cout << "ID keyword? ";
			cin >> ID;
			cout.setf(ios::left);
			cout << setw(15) << "Name";
			cout << " " << setw(10) << "StudentID";
			cout << " " << setw(20) << "Dept";
			cout << " " << setw(3) << "Age";
			cout << " " << setw(12) << "Tel" << endl;
			for (int i = 0; i < 100; i++)
			{
				if (!strcmp(students[i].ID, ID))
				{
					cout << setw(15) << students[i].name;
					cout << " " << setw(10) << students[i].ID;
					cout << " " << setw(20) << students[i].department;
					cout << " " << setw(3) << students[i].age;
					cout << " " << setw(12) << students[i].tel << endl;
				}
			}
			break;
		case 3:
			char department[21];
			cout << "Department name keyword? ";
			cin.ignore(20, '\n');
			cin.getline(department, 20);
			cout.setf(ios::left);
			cout << setw(15) << "Name";
			cout << " " << setw(10) << "StudentID";
			cout << " " << setw(20) << "Dept";
			cout << " " << setw(3) << "Age";
			cout << " " << setw(12) << "Tel" << endl;
			for (int i = 0; i < 100; i++)
			{
				if (!strcmp(students[i].department, department))
				{
					cout << setw(15) << students[i].name;
					cout << " " << setw(10) << students[i].ID;
					cout << " " << setw(20) << students[i].department;
					cout << " " << setw(3) << students[i].age;
					cout << " " << setw(12) << students[i].tel << endl;
				}
			}
			break;
		case 4:
			char age[4];
			cout << "Age keyword? ";
			cin >> age;
			cout.setf(ios::left);
			cout << setw(15) << "Name";
			cout << " " << setw(10) << "StudentID";
			cout << " " << setw(20) << "Dept";
			cout << " " << setw(3) << "Age";
			cout << " " << setw(12) << "Tel" << endl;
			for (int i = 0; i < 100; i++)
			{
				if (!strcmp(students[i].age, age))
				{
					cout << setw(15) << students[i].name;
					cout << " " << setw(10) << students[i].ID;
					cout << " " << setw(20) << students[i].department;
					cout << " " << setw(3) << students[i].age;
					cout << " " << setw(12) << students[i].tel << endl;
				}
			}
			break;
		case 5:
			cout.setf(ios::left);
			cout << setw(15) << "Name";
			cout << " " << setw(10) << "StudentID";
			cout << " " << setw(20) << "Dept";
			cout << " " << setw(3) << "Age";
			cout << " " << setw(12) << "Tel" << endl;
			for (int i = 0; i < num; i++)
			{
				cout << setw(15) << students[i].name;
				cout << " " << setw(10) << students[i].ID;
				cout << " " << setw(20) << students[i].department;
				cout << " " << setw(3) << students[i].age;
				cout << " " << setw(12) << students[i].tel << endl;
			}
			break;
		default:
			cout << "Wrong Input. Please enter again" << endl;
		}
	}
}

int main(int argc, char* argv[]) {      //�����Լ�
	FileName = string(argv[1]);
	StudentDB db;      //StudentDB ��ü ����
	db.getAry();      //file���� ���� �ҷ�����
	int menu = -1;
	while (menu != 3) {
		Menu();      //���θ޴� ���
		cin >> menu;
		if (cin.fail()) {
			cin.clear();
			cout << "Wrong Input. Please enter again" << endl;
			continue;
		}
		switch (menu)
		{
		case 1:
			db.insert();      //�л� ���� ����
			break;
		case 2:
			db.search();      //�л� ���� �˻�
			break;
		case 3:      //exit
			break;
		default:
			cout << "Wrong Input. Please enter again" << endl;
		}
	}
	return 0;
}