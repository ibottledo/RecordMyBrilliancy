#include <filesystem>
#include <iostream>
#include <fstream>
#include <set>
#include <chrono>
#include <iomanip>

namespace fs = std::filesystem;
using namespace std;
using namespace chrono;

int main() {
    set<string> brilliantDates;

    // 🔧 필수: _includes 폴더 없으면 생성
    fs::create_directories("_includes");

    // 1. _posts 디렉토리 순회
    for (const auto& entry : fs::directory_iterator("_posts")) {
        string filename = entry.path().filename().string();
        if (filename.size() >= 10 && filename[4] == '-' && filename[7] == '-') {
            string date = filename.substr(0, 10); // YYYY-MM-DD
            brilliantDates.insert(date);
        }
    }

    // 2. 오늘 기준 최근 365일 스트릭 그리기
    auto today = system_clock::to_time_t(system_clock::now());
    tm today_tm = *localtime(&today);

    // 시작일 = 1년 전
    tm start_tm = today_tm;
    start_tm.tm_mday -= 364;
    mktime(&start_tm);

    // 3. 파일 생성 (with 체크)
    ofstream out("_includes/streak.html");
    if (!out.is_open()) {
        cerr << "❌ Failed to open _includes/streak.html for writing.\n";
        return 1;
    }

    out << "<h2>🔥 Brilliant Move Streak</h2>\n";
    out << "<div style='display:grid; grid-template-columns: repeat(53, 14px); gap: 2px;'>\n";

    for (int i = 0; i < 365; ++i) {
        tm current = start_tm;
        current.tm_mday += i;
        mktime(&current);

        char buf[11];
        strftime(buf, sizeof(buf), "%Y-%m-%d", &current);
        string dateStr(buf);

        string color = brilliantDates.count(dateStr) ? "#2ecc71" : "#ebedf0";
        string link = brilliantDates.count(dateStr)
            ? "/RecordMyBrilliancy/" + dateStr.substr(0,4) + "/" + dateStr.substr(5,2) + "/" + dateStr.substr(8,2) + "/brilliant/"
            : "#";

        out << "<a href='" << link << "' title='" << dateStr
            << "' style='width:14px;height:14px;background-color:" << color
            << ";display:block;border-radius:3px;'></a>\n";
    }

    out << "</div>\n";
    out << "<p style='font-size:12px;'>🟩 = brilliant move, ⬜ = no move</p>\n";

    cout << "✅ streak.html generated successfully.\n";
    return 0;
}
