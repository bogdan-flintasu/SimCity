//
// Created by flint on 1/5/2026.
//

#ifndef OOP_CASA_H
#define OOP_CASA_H

#include "CladireRezidentiala.h"
#include "Proiect.h"

class Casa : public CladireRezidentiala {
private:
    bool ocupata{true};

public:
    explicit Casa(int id = 0,
                  std::string nume_ = "",
                  double cost_c = 0.0,
                  double suprafata = 0.0,
                  int etaje = 0,
                  int locatari = 0);

    void seteaza_locatari(int locatari);

    void calculeaza_cost_intretinere(double cost_fix_casa,
                                     double cost_pe_mp,
                                     double cost_pe_locatar);

    [[nodiscard]] double impact_fericire(Amanunte actiune) const override;
    [[nodiscard]] double incasari_lunare() const override;
    [[nodiscard]] int get_numar_locuitori() const override;

    [[nodiscard]] std::unique_ptr<CladireRezidentiala> clone() const override;

    void print(std::ostream& os) const override;
};


#endif //OOP_CASA_H