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

    // 🔧 _includes 폴더 없으면 생성
    fs::create_directories("_includes");

    // 1. _posts 디렉토리에서 날짜 추출
    for (const auto& entry : fs::directory_iterator("_posts")) {
        string filename = entry.path().filename().string();
        if (filename.size() >= 10 && filename[4] == '-' && filename[7] == '-') {
            string date = filename.substr(0, 10); // YYYY-MM-DD
            brilliantDates.insert(date);
        }
    }

    // 2. 오늘 기준 최근 364일 계산
    auto today = system_clock::to_time_t(system_clock::now());
    tm today_tm = *localtime(&today);

    // 시작일 = 363일 전 (오늘까지 포함해야 7의 배수)
    tm start_tm = today_tm;
    start_tm.tm_mday -= 363;
    mktime(&start_tm);  // normalize

    // 3. streak.html 생성
    ofstream out("_includes/streak.html");
    if (!out.is_open()) {
        cerr << "❌ Failed to open _includes/streak.html for writing.\n";
        return 1;
    }

    out << "<h2></h2>\n";

    // 🔁 가로 스크롤 가능한 래퍼 div 추가
    out << "<div style='overflow-x: auto; padding-bottom: 8px;'>\n";
    out << "<div style='display:grid; grid-template-rows: repeat(7, 14px); grid-auto-flow: column; gap: 2px; width: max-content;'>\n";

    for (int i = 0; i < 364; ++i) {
        tm current = start_tm;
        current.tm_mday += i;
        mktime(&current);  // normalize

        char buf[11];
        strftime(buf, sizeof(buf), "%Y-%m-%d", &current);
        string dateStr(buf);

        int isBrilliant = brilliantDates.count(dateStr);
        string color = "#ebedf0";       //"#8AABBF";
        if (isBrilliant == 1) {
            color = "#BFF3E8";          //#25C2A3
        } else if (isBrilliant > 1) {
            color = "#3FC1B0";
        }

        string link = isBrilliant
            ? "/RecordMyBrilliancy/blog/" + dateStr.substr(0,4) + "-" + dateStr.substr(5,2) + "-" + dateStr.substr(8,2) + "-brilliant/"
            : "#";

        out << "<a href='" << link << "' title='" << dateStr
            << "' style='width:14px;height:14px;background-color:" << color
            << ";display:block;border-radius:3px;'></a>\n";
    }

    out << "</div>\n</div>\n";  // 내부 그리드 div + 스크롤 div 닫기

    cout << "✅ streak.html generated successfully.\n";
    return 0;
}
