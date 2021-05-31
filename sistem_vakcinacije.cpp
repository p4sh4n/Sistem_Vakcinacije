#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>
#include <cstring>
#include <ctime>
#include <stdlib.h>
#include <random>
#include <algorithm>
#include <functional>
#include <sstream>
using namespace std;

char* crt = "\n---------------------------------------------\n";
const string adminUser="administrator";
const string adminPass="AZD1222";
typedef std::vector<char> char_array;

/*----------ENUMERACIJE I NJIHOVE FUNKCIJE----------*/
enum uposlenja{zdravstveni_uposlenik=1, radnik_ili_sticenik_socijalne_ustanove, javna_sluzba, ostalo};
enum bolesti{down_sindrom=1, primatelj_transplantiranog_organa, karcinom, teska_respiratorna_bolest, Ostalo};
enum ambulante{mokusnice=1,travnicka,crkvice,radakovo,kineski};

string vratiUposlenje(int x){
    switch(x){
        case 1:
            return "Zdravstveni_uposlenik";
        case 2:
            return "Radnik_ili_sticenik_socijalne_ustanove";
        case 3:
            return "Radnik_javne_sluzbe";
        case 4:
            return "Ostalo";
    }
}

string vratiBolest(int x){
    switch(x){
        case 1:
            return "Down_sindrom";
        case 2:
            return "Primatelj_transplantiranog_organa";
        case 3:
            return "Karcinom";
        case 4:
            return "Teska_respiratorna_bolest";
        case 5:
            return "Ostalo";
    }
}

string vratiAmbulantu(int x){
    switch(x){
        case 1:
            return "Mokusnice";
        case 2:
            return "Travnicka";
        case 3:
            return "Crkvice";
        case 4:
            return "Radakovo";
        case 5:
            return "Kineski";
    }
}

/*----------FUNKCIJE POTREBNE ZA FUNKCIJE STRUKTURE PACIJENT----------*/
bool validanDatum(int dan, int mjesec, int godina){
	int minValidnaGodina(1900),maxValidnaGodina(2021);
	if (godina<minValidnaGodina || godina>maxValidnaGodina) return false;
	if (mjesec<1 || mjesec>12) return false;
	if (dan < 1 || dan > 31) return false;
	if (mjesec == 4 || mjesec == 6 || mjesec == 9 || mjesec == 11) return (dan <= 30);
	if (mjesec == 1 || mjesec == 3 || mjesec == 5 || mjesec == 7 || mjesec == 8 || mjesec==10 || mjesec==12) return (dan <= 31);
	if (mjesec == 2 && godina % 4 == 0) {
        if (godina % 100 == 0) {
            if (godina % 400 == 0) return (dan <= 29);
            else return (dan <= 28);
        }
        else return (dan <= 29);
    }
    else return (dan <= 28);
}


char_array licnaKarta()
{
    return char_array( 
    {'0','1','2','3','4',
    '5','6','7','8','9',
    'A','B','C','D','E','F',
    'G','H','I','J','K',
    'L','M','N','O','P',
    'R','S','T','U',
    'V','Z'
    });
};

char_array brojTelefona()
{
    return char_array( 
    {'0','1','2','3','4',
    '5','6','7','8','9'
    });
};

char_array trecaCifra()
{
    return char_array( 
    {'0','1','2','3','4'});
};

//VRACA RANDOM STRING ZAVISNO OD DUZINE I PROSLIJEDJENOG NIZA
std::string randomString(size_t length, std::function<char(void)> rand_char){
    std::string str(length,0);
    std::generate_n(str.begin(), length, rand_char);
    return str;
}

//GENERISE RANDOM BROJ LICNE KARTE
string generisiBrojLicne() {
    const auto brojLicneKarte = licnaKarta();
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(0, brojLicneKarte.size()-1);
    string temp;
    auto randchar = [brojLicneKarte,&dist,&gen](){return brojLicneKarte[dist(gen)];};
    auto len=9;
    return temp+=randomString(len, randchar);
}

//GENERISE RANDOM BROJ TELEFONA
string generisiBrojTelefona(){
    string temp;
    const auto broj = brojTelefona();
    const auto trecaCif = trecaCifra();
    auto len=1;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(0, broj.size()-1);
    std::uniform_int_distribution<> distT(0, trecaCif.size()-1);
    auto randchar = [broj,&dist,&gen](){return broj[dist(gen)];};
    auto treca = [trecaCif,&distT,&gen](){return trecaCif[distT(gen)];};
    temp+="06";
    temp+=randomString(len, treca);
    len=6;
    return temp+randomString(len, randchar);
}

