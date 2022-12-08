//B
#include <iostream>
#include <iomanip>
#include <string>
#include <algorithm>
#include <Windows.h> 
using namespace std;

enum Spec { ME, MF, FI, In, KN };
string specStr[] = { "���������� �� ��������", "������� ��������", "Գ���� �� �����������", "�����������" ,"����'����� �����" };

struct Student
{
	string prizv;
	unsigned kurs;
	Spec spec;
	union
	{
		double fizika;
	};
	union
	{
		double matematika;
	};
	union {
		double programuvanna;
		double chslmetods;
		double pedagogika;
	};
};

void Create(Student* p, const int N);
void Print(Student* p, const int N);
void Sort(Student* p, const int N);
int* IndexSort(Student* p, const int N);
void PrintIndexSorted(Student* p, int* I, const int N);
int BinSearch(Student* p, const int N, const string prizv, const unsigned kurs, const Spec spec, const unsigned pedagogika);

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	int N;
	cout << "������ ������� ��������: "; cin >> N;

	Student* p = new Student[N];

	//��� �� ���
	/*int ikurs;
	unsigned kurs;
	unsigned pedagogika;
	unsigned ipedagogika;
	int ispec;
	Spec spec;*/
	double pedagogika, kurs, ispec;
	Spec spec;
	string prizv;
	int found;
	char filename[100];

	int menuItem;
	do {
		cout << endl << endl << endl;
		cout << "������� ��:" << endl << endl;
		cout << " [1] - �������� ����� � ���������" << endl;
		cout << " [2] - ���� ����� �� �����" << endl;
		cout << " [3] - ������� �����" << endl;
		cout << " [4] - ������� ������������� �����" << endl;
		cout << " [5] - �������� �������������" << endl;
		cout << " [0] - ����� �� ���������� ������ ��������" << endl << endl;
		cout << "������ ��������: "; cin >> menuItem;
		cout << endl << endl << endl;
		switch (menuItem)
		{
		case 1:
			Create(p, N);
			break;
		case 2:
			Print(p, N);
			break;
		case 3:
			cout << "������ ����� ������:" << endl;
			cin.get();
			cin.sync();
			cout << " �������: "; getline(cin, prizv);
			cout << endl;
			cout << "���� : ";
			cin >> kurs;
			cout << " ������������ ( 0 - ���������� �� ��������, 1 - ������� ��������, 2 - Գ���� �� �����������, 3 - ����������� , 4 - ����'����� �����): ";
			cin >> ispec;
			spec = (Spec)ispec;
			cout << "������ � �������� ��������: ";
			cin >> pedagogika;
			
			if ((found = BinSearch(p, N, prizv, kurs, spec, pedagogika)) != -1)
				cout << "�������� �������� � ������� " << found + 1 << endl;
			else
				cout << "�������� �������� �� ��������" << endl;
			break;

			break;
		case 4:
			Sort(p, N);
			break;
		case 5:
			PrintIndexSorted(p, IndexSort(p, N), N);
		case 0:
			break;
		default:
			cout << "�� ����� ��������� ��������! "
				"��� ������ ����� - ����� ��������� ������ ����" << endl;

		}
	} while (menuItem != 0);
	return 0;
}

void Create(Student* p, const int N)
{
	int spec;
	for (int i = 0; i < N; i++)
	{
		cout << "������� � " << i + 1 << ":" << endl;
		cin.get();
		cin.sync();

		cout << " �������: "; getline(cin, p[i].prizv);
		cout << " ����: "; cin >> p[i].kurs;
		cout << " ������������ ( 0 - ���������� �� ��������, 1 - ������� ��������, 2 - Գ���� �� �����������, 3 - ����������� , 4 - ����'����� �����): ";
		cin >> spec;
		p[i].spec = (Spec)spec;


		switch (p[i].spec) {

		case 3:
			cout << " ��� � ������: "; cin >> p[i].fizika;
			cout << " ��� � ����������:"; cin >> p[i].matematika;
			cout << " ��� � ��������� ������: "; cin >> p[i].chslmetods;
			break;
		case 4:
			cout << " ��� � ������: "; cin >> p[i].fizika;
			cout << " ��� � ����������: "; cin >> p[i].matematika;
			cout << " ��� � �������������: "; cin >> p[i].programuvanna;
			break;

		default:
			cout << " ��� � ������: "; cin >> p[i].fizika;
			cout << " ��� � ����������: "; cin >> p[i].matematika;
			cout << " ��� � ���������: "; cin >> p[i].pedagogika;
			break;
		}
		cout << endl;
	}
}

