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

unordered_map<string, int> zodziuSkaicius(const string& text) {
    unordered_map<string, int> wordCounts;
    istringstream iss(text);
    string word;

    while (iss >> word) {
        word = normalizuotiZodi(word);
        if (!word.empty()) {
            wordCounts[word]++;
        }
    }
    return wordCounts;
}

unordered_map<string, int> rastiPasikartojimus(const unordered_map<string, int>& wordCounts) {
    unordered_map<string, int> repeatedWords;
    for (const auto& pair : wordCounts) {
        if (pair.second > 1) {
            repeatedWords[pair.first] = pair.second;
        }
    }
    return repeatedWords;
}

unordered_map<string, set<int>> indeksuKurimas(const string& text) {
    unordered_map<string, set<int>> crossReference;
    istringstream iss(text);
    string line;
    int lineNumber = 0;

    while (getline(iss, line)) {
        ++lineNumber;
        istringstream lineStream(line);
        string word;

        while (lineStream >> word) {
            word = normalizuotiZodi(word);
            if (!word.empty()) {
                crossReference[word].insert(lineNumber);
            }
        }
    }
    return crossReference;
}
