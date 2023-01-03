#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stdio.h>

using namespace std;

int main() {

    vector<pair<char, int>> nucleotide_cred1;
    vector<pair<char, int>> nucleotide_cred2;
    vector<pair<char, int>> nucleotide_cred3;
    vector<pair<char, int>> nucleotide_cred4;
    vector<pair<char, int>> nucleotide_cred5;

    nucleotide_cred1.emplace_back(make_pair('-', 0));
    nucleotide_cred2.emplace_back(make_pair('-', 0));
    nucleotide_cred3.emplace_back(make_pair('-', 0));
    nucleotide_cred4.emplace_back(make_pair('-', 0));
    nucleotide_cred5.emplace_back(make_pair('-', 0));

    // otwieranie plikow

    ifstream fastafile;
    fastafile.open("C:\\Users\\Administrator\\CLionProjects\\algorytmy_kombinatoryczne_3\\instancja1.fasta",
                   fstream::in);

    if (!fastafile) {
        cout << "Blad otwierania pliku typu .fasta." << endl;
    }

    ifstream qualfile;
    qualfile.open("C:\\Users\\Administrator\\CLionProjects\\algorytmy_kombinatoryczne_3\\instancja1.qual", fstream::in);

    if (!qualfile) {
        cout << "Blad otwierania pliku typu .qual." << endl;
    }

    // wczytywanie danych z pliku

    string fasta;
    string qual;
    char letter = 'n';
    string credibility;
    int cred;
    int sequence_id = 1;

    while (!fastafile.eof()) {

        while (!fastafile.eof()) {
            getline(fastafile, fasta);
            if (fasta[0] == '>') {
                break;
            }
        }

        while (!qualfile.eof()) {
            getline(qualfile, qual);
            if (qual == fasta) {
                break;
            }
        }

        while (letter != '>' && letter != EOF) {
            cout << letter << "  ";
            cout << "linijka 53" << endl;
            if (letter != '>') {
                letter = fastafile.get();
                cout << "linijka 55" << endl;
                if (letter == '\n') {
                    letter = fastafile.get();
                    cout << "linijka 58" << endl;
                }
                if (letter != '>') {
                    getline(qualfile, credibility, ' ');
                    cout << "linijka 62 credibility: " << credibility << endl;
                    if (credibility.length() > 2) {                         // !!!!!!
                        if (credibility[0] == 1 || credibility[0] == 2 || credibility[0] == 3 || credibility[0] == 4 || credibility[0] == 5 || credibility[0] == 6 || credibility[0] == 8 || credibility[0] == 8 || credibility[0] == 9) {
                            getline(qualfile, credibility, '\n');
                            cout << "linijka 65" << endl;
                        }
                    }
                        cred = stoi(credibility);
                        cout << "linijka 68" << endl;
                    if (sequence_id == 1)
                        nucleotide_cred1.emplace_back(make_pair(letter, cred));
                    else if (sequence_id == 2)
                        nucleotide_cred2.emplace_back(make_pair(letter, cred));
                    else if (sequence_id == 3)
                        nucleotide_cred3.emplace_back(make_pair(letter, cred));
                    else if (sequence_id == 4)
                        nucleotide_cred4.emplace_back(make_pair(letter, cred));
                    else if (sequence_id == 5)
                        nucleotide_cred5.emplace_back(make_pair(letter, cred));
                    cout << "linijka 70" << endl;
                }
            }
        }
        sequence_id++;
    }

    cout << "sekwencja 1: ";
    for (auto &n: nucleotide_cred1) {
        cout << n.first << ' ' << n.second << endl;
    }

    return 0;
}
