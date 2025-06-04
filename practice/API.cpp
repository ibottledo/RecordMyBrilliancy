#include <curl/curl.h>
#include <json/json.h>
#include <iostream>
#include <sstream>

static size_t WriteCallback(void* contents, size_t size, size_t nmemb, std::string* s) {
    size_t totalSize = size * nmemb;
    s->append((char*)contents, totalSize);
    return totalSize;
}

int main() {
    CURL* curl = curl_easy_init();
    std::string readBuffer;

    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, "https://api.chess.com/pub/player/hikaru/games/archives");
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
        curl_easy_perform(curl);
        curl_easy_cleanup(curl);

        Json::CharReaderBuilder rbuilder;
        Json::Value root;
        std::string errs;

        std::istringstream s(readBuffer);
        std::string doc;
        std::getline(s, doc);

        std::istringstream iss(doc);
        if (Json::parseFromStream(rbuilder, iss, &root, &errs)) {
            const Json::Value archives = root["archives"];
            for (const auto& archive : archives)
                std::cout << archive.asString() << "\n";
        }
    }

    return 0;
}