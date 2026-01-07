//
// Created by flint on 1/5/2026.
//

#ifndef OOP_SPATIUVERDE_H
#define OOP_SPATIUVERDE_H

#include "CladirePublica.h"

class SpatiuVerde : public CladirePublica {
private:
    double suprafata_mp{};
    double nivel_mentenanta{};

public:
    explicit SpatiuVerde(int id = 0,
                         std::string nume_ = "",
                         double cost_c = 0.0,
                         double cost_i = 0.0,
                         int capacitate = 0,
                         bool inchiriat_ = false,
                         double suprafata = 0.0,
                         double mentenanta = 0.0);

    void set_suprafata_mp(double x);
    void set_nivel_mentenanta(double x);

    [[nodiscard]] double incasari() const override;
    [[nodiscard]] double impact_fericire(Amanunte actiune) const override;

    void print(std::ostream& os) const override;

    [[nodiscard]] std::unique_ptr<CladirePublica> clone() const override;
};

#endif //OOP_SPATIUVERDE_H