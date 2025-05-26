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
public:
    struct Move {
        string from, to, promotion, drop;
    };
    static Move decode(const string& code);
    // static string decodeMoveList(const string& moveList); // 얘는 없어도 될 거 같음
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
    // void printSummary() const;  // 게임 요약 출력 << 얘도 없어도 될 거 같음
    void printMoves() const;    // Brilliant Move 직전의 보드를 출력
};

// 입력받은 string으로 작동
class ChessFetcher {    // API에서 게임 정보를 가져오는 클래스
public:
    static int getBrilliantMoveIndex(const string& s);
    // 여기서 받는 string은 "이 탁월한 수를 보십시오: https://www.chess.com/analysis/game/live/138303590064?move=44&tab=review" 같은 형식
    static string s2GameAPI(const string& s);       // string을 https://www.chess.com/callback/live/game/138303590064 같은 API 형식으로 바꿔주는 함수 (daily, live 구분 필요)
    static string s2MonthGameAPI(const string& s);  // string을 https://api.chess.com/pub/player/ibottledo/games/2025/05 같은 API 형식으로
    static json fetchGame(const string& url1, const string& url2);       // API에서 게임 정보를 가져오는 함수 (월별 게임 정보도 가져옴)
};

int main() {
    string s;
    cin >> s; // 여기서 받는 string은 "이 탁월한 수를 보십시오: https://www.chess.com/analysis/game/live/138303590064?move=44&tab=review" 같은 형식
    // public static 함수이므로 ChessFetcher::foo() 로 호출 가능
    string url1 = ChessFetcher::s2GameAPI(s);  // 위 string에서 게임 번호를 추출해 https://www.chess.com/callback/live/game/138303590064 같은 API 형식으로 바꿔주는 함수
    string url2 = ChessFetcher::s2MonthGameAPI(s);  // 위 string에서 게임 번호를 추출해 https://api.chess.com/pub/player/ibottledo/games/2025/05 같은 API 형식으로 바꿔주는 함수
    json j = ChessFetcher::fetchGame(url1, url2);

    if (j.is_null()) {
        cout << "Failed to fetch game data." << '\n';   // cerr?
        return 1;
    }

    ChessGame game(j);  // 게임 정보를 담은 json 객체로 ChessGame 객체 생성
    game.printSummary();
    game.printMoves();

    return 0;
}