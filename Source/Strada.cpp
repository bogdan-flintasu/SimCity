//
// Created by flint on 10/28/2025.
//

#include <iostream>

#include "../Headers/Strada.h"

int Strada::next_id = 1;

int Strada::gen_id() {
    return next_id++;
}

void Strada::reset_id(int start) {
    next_id = start;
}

Strada::Strada(int id, std::string  nume_, double cost_c, double cost_i, bool trot, bool unic, int nr_benzi, double lung) : ID(id == 0 ? gen_id() : id), nume(std::move(nume_)), cost_construire(cost_c), cost_intretinere(cost_i),
                                                                                                            trotuar(trot), sens_unic(unic), numar_benzi(nr_benzi), lungime(lung) {std::cout << "[DEBUG STRADA] S-a creat obiectul '" << nume << "' cu ID final: " << this->ID << "\n";}

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

void Strada::set_numar_benzi(const int n) {
    numar_benzi = n;
}

void Strada::set_ID(const int id_nou) {
    this->ID = id_nou;
}


std::ostream& operator<<(std::ostream& os, const Strada& s) {
    os << " Strada" << s.nume << " (ID: " << s.ID << ")\n";
    os << " Cost C/I: " << s.cost_construire << "/" << s.cost_intretinere << " RON \n";
    os << " Detalii: " << s.lungime << "m, " << s.numar_benzi << " benzi, "<< (s.trotuar ? "Cu trotuar" : "Fara trotuar") << ", "<< (s.sens_unic ? "Sens unic" : "Sens dublu");
    return os;
}