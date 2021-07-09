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
	Puzzle puzzle(8, 8); // Puzzle 객체를 생성합니다.
	int state; // 입력받은 값에 따라 상황을 결정합니다.
	while (1)
	{
		cout << "<<< BEJEWELED >>>\n\n" << "[1] Start a new random puzzle\n" << "[2] Start a pre-defined puzzle\n" << "[3] Exit\n\n";
		cout << "> Choose a menu option (1~3): ";
		cin >> state;
		if (state == 1)			random(puzzle); // 1을 입력받으면 게임 판이 랜덤으로 생성됩니다.
		else if (state == 2)	defined(puzzle);// 2를 입력받으면 이미 있는 게임판으로 게임을 진행합니다.
		else if (state == 3)	return 0; // 3을 입력받으면 프로그램이 종료됩니다.
		else // 1, 2, 3 이외의 다른 값을 입력받으면 반복문의 처음으로 돌아갑니다.
		{
			cout << "\n\n";
			continue;
		}
	}
}

void random(Puzzle& puzzle)
{
	puzzle.randomize(); //게임의 판을 랜덤으로 생성합니다.
	puzzle.printfield(); // 랜덤으로 생성한 판을 보여줍니다.
	updating(puzzle); // 랜덤으로 만들어진 판에서 체인이 있는지를 확인하고 있다면 체인을 정리합니다.
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
	int puzzlenumber; // 미리 준비된 퍼즐의 판을 선택합니다.
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
	puzzle.printfield(); // 그 판을 보여줍니다.
	updating(puzzle);// 그 판에서 체인이 있는지를 확인하고 있다면 체인을 정리합니다.
	while (1)
	{
		int gotoswap = swapping(puzzle); //swapping 함수의 반환값에 따라서 진행여부를 결정합니다.
		if (gotoswap == -1)// -1이 반환되면 main 함수의 반복문의 맨 처음으로 되돌아갑니다.
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
	if (puzzle.swapJewels(firstpoint, secondpoint) == true) // Puzzle 객체의 swapJewel함수가 참이면, 즉 입력받은 좌표가 인접해있으면 updating함수로 넘어갑니다.
	{
		puzzle.printfield();
		updating(puzzle);
		return 0;
	}
	else // swapJewel이 false를 반환하면 -1를 반환합니다.
		return -1;
}

void updating(Puzzle& puzzle)
{
	while (1) // Puzzle 객체의 update함수가 false를 반환할 때까지, 즉 체인이 없을 때까지 계속 실행됩니다.
	{
		bool checkupdate = puzzle.update();
		if (checkupdate == false)
			return;
	}
}
