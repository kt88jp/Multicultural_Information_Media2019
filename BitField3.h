#pragma once
#include<string>
#include<iostream>
#include "Pack.h"
#include<algorithm>
#include <stdint.h>
#include <vector>
#include <assert.h>
#include <immintrin.h>

//using uint32_t = unsigned long;

extern double ojamaScoreChain[100];
extern double ojamaScoreSkill[161];

extern double INF;
extern int intINF;

class BitField3
{

	static constexpr int Width = 10;
	static constexpr int Height = 19;

	class Sfield {
	public:
		uint32_t fieldcol[Width];


		Sfield() {
			clear();
		}

		void clear() {
			memset(fieldcol, 0, sizeof(Sfield));
		}

		bool isEmpty() const {
			uint32_t result = 0;

			for (int i = 0; i < Width; i++) {
				result |= fieldcol[i];
			}

			return !result;

		}

		void dump() {
			std::cerr << "sfield info " <<std::endl;
			// 修正点その１（ここはデバッグ用の表示の間違いなので実行結果とは関係ない）
			for (int y = Height - 1; y >= 0; y--) {
				for (int x = 0; x < Width; x++) {
					if (get(x, y)) {
						std::cerr << "x";
					}
					else {
						std::cerr << ".";

					}

				}
				std::cerr << std::endl;
			}

		}

		void set(const int x, const int y) {
			if (!(x >= 0 && x < 10 && y >= 0 && y < Height)) {
				std::cerr << x << "," << y << std::endl;
			}

			assert(x >= 0 && x < Width && y >= 0 && y < Height);
			/*if (!(value >= 0 && value <= 11 && value != 10)) {
				std::cerr << x << "," << y << std::endl;
				std::cerr << "v2 " << static_cast<int>(value) << std::endl;
			}
			assert(value >= 0 && value <= 11 && value != 10);*/

			// 修正
			//fieldcol[x] |= (1 << (18 - y));
			fieldcol[x] |= (1 << y);

			/*switch (value) {
			case 0:
				fieldcol[x][0] &= (0xffffffff - (1 << y));
				fieldcol[x][1] &= (0xffffffff - (1 << y));
				fieldcol[x][2] &= (0xffffffff - (1 << y));
				fieldcol[x][3] &= (0xffffffff - (1 << y));
				break;
			case 1:
				fieldcol[x][0] &= (0xffffffff - (1 << y));
				fieldcol[x][1] |= (1 << y);
				fieldcol[x][2] &= (0xffffffff - (1 << y));
				fieldcol[x][3] &= (0xffffffff - (1 << y));
				break;
			case 2:
				fieldcol[x][0] &= (0xffffffff - (1 << y));
				fieldcol[x][1] |= (1 << y);
				fieldcol[x][2] &= (0xffffffff - (1 << y));
				fieldcol[x][3] |= (1 << y);
				break;
			case 3:
				fieldcol[x][0] &= (0xffffffff - (1 << y));
				fieldcol[x][1] |= (1 << y);
				fieldcol[x][2] |= (1 << y);
				fieldcol[x][3] &= (0xffffffff - (1 << y));
				break;
			case 4:
				fieldcol[x][0] &= (0xffffffff - (1 << y));
				fieldcol[x][1] |= (1 << y);
				fieldcol[x][2] |= (1 << y);
				fieldcol[x][3] |= (1 << y);
				break;
			case 5:
				fieldcol[x][0] |= (1 << y);
				fieldcol[x][1] |= (1 << y);
				fieldcol[x][2] |= (1 << y);
				fieldcol[x][3] |= (1 << y);
				break;
			case 6:
				fieldcol[x][0] |= (1 << y);
				fieldcol[x][1] &= (0xffffffff - (1 << y));
				fieldcol[x][2] |= (1 << y);
				fieldcol[x][3] |= (1 << y);
				break;
			case 7:
				fieldcol[x][0] |= (1 << y);
				fieldcol[x][1] &= (0xffffffff - (1 << y));
				fieldcol[x][2] |= (1 << y);
				fieldcol[x][3] &= (0xffffffff - (1 << y));
				break;
			case 8:
				fieldcol[x][0] |= (1 << y);
				fieldcol[x][1] &= (0xffffffff - (1 << y));
				fieldcol[x][2] &= (0xffffffff - (1 << y));
				fieldcol[x][3] |= (1 << y);
				break;
			case 9:
				fieldcol[x][0] |= (1 << y);
				fieldcol[x][1] &= (0xffffffff - (1 << y));
				fieldcol[x][2] &= (0xffffffff - (1 << y));
				fieldcol[x][3] &= (0xffffffff - (1 << y));
				break;
			case 11:
				fieldcol[x][0] &= (0xffffffff - (1 << y));
				fieldcol[x][1] &= (0xffffffff - (1 << y));
				fieldcol[x][2] |= (1 << y);
				fieldcol[x][3] |= (1 << y);
				break;


			}*/

		}