void Print(Student* p, const int N)
{
	cout << "=============================================================================================================================="
		<< endl;
	cout << "________________________________________________________|                          ����                              |"
		<< endl;
	cout << "| � |     �������     | ���� |       ������������     | Գ���� | ���������� | ������������� | ������� ������ | ��������� |"
		<< endl;
	cout << "------------------------------------------------------------------------------------------------------------------------------"
		<< endl;

	for (int i = 0; i < N; i++)
	{
		switch (p[i].spec) {

		case 3:
			cout << "| " << setw(1) << right << i + 1 << " ";
			cout << "| " << setw(17) << left << p[i].prizv
				<< "| " << setw(4) << right << p[i].kurs << " "
				<< "| " << setw(24) << left << specStr[p[i].spec] << "| " << setw(7) << right << p[i].fizika << "| " << setw(11) << right << p[i].matematika << "|" << setw(16) << "|" << setw(17) << right << p[i].chslmetods << "|" << setw(13) << "|" << endl;
			break;
		case 4:
			cout << "| " << setw(1) << right << i + 1 << " ";
			cout << "| " << setw(17) << left << p[i].prizv
				<< "| " << setw(4) << right << p[i].kurs << " "
				<< "| " << setw(24) << left << specStr[p[i].spec] << "| " << setw(7) << right << p[i].fizika << "| " << setw(11) << right << p[i].matematika << "|" << setw(15) << p[i].programuvanna << "|" << setw(18) << right << "|" << setw(13) << "|" << endl;
			break;

		default:
			cout << "| " << setw(1) << right << i + 1 << " ";
			cout << "| " << setw(17) << left << p[i].prizv
				<< "| " << setw(4) << right << p[i].kurs << " "
				<< "| " << setw(24) << left << specStr[p[i].spec] << "| " << setw(7) << right << p[i].fizika << "| " << setw(11) << right << p[i].matematika << "|" << setw(16) << "|" << setw(18) << right << "|" << setw(12) << p[i].pedagogika << "|" << endl;
			break;
		}
	}
	cout << "=============================================================================================================================="
		<< endl;
	cout << endl;
}

void Sort(Student* p, const int N)
{
	Student tmp;
	for (int i0 = 0; i0 < N - 1; i0++) // ����� "���������"
		for (int i1 = 0; i1 < N - i0 - 1; i1++) {
			if ((p[i1].kurs > p[i1 + 1].kurs)
			   ||
				(p[i1].kurs == p[i1 + 1].kurs &&
					p[i1].spec > p[i1 + 1].spec)
				||
				(p[i1].kurs == p[i1 + 1].kurs && p[i1].spec == p[i1 + 1].spec && p[i1].pedagogika > p[i1 + 1].pedagogika)
				||
				(p[i1].kurs == p[i1 + 1].kurs && p[i1].spec == p[i1 + 1].spec && p[i1].pedagogika == p[i1 + 1].pedagogika && p[i1].prizv < p[i1 + 1].prizv))
			{
				tmp = p[i1];
				p[i1] = p[i1 + 1];
				p[i1 + 1] = tmp;
			}

		}
}

int BinSearch(Student* p, const int N, const string prizv, const unsigned kurs, const Spec spec, const unsigned pedagogika)
{ // ������� ������ ���������� �������� ��� -1, ���� ������� ������� �������
	int L = 0, R = N - 1, m;
	do {
		m = (L + R) / 2;
		if (p[m].prizv == prizv && p[m].kurs == kurs && p[m].spec == spec)
			return m;
		if ((p[m].kurs < kurs)
			||
			(p[m].kurs == kurs &&
				p[m].prizv < prizv)
			||
			(p[m].kurs == kurs &&
				p[m].prizv == prizv && p[m].spec < spec)
			||
			(p[m].kurs == kurs &&
				p[m].prizv == prizv && p[m].spec == spec && p[m].pedagogika < pedagogika))
		{
			L = m + 1;
		}
		else
		{
			R = m - 1;
		}
	} while (L <= R);
	return -1;
}

int* IndexSort(Student* p, const int N)
{
	int* I = new int[N]; // �������� ��������� �����
	for (int i = 0; i < N; i++)
		I[i] = i; // ��������� ���� ����������� ������
	int i, j, value; // �������� ��������� ����� �������
	for (i = 1; i < N; i++)
	{
		value = I[i];
		for (j = i - 1;
			j >= 0 && ((p[I[j]].kurs > p[value].kurs)
				||
				(p[I[j]].kurs == p[value].kurs &&
					p[I[j]].spec > p[value].spec)
				||
				(p[I[j]].kurs == p[value].kurs &&
					p[I[j]].spec == p[value].spec && p[I[j]].pedagogika > p[value].pedagogika)
				||
				(p[I[j]].kurs == p[value].kurs &&
					p[I[j]].spec == p[value].spec && p[I[j]].pedagogika == p[value].pedagogika && p[I[j]].prizv > p[value].prizv));
			j--)
		{
			I[j + 1] = I[j];
		}
		I[j + 1] = value;
	}
	return I;
}
void PrintIndexSorted(Student* p, int* I, const int N)
{
	cout << "=============================================================================================================================="
		<< endl;
	cout << "________________________________________________________|                              ����                                  |"
		<< endl;
	cout << "| � |     �������     | ���� |       ������������     | Գ���� | ���������� | ������������� | ������� ������ | ��������� |"
		<< endl;
	cout << "------------------------------------------------------------------------------------------------------------------------------"
		<< endl;

	for (int i = 0; i < N; i++)
	{
		cout << "| " << setw(1) << right << i + 1 << " ";
		cout << "| " << setw(17) << left << p[I[i]].prizv
			<< "| " << setw(4) << right << p[I[i]].kurs << " "
			<< "| " << setw(24) << left << specStr[p[I[i]].spec] << "| " << setw(7) << right << p[I[i]].fizika << "| " << setw(11) << right << p[I[i]].matematika;
		switch (p[I[i]].spec) {

		case 3:
			cout << "|" << setw(16) << "|" << setw(17) << right << p[I[i]].chslmetods << "|" << setw(13) << "|" << endl;
			break;
		case 4:
			cout << "| " << setw(14) << right << p[I[i]].programuvanna << "| " << setw(18) << "| " << setw(13) << "| " << endl;
			break;

		default:
			cout << "|" << setw(16) << "|" << setw(18) << "|" << setw(12) << right << p[I[i]].pedagogika << "|" << endl;
			break;
		}
	}
	cout << "------------------------------------------------------------------------------------------------------------------------------" << endl;
}