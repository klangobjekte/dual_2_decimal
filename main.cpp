#include <iostream>
//#include <cstdio>
#define BUFSIZ 256

using namespace std;

unsigned int berechneStellen();
void initBuffer(unsigned long dualsplit[],unsigned int laenge);
bool eingabeBits(unsigned long dualsplit[],int count);
void printEingabe(unsigned long dualsplit[],unsigned int laenge);

void berechneErgebniss(unsigned long dualsplit[],int laenge);






int main()
{
     unsigned int laenge = berechneStellen();

     unsigned long dualsplit[laenge];

     bool nocheinmal = false, mehrBits = false, eingabeOk;

     do{//! Abfrage Programm beenden?
     unsigned int bitcount = 0;
        do{//! eingabe OK
            initBuffer(dualsplit,laenge);
            eingabeOk = true;
            do{//! mehr Bits
                mehrBits = 0;
                eingabeOk = eingabeBits(dualsplit,bitcount);
                if(eingabeOk){
                    printEingabe(dualsplit,laenge);


                }
                bitcount++;
                if(bitcount < laenge/8){
                    cout << "moechten Sie weiter Bits eingeben (Ja = 1)" << endl;
                    cin >> mehrBits;
                    if(cin.fail()){
                        //cout << "ihre Eingabe war nicht gueltig!\n";
                        cin.clear();
                        cin.ignore(BUFSIZ, '\n');
                        mehrBits = 0;
                    }
                }

            }while(mehrBits ==1);

        berechneErgebniss(dualsplit,laenge);

        }while(!eingabeOk);
        cout << "moechten sie noch eine Berechung durchfuehren? (Ja = 1)" << endl;
        cin >> nocheinmal;
        if(cin.fail()){
            //cout << "ihre Eingabe war nicht gueltig!\n";
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

void initBuffer(unsigned long dualsplit[],unsigned int laenge){
    for (unsigned int i=0;i<laenge;i++){
        dualsplit[i] = 0;
    }
}



bool eingabeBits(unsigned long dualsplit[],int count){
    unsigned long dualin =0,letzte =0,kuerzer=0;
    bool eingabeOk = true;
    cout << "Geben sie die Bits "<< count*8 << " bis "<<  8*(count+1)-1 << " ein: (niederwertigstes Bit zuerst)" << endl;
    cin >> dualin;
    kuerzer = dualin;
    //cout << "kuerzer: " << kuerzer << endl;
    int i = 0;
    do{
        letzte = kuerzer%10;
        //cout << "letzte " << letzte << endl;
        if(letzte < 0 || letzte > 1 || i>8 || cin.fail())
        {
            eingabeOk = false;
            cout << "\nFalsche Eingabe. Die Zahl darf nur 0 oder 1 als Ziffer beinhalten und maximal 8 Stellen pro Eingabe haben!" << endl;
            //y= bitcount;
            cin.clear();
            cin.ignore(BUFSIZ, '\n');
            break;
        }
        else{
            kuerzer = kuerzer/10;
            dualsplit[i+count*8] = letzte;
            i++;
        }
    }while(letzte);
    cout << endl;
    return eingabeOk;
}

void printEingabe(unsigned long dualsplit[],unsigned int laenge){
    cout << "Ihre Eingabe: " << endl;
    for (int i=laenge-1;i>=0;i--){
        cout << dualsplit[i];
        if (i % 4 == 0) cout << " ";
        if (i % 8 == 0) cout << "  ";
        if (i % 16 == 0) cout << "\n";
    }
    cout << endl;
}

void berechneErgebniss(unsigned long dualsplit[],int laenge){
    unsigned long dezi = 0;
    for ( int i=0;i<laenge;i++){
        unsigned long dezistelle = 1;
        if(i == 0){
            dezistelle = 1;
        }
        else{
             int z = laenge-i;
            while(z < laenge){
                dezistelle = 2*dezistelle;
                z++;
            }
        }
        dezi = dezi + dezistelle*dualsplit[i];
    }
    cout << endl<< "Die Dezimalzahl lautet: " << dezi << endl << endl;
}
