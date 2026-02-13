//
// Created by flint on 1/5/2026.
//

#include "../Headers/CladireServicii.h"
#include "../Headers/ExceptieOras.h"
#include "Clamp.h"

#include <ostream>



CladireServicii::CladireServicii(const int id,
                                 std::string nume_,
                                 const double cost_c,
                                 const double cost_i,
                                 const int capacitate,
                                 const bool inchiriat_,
                                 const int nivel_sec,
                                 const double timp,
                                 const double coruptie,
                                 const double dotare_,
                                 const double timp_asteptare_,
                                 const double stoc_curent_,
                                 const double rata_rezolvare_)
    : CladireAdministrativa(id, std::move(nume_), cost_c, cost_i, capacitate, inchiriat_,
                            nivel_sec, timp, coruptie),
      dotare(dotare_),
      timp_asteptare(timp_asteptare_),
      stoc_curent(stoc_curent_),
      rata_rezolvare_cazuri(rata_rezolvare_) {

    if (dotare < 0.0) throw ExceptieDateInvalide("CladireServicii: dotare negativa");
    if (timp_asteptare < 0.0) throw ExceptieDateInvalide("CladireServicii: timp_asteptare negativ");
    if (stoc_curent < 0.0) throw ExceptieDateInvalide("CladireServicii: stoc negativ");
    if (rata_rezolvare_cazuri < 0.0 || rata_rezolvare_cazuri > 1.0) throw ExceptieDateInvalide("CladireServicii: rata_rezolvare in afara [0,1]");
}

void CladireServicii::set_dotare(const double x) { dotare = (x < 0.0 ? 0.0 : x); }
void CladireServicii::set_timp_asteptare(const double x) { timp_asteptare = (x < 0.0 ? 0.0 : x); }
void CladireServicii::set_stoc_curent(const double x) { stoc_curent = (x < 0.0 ? 0.0 : x); }
void CladireServicii::set_rata_rezolvare_cazuri(const double x) {
    if (x < 0.0) rata_rezolvare_cazuri = 0.0;
    else if (x > 1.0) rata_rezolvare_cazuri = 1.0;
    else rata_rezolvare_cazuri = x;
}

double CladireServicii::incasari() const {
    return 0.0;
}

double CladireServicii::impact_fericire(const Amanunte actiune) const {
    const double base_admin = CladireAdministrativa::impact_fericire(actiune);

    const double equip = clamp01(dotare / 100.0);
    const double wait = clamp01(1.0 - (timp_asteptare / 60.0));
    const double stock = clamp01(stoc_curent / 100.0);
    const double solve = clamp01(rata_rezolvare_cazuri);

    double score = 0.0;
    score += equip * 0.30;
    score += wait * 0.25;
    score += stock * 0.15;
    score += solve * 0.30;

    double extra = 0.0;
    if (actiune == Amanunte::DE_LA_ZERO)   extra = +0.035 * score;
    else extra = -0.045 * (0.6 + 0.4 * score);

    return base_admin + extra;
}

void CladireServicii::print(std::ostream& os) const {
    CladireAdministrativa::print(os);
    os << ", dotare=" << dotare
       << ", timp_asteptare=" << timp_asteptare
       << ", stoc_curent=" << stoc_curent
       << ", rata_rezolvare=" << rata_rezolvare_cazuri;
}

std::unique_ptr<CladirePublica> CladireServicii::clone() const {
    return std::make_unique<CladireServicii>(*this);
}