/*----------STRUKTURE----------*/
struct pacijent{
    string imePrezime, brojLicneKarte, brojTelefona;
    int d, m, g, prioritetnaGrupa;
    uposlenja uposlenje;
    bolesti bolest;
    ambulante ambulanta;

    //REGISTRACIJA NOVOG PACIJENTA
    void inicijalizacija(){
        system("cls");
        int x;
        cout<<crt<<"\t::UNOS PODATAKA O PACIJENTU::"<<crt;
        cout<<"Unesite svoje ime i prezime (u prijavi ce ovo biti vas username): ";
        cin.ignore();
        getline(cin, imePrezime);
        cout<<"Unesite datum rodjenja (npr. 02.09.2001.): ";
        do{
            cin >> d;
            cin.get();
            cin >> m;
            cin.get();
            cin >> g;
            cin.get();
        }while(!validanDatum(d, m, g));
        cout<<"Unesite broj licne karte (u prijavi ce ovo biti vas password): ";
        do{
            getline(cin, brojLicneKarte);
        }while(brojLicneKarte.length()!=9);
        cout<<"Unesite broj telefona: ";
        getline(cin, brojTelefona);
        cout<<endl<<"Odaberite grupu kojoj pripadate: "<<endl;
        cout<<"1. Zdravstveni uposlenik"<<endl;
        cout<<"2. Radnik ili sticenik socijalne ustanove"<<endl;
        cout<<"3. Radnik javne sluzbe"<<endl;
        cout<<"4. Ostalo"<<endl;
        cout<<"Unesite izbor: ";
        do{
            cin>>x;
        }while(x<1 || x>4);
        uposlenje=(uposlenja)x;
        cout<<endl<<"Odaberite klinicko stanje kojem pripadate: "<<endl;
        cout<<"1. Down sindrom"<<endl;
        cout<<"2. Primatelj transplantiranog organa"<<endl;
        cout<<"3. Karcinom"<<endl;
        cout<<"4. Teska respiratorna bolest(cisticna fibroza, teska astma, teska kronicna opstruktivna bolest pluca)"<<endl;
        cout<<"5. Ostalo"<<endl;
        cout<<"Unesite izbor: ";
        do{
            cin>>x;
        }while(x<1 || x>5);
        bolest=(bolesti)x;
        cout<<endl<<"Odaberite vasu ambulantu: "<<endl; 
        cout<<"1. Mokusnice"<<endl;
        cout<<"2. Travnicka"<<endl;
        cout<<"3. Crkvice"<<endl;
        cout<<"4. Radakovo"<<endl;
        cout<<"5. Kineski"<<endl;
        cout<<"Unesite izbor: ";
        do{
            cin>>x;
        }while(x<1 || x>5); 
        ambulanta=(ambulante)x;
        if(int(uposlenje)<=2) prioritetnaGrupa=1;
        else if(2021-g>=75) prioritetnaGrupa=2;
        else if(2021-g>=60 && 2021-g<75) prioritetnaGrupa=3;
        else if (int(uposlenje)==3 || int(bolest)<5) prioritetnaGrupa=4;
        else prioritetnaGrupa=5;
        ofstream prijave("prijave.txt", ios::app);
        prijave<<prioritetnaGrupa<<" ";
        prijave<<imePrezime<<" ";
        prijave<<setfill('0')<<setw(2)<<d<<"."<<setw(2)<<m<<"."<<g<<" ";
        prijave<<brojLicneKarte<<" ";
        prijave<<brojTelefona<<" ";
        prijave<<vratiUposlenje(uposlenje)<<" ";
        prijave<<vratiBolest(bolest)<<" ";
        prijave<<vratiAmbulantu(ambulanta)<<endl;
        cout<<"\nREGISTRACIJA USPJESNA!"<<endl;
        prijave.close();
        system("PAUSE");
        system("cls");
    }

