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
                  int etaje = 0);

    [[nodiscard]] int get_nr_apartamente() const;
    [[nodiscard]] int get_nr_apartamente_ocupate() const;
    [[nodiscard]] double get_mp_total_apartamente(bool doar_ocupate = false) const;
    [[nodiscard]] int get_locatari_total() const;

    void adauga_apartament(const Apartament& ap);
    void seteaza_vacant(int id_ap, bool vacant);
    void seteaza_locatari(int id_ap, int locatari);

    [[nodiscard]] double impact_fericire(Amanunte actiune) const override;
    [[nodiscard]] double incasari_lunare() const override;

    void calculeaza_cost_intretinere(double cost_fix_bloc,
                                     double cost_pe_apartament,
                                     double cost_pe_mp,
                                     bool doar_ocupate = false);

    [[nodiscard]] std::unique_ptr<CladireRezidentiala> clone() const override;
};

#endif //OOP_BLOC_H