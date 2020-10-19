#pragma once
#include <iostream>
#include <fstream>
#include <cctype>
#include <string>
#include <cerrno>
#include <cstring>

std::filebuf getFile();
void outputCount(std::string, int);

int main(int, char **, char **);
