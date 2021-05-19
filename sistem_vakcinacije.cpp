#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>
using namespace std;

char * crt = "\n---------------------------------------------\n";
enum uposlenja{zdravstveni_uposlenik=1, radnik_ili_sticenik_socijalne_ustanove, javna_sluzba, ostalo};
enum bolesti{down_sindrom=1, primatelj_transplantiranog_organa, karcinom, teska_respiratorna_bolest, Ostalo};

string vratiUposlenje(int x){
    switch(x){
        case 1:
            return "Zdravstveni uposlenik";
        case 2:
            return "Radnik ili sticenik socijalne ustanove";
        case 3:
            return "Radnik javne sluzbe";
        case 4:
            return "Ostalo";
    }
}

string vratiBolest(int x){
    switch(x){
        case 1:
            return "Down sindrom";
        case 2:
            return "Primatelj transplantiranog organa";
        case 3:
            return "Karcinom";
        case 4:
            return "Teska respiratorna bolest";
        case 5:
            return "Ostalo";
    }
}

struct pacijent{
    string imePrezime, brojLicneKarte, brojTelefona;
    int d, m, g, prioritetnaGrupa;
    uposlenja uposlenje;
    bolesti bolest;
};

void inicijalizacija(pacijent &p){
    int x;
    cout<<crt<<"\t::UNOS PODATAKA O PACIJENTU::"<<crt;
    cout<<"Unesite svoje ime i prezime: ";
    cin.ignore();
    getline(cin, p.imePrezime);
    cout<<"Unesite datum rodjenja (npr. 02.09.2001.): ";
    cin >> p.d;
    cin.get();
    cin >> p.m;
    cin.get();
    cin >> p.g;
    cout<<"Unesite broj licne karte: ";
    do{
        getline(cin, p.brojLicneKarte);
    }while(p.brojLicneKarte.length()!=9);
    cout<<"Unesite broj telefona: ";
    getline(cin, p.brojTelefona);
    cout<<endl<<"Odaberite grupu kojoj pripadate: "<<endl;
    cout<<"1. Zdravstveni uposlenik"<<endl;
    cout<<"2. Radnik ili sticenik socijalne ustanove"<<endl;
    cout<<"3. Radnik javne sluzbe"<<endl;
    cout<<"4. Ostalo"<<endl;
    cout<<"Unesite izbor: ";
    do{
        cin>>x;
    }while(x<1 || x>4);
    p.uposlenje=(uposlenja)x;
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
    p.bolest=(bolesti)x;
    if(int(p.uposlenje)<=2) p.prioritetnaGrupa=1;
    else if(2021-p.g>=75) p.prioritetnaGrupa=2;
    else if(2021-p.g>=60 && 2021-p.g<75) p.prioritetnaGrupa=3;
    else if (int(p.uposlenje)==3 || int(p.bolest)<5) p.prioritetnaGrupa=4;
    else p.prioritetnaGrupa=5;

}

void ispisPacijent(pacijent p){
    cout<<crt<<"\tPodaci o pacijentu"<<crt;
    cout<<"Ime i prezime: "<<p.imePrezime<<endl;
    cout<<"Datum rodjenja: "<<setfill('0')<<setw(2)<<p.d<<"."<<setw(2)<<p.m<<"."<<p.g<<endl;
    cout<<"Broj licne karte: "<<p.brojLicneKarte<<endl;
    cout<<"Broj telefona: "<<p.brojTelefona<<endl;
    cout<<"Prioritetna grupa: "<<vratiUposlenje(p.uposlenje)<<endl;
    cout<<"Klinicko stanje: "<<vratiBolest(p.bolest)<<endl;
    cout<<"Prioritetna grupa: "<<p.prioritetnaGrupa<<endl;
}

int main(){
    int test;
    cin>>test;
    vector <pacijent> pacijenti;
    pacijent temp;
    inicijalizacija(temp);
    pacijenti.push_back(temp);
    system("pause");
    system("cls");
    ispisPacijent(temp);
    return 0;
}