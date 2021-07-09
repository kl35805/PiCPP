#include "Puzzle.h"
#include <vector>
#include <cstdlib> // abs �Լ��� ���� ���� include �߽��ϴ�.
#include <iostream>
#include <windows.h> // Sleep �Լ��� ���� ���� include �߽��ϴ�.

using namespace std;

Puzzle::Puzzle(int num_rows, int num_columns) // Puzzle Ŭ������ ������ �Լ��Դϴ�.
{
	Puzzle::num_rows = num_rows;
	Puzzle::num_columns = num_columns;
	field.resize(num_rows, vector<Jewel>(num_columns, Jewel::NONE)); // Jewel Ÿ���� 2���� ���͸� �̿��Ͽ� ���� �����߽��ϴ�.
}

bool Puzzle::initialize(const string& jewel_list)
{
	if (jewel_list.length() != num_rows * num_columns) { return false; }
	int a = 0;
	for (int i = 0; i < num_rows; i++)
	{
		for (int j = 0; j < num_columns; j++)
		{
			field[i][j] = getJewelType(jewel_list[a]); // �Է¹��� ���ڿ��� �°� 2���� ���Ϳ� ���� �־��ݴϴ�.
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
			switch (rand() % 7)								// rand �Լ��� �̿��� ������ �����ϰ� �� ��츦 ������ 2���� ���Ϳ� ���� �־��ݴϴ�.
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
	vector<Chain> chains; // Chain Ŭ������ �����ϰ� ü���� ����� ���� Chain Ÿ���� ���͸� �����մϴ�.

	for (int i = 0; i < num_rows; i++) // ���� ����� ü���� �ִ��� Ȯ���մϴ�.
	{
		for (int j = 0; j < num_columns - 2; j++) // ü���� ������ ������ ���� �ʰ� �ϱ� ���� j�� num_columns - 2���� ������������ ����˴ϴ�.
		{
			if (field[i][j] == field[i][j + 1] && field[i][j + 1] == field[i][j + 2]) 
			{
				chain.jewel = field[i][j]; // � ������ ü�������� �����մϴ�.
				chain.start = make_pair(i, j); // ü���� �������� �����մϴ�.
				j += 2; // ü���� �ּ� ������ 3�� �����ݴϴ�.
				if (j == num_columns - 1) // j+=2�� ����� ���Ŀ� j�� ������ ���� ������ ����Դϴ�.
				{
					chain.end = make_pair(i, j); //ü���� ������ �����մϴ�.
					chains.push_back(chain); // ü���� ����� ��Ÿ���� ���Ϳ� �� ü���� �־��ݴϴ�.
				}
				else // j += 2�� ����� ���Ŀ� j�� ������ ���� �������� ���� ����Դϴ�.
				{
					while (field[i][j + 1] == chain.jewel ) 
					{ 
						j++; // ü���� ������ ���� ������ ���������� ���ö����� j�� ������ŵ�ϴ�.
						if (j == num_columns - 1) // ������ ���� ���������� ü���� ������ ������ �ݺ����� ���� ���ɴϴ�.
							break;
					}
					chain.end = make_pair(i, j); //ü���� ������ �����մϴ�.
					chains.push_back(chain); // ü���� ����� ��Ÿ���� ���Ϳ� �� ü���� �־��ݴϴ�.
				}
			}
		}
	}

	for (int j = 0; j < num_columns; j++) // ���� ����� ü���� �ִ��� Ȯ���մϴ�. ����� ���� ����� ü���� Ȯ���ϴ� �Ͱ� �����մϴ�.
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

	if (chains.size() == 0) { return false; } // ü���� ����� ��������� ü���� ���� ����̹Ƿ� false�� ��ȯ�ϰ� �Լ��� ����˴ϴ�.

	for (const Chain& x : chains) // ������ ü�ε��� ��� NONE���� �����մϴ�.
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

	printfield(); // NONE���� ����� ��Ȳ�� �����ݴϴ�.

	for (const Chain& x : chains)
	{
		if (x.start.first == x.end.first) // ���� ����� ü���� ���ְ� �� ���� �������� �Ʒ��� �����ϴ�.
		{
			int chainsize = x.end.second - x.start.second + 1; 
			int a = x.start.first;
			while (a > 0)										
			{
				for (int b = x.start.second; b <= x.end.second; b++)
					field[a][b] = field[a - 1][b];
				a--;
				if (a == 0) // ���� ���� �κ��� ���Ӱ� �����Ǿ�� �ϹǷ� �ӽ÷� ����α� ���� NONE���� ������ݴϴ�.
				{
					for (int b = x.start.second; b <= x.end.second; b++)
						field[a][b] = Jewel::NONE;
				}
			}
		}
		if (x.start.second == x.end.second) // ���� ����� ü���� ���ְ� �� ���� �������� �Ʒ��� �����ϴ�.
		{
			int chainsize = x.end.first - x.start.first + 1; // ü���� ���̸� �����մϴ�.
			int a = x.start.first;
			int b = 0;
			while (a > 0)
			{
				field[x.end.first - b][x.end.second] = field[x.end.first - b - chainsize][x.end.second];
				b++;
				a--;
				if (a == 0)  // ���� ���� �κ��� ���Ӱ� �����Ǿ�� �ϹǷ� �ӽ÷� ����α� ���� NONE���� ������ݴϴ�.
				{
					for (int c = 0; c < chainsize; c++)
						field[c][x.end.second] = Jewel::NONE;
				}
			}
		}
		for (int i = 0; i < num_rows; i++) // �������� ������ �Ŀ� ����ִ� ĭ�� �ٽ� ä���ݴϴ�.
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
	printfield(); // ������Ȳ�� �����ְ� true�� ��ȯ�Ͽ� �Լ��� �����մϴ�.

	return true;
}

bool Puzzle::swapJewels(pair<int, int> prev_loc, pair<int, int> next_loc)
{
	if (prev_loc.first >= num_rows || prev_loc.first < 0) { return false; } // �Է¹��� ��ǥ�� ������ �ִ����� Ȯ���մϴ�.
	else if (prev_loc.second >= num_columns || prev_loc.second < 0) { return false; }// ������ ���� ������ false�� ��ȯ�մϴ�.
	else if (next_loc.first >= num_rows || next_loc.first < 0) { return false; }
	else if (next_loc.second >= num_columns || next_loc.second < 0) { return false; }
	else if (prev_loc == next_loc) { return false; }
	else if (prev_loc.first == next_loc.first && abs(prev_loc.second - next_loc.second) == 1) // �� ��ǥ�� �ִ� �������� ���� �ٲپ��ݴϴ�.
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

void Puzzle::printfield(void) // ���� ���� ���� �����ݴϴ�.
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
	Sleep(600); // ��Ȳ�� �ٷιٷ� ��µǵ��� ���� �ʰ� ���� �ð��� �� �ڿ� ��µǵ��� �߽��ϴ�.
}