		void reset(const int x, const int y) {
			if (!(x >= 0 && x < 10 && y >= 0 && y < Height)) {
				std::cerr << x << "," << y << std::endl;
			}

			assert(x >= 0 && x < Width && y >= 0 && y < Height);
			/*if (!(value >= 0 && value <= 11 && value != 10)) {
				std::cerr << x << "," << y << std::endl;
				std::cerr << "v2 " << static_cast<int>(value) << std::endl;
			}
			assert(value >= 0 && value <= 11 && value != 10);*/

			// 修正
			//fieldcol[x] &= (0xffffffff - (1 << (18 - y)));
			fieldcol[x] &= (0xffffffff - (1 << y));

			/*switch (value) {
			case 0:
				fieldcol[x][0] &= (0xffffffff - (1 << y));
				fieldcol[x][1] &= (0xffffffff - (1 << y));
				fieldcol[x][2] &= (0xffffffff - (1 << y));
				fieldcol[x][3] &= (0xffffffff - (1 << y));
				break;
			case 1:
				fieldcol[x][0] &= (0xffffffff - (1 << y));
				fieldcol[x][1] |= (1 << y);
				fieldcol[x][2] &= (0xffffffff - (1 << y));
				fieldcol[x][3] &= (0xffffffff - (1 << y));
				break;
			case 2:
				fieldcol[x][0] &= (0xffffffff - (1 << y));
				fieldcol[x][1] |= (1 << y);
				fieldcol[x][2] &= (0xffffffff - (1 << y));
				fieldcol[x][3] |= (1 << y);
				break;
			case 3:
				fieldcol[x][0] &= (0xffffffff - (1 << y));
				fieldcol[x][1] |= (1 << y);
				fieldcol[x][2] |= (1 << y);
				fieldcol[x][3] &= (0xffffffff - (1 << y));
				break;
			case 4:
				fieldcol[x][0] &= (0xffffffff - (1 << y));
				fieldcol[x][1] |= (1 << y);
				fieldcol[x][2] |= (1 << y);
				fieldcol[x][3] |= (1 << y);
				break;
			case 5:
				fieldcol[x][0] |= (1 << y);
				fieldcol[x][1] |= (1 << y);
				fieldcol[x][2] |= (1 << y);
				fieldcol[x][3] |= (1 << y);
				break;
			case 6:
				fieldcol[x][0] |= (1 << y);
				fieldcol[x][1] &= (0xffffffff - (1 << y));
				fieldcol[x][2] |= (1 << y);
				fieldcol[x][3] |= (1 << y);
				break;
			case 7:
				fieldcol[x][0] |= (1 << y);
				fieldcol[x][1] &= (0xffffffff - (1 << y));
				fieldcol[x][2] |= (1 << y);
				fieldcol[x][3] &= (0xffffffff - (1 << y));
				break;
			case 8:
				fieldcol[x][0] |= (1 << y);
				fieldcol[x][1] &= (0xffffffff - (1 << y));
				fieldcol[x][2] &= (0xffffffff - (1 << y));
				fieldcol[x][3] |= (1 << y);
				break;
			case 9:
				fieldcol[x][0] |= (1 << y);
				fieldcol[x][1] &= (0xffffffff - (1 << y));
				fieldcol[x][2] &= (0xffffffff - (1 << y));
				fieldcol[x][3] &= (0xffffffff - (1 << y));
				break;
			case 11:
				fieldcol[x][0] &= (0xffffffff - (1 << y));
				fieldcol[x][1] &= (0xffffffff - (1 << y));
				fieldcol[x][2] |= (1 << y);
				fieldcol[x][3] |= (1 << y);
				break;


			}*/
		}

