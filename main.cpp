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

unsigned long berechneErgebniss(unsigned int dualzahl[],unsigned int laenge,int basis = 2);

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


#define NEUE_EINGABE
#ifndef NEUE_EINGABE
bool eingabeBits(unsigned int dualzahl[],int count){
    unsigned long kuerzer =0,letzte =0;
    bool eingabeOk = true;

    cout << "Geben  Sie die "<< count+1 << ".ten 8 Bit ein: (niederwertigstes Bit zuerst)" << endl;
    cin >> kuerzer;
    for (int i=0;i<8;i++){
        letzte = kuerzer%10;
        //cout << "letzte " << letzte << endl;
        if(kuerzer > 11111111 || letzte < 0 || letzte > 1 || cin.fail()){
            eingabeOk = false;
            cout << "\nFalsche Eingabe. Die Zahl darf nur 0 oder 1 als Ziffer beinhalten und max 8 Stellen haben!\nEingabe Wiederholen:" << endl;
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

        }
    };
    return eingabeOk;
#else
bool eingabeBits(unsigned int dualzahl[],int count){

        unsigned int byte[8];
        unsigned long zahl =0;
        unsigned int bit = 0;
        for (int i=0;i<8;i++){
            cout << "geben sie Bit "<< i+count*8 <<" ein:" << endl;
            bool nochmal = false;
            do{
                cin >> bit;
                if(bit == 1 || bit == 0){
                    byte[i] = bit;
                    nochmal = false;
                }
                else{
                    cout << "\nFalsche Eingabe. Ein Bit kann nur den Wert 0 oder 1 annehmen!\nEingabe Wiederholen:" << endl;
                    cin.clear();
                    cin.ignore(BUFSIZ, '\n');
                    nochmal = true;
                }
            }while(nochmal);
        }
        /*
        for(unsigned int i= 0;i<8;i++){
            unsigned int z = 8 - i;
            unsigned long dezistelle = 1;
            while(z<8){
                dezistelle *= 10;
                z++;
            }
            zahl += dezistelle*byte[i];
        }
        */
        zahl = berechneErgebniss(byte,8,10);
        //cout << "zahl: " << zahl << endl;
        int i=0;
        unsigned long letzte =0;
        do{
            letzte = zahl%10;
            //cout << "zahl: " << zahl << " letzte: " << letzte;
            zahl = zahl/10;
            //cout << "  durchlauf: " << i <<endl;
            dualzahl[i+count*8] = letzte;
            i++;
        }while(i<8);
        return true;
}
#endif




void printEingabe(unsigned int dualzahl[],unsigned int laenge){
    cout << endl <<"Ihre Eingabe: " << endl;
    for (int i=laenge-1;i>=0;i--){
        cout << dualzahl[i];
        if (i % 4 == 0) cout << " ";
        if (i % 8 == 0) cout << "  ";
        if (i % 16 == 0) cout << "\n";
    }
    cout << endl;
}

unsigned long berechneErgebniss(unsigned int dualzahl[],
                                unsigned int laenge,
                                int basis){
    //#define KOMPLIZIERT
    #ifdef KOMPLIZIERT
    unsigned long dezi = 0;
    for ( unsigned int i=0;i<laenge;i++){
        unsigned long dezistelle = 1;
        if(i == 0){
            dezistelle = 1;
        }
        else{
             unsigned int z = laenge-i;
            while(z < laenge){
                dezistelle *= 2;
                z++;
            }
        }
        dezi += dezistelle*dualzahl[i];
    }
    return dezi;

    #else
    unsigned long ergebnis = 0;
    //unsigned int n = laenge-1;
    for(unsigned int i= 0;i<laenge;i++){
            unsigned int z = laenge - i;
            unsigned long dezistelle = 1;
            while(z<laenge){
                dezistelle *= basis;
                z++;
            }
        ergebnis += dezistelle*dualzahl[i];
    }
    return ergebnis;
    #endif


}

void printErgebnis(unsigned long dezi){
    cout << endl<< "Die Dezimalzahl lautet: " << dezi << endl << endl;
}
