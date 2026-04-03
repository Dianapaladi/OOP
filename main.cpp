#include <iostream>
#include <fstream>
using namespace std;

class Rezervare {
protected:
    string nume;
    string dataOra;
    int nrPersoane;
    int durata;

public:
    Rezervare(string n, string d, int nr, int dur) {
        nume = n;
        dataOra = d;
        nrPersoane = nr;
        durata = dur;
    }

    virtual int calculeazaDurata() {
        return durata;
    }

    virtual int calculeazaPret() = 0;

    virtual string tip() {
        return "Rezervare";
    }

    virtual void afisare() {
        cout << "Tip: " << tip() << endl;
        cout << "Client: " << nume << endl;
        cout << "Data/Ora: " << dataOra << endl;
        cout << "Nr persoane: " << nrPersoane << endl;
        cout << "Durata: " << calculeazaDurata() << " ore" << endl;
        cout << "Pret: " << calculeazaPret() << " lei\n";
        cout << "   \n";
    }

    virtual ~Rezervare() {}
};

class RezervareZilnica : public Rezervare {
public:
    RezervareZilnica(string n, string d, int nr, int dur)
        : Rezervare(n, d, nr, dur) {}

    int calculeazaPret() {
        if (nrPersoane <= 2)
            return 50;
        return 50 + (nrPersoane - 2) * 20;
    }

    string tip() {
        return "Zilnica";
    }
};

class RezervareEveniment : public Rezervare {
public:
    RezervareEveniment(string n, string d, int nr, int dur)
        : Rezervare(n, d, nr, dur) {}

    int calculeazaPret() {
        int pret = 200;
        if (durata > 3)
            pret += (durata - 3) * 50;
        return pret;
    }

    string tip() {
        return "Eveniment Special";
    }
};

class RezervareGrup : public Rezervare {
public:
    RezervareGrup(string n, string d, int nr, int dur)
        : Rezervare(n, d, nr, dur) {}

    int calculeazaPret() {
        if (nrPersoane <= 20)
            return 500;
        return 500 + (nrPersoane - 20) * 10;
    }

    string tip() {
        return "Grup Mare";
    }
};

class RezervareVIP : public Rezervare {
public:
    RezervareVIP(string n, string d, int nr, int dur)
        : Rezervare(n, d, nr, dur) {}

    int calculeazaPret() {
        if (nrPersoane <= 5)
            return 1000;
        return 1000 + (nrPersoane - 5) * 50;
    }

    string tip() {
        return "VIP";
    }
};

int main() {
    Rezervare** lista = new Rezervare*[100];
    int n = 0;
    ifstream f("rezervari.txt");
    string tip, nume, data, ora;
    int nr, durata;

    while (f >> tip >> nume >> data >> ora >> nr >> durata) {
        string dataOra = data + " " + ora;

        if (tip == "RezervareZilnica")
            lista[n++] = new RezervareZilnica(nume, dataOra, nr, durata);
        else if (tip == "RezervareEvenimentSpecial")
            lista[n++] = new RezervareEveniment(nume, dataOra, nr, durata);
        else if (tip == "RezervareGrupMare")
            lista[n++] = new RezervareGrup(nume, dataOra, nr, durata);
        else if (tip == "RezervareVIP")
            lista[n++] = new RezervareVIP(nume, dataOra, nr, durata);
    }
    f.close();
    for (int i = 0; i < n; i++) {
        lista[i]->afisare();
    }
    for (int i = 0; i < n; i++) {
        delete lista[i];
    }
    delete[] lista;
    return 0;
}
