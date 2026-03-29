#pragma once
#include <string>
#include <vector>

std::string readFile(const std::string &path);
void writeFile(const std::string &path, const std::string &content);

std::vector<std::string> getIgnore();

std::string sha1(const std::string &input);

std::string getCurrentBranch();