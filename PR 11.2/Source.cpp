// PR_11_2.cpp
// ������� ³����
// ����������� ������ � 11.2
// ���������� ����� � �������� ����
// ������ 7

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <stdio.h>
#include <Windows.h>
#include <fstream>
#include <iomanip>

using namespace std;


enum Specialty { KN, IT, ME, PI, TN };;
string SpecialtyStr[] = { "��������� �����", "�����������", "���������� �� ��������","Գ���� �� �����������","������� ��������" };

struct Student
{
	char prizv[25];
	int kurs;
	float sb;
	Specialty specialty;
	int Phisic;
	int Math;
	union {
		int Prog;
		int Num_Methods;
		int Pedagogy;
	};
};


void Create(char* fname);
void Print(char* fname);
void PercentageStudents(char* fname);
void PrintStudentsBal(char* fname);

int main()
{

	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	char fname[100];
	int menuItem;

	do {
		cout << endl << endl;
		cout << "������� ��:" << endl << endl;
		cout << " [1] - ������ ��� � ����" << endl;
		cout << " [2] - ������� ��� �� �����" << endl;
		cout << " [3] - ������� ������� ������ � ������ ������ �5� ��� �4�" << endl;
		cout << " [4] - ������� ������� ��������, ������� ���" << endl;
		cout << " [0] - ����� �� ���������� ������ ��������" << endl << endl;
		cout << "������ ��������: "; cin >> menuItem;
		cout << endl << endl << endl;
		switch (menuItem)
		{
		case 1:

			cin.get(); 
			cin.sync();
			cout << "������ ��'� �����: "; cin.getline(fname, sizeof(fname));
			Create(fname);
			break;
		case 2:
			cin.get();
			cin.sync();
			cout << "������ ��'� �����: "; cin.getline(fname, sizeof(fname));
			Print(fname);
			break;
		case 3:
			cin.get();
			cin.sync();
			cout << "������ ��'� �����: "; cin.getline(fname, sizeof(fname));
			PercentageStudents(fname);
			break;
		case 4:
			cin.get();
			cin.sync();
			cout << "������ ��'� �����: "; cin.getline(fname, sizeof(fname));
			PrintStudentsBal(fname);
			break;
		case 0:
			break;
		default:
			cout << "�� ����� ��������� ��������! "
				"��� ������ ����� - ����� ��������� ������ ����" << endl;
		}
	} while (menuItem != 0);

	return 0;


}
void Create(char* fname)
{
	FILE* f;
	if ((f = fopen(fname, "wb")) == NULL)
	{
		cerr << "Error opening file '" << fname << "'" << endl;
		return;
	}

	int specialty;
	Student student;
	char ch;

	do
	{
		cout << endl;
		cout << " �������: ";  cin.sync(); cin >> student.prizv;
		cout << " ����: "; cin >> student.kurs;
		cout << " ������������ (0 - ��������� �����, 1 - �����������, 2 - ���������� �� ��������, 3 - Գ���� �� �����������, 4 - ������� ��������): ";
		cin >> specialty;
		student.specialty = (Specialty)specialty;
		cout << " ������ � Գ����: "; cin >> student.Phisic;
		cout << " ������ � ����������: "; cin >> student.Math;
		switch (student.specialty)
		{
		case KN:
			cout << " ������ � �������������: "; cin >> student.Prog;
			break;
		case IT:
			cout << " ������ � ��������� ������: "; cin >> student.Num_Methods;
			break;
		case ME:
		case PI:
		case TN:
			cout << " ������ � ���������: "; cin >> student.Pedagogy;
			break;
		}
		if (fwrite(&student, sizeof(Student), 1, f) != 1)
		{
			cerr << "Error writing file." << endl;
			return;
		}

		cout << "����������? (Y/N): "; cin >> ch;
	} while (ch == 'y' || ch == 'Y');

	fclose(f);
}
void Print(char* fname) // ��������� ����� �� �����
{
	FILE* f;
	if ((f = fopen(fname, "rb")) == NULL)
	{
		cerr << "Error opening file '" << fname << "'" << endl;
		return;
	}
	Student student;

	while (!feof(f))
	{

		if (fread(&student, sizeof(Student), 1, f) != 1)
			if (feof(f))
			{
				return;
			}

		cout << endl;
		cout << " ������� : " << student.prizv << endl;
		cout << " ����: " << student.kurs << endl;
		cout << " ������������: " << SpecialtyStr[student.specialty] << endl;
		cout << " ������ � Գ����:" << student.Phisic << endl;
		cout << " ������ � ����������:" << student.Math << endl;
		switch (student.specialty)
		{
		case KN:
			cout << " ������ � �������������: :" << student.Prog << endl;
			break;
		case IT:
			cout << " ������ � ��������� ������:" << student.Num_Methods << endl;
			break;
		case ME:
		case PI:
		case TN:
			cout << "������ � ���������:" << student.Pedagogy << endl;
			break;
		}
	}


	fclose(f);
}
void PercentageStudents(char* fname)
{
	ifstream f(fname, ios::binary);
	Student student;

	if (!f)
	{
		cerr << "Error opening file '" << fname << "'" << endl;
		return;
	}

	double P_of_S = 0;
	int kilk = 0;

	while (f.read((char*)&student, sizeof(Student)))
	{
		if (student.Phisic == 4 || student.Phisic == 5)
			P_of_S += 1;

		kilk++;
	}
	P_of_S = (P_of_S / kilk) * 100;

	cout << "������� ��������, �� �������� � ������ ������ �5� ��� �4�. = " << setprecision(3) << P_of_S << "%" << endl;

}
void PrintStudentsBal(char* fname)
{
	ifstream f(fname, ios::binary);
	Student student;

	if (!f)
	{
		cerr << "Error opening file '" << fname << "'" << endl;
		return;
	}
	int � = 0;
	cout << "������� ��������, ������� ���: " << endl;
	while (f.read((char*)&student, sizeof(Student)))
	{

		if ((student.Math +student.Phisic + student.specialty) / 3.0 )
		    cout << ++� << "." << student.prizv << " , " << " ������� ��� = " << student.sb << endl;

	}

}