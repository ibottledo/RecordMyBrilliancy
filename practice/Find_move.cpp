// 모든 월의 게임에서 탁월수 PGN을 찾음
#include <iostream>
#include <string>
#include <curl/curl.h>
#include <nlohmann/json.hpp>
#include <regex>

using json = nlohmann::json;
using namespace std;

static size_t WriteCallback(void* contents, size_t size, size_t nmemb, string* output) {
    size_t totalSize = size * nmemb;
    output->append((char*)contents, totalSize);
    return totalSize;
}

string extractBrilliantMoveIndex(const string& Brilliant_url) {
    size_t start = Brilliant_url.find("move=");
    if (start == string::npos) return "";

    start += 5; // "move=" 길이만큼 이동
    size_t end = Brilliant_url.find("&tab", start);
    if (end == string::npos) end = Brilliant_url.length();

    return Brilliant_url.substr(start, end - start);
}

string extractGameId(const string& url) {
    size_t start = url.find("live/");
    if (start == string::npos) return "";

    start += 5; // "live/" 길이만큼 이동
    size_t end = url.find("?move", start);
    if (end == string::npos) return "";

    return url.substr(start, end - start);
}

string extractBrilliant(const string& pgn, const string& brilliantMoveIndex) {
    int index = stoi(brilliantMoveIndex) + 1;
    string moveIndex = to_string((index + 1) / 2);
    if (index % 2 == 0) {
        moveIndex += "... ";
    } else {
        moveIndex += ". ";
    }

    // test
    cout<< "Move index: " << moveIndex << '\n';
    
    size_t start = pgn.find(moveIndex);
    if (start == string::npos) return "";
    start += moveIndex.length();

    size_t end = pgn.find("{", start);
    if (end == string::npos) return "";
    end--;

    return pgn.substr(start, end - start);
}

int main() {
    CURL* curl;
    CURLcode res;
    string readBuffer;

    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();

    if (curl) {
        string Brilliant_url, url = "https://www.chess.com/callback/live/game/";
        cout << "Enter: Brilliant URL: ";
        // Brilliant_url입력 (ex: 이 탁월한 수를 보십시오: https://www.chess.com/analysis/game/live/138303590064?move=44&tab=review)
        getline(cin, Brilliant_url);
        string gameId = extractGameId(Brilliant_url); // URL에서 게임 ID 추출
        url += gameId;
        
        // date, userId추출  
        string date, userId;
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
        curl_easy_setopt(curl, CURLOPT_USERAGENT, "Mozilla/5.0");  // Chess.com이 user-agent 없으면 차단할 수 있음

        res = curl_easy_perform(curl);

        if (res != CURLE_OK) {
            cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << '\n';
        } else {
            try {
                json j = json::parse(readBuffer);

                date = j["game"]["pgnHeaders"]["Date"];
                userId = j["players"]["bottom"]["username"];
            } catch (json::exception& e) {
                cerr << "JSON parsing error: " << e.what() << '\n';
            }
        }

        // curl_easy_cleanup(curl); // 중간에 없애면 안됨 (보고서용)
        curl = curl_easy_init(); // curl 재초기화

        // 특정 달의 모든 게임이 기록된 API URL
        string target_url = "https://www.chess.com/game/live/";
        target_url += gameId;
        url = "https://api.chess.com/pub/player/" + userId + "/games/" + date.substr(0, 4) + "/" + date.substr(5, 2);   // substr(5, 7)아님;; index인줄 (보고서용)

        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
        curl_easy_setopt(curl, CURLOPT_USERAGENT, "Mozilla/5.0");  // Chess.com이 user-agent 없으면 차단할 수 있음     
        
        readBuffer.clear();  // 꼭 해줘야 함! (보고서용)
        res = curl_easy_perform(curl);  // 이 줄이 필요 (보고서용)

        if (res != CURLE_OK) {
            cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << '\n';
        } else {
            try {
                json j = json::parse(readBuffer);

                for (const auto& game : j["games"]) {
                    if (game.contains("url") && game["url"] == target_url) {
                        if (game.contains("pgn")) {
                            string s = game["pgn"]; // '\n' 적용
                            string brilliantMoveIndex = extractBrilliantMoveIndex(Brilliant_url); // 탁월수 인덱스 추출
                            // cout << "Brilliant move index: " << brilliantMoveIndex << '\n';
                            string b = extractBrilliant(s, brilliantMoveIndex); // 탁월수 찾기!!
                            cout << "Brilliant move found in this game: " << b << "!!" << '\n';
                            cout << "len: " << b.length() << '\n';
                            break;
                        } else {    // 예외 처리
                            cout << "PGN not found in this game." << '\n';
                        }
                    }
                }
            } catch (json::exception& e) {
                cerr << "JSON parsing error: " << e.what() << '\n';
            }
        }

        curl_easy_cleanup(curl);
    }

    curl_global_cleanup();
    return 0;
}
// 실행방법
// g++ Find_PGN.cpp -o Find_PGN -lcurl -I/usr/local/Cellar/nlohmann-json/3.12.0/include
// ./Find_PGN