    //KREIRANJE I ISPIS RANDOM PRIJAVE U PRIJAVE.TXT
    void inicijalizacijaRand(){
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> distribUsername(1, 100);
        std::uniform_int_distribution<> distribDan(1, 31);
        std::uniform_int_distribution<> distribMjesec(1, 12);
        std::uniform_int_distribution<> distribGodina(1921, 2020);
        std::uniform_int_distribution<> distribProcenat(0, 99);
        std::uniform_int_distribution<> distribAmbulanta(1, 5);
        int x;
        string temp;
        ifstream imena("imena.txt");
        ifstream prezimena("prezimena.txt");
        x=distribUsername(gen);
        for(int i=0; i<x; i++){
            imena>>temp;
        }
        imePrezime=temp;
        x=distribUsername(gen);
        for(int i=0; i<x; i++){
            prezimena>>temp;
        }
        imePrezime+=" "+temp;
        imena.close();
        prezimena.close();
        do{
            d=distribDan(gen);
            m=distribMjesec(gen);
            g=distribGodina(gen);
        }while(!validanDatum(d, m, g));
        brojLicneKarte=generisiBrojLicne();
        brojTelefona=generisiBrojTelefona();
        int i;
        i=distribProcenat(gen);
        if(i<70) x=4;
        else if (i<80) x=3;
        else if (i<90) x=2;
        else if (i<100) x=1;
        uposlenje=(uposlenja)x;
        i=distribProcenat(gen);
        if(i<60) x=5;
        else if (i<70) x=4;
        else if (i<80) x=3;
        else if (i<90) x=2;
        else if (i<100) x=1;
        bolest=(bolesti)x;
        x=distribAmbulanta(gen);
        ambulanta=(ambulante)x;
        if(int(uposlenje)<=2) prioritetnaGrupa=1;
        else if(2021-g>=75) prioritetnaGrupa=2;
        else if(2021-g>=60 && 2021-g<75) prioritetnaGrupa=3;
        else if (int(uposlenje)==3 || int(bolest)<5) prioritetnaGrupa=4;
        else prioritetnaGrupa=5;
        ofstream prijave("prijave.txt", ios::app);
        prijave<<prioritetnaGrupa<<" ";
        prijave<<imePrezime<<" ";
        prijave<<setfill('0')<<setw(2)<<d<<"."<<setw(2)<<m<<"."<<g<<" ";
        prijave<<brojLicneKarte<<" ";
        prijave<<brojTelefona<<" ";
        prijave<<vratiUposlenje(uposlenje)<<" ";
        prijave<<vratiBolest(bolest)<<" ";
        prijave<<vratiAmbulantu(ambulanta)<<endl;
        prijave.close();
    }

    //ISPIS PODATAKA JEDNOG PACIJENTA
    void ispisPacijent(){ 
        cout<<crt<<"\tPodaci o pacijentu"<<crt;
        cout<<"Ime i prezime: "<<imePrezime<<endl;
        cout<<"Datum rodjenja: "<<setfill('0')<<setw(2)<<d<<"."<<setw(2)<<m<<"."<<g<<endl;
        cout<<"Broj licne karte: "<<brojLicneKarte<<endl;
        cout<<"Broj telefona: "<<brojTelefona<<endl;
        cout<<"Prioritetna grupa: "<<vratiUposlenje(uposlenje)<<endl;
        cout<<"Klinicko stanje: "<<vratiBolest(bolest)<<endl;
        cout<<"Ambulanta prijave: "<<vratiAmbulantu(ambulanta)<<endl;
        cout<<"Prioritetna grupa: "<<prioritetnaGrupa<<endl;
    }
};

/*----------GLOBALNE FUNKCIJE----------*/
void ispisPrijavljenih(){ 
    system("cls");
    string temp;
    ifstream ispis("prijave.txt");
    cout<<left<<setw(20)<<"Prioritetna grupa:"<<setw(20)<<"Ime i prezime:"<<setw(20)<<"Datum rodenja:"<<setw(20)<<"Broj licne karte:"<<setw(20)<<"Broj telefona:"<<setw(40)<<"Uposlenje:"<<setw(35)<<"Klinicko stanje:"<<setw(15)<<"Ambulanta:"<<endl;
    while(true){
        ispis>>temp;
        if(ispis.eof()) break;
        cout<<setw(20)<<temp;
        ispis>>temp;
        cout<<temp<<" ";
        int duzinaImena;
        duzinaImena=temp.length();
        ispis>>temp;
        cout<<setw(19-duzinaImena)<<temp;
        ispis>>temp;
        cout<<setw(20)<<temp;
        ispis>>temp;
        cout<<setw(20)<<temp;
        ispis>>temp;
        cout<<setw(20)<<temp;
        ispis>>temp;
        cout<<setw(40)<<temp;
        ispis>>temp;
        cout<<setw(35)<<temp;
        ispis>>temp;
        cout<<setw(15)<<temp<<endl;
    }
    ispis.close();
    system("PAUSE");
}

