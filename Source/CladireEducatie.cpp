//
// Created by flint on 1/5/2026.
//

#include "../Headers/CladireEducatie.h"
#include "../Headers/ExceptieOras.h"
#include "Clamp.h"


CladireEducatie::CladireEducatie(const int id,
                                 std::string nume_,
                                 const double cost_c,
                                 const double cost_i,
                                 const int capacitate,
                                 const bool inchiriat_,
                                 const int nivel,
                                 const double promovare,
                                 const double medie_promovare,
                                 const double abs,
                                 const double rating)
    : CladirePublica(id, std::move(nume_), cost_c, cost_i, capacitate, inchiriat_),
      nivel_educatie(nivel),
      rata_promovare(promovare),
      medie_promovare_unitate(medie_promovare),
      rata_absenta(abs),
      rating_elevi(rating) {

    if (nivel_educatie < 0) throw ExceptieDateInvalide("CladireEducatie: nivel negativ");
    if (rata_promovare < 0.0 || rata_promovare > 1.0) throw ExceptieDateInvalide("CladireEducatie: promovare in afara [0,1]");
    if (rata_absenta < 0.0 || rata_absenta > 1.0) throw ExceptieDateInvalide("CladireEducatie: absenta in afara [0,1]");
    if (rating_elevi < 0.0) throw ExceptieDateInvalide("CladireEducatie: rating negativ");
}

void CladireEducatie::adauga_salariat(const Salariat& s) {
    salariati.push_back(s);
    cost_intretinere += s.salariu;
}

int CladireEducatie::get_nr_salariati() const {
    return static_cast<int>(salariati.size());
}

double CladireEducatie::eficienta_cladire() const {
    if (salariati.empty()) return 0.0;
    double suma = 0.0;
    for (const auto& s : salariati) suma += s.eficienta;
    return suma / static_cast<double>(salariati.size());
}

void CladireEducatie::set_nivel_educatie(const int x) { nivel_educatie = (x < 0 ? 0 : x); }

void CladireEducatie::set_rata_promovare(const double x) {
    if (x < 0.0) rata_promovare = 0.0;
    else if (x > 1.0) rata_promovare = 1.0;
    else rata_promovare = x;
}

void CladireEducatie::set_absente(const double x) {
    if (x < 0.0) rata_absenta = 0.0;
    else if (x > 1.0) rata_absenta = 1.0;
    else rata_absenta = x;
}

double CladireEducatie::incasari() const {
    return 0.0;
}

double CladireEducatie::impact_fericire(const Amanunte actiune) const {
    const double lvl = clamp01(static_cast<double>(nivel_educatie) / 5.0);
    const double prom = clamp01(rata_promovare);
    const double absn = clamp01(1.0 - rata_absenta);
    const double eff = clamp01(eficienta_cladire() / 100.0);
    const double rating = clamp01(rating_elevi / 10.0);

    double score = 0.0;
    score += lvl * 0.15;
    score += prom * 0.35;
    score += absn * 0.20;
    score += eff * 0.15;
    score += rating * 0.15;

    if (actiune == Amanunte::DE_LA_ZERO)   return +0.030 * score;
    if (actiune == Amanunte::IMBUNATATIRE) return +0.018 * score;
    return -0.028 * (0.6 + 0.4 * score);
}

void CladireEducatie::print(std::ostream& os) const {
    CladirePublica::print(os);
    os << ", salariati=" << salariati.size()
       << ", eficienta_medie=" << eficienta_cladire()
       << ", nivel_educatie=" << nivel_educatie
       << ", rata_promovare=" << rata_promovare
       << ", medie_promovare_unitate=" << medie_promovare_unitate
       << ", absenteism=" << rata_absenta
       << ", rating=" << rating_elevi;
}

std::unique_ptr<CladirePublica> CladireEducatie::clone() const {
    return std::make_unique<CladireEducatie>(*this);
}
