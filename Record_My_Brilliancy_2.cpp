// 개발 과정 보고서에 첨부할 예시코드
#include <iostream> 
#include <string>
#include <curl/curl.h>
#include <nlohmann/json.hpp>
#include <vector>

using json = nlohmann::json;
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
class ChessGame {
private:
    string white, black, result, moveList;
    int plyCount;
public:
    // 읽기 전용 함수 (ex, print, get, toString 등)
    // 자동 형변환 방지용 explicit
    explicit ChessGame(const json& j);
    
    void printMoves() const;    // Brilliant Move 직전의 보드를 출력
};

// 입력받은 string으로 작동
// API에서 게임 정보를 가져오는 클래스
class ChessFetcher {    
public:
    // 여기서 받는 string은 "이 탁월한 수를 보십시오: https://www.chess.com/analysis/game/live/138303590064?move=44&tab=review" 같은 형식
    // string을 https://www.chess.com/callback/live/game/138303590064 같은 API 형식으로 바꿔주는 함수 (daily, live 구분 필요)
    static int getBrilliantMoveIndex(const string& s);
    
    static string s2GameAPI(const string& s) {
        size_t start = s.find("live/");
        if (start != string::npos)  {
            start += 5; // "live/" 길이만큼 이동
            size_t end = s.find("?move", start);
            if (end == string::npos) return "";
            string gameId = s.substr(start, end - start);
            return "https://www.chess.com/callback/live/game/" + gameId;
        } else {
            start = s.find("daily/");
            if (start != string::npos) {
                start += 6; // "daily/" 길이만큼 이동
                size_t end = s.find("?move", start);
                if (end == string::npos) return "";
                string gameId = s.substr(start, end - start);
                return "https://www.chess.com/callback/daily/game/" + gameId;
            } else {
                return "";  // daily, live 둘 다 아닌 경우
            }
        }
    }
    // string을 https://api.chess.com/pub/player/ibottledo/games/2025/05 같은 API 형식으로
    static string s2MonthGameAPI(const string& s) {

    }
    // API에서 게임 정보를 가져오는 함수 (월별 게임 정보도 가져옴)
    static json fetchGame(const string& url) {
        CURL* curl;
        CURLcode res;
        string readBuffer;

        curl = curl_easy_init();
        if (curl) {
            curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
            curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, NULL);
            curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
            res = curl_easy_perform(curl);
            curl_easy_cleanup(curl);
        }
        return json::parse(readBuffer);
    }
};

int main() {
    curl_global_init(CURL_GLOBAL_DEFAULT);

    // 여기서 받는 string은 "이 탁월한 수를 보십시오: https://www.chess.com/analysis/game/live/138303590064?move=44&tab=review" 같은 형식
    string s;
    cin >> s; 
    // public static 함수이므로 ChessFetcher::foo() 로 호출 가능

    // 위 string에서 게임 번호를 추출해 https://www.chess.com/callback/live/game/138303590064 같은 API 형식으로 바꿔주는 함수
    string url1 = ChessFetcher::s2GameAPI(s);  
    // 위 string에서 게임 번호를 추출해 https://api.chess.com/pub/player/ibottledo/games/2025/05 같은 API 형식으로 바꿔주는 함수
    string url2 = ChessFetcher::s2MonthGameAPI(s);  
    json j1 = ChessFetcher::fetchGame(url1);
    json j2 = ChessFetcher::fetchGame(url2);



    if (j.is_null()) {
        cout << "Failed to fetch game data." << '\n';   // cerr?
        return 1;
    }

    // 게임 정보를 담은 json 객체로 ChessGame 객체 생성
    ChessGame game(j);  
    game.printSummary();
    game.printMoves();

    curl_global_cleanup();
    return 0;
}