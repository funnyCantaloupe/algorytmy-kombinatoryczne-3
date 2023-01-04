#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stdio.h>

using namespace std;

vector<pair<char, int>> nucleotide_cred1;
vector<pair<char, int>> nucleotide_cred2;
vector<pair<char, int>> nucleotide_cred3;
vector<pair<char, int>> nucleotide_cred4;
vector<pair<char, int>> nucleotide_cred5;

void pair_up(char letter, int cred, int sequence_id) {
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
}

int main() {

    // otwieranie plikow

    ifstream fastafile;
    fastafile.open("C:\\Users\\Administrator\\CLionProjects\\algorytmy_kombinatoryczne_3\\instancja1.fasta",
                   fstream::in);

    if (!fastafile) {
        cout << "Blad otwierania pliku typu .fasta." << endl;
        exit(1);
    }

    ifstream qualfile;
    qualfile.open("C:\\Users\\Administrator\\CLionProjects\\algorytmy_kombinatoryczne_3\\instancja1.qual", fstream::in);

    if (!qualfile) {
        cout << "Blad otwierania pliku typu .qual." << endl;
        exit(1);
    }

    ifstream qual_pomoc;
    qual_pomoc.open("C:\\Users\\Administrator\\CLionProjects\\algorytmy_kombinatoryczne_3\\instancja1.qual",
                    fstream::in);

    if (!qual_pomoc) {
        cout << "Blad otwierania pomocnieczego pliku typu .qual." << endl;
        exit(1);
    }

    // wczytywanie danych z pliku

    vector<string> lines;
    string line;
    string line_pomoc;
    int lines_nr;
    int linie_w_pliku = 0;
    int spaces;
    int licznik; // licznik nukleotydow
    int przelacznik = 0; // zeby nie robic 2x emplace_back dla licznik == spaces
    bool dolaczono = false;
    int spacje_count;
    bool last_in_line = false;

    while (!qual_pomoc.eof()) {
        getline(qual_pomoc, line);
        lines.push_back(line);
        linie_w_pliku++;
    }
    linie_w_pliku--;
    qual_pomoc.close();

    string fasta;
    string qual;
    string qualp; //qual - pomoc
    char letter = 'n';
    string credibility;
    int cred;
    int sequence_id = 1;


    while (sequence_id < 6) {
        licznik = 0;
        while (!fastafile.eof()) {
            getline(fastafile, fasta);
            if (fasta[0] == '>') {
                break;
            }
        }

        qualfile.seekg(0);
        spaces = 0;
        lines_nr = 0;
        while (!qualfile.eof()) {
            getline(qualfile, qual);
            lines_nr++;
            if (qual == fasta) {
                for (auto &n: lines[lines_nr]) {
                    if (n == ' ') {
                        spaces++;
                    }
                }
                cout << "lines[lines_nr]: " << lines[lines_nr] << endl;
                break;
            }
        }

        cout << "linie w pliku: " << linie_w_pliku << endl;

        while (letter != '>' && letter != EOF) {
                letter = fastafile.get();
                if (letter == '\n') {
                    letter = fastafile.get();
                }
                cout << " spaces: " << spaces <<  endl;
                if (letter != '>') {
                    if (licznik != spaces) {
                        getline(qualfile, credibility, ' ');
                        licznik++;
                        cout << "credibility: " << credibility << " letter: " << letter << endl;
                        cred = stoi(credibility);
                    }
                    else if (lines_nr == linie_w_pliku && licznik == spaces) {
                        getline(qualfile, credibility, ' ');
                        cred = stoi(credibility);
                        pair_up(letter, cred, sequence_id);
                        break; // nie usuwac!
                    }
                    else {
                        lines_nr++;
                        getline(qualfile, credibility, '\n');
                        cout << "credibility: " << credibility << " letter: " << letter << endl;
                        licznik = 0;
                        spaces = 0;
                        for (auto &n: lines[lines_nr]) {
                            if (n == ' ') {
                                spaces++;
                            }
                        }
                        line_pomoc = "";
                        for (auto& m : lines[lines_nr]) {
                                if (m != ' ') {
                                    line_pomoc = line_pomoc + m;
                                }
                                else {
                                    break;
                                }
                        }
                        if (line_pomoc[0] == '>') {
                            cout << "line_pomoc break: " << line_pomoc << " line_nr: " << lines_nr << endl;
                            cred = stoi(credibility);
                            pair_up(letter, cred, sequence_id);
                            break;
                        }
                        else {
                            cout << "line_pomoc: " << line_pomoc << " line_nr: " << lines_nr << endl;
                            cred = stoi(credibility);
                            pair_up(letter, cred, sequence_id);
                            dolaczono = true;
                        }
                    }
                    if (!dolaczono) {
                        pair_up(letter, cred, sequence_id);
                    }
                    else {
                        dolaczono = false;
                    }
                }
            }
            sequence_id++;
            cout << "test" << endl;
        }

    cout << "czy to dziala?" << endl;

        cout << "sekwencja 1: " << endl;
        for (auto &n: nucleotide_cred1) {
            cout << n.first << ' ' << n.second << endl;
        }

        cout << "sekwencja 2: " << endl;
        for (auto &n: nucleotide_cred2) {
            cout << n.first << ' ' << n.second << endl;
        }

        cout << "sekwencja 3: " << endl;
        for (auto &n: nucleotide_cred3) {
            cout << n.first << ' ' << n.second << endl;
        }

        cout << "sekwencja 4: " << endl;
        for (auto &n: nucleotide_cred4) {
            cout << n.first << ' ' << n.second << endl;
        }

        cout << "sekwencja 5: " << endl;
        for (auto &n: nucleotide_cred5) {
            cout << n.first << ' ' << n.second << endl;
        }

        fastafile.close();
        qualfile.close();

        return 0;
    }