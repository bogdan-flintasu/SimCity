//
// Created by flint on 1/5/2026.
//

#ifndef OOP_CLADIREECONOMIE_H
#define OOP_CLADIREECONOMIE_H

#include "CladirePublica.h"
#include <memory>
#include <string>

class CladireEconomie : public CladirePublica {
protected:
    double infrastructura{0.5};

public:
    explicit CladireEconomie(int id = 0,
                             std::string nume_ = "",
                             double cost_c = 0.0,
                             double cost_i = 0.0,
                             int capacitate = 0,
                             bool inchiriat_ = false,
                             double infrastructura_ = 0.5);

    [[nodiscard]] double get_infrastructura() const;
    void set_infrastructura(double v);

    [[nodiscard]] double incasari() const override;
    [[nodiscard]] double impact_fericire(Amanunte actiune) const override;

    void print(std::ostream& os) const override;
    [[nodiscard]] std::unique_ptr<CladirePublica> clone() const override;
};

#endif // OOP_CLADIREECONOMIE_H
