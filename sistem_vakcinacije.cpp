#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>
using namespace std;

char * crt = "\n---------------------------------------------\n";
enum uposlenja{zdravstveni_uposlenik=1, radnik_ili_sticenik_socijalne_ustanove, javna_sluzba, ostalo};
enum bolesti{down_sindrom=1, primatelj_transplantiranog_organa, karcinom, teska_respiratorna_bolest, Ostalo};
enum lokacije{mokusnice=1,travnicka,crkvice,radakovo,kineski};

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

string vratiLokaciju(int x){  //mozemo ih  jos dodat poslije, al ovo samo za primjer
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
bool validanDatum(int dan,int mjesec,int godina){
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
};

struct ambulanta{
	int lokacija, brojVakcina;
};

struct termin{
    pacijent pacijent;
    ambulanta ambulanta;
    string termin;
    string datum;
};

void inicijalizacija(pacijent &p,ambulanta &a){
    int x;
    cout<<crt<<"\t::UNOS PODATAKA O PACIJENTU::"<<crt;
    cout<<"Unesite svoje ime i prezime: ";
    cin.ignore();
    getline(cin, p.imePrezime);
    cout<<"Unesite datum rodjenja (npr. 02.09.2001.): ";
    do{
    	cin >> p.d;
    	cin.get();
    	cin >> p.m;
    	cin.get();
    	cin >> p.g;
    	cin.get();
    }while(!validanDatum(p.d,p.m,p.g));
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
    cout<<endl<<"Odaberite vasu ambulantu: "<<endl; 
    
    if(int(p.uposlenje)<=2) p.prioritetnaGrupa=1;
    else if(2021-p.g>=75) p.prioritetnaGrupa=2;
    else if(2021-p.g>=60 && 2021-p.g<75) p.prioritetnaGrupa=3;
    else if (int(p.uposlenje)==3 || int(p.bolest)<5) p.prioritetnaGrupa=4;
    else p.prioritetnaGrupa=5;
    cout<<"1. Mokusnice"<<endl;
    cout<<"2. Travnicka"<<endl;
    cout<<"3. Crkvice"<<endl;
    cout<<"4. Radakovo"<<endl;
    cout<<"5. Kineski"<<endl;
    cout<<"Unesite izbor: ";
    do{
        cin>>x;
    }while(x<1 || x>5); 
    a.lokacija=(lokacije)x;

}

void ispisPacijent(pacijent p,ambulanta a){
    cout<<crt<<"\tPodaci o pacijentu"<<crt;
    cout<<"Ime i prezime: "<<p.imePrezime<<endl;
    cout<<"Datum rodjenja: "<<setfill('0')<<setw(2)<<p.d<<"."<<setw(2)<<p.m<<"."<<p.g<<endl;
    cout<<"Broj licne karte: "<<p.brojLicneKarte<<endl;
    cout<<"Broj telefona: "<<p.brojTelefona<<endl;
    cout<<"Prioritetna grupa: "<<vratiUposlenje(p.uposlenje)<<endl;
    cout<<"Klinicko stanje: "<<vratiBolest(p.bolest)<<endl;
    cout<<"Prioritetna grupa: "<<p.prioritetnaGrupa<<endl;
    cout<<"Ambulanta prijave: "<<vratiLokaciju(a.lokacija)<<endl;
}

int main(){
    int test;
    cin>>test;
    vector <pacijent> pacijenti;
    pacijent temp;
    ambulanta vak;
    inicijalizacija(temp,vak);
    pacijenti.push_back(temp);
    system("pause");
    system("cls");
    ispisPacijent(temp,vak);
    return 0;
}
