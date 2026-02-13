//
// Created by flint on 1/5/2026.
//

#include "../Headers/Bloc.h"
#include "Clamp.h"

Bloc::Bloc(const int id, std::string nume_, const double cost_c, const double suprafata, const int etaje)
    : CladireRezidentiala(id, std::move(nume_), cost_c, 0.0, suprafata, etaje, 0) {}

int Bloc::get_nr_apartamente() const {
    return static_cast<int>(apartamente.size());
}

int Bloc::get_nr_apartamente_ocupate() const {
    int cnt = 0;
    for (const auto& ap : apartamente)
        if (!ap.este_vacant()) cnt++;
    return cnt;
}

double Bloc::get_mp_total_apartamente(const bool doar_ocupate) const {
    double s = 0.0;
    for (const auto& ap : apartamente) {
        if (doar_ocupate && ap.este_vacant()) continue;
        s += ap.get_mp_total();
    }
    return s;
}

int Bloc::get_numar_locuitori() const {
    int s = 0;
    for (const auto& ap : apartamente)
        s += ap.get_locatari();
    return s;
}

void Bloc::adauga_apartament(const Apartament& ap) {
    apartamente.push_back(ap);
}

void Bloc::seteaza_vacant(const int id_ap, const bool vacant) {
    for (auto& ap : apartamente) {
        if (ap.get_id() == id_ap) {
            ap.seteaza_vacant(vacant);
            break;
        }
    }
}

void Bloc::seteaza_locatari(const int id_ap, const int locatari) {
    for (auto& ap : apartamente) {
        if (ap.get_id() == id_ap) {
            ap.seteaza_locatari(locatari);
            break;
        }
    }
}

double Bloc::impact_fericire(const Amanunte actiune) const {
    const int total = get_nr_apartamente();
    const int ocupate = get_nr_apartamente_ocupate();
    const double occ = (total == 0) ? 0.0 : static_cast<double>(ocupate) / static_cast<double>(total);

    const double mp = get_mp_total_apartamente(false);
    const int loc = get_numar_locuitori();
    const double mp_per_loc = (loc == 0) ? 0.0 : mp / static_cast<double>(loc);

    double score = 0.0;
    score += clamp01(occ) * 0.55;
    score += clamp01(mp_per_loc / 35.0) * 0.35;
    score += 0.10;

    if (actiune == Amanunte::DE_LA_ZERO)   return +0.035 * score;
    return -0.05 * (0.6 + 0.4 * score);
}

double Bloc::incasari_lunare() const {
    return static_cast<double>(get_numar_locuitori()) * 10.0;
}

void Bloc::calculeaza_cost_intretinere(const double cost_fix_bloc,
                                       const double cost_pe_apartament,
                                       const double cost_pe_mp,
                                       const bool doar_ocupate) {
    const int nr_ap = doar_ocupate ? get_nr_apartamente_ocupate()
                                   : get_nr_apartamente();
    const double mp = get_mp_total_apartamente(doar_ocupate);

    cost_intretinere =
        cost_fix_bloc +
        cost_pe_apartament * nr_ap +
        cost_pe_mp * mp;
}

std::unique_ptr<CladireRezidentiala> Bloc::clone() const {
    return std::make_unique<Bloc>(*this);
}
