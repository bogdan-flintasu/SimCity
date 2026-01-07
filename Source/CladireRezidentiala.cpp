//
// Created by flint on 12/21/2025.
//
#include <iostream>
#include "../Headers/CladireRezidentiala.h"
#include "../Headers/ExceptieOras.h"


int CladireRezidentiala::next_id = 1;

int CladireRezidentiala::gen_id() {
    return next_id++;
}

void CladireRezidentiala::reset_id(int start) { next_id = start; }


CladireRezidentiala::CladireRezidentiala(const int id, std::string nume_, const double cost_c, const double cost_i, const double suprafata, const int etaje, const int locatari) : ID(id == 0 ? gen_id() : id), nume(std::move(nume_)), cost_construire(cost_c),
                                                                                                                                                    cost_intretinere(cost_i), suprafata_utila(suprafata),
                                                                                                                                                    numar_etaje(etaje), numar_locuitori(locatari) {
    if (ID < 0) throw ExceptieDateInvalide("CladireRezidentiala: ID negativ");
    if (cost_construire < 0.0) throw ExceptieDateInvalide("CladireRezidentiala: cost_construire negativ");
    if (cost_intretinere < 0.0) throw ExceptieDateInvalide("CladireRezidentiala: cost_intretinere negativ");
    if (suprafata_utila < 0.0) throw ExceptieDateInvalide("CladireRezidentiala: suprafata negativa");
    if (numar_etaje < 0) throw ExceptieDateInvalide("CladireRezidentiala: etaje negative");
    if (numar_locuitori < 0) throw ExceptieDateInvalide("CladireRezidentiala: locatari negativi");

    if (id > 0 && id >= next_id) next_id = id + 1;
}

CladireRezidentiala::CladireRezidentiala(const CladireRezidentiala &other): ID(other.ID),
      nume(other.nume),
      cost_construire(other.cost_construire),
      cost_intretinere(other.cost_intretinere),
      suprafata_utila(other.suprafata_utila),
      numar_etaje(other.numar_etaje),
      numar_locuitori(other.numar_locuitori) {
}

CladireRezidentiala& CladireRezidentiala:: operator=(const CladireRezidentiala& other) {
    if (this != &other) {
        ID = other.ID;
        nume = other.nume;
        cost_construire = other.cost_construire;
        cost_intretinere = other.cost_intretinere;
        suprafata_utila = other.suprafata_utila;
        numar_etaje = other.numar_etaje;
        numar_locuitori = other.numar_locuitori;
    }
    return *this;
}

CladireRezidentiala::~CladireRezidentiala() {}

int CladireRezidentiala::get_ID() const { return ID; }
double CladireRezidentiala::get_cost_intretinere() const { return cost_intretinere; }
const std::string& CladireRezidentiala::get_nume() const { return nume; }
int CladireRezidentiala::get_numar_locuitori() const { return numar_locuitori; }

void CladireRezidentiala::print(std::ostream &os) const {
    os << "ID=" << ID
           << ", nume=" << nume
           << ", suprafata=" << suprafata_utila
           << ", locuitori=" << numar_locuitori
           << ", cost_intretinere=" << cost_intretinere;
}

std::ostream& operator<<(std::ostream& os, const CladireRezidentiala& cr) {
    cr.print(os);
    return os;
}