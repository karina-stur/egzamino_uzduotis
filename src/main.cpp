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
        cout << "- zodziu_pasikartojimai.txt (rasti zodziai ir isvestas ju pasikartojimo skaicius)\n";
        cout << "- indeksai.txt (rasti zodziai ir ju pasikartojimo eilutes)\n";
        cout << "- nuorodos.txt (failas su tekste rastomis nuorodomis)\n";
        return 0;
    }
    catch (const exception& e) {
        cerr << "Klaida: " << e.what() << endl;
        return 1;
    }
}
