//
// Created by flint on 1/5/2026.
//

#include "../Headers/SpatiuVerde.h"
#include "../Headers/ExceptieOras.h"
#include "Clamp.h"

#include <ostream>


SpatiuVerde::SpatiuVerde(const int id,
                         std::string nume_,
                         const double cost_c,
                         const double cost_i,
                         const int capacitate,
                         const bool inchiriat_,
                         const double suprafata,
                         const double mentenanta)
    : CladirePublica(id, std::move(nume_), cost_c, cost_i, capacitate, inchiriat_),
      suprafata_mp(suprafata),
      nivel_mentenanta(mentenanta) {

    if (suprafata_mp < 0.0) throw ExceptieDateInvalide("SpatiuVerde: suprafata negativa");
    if (nivel_mentenanta < 0.0 || nivel_mentenanta > 1.0) throw ExceptieDateInvalide("SpatiuVerde: mentenanta in afara [0,1]");
}

double SpatiuVerde::incasari() const {
    return -get_cost_intretinere();
}

double SpatiuVerde::impact_fericire(const Amanunte actiune) const {
    const double area = clamp01(suprafata_mp / 5000.0);
    const double ment = clamp01(nivel_mentenanta);
    const double cap = clamp01(static_cast<double>(get_capacitate()) / 1000.0);

    double score = 0.0;
    score += area * 0.55;
    score += ment * 0.35;
    score += cap * 0.10;

    if (actiune == Amanunte::DE_LA_ZERO)   return +0.050 * score;
    return -0.060 * (0.6 + 0.4 * score);
}

void SpatiuVerde::print(std::ostream& os) const {
    CladirePublica::print(os);
    os << ", suprafata_mp=" << suprafata_mp
       << ", mentenanta=" << nivel_mentenanta;
}

std::unique_ptr<CladirePublica> SpatiuVerde::clone() const {
    return std::make_unique<SpatiuVerde>(*this);
}
