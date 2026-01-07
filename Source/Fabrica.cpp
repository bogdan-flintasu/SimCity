//
// Created by flint on 1/7/2026.
//

#include "../Headers/Fabrica.h"
#include "../Headers/Clamp.h"

#include <utility>

Fabrica::Fabrica(const int id,
                 std::string nume_,
                 const double cost_c,
                 const double cost_i,
                 const int capacitate,
                 const bool inchiriat_,
                 const double infrastructura_,
                 const double productie_lunara_,
                 const double automatizare_,
                 const double siguranta_)
    : CladireEconomie(id, std::move(nume_), cost_c, cost_i, capacitate, inchiriat_, infrastructura_),
      productie_lunara(productie_lunara_ < 0 ? 0.0 : productie_lunara_),
      automatizare(clamp01(automatizare_)),
      siguranta(clamp01(siguranta_)) {}

void Fabrica::set_productie_lunara(const double v) { productie_lunara = (v < 0 ? 0.0 : v); }
void Fabrica::set_automatizare(const double v) { automatizare = clamp01(v); }

double Fabrica::incasari() const {
    const double baza = CladireEconomie::incasari();

    const double prod = clamp01(productie_lunara / 60000.0);
    const double cap  = clamp01(static_cast<double>(get_capacitate()) / 2500.0);

    double score = 0.0;
    score += 0.40 * prod;
    score += 0.25 * automatizare;
    score += 0.15 * siguranta;
    score += 0.20 * cap;

    return baza + 700.0 + 3200.0 * score;
}

double Fabrica::impact_fericire(const Amanunte actiune) const {
    const double prod = clamp01(productie_lunara / 60000.0);
    const double cap  = clamp01(static_cast<double>(get_capacitate()) / 2500.0);

    double score = 0.0;
    score += 0.35 * prod;
    score += 0.25 * automatizare;
    score += 0.25 * siguranta;
    score += 0.15 * cap;

    if (actiune == Amanunte::DE_LA_ZERO)   return +0.030 * score;
    if (actiune == Amanunte::IMBUNATATIRE) return +0.015 * score;
    return -0.070 * (0.6 + 0.4 * score);
}

void Fabrica::print(std::ostream& os) const {
    CladireEconomie::print(os);
    os << " | productie_lunara=" << productie_lunara
       << " | automatizare=" << automatizare
       << " | siguranta=" << siguranta;
}

std::unique_ptr<CladirePublica> Fabrica::clone() const {
    return std::make_unique<Fabrica>(*this);
}
