//
// Created by flint on 12/4/2025.
//

#ifndef OOP_CLADIREPUBLICA_H
#define OOP_CLADIREPUBLICA_H

#include <string>
#include <vector>
#include <ostream>
#include <memory>

class CladirePublica {
protected:
    int ID{};
    std::string nume;
    double cost_construire;
    double cost_intretinere;
    int capacitate_servicii;
    bool inchiriat{false};
    double taxe_lunare;
    static int next_id;
    static int gen_id();
    static void reset_id(int start = 1);

public:
    explicit CladirePublica(int id = 0, std::string  n = "", double cost_c = 0, double cost_i = 0, int capacitate = 0, bool inchiriat_ = false, double taxe = 0.0);

    CladirePublica(const CladirePublica& other);
    CladirePublica& operator=(const CladirePublica& other);
    virtual ~CladirePublica();

    [[nodiscard]] int get_ID() const;
    [[nodiscard]] double get_cost_intretinere() const;
    [[nodiscard]] const std::string& get_nume() const;
    [[nodiscard]] int get_capacitate() const;
    [[nodiscard]] bool get_inchiriat() const;

    [[nodiscard]] virtual const char* tip_cladire() const = 0;
    [[nodiscard]] virtual double incasari() const = 0;
    virtual void print(std::ostream& os) const;

    [[nodiscard]] virtual std::unique_ptr<CladirePublica> clone() const = 0;


    friend std::ostream& operator<<(std::ostream& os, const CladirePublica& cp);
};

struct Salariat {
    int id{};
    double salariu{};
    int eficienta{};

    Salariat(const int id_,
             const double salariu_,
             const int eficienta_ = 50)
        : id(id_), salariu(salariu_), eficienta(eficienta_) {}
};


class CladireAdministrativa : public CladirePublica {
private:
    std::vector<Salariat> salariati;
    int nivel_securitate{};
    double timp_raspuns{};
    double nivel_coruptie{};
public:
    explicit CladireAdministrativa(const int id = 0,
                                   std::string nume_ = "",
                                   const double cost_c = 0.0,
                                   const double cost_i = 0.0,
                                   const int capacitate = 0,
                                   const bool inchiriat_ = false,
                                   const int nivel_sec = 0,
                                   const double timp = 0.0,
                                   const double coruptie = 0.0)
    : CladirePublica(id, std::move(nume_), cost_c, cost_i, capacitate, inchiriat_),
      nivel_securitate(nivel_sec),
      timp_raspuns(timp),
      nivel_coruptie(coruptie) {}

    [[nodiscard]] const char* tip_cladire() const override { return "CladireAdministrativa"; }

    void adauga_salariat(const Salariat& s) {
        salariati.push_back(s);
        cost_intretinere += s.salariu;
    }

    [[nodiscard]] int get_nr_salariati() const { return static_cast<int>(salariati.size()); }
    [[nodiscard]] double eficienta_cladire() const {
        if (salariati.empty()) return 0.0;
        double s = 0.0;
        for (const auto& sal : salariati)
            s += sal.eficienta;
        return s / static_cast<double>(salariati.size());
    }
    [[nodiscard]] int get_nivel_securitate() const { return nivel_securitate; }
    [[nodiscard]] double get_timp_raspuns() const { return timp_raspuns; }
    [[nodiscard]] double get_nivel_coruptie() const { return nivel_coruptie; }

    [[nodiscard]] double incasari() const override {
        return -cost_intretinere - taxe_lunare;
    }

    void set_nivel_coruptie(const double x) {
        if (x < 0.0) nivel_coruptie = 0.0;
        else if (x > 1.0) nivel_coruptie = 1.0;
        else nivel_coruptie = x;
    }

    void print(std::ostream& os) const override {
        CladirePublica::print(os);
        os << ", salariati=" << salariati.size()
           << ", eficienta_medie=" << eficienta_cladire();
    }

