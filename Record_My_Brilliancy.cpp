// 최종 보고서로 제출할 완성 코드
#include <iostream> 
#include <string>
#include <vector>

using namespace std;

// moveList decoder
class MoveDecoder {
private:
    const string T = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!?{~}(^)[_]@#$,./&-*++=";
    const string promotionPieces = "qnrbkp";
    const string fileMap = "abcdefgh";
public:
    struct Move {
        string from, to, promotion, drop;
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
};

// decode한 move를 바탕으로 체스판을 출력(탁월수 직전 모습)
class ChessBoard {
private:
    pair<int, int> coord(const string& pos) {
        return {8 - (pos[1] - '0'), pos[0] - 'a'};
    }
    char board[8][8] = 
    {
        {'r', 'n', 'b', 'q', 'k', 'b', 'n', 'r'},
        {'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p'},
        {'.', '.', '.', '.', '.', '.', '.', '.'},
        {'.', '.', '.', '.', '.', '.', '.', '.'},
        {'.', '.', '.', '.', '.', '.', '.', '.'},
        {'.', '.', '.', '.', '.', '.', '.', '.'},
        {'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P'},
        {'R', 'N', 'B', 'Q', 'K', 'B', 'N', 'R'}
    };
    void printBoard() const{
        for (int i = 0; i < 8; ++i) {
            for (int j = 0; j < 8; ++j) {
                cout << board[i][j] << ' ';
            }
            cout << '\n';
        }
    }
    // moveList에서 move를 decode한 후, board에 적용
    // 앙파상 구현 필요?
    void applyMove(const MoveDecoder::Move& move, bool isWhiteTurn) {
        if (move.from.empty() || move.to.empty()) return;

        auto [fromY, fromX] = coord(move.from);
        auto [toY, toX] = coord(move.to);

        // 프로모션
        char piece = board[fromY][fromX];
        if (move.promotion.size() == 1) {
            piece = isWhiteTurn ? toupper(move.promotion[0]) : move.promotion[0];   // toupper()는 대문자로 변환
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
    }
public:
    // Brilliant Move 직전의 보드를 출력
    void printChessBoard(const string& moveList, const int& brilliantMoveIndex) {
        for (int i = 0; i < brilliantMoveIndex; ++i) {
            string code = moveList.substr(i * 2, 2);
            MoveDecoder::Move move = MoveDecoder().decodeMove(code);
            applyMove(move, i % 2 == 0);
        }
        printBoard();
    }
};

int main() {
    // string moveList = "lBZJcD2Ugv6Lmu5Qks0Sdr45fH9RDw1TblUMeg3NpFMEveRwnwWOfLSLHQXQry7RyO!0et8!tD5jlr0UDURwUDwughuDOQDCagEw";

    // int brilliantMoveIndex = 40;
    // ChessBoard chessBoard;
    // // 탁월수 직전의 보드를 출력
    // chessBoard.printChessBoard(moveList, brilliantMoveIndex - 1);

    return 0;
}

// 브랜치 확인 주석