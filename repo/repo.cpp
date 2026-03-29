#include "repo.h"
#include <iostream>
#include <fstream>
#include <filesystem>
#include <utils/utils.h>
#include "config.h"

using namespace std;
namespace fs = std::filesystem;

void init()
{
    if (fs::exists(BASE))
    {
        cout << "Already Inited!" << endl;
        return;
    }

    fs::create_directories(BASE);

    writeFile(HEAD, "");
    writeFile(INDEX, "main");
}