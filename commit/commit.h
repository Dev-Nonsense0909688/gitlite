#pragma once
#include <string>

void commit(std::string message);
void processPath(std::string path, std::string commitContent);
void storeBlob(std::string file, std::string commitContent);