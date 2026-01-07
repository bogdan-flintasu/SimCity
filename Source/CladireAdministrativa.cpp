//
// Created by flint on 1/5/2026.
//

#include "../Headers/CladireAdministrativa.h"
#include "../Headers/ExceptieOras.h"
#include "Clamp.h"


#include <algorithm>
#include <memory>

CladireAdministrativa::CladireAdministrativa(const int id,
                                             std::string nume_,
                                             const double cost_c,
                                             const double cost_i,
                                             const int capacitate,
                                             const bool inchiriat_,
                                             const int nivel_sec,
                                             const double timp,
                                             const double coruptie)
    : CladirePublica(id, std::move(nume_), cost_c, cost_i, capacitate, inchiriat_),
      nivel_securitate(nivel_sec),
      timp_raspuns(timp),
      nivel_coruptie(coruptie) {

    if (nivel_securitate < 0) throw ExceptieDateInvalide("CladireAdministrativa: nivel_securitate negativ");
    if (timp_raspuns < 0.0) throw ExceptieDateInvalide("CladireAdministrativa: timp_raspuns negativ");
    if (nivel_coruptie < 0.0 || nivel_coruptie > 1.0) throw ExceptieDateInvalide("CladireAdministrativa: coruptie in afara [0,1]");
}

void CladireAdministrativa::adauga_salariat(const Salariat& s) {
    salariati.push_back(s);
    cost_intretinere += s.salariu;
}

int CladireAdministrativa::get_nr_salariati() const {
    return static_cast<int>(salariati.size());
}

double CladireAdministrativa::eficienta_cladire() const {
    if (salariati.empty()) return 0.0;
    double s = 0.0;
    for (const auto& sal : salariati) s += sal.eficienta;
    return s / static_cast<double>(salariati.size());
}

int CladireAdministrativa::get_nivel_securitate() const { return nivel_securitate; }
double CladireAdministrativa::get_timp_raspuns() const { return timp_raspuns; }
double CladireAdministrativa::get_nivel_coruptie() const { return nivel_coruptie; }

void CladireAdministrativa::set_nivel_coruptie(const double x) {
    if (x < 0.0) nivel_coruptie = 0.0;
    else if (x > 1.0) nivel_coruptie = 1.0;
    else nivel_coruptie = x;
}

double CladireAdministrativa::incasari() const {
    return 0.0;
}

double CladireAdministrativa::impact_fericire(const Amanunte actiune) const {
    const double eff = clamp01(eficienta_cladire() / 100.0);
    const double sec = clamp01(static_cast<double>(nivel_securitate) / 10.0);
    const double resp = clamp01(1.0 - (timp_raspuns / 30.0));
    const double corrupt = clamp01(1.0 - nivel_coruptie);
    const double staff = clamp01(static_cast<double>(get_nr_salariati()) / 40.0);

    double score = 0.0;
    score += eff * 0.30;
    score += sec * 0.20;
    score += resp * 0.20;
    score += corrupt * 0.20;
    score += staff * 0.10;

    if (actiune == Amanunte::DE_LA_ZERO)   return +0.020 * score;
    if (actiune == Amanunte::IMBUNATATIRE) return +0.012 * score;
    return -0.018 * (0.6 + 0.4 * score);
}

void CladireAdministrativa::print(std::ostream& os) const {
    CladirePublica::print(os);
    os << ", salariati=" << salariati.size()
       << ", eficienta_medie=" << eficienta_cladire()
       << ", nivel_securitate=" << nivel_securitate
       << ", timp_raspuns=" << timp_raspuns
       << ", coruptie=" << nivel_coruptie;
}

std::unique_ptr<CladirePublica> CladireAdministrativa::clone() const {
    return std::make_unique<CladireAdministrativa>(*this);
}
