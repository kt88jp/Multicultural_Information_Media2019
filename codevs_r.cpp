// codevs_r.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include "GameInfo.h"
#include "Field.h"
#include "stopwatch.h"
#include <string.h>
#include <cmath>
#include <limits>

GameInfo gameinfo;

double ojamaScoreChain[100];
double ojamaScoreSkill[161];

void init() {
	double score = 0;
	for (int i = 1; i < 100; i++) {
		score += floor(pow(1.3, i));
		ojamaScoreChain[i] = floor(score / 2.0);
	}

	for (int i = 1; i < 161; i++) {
		ojamaScoreSkill[i] = floor(floor(25.0 * pow(2.0, static_cast<double>(i) / 12.0)) / 2.0);
	}
}

int main(int argc, char** argv)
{

	init();


	for (int i = 1; i < argc; i++) {
		if (strcmp("-d", argv[i]) == 0 && i + 1 < argc) {
			gameinfo.sdepth = strtol(argv[i + 1], NULL, 10);
			i++;
		}
		if (strcmp("-w", argv[i]) == 0 && i + 1 < argc) {
			gameinfo.swidth = strtol(argv[i + 1], NULL, 10);
			i++;
		}
		if (strcmp("-fd", argv[i]) == 0 && i + 1 < argc) {
			gameinfo.firstdepth = strtol(argv[i + 1], NULL, 10);
			i++;
		}
		if (strcmp("-fw", argv[i]) == 0 && i + 1 < argc) {
			gameinfo.firstwidth = strtol(argv[i + 1], NULL, 10);
			i++;
		}
		if (strcmp("-s", argv[i]) == 0 && i + 1 < argc) {
			if (strcmp("d", argv[i + 1]) == 0) {
				gameinfo.stype = GameInfo::SearchType::DEPTHFIRST;
			}
			else if (strcmp("b", argv[i + 1]) == 0) {
				gameinfo.stype = GameInfo::SearchType::BEAM;
			}
			i++;
		}
		if (strcmp("-h", argv[i]) == 0) {
			std::cerr << "usage:" << std::endl;
			std::cerr << " -d depth" << std::endl;
			return 0;
		}
	}
	gameinfo.parameterDump();
	//return 0;

	std::cout << "MyAI" << std::endl << std::flush;

	gameinfo.loadPack();

	gameinfo.dump();


	for (int i = 0; i < 500; i++) {
		gameinfo.loadTurnInfo(i);

		gameinfo.tt.clear();

		std::unique_ptr<Stopwatch> sw;
		sw = Stopwatch::startNew();
		if (gameinfo.stype == GameInfo::SearchType::DEPTHFIRST) {
			double h = gameinfo.dfs(0, gameinfo.sdepth, gameinfo.getField());
			std::cerr << h << std::endl;
		}
		else {
			if (i == 0) {
				gameinfo.beam_search(gameinfo.firstdepth, gameinfo.firstwidth, gameinfo.getField());
			}

			if (gameinfo.getField().ojama >= 10 || i >= gameinfo.plan.size()) {
				gameinfo.isContinued = false;
			}
			std::cerr << "ojama" << gameinfo.getField().ojama << " plansize" << gameinfo.plan.size() << std::endl;
			std::cerr << "isc," << i << "," << gameinfo.isContinued << std::endl;

			if (gameinfo.isContinued) {
				gameinfo.bestmove = gameinfo.plan[i];
			}
			else {
				gameinfo.beam_search(gameinfo.sdepth, gameinfo.swidth, gameinfo.getField());
			}
		
		}
		/*double h = gameinfo.dfs(0, 2, gameinfo.getField());*/
		if (gameinfo.bestmove.first >= 0) {


			std::cout << static_cast<int>(gameinfo.bestmove.first) << " " << static_cast<int>(gameinfo.bestmove.second) << std::endl << std::flush;
			//gameinfo.turndump(i);
		}
		else {
			std::cout << "S" << std::endl;
		}
		gameinfo.tt.dump_count();

		std::cerr << sw->getElapsedMilliseconds() << "ms" << std::endl;

		
	}

}

// プログラムの実行: Ctrl + F5 または [デバッグ] > [デバッグなしで開始] メニュー
// プログラムのデバッグ: F5 または [デバッグ] > [デバッグの開始] メニュー

// 作業を開始するためのヒント: 
//    1. ソリューション エクスプローラー ウィンドウを使用してファイルを追加/管理します 
//   2. チーム エクスプローラー ウィンドウを使用してソース管理に接続します
//   3. 出力ウィンドウを使用して、ビルド出力とその他のメッセージを表示します
//   4. エラー一覧ウィンドウを使用してエラーを表示します
//   5. [プロジェクト] > [新しい項目の追加] と移動して新しいコード ファイルを作成するか、[プロジェクト] > [既存の項目の追加] と移動して既存のコード ファイルをプロジェクトに追加します
//   6. 後ほどこのプロジェクトを再び開く場合、[ファイル] > [開く] > [プロジェクト] と移動して .sln ファイルを選択します
