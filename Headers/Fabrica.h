//
// Created by flint on 1/7/2026.
//

#ifndef OOP_FABRICA_H
#define OOP_FABRICA_H

#include "CladireEconomie.h"
#include <memory>
#include <string>

class Fabrica : public CladireEconomie {
private:
    double productie_lunara{0.0};
    double automatizare{0.5};
    double siguranta{0.5};

public:
    explicit Fabrica(int id = 0,
                     std::string nume_ = "",
                     double cost_c = 0.0,
                     double cost_i = 0.0,
                     int capacitate = 0,
                     bool inchiriat_ = false,
                     double infrastructura_ = 0.5,
                     double productie_lunara_ = 0.0,
                     double automatizare_ = 0.5,
                     double siguranta_ = 0.5);

    void set_automatizare(double v);

    [[nodiscard]] double incasari() const override;
    [[nodiscard]] double impact_fericire(Amanunte actiune) const override;

    void print(std::ostream& os) const override;
    [[nodiscard]] std::unique_ptr<CladirePublica> clone() const override;
};

#endif // OOP_FABRICA_H
