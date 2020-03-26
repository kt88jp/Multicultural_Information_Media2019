#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "TurnInfo.h"
#include "Pack.h"
#include <algorithm>
#include <utility>
#include <algorithm>
#include "tt.h"

using Action = std::pair<char,char>;

class GameInfo
{
	static constexpr int MAX_TURN = 500;
	Pack pack[MAX_TURN];
	TurnInfo turninfo[MAX_TURN];
	int turn;



	
public:

	bool isContinued = true;
	std::vector<Action> plan;

	TT_TABLE tt;

	static enum SearchType {
		BEAM,
		DEPTHFIRST
	};

	SearchType stype = SearchType::BEAM;

	int sdepth = 5;
	int swidth = 100;

	int firstdepth = 8;
	int firstwidth = 500;

	void parameterDump() {
		std::cerr << "ParameterDump" << std::endl;
		if (stype == SearchType::BEAM) {
			std::cerr << "search type: Beam" << std::endl;
		}
		else {
			std::cerr << "search type: DFS" << std::endl;
		}

		std::cerr << "firstsearchdepth: " << firstdepth << " width: " << firstwidth << std::endl;

		std::cerr << "searchdepth: " << sdepth << " width: " << swidth << std::endl;
	}



	Action bestmove = std::make_pair(0, 0);
	void loadPack() {
		std::string d;
		for (int i = 0; i < 500; i++) {
			for (int y = 0; y < 2; y++) {
				for (int x = 0; x < 2; x++) {
					int p;
					std::cin >> p;
					pack[i].pack[x][y] = p;
				}
			}
			std::cin >> d;
			
		}
	}

	void loadTurnInfo(const int t) {
		turninfo[t].loadTurnInfo();
		turn = t;
	}

	void dump() {
		std::cerr << "Pack Info" << std::endl;
		for (int i = 0; i < 500; i++) {
			//std::cerr << "Turn " << i << std::endl << pack[i].pack[0][0] << pack[i].pack[1][0] << std::endl << pack[i].pack[0][1] << pack[i].pack[1][1] << std::endl;
		}

	}

	void turndump(const int turn) {
		std::cerr << "Turn Info" << std::endl;
		turninfo[turn].dump();
	}

	Field getField() {
		return turninfo[turn].field[0];
	}

	Pack getPack() {
		return pack[turn];
	}

	double dfs(int depth, int mdepth, Field f) {

		if (depth == mdepth) {
			return f.evaluation(pack[depth + turn]);
		}

		uint64_t hash = f.calc_hash();

		bool found;

		TT_DATA* ttdata = tt.findcache(hash, found);

		if (found) {
			return ttdata->get();
		}

		double maxeval = -1;

		for (int i = 0; i <= 8; i++) {
			for (int j = 0; j < 4; j++) {
				Field nextf = f;
				double chain = nextf.transition(i, j, pack[depth + turn]);

				if (depth == 0 && chain >= 9) {
					bestmove = std::make_pair(i, j);
					std::cerr << "chain!! " << chain << " " << i << "," << j << std::endl;
					nextf = f;
					nextf.transition(i, j, pack[depth + turn], true);
					ttdata->set(hash, chain);
					return chain;
				}

				double cureval;

				if (chain == -1) {
					cureval = -1;
				}
				else {
					cureval = dfs(depth + 1, mdepth, nextf);
				}
				

				if (maxeval < cureval) {
					maxeval = cureval;
					if (depth == 0) {
						bestmove = std::make_pair(i, j);
					}
				}

			}
		}

		ttdata->set(hash, maxeval);

		return maxeval;
	}

	//フィールドデータクラス
	class Fielddata {
	public:
		Fielddata() {}
		Fielddata(const Field& f): curfld(f), prevfldata(nullptr), eval(0), movement(std::make_pair(0,0)) {}
		Fielddata(const Field& f, Fielddata* pf, const double ev, std::pair<int,int> mv) : curfld(f), prevfldata(pf), eval(ev), movement(mv) {}
		Field curfld;
		Fielddata* prevfldata;
		std::pair<int, int> movement;
		double eval;

		void dump() {
			std::cerr << "field dump " << std::endl;
			curfld.dump();
			std::cerr << "eval " << eval << " " << static_cast<int>(movement.first) << "," << static_cast<int>(movement.second) << std::endl;
		}
	};

	using Fields = std::vector<std::vector<Fielddata>>;
	//using Fields = std::vector<std::vector<std::pair<Field, std::pair<Field*, double>>>>;
	static bool greaterSecond(const Fielddata& f, const Fielddata& s) {
		return f.eval > s.eval;
	}

	
	void beam_search(int d, int w, Field nowf) {
		Fields fields(d + 1);
		Fielddata firstfld(nowf);

		std::cerr << "bsearch start " << turn << std::endl;
		nowf.dump();
		fields[0].push_back(firstfld);
		for (int i = 0; i < d; i++) {
			//std::cerr << i << std::endl;
			int cnt = 0;
			for (auto& f : fields[i]) {
				if (cnt >= w) {
					break;
				}
				cnt++;

				for (int j = 0; j < 9; j++) {
					for (int k = 0; k < 4; k++) {
				
						Field nextf = f.curfld;
						double ojamascore;
						
						ojamascore = nextf.transition(j, k, pack[i + turn]);
						//std::cerr << "oscore" << ojamascore << std::endl;
						if (ojamascore < 0) {
							continue;
						}
						if (ojamascore > ojamaScoreChain[10] && i == 0) {
							bestmove = std::make_pair(j, k);
							return;
						}
						double hyouka = nextf.evaluation(pack[i + turn + 1]);
						
						Fielddata nextfld(nextf, &f, hyouka, std::make_pair(j, k));

						fields[i + 1].push_back(nextfld);
	
					}
				}

				
			}



			std::sort(fields[i + 1].begin(), fields[i + 1].end(), greaterSecond);


		}

		if (nowf.skillpoint >= 80) {
			Field nextf = nowf;
			double ojamascore;

			ojamascore = nextf.transition(-1, 0, pack[turn]);

			if (ojamascore > 0) {
				bestmove = std::make_pair(-1, 0);
				return;
			}


		}

		Fielddata *fptr = &(fields[d][0]);
		Fielddata* bestfptr = nullptr;
		std::cerr << "best " << fptr << std::endl;

		plan.clear();
		while (fptr) {

			plan.push_back(fptr->movement);

			fptr->dump();
			if (fptr->prevfldata->prevfldata == nullptr) {

				bestfptr = fptr;
				break;
			}
			fptr = fptr->prevfldata;
		}

		std::reverse(plan.begin(), plan.end());

		for (auto& p : plan) {
			std::cerr << static_cast<int>(p.first) << "," << static_cast<int>(p.second) << std::endl;
		}

		if (bestfptr != nullptr) {


			bestmove = fptr->movement;

		}
		else {
			std::cerr << "error!" << std::endl;
		}


	}

};

