//
// Created by flint on 10/28/2025.
//

#include <string>
#include <iostream>

#include "../Headers/Proiect.h"

Proiect::Proiect(std::string  nume, Proiecte tip_, Amanunte det, int cost, int tinta): nume_proiect(std::move(nume)), tip(tip_), detalii(det), cost_estimat(cost), id_tinta(tinta) {}

Proiect::Proiect(const Proiect &other) = default;

Proiect& Proiect::operator=(const Proiect &other) {
    if (this != &other) {
        nume_proiect = other.nume_proiect;
        tip = other.tip;
        detalii = other.detalii;
        cost_estimat = other.cost_estimat;
        id_tinta = other.id_tinta;
    }
    return *this;
}

Proiect::~Proiect() = default;

const std::string& Proiect::get_nume() const { return nume_proiect; }
Proiecte Proiect::get_tip() const { return tip; }
Amanunte Proiect::get_detalii() const { return detalii; }
double Proiect::get_cost_estimat() const { return cost_estimat; }

std::ostream& operator<<(std::ostream& os, const Proiect& p) {
    os << " Proiect: " << p.nume_proiect << "( Cost estimat: " << p.cost_estimat << " RON )\n";
    os << " Detalii: " << "proiectul este destinat " << prtostr(p.tip) << ",iar acesta este de tipul "<< amtostr(p.detalii) <<"\n";
    return os;
}
