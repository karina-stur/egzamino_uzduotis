#include "funkcija.h"

using namespace std;

string normalizuotiZodi(const string& word) {
    string normalized = word;

    transform(normalized.begin(), normalized.end(), normalized.begin(), [](unsigned char c) {
        return std::tolower(c);
        });

    normalized.erase(remove_if(normalized.begin(), normalized.end(), [](unsigned char c) {
        return std::ispunct(c);
        }), normalized.end());

    if (!any_of(normalized.begin(), normalized.end(), [](unsigned char c) {
        return std::isalpha(c);
        })) {
        return "";
    }

    return normalized;
}

string tekstasIsFailo(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        throw runtime_error("Unable to open file: " + filename);
    }

    stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}
