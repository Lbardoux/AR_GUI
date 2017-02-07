/**
 * @file CLmanager.cpp
 */
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>

#include "CLmanager.hpp"

namespace
{
    /**
     * @brief Substitue une balise de @b line si elle a un équivalent dans @b argv.
     * @param[in]     argv0 La liste des arguments du programme.
     * @param[in,out] line  La ligne dans laquelle faire la substitution.
     * @return Une référence sur @b line.
     */
    std::string& substituteIfBeacon(const std::string& argv0, std::string& line) noexcept
    {
        std::size_t pos = line.find("%0%");
        if (pos != std::string::npos)
        {
            line.replace(pos, argv0.length(), argv0);
        }
        return line;
    }
}


#define USAGE_FILE "assets/usage.txt"
void checkCommandLine(int argc, char** argv)
{
    std::ifstream usage(USAGE_FILE);
    if (usage.good())
    {
        std::string foo("");
        std::string argv0(argv[0]);
        int         nb(0);
        usage >> foo >> nb;
        if (argc != nb+1)
        {
            while(std::getline(usage, foo))
            {
                if (foo == "END")
                    break;
                std::cerr << substituteIfBeacon(argv0, foo) << std::endl;
            }
            throw std::runtime_error("Invalid command line");
        }
        return;
    }
    throw std::ios_base::failure("Unable to open " USAGE_FILE);
}
#undef USAGE_FILE
