// 개발 과정 보고서에 첨부할 예시코드
#include <iostream> 
#include <string>
#include <curl/curl.h>
#include <nlohmann/json.hpp>
#include <vector>

using json = nlohmann::json;
using namespace std;

class MoveDecoder {
public:
    struct Move {
        string from, to, promotion, drop;
    };

    static Move decode(const string& code);
    static string decodeMoveList(const string& moveList);   // 얘는 없어도 될지도
};
    
class ChessGame {
private:
    string white, black, result, moveList;
    int plyCount;

public:
    // 읽기 전용 함수 (ex, print, get, toString 등)
    // 자동 형변환 방지용 explicit
    explicit ChessGame(const json& j);
    void printSummary() const;  // 
    void printMoves() const;    // Brilliant Move 직전의 보드를 출력
};
    
class ChessFetcher {    // API에서 게임 정보를 가져오는 클래스
public:
    static int getBrilliantMoveIndex(const string& s);
    static string changeURL(const string& s);  // 여기서 받는 string은 "이 탁월한 수를 보십시오: https://www.chess.com/analysis/game/live/138303590064?move=44&tab=review" 같은 형식
    static json fetchGame(const string& url);
};

int main() {
    string s;
    cin >> s; // 여기서 받는 string은 "이 탁월한 수를 보십시오: https://www.chess.com/analysis/game/live/138303590064?move=44&tab=review" 같은 형식
    // static 함수이므로 ChessFetcher::foo() 로 호출 가능
    string url = ChessFetcher::changeURL(s);  // 위 string에서 게임 번호를 추출해 https://www.chess.com/callback/live/game/138303590064 같은 형식으로 바꿔주는 함수
    json j = ChessFetcher::fetchGame(url);

    if (j.is_null()) {
        cout << "Failed to fetch game data." << '\n';   // cerr?
        return 1;
    }

    ChessGame game(j);  // 게임 정보를 담은 json 객체로 ChessGame 객체 생성
    game.printSummary();
    game.printMoves();

    return 0;
}
// g++ Record_My_Brilliancy_OOP_Structure_test.cpp -o strTest -lcurl -I/usr/local/Cellar/nlohmann-json/3.12.0/include
// ./strTest
// 불편해서 Makefile 만듦 make로 작동