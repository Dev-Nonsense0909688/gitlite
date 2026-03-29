#include <iostream>
#include <string>
#include <filesystem>

#include "config.h"
#include "repo/repo.h"
#include "branch/branch.h"
#include "staging/add.h"
#include "staging/status.h"
#include "commit/commit.h"
#include "log/log.h"

using namespace std;
namespace fs = std::filesystem;

bool repoExists()
{
    return fs::exists(".gitlite") && fs::is_directory(".gitlite");
}

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        cout << "Usage: gitlite <command>\n";
        return 1;
    }

    string cmd = argv[1];

    try
    {

        if (cmd == "init")
        {
            init();
            return 0;
        }

        if (!repoExists())
        {
            cout << "Not a gitlite repository. Run 'gitlite init' first.\n";
            return 1;
        }

        if (cmd == "add")
        {
            if (argc < 3)
            {
                cout << "Usage: gitlite add <file>\n";
                return 1;
            }
            add(argv[2]);
        }

        else if (cmd == "branch")
        {
            if (argc < 3)
            {
                cout << "Usage: gitlite branch <name>\n";
                return 1;
            }
            branch(argv[2]);
        }

        else if (cmd == "switch")
        {
            if (argc < 3)
            {
                cout << "Usage: gitlite switch <name>\n";
                return 1;
            }
            switchB(argv[2]);
        }

        else if (cmd == "status")
        {
            status();
        }

        else if (cmd == "log")
        {
            logHistory();
        }
        else if (cmd == "commit")
        {
            if (argc < 4)
            {
                cout << "Usage: gitlite commit -m \"message\"\n";
                return 1;
            }

            string flag = argv[2];
            if (flag != "-m")
            {
                cout << "Invalid flag. Use -m\n";
                return 1;
            }

            commit(argv[3]);
        }

        else
        {
            cout << "Unknown command: " << cmd << endl;
        }
    }
    catch (const exception &e)
    {
        cout << "Error: " << e.what() << endl;
        return 1;
    }
    catch (...)
    {
        cout << "Unknown error occurred \n";
        return 1;
    }

    return 0;
}