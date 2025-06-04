#include <iostream>
#include <string>
#include <vector>
using namespace std;

const string T = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!?{~}(^)[_]@#$,./&-*++=";
const string promotionPieces = "qnrbkp";
const string fileMap = "abcdefgh";

struct Move {
    string from;
    string to;
    string promotion;
    string drop;
};

Move decodeMove(const string& code) {
    Move move;
    if (code.size() != 2) return move;

    int b = T.find(code[0]);
    int a = T.find(code[1]);

    if (a > 63) {
        move.promotion = string(1, promotionPieces[(a - 64) / 3]);
        a = b + (b < 16 ? -8 : 8) + ((a - 1) % 3) - 1;
    }

    if (b > 75) {
        move.drop = string(1, promotionPieces[b - 79]);
    } else {
        move.from = string(1, fileMap[b % 8]) + to_string((b / 8) + 1);
    }

    move.to = string(1, fileMap[a % 8]) + to_string((a / 8) + 1);
    return move;
}

string decodeMoveList(const string& moveList) {
    string pgn;
    int ply = 0;

    for (size_t i = 0; i + 1 < moveList.size(); i += 2) {
        string code = moveList.substr(i, 2);

        // 무효 문자 처리
        if (T.find(code[0]) == string::npos || T.find(code[1]) == string::npos)
            continue;

        Move move = decodeMove(code);

        if (ply % 2 == 0)
            pgn += to_string(ply / 2 + 1) + ". ";

        if (!move.drop.empty()) {
            pgn += move.drop + "@";
        } else if (!move.from.empty()) {
            pgn += move.from + "-";
        }

        pgn += move.to;

        if (!move.promotion.empty()) {
            pgn += "=" + move.promotion;
        }

        pgn += " ";
        ++ply;
    }

    return pgn;
}

int main() {
    string moveList;
    getline(cin, moveList);
    
    
    string decodedPGN = decodeMoveList(moveList);
    cout << "Decoded moves:\n" << decodedPGN << endl;

    return 0;
}