//SORTIRA PRIJAVE.TXT NA OSNOVU PRIORITETNIH GRUPA
void sortirajPrijavljene(){
    system("cls");
    ifstream prijave("prijave.txt");
    string temp;
    vector<string> prijavljeni;
    while(!prijave.eof()){
        getline(prijave, temp);
        prijavljeni.push_back(temp);
    }
    prijave.close();
    for(int i=0; i<prijavljeni.size(); i++){
        for(int j=i; j<prijavljeni.size(); j++){
            stringstream temp1(prijavljeni[i]), temp2(prijavljeni[j]);
            int a, b;
            temp1>>a;
            temp2>>b;
            if(a>b) swap(prijavljeni[i], prijavljeni[j]);
        }
    }
    ofstream ispis("prijave.txt");
    for(int i=0; i<prijavljeni.size(); i++){
        ispis<<prijavljeni[i]<<endl;
    }
    ispis.close();
    cout<<"Sortiranje uspjesno!"<<endl;
    system("PAUSE");
}

//PREBACUJE SVE PRIJAVE U VAKCINISANI.TXT
void sviVakcinisani(){
    remove("vakcinisani.txt");
    rename("prijave.txt", "vakcinisani.txt");
    ofstream temp("prijave.txt");
    temp.close();
}

//PREBACUJE VAKCINISANE IZ PRIJAVE.TXT U VAKCINISANI.TXT DOK OSTAVLJA NEVAKCINISANE
void prebaciVakcinisane(int brojVakcina){
    string temp;
    ofstream vakcinisani("vakcinisani.txt");
    ofstream novePrijave("temp.txt");
    ifstream ostatakPrijava("prijave.txt");
    for(int i=0; i<brojVakcina; i++){
        getline(ostatakPrijava, temp);
        vakcinisani<<temp<<endl;
        }
    while(true){
        getline(ostatakPrijava, temp);
        if(ostatakPrijava.eof()) break;
        novePrijave<<temp<<endl;
    }
    ostatakPrijava.close();
    vakcinisani.close();
    novePrijave.close();
    remove("prijave.txt");
    rename("temp.txt", "prijave.txt");
}

