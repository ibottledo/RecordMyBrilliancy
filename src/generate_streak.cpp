#include <filesystem>
#include <iostream>
#include <fstream>
#include <map>
#include <chrono>
#include <iomanip>

namespace fs = std::filesystem;
using namespace std;
using namespace chrono;

int main() {
    map<string,int> brilliantCounts;

    // 🔧 _includes 폴더 없으면 생성
    fs::create_directories("_includes");

    // 1. _posts 디렉토리에서 날짜 추출
    for (const auto& entry : fs::directory_iterator("_posts")) {
        string filename = entry.path().filename().string();
        if (filename.size() >= 10 && filename[4] == '-' && filename[7] == '-') {
            string date = filename.substr(0, 10); // YYYY-MM-DD
            brilliantCounts[date]++;
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

        int cnt = brilliantCounts[dateStr];
        string color = " #DCDFE0";       // #8AABBF (연한 파랑, 바꿔본 안탁월), #EAEBD0
        if (cnt == 1) color = " #8FD9E5";          // #25C2A3 (연한 초록, 원래 탁월)ㄴ
        if (cnt == 2) color = " #63B7C5";
        if (cnt == 3) color = " #3894A5";
        if (cnt > 3) color = " #087285";

        string link = (cnt > 0)
            ? "{{ site.baseurl }}/blog/" + dateStr.substr(0,4) + "-" + dateStr.substr(5,2) + "-" + dateStr.substr(8,2) + "-brilliant-1/"
            : "#";

        out << "<a href='" << link << "' title='" << dateStr
            << "' style='width:14px;height:14px;background-color:" << color
            << ";display:block;border-radius:3px;'></a>\n";
    }

    out << "</div>\n</div>\n";  // 내부 그리드 div + 스크롤 div 닫기

    cout << "✅ streak.html generated successfully.\n";
    return 0;
}
