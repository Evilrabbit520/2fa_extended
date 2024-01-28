
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
    std::string fileName = "conf.txt";
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
                // 如果是 -c, -l 选项，直接存储，不需要检查后面是否有参数
                if (arguments[i] == "-c" || arguments[i] == "-l")
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
            cfile.open(fileName, std::ios::out | std::ios::app);
            cfile << "name:" << options["-a"] << std::endl;
            std::cout << "Please enter your token:";
            std::cin >> secret;
            cfile << "secret:" << secret << std::endl;
            cfile.close();

            if (options.count("-c"))
            {
                std::ostringstream oss;
                oss << auth::generateToken(secret);
                std::string secretStr = oss.str();
                copyToClipboard(secretStr);
            }
            std::cout << "your dynamic token:" << auth::generateToken(secret) << std::endl;
        }
        if (options.count("-l"))
        {
            std::ifstream inputFile(fileName);
            if (!inputFile.is_open())
            {
                std::cerr << "Unable to open the file." << std::endl;
            }
            std::string line;
            std::string currentName, allNames;

            while (std::getline(inputFile, line))
            {
                size_t namePos = line.find("name:");
                if (namePos != std::string::npos)
                {
                    currentName = line.substr(namePos + 5); // 5 是 "name:" 的长度
                    allNames += currentName + "\n";
                }
            }
            inputFile.close();

            // 检查最后换行
            if (!allNames.empty() && allNames.back() == '\n')
            {
                allNames.pop_back();
            }

            if (!fileName.empty())
            {
                std::cout << "Name found: \n" << allNames << std::endl;
            }
            else
            {
                std::cout << "Name not found in the file." << std::endl;
            }
        }
        if (options.count("-n"))
        {
            std::string targetName;
            std::string foundSecret;  // 用于存储找到的secret值
            targetName = /*"dfsfs";*/ options["-n"];
            std::ifstream inputFile(fileName);
            if (!inputFile.is_open())
            {
                std::cerr << "Unable to open the file." << std::endl;
            }
            std::string line;
            std::string currentName;

            while (std::getline(inputFile, line))
            {
                size_t namePos = line.find("name:");
                if (namePos != std::string::npos)
                {
                    std::string currentName = line.substr(namePos + 5); // 5 是 "name:" 的长度
                    if (currentName == targetName)
                    {
                        // 找到目标名字后，继续查找对应的secret值
                        while (std::getline(inputFile, line))
                        {
                            size_t secretPos = line.find("secret:");
                            if (secretPos != std::string::npos)
                            {
                                foundSecret = line.substr(secretPos + 7); // 7 是 "secret:" 的长度
                                break;                                    // 找到secret值后，结束循环
                            }
                        }
                        break; // 结束外层循环
                    }
                }
            }
            if (options.count("-c"))
            {
                std::ostringstream oss;
                oss << auth::generateToken(foundSecret);
                std::string secretStr = oss.str();
                copyToClipboard(secretStr);
            }
            std::cout << "your dynamic token:" << auth::generateToken(foundSecret) << std::endl;
            inputFile.close();
        }
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
            cfile.open(fileName, std::ios::out | std::ios::app);
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