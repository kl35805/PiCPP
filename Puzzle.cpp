#include "Puzzle.h"
#include <vector>
#include <cstdlib> // abs 함수를 쓰기 위해 include 했습니다.
#include <iostream>
#include <windows.h> // Sleep 함수를 쓰기 위해 include 했습니다.

using namespace std;

Puzzle::Puzzle(int num_rows, int num_columns) // Puzzle 클래스의 생성자 함수입니다.
{
	Puzzle::num_rows = num_rows;
	Puzzle::num_columns = num_columns;
	field.resize(num_rows, vector<Jewel>(num_columns, Jewel::NONE)); // Jewel 타입의 2차원 벡터를 이용하여 판을 구성했습니다.
}

bool Puzzle::initialize(const string& jewel_list)
{
	if (jewel_list.length() != num_rows * num_columns) { return false; }
	int a = 0;
	for (int i = 0; i < num_rows; i++)
	{
		for (int j = 0; j < num_columns; j++)
		{
			field[i][j] = getJewelType(jewel_list[a]); // 입력받은 문자열에 맞게 2차원 벡터에 값을 넣어줍니다.
			a++;
		}
	}

	return true;
}

void Puzzle::randomize(void)
{
	for (int i = 0; i < num_rows; i++)
	{
		for (int j = 0; j < num_columns; j++)
		{
			switch (rand() % 7)								// rand 함수를 이용해 난수를 생성하고 그 경우를 나눠서 2차원 벡터에 값을 넣어줍니다.
 			{
			case 0: field[i][j] = Jewel::RED;		break;
			case 1: field[i][j] = Jewel::ORANGE;	break;
			case 2: field[i][j] = Jewel::YELLOW;	break;
			case 3: field[i][j] = Jewel::GREEN;		break;
			case 4: field[i][j] = Jewel::BLUE;		break;
			case 5: field[i][j] = Jewel::PURPLE;	break;
			case 6: field[i][j] = Jewel::WHITE;		break;
			}
		}
	}
}

