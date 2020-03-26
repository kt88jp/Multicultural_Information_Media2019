#pragma once
#include "Field.h"
#include "BitField.h"
#include "BitField2.h"
#include "BitField3.h"

using Field = BitField3;

class TurnInfo
{
public:
	int turn;
	int timeLeft[2];
	//int skill[2];
	int score[2];

public:
	Field field[2];
public:
	void loadTurnInfo() {
		std::cin >> turn;
		for (int i = 0; i < 2; i++) {
			std::cin >> timeLeft[i] >> field[i].ojama >> field[i].skillpoint >> score[i];
			field[i].loadField();
		}

	}

	void dump() {
		std::cerr << "Turn Info " << turn << std::endl;
		for (int i = 0; i < 2; i++) {
			std::cerr << timeLeft[i] << " " <<  field[i].ojama << " " << field[i].skillpoint << " " << score[i] << std::endl;
			field[i].dump();
		}
	}


};

