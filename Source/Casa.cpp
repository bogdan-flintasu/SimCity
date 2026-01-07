//
// Created by flint on 1/5/2026.
//

#include "../Headers/Casa.h"
#include "Clamp.h"


#include <algorithm>
#include <ostream>


Casa::Casa(const int id,
           std::string nume_,
           const double cost_c,
           const double suprafata,
           const int etaje,
           const int locatari)
    : CladireRezidentiala(id, std::move(nume_), cost_c, 0.0, suprafata, etaje, locatari),
      ocupata(locatari > 0) {}


void Casa::seteaza_locatari(const int locatari) {
    numar_locuitori = (locatari < 0 ? 0 : locatari);
    ocupata = (numar_locuitori > 0);
}

void Casa::calculeaza_cost_intretinere(const double cost_fix_casa,
                                       const double cost_pe_mp,
                                       const double cost_pe_locatar) {
    cost_intretinere =
        cost_fix_casa +
        cost_pe_mp * suprafata_utila +
        cost_pe_locatar * numar_locuitori;
}

double Casa::impact_fericire(const Amanunte actiune) const {
    const double mp = suprafata_utila;
    const int loc = numar_locuitori;

    const double mp_per_loc = (loc == 0) ? mp : (mp / static_cast<double>(loc));

    double score = 0.0;

    score += clamp01(mp_per_loc / 40.0) * 0.65;
    score += clamp01(static_cast<double>(numar_etaje) / 2.0) * 0.10;

    if (ocupata) score += 0.25;
    else score += 0.05;

    if (actiune == Amanunte::DE_LA_ZERO)   return +0.03 * score;
    if (actiune == Amanunte::IMBUNATATIRE) return +0.015 * score;

    return -0.04 * (0.7 + 0.3 * score);
}

double Casa::incasari_lunare() const {
    return static_cast<double>(get_numar_locuitori()) * 15.0;
}

std::unique_ptr<CladireRezidentiala> Casa::clone() const {
    return std::make_unique<Casa>(*this);
}

void Casa::print(std::ostream& os) const {
    CladireRezidentiala::print(os);
    os << ", ocupata=" << (ocupata ? "da" : "nu");
}