bool Puzzle::update(void)
{
	Chain chain;
	vector<Chain> chains; // Chain 클래스를 생성하고 체인의 목록을 담을 Chain 타입의 벡터를 생성합니다.

	for (int i = 0; i < num_rows; i++) // 가로 모양의 체인이 있는지 확인합니다.
	{
		for (int j = 0; j < num_columns - 2; j++) // 체인이 벡터의 범위를 넘지 않게 하기 위해 j가 num_columns - 2보다 작을때까지만 실행됩니다.
		{
			if (field[i][j] == field[i][j + 1] && field[i][j + 1] == field[i][j + 2]) 
			{
				chain.jewel = field[i][j]; // 어떤 보석의 체인인지를 정의합니다.
				chain.start = make_pair(i, j); // 체인의 시작점을 정의합니다.
				j += 2; // 체인의 최소 길이인 3을 맞춰줍니다.
				if (j == num_columns - 1) // j+=2가 실행된 직후에 j가 마지막 열에 도달한 경우입니다.
				{
					chain.end = make_pair(i, j); //체인의 끝점을 정의합니다.
					chains.push_back(chain); // 체인의 목록을 나타내는 벡터에 이 체인을 넣어줍니다.
				}
				else // j += 2가 실행된 직후에 j가 마지막 열에 도달하지 않은 경우입니다.
				{
					while (field[i][j + 1] == chain.jewel ) 
					{ 
						j++; // 체인의 보석과 같은 보석이 마지막으로 나올때까지 j를 증가시킵니다.
						if (j == num_columns - 1) // 마지막 열의 보석까지도 체인의 보석과 같으면 반복문을 빠져 나옵니다.
							break;
					}
					chain.end = make_pair(i, j); //체인의 끝점을 정의합니다.
					chains.push_back(chain); // 체인의 목록을 나타내는 벡터에 이 체인을 넣어줍니다.
				}
			}
		}
	}

	for (int j = 0; j < num_columns; j++) // 세로 모양의 체인이 있는지 확인합니다. 방식은 가로 모양의 체인을 확인하는 것과 동일합니다.
	{
		for (int i = 0; i < num_rows - 2; i++)
		{
			if (field[i][j] == field[i + 1][j] && field[i + 1][j] == field[i + 2][j])
			{
				chain.jewel = field[i][j];
				chain.start = make_pair(i, j);
				i += 2;
				if (i == num_rows - 1)
				{
					chain.end = make_pair(i, j);
					chains.push_back(chain);
				}
				else
				{
					while (field[i + 1][j] == chain.jewel)
					{
						i++;
						if (i == num_rows - 1)
							break;
					}
					chain.end = make_pair(i, j);
					chains.push_back(chain);
				}
			}
		}
	}

	if (chains.size() == 0) { return false; } // 체인의 목록이 비어있으면 체인이 없는 경우이므로 false를 반환하고 함수가 종료됩니다.

	for (const Chain& x : chains) // 각각의 체인들을 모두 NONE으로 변경합니다.
	{
		if (x.start.first == x.end.first)
		{
			for (int a = x.start.second; a <= x.end.second; a++)
				field[x.start.first][a] = Jewel::NONE;
		}
		if (x.start.second == x.end.second)
		{
			for (int a = x.start.first; a <= x.end.first; a++)
				field[a][x.start.second] = Jewel::NONE;
		}
	}

	printfield(); // NONE으로 변경된 상황을 보여줍니다.

	for (const Chain& x : chains)
	{
		if (x.start.first == x.end.first) // 가로 모양의 체인을 없애고 그 위의 보석들을 아래로 내립니다.
		{
			int chainsize = x.end.second - x.start.second + 1; 
			int a = x.start.first;
			while (a > 0)										
			{
				for (int b = x.start.second; b <= x.end.second; b++)
					field[a][b] = field[a - 1][b];
				a--;
				if (a == 0) // 가장 위의 부분은 새롭게 생성되어야 하므로 임시로 비워두기 위해 NONE으로 만들어줍니다.
				{
					for (int b = x.start.second; b <= x.end.second; b++)
						field[a][b] = Jewel::NONE;
				}
			}
		}
		if (x.start.second == x.end.second) // 세로 모양의 체인을 없애고 그 위의 보석들을 아래로 내립니다.
		{
			int chainsize = x.end.first - x.start.first + 1; // 체인의 길이를 정의합니다.
			int a = x.start.first;
			int b = 0;
			while (a > 0)
			{
				field[x.end.first - b][x.end.second] = field[x.end.first - b - chainsize][x.end.second];
				b++;
				a--;
				if (a == 0)  // 가장 위의 부분은 새롭게 생성되어야 하므로 임시로 비워두기 위해 NONE으로 만들어줍니다.
				{
					for (int c = 0; c < chainsize; c++)
						field[c][x.end.second] = Jewel::NONE;
				}
			}
		}
		for (int i = 0; i < num_rows; i++) // 보석들이 내려온 후에 비어있는 칸을 다시 채워줍니다.
		{
			for (int j = 0; j < num_columns; j++)
			{
				if (field[i][j] == Jewel::NONE)
				{
					switch (rand() % 7)
					{
					case 0: field[i][j] = Jewel::RED;		break;
					case 1: field[i][j] = Jewel::ORANGE;	break;
					case 2: field[i][j] = Jewel::YELLOW;	break;
					case 3: field[i][j] = Jewel::GREEN;		break;
					case 4: field[i][j] = Jewel::BLUE;		break;
					case 5: field[i][j] = Jewel::PURPLE;	break;
					case 6: field[i][j] = Jewel::WHITE;		break;
					}
				}
			}
		}
	}
	printfield(); // 최종상황을 보여주고 true를 반환하여 함수를 종료합니다.

	return true;
}

