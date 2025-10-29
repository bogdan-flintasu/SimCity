//
// Created by flint on 10/28/2025.
//

#ifndef OOP_ZONA_H
#define OOP_ZONA_H


#include <vector>

#include "Structuri.h"

class Zona {
private:
    std::string nume_zona;
    std::vector<Strada> strazi;
    std::vector<CladireRezidentiala> cladiri_rezidentiale;
    std::vector<CladirePublica> cladiri_publice;
public:
    explicit Zona(std::string  nume = "");

    Zona(const Zona& other);
    Zona& operator=(const Zona& other);
    ~Zona();

    void adauga_strada(const Strada& s);
    void adauga_cladire_rezidentiala(const CladireRezidentiala& cr);
    void adauga_cladire_publica(const CladirePublica& cp);

    // functie pentru calculul intretinerii platite de primarie pentru o zona
    [[nodiscard]] double calcul_cost_intretinere_zona() const;

    // functie pentru calculul masinilor dintr-o zona pentru a putea aplica taxele in functie de acest numar
    [[nodiscard]] int calcul_numar_masini_zona() const;

    // functie pentru calculul taxelor, impozitelor, chirii si orice tip de venit incasat de primarie
    [[nodiscard]] double calcul_incasari_zona() const;

    [[nodiscard]] const std::string& get_nume() const;
    [[nodiscard]] const std::vector<CladireRezidentiala>& get_cladiri_rezidentiale() const;

    std::vector<Strada>& get_strazi_modificabile();
    std::vector<CladireRezidentiala>& get_cladiri_rezidentiale_modificabile();
    std::vector<CladirePublica>& get_cladiri_publice_modificabile();

    [[nodiscard]] bool stergere_strada(int id_tinta);
    [[nodiscard]] bool stergere_rezidentiala(int id_tinta);
    [[nodiscard]] bool stergere_publica(int id_tinta);

    [[nodiscard]] bool modifica_strada(int id_tinta, const Strada& date_noi);
    [[nodiscard]] bool modifica_rezidentiala(int id_tinta, const CladireRezidentiala& date_noi);
    [[nodiscard]] bool modifica_publica(int id_tinta, const CladirePublica& date_noi);

    friend std::ostream& operator<<(std::ostream& os, const Zona& z);
};

#endif