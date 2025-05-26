#include <iostream>
#include <string>
#include <curl/curl.h>
#include <nlohmann/json.hpp>

using json = nlohmann::json;
using namespace std;

// 콜백 함수: 서버 응답을 문자열로 저장
static size_t WriteCallback(void* contents, size_t size, size_t nmemb, string* output) {
    size_t totalSize = size * nmemb;
    output->append((char*)contents, totalSize);
    return totalSize;
}

int main() {
    CURL* curl;
    CURLcode res;
    string readBuffer;

    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();

    if (curl) {
        // string url = "https://www.chess.com/callback/live/game/138303590064";
        string url;
        cin >> url; // link입력
        
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
        curl_easy_setopt(curl, CURLOPT_USERAGENT, "Mozilla/5.0");  // Chess.com이 user-agent 없으면 차단할 수 있음

        res = curl_easy_perform(curl);

        if (res != CURLE_OK) {
            cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << endl;
        } else {
            try {
                json j = json::parse(readBuffer);

                string white = j["players"]["bottom"]["username"];
                string black = j["players"]["top"]["username"];
                string result = j["game"]["resultMessage"];
                int plyCount = j["game"]["plyCount"];

                cout << "White: " << white << "\n";
                cout << "Black: " << black << "\n";
                cout << "Result: " << result << "\n";
                cout << "Total moves: " << (plyCount / 2.0) << " turns" << endl;
            } catch (json::exception& e) {
                cerr << "JSON parsing error: " << e.what() << endl;
            }
        }

        curl_easy_cleanup(curl);
    }

    curl_global_cleanup();
    return 0;
}
// 실행방법
// g++ API_test.cpp -o api_test -lcurl -I/usr/local/Cellar/nlohmann-json/3.12.0/include
// ./api_test