//UZIMA PODATKE IZ PRIJAVE.TXT, TE NA OSNOVU BROJA VAKCINA UNESENOG OD ADMINISTRATORA KREIRA TERMINI.TXT
void kreirajTermine(){
    system("cls");
    int brojVakcina, brojRadnika, d, m, g, h=8, min=0, br=0;
    ofstream termini("termini.txt");
    ifstream prijave("prijave.txt");
    while(true){
        cout<<"\tUnesite broj vakcina za ovu sedmicu: ";
        cin>>brojVakcina;
        cout<<"\tUnesite broj zdravstvenih radnika za ovu sedmicu: ";
        cin>>brojRadnika;
        if(brojVakcina>360*brojRadnika) {
            cout<<"\t[ERROR] Prevelik broj vakcina na zadani broj radnika"<<endl;
            cout<<"\tSmanjite broj vakcina ili povecajte broj radnika!"<<endl;
        }
        else break;
    }
    int dnevniBrojVakcina=brojVakcina/5;
    int ostatakVakcina=brojVakcina%5;
    cout<<"\tUnesite danasnji datum: ";
    do{
        cin>>d;
        cin.get();
        cin>>m;
        cin.get();
        cin>>g;
        cin.get();
    }while(!validanDatum(d, m, g));

    string temp;
    termini<<setw(2)<<setfill('0')<<d<<"."<<setw(2)<<setfill('0')<<m<<"."<<g<<endl;
    termini<<left<<setw(15)<<setfill(' ')<<"PONEDELJAK: ";
    for(int i=0; i<dnevniBrojVakcina; i++){
        prijave>>temp;
        if(prijave.eof()) {
            cout<<"\tPrijave uspjesno kreirane!"<<endl;
            cout<<"\tOstatak vakcina: "<<brojVakcina-br<<endl;
            prijave.close();
            termini.close();
            sviVakcinisani();
            system("PAUSE");
            return;
        }
        termini<<" | "<<h<<":"<<setw(2)<<setfill('0')<<min<<" ";
        if((i+1)%brojRadnika==0){
            min+=10;
            if(min==60) {
                h++;
                min=0;
            }
        }
        prijave>>temp;
        prijave>>temp;
        prijave>>temp;
        prijave>>temp;
        termini<<temp;
        br++;
        getline(prijave, temp);
    }
    h=8;
    min=0;
    termini<<endl<<left<<setw(15)<<setfill(' ')<<"UTORAK: ";
    for(int i=0; i<dnevniBrojVakcina; i++){
        prijave>>temp;
        if(prijave.eof()) {
            cout<<"\tPrijave uspjesno kreirane!"<<endl;
            cout<<"\tOstatak vakcina: "<<brojVakcina-br<<endl;
            prijave.close();
            termini.close();
            sviVakcinisani();
            system("PAUSE");
            return;
        }
        termini<<" | "<<h<<":"<<setw(2)<<setfill('0')<<min<<" ";
        if((i+1)%brojRadnika==0){
            min+=10;
            if(min==60) {
                h++;
                min=0;
            }
        }
        prijave>>temp;
        prijave>>temp;
        prijave>>temp;
        prijave>>temp;
        termini<<temp;
        br++;
        getline(prijave, temp);
    }
    h=8;
    min=0;
    termini<<endl<<left<<setw(15)<<setfill(' ')<<"SRIJEDA: ";
    for(int i=0; i<dnevniBrojVakcina; i++){
        prijave>>temp;
        if(prijave.eof()) {
            cout<<"\tPrijave uspjesno kreirane!"<<endl;
            cout<<"\tOstatak vakcina: "<<brojVakcina-br<<endl;
            prijave.close();
            termini.close();
            sviVakcinisani();
            system("PAUSE");
            return;
        }
        termini<<" | "<<h<<":"<<setw(2)<<setfill('0')<<min<<" ";
        if((i+1)%brojRadnika==0){
            min+=10;
            if(min==60) {
                h++;
                min=0;
            }
        }
        prijave>>temp;
        prijave>>temp;
        prijave>>temp;
        prijave>>temp;
        termini<<temp;
        br++;
        getline(prijave, temp);
    }
    h=8;
    min=0;
    termini<<endl<<left<<setw(15)<<setfill(' ')<<"CETVRTAK: ";
    for(int i=0; i<dnevniBrojVakcina; i++){
        prijave>>temp;
        if(prijave.eof()) {
            cout<<"\tPrijave uspjesno kreirane!"<<endl;
            cout<<"\tOstatak vakcina: "<<brojVakcina-br<<endl;
            prijave.close();
            termini.close();
            sviVakcinisani();
            system("PAUSE");
            return;
        }
        termini<<" | "<<h<<":"<<setw(2)<<setfill('0')<<min<<" ";
        if((i+1)%brojRadnika==0){
            min+=10;
            if(min==60) {
                h++;
                min=0;
            }
        }
        prijave>>temp;
        prijave>>temp;
        prijave>>temp;
        prijave>>temp;
        termini<<temp;
        br++;
        getline(prijave, temp);
    }
    h=8;
    min=0;
    termini<<endl<<left<<setw(15)<<setfill(' ')<<"PETAK: ";
    for(int i=0; i<dnevniBrojVakcina+ostatakVakcina; i++){
        prijave>>temp;
        if(prijave.eof()) {
            cout<<"\tPrijave uspjesno kreirane!"<<endl;
            cout<<"\tOstatak vakcina: "<<brojVakcina-br<<endl;
            prijave.close();
            termini.close();
            sviVakcinisani();
            system("PAUSE");
            return;
        }
        termini<<" | "<<h<<":"<<setw(2)<<setfill('0')<<min<<" ";
        if((i+1)%brojRadnika==0){
            min+=10;
            if(min==60) {
                h++;
                min=0;
            }
        }
        prijave>>temp;
        prijave>>temp;
        prijave>>temp;
        prijave>>temp;
        termini<<temp;
        br++;
        getline(prijave, temp);
    }
    prijave.close();
    termini.close();
    prebaciVakcinisane(brojVakcina);
    cout<<"\tTermini uspjesno kreirani!"<<endl;
    system("PAUSE");
}

