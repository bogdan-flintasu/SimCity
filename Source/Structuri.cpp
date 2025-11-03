//
// Created by flint on 10/28/2025.
//

#include <iostream>

#include "../Headers/Structuri.h"

//Implementare clasa Strada
Strada::Strada(int id, std::string  nume_, double cost_c, double cost_i, bool trot, bool unic, int nr_benzi, double lung) : ID(id), nume(std::move(nume_)), cost_construire(cost_c), cost_intretinere(cost_i),
                                                                                                            trotuar(trot), sens_unic(unic), numar_benzi(nr_benzi), lungime(lung) {}

Strada::Strada(const Strada& other) = default;


Strada::~Strada() = default;

Strada& Strada::operator=(const Strada& other) {
    if (this != &other) {
        ID = other.ID;
        nume = other.nume;
        cost_construire = other.cost_construire;
        cost_intretinere = other.cost_intretinere;
        trotuar = other.trotuar;
        sens_unic = other.sens_unic;
        numar_benzi = other.numar_benzi;
        lungime = other.lungime;
    }
    return *this;
}

int Strada::get_ID() const { return ID; }
double Strada::get_cost_intretinere() const { return cost_intretinere; }
const std::string& Strada::get_nume() const { return nume; }
bool Strada::get_sens_unic() const { return sens_unic; }
double Strada::get_lungime() const { return lungime; }
int Strada::get_numar_benzi() const { return numar_benzi; }

std::ostream& operator<<(std::ostream& os, const Strada& s) {
    os << " Strada" << s.nume << " (ID: " << s.ID << ")\n";
    os << " Cost C/I: " << s.cost_construire << "/" << s.cost_intretinere << " RON \n";
    os << " Detalii: " << s.lungime << "m, " << s.numar_benzi << " benzi, "<< (s.trotuar ? "Cu trotuar" : "Fara trotuar") << ", "<< (s.sens_unic ? "Sens unic" : "Sens dublu");
    return os;
}

//Implementari clasa CladireRezidentiala
std::string reztostr(const CladiriRezidentiale tip) {
    switch (tip) {
        case CladiriRezidentiale::CASA: return "Casa";
        case CladiriRezidentiale::BLOC: return "Bloc";
        default: return "Necunoscut";
    }
}



CladireRezidentiala::CladireRezidentiala(int id, std::string nume_, int cost_c, int cost_i, CladiriRezidentiale  tip_, int suprafata, int etaje, int locatari) : ID(id), nume(std::move(nume_)), cost_construire(cost_c),
                                                                                                                                                    cost_intretinere(cost_i), tip(tip_), suprafata_utila(suprafata),
                                                                                                                                                    numar_etaje(etaje), numar_locuitori(locatari){}

CladireRezidentiala::CladireRezidentiala(const CladireRezidentiala &other): ID(other.ID),
      nume(other.nume),
      cost_construire(other.cost_construire),
      cost_intretinere(other.cost_intretinere),
      tip(other.tip),
      suprafata_utila(other.suprafata_utila),
      numar_etaje(other.numar_etaje),
      numar_locuitori(other.numar_locuitori) {
    std::cout << "Constructorul de copiere al clasei CladireRezidentiala a fost apelat.\n";
}

CladireRezidentiala& CladireRezidentiala:: operator=(const CladireRezidentiala& other) {
    if (this != &other) {
        ID = other.ID;
        nume = other.nume;
        cost_construire = other.cost_construire;
        cost_intretinere = other.cost_intretinere;
        tip = other.tip;
        suprafata_utila = other.suprafata_utila;
        numar_etaje = other.numar_etaje;
        numar_locuitori = other.numar_locuitori;
    }
    return *this;
}

CladireRezidentiala::~CladireRezidentiala() {
    std::cout << "Destructorul clasei CladireRezidentiala a fost apelat.\n";
}

int CladireRezidentiala::get_ID() const { return ID; }
double CladireRezidentiala::get_cost_intretinere() const { return cost_intretinere; }
const std::string& CladireRezidentiala::get_nume() const { return nume; }
CladiriRezidentiale CladireRezidentiala::get_tip() const { return tip; }
int CladireRezidentiala::get_numar_locuitori() const { return numar_locuitori; }

std::ostream& operator<<(std::ostream& os, const CladireRezidentiala& cr) {
    os << " Cladire rezidentiala: " << cr.nume << " (Tip: " << reztostr(cr.tip) << ")\n";
    os << " Cost C/I: " << cr.cost_construire << "/" << cr.cost_intretinere << " RON \n";
    os << "Detalii: " << cr.numar_etaje <<" etaje, " << cr.suprafata_utila << "m2 suprafata utila, " << cr.numar_locuitori << " locatari\n";
    return os;
}

//Implementare clasa CladirePublica
std::string pubtostr(CladiriPublice tip) {
    switch (tip) {
        case CladiriPublice::SCOALA: return "Scoala";
        case CladiriPublice::UNIVERSITATE: return "Universitate";
        case CladiriPublice::SPITAL: return "Spital";
        case CladiriPublice::POLITIE: return "Politie";
        case CladiriPublice::POMPIERI: return "Pompieri";
        case CladiriPublice::SPATIU_COMERCIAL: return "Spatiu Comercial";
        case CladiriPublice::CLADIRE_BIROURI: return "Cladire Birouri";
        case CladiriPublice::PARC: return "Parc";
        case CladiriPublice::BISERICA: return "Biserica";
        case CladiriPublice::FABRICA: return "Fabrica";
        default: return "Necunoscut";
    }
}



CladirePublica::CladirePublica(int id, std::string  n, int cost_c, int cost_i, CladiriPublice tip_, int capacitate, bool inchiriat_): ID(id), nume(std::move(n)), cost_construire(cost_c), cost_intretinere(cost_i),
                                                                                                                tip(tip_), capacitate_servicii(capacitate), inchiriat(inchiriat_) {}

CladirePublica::CladirePublica(const CladirePublica &other) = default;

CladirePublica& CladirePublica:: operator=(const CladirePublica& other) {
    if (this != &other) {
        ID = other.ID;
        nume = other.nume;
        cost_construire = other.cost_construire;
        cost_intretinere = other.cost_intretinere;
        tip = other.tip;
        capacitate_servicii = other.capacitate_servicii;
        inchiriat = other.inchiriat;
    }
    return *this;
}

CladirePublica::~CladirePublica() = default;

int CladirePublica::get_ID() const { return ID; }
double CladirePublica::get_cost_intretinere() const { return cost_intretinere; }
const std::string& CladirePublica::get_nume() const { return nume; }
CladiriPublice CladirePublica::get_tip() const { return tip; }
int CladirePublica::get_capacitate() const { return capacitate_servicii; }
bool CladirePublica::get_inchiriat() const { return inchiriat; }

std::ostream& operator<<(std::ostream& os, const CladirePublica& cp) {
    os << " Cladire Publica: " << cp.nume << " (Tip: " << pubtostr(cp.tip) <<")\n";
    os << " Cost C/I: " << cp.cost_construire << "/" << cp.cost_intretinere << " RON \n";
    os << " Detalii: " << cp.capacitate_servicii << ", iar cladirea " << (cp.inchiriat ? "este" : "nu este") << " inchiriata de primarie" <<"\n";
    return os;
}
