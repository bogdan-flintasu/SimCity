//
// Created by flint on 10/28/2025.
//

#ifndef OOP_ORAS_H
#define OOP_ORAS_H

#include <string>
#include <vector>

#include "Proiect.h"
#include "Zona.h"
#include "../Headers/TrackerProgres.h"

class Oras {
private:
    std::string nume_oras;
    int luni_mandat;
    int luni_consecutive_excelenta;
    int stare_joc;
    double buget_curent;
    double indice_fericire;
    double buget_initial;
    double fericire_initiala;
    std::vector<Zona> zone;
    int luni_fara_proiect;
    bool proiect_implementat_luna_curenta;
    TrackerProgres<double, int> istoricBuget;

    [[nodiscard]] const Zona* cautare_zona(const std::string& nume) const;


public:
    Zona* cautare_zona(const std::string& nume);

    explicit Oras(std::string nume = "", double buget = 0.0, double fericire_init = 0.5);

    Oras(const Oras& other) = default;
    Oras& operator=(const Oras& other) = default;

    Oras(Oras&& other) noexcept = default;
    Oras& operator=(Oras&& other) noexcept = default;

    ~Oras() = default;

    friend void swap(Oras& a, Oras& b) noexcept;

    [[nodiscard]] double get_buget() const;
    [[nodiscard]] [[maybe_unused]] int get_populatie() const;
    [[nodiscard]] double get_fericire() const;
    [[nodiscard]] [[maybe_unused]] bool get_proiect_implementat() const;
    [[nodiscard]] int get_luna_curenta() const;
    [[nodiscard]] [[maybe_unused]] int get_luni_excelenta() const;
    [[nodiscard]] [[maybe_unused]] int get_stare_joc() const;

    [[maybe_unused]] void set_proiect_implementat();
    [[maybe_unused]] void set_nume(const std::string& nume);
    void set_stare_joc(int stare);

    [[maybe_unused]] void adauga_zona(Zona z);

    [[nodiscard]] double calcul_cost_intretinere_total() const;
    [[nodiscard]] double calcul_incasari_totale() const;
    [[nodiscard]] int calcul_numar_total_masini() const;

    [[maybe_unused]] bool implementare_proiect_stradal(const Proiect& p,
                                                    const Strada& s,
                                                    const std::string& nume_zona_proiect);

    [[maybe_unused]] bool implementare_proiect_rezidential(const Proiect& p,
                                                        std::unique_ptr<CladireRezidentiala> cr,
                                                        const std::string& nume_zona_proiect);

    [[maybe_unused]] bool implementare_proiect_public(const Proiect& p,
                                                   std::unique_ptr<CladirePublica> cp,
                                                   const std::string& nume_zona_proiect);

    [[maybe_unused]] void simulare_luna();

    void reset();
    [[maybe_unused]] void incarca_preset_challenge();
    [[nodiscard]] [[maybe_unused]] bool sterge_zona(const std::string& nume);

    [[nodiscard]] std::string genereaza_raport_final() const;

    friend std::ostream& operator<<(std::ostream& os, const Oras& o);
};

#endif //OOP_ORAS_H