bool Puzzle::swapJewels(pair<int, int> prev_loc, pair<int, int> next_loc)
{
	if (prev_loc.first >= num_rows || prev_loc.first < 0) { return false; } // 입력받은 좌표가 인접해 있는지를 확인합니다.
	else if (prev_loc.second >= num_columns || prev_loc.second < 0) { return false; }// 인접해 있지 않으면 false를 반환합니다.
	else if (next_loc.first >= num_rows || next_loc.first < 0) { return false; }
	else if (next_loc.second >= num_columns || next_loc.second < 0) { return false; }
	else if (prev_loc == next_loc) { return false; }
	else if (prev_loc.first == next_loc.first && abs(prev_loc.second - next_loc.second) == 1) // 각 좌표에 있는 보석들을 서로 바꾸어줍니다.
	{
		Jewel temp1 = field[prev_loc.first][prev_loc.second];
		field[prev_loc.first][prev_loc.second] = field[next_loc.first][next_loc.second];
		field[next_loc.first][next_loc.second] = temp1;

		return true;
	}
	else if (abs(prev_loc.first - next_loc.first) == 1 && prev_loc.second == next_loc.second)
	{
		Jewel temp2 = field[prev_loc.first][prev_loc.second];
		field[prev_loc.first][prev_loc.second] = field[next_loc.first][next_loc.second];
		field[next_loc.first][next_loc.second] = temp2;

		return true;
	}
	else { return false; }
}

bool Puzzle::setJewel(pair<int, int> loc, Jewel jewel)
{
	if (loc.first >= num_rows || loc.first < 0) { return false; }
	if (loc.second >= num_columns || loc.second < 0) { return false; }
	field[loc.first][loc.second] = jewel;

	return true;
}

Jewel Puzzle::getJewel(pair<int, int> loc) const
{
	if (loc.first >= num_rows || loc.first < 0) { return Jewel::NONE; }
	if (loc.second >= num_columns || loc.second < 0) { return Jewel::NONE; }

	return field[loc.first][loc.second];
}

Jewel Puzzle::getJewelType(char letter)
{
	Jewel jewel = Jewel::NONE;

	switch (letter)
	{
	case ' ': jewel = Jewel::NONE;		break;
	case '@': jewel = Jewel::RED;		break;
	case '#': jewel = Jewel::ORANGE;	break;
	case '*': jewel = Jewel::YELLOW;	break;
	case '%': jewel = Jewel::GREEN;		break;
	case '$': jewel = Jewel::BLUE;		break;
	case '&': jewel = Jewel::PURPLE;	break;
	case '!': jewel = Jewel::WHITE;		break;
	}

	return jewel;
}

char Puzzle::getJewelLetter(Jewel jewel)
{
	char letter = ' ';

	switch (jewel)
	{
	case Jewel::NONE:	letter = ' ';		break;
	case Jewel::RED:	letter = '@';		break;
	case Jewel::ORANGE:	letter = '#';		break;
	case Jewel::YELLOW:	letter = '*';		break;
	case Jewel::GREEN:	letter = '%';		break;
	case Jewel::BLUE:	letter = '$';		break;
	case Jewel::PURPLE:	letter = '&';		break;
	case Jewel::WHITE:	letter = '!';		break;
	}

	return letter;
}

void Puzzle::printfield(void) // 현재 게임 판을 보여줍니다.
{
	cout << "\n\n";
	cout << "   0 1 2 3 4 5 6 7\n";
	cout << "  +---------------\n";
	for (int i = 0; i < num_rows; i++)
	{
		cout << i << " |";
		for (int j = 0; j < num_columns; j++)
			cout << getJewelLetter(field[i][j]) << ' ';
		cout << "\n";
	}
	Sleep(600); // 상황이 바로바로 출력되도록 하지 않고 일정 시간을 둔 뒤에 출력되도록 했습니다.
}



