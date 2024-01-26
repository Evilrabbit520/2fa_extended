
#include <iostream>
#include <fstream>
#include "auth.h"

int main()
{
    std::string secret = "";

    std::cout << "Whether to save(yes/no)?";
    std::string save;
    std::cin >> save;
    if(save == "yes" || save == "y")
    {
        std::fstream cfile;
        cfile.open("conf.txt", std::ios::out|std::ios::app);
        std::string Name;
        std::cout << "the name you wish to save:";
        std::cin >> Name;
        cfile << "name:" << Name << std::endl;
        cfile << "secret:" << secret << std::endl;
        cfile.close();
    }
    std::cout << auth::generateToken(secret) << std::endl;

    return 0;
}