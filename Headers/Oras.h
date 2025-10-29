//
// Created by flint on 10/28/2025.
//

#ifndef OOP_ORAS_H
#define OOP_ORAS_H

#include <string>
#include <vector>

#include "Proiect.h"
#include "Zona.h"

class Oras {
private:
    std::string nume_oras;
    double buget_curent;
    double indice_fericire;
    std::vector<Zona> zone;

    Zona* cautare_zona(const std::string& nume);

    [[nodiscard]] const Zona* cautare_zona(const std::string& nume) const;

public:

    explicit Oras(std::string nume = "", double buget = 0.0, double fericire_init = 0.5);

    Oras(const Oras& other);
    Oras& operator=(const Oras& other);
    ~Oras();

    void adauga_zona(const Zona& z);

    [[nodiscard]] double calcul_cost_intretinere_total() const;
    [[nodiscard]] double calcul_incasari_totale() const;
    [[nodiscard]] int calcul_numar_total_masini() const;

    [[nodiscard]] bool implementare_proiect_stradal(const Proiect& p, const Strada& s, const std::string& nume_zona_proiect);
    [[nodiscard]] bool implementare_proiect_rezidential(const Proiect& p, const CladireRezidentiala& cr, const std::string& nume_zona_proiect);
    [[nodiscard]] bool implementare_proiect_public(const Proiect& p, const CladirePublica& cp, const std::string& nume_zona_proiect);



    void simulare_luna();

    [[nodiscard]] double get_buget() const;
    [[nodiscard]] double get_fericire() const;

    friend std::ostream& operator<<(std::ostream& os, const Oras& o);
};

#endif //OOP_ORAS_H
