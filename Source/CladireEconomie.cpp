#include "../Headers/CladireEconomie.h"
#include "../Headers/Clamp.h"

#include <utility>
#include <ostream>


CladireEconomie::CladireEconomie(const int id,
                                 std::string nume_,
                                 const double cost_c,
                                 const double cost_i,
                                 const int capacitate,
                                 const bool inchiriat_,
                                 const double infrastructura_)
    : CladirePublica(id, std::move(nume_), cost_c, cost_i, capacitate, inchiriat_),
      infrastructura(clamp01(infrastructura_)) {}


double CladireEconomie::incasari() const {
    const double cap  = clamp01(static_cast<double>(get_capacitate()) / 2000.0);
    const double rent = get_inchiriat() ? 1.0 : 0.4;

    double score = 0.0;
    score += 0.55 * cap;
    score += 0.30 * infrastructura;
    score += 0.15 * rent;

    return 350.0 + 2600.0 * score;
}

double CladireEconomie::impact_fericire(const Amanunte actiune) const {
    const double cap  = clamp01(static_cast<double>(get_capacitate()) / 2000.0);
    const double rent = get_inchiriat() ? 1.0 : 0.35;

    double score = 0.0;
    score += 0.50 * cap;
    score += 0.30 * infrastructura;
    score += 0.20 * rent;

    if (actiune == Amanunte::DE_LA_ZERO)   return +0.050 * score;
    return -0.060 * (0.6 + 0.4 * score);
}

void CladireEconomie::print(std::ostream& os) const {
    CladirePublica::print(os);
    os << " | infrastructura=" << infrastructura;
}

std::unique_ptr<CladirePublica> CladireEconomie::clone() const {
    return std::make_unique<CladireEconomie>(*this);
}
