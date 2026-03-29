#include "status.h"
#include <iostream>
#include <fstream>
#include <filesystem>
#include <unordered_map>
#include <unordered_set>

#include "config.h"
#include "utils/utils.h"

using namespace std;
namespace fs = std::filesystem;

// load staged (HEAD)
unordered_set<string> loadStaged()
{
    unordered_set<string> staged;
    ifstream head(BASE + "/HEAD");

    string path;
    while (getline(head, path))
    {
        if (!path.empty())
            staged.insert(path);
    }
    return staged;
}

// load last commit files -> map<file, hash>
unordered_map<string, string> loadLastCommit()
{
    unordered_map<string, string> files;

    string branch = getCurrentBranch();
    string branchPath = BASE + "/refs/heads/" + branch;

    if (!fs::exists(branchPath))
        return files;

    string commitHash = readFile(branchPath);
    if (commitHash.empty())
        return files;

    string commitPath = BASE + "/objects/commits/" + commitHash;
    string content = readFile(commitPath);

    istringstream ss(content);
    string line;

    bool filesSection = false;

    while (getline(ss, line))
    {
        if (line == "files:")
        {
            filesSection = true;
            continue;
        }

        if (!filesSection || line.empty())
            continue;

        size_t space = line.find(' ');
        if (space == string::npos)
            continue;

        string file = line.substr(0, space);
        string hash = line.substr(space + 1);

        files[file] = hash;
    }

    return files;
}

void status()
{
    auto staged = loadStaged();
    auto last = loadLastCommit();

    unordered_set<string> printed;

    cout << "=== Staged ===\n";
    for (auto &file : staged)
    {
        cout << "[+] " << file << "\n";
        printed.insert(file);
    }

    cout << "\n=== Modified ===\n";
    for (auto &[file, oldHash] : last)
    {
        if (!fs::exists(file))
            continue;

        string newHash = sha1(readFile(file));

        if (newHash != oldHash && !staged.count(file))
        {
            cout << "[M] " << file << "\n";
            printed.insert(file);
        }
    }

    cout << "\n=== Deleted ===\n";
    for (auto &[file, _] : last)
    {
        if (!fs::exists(file))
        {
            cout << "[D] " << file << "\n";
            printed.insert(file);
        }
    }

    cout << "\n=== Untracked ===\n";
    for (auto &entry : fs::recursive_directory_iterator("."))
    {
        if (!fs::is_regular_file(entry.path()))
            continue;

        string file = entry.path().string();

        if (file.find(".gitlite") != string::npos)
            continue;

        if (!last.count(file) && !staged.count(file))
        {
            cout << "[?] " << file << "\n";
        }
    }
}