    [[nodiscard]] std::unique_ptr<CladirePublica> clone() const override {
        return std::make_unique<CladireAdministrativa>(*this);
    }
};

class CladireServicii : public CladireAdministrativa {
private:
    double dotare{};
    double timp_asteptare{};
    double stoc_curent{};
    double rata_rezolvare_cazuri{};
public:
    explicit CladireServicii(const int id = 0,
                             std::string nume_ = "",
                             const double cost_c = 0.0,
                             const double cost_i = 0.0,
                             const int capacitate = 0,
                             const bool inchiriat_ = false,
                             const int nivel_sec = 0,
                             const double timp = 0.0,
                             const double coruptie = 0.0,
                             const double dotare_ = 0.0,
                             const double timp_asteptare_ = 0.0,
                             const double stoc_curent_ = 0.0,
                             const double rata_rezolvare_ = 0.0)
        : CladireAdministrativa(id, std::move(nume_), cost_c, cost_i, capacitate, inchiriat_,
                                nivel_sec, timp, coruptie),
          dotare(dotare_),
          timp_asteptare(timp_asteptare_),
          stoc_curent(stoc_curent_),
          rata_rezolvare_cazuri(rata_rezolvare_) {}

    [[nodiscard]] const char* tip_cladire() const override {
        return "CladireServicii";
    }

    [[nodiscard]] double get_dotare() const { return dotare; }
    [[nodiscard]] double get_timp_asteptare() const { return timp_asteptare; }
    [[nodiscard]] double get_stoc_curent() const { return stoc_curent; }
    [[nodiscard]] double get_rata_rezolvare_cazuri() const { return rata_rezolvare_cazuri; }

    void set_dotare(const double x) { dotare = x < 0.0 ? 0.0 : x; }
    void set_timp_asteptare(const double x) { timp_asteptare = x < 0.0 ? 0.0 : x; }
    void set_stoc_curent(const double x) { stoc_curent = x < 0.0 ? 0.0 : x; }
    void set_rata_rezolvare_cazuri(const double x) {
        if (x < 0.0) rata_rezolvare_cazuri = 0.0;
        else if (x > 1.0) rata_rezolvare_cazuri = 1.0;
        else rata_rezolvare_cazuri = x;
    }

    void print(std::ostream& os) const override {
        CladireAdministrativa::print(os);
        os << ", dotare=" << dotare
           << ", timp_asteptare=" << timp_asteptare
           << ", stoc_curent=" << stoc_curent
           << ", rata_rezolvare_cazuri=" << rata_rezolvare_cazuri;
    }

    [[nodiscard]] std::unique_ptr<CladirePublica> clone() const override {
        return std::make_unique<CladireServicii>(*this);
    }

};

class CladireEducatie : public CladirePublica {
private:
    std::vector<Salariat> salariati;
    int nivel_educatie{};
    double rata_promovare{};
    double medie_promovare_unitate{};
    double rata_absenta{};
    double rating_elevi{};
public:
    explicit CladireEducatie(const int id = 0,
                             std::string nume_ = "",
                             const double cost_c = 0.0,
                             const double cost_i = 0.0,
                             const int capacitate = 0,
                             const bool inchiriat_ = false,
                             const int nivel = 1,
                             const double promovare = 0.0,
                             const double medie_promovare = 0.0,
                             const double abs = 0.0,
                             const double rating = 0.0)
        : CladirePublica(id, std::move(nume_), cost_c, cost_i, capacitate, inchiriat_),
          nivel_educatie(nivel),
          rata_promovare(promovare),
          medie_promovare_unitate(medie_promovare),
          rata_absenta(abs),
          rating_elevi(rating) {}

    [[nodiscard]] const char* tip_cladire() const override { return "CladireEducatie"; }

    void adauga_salariat(const Salariat& s) {
        salariati.push_back(s);
        cost_intretinere += s.salariu;
    }

    [[nodiscard]] int get_nr_salariati() const {
        return static_cast<int>(salariati.size());
    }

