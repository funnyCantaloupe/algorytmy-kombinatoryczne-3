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

    ifstream qual_pomoc;
    qual_pomoc.open("C:\\Users\\Administrator\\CLionProjects\\algorytmy_kombinatoryczne_3\\instancja1.qual",
                    fstream::in);

    if (!qual_pomoc) {
        cout << "Blad otwierania pomocnieczego pliku typu .qual." << endl;
    }

    // wczytywanie danych z pliku

    vector<string> lines;
    string line;
    string line_pomoc;
    char i = '\n'; // tez pomoc line
    int lines_nr = 0;
    int spaces;
    int licznik; // licznik nukleotydow
    int przelacznik = 0; // gdy == 1 to bierzemy cred2 zamiast cred

    while (!qual_pomoc.eof()) {
        getline(qual_pomoc, line);
        lines.push_back(line);
    }

    string fasta;
    string qual;
    string qualp; //qual - pomoc
    char letter = 'n';
    string credibility;
    int cred;
    int cred2;
    int sequence_id = 1;

    while (!fastafile.eof()) {
        licznik = 0;
        while (!fastafile.eof()) {
            getline(fastafile, fasta);
            if (fasta[0] == '>') {
                break;
            }
        }

        qualfile.seekg(0);
        spaces = 0;
        while (!qualfile.eof()) {
            getline(qualfile, qual);
            lines_nr++;
            if (qual == fasta) {
                for (auto &n: lines[lines_nr]) {
                    if (n == ' ') {
                        spaces++;
                    }
                }
                break;
            }
        }
        cout << "spacje: " << spaces << endl;

        while (letter != '>' && letter != EOF) {
            cout << letter << "  ";
            if (letter != '>') {
                letter = fastafile.get();
                if (letter == '\n') {
                    letter = fastafile.get();
                }
                if (letter != '>') {
                    if (licznik != spaces) {
                        getline(qualfile, credibility, ' ');
                        licznik++;
                        cout << "linijka 62 credibility: " << credibility << endl;
                        cred = stoi(credibility);
                    } else {
                        lines_nr++;
                        getline(qualfile, credibility, '\n');
                        cout << "linijka 63 credibility: " << credibility << endl;
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
                            cout << "line_pomoc break: " << line_pomoc << endl;
                            break;
                        }
                        else {
                            cout << "line_pomoc: " << line_pomoc << endl;
                            cred = stoi(credibility);
                        }
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

                        cred = stoi(line_pomoc);
                    }
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