		bool get(const int x, const int y) const {
			if (!(x >= 0 && x < 10 && y >= 0 && y < Height)) {
				std::cerr << x << "," << y << std::endl;
			}
			assert(x >= 0 && x < Width && y >= 0 && y < Height);

			// 修正
			//return static_cast<bool>(fieldcol[x] & (1 << (18 - y)));
			return static_cast<bool>(fieldcol[x] & (1 << y));

			/*int sum = ((fieldcol[x][0] & (1 << y)) ? 1 : 0) +
				((fieldcol[x][1] & (1 << y)) ? 2 : 0) +
				((fieldcol[x][2] & (1 << y)) ? 4 : 0) +
				((fieldcol[x][3] & (1 << y)) ? 8 : 0);

			switch (sum) {
			case 0:
				return 0;
			case 2:
				return 1;
			case 10:
				return 2;
			case 6:
				return 3;
			case 14:
				return 4;
			case 15:
				return 5;
			case 13:
				return 6;
			case 5:
				return 7;
			case 9:
				return 8;
			case 1:
				return 9;
			default:
				return 11;
			}*/
		}

	};


	//static constexpr int ByteOfColumn = (Height + 1) / 2;
	//uint32_t fieldcol[Width][4];
	Sfield field[4];

	char blockNum[Width];

public:

	int ojama;
	int skillpoint = 0;

	

	void set(const int x, const int y, const int value) {
		if (!(x >= 0 && x < 10 && y >= 0 && y < Height)) {
			std::cerr << x << "," << y << std::endl;
		}

		assert(x >= 0 && x < Width && y >= 0 && y < Height);
		if (!(value >= 0 && value <= 11 && value != 10)) {
			std::cerr << x << "," << y << std::endl;
			std::cerr << "v2 " << static_cast<int>(value) << std::endl;
		}
		assert(value >= 0 && value <= 11 && value != 10);


		switch (value) {
		case 0:
			field[0].reset(x, y);
			field[1].reset(x, y);
			field[2].reset(x, y);
			field[3].reset(x, y);
			//fieldcol[x][0] &= (0xffffffff - (1 << y));
			//fieldcol[x][1] &= (0xffffffff - (1 << y));
			//fieldcol[x][2] &= (0xffffffff - (1 << y));
			//fieldcol[x][3] &= (0xffffffff - (1 << y));
			break;
		case 1:
			field[0].reset(x, y);
			field[1].set(x, y);
			field[2].reset(x, y);
			field[3].reset(x, y);
			//fieldcol[x][0] &= (0xffffffff - (1 << y));
			//fieldcol[x][1] |= (1 << y);
			//fieldcol[x][2] &= (0xffffffff - (1 << y));
			//fieldcol[x][3] &= (0xffffffff - (1 << y));
			break;
		case 2:
			field[0].reset(x, y);
			field[1].set(x, y);
			field[2].reset(x, y);
			field[3].set(x, y);
			//fieldcol[x][0] &= (0xffffffff - (1 << y));
			//fieldcol[x][1] |= (1 << y);
			//fieldcol[x][2] &= (0xffffffff - (1 << y));
			//fieldcol[x][3] |= (1 << y);
			break;
		case 3:
			field[0].reset(x, y);
			field[1].set(x, y);
			field[2].set(x, y);
			field[3].reset(x, y);
			//fieldcol[x][0] &= (0xffffffff - (1 << y));
			//fieldcol[x][1] |= (1 << y);
			//fieldcol[x][2] |= (1 << y);
			//fieldcol[x][3] &= (0xffffffff - (1 << y));
			break;
		case 4:
			field[0].reset(x, y);
			field[1].set(x, y);
			field[2].set(x, y);
			field[3].set(x, y);
			//fieldcol[x][0] &= (0xffffffff - (1 << y));
			//fieldcol[x][1] |= (1 << y);
			//fieldcol[x][2] |= (1 << y);
			//fieldcol[x][3] |= (1 << y);
			break;
		case 5:
			field[0].set(x, y);
			field[1].set(x, y);
			field[2].set(x, y);
			field[3].set(x, y);
			//fieldcol[x][0] |= (1 << y);
			//fieldcol[x][1] |= (1 << y);
			//fieldcol[x][2] |= (1 << y);
			//fieldcol[x][3] |= (1 << y);
			break;
		case 6:
			field[0].set(x, y);
			field[1].reset(x, y);
			field[2].set(x, y);
			field[3].set(x, y);
			//fieldcol[x][0] |= (1 << y);
			//fieldcol[x][1] &= (0xffffffff - (1 << y));
			//fieldcol[x][2] |= (1 << y);
			//fieldcol[x][3] |= (1 << y);
			break;
		case 7:
			field[0].set(x, y);
			field[1].reset(x, y);
			field[2].set(x, y);
			field[3].reset(x, y);
			//fieldcol[x][0] |= (1 << y);
			//fieldcol[x][1] &= (0xffffffff - (1 << y));
			//fieldcol[x][2] |= (1 << y);
			//fieldcol[x][3] &= (0xffffffff - (1 << y));
			break;
		case 8:
			field[0].set(x, y);
			field[1].reset(x, y);
			field[2].reset(x, y);
			field[3].set(x, y);
			//fieldcol[x][0] |= (1 << y);
			//fieldcol[x][1] &= (0xffffffff - (1 << y));
			//fieldcol[x][2] &= (0xffffffff - (1 << y));
			//fieldcol[x][3] |= (1 << y);
			break;
		case 9:
			field[0].set(x, y);
			field[1].reset(x, y);
			field[2].reset(x, y);
			field[3].reset(x, y);
			//fieldcol[x][0] |= (1 << y);
			//fieldcol[x][1] &= (0xffffffff - (1 << y));
			//fieldcol[x][2] &= (0xffffffff - (1 << y));
			//fieldcol[x][3] &= (0xffffffff - (1 << y));
			break;
		case 11:
			field[0].reset(x, y);
			field[1].reset(x, y);
			field[2].set(x, y);
			field[3].set(x, y);
			//fieldcol[x][0] &= (0xffffffff - (1 << y));
			//fieldcol[x][1] &= (0xffffffff - (1 << y));
			//fieldcol[x][2] |= (1 << y);
			//fieldcol[x][3] |= (1 << y);
			break;


		}
	}

