//
// Created by flint on 1/5/2026.
//

#ifndef OOP_CLADIREEDUCATIE_H
#define OOP_CLADIREEDUCATIE_H

#include <vector>

#include "CladirePublica.h"

class CladireEducatie : public CladirePublica {
private:
    std::vector<Salariat> salariati;
    int nivel_educatie{};
    double rata_promovare{};
    double medie_promovare_unitate{};
    double rata_absenta{};
    double rating_elevi{};

public:
    explicit CladireEducatie(int id = 0,
                             std::string nume_ = "",
                             double cost_c = 0.0,
                             double cost_i = 0.0,
                             int capacitate = 0,
                             bool inchiriat_ = false,
                             int nivel = 1,
                             double promovare = 0.0,
                             double medie_promovare = 0.0,
                             double abs = 0.0,
                             double rating = 0.0);

    void adauga_salariat(const Salariat& s);

    [[nodiscard]] int get_nr_salariati() const;
    [[nodiscard]] double eficienta_cladire() const;

    void set_nivel_educatie(int x);
    void set_rata_promovare(double x);
    void set_absente(double x);

    [[nodiscard]] double incasari() const override;
    [[nodiscard]] double impact_fericire(Amanunte actiune) const override;

    void print(std::ostream& os) const override;

    [[nodiscard]] std::unique_ptr<CladirePublica> clone() const override;
};

#endif //OOP_CLADIREEDUCATIE_H