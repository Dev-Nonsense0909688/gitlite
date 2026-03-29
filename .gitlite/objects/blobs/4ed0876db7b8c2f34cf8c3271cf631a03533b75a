#include "add.h"
#include <iostream>
#include <fstream>
#include <filesystem>
#include <vector>

#include "config.h"
#include "utils/utils.h"

using namespace std;
namespace fs = std::filesystem;

// load .ignore
vector<string> loadIgnoreFile()
{
    vector<string> rules;
    ifstream in(".ignore");

    string line;
    while (getline(in, line))
    {
        if (!line.empty())
            rules.push_back(line);
    }

    return rules;
}

// match ignore rules
bool isIgnored(const string &file, const vector<string> &rules)
{
    for (auto &rule : rules)
    {
        // folder rule
        if (rule.back() == '/')
        {
            if (file.find(rule.substr(0, rule.size() - 1)) != string::npos)
                return true;
        }
        // extension rule (*.log)
        else if (rule[0] == '*')
        {
            if (file.size() >= rule.size() - 1 &&
                file.substr(file.size() - (rule.size() - 1)) == rule.substr(1))
                return true;
        }
        // exact match
        else
        {
            if (file == rule)
                return true;
        }
    }
    return false;
}

void add(string file)
{
    ofstream head(HEAD, ios::app);
    vector<string> ignore = loadIgnoreFile();

    if (file == ".")
    {
        for (auto &entry : fs::recursive_directory_iterator("."))
        {
            if (!fs::is_regular_file(entry.path()))
                continue;

            string path = entry.path().string();

            if (path.find(".gitlite") != string::npos)
                continue;

            if (isIgnored(path, ignore))
                continue;

            head << path << "\n";
            cout << "[+] " << path << "\n";
        }
    }
    else
    {
        if (!fs::exists(file) || file.find(".gitlite") != string::npos)
        {
            cout << "File not found\n";
            return;
        }

        if (isIgnored(file, ignore))
        {
            cout << "Ignored: " << file << "\n";
            return;
        }

        head << file << "\n";
        cout << "[+] " << file << "\n";
    }
}