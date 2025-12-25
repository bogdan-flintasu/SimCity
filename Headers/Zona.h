//
// Created by flint on 10/28/2025.
//

#ifndef OOP_ZONA_H
#define OOP_ZONA_H


#include <vector>
#include <memory>


#include "Strada.h"
#include "CladirePublica.h"
#include "CladireRezidentiala.h"

class Zona {
private:
    std::string nume_zona;
    std::vector<Strada> strazi;
    std::vector<std::unique_ptr<CladireRezidentiala>> cladiri_rezidentiale;
    std::vector<std::unique_ptr<CladirePublica>> cladiri_publice;
public:
    explicit Zona(std::string  nume = "");

    Zona(const Zona& other);
    Zona& operator=(Zona other);

    Zona(Zona&&) noexcept = default;
    Zona& operator=(Zona&&) noexcept = default;

    ~Zona();

    friend void swap(Zona& a, Zona& b) noexcept;

    void adauga_strada(const Strada& s);
    void adauga_cladire_rezidentiala(std::unique_ptr<CladireRezidentiala> cr);
    void adauga_cladire_publica(std::unique_ptr<CladirePublica> cp);

    // functie pentru calculul intretinerii platite de primarie pentru o zona
    [[nodiscard]] double calcul_cost_intretinere_zona() const;

    // functie pentru calculul masinilor dintr-o zona pentru a putea aplica taxele in functie de acest numar
    [[nodiscard]] int calcul_numar_masini_zona() const;

    // functie pentru calculul taxelor, impozitelor, chirii si orice tip de venit incasat de primarie
    [[nodiscard]] double calcul_incasari_zona() const;

    [[nodiscard]] const std::string& get_nume() const;

    [[nodiscard]] bool stergere_strada(int id_tinta);
    [[nodiscard]] bool stergere_rezidentiala(int id_tinta);
    [[nodiscard]] bool stergere_publica(int id_tinta);

    [[nodiscard]] bool modifica_strada(int id_tinta, const Strada& date_noi);
    [[nodiscard]] bool modifica_rezidentiala(int id_tinta, std::unique_ptr<CladireRezidentiala> date_noi);
    [[nodiscard]] bool modifica_publica(int id_tinta, std::unique_ptr<CladirePublica> date_noi);

    friend std::ostream& operator<<(std::ostream& os, const Zona& z);
};

#endif