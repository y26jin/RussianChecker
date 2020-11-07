#include <iostream>
#include <vector>
#include <queue>

using namespace std;

void printBoard(vector<string> &b);
bool isVacant(vector<string> &b, int sx, int sy, int dx, int dy);
bool isJump(vector<string> &b, int sx, int sy, int dx, int dy);
vector<vector<string>> generateMovePerPiece(vector<string>& board, int ix, int iy);