	int getfield(const int x, const int y) const {
		if (!(x >= 0 && x < 10 && y >= 0 && y < Height)) {
			std::cerr << x << "," << y << std::endl;
		}
		assert(x >= 0 && x < Width && y >= 0 && y < Height);

		int sum = (field[0].get(x, y) ? 1 : 0) +
			(field[1].get(x, y) ? 2 : 0) +
			(field[2].get(x, y) ? 4 : 0) + 
			(field[3].get(x, y) ? 8 : 0);

		//int sum = ((fieldcol[x][0] & (1 << y)) ? 1 : 0) +
		//	((fieldcol[x][1] & (1 << y)) ? 2 : 0) +
		//	((fieldcol[x][2] & (1 << y)) ? 4 : 0) +
		//	((fieldcol[x][3] & (1 << y)) ? 8 : 0);

		switch (sum) {
		case 0:
			return 0;
		case 2:
			return 1;
		case 10:
			return 2;
		case 6:
			return 3;
		case 14:
			return 4;
		case 15:
			return 5;
		case 13:
			return 6;
		case 5:
			return 7;
		case 9:
			return 8;
		case 1:
			return 9;
		default:
			return 11;
		}
	}


	void setb(const int x, const int value) {
		assert(x >= 0 && x < Width);
		assert(value >= 0 && value <= Height);
		blockNum[x] = value;
	}

	void addb(const int x) {
		assert(getb(x) + 1 <= Height);
		setb(x, getb(x) + 1);
	}

	int getb(const int x) const {
		assert(x >= 0 && x < Width);
		return blockNum[x];
	}



	BitField3() {
		for (int x = 0; x < Width; x++) {
			setb(x, 0);
			//blockNum[x] = 0;
		}
	}

	void loadField() {
		std::string d;
		for (int y = Height - 4; y >= 0; y--) {
			for (int x = 0; x < Width; x++) {
				int tmp;
				std::cin >> tmp;

//				std::cerr << tmp << "," << x << "," << y << std::endl;
				//				std::cerr << tmp << std::endl;s
								//std::cerr << "lf " << tmp << std::endl;
				set(x, y, tmp);
				//std::cin >> field[x][y];
				if (getfield(x, y) != 0) {
					addb(x);
					//blockNum[x]++;
				}
			}
		}

		std::cin >> d;
	}

	void dump() {
		std::cerr << "Field Info " << std::dec << ojama << std::endl;
		for (int y = Height - 1; y >= 0; y--) {
			for (int x = 0; x < Width; x++) {
				if (getfield(x, y) == 0) {
					std::cerr << ".";
				}
				else if (getfield(x, y) == 11) {
					std::cerr << "x";

				}
				else {
					std::cerr << static_cast<int>(getfield(x, y));
				}

			}
			std::cerr << std::endl;
		}

		for (int x = 0; x < Width; x++) {
			std::cerr << std::hex << static_cast<int>(blockNum[x]);
		}
		std::cerr << std::dec << std::endl;

	}