//POZIVA RANDOM PRIJAVU N PUTA
void generisiPrijave(){ 
    system("cls");
    int n;
    cout<<"Unesite koliko mock prijava zelite: "<<endl;
    cin>>n;
    for(int i=0; i<n; i++){
        pacijent *temp=new pacijent;
        temp->inicijalizacijaRand();
        delete temp;
        temp=NULL;
    }
    cout<<"Generisanje uspjesno!"<<endl;
    system("PAUSE");
}

//BRISE PODATKE IZ PRIJAVE.TXT
void obrisiPrijave(){ 
    system("cls");
    ofstream brisanje("prijave.txt");
    brisanje.clear();
    cout<<"Brisanje uspjesno!"<<endl;
    system("PAUSE");
}

//ADMIN MENI SA SVIM OPCIJAMA, OPCIJE U [] PREDSTAVLJAJU OPCIJE KOJE SE KORISTE U SVRHU TESTIRANJA
void adminMeni(){ 
    int izbor=0;
    do{
        system("cls");
        cout<<"--------------------ADMIN MENI--------------------"<<endl;
        cout<<"\n\tUPUTE: Sortiranje prijavljenih pozivati prije kreiranja termina\n\t       Sortirati i kreirati termine nedjeljom"<<endl;
        cout<<"\n\t1. Ispis liste prijavljenih"<<endl;
        cout<<"\t2. Sortiraj prijavljene"<<endl;
        cout<<"\t3. Kreiraj termine za narednu sedmicu"<<endl;
        cout<<"\t4. [GENERISI N MOCK PRIJAVA]"<<endl;
        cout<<"\t5. [OBRISI LISTU PRIJAVLJENIH]"<<endl;
        cout<<"\t6. Kraj programa"<<endl;
        cout<<"\n\tUnos: ";
        do{
            cin>>izbor;
        }while(izbor<1 || izbor>6);
        switch(izbor){
            case 1:
                ispisPrijavljenih();
                break;
            case 2:
                sortirajPrijavljene();
                break;
            case 3:
                kreirajTermine();
                break;
            case 4:
                generisiPrijave();
                break;
            case 5:
                obrisiPrijave();
                break;
            case 6:
                cout<<"\n\tDovidenja!";
                exit(0);
        }
    }while(izbor!=6);
}

//Na osnovu broja licne karte/passworda ispisuje datum i vrijeme vakcinacije iz dokumenta termini.txt
void ispisiTermin(string password){
    system("cls");
    string temp1, temp2, temp3;
    string temp, vrijeme;
    int br=0;
    ifstream termin("termini.txt");
    termin>>temp;
    if(termin.eof()){
            cout<<"\tTermin Vam jos nije dodijeljen!"<<endl;
            system("PAUSE");
            termin.close();
            return;
    }
    temp1=temp.substr(0, 2);
    temp2=temp.substr(3, 2);
    temp3=temp.substr(6, 4);
    stringstream dan(temp1), mjesec(temp2), godina(temp3);
    int d, m, g;
    dan>>d;
    mjesec>>m;
    godina>>g;
    while(true){
        termin>>temp;
        if(termin.eof()){
            cout<<"\tTermin Vam jos nije dodijeljen!"<<endl;
            system("PAUSE");
            termin.close();
            return;
        }
        if(temp=="PONEDELJAK:" || temp=="UTORAK:" || temp=="SRIJEDA:" || temp=="CETVRTAK:" || temp=="PETAK:" ) {
            termin>>temp;
            br++;
        }
        termin>>vrijeme;
        termin>>temp;
        if(temp==password){
            for(int i=0; i<br; i++){
                d++;
                if(!validanDatum(d, m, g)){
                    m++;
                    d=1;
                    if(!validanDatum(d, m, g)){
                        g++;
                        m=1;
                    }
                }
            }
            cout<<"Datum vakcinacije: "<<setw(2)<<setfill('0')<<d<<"."<<setw(2)<<m<<"."<<g<<"."<<endl;
            cout<<"Vrijeme vakcinacije: "<<vrijeme<<endl;
            termin.close();
            system("PAUSE");
            return;
        }
    }
}

