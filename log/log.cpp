#include "log.h"
#include "config.h"
#include "utils/utils.h"
#include "repo/repo.h"

#include <iostream>
#include <filesystem>

using namespace std;
namespace fs = std::filesystem;

void logHistory()
{
    string branch = getCurrentBranch();
    string branchPath = BASE + "/refs/heads/" + branch;

    if (!fs::exists(branchPath))
    {
        cout << "No commits yet\n";
        return;
    }

    string commitHash = readFile(branchPath);

    while (!commitHash.empty())
    {
        string commitPath = BASE + "/objects/commits/" + commitHash;

        if (!fs::exists(commitPath))
            break;

        string content = readFile(commitPath);

        string msg = "";
        string parent = "";

        size_t msgPos = content.find("msg:");
        size_t parentPos = content.find("parent:");

        if (msgPos != string::npos)
        {
            size_t end = content.find("\n", msgPos);
            msg = content.substr(msgPos + 4, end - (msgPos + 4));
        }

        if (parentPos != string::npos)
        {
            size_t end = content.find("\n", parentPos);
            parent = content.substr(parentPos + 7, end - (parentPos + 7));
        }

        cout << "commit " << commitHash << "\n";
        cout << "    " << msg << "\n\n";

        commitHash = parent;
    }
}