	double transition(const int px, const int r, const Pack p, bool debug = false) {

		//debug = true;
		//std::cerr << "trans r " << r << " " << (int)p.pack[0][0] << std::endl;

		Pack p2;
		switch (r) {
		case 0:
			p2 = p;
			break;
		case 1:
			p2.pack[1][0] = p.pack[0][0];
			p2.pack[0][0] = p.pack[0][1];
			p2.pack[1][1] = p.pack[1][0];
			p2.pack[0][1] = p.pack[1][1];
			break;
		case 2:
			p2.pack[1][0] = p.pack[0][1];
			p2.pack[0][0] = p.pack[1][1];
			p2.pack[1][1] = p.pack[0][0];
			p2.pack[0][1] = p.pack[1][0];
			break;
		case 3:
			p2.pack[1][0] = p.pack[1][1];
			p2.pack[0][0] = p.pack[1][0];
			p2.pack[1][1] = p.pack[0][1];
			p2.pack[0][1] = p.pack[0][0];
			break;

		}

		if (debug) {
			std::cerr << "start " << std::endl;
			dump();
		}

		if (ojama >= Width) {
			for (int x = 0; x < Width; x++) {
				//std::cerr << "set1" << x << "," << Height - 1 - blockNum[x] << std::endl;
				//if (blockNum[x] == -1) std::cerr << "1" << std::endl;
				set(x, blockNum[x], 11);
				//				field[x][17 - blockNum[x]] = 11;
				addb(x);
				//blockNum[x]++;


			}

			ojama -= Width;
			if (debug) {
				std::cerr << "ojama drop " << std::endl;
				dump();
			}
		}

		double ojamaNum = 0;

		int chain = 0;
		//bool disappear[Width][Height];
		Sfield disappear;

		if (px == -1) {

			chain = -1;

			skillpoint = 0;

			for (int x = 0; x < Width; x++) {
				for (int y = 0; y < Height; y++) {
					if (getfield(x, y) == 5) {
						for (int dx = -1; dx <= 1; dx++) {
							for (int dy = -1; dy <= 1; dy++) {
								if (x + dx < 0 || x + dx >= Width || y + dy < 0 || y + dy >= Height ||
									getfield(x + dx, y + dy) < 1 || getfield(x + dx, y + dy) > 9) {
									continue;
								}
								//disappear[x + dx][y + dy] = true;
								disappear.set(x + dx, y + dy);
							}
						}
					}
				}
			}

			int cnt = 0;

			for (int x = 0; x < Width; x++) {
				for (int y = 0; y < Height; y++) {
					if (disappear.get(x,y)) {
						cnt++;
					}
				}
			}

			ojamaNum += ojamaScoreSkill[cnt];

		}
		else {
			//パックを落とす
			for (int x = px; x < px + 2; x++) {
				for (int y = 1; y >= 0; y--) {
					if (p2.pack[x - px][y] == 0) {
						continue;
					}
					//std::cerr << x - px << "," << y << "," << (int)p2.pack[x - px][y] << std::endl;
					//if (i >= 10 || blockNum[i] < 0 || blockNum[i] > 17) {
					//	std::cout << "a " << i << "," << 17 - blockNum[i] << std::endl;
					//}
					if (blockNum[x] > Height - 1) {
						std::cerr << "err " << static_cast<int>(blockNum[x]) << std::endl;
						dump();
					}

					int p = p2.pack[x - px][y];
					if (!(p >= 0 && p <= 11 && p != 10)) {
						std::cerr << "p " << p << "px " << px << std::endl;
					}
					//std::cerr << "pack " << static_cast<char>(p2.pack[x - px][y]) << std::endl;
					//if (Height - 1 - blockNum[x] == -1) std::cerr << static_cast<int>(blockNum[x]) << std::endl;
					//std::cerr << "a " << x << "," << Height - 1 - blockNum[x] << "," << static_cast<int>(p2.pack[x - px][y]) << std::endl;
					//field[x][17 - blockNum[x]] =  << "," << (int)p2.pack[x - px][y] << std::endl;
					set(x, blockNum[x], static_cast<char>(p2.pack[x - px][y]));
					//dump();
					//field[x][17 - blockNum[x]] = p2.pack[x - px][y];
					addb(x);
					//blockNum[x]++;
				}
			}
		}

		//dump();



		//連鎖チェック開始
		while (true) {
			//消える場所の初期化
			if (chain >= 0) {



				if (debug) {
					std::cerr << "d22 " << std::endl;
				}

				//bool isDisappeared = false;

				disappear.clear();

				//消える場所の探索
				for (int x = 0; x < Width; x++) {
					if (x < Width - 1) {
						uint32_t result =
							(~((field[3].fieldcol[x] ^ field[3].fieldcol[x + 1]) |
							(field[2].fieldcol[x] ^ field[2].fieldcol[x + 1]) |
								(field[1].fieldcol[x] ^ field[0].fieldcol[x + 1]) |
								(field[0].fieldcol[x] ^ field[1].fieldcol[x + 1]))) &
								(field[1].fieldcol[x] | field[0].fieldcol[x]);

						//std::cerr << "result " << x << "," << result << "," << std::hex <<field[0].fieldcol[x] << "," << field[0].fieldcol[x + 1] << std::dec << std::endl;
						//std::cerr << std::hex <<  (field[3].fieldcol[x] ^ field[3].fieldcol[x + 1]) << "," << (field[2].fieldcol[x] ^ field[2].fieldcol[x + 1])
						//	<< "," << (field[1].fieldcol[x] ^ field[0].fieldcol[x + 1]) << "," << (field[0].fieldcol[x] ^ field[1].fieldcol[x + 1]) << "," << (field[1].fieldcol[x] | field[0].fieldcol[x]) << "," << ~((field[3].fieldcol[x] ^ field[3].fieldcol[x + 1]) |
						//	(field[2].fieldcol[x] ^ field[2].fieldcol[x + 1]) |
						//		(field[1].fieldcol[x] ^ field[0].fieldcol[x + 1]) |
						//		(field[0].fieldcol[x] ^ field[1].fieldcol[x + 1])) << std::dec << std::endl;
						disappear.fieldcol[x] |= result;
						disappear.fieldcol[x + 1] |= result;
					}


					uint32_t result =
						(~((field[3].fieldcol[x] ^ (field[3].fieldcol[x] >> 1)) |
						(field[2].fieldcol[x] ^ (field[2].fieldcol[x] >> 1)) |
							(field[1].fieldcol[x] ^ (field[0].fieldcol[x] >> 1)) |
							(field[0].fieldcol[x] ^ (field[1].fieldcol[x] >> 1)))) &
							(field[1].fieldcol[x] | field[0].fieldcol[x]);

					disappear.fieldcol[x] |= result;
					disappear.fieldcol[x] |= (result << 1);

					if (x < Width - 1) {
						uint32_t result =
							(~((field[3].fieldcol[x] ^ (field[3].fieldcol[x + 1] << 1)) |
							(field[2].fieldcol[x] ^ (field[2].fieldcol[x + 1] << 1)) |
								(field[1].fieldcol[x] ^ (field[0].fieldcol[x + 1] << 1)) |
								(field[0].fieldcol[x] ^ (field[1].fieldcol[x + 1] << 1)))) &
								(field[1].fieldcol[x] | field[0].fieldcol[x]);

						disappear.fieldcol[x] |= result;
						disappear.fieldcol[x + 1] |= (result >> 1);
					}

					if (x < Width - 1) {
						uint32_t result =
							(~((field[3].fieldcol[x] ^ (field[3].fieldcol[x + 1] >> 1)) |
							(field[2].fieldcol[x] ^ (field[2].fieldcol[x + 1] >> 1)) |
								(field[1].fieldcol[x] ^ (field[0].fieldcol[x + 1] >> 1)) |
								(field[0].fieldcol[x] ^ (field[1].fieldcol[x + 1] >> 1)))) &
								(field[1].fieldcol[x] | field[0].fieldcol[x]);

						disappear.fieldcol[x] |= result;
						disappear.fieldcol[x + 1] |= (result << 1);
					}
				}

				

				if (debug) {
					std::cerr << "d221 " << std::endl;
				}
				if (disappear.isEmpty()) {
					break;
				}
				//std::cerr << "disappear " << std::endl;
				//disappear.dump();
			}

			//std::cerr << "before disappear " << std::hex << disappear.fieldcol[0] << "," << ~disappear.fieldcol[0] << std::dec << std::endl;
			//dump();
			//消してずらしている
			for (int x = 0; x < Width; x++) {
				//for (int y = 0; y < Height; y++) {
				//	if (disappear.get(x,y)) {
				//		for (int k = y; k > 0; k--) {
				//			int p = getfield(x, k - 1);
				//			if (!(p >= 0 && p <= 11 && p != 10)) {
				//				std::cerr << "p " << p << std::endl;
				//			}
				//			//std::cerr << "set1" << x << "," << k << std::endl;
				//			if (k == -1) std::cerr << "3" << std::endl;

				//			set(x, k, getfield(x, k - 1));
				//			//field[x][k] = field[x][k - 1];
				//		}
				//		set(x, 0, 0);
				//		//field[x][0] = 0;
				//	}
				//}

				for (int i = 0; i < 4; i++) {
					//std::cerr << std::hex << "a" <<field[i].fieldcol[x] << "," << ~(disappear.fieldcol[x]) << ",";
					field[i].fieldcol[x] = _pext_u32(field[i].fieldcol[x], ~(disappear.fieldcol[x]));
					//std::cerr << field[i].fieldcol[x] << std::dec << std::endl;
				}
			}

			//std::cerr << "after disappear " << std::endl;
			//dump();


			if (debug) {
				std::cerr << "d222 " << std::endl;
			}
			chain++;

			for (int x = 0; x < Width; x++) {
				setb(x, _mm_popcnt_u32(field[0].fieldcol[x] | field[1].fieldcol[x] | field[2].fieldcol[x] | field[3].fieldcol[x]));

				//setb(x, 0);
				////blockNum[x] = 0;
				//for (int y = 0; y < Height; y++) {
				//	if (getfield(x, y) != 0) {
				//		addb(x);
				//		//blockNum[x]++;
				//	}
				//}
			}

			//dump();

			if (debug) {
				std::cerr << "d3 " << std::endl;
			}


			if (debug) {
				std::cerr << "chain " << chain << std::endl;
				dump();
			}



		}


		for (int x = 0; x < Width; x++) {
			if (blockNum[x] > 16) {
				return -INF;
			}
		}

		if (chain > 0) {
			skillpoint += 8;
			if (skillpoint > 100) {
				skillpoint = 100;
			}
		}


		return ojamaScoreChain[chain] + ojamaNum;

	}


