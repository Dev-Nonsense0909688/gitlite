#include <string>
#include "config.h"
#include "utils/utils.h"
#include "repo/repo.h"

#include <fstream>
#include <filesystem>
#include <iostream>

using namespace std;
namespace fs = std::filesystem;

void storeBlob(string file, string commitContent)
{
    if (!fs::exists(file) || !fs::is_regular_file(file))
        return;

    string data = readFile(file);
    string hash = sha1(data);

    string blobPath = BASE + "/objects/blobs/" + hash;

    if (!fs::exists(blobPath))
    {
        writeFile(blobPath, data);
    }

    commitContent += file + " " + hash + "\n";
}

void processPath(string path, string commitContent)
{
    if (!fs::exists(path))
        return;

    if (fs::is_regular_file(path))
    {
        storeBlob(path, commitContent);
    }
    else if (fs::is_directory(path))
    {
        for (auto &entry : fs::recursive_directory_iterator(path))
        {
            if (!fs::is_regular_file(entry.path()))
                continue;

            string file = entry.path().string();

            if (file.find(".gitlite") != string::npos)
                continue;

            storeBlob(file, commitContent);
        }
    }
}

void commit(string message)
{
    ifstream head(BASE + "/HEAD");
    if (!head)
    {
        cout << "Nothing to commit\n";
        return;
    }

    string branch = getCurrentBranch();
    string branchPath = BASE + "/refs/heads/" + branch;

    fs::create_directories(BASE + "/objects/blobs");
    fs::create_directories(BASE + "/refs/heads");

    string parent = "";
    if (fs::exists(branchPath))
    {
        parent = readFile(branchPath);
    }

    string commitContent;
    commitContent += "msg:" + message + "\n";
    commitContent += "parent:" + parent + "\n";
    commitContent += "files:\n";

    string path;
    while (getline(head, path))
    {
        if (path.empty())
            continue;

        processPath(path, commitContent);
    }

    string commitHash = sha1(commitContent);

    string commitPath = BASE + "/objects/commits/" + commitHash;
    fs::create_directories(BASE + "/objects/commits");
    writeFile(commitPath, commitContent);

    writeFile(branchPath, commitHash);

    ofstream(BASE + "/HEAD", ios::trunc).close();

    cout << "Committed: " << commitHash << endl;

    head.close();
}