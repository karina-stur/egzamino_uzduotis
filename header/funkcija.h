#ifndef FUNKCIJA_H
#define FUNKCIJA_H

#include <string>
#include <unordered_map>
#include <map>
#include <set>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <cctype>
#include <regex>
#include <iomanip>
#include <stdexcept>
#ifdef _WIN32
#include <windows.h>
#endif

using namespace std;

std::string normalizuotiZodi(const std::string& word);
std::string tekstasIsFailo(const std::string& filename);
std::unordered_map<std::string, int> zodziuSkaicius(const std::string& text);
std::unordered_map<std::string, int> rastiPasikartojimus(const std::unordered_map<std::string, int>& wordCounts);
std::unordered_map<std::string, std::set<int>> indeksuKurimas(const std::string& text);
std::vector<std::string> rastiUrl(const std::string& text);
void pasikartojimuFailas(const std::unordered_map<std::string, int>& repeatedWords, const std::string& filename);
void indeksuFailas(const std::unordered_map<std::string, std::set<int>>& crossReference, const std::string& filename);
void urlFailas(const std::vector<std::string>& urls, const std::string& filename);

#endif // FUNKCIJA_H
