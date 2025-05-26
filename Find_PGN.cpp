// 모든 월의 게임에서 특정 게임 PGN을 찾음
// uuid로 주어지는 경우 못찾는 문제가 있음 (보고서용)
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

string extractGameId(const string& url) {
    size_t start = url.find("live/");
    if (start == string::npos) return "";

    start += 5; // "live/" 길이만큼 이동
    size_t end = url.find("?move", start);
    if (end == string::npos) return "";

    return url.substr(start, end - start);
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

                // test
                cout << "Date: " << date << ", userId: " << userId << '\n';

            } catch (json::exception& e) {
                cerr << "JSON parsing error: " << e.what() << '\n';
            }
        }

        // curl_easy_cleanup(curl); // 중간에 없애면 안됨 (보고서용)
        curl = curl_easy_init(); // curl 재초기화

        // PGN 추출
        string target_url = "https://www.chess.com/game/live/";
        target_url += gameId;
        url = "https://api.chess.com/pub/player/" + userId + "/games/" + date.substr(0, 4) + "/" + date.substr(5, 2);   // substr(5, 7)아님;; index인줄 (보고서용)

        // test
        cout << "URL: " << url << " target_url: " << target_url << '\n';

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
                    // test
                    // cout << "Game URL: " << game["url"] << '\n';

                    if (game.contains("url") && game["url"] == target_url) {
                        if (game.contains("pgn")) {
                            // test
                            cout << "Found PGN for game: " << game["url"] << '\n';

                            string s = game["pgn"]; // '\n' 적용
                            s = regex_replace(s, regex(R"(\\n)"), "\n");  // "\\n" → "\n"
                            cout << s << '\n';
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
    return 0;
}
// 실행방법
// g++ Find_PGN.cpp -o Find_PGN -lcurl -I/usr/local/Cellar/nlohmann-json/3.12.0/include
// ./Find_PGN