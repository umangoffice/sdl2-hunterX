#include "LevelMaker.h"
#include "ExternDecl.h"

void LevelMaker::make_level(const char* tilemap[], const char* path_float, const char* path_mudUp1, const char* path_top1, const char* path_top2, const char* path_top3, const char* path_mid1, const char* path_mid2, const char* path_mid3, const char* path_bot1, const char* path_bot2, const char* path_bot3, const char* path_grassUp1, const char* path_mudDown1, const char* path_grassUp2) {
	for (int count = 0; count < 11; count++) {
		for (int index = 0; index < 28; index++) {
			int x, y;
			x = index * 50;
			y = count * 50;

			if (tilemap[count][index] == '1') {
				group_of_tiles.push_back(new Tile(x, y, path_top1));
			}

			if (tilemap[count][index] == '2') {
				group_of_tiles.push_back(new Tile(x, y, path_top2));
			}

			if (tilemap[count][index] == '3') {
				group_of_tiles.push_back(new Tile(x, y, path_top3));
			}

			if (tilemap[count][index] == '4') {
				group_of_tiles.push_back(new Tile(x, y, path_mid1));
			}

			if (tilemap[count][index] == '5') {
				group_of_tiles.push_back(new Tile(x, y, path_mid2));
			}

			if (tilemap[count][index] == '6') {
				group_of_tiles.push_back(new Tile(x, y, path_mid3));
			}

			if (tilemap[count][index] == '7') {
				group_of_tiles.push_back(new Tile(x, y, path_bot1));
			}

			if (tilemap[count][index] == '8') {
				group_of_tiles.push_back(new Tile(x, y, path_bot2));
			}

			if (tilemap[count][index] == '9') {
				group_of_tiles.push_back(new Tile(x, y, path_bot3));
			}

			if (tilemap[count][index] == '(') {
				group_of_tiles.push_back(new Tile(x, y, path_grassUp1));
			}

			if (tilemap[count][index] == '>') {
				group_of_tiles.push_back(new Tile(x, y, path_mudDown1));
			}

			if (tilemap[count][index] == ')') {
				group_of_tiles.push_back(new Tile(x, y, path_grassUp2));
			}

			if (tilemap[count][index] == '{') {
				group_of_tiles.push_back(new Tile(x, y, path_mudUp1));
			}

			if (tilemap[count][index] == '-') {
				group_of_tiles.push_back(new Tile(x, y, path_float));
			}
		}
	}
}