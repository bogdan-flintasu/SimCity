//
// Created by flint on 1/5/2026.
//

#include "../Headers/Bloc.h"

#include <random>

#include "Clamp.h"

Bloc::Bloc(const int id, std::string nume_, const double cost_c, const double suprafata, const int etaje, const int locatari)
    : CladireRezidentiala(id, std::move(nume_), cost_c, 0.0, suprafata, etaje, locatari) {
    const int nr_ap = std::max(etaje, static_cast<int>(suprafata / 55.0));

    for (int i = 0; i < nr_ap; ++i) {
        const int tip_camere = (i % 4) + 1;
        adauga_apartament(Apartament(i, tip_camere, 0));
    }

    if (nr_ap > 0 && numar_locuitori > 0) {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(0, nr_ap - 1);

        int distribuiti = 0;
        while (distribuiti < numar_locuitori) {
            const int idx = dis(gen);

            if (apartamente[idx].get_locatari() < 5) {
                const int curent = apartamente[idx].get_locatari();
                apartamente[idx].seteaza_locatari(curent + 1);
                distribuiti++;
            }

            if (distribuiti < numar_locuitori && nr_ap * 5 < numar_locuitori) {
                const int curent = apartamente[idx].get_locatari();
                apartamente[idx].seteaza_locatari(curent + 1);
                distribuiti++;
            }
        }
    }
}

int Bloc::get_nr_apartamente() const {
    return static_cast<int>(apartamente.size());
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

double Bloc::impact_fericire(const Amanunte actiune) const {
    const int total_locatari = get_numar_locuitori();

    const double mp_per_loc = (total_locatari == 0) ? 40.0 : suprafata_utila / static_cast<double>(total_locatari);

    double score = 0.0;
    score += clamp01(mp_per_loc / 35.0) * 0.7;
    score += 0.30;

    if (actiune == Amanunte::DE_LA_ZERO) return +0.035 * score;
    return -0.05 * (0.6 + 0.4 * score);
}

double Bloc::incasari_lunare() const {
    return static_cast<double>(get_numar_locuitori()) * 10.0;
}

void Bloc::calculeaza_cost_intretinere(const double cost_fix_bloc,
                                       const double cost_pe_apartament,
                                       const double cost_pe_mp) {
    const int nr_ap = get_nr_apartamente();

    cost_intretinere =
        cost_fix_bloc +
        cost_pe_apartament * static_cast<double>(nr_ap) +
        cost_pe_mp * suprafata_utila;
}

std::unique_ptr<CladireRezidentiala> Bloc::clone() const {
    return std::make_unique<Bloc>(*this);
}
