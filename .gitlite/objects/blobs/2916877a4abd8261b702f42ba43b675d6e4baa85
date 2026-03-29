#include "utils.h"
#include <fstream>
#include <sstream>
#include <filesystem>
#include <openssl/sha.h>
#include <iomanip>
#include "config.h"

using namespace std;
namespace fs = std::filesystem;


string readFile(const string &path)
{
    ifstream in(path, ios::binary);
    if (!in)
        return "";

    return string((istreambuf_iterator<char>(in)),
                  istreambuf_iterator<char>());
}

string getCurrentBranch()
{
    ifstream index(INDEX);
    string branch;
    getline(index, branch);
    return branch;
}

void writeFile(const string &path, const string &content)
{
    if(content == ""){
        ofstream(path, ios::binary).close();
        return;
    }
    ofstream out(path, ios::binary);
    out << content;
}

vector<string> getIgnore()
{
    vector<string> files = {".gitlite", ".ignore"};

    if (fs::exists(".ignore"))
    {
        ifstream file(".ignore");
        string line;
        while (getline(file, line))
        {
            if (line != "")
                files.push_back(line);
        }
    }

    return files;
}

string sha1(const string &input)
{
    unsigned char hash[SHA_DIGEST_LENGTH];
    SHA1((unsigned char *)input.c_str(), input.size(), hash);

    stringstream ss;
    for (int i = 0; i < SHA_DIGEST_LENGTH; i++)
    {
        ss << hex << setw(2) << setfill('0') << (int)hash[i];
    }
    return ss.str();
}