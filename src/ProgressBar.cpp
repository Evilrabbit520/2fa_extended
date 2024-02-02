#include "ProgressBar.h"

void showProgressBar(int progress, int total)
{
    int barWidth = 50;
    float ratio = static_cast<float>(progress) / total;
    int barProgress = static_cast<int>(ratio * barWidth);

    std::cout << "[";
    for (int i = 0; i < barWidth; ++i) {
        if (i < barWidth - barProgress) {
            std::cout << "#";
        } else {
            std::cout << " ";
        }
    }
    std::cout << "] " << int(ratio * 100.0) << "%\r";
    std::cout.flush();
}

int showCountdown()
{
    // 获取当前时间点后将时间点转换为秒数
    auto secondsSinceEpoch = std::chrono::duration_cast<std::chrono::seconds>(std::chrono::system_clock::now().time_since_epoch()).count();
    // 取余数，保留0到30的秒数
    int secondsInRange = secondsSinceEpoch % 30;

    int totalSeconds = 30;

    for (int i = secondsInRange; i <= totalSeconds; ++i) {
        // std::cout << token << "\r";
        showProgressBar(i, totalSeconds);
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }

    // 清空进度条
    std::cout << std::string(60, ' ') << "\r";
    std::cout.flush();
}