//PACIJENT MENI SA SVOJIM OPCIJAMA
void pacijentMeni(string username, string password){ 
    system("cls");
    int izbor;
    cout<<"\t--------PACIJENT MENI--------"<<endl;
    do{
        cout<<"\n\t1. Prikazi datum i termin vakcinacije"<<endl;
        cout<<"\t2. Kraj programa"<<endl;
        cout<<"\n\tUnos: ";
        do{
            cin>>izbor;
        }while(izbor<1 || izbor>2);
        switch(izbor){
            case 1:
                ispisiTermin(password);
                break;
            case 2:
                cout<<"\n\tDovidenja!";
                exit(0);
        }
    }while(izbor!=2);
}

//PRETRAZUJE UNESENI USERNAME U PRIJAVE.TXT, USERNAME ODGOVARA IMENU I PREZIMENU
bool userProvjera(string username){ 
    string temp, ime, prezime, imeProvjera, prezimeProvjera;
    ifstream provjera("prijave.txt");
    ifstream provjeraVakcinisani("vakcinisani.txt");
    imeProvjera=username.substr(0, username.find(' '));
    prezimeProvjera=username.substr(username.find(' ')+1, username.length()-imeProvjera.length());
    while(!provjera.eof()){
        provjera>>temp;
        provjera>>temp;
        ime=temp;
        provjera>>temp;
        prezime=temp;
        if(ime==imeProvjera && prezime==prezimeProvjera) return true;
        getline(provjera, temp);
    }
    while(!provjeraVakcinisani.eof()){
        provjeraVakcinisani>>temp;
        provjeraVakcinisani>>temp;
        ime=temp;
        provjeraVakcinisani>>temp;
        prezime=temp;
        if(ime==imeProvjera && prezime==prezimeProvjera) return true;
        getline(provjeraVakcinisani, temp);
    }
    provjeraVakcinisani.close();
    provjera.close();
    return false;
}

//PRETRAZUJE UNESENI PASSWORD U PRIJAVE.TXT, PASSWORD ODGOVARA BROJU LICNE KARTE
bool passProvjera(string password){ 
    string temp;
    ifstream provjera("prijave.txt");
    ifstream provjeraVakcinisani("vakcinisani.txt");
    while(!provjera.eof()){
        provjera>>temp;
        provjera>>temp;
        provjera>>temp;
        provjera>>temp;
        provjera>>temp;
        if(temp==password) return true;
        getline(provjera, temp);
    }
    while(!provjeraVakcinisani.eof()){
        provjeraVakcinisani>>temp;
        provjeraVakcinisani>>temp;
        provjeraVakcinisani>>temp;
        provjeraVakcinisani>>temp;
        provjeraVakcinisani>>temp;
        if(temp==password) return true;
        getline(provjeraVakcinisani, temp);
    }
    provjeraVakcinisani.close();
    provjera.close();
    return false;
}

int main(){
    srand(time(NULL));
    rand();
    pacijent temp;
    string username, password;
    int izbor;
    
    cout<<"--------DOBRODOSLI U ASTRAZENICU!--------"<<endl;
    //POCETNI MENI
    do{
        do{
            cout<<"\n\t1. Registracija"<<endl;
            cout<<"\t2. Prijava"<<endl;
            cout<<"\t3. [ADMIN OVERRIDE]"<<endl;
            cout<<"\t4. Kraj programa"<<endl;
            cout<<"\tUnos: ";
            cin>>izbor;
        }while(izbor<1 || izbor>4);
        switch(izbor){
            case 1:
                temp.inicijalizacija();
            case 2:
                while(true){
                    do{
                        cout<<"\tUsername: ";
                        cin.ignore();
                        getline(cin, username);
                        cout<<"\tPassword: ";
                        getline(cin, password);
                        if(username==adminUser && password==adminPass) {
                            adminMeni();
                            break;
                        }
                        if(userProvjera(username) && passProvjera(password)) {
                            pacijentMeni(username, password);
                            break;
                        }
                        else cout<<"\tPogresni username i/ili password!"<<endl;
                    }while(true);
                }
            case 3:
                adminMeni();
                break;
            case 4:
                cout<<"\n\tDovidenja!"<<endl;
                exit(0);
        }
    }while(izbor!=3);
}