	double evaluation(Pack p) {

		double penalty = 0;

		for (int i = 0; i < 10; i++) {
			if (blockNum[i] > 13) {
				penalty += 100;
			}
		}

		double maxOjamaScore = 0;
		for (int i = 0; i <= 8; i++) {
			for (int j = 0; j <= 3; j++) {
				//std::cout << i << "," << j << std::endl;
				BitField3 f = *this;
				double ojamaScore = f.transition(i, j, p, false);
				maxOjamaScore = std::max(maxOjamaScore, ojamaScore);
			}
		}
		//std::cout << "end!" << std::endl;

		if (skillpoint >= 80) {
			BitField3 f = *this;
			double ojamaScore = f.transition(-1, 0, p, false);
			maxOjamaScore = std::max(maxOjamaScore, ojamaScore);
		}

		maxOjamaScore -= penalty;
		return maxOjamaScore;
	}

	//fnv1a 32 and 64 bit hash functions
	// key is the data to hash, len is the size of the data (or how much of it to hash against)
	// code license: public domain or equivalent
	// post: https://notes.underscorediscovery.com/constexpr-fnv1a/

	inline const uint32_t hash_32_fnv1a(const void* key, const uint32_t len) {

		const char* data = (char*)key;
		uint32_t hash = 0x811c9dc5;
		uint32_t prime = 0x1000193;

		for (uint32_t i = 0; i < len; ++i) {
			uint8_t value = data[i];
			hash = hash ^ value;
			hash *= prime;
		}

		return hash;

	} //hash_32_fnv1a

	inline const uint64_t hash_64_fnv1a(const void* key, const uint64_t len) {

		const char* data = (char*)key;
		uint64_t hash = 0xcbf29ce484222325;
		uint64_t prime = 0x100000001b3;

		for (int i = 0; i < len; ++i) {
			uint8_t value = data[i];
			hash = hash ^ value;
			hash *= prime;
		}

		return hash;

	} //hash_64_fnv1a


	uint64_t calc_hash() {
		return hash_64_fnv1a(this, sizeof(BitField3));
	}
};

