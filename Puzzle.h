#pragma once

#include <utility>
#include <string>
#include <vector>

enum class Jewel
{
	NONE=-1, RED, ORANGE, YELLOW, GREEN, BLUE, PURPLE, WHITE
};

class Puzzle
{
public:
	struct Chain
	{
		Jewel jewel;
		std::pair<int, int> start;
		std::pair<int, int> end;
	};

	Puzzle(int num_rows, int num_columns);

	bool initialize(const std::string& jewel_list);
	void randomize();
	bool update();

	bool swapJewels(std::pair<int, int> prev_loc, std::pair<int, int> next_loc);

	bool setJewel(std::pair<int, int> loc, Jewel jewel);
	Jewel getJewel(std::pair<int, int> loc) const;

	inline int getNumRows() const { return num_rows; }
	inline int getNumColumns() const { return num_columns; }

	static Jewel getJewelType(char letter);
	static char getJewelLetter(Jewel jewel);

	void printfield(void); // 게임 판의 상황을 보여주기 위해서 추가로 선언했습니다.

private:
	int num_rows;
	int num_columns;
	std::vector<std::vector<Jewel>> field;

	/*
	* Add as many member functions and variables as necessary
	*/
};

