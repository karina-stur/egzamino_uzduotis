#include "funkcija.h"

int main() {
    try {
#ifdef _WIN32
        SetConsoleOutputCP(CP_UTF8);
        SetConsoleCP(CP_UTF8);
#endif

        string filename = "tekstas.txt";
        string text = tekstasIsFailo(filename);
        auto wordCounts = zodziuSkaicius(text);

        auto repeatedWords = rastiPasikartojimus(wordCounts);
        pasikartojimuFailas(repeatedWords, "zodziu_pasikartojimai.txt");
        auto crossReference = indeksuKurimas(text);
        indeksuFailas(crossReference, "indeksai.txt");
        auto urls = rastiUrl(text);
        urlFailas(urls, "nuorodos.txt");
        cout << "Buvo isvesti 3 failai: \n";
        cout << "- zodziu_pasikartojimai.txt\n";
        cout << "- indeksai.txt\n";
        cout << "- nuorodos.txt\n";
        return 0;
    }
    catch (const exception& e) {
        cerr << "Klaida: " << e.what() << endl;
        return 1;
    }
}
