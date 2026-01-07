//
// Created by flint on 1/5/2026.
//

#ifndef OOP_CLADIRESERVICII_H
#define OOP_CLADIRESERVICII_H

#include "CladireAdministrativa.h"

class CladireServicii : public CladireAdministrativa {
private:
    double dotare{};
    double timp_asteptare{};
    double stoc_curent{};
    double rata_rezolvare_cazuri{};

public:
    explicit CladireServicii(int id = 0,
                             std::string nume_ = "",
                             double cost_c = 0.0,
                             double cost_i = 0.0,
                             int capacitate = 0,
                             bool inchiriat_ = false,
                             int nivel_sec = 0,
                             double timp = 0.0,
                             double coruptie = 0.0,
                             double dotare_ = 0.0,
                             double timp_asteptare_ = 0.0,
                             double stoc_curent_ = 0.0,
                             double rata_rezolvare_ = 0.0);



    void set_dotare(double x);
    void set_timp_asteptare(double x);
    void set_stoc_curent(double x);
    void set_rata_rezolvare_cazuri(double x);

    [[nodiscard]] double incasari() const override;
    [[nodiscard]] double impact_fericire(Amanunte actiune) const override;

    void print(std::ostream& os) const override;

    [[nodiscard]] std::unique_ptr<CladirePublica> clone() const override;
};

#endif //OOP_CLADIRESERVICII_H