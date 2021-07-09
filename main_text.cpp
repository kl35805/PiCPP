#include "Puzzle.h"

#include <iostream>
#include <vector>
#include <string>

using namespace std;

vector<string> predefined_puzzles = {
	"!#!&%*&@&!@&!!@#!@$$**%!&!&&!##&#*@$&@$%%$$*&*@$##$#@$%@#$&#%$@#",
	"#!%%@%!&@*%!&@&!#*$$%%%&#*$#@$@!$%$@%@&!%$&%&@*%*$&&*&#!$$&*$#*!",
	"*@&*@#%%&%%&!$!*%#%*!*##*$$###*$$!#&&@*$$@#&#$&$$#!!!**@##@@@!!!",
	"$#@!%@$#$&$&!!*@@!$$@$!&*@**&$&@$!#*@&*@&###!@@%&@&!%&&%##$#@@&$",
};

void random(Puzzle& puzzle);

void defined(Puzzle& puzzle);

int swapping(Puzzle& puzzle);

void updating(Puzzle& puzzle);

int main()
{
	Puzzle puzzle(8, 8); // Puzzle ��ü�� �����մϴ�.
	int state; // �Է¹��� ���� ���� ��Ȳ�� �����մϴ�.
	while (1)
	{
		cout << "<<< BEJEWELED >>>\n\n" << "[1] Start a new random puzzle\n" << "[2] Start a pre-defined puzzle\n" << "[3] Exit\n\n";
		cout << "> Choose a menu option (1~3): ";
		cin >> state;
		if (state == 1)			random(puzzle); // 1�� �Է¹����� ���� ���� �������� �����˴ϴ�.
		else if (state == 2)	defined(puzzle);// 2�� �Է¹����� �̹� �ִ� ���������� ������ �����մϴ�.
		else if (state == 3)	return 0; // 3�� �Է¹����� ���α׷��� ����˴ϴ�.
		else // 1, 2, 3 �̿��� �ٸ� ���� �Է¹����� �ݺ����� ó������ ���ư��ϴ�.
		{
			cout << "\n\n";
			continue;
		}
	}
}

void random(Puzzle& puzzle)
{
	puzzle.randomize(); //������ ���� �������� �����մϴ�.
	puzzle.printfield(); // �������� ������ ���� �����ݴϴ�.
	updating(puzzle); // �������� ������� �ǿ��� ü���� �ִ����� Ȯ���ϰ� �ִٸ� ü���� �����մϴ�.
	while (1)
	{
		int gotoswap = swapping(puzzle);
		if (gotoswap == -1)
		{
			cout << "\n\n";
			return;
		}
	}
}

void defined(Puzzle& puzzle)
{
	int puzzlenumber; // �̸� �غ�� ������ ���� �����մϴ�.
	cout << "> Choose a puzzle number (0~3) : ";
	cin >> puzzlenumber;
	if (puzzlenumber == 0)			puzzle.initialize(predefined_puzzles[0]);
	else if (puzzlenumber == 1)		puzzle.initialize(predefined_puzzles[1]);
	else if (puzzlenumber == 2)		puzzle.initialize(predefined_puzzles[2]);
	else if (puzzlenumber == 3)		puzzle.initialize(predefined_puzzles[3]);
	else
	{
		cout << "\n\n";
		return;
	}
	puzzle.printfield(); // �� ���� �����ݴϴ�.
	updating(puzzle);// �� �ǿ��� ü���� �ִ����� Ȯ���ϰ� �ִٸ� ü���� �����մϴ�.
	while (1)
	{
		int gotoswap = swapping(puzzle); //swapping �Լ��� ��ȯ���� ���� ���࿩�θ� �����մϴ�.
		if (gotoswap == -1)// -1�� ��ȯ�Ǹ� main �Լ��� �ݺ����� �� ó������ �ǵ��ư��ϴ�.
		{
			cout << "\n\n";
			return;
		}
	}
}

int swapping(Puzzle& puzzle)
{
	int row;
	int col;
	cout << "\nInput the first swap position (row, col): ";
	cin >> row >> col;
	pair<int, int>firstpoint = make_pair(row, col);
	cout << "Input the second swap position (row, col): ";
	cin >> row >> col;
	pair<int, int>secondpoint = make_pair(row, col);
	if (puzzle.swapJewels(firstpoint, secondpoint) == true) // Puzzle ��ü�� swapJewel�Լ��� ���̸�, �� �Է¹��� ��ǥ�� ������������ updating�Լ��� �Ѿ�ϴ�.
	{
		puzzle.printfield();
		updating(puzzle);
		return 0;
	}
	else // swapJewel�� false�� ��ȯ�ϸ� -1�� ��ȯ�մϴ�.
		return -1;
}

void updating(Puzzle& puzzle)
{
	while (1) // Puzzle ��ü�� update�Լ��� false�� ��ȯ�� ������, �� ü���� ���� ������ ��� ����˴ϴ�.
	{
		bool checkupdate = puzzle.update();
		if (checkupdate == false)
			return;
	}
}
