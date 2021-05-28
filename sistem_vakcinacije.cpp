#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>
#include <cstring>
using namespace std;

char * crt = "\n---------------------------------------------\n";
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

bool validanDatum(int dan, int mjesec, int godina){
	int minValidnaGodina(1900),maxValidnaGodina(2020);
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

struct pacijent{
    string imePrezime, brojLicneKarte, brojTelefona;
    int d, m, g, prioritetnaGrupa;
    uposlenja uposlenje;
    bolesti bolest;
    ambulante ambulanta;

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
        
        if(int(uposlenje)<=2) prioritetnaGrupa=1;
        else if(2021-g>=75) prioritetnaGrupa=2;
        else if(2021-g>=60 && 2021-g<75) prioritetnaGrupa=3;
        else if (int(uposlenje)==3 || int(bolest)<5) prioritetnaGrupa=4;
        else prioritetnaGrupa=5;
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
        ofstream prijave("prijave.txt", ios::app);
        prijave<<endl<<prioritetnaGrupa<<" ";
        prijave<<imePrezime<<" ";
        prijave<<setfill('0')<<setw(2)<<d<<"."<<setw(2)<<m<<"."<<g<<" ";
        prijave<<brojLicneKarte<<" ";
        prijave<<brojTelefona<<" ";
        prijave<<vratiUposlenje(uposlenje)<<" ";
        prijave<<vratiBolest(bolest)<<" ";
        prijave<<vratiAmbulantu(ambulanta);
        cout<<"REGISTRACIJA USPJESNA!"<<endl;
        prijave.close();
        system("PAUSE");
        system("cls");
    }

    void ispisPacijent(){ //trenutno ne radi nista ali nek ostane do finalne verzije
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

struct termin{ //prilikom kreiranja termina koristiti funkcije unutar strukture, a ne globalne
    pacijent pacijent;
    string termin;
    int d, m, g;
};

void ispisPrijavljenih(){ //iz prijave.txt uzima sve prijavljene te ispisuje na ekran
    system("cls");
    string temp;
    ifstream ispis("prijave.txt");
    cout<<left<<setw(20)<<"Prioritetna grupa:"<<setw(20)<<"Ime i prezime:"<<setw(20)<<"Datum rodenja:"<<setw(20)<<"Broj licne karte:"<<setw(20)<<"Broj telefona:"<<setw(40)<<"Uposlenje:"<<setw(35)<<"Klinicko stanje:"<<setw(15)<<"Ambulanta:"<<endl;
    while(!ispis.eof()){
        ispis>>temp;
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

void sortirajPrijavljene(){ //sortiranje dodaje viska red, te iz tog razloga nakon sortiranja ispis nece funkcionisati uredno
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

void kreirajTermine(){
    /*
    -Omoguciti administratoru unos broja vakcina za sedmicu
    -Na osnovu broja vakcina kreirati za svaki dan brojVakcina/5 termina od npr. 10:00 sa razmakom od 5 minuta izmedju termina
    -U novi dokument termini.txt ispisati po kolonama termine u formatu:
    PONEDELJAK              UTORAK                  SRIJEDA                 CETVRTAK                PETAK
    vrijeme brojLicneKarte  vrijeme brojLicneKarte  vrijeme brojLicneKarte  vrijeme brojLicneKarte  vrijeme brojLicneKarte
    vrijeme brojLicneKarte  vrijeme brojLicneKarte  vrijeme brojLicneKarte  vrijeme brojLicneKarte  vrijeme brojLicneKarte
    vrijeme brojLicneKarte  vrijeme brojLicneKarte  vrijeme brojLicneKarte  vrijeme brojLicneKarte  vrijeme brojLicneKarte
    .
    .
    .

    -Tricky part nakon ovoga: obrisati sve prijavljene iz prijave.txt koji su dobili svoj termin a ostaviti za sljedecu sedmicu one bez termina
    (ideja: dodati varijablu u strukturu pacijent koja se odnosi na postojanje termina za pacijenta na osnovu koje se taj pacijent brise ili ostavlja u prijave.txt)
    (dodatni tip: kada dodje do prvog pacijenta kojem je vrijednost false svi ostaju u dokumentu iz razloga sto su pacijenti vec sortirani po prioritetnim grupama, te kada prvi nema termin svi do kraja nemaju)
    
    */
}

void adminMeni(){ //potpuno funkcionalan meni samo kreirajTermine trenutno ne radi nista
    int izbor=0;
    do{
        system("cls");
        cout<<"\t-----ADMIN MENI-----"<<endl;
        cout<<"1. Ispis liste prijavljenih"<<endl;
        cout<<"2. Sortiraj prijavljene"<<endl;
        cout<<"3. Kreiraj termine za narednu sedmicu"<<endl;
        cout<<"4. Kraj programa"<<endl;
        cout<<"Unos: ";
        do{
            cin>>izbor;
        }while(izbor<1 || izbor>4);
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
                cout<<"Dovidenja!";
                exit(0);
        }
    }while(izbor!=4);
}

void ispisiTermin(string password){ 
    /*
    -Na osnovu broja licne karte/passworda ispisati datum i vrijeme vakcinacije iz dokumenta termini.txt
    -U slucaju da jos nema termin ispisati navedeno
    */
}

void pacijentMeni(string username, string password){ //gotov meni ali nema funkcionalnost
    system("cls");
    int izbor;
    do{
        cout<<"1. Prikazi datum i termin vakcinacije"<<endl;
        cout<<"2. Kraj programa"<<endl;
        cout<<"Unos: ";
        do{
            cin>>izbor;
        }while(izbor<1 || izbor>2);
        switch(izbor){
            case 1:
                ispisiTermin(password);
                break;
            case 2:
                cout<<"Dovidenja!";
                exit(0);
        }
    }while(izbor!=2);
}

bool userProvjera(string username){ //pretrazuje username-a u prijave.txt sto odgovara imenu i prezimenu
    string temp, ime, prezime, imeProvjera, prezimeProvjera;
    ifstream provjera("prijave.txt");
    imeProvjera=username.substr(0, username.find(' '));
    cout<<imeProvjera<<endl;
    prezimeProvjera=username.substr(username.find(' ')+1, username.length()-imeProvjera.length());
    cout<<prezimeProvjera<<endl;
    while(!provjera.eof()){
        provjera>>temp;
        provjera>>temp;
        ime=temp;
        provjera>>temp;
        prezime=temp;
        if(ime==imeProvjera && prezime==prezimeProvjera) return true;
        getline(provjera, temp);
    }
    provjera.close();
    return false;
}

bool passProvjera(string password){ //pretrazuje pass u prijave.txt sto odgovara broju licne karte
    string temp;
    ifstream provjera("prijave.txt");
    while(!provjera.eof()){
        provjera>>temp;
        provjera>>temp;
        provjera>>temp;
        provjera>>temp;
        provjera>>temp;
        if(temp==password) return true;
        getline(provjera, temp);
    }
    provjera.close();
    return false;
}

int main(){
    pacijent temp;
    string username, password;
    string adminUser="administrator", adminPass="AZD1222"; //admin info
    cout<<"\tDOBRODOSLI U ASTRAZENICU!"<<endl;
    int izbor;
    do{
        do{
            cout<<"1. Registracija"<<endl;
            cout<<"2. Prijava"<<endl;
            cout<<"3. Kraj programa"<<endl;
            cout<<"4. [ADMIN OVERRIDE]"<<endl; //obrisati prije finalne verzije
            cout<<"Unos: ";
            cin>>izbor;
        }while(izbor<1 || izbor>4);
        switch(izbor){
            case 1:
                temp.inicijalizacija();
            case 2:
                while(true){
                    do{
                        cout<<"Username: ";
                        cin.ignore();
                        getline(cin, username);
                        cout<<username<<endl;
                        cout<<"Password: ";
                        getline(cin, password);
                        cout<<password<<endl;
                        if(username==adminUser && password==adminPass) {
                            adminMeni();
                            break;
                        }
                        if(userProvjera(username) && passProvjera(password)) {
                            pacijentMeni(username, password);
                            break;
                        }
                        else cout<<"Pogresni username i/ili password!"<<endl;
                    }while(true);
                }
            case 3:
                cout<<"Dovidenja!"<<endl;
                exit(0);
            case 4:
                adminMeni();
                break;
        }
    }while(izbor!=3);
    return 0;
}