
#include <iostream>
#include <fstream>
#include <vector>
#include <cstdio>
#include <sstream>
#include <map>
#include "auth.h"

#ifdef _WIN32
#include <windows.h>
#endif

void copyToClipboard(const std::string &content)
{
#ifdef __APPLE__
    // macOS
    FILE *pbcopyProcess = popen("pbcopy", "w");
    if (pbcopyProcess == nullptr)
    {
        std::cerr << "Error opening pipe to pbcopy" << std::endl;
        return;
    }
    fprintf(pbcopyProcess, "%s", content.c_str());
    if (pclose(pbcopyProcess) == -1)
    {
        std::cerr << "Error closing pipe to pbcopy" << std::endl;
        return;
    }
#elif _WIN32
    // Windows
    if (OpenClipboard(nullptr))
    {
        EmptyClipboard();
        HGLOBAL hg = GlobalAlloc(GMEM_MOVEABLE, content.size() + 1);
        if (hg == nullptr)
        {
            CloseClipboard();
            return;
        }
        memcpy(GlobalLock(hg), content.c_str(), content.size() + 1);
        GlobalUnlock(hg);
        SetClipboardData(CF_TEXT, hg);
        CloseClipboard();
        GlobalFree(hg);
    }
#endif
}

int main(int argc, char *argv[])
{
    std::vector<std::string> arguments(argv + 1, argv + argc);
    std::map<std::string, std::string> options;
    std::string secret = "";

    if (argc > 1)
    {

        for (size_t i = 0; i < arguments.size(); ++i)
        {
            // 如果参数以 "-" 开头
            if (arguments[i].size() > 1 && arguments[i][0] == '-')
            {
                // 如果是 -c 选项，直接存储，不需要检查后面是否有参数
                if (arguments[i] == "-c")
                {
                    options[arguments[i]] = "";
                }
                else if (i + 1 < arguments.size())
                {
                    // 如果后面还有参数，存储选项和值
                    options[arguments[i]] = arguments[i + 1];
                    // 跳过参数值
                    ++i;
                }
                else
                {
                    // 如果后面没有参数且不是 -c，输出错误信息
                    std::cout << "Option " << arguments[i] << " requires a value." << std::endl;
                }
            }
            else
            {
                // 如果不是以 "-" 开头，输出错误信息
                std::cout << "Unknown option or missing value: " << arguments[i] << std::endl;
            }
        }
        // 根据选项执行不同的操作
        if (options.count("-a"))
        {
            std::cout << "Option -a selected with value: " << options["-a"] << std::endl;

            std::fstream cfile;
            cfile.open("conf.txt", std::ios::out | std::ios::app);
            cfile << "name:" << options["-a"] << std::endl;
            std::cout << "Please enter your token:";
            std::cin >> secret;
            cfile << "secret:" << secret << std::endl;
            cfile.close();
            std::cout << "your dynamic token:" << auth::generateToken(secret) << std::endl;

            if (options.count("-c"))
            {
                std::cout << "copy!";
                std::ostringstream oss;
                oss << auth::generateToken(secret);
                std::string secretStr = oss.str();
                copyToClipboard(secretStr);
            }
        }

        // if (options.count("-b"))
        // {
        //     std::cout << "Option -b selected with value: " << options["-b"] << std::endl;

        //     // 添加更多 -b 相关的逻辑
        //     // ...
        // }
    }
    else
    {
        std::cout << "Please enter your token:";
        std::cin >> secret;
        std::cout << "Whether to save(yes/no)?";
        std::string save;
        std::cin >> save;
        if (save == "yes" || save == "y")
        {
            std::fstream cfile;
            cfile.open("conf.txt", std::ios::out | std::ios::app);
            std::string Name;
            std::cout << "the name you wish to save:";
            std::cin >> Name;
            cfile << "name:" << Name << std::endl;
            cfile << "secret:" << secret << std::endl;
            cfile.close();
        }
        std::cout << "your dynamic token:" << auth::generateToken(secret) << std::endl;
    }

    return 0;
}