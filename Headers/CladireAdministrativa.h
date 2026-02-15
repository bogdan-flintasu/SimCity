//
// Created by flint on 1/5/2026.
//

#ifndef OOP_CLADIREADMINISTRATIVA_H
#define OOP_CLADIREADMINISTRATIVA_H

#include <vector>

#include "CladirePublica.h"

class CladireAdministrativa : public CladirePublica {
private:
    std::vector<Salariat> salariati;
    int nivel_securitate{};
    double timp_raspuns{};
    double nivel_coruptie{};

public:
    explicit CladireAdministrativa(int id = 0,
                                   std::string nume_ = "",
                                   double cost_c = 0.0,
                                   double cost_i = 0.0,
                                   int capacitate = 0,
                                   bool inchiriat_ = false,
                                   int nivel_sec = 0,
                                   double timp = 0.0,
                                   double coruptie = 0.0);

    [[nodiscard]] int get_nr_salariati() const;
    [[nodiscard]] double eficienta_cladire() const;


    [[nodiscard]] double incasari() const override;
    [[nodiscard]] double impact_fericire(Amanunte actiune) const override;

    void print(std::ostream& os) const override;

    [[nodiscard]] std::unique_ptr<CladirePublica> clone() const override;
};

#endif //OOP_CLADIREADMINISTRATIVA_H