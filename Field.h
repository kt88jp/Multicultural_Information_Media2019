#pragma once
#include<string>
#include<iostream>
#include "Pack.h"
#include<algorithm>
#include <stdint.h>
#include <vector>
#include <assert.h>

extern double ojamaScoreChain[100];
extern double ojamaScoreSkill[161];

extern double INF;
extern int intINF;

class NormalField
{
	static constexpr int Width = 10;
	static constexpr int Height = 19;
	char field[Width][Height];

	char blockNum[Width];



	
public:

	int ojama;
	int skillpoint = 0;

	void set(const int x, const int y, const char value) {
		if (!(x >= 0 && x < 10 && y >= 0 && y < Height)) {
			std::cerr << x << "," << y << std::endl;
		}

		assert(x >= 0 && x < Width && y >= 0 && y < Height);
		if (!(value >= 0 && value <= 11 && value != 10)) {
			std::cerr << x << "," << y << std::endl;
			std::cerr << "v2 " << static_cast<int>(value) << std::endl;
		}
		assert(value >= 0 && value <= 11 && value != 10);
//		if (x >= 0 && x < 10 && y >= 0 && y < 18) {
			field[x][y] = value;
//		}
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



	NormalField() {
		for (int x = 0; x < Width; x++) {
			setb(x, 0);
			//blockNum[x] = 0;
		}
	}

	void loadField() {
		std::string d;
		for (int y = 3; y < Height; y++) {
			for (int x = 0; x < Width; x++) {
				int tmp;
				std::cin >> tmp;
//				std::cerr << tmp << std::endl;s
				//std::cerr << "lf " << tmp << std::endl;
				set(x, y, tmp);
				//std::cin >> field[x][y];
				if (field[x][y] != 0) {
					addb(x);
					//blockNum[x]++;
				}
			}
		}

		std::cin >> d;
	}

	void dump() {
		std::cerr << "Field Info " << std::dec << ojama << std::endl;
		for (int y = 0; y < Height; y++) {
			for (int x = 0; x < Width; x++) {
				if (field[x][y] == 0) {
					std::cerr << ".";
				} 
				else if(field[x][y] == 11){
					std::cerr << "x";
					
				}
				else {
					std::cerr << static_cast<int>(field[x][y]);
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
		//std::cerr << "trans" << std::endl;

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
				if (Height - 1 - blockNum[x] == -1) std::cerr << "1" << std::endl;
				set(x, Height - 1 - blockNum[x], 11);
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
		bool disappear[Width][Height];
		
		if (px == -1) {

			chain = -1;

			skillpoint = 0;

			for (int x = 0; x < Width; x++) {
				for (int y = 0; y < Height; y++) {
					if (field[x][y] == 5) {
						for (int dx = -1; dx <= 1; dx++) {
							for (int dy = -1; dy <= 1; dy++) {
								if (x + dx < 0 || x + dx >= Width || y + dy < 0 || y + dy >= Height ||
									field[x + dx][y + dy] < 1 || field[x + dx][y + dy] > 9) {
									continue;
								}
								disappear[x + dx][y + dy] = true;
							}
						}
					}
				}
			}

			int cnt = 0;

			for (int x = 0; x < Width; x++) {
				for (int y = 0; y < Height; y++) {
					if (disappear[x][y]) {
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
					if (Height - 1 - blockNum[x] == -1) std::cerr << static_cast<int>(blockNum[x]) << std::endl;
					set(x, Height - 1 - blockNum[x], static_cast<char>(p2.pack[x - px][y]));
					//field[x][17 - blockNum[x]] = p2.pack[x - px][y];
					addb(x);
					//blockNum[x]++;
				}
			}
		}



		//連鎖チェック開始
		while (true) {
			//消える場所の初期化
			if (chain >= 0) {


				for (int x = 0; x < Width; x++) {
					for (int y = 0; y < Height; y++) {
						assert(x >= 0 && x < Width && y >= 0 && y < Height);
						disappear[x][y] = false;
					}
				}
				if (debug) {
					std::cerr << "d22 " << std::endl;
				}
				bool isDisappeared = false;

				//消える場所の探索
				for (int x = 0; x < Width; x++) {
					for (int y = 0; y < Height; y++) {
						if (debug) {
							std::cerr << "d2210 " << x << "," << y << std::endl;
						}
						int cblock = field[x][y];
						if (cblock == 0 || cblock == 11) {
							continue;
						}
						for (int dx = -1; dx <= 1; dx++) {
							for (int dy = -1; dy <= 1; dy++) {
								if (dx == dy && dx == 0) {
									continue;
								}
								if (x + dx < 0 || x + dx >= Width || y + dy < 0 || y + dy >= Height) {
									continue;
								}
								int ablock = field[x + dx][y + dy];
								if (ablock + cblock == 10) {
									assert(x >= 0 && x < Width && y >= 0 && y < Height);
									disappear[x][y] = true;
									assert(x + dx >= 0 && x + dx < Width && y + dy >= 0 && y + dy < Height);
									disappear[x + dx][y + dy] = true;
									isDisappeared = true;
								}
							}
						}
					}
				}

				if (debug) {
					std::cerr << "d221 " << std::endl;
				}
				if (!isDisappeared) {
					break;
				}
			}

			//消してずらしている
			for (int x = 0; x < Width; x++) {
				for (int y = 0; y < Height; y++) {
					if (disappear[x][y]) {
						for (int k = y; k > 0; k--) {
							int p = field[x][k - 1];
							if (!(p >= 0 && p <= 11 && p != 10)) {
								std::cerr << "p " << p << std::endl;
							}
							//std::cerr << "set1" << x << "," << k << std::endl;
							if (k == -1) std::cerr << "3" << std::endl;

							set(x, k, field[x][k - 1]);
							//field[x][k] = field[x][k - 1];
						}
						set(x, 0, 0);
						//field[x][0] = 0;
					}
				}
			}

			if (debug) {
				std::cerr << "d222 " << std::endl;
			}
			chain++;

			for (int x = 0; x < Width; x++) {
				setb(x, 0);
				//blockNum[x] = 0;
				for (int y = 0; y < Height; y++) {
					if (field[x][y] != 0) {
						addb(x);
						//blockNum[x]++;
					}
				}
			}

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
				NormalField f = *this;
				double ojamaScore = f.transition(i, j, p, false);
				maxOjamaScore = std::max(maxOjamaScore, ojamaScore);
			}
		}
		//std::cout << "end!" << std::endl;

		if (skillpoint >= 80) {
			NormalField f = *this;
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
		return hash_64_fnv1a(this, sizeof(NormalField));
	}
};

