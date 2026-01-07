//
// Created by flint on 1/7/2026.
//

#ifndef OOP_SPATIUCOMERCIAL_H
#define OOP_SPATIUCOMERCIAL_H

#include "CladireEconomie.h"
#include <memory>
#include <string>

class SpatiuComercial : public CladireEconomie {
private:
    int unitati{0};
    double trafic_zilnic{0.0};
    int locuri_parcare{0};
    double nivel_servicii{0.5};

    [[nodiscard]] double eficienta_trafic() const;

public:
    explicit SpatiuComercial(int id = 0,
                             std::string nume_ = "",
                             double cost_c = 0.0,
                             double cost_i = 0.0,
                             int capacitate = 0,
                             bool inchiriat_ = false,
                             double infrastructura_ = 0.5,
                             int unitati_ = 0,
                             double trafic_zilnic_ = 0.0,
                             int locuri_parcare_ = 0,
                             double nivel_servicii_ = 0.5);

    [[nodiscard]] int get_unitati() const;
    [[nodiscard]] double get_trafic_zilnic() const;
    [[nodiscard]] int get_locuri_parcare() const;
    [[nodiscard]] double get_nivel_servicii() const;

    void set_unitati(int v);
    void set_trafic_zilnic(double v);
    void set_locuri_parcare(int v);
    void set_nivel_servicii(double v);

    [[nodiscard]] double incasari() const override;
    [[nodiscard]] double impact_fericire(Amanunte actiune) const override;

    void print(std::ostream& os) const override;
    [[nodiscard]] std::unique_ptr<CladirePublica> clone() const override;
};

#endif // OOP_SPATIUCOMERCIAL_H
