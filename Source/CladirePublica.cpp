//
// Created by flint on 12/21/2025.
//

#include <iostream>

#include <../Headers/CladirePublica.h>
#include "../Headers/ExceptieOras.h"

int CladirePublica::next_id = 1;

int CladirePublica::gen_id() {
    return next_id++;
}


CladirePublica::CladirePublica(const int id, std::string  n, const double cost_c, const double cost_i, const int capacitate, const bool inchiriat_): ID(id == 0 ? gen_id() : id), nume(std::move(n)), cost_construire(cost_c), cost_intretinere(cost_i),
                                                                                                                capacitate_servicii(capacitate), inchiriat(inchiriat_) {
    if (ID < 0) throw ExceptieDateInvalide("CladirePublica: ID negativ");
    if (cost_construire < 0.0) throw ExceptieDateInvalide("CladirePublica: cost_construire negativ");
    if (cost_intretinere < 0.0) throw ExceptieDateInvalide("CladirePublica: cost_intretinere negativ");
    if (capacitate_servicii < 0) throw ExceptieDateInvalide("CladirePublica: capacitate negativa");

    if (id > 0 && id >= next_id) next_id = id + 1;
}


CladirePublica::CladirePublica(const CladirePublica &other) = default;

CladirePublica& CladirePublica:: operator=(const CladirePublica& other) {
    if (this != &other) {
        ID = other.ID;
        nume = other.nume;
        cost_construire = other.cost_construire;
        cost_intretinere = other.cost_intretinere;
        capacitate_servicii = other.capacitate_servicii;
        inchiriat = other.inchiriat;
    }
    return *this;
}

CladirePublica::~CladirePublica() = default;

int CladirePublica::get_ID() const { return ID; }
double CladirePublica::get_cost_intretinere() const { return cost_intretinere; }
const std::string& CladirePublica::get_nume() const { return nume; }
int CladirePublica::get_capacitate() const { return capacitate_servicii; }
bool CladirePublica::get_inchiriat() const { return inchiriat; }

void CladirePublica::print(std::ostream& os) const {
    os << "ID=" << ID
       << ", nume=" << nume
       << ", capacitate=" << capacitate_servicii
       << ", cost_intretinere=" << cost_intretinere;
}

std::ostream& operator<<(std::ostream& os, const CladirePublica& cp) {
    cp.print(os);
    return os;
}