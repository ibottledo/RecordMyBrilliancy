// 최종 보고서로 제출할 완성 코드
#include <iostream> 
#include <string>
#include <vector>
#include <curl/curl.h>
#include <nlohmann/json.hpp>
#include <regex>

using namespace std;
using json = nlohmann::json;

// 콜백 함수: 서버 응답을 문자열로 저장
static size_t WriteCallback(void* contents, size_t size, size_t nmemb, string* output) {
    size_t totalSize = size * nmemb;
    output->append((char*)contents, totalSize);
    return totalSize;
}

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

// 입력받은 string으로 작동
// API에서 게임 정보를 가져오는 클래스
class ChessFetcher {    
private:
    int plyCount;
    string white, black, result, date, userId, moveList, url;

    // API에서 게임 정보를 가져오는 함수 (월별 게임 정보도 가져옴)
    void fetchGame() {
        CURL* curl;
        CURLcode res;
        string readBuffer;

        curl = curl_easy_init();
        if (curl) {
            curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
            curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
            curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
            curl_easy_setopt(curl, CURLOPT_USERAGENT, "Mozilla/5.0");

            res = curl_easy_perform(curl);

            if (res != CURLE_OK) {
                cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << endl;
            } else {
                try {
                    json j = json::parse(readBuffer);

                    plyCount = j["game"]["plyCount"];
                    white = j["players"]["bottom"]["username"];
                    black = j["players"]["top"]["username"];
                    result = j["game"]["resultMessage"];
                    date = j["game"]["pgnHeaders"]["Date"];
                    moveList = j["game"]["moveList"];
                } catch (json::exception& e) {
                    cerr << "JSON parsing error: " << e.what() << endl;
                }
            }

            curl_easy_cleanup(curl);
        }
        return;
    }

    // live, daily 둘 다 가능
    string extractGameId(const string& url) {
        size_t start = url.find("live/");
        if (start != string::npos) {
            start += 5; // "live/" 길이만큼 이동
            size_t end = url.find("?move", start);
            if (end == string::npos) return url.substr(start);
            return url.substr(start, end - start);
        } else {
            start = url.find("daily/");
            if (start == string::npos) return "";
            start += 6; // "daily/" 길이만큼 이동
            size_t end = url.find("?move", start);
            if (end == string::npos) return url.substr(start);
            return url.substr(start, end - start);
        }
    }

    bool isNumeric(const string& str) {
        return all_of(str.begin(), str.end(), ::isdigit);
    }
public:
    explicit ChessFetcher(const string& _url) : url(_url) {
        fetchGame();
    }

    // 여기서 받는 string은 "이 탁월한 수를 보십시오: https://www.chess.com/analysis/game/live/138303590064?move=44&tab=review" 같은 형식
    // string을 https://www.chess.com/callback/live/game/138303590064 같은 API 형식으로 바꿔주는 함수 (daily, live 구분 필요)
    static int getBrilliantMoveIndex(const string& s) {
        size_t pos = s.find("move=");
        if (pos == string::npos) return -1;
        pos += 5; // "move=" 길이만큼 이동
        size_t end = s.find('&', pos);
        if (end == string::npos) end = s.length(); // '&'가 없으면 문자열 끝까지
        return stoi(s.substr(pos, end - pos)); // move= 뒤의 숫자를 정수로 변환
    }

    // daily, live 둘 다 가능
    static string getGameAPI(const string& s) {
        size_t start = s.find("live/");
        if (start != string::npos)  {
            start += 5; // "live/" 길이만큼 이동
            size_t end = s.find("?move", start);
            if (end == string::npos) return "https://www.chess.com/callback/live/game/" + s.substr(start);
            string gameId = s.substr(start, end - start);
            return "https://www.chess.com/callback/live/game/" + gameId;
        } else {
            start = s.find("daily/");
            if (start != string::npos) {
                start += 6; // "daily/" 길이만큼 이동
                size_t end = s.find("?move", start);
                if (end == string::npos) return "https://www.chess.com/callback/daily/game/" + s.substr(start);
                string gameId = s.substr(start, end - start);
                return "https://www.chess.com/callback/daily/game/" + gameId;
            }
        }
        return "";
    }

