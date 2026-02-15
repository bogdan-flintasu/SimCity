//
// Created by flint on 1/7/2026.
//

#include "../Headers/SpatiuComercial.h"
#include "../Headers/Clamp.h"

#include <utility>
#include <ostream>


SpatiuComercial::SpatiuComercial(const int id,
                                 std::string nume_,
                                 const double cost_c,
                                 const double cost_i,
                                 const int capacitate,
                                 const bool inchiriat_,
                                 const double infrastructura_,
                                 const int unitati_,
                                 const double trafic_zilnic_,
                                 const int locuri_parcare_,
                                 const double nivel_servicii_)
    : CladireEconomie(id, std::move(nume_), cost_c, cost_i, capacitate, inchiriat_, infrastructura_),
      unitati(unitati_ < 0 ? 0 : unitati_),
      trafic_zilnic(trafic_zilnic_ < 0 ? 0.0 : trafic_zilnic_),
      locuri_parcare(locuri_parcare_ < 0 ? 0 : locuri_parcare_),
      nivel_servicii(clamp01(nivel_servicii_)) {}

double SpatiuComercial::eficienta_trafic() const {
    const double t = trafic_zilnic < 0 ? 0.0 : trafic_zilnic;
    const double p = locuri_parcare < 0 ? 0.0 : static_cast<double>(locuri_parcare);

    const double cerere_parcare = 1.0 + 0.12 * t;
    const double ratio = p / cerere_parcare;

    return clamp01(ratio);
}

double SpatiuComercial::incasari() const {
    const double baza = CladireEconomie::incasari();

    const double traf = clamp01(trafic_zilnic / 14000.0);
    const double un   = clamp01(static_cast<double>(unitati) / 80.0);
    const double eff  = eficienta_trafic();

    double score = 0.0;
    score += 0.30 * traf;
    score += 0.25 * un;
    score += 0.25 * nivel_servicii;
    score += 0.20 * eff;

    return baza + 600.0 + 3000.0 * score;
}

double SpatiuComercial::impact_fericire(const Amanunte actiune) const {
    const double traf = clamp01(trafic_zilnic / 14000.0);
    const double un   = clamp01(static_cast<double>(unitati) / 80.0);
    const double eff  = eficienta_trafic();

    double score = 0.0;
    score += 0.35 * nivel_servicii;
    score += 0.20 * un;
    score += 0.20 * traf;
    score += 0.25 * eff;

    if (actiune == Amanunte::DE_LA_ZERO)   return +0.050 * score;
    return -0.060 * (0.6 + 0.4 * score);
}

void SpatiuComercial::print(std::ostream& os) const {
    CladireEconomie::print(os);
    os << " | unitati=" << unitati
       << " | trafic_zilnic=" << trafic_zilnic
       << " | parcare=" << locuri_parcare
       << " | nivel_servicii=" << nivel_servicii
       << " | eficienta_trafic=" << eficienta_trafic();
}

std::unique_ptr<CladirePublica> SpatiuComercial::clone() const {
    return std::make_unique<SpatiuComercial>(*this);
}
