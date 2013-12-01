#include <iostream>
#include <cstdio>
/*
Programm zum Umrechnen von Dualzahlen
nach Dezimalzahlen
*/

using namespace std;

const string text = "Ein Konsoleprogramm zum Umrechnen von Dualzahlen nach Dezimalzahlen";

//! wieviel bit unterstützt das System
unsigned int berechneStellen();

//! Buffer für die Dualzahl mit nullen initialisieren
void initBuffer(unsigned int dualzahl[],unsigned int laenge);

//! Eingabe der Dualzahl
bool eingabeBits(unsigned int dualzahl[],int count);

//! Anzeige der Eingabe
void printEingabe(unsigned int dualzahl[],unsigned int laenge);
unsigned long berechneErgebniss(unsigned int dualzahl[],unsigned int laenge);
void printErgebnis(unsigned long dezi);


int main()
{
    unsigned int laenge = berechneStellen();
    unsigned int dualzahl[laenge];
    bool nocheinmal = false, mehrBits = false, eingabeOk;
    cout << text << endl << endl;

    do{//! Noch ein Programmdurchlauf?
        unsigned int bitcount = 0;
        initBuffer(dualzahl,laenge);
        do{//! eingabe OK
            //eingabeOk = true;
            do{//! mehr Bits
                mehrBits = 0;
                eingabeOk = eingabeBits(dualzahl,bitcount);
                if(eingabeOk){
                    printEingabe(dualzahl,laenge);
                    bitcount++;
                    if(bitcount < laenge/8){
                        cout << "moechten Sie weitere 8 Bits eingeben (Ja = 1)" << endl;
                        cin >> mehrBits;
                        if(cin.fail()){
                            cin.clear();
                            cin.ignore(BUFSIZ, '\n');
                            mehrBits = 0;
                        }
                    }
                }
            }while(mehrBits ==1);

        }while(!eingabeOk);
        printErgebnis(berechneErgebniss(dualzahl,laenge));
        cout << "moechten sie noch eine Berechung durchfuehren? (Ja = 1)" << endl;
        cin >> nocheinmal;
        if(cin.fail()){
            cin.clear();
            cin.ignore(BUFSIZ, '\n');
            nocheinmal = 0;
        }
    }while(nocheinmal == 1);
}


unsigned int berechneStellen()
{
    unsigned int stellen =  sizeof(unsigned long)*8;
    return  stellen;
}


void initBuffer(unsigned int dualzahl[],unsigned int laenge){
    for (unsigned int i=0;i<laenge;i++){
        dualzahl[i] = 0;
    }
}



bool eingabeBits(unsigned int dualzahl[],int count){
    unsigned long kuerzer =0,letzte =0;
    bool eingabeOk = true;
    int i = 0;
    cout << "Geben  Sie Byte "<< count << " ein: (niederwertigstes Bit zuerst)" << endl;
    cin >> kuerzer;
    do{
        letzte = kuerzer%10;
        //cout << "letzte " << letzte << endl;
        if(letzte < 0 || letzte > 1 || i>8 || cin.fail()){
            eingabeOk = false;
            cout << "\nFalsche Eingabe. Die Zahl darf nur 0 oder 1 als Ziffer beinhalten und maximal 8 Stellen pro Eingabe haben!\nEingabe Wiederholen:" << endl;
            cin.clear();
            cin.ignore(BUFSIZ, '\n');
            for(int y = 0;y<i;i++){
                dualzahl[y+count*8] = 0;
            }
            break;
        }
        else{
            eingabeOk = true;
            kuerzer = kuerzer/10;
            dualzahl[i+count*8] = letzte;
            i++;
        }
    }while(letzte);
    return eingabeOk;
}

void printEingabe(unsigned int dualzahl[],unsigned int laenge){
    cout << "Ihre Eingabe: " << endl;
    for (int i=laenge-1;i>=0;i--){
        cout << dualzahl[i];
        if (i % 4 == 0) cout << " ";
        if (i % 8 == 0) cout << "  ";
        if (i % 16 == 0) cout << "\n";
    }
    cout << endl;
}

unsigned long berechneErgebniss(unsigned int dualzahl[],unsigned int laenge){
    unsigned long dezi = 0;
    for ( unsigned int i=0;i<laenge;i++){
        unsigned long dezistelle = 1;
        if(i == 0){
            dezistelle = 1;
        }
        else{
             unsigned int z = laenge-i;
            while(z < laenge){
                dezistelle = 2*dezistelle;
                z++;
            }
        }
        dezi = dezi + dezistelle*dualzahl[i];
    }
    return dezi;
}

void printErgebnis(unsigned long dezi){
    cout << endl<< "Die Dezimalzahl lautet: " << dezi << endl << endl;
}