    // string을 https://api.chess.com/pub/player/ibottledo/games/2025/05 같은 API 형식으로
    string getMonthGameAPI(const int& brilliantMoveIndex) {
        userId = (brilliantMoveIndex % 2 == 0) ? white : black;
        return "https://api.chess.com/pub/player/" + userId + "/games/" + date.substr(0, 4) + "/" + date.substr(5, 2);
    }

    string getMoveList() const {
        return moveList;
    }

    // Brilliant URL의 gameId가 numeric, UUID 둘 다 가능
    string getBrilliantPGN(const string& Brilliant_url) {
        CURL* curl;
        CURLcode res;
        string readBuffer;
        string url = getMonthGameAPI(getBrilliantMoveIndex(Brilliant_url));
        string gameId = extractGameId(Brilliant_url); // URL에서 게임 ID 추출
        string target_url;
        string uuid;
        if (isNumeric(gameId)) {
            target_url = "https://www.chess.com/game/live/" + gameId;
        } else {
            uuid = gameId;
        }
        string result;

        // test
        cout << "url: " << url << " target_url: " << target_url << '\n';

        curl = curl_easy_init();
        if (curl) {
            curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
            curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
            curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
            curl_easy_setopt(curl, CURLOPT_USERAGENT, "Mozilla/5.0");

            res = curl_easy_perform(curl);

            if (res != CURLE_OK) {
                cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << endl;
            } else {
                try {
                    json j = json::parse(readBuffer);

                    for (const auto& game : j["games"]) {
                        if ((game.contains("url") && game["url"] == target_url) || (game.contains("uuid") && game["uuid"] == uuid)) {
                            if (game.contains("pgn")) {
                                string s = game["pgn"];
                                s = regex_replace(s, regex(R"(\\n)"), "\n");  // "\\n" → "\n" ('\n' 적용)
                                result = s; // PGN 저장
                                break;
                            } else {    // 예외 처리
                                cout << "PGN not found in this game." << '\n';
                            }
                        } else {
                            // else 처리 (uuid로 주어지는 경우)
                        }
                    }
                } catch (json::exception& e) {
                    cerr << "JSON parsing error: " << e.what() << '\n';
                }
            }
            curl_easy_cleanup(curl);
        }

        curl_global_cleanup();

        int brilliantMoveIndex = getBrilliantMoveIndex(Brilliant_url) + 2;
        size_t start = result.find(to_string(brilliantMoveIndex / 2) + (brilliantMoveIndex % 2 == 0 ? ". " : "... "));
        if (start != string::npos) {
            size_t end = result.find(" {[", start);
            if (end == string::npos) end = result.length(); // " {["가 없으면 문자열 끝까지
            result = result.substr(start, end - start); // 해당 부분만 추출
        } else {
            cout << "Brilliant move not found in PGN." << '\n';
        }

        return result;
    }
};

int main() {
    string Brilliant_url;
    cout << "Enter: Brilliant URL: ";
    getline(cin, Brilliant_url);
    int brilliantMoveIndex = ChessFetcher::getBrilliantMoveIndex(Brilliant_url);
    string gameAPI = ChessFetcher::getGameAPI(Brilliant_url);

    ChessFetcher fetcher(gameAPI);
    string moveList = fetcher.getMoveList();

    ChessBoard chessBoard;
    chessBoard.printChessBoard(moveList, brilliantMoveIndex);

    cout << "Brilliant Move:\n";
    string pgn = fetcher.getBrilliantPGN(Brilliant_url);
    cout << pgn << "!!" << '\n';

    return 0;
}