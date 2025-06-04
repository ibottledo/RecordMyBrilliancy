#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
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

pair<int, int> coord(const string& pos) {
    return {8 - (pos[1] - '0'), pos[0] - 'a'};
}

void initializeBoard(char board[8][8]) {
    string init[8] = {
        "rnbqkbnr",
        "pppppppp",
        "........",
        "........",
        "........",
        "........",
        "PPPPPPPP",
        "RNBQKBNR"
    };
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            board[i][j] = init[i][j];
        }
    }
}

void printBoard(char board[8][8]) {
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            cout << board[i][j] << ' ';
        }
        cout << '\n';
    }
}

int main() {
    string moveList;
    getline(cin, moveList);

    char board[8][8];
    initializeBoard(board);

    bool isWhiteTurn = true;

    for (size_t i = 0; i + 1 < moveList.size(); i += 2) {
        string code = moveList.substr(i, 2);
        if (T.find(code[0]) == string::npos || T.find(code[1]) == string::npos) continue;

        Move move = decodeMove(code);

        // if (!move.drop.empty()) continue; // 드롭은 패스 (버그일 수 있음)
        if (move.from.empty() || move.to.empty()) continue;

        auto [fromY, fromX] = coord(move.from);
        auto [toY, toX] = coord(move.to);

        char piece = board[fromY][fromX];
        if (move.promotion.size() == 1) {
            piece = isWhiteTurn ? toupper(move.promotion[0]) : move.promotion[0];
        }

        board[fromY][fromX] = '.';
        board[toY][toX] = piece;

        // 캐슬링
        if (piece == 'K' && move.from == "e1") {
            if (move.to == "g1") board[7][7] = '.', board[7][5] = 'R'; // O-O
            if (move.to == "c1") board[7][0] = '.', board[7][3] = 'R'; // O-O-O
        }
        if (piece == 'k' && move.from == "e8") {
            if (move.to == "g8") board[0][7] = '.', board[0][5] = 'r'; // O-O
            if (move.to == "c8") board[0][0] = '.', board[0][3] = 'r'; // O-O-O
        }

        isWhiteTurn = !isWhiteTurn;
        printBoard(board);  // 매번 보드 출력
        cout << "------------------------" << i / 2 + 1 << '\n';
    }

    
    return 0;
}
