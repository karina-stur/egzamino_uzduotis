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
        throw runtime_error("Nepavyko atidaryti failo: " + filename);
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

vector<string> rastiUrl(const string& text) {
    vector<string> urls;
    const regex url_regex(R"((https?://|www\.|[a-zA-Z0-9.-]+\.[a-zA-Z]{2,6})([^\s]*)?)", regex::icase);
    auto words_begin = sregex_iterator(text.begin(), text.end(), url_regex);
    auto words_end = sregex_iterator();

    for (auto it = words_begin; it != words_end; ++it) {
        urls.push_back(it->str());
    }
    return urls;
}

void pasikartojimuFailas(const unordered_map<string, int>& repeatedWords, const string& filename) {
    ofstream outFile(filename);
    if (!outFile.is_open()) {
        throw runtime_error("Nepavyko atidaryti failo: " + filename);
    }

    const int wordColumnWidth = 20;
    const int countColumnWidth = 5;

    outFile << setw(wordColumnWidth) << left << "Zodis"
        << setw(countColumnWidth) << "Pasikartojimu skaicius" << endl;

    outFile << string(wordColumnWidth + countColumnWidth, '-') << endl;

    for (const auto& pair : repeatedWords) {
        outFile << setw(wordColumnWidth) << left << pair.first
            << setw(countColumnWidth) << right << pair.second << endl;
    }

    outFile.close();
}

void indeksuFailas(const unordered_map<string, set<int>>& crossReference, const string& filename) {
    ofstream outFile(filename);
    if (!outFile.is_open()) {
        throw runtime_error("Nepavyko atidaryti failo: " + filename);
    }

    outFile << setw(20) << left << "Zodis" << "Eilutes numeris\n";
    outFile << string(30, '-') << "\n";

    for (const auto& pair : crossReference) {
        outFile << setw(20) << left << pair.first;
        for (const int line : pair.second) {
            outFile << line << " ";
        }
        outFile << "\n";
    }
    outFile.close();
}

void urlFailas(const vector<string>& urls, const string& filename) {
    ofstream outFile(filename);
    if (!outFile.is_open()) {
        throw runtime_error("Nepavyko atidaryti failo: " + filename);
    }

    for (const auto& url : urls) {
        outFile << url << "\n";
    }
    outFile.close();
}
