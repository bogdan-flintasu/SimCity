//
// Created by flint on 1/5/2026.
//

#ifndef OOP_BLOC_H
#define OOP_BLOC_H

#include "CladireRezidentiala.h"
#include "Proiect.h"
#include "Apartament.h"
#include <vector>

class Bloc : public CladireRezidentiala {
private:
    std::vector<Apartament> apartamente;

public:
    explicit Bloc(int id = 0,
                  std::string nume_ = "",
                  double cost_c = 0.0,
                  double suprafata = 0.0,
                  int etaje = 0,
                  int locatari = 0);

    [[nodiscard]] int get_nr_apartamente() const;
    [[nodiscard]] int get_numar_locuitori() const override;

    void adauga_apartament(const Apartament& ap);

    [[nodiscard]] double impact_fericire(Amanunte actiune) const override;
    [[nodiscard]] double incasari_lunare() const override;

    [[maybe_unused]] void calculeaza_cost_intretinere(double cost_fix_bloc,
                                     double cost_pe_apartament,
                                     double cost_pe_mp);

    [[nodiscard]] std::unique_ptr<CladireRezidentiala> clone() const override;
};

#endif //OOP_BLOC_H