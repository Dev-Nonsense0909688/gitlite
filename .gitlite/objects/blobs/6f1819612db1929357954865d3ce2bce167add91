#include "branch.h"
#include <iostream>
#include <filesystem>
#include <fstream>
#include "config.h"

using namespace std;
namespace fs = std::filesystem;

void branch(string name)
{
    string path = BASE + "/refs/heads/" + name;

    if (fs::exists(path))
    {
        cout << "Branch already exists\n";
        return;
    }

    // 🔹 get current branch from INDEX
    string currentBranch;
    ifstream idx(BASE + "/INDEX");
    if (!idx || !getline(idx, currentBranch))
    {
        cout << "No current branch set\n";
        return;
    }

    // 🔹 get current commit hash
    string currentCommit;
    ifstream ref(BASE + "/refs/heads/" + currentBranch);
    if (ref)
        getline(ref, currentCommit);

    fs::create_directories(BASE + "/refs/heads");

    // new branch points to same commit
    ofstream(path) << currentCommit;

    cout << "Created branch: " << name << endl;
}

void switchB(string name)
{
    string path = BASE + "/refs/heads/" + name;

    if (!fs::exists(path))
    {
        cout << "Branch not found\n";
        return;
    }

    // 🔹 update INDEX (current branch)
    ofstream(BASE + "/INDEX") << name;

    cout << "Switched to branch: " << name << endl;
}