    [[nodiscard]] double eficienta_cladire() const {
        if (salariati.empty()) return 0.0;
        double suma = 0.0;
        for (const auto& sal : salariati) suma += sal.eficienta;
        return suma / static_cast<double>(salariati.size());
    }

    [[nodiscard]] int get_nivel_educatie() const { return nivel_educatie; }
    [[nodiscard]] double get_rata_promovare() const { return rata_promovare; }
    [[nodiscard]] double get_rata_absenta() const { return rata_absenta; }
    [[nodiscard]] double get_rating_elevi() const { return rating_elevi; }

    [[nodiscard]] double incasari() const override {
        return -cost_intretinere - taxe_lunare;
    }

    void set_nivel_educatie(const int x) { nivel_educatie = (x < 0 ? 0 : x); }

    void set_rata_promovare(const double x) {
        if (x < 0.0) rata_promovare = 0.0;
        else if (x > 1.0) rata_promovare = 1.0;
        else rata_promovare = x;
    }

    void set_absente(const double x) {
        if (x < 0.0) rata_absenta = 0.0;
        else if (x > 1.0) rata_absenta = 1.0;
        else rata_absenta = x;
    }

    void print(std::ostream& os) const override {
        CladirePublica::print(os);
        os << ", salariati=" << static_cast<int>(salariati.size())
           << ", eficienta_medie=" << eficienta_cladire()
           << ", nivel_educatie=" << nivel_educatie
           << ", rata_promovare=" << rata_promovare
           << ", medie_promovare_unitate=" << medie_promovare_unitate
           << ", absenteism=" << rata_absenta;
    }

    [[nodiscard]] std::unique_ptr<CladirePublica> clone() const override {
        return std::make_unique<CladireEducatie>(*this);
    }
};

class CladireEconomie : public CladirePublica {
private:

public:
    [[nodiscard]] const char* tip_cladire() const override { return "CladireEconomie"; }

    [[nodiscard]] double incasari() const override {
        return taxe_lunare;
    }

    [[nodiscard]] std::unique_ptr<CladirePublica> clone() const override {
        return std::make_unique<CladireEconomie>(*this);
    }
};

class SpatiuVerde : public CladirePublica {
private:
    double suprafata_mp{};
    double nivel_mentenanta{};

public:
    explicit SpatiuVerde(const int id = 0,
                         std::string nume_ = "",
                         const double cost_c = 0.0,
                         const double cost_i = 0.0,
                         const int capacitate = 0,
                         const bool inchiriat_ = false,
                         const double taxe = 0.0,
                         const double suprafata = 0.0,
                         const double mentenanta = 0.0)
        : CladirePublica(id, std::move(nume_), cost_c, cost_i, capacitate, inchiriat_, taxe),
          suprafata_mp(suprafata),
          nivel_mentenanta(mentenanta) {}

    [[nodiscard]] const char* tip_cladire() const override {
        return "SpatiuVerde";
    }

    [[nodiscard]] double incasari() const override {
        return -cost_intretinere - taxe_lunare;
    }

    [[nodiscard]] double get_suprafata_mp() const { return suprafata_mp; }
    [[nodiscard]] double get_nivel_mentenanta() const { return nivel_mentenanta; }

    void set_suprafata_mp(const double x) { suprafata_mp = (x < 0.0 ? 0.0 : x); }
    void set_nivel_mentenanta(const double x) {
        if (x < 0.0) nivel_mentenanta = 0.0;
        else if (x > 1.0) nivel_mentenanta = 1.0;
        else nivel_mentenanta = x;
    }

    void print(std::ostream& os) const override {
        CladirePublica::print(os);
        os << ", suprafata_mp=" << suprafata_mp
           << ", nivel_mentenanta=" << nivel_mentenanta;
    }

    [[nodiscard]] std::unique_ptr<CladirePublica> clone() const override {
        return std::make_unique<SpatiuVerde>(*this);
    }
};


#endif //OOP_CLADIREPUBLICA_H
