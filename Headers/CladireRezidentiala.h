//
// Created by flint on 12/4/2025.
//

#ifndef OOP_CLADIREREZIDENTIALA_H
#define OOP_CLADIREREZIDENTIALA_H


#include <string>
#include <vector>
#include <memory>

class CladireRezidentiala {
protected:
    int ID{};
    std::string nume;
    double cost_construire;
    double cost_intretinere;
    double suprafata_utila;
    int numar_etaje;
    int numar_locuitori;
    static int next_id;
    static int gen_id();
    static void reset_id(int start = 1);

public:

    explicit CladireRezidentiala(int id = 0, std::string  nume_ = "", double cost_c = 0, double cost_i = 0,
                                 double suprafata = 0, int etaje = 0 , int locatari = 0);

    CladireRezidentiala(const CladireRezidentiala& other);
    CladireRezidentiala& operator=(const CladireRezidentiala& other);
    virtual ~CladireRezidentiala();

    [[nodiscard]] int get_ID() const;
    [[nodiscard]] double get_cost_intretinere() const;
    [[nodiscard]] const std::string& get_nume() const;
    [[nodiscard]] int get_numar_locuitori() const;

    [[nodiscard]] virtual const char* tip_cladire() const = 0;
    virtual void print(std::ostream& os) const;

    [[nodiscard]] virtual std::unique_ptr<CladireRezidentiala> clone() const = 0;

    friend std::ostream& operator<<(std::ostream& os, const CladireRezidentiala& cr);
};

struct Apartament {
    int id{};
    int etaj{};
    int camere{};
    double mp_total{};
    int locatari{};
    bool vacant{true};

    Apartament(const int id_,
               const int etaj_,
               const int camere_,
               const double mp_total_,
               const int locatari_,
               const bool vacant_ = true)
        : id(id_),
          etaj(etaj_),
          camere(camere_),
          mp_total(mp_total_),
          locatari(locatari_),
          vacant(vacant_) {}
};

class Bloc : public CladireRezidentiala {
private:
    std::vector<Apartament> apartamente;

public:
    explicit Bloc(const int id = 0,
         std::string nume_ = "",
         const double cost_c = 0.0,
         const double suprafata = 0.0,
         const int etaje = 0)
        : CladireRezidentiala(id, std::move(nume_), cost_c, 0.0,
                              suprafata, etaje, 0) {}

    [[nodiscard]] const char* tip_cladire() const override {
        return "Bloc";
    }

    [[nodiscard]] int get_nr_apartamente() const {
        return static_cast<int>(apartamente.size());
    }

    [[nodiscard]] int get_nr_apartamente_ocupate() const {
        int cnt = 0;
        for (const auto& ap : apartamente)
            if (!ap.vacant) cnt++;
        return cnt;
    }

    [[nodiscard]] double get_mp_total_apartamente(const bool doar_ocupate = false) const {
        double s = 0.0;
        for (const auto& ap : apartamente) {
            if (doar_ocupate && ap.vacant) continue;
            s += ap.mp_total;
        }
        return s;
    }

    [[nodiscard]] int get_locatari_total() const {
        int s = 0;
        for (const auto& ap : apartamente)
            s += ap.locatari;
        return s;
    }

    void adauga_apartament(const Apartament& ap) {
        apartamente.push_back(ap);
        sincronizeaza_baza();
    }

    void seteaza_vacant(const int id_ap, const bool vacant) {
        for (auto& ap : apartamente) {
            if (ap.id == id_ap) {
                ap.vacant = vacant;
                if (vacant) ap.locatari = 0;
                break;
            }
        }
        sincronizeaza_baza();
    }

    void seteaza_locatari(const int id_ap, const int locatari) {
        for (auto& ap : apartamente) {
            if (ap.id == id_ap) {
                ap.locatari = (locatari < 0 ? 0 : locatari);
                ap.vacant = (ap.locatari == 0);
                break;
            }
        }
        sincronizeaza_baza();
    }

    void calculeaza_cost_intretinere(const double cost_fix_bloc,
                                     const double cost_pe_apartament,
                                     const double cost_pe_mp,
                                     const bool doar_ocupate = false) {
        const int nr_ap = doar_ocupate ? get_nr_apartamente_ocupate()
                                       : get_nr_apartamente();
        const double mp = get_mp_total_apartamente(doar_ocupate);

        cost_intretinere =
            cost_fix_bloc +
            cost_pe_apartament * nr_ap +
            cost_pe_mp * mp;
    }

    [[nodiscard]] std::unique_ptr<CladireRezidentiala> clone() const override {
        return std::make_unique<Bloc>(*this);
    }

private:
    void sincronizeaza_baza() {
        numar_locuitori = get_locatari_total();
        suprafata_utila = get_mp_total_apartamente(false);
    }
};



class Casa : public CladireRezidentiala {
private:
    bool ocupata{true};

public:
    explicit Casa(const int id = 0,
         std::string nume_ = "",
         const double cost_c = 0.0,
         const double suprafata = 0.0,
         const int etaje = 0,
         const int locatari = 0)
        : CladireRezidentiala(id, std::move(nume_), cost_c, 0.0,
                              suprafata, etaje, locatari),
          ocupata(locatari > 0) {}

    [[nodiscard]] const char* tip_cladire() const override {
        return "Casa";
    }

    [[nodiscard]] bool este_ocupata() const {
        return ocupata;
    }

    void seteaza_locatari(const int locatari) {
        numar_locuitori = (locatari < 0 ? 0 : locatari);
        ocupata = (numar_locuitori > 0);
    }

    void seteaza_vacanta() {
        numar_locuitori = 0;
        ocupata = false;
    }

    void calculeaza_cost_intretinere(const double cost_fix_casa,
                                     const double cost_pe_mp,
                                     const double cost_pe_locatar) {
        cost_intretinere =
            cost_fix_casa +
            cost_pe_mp * suprafata_utila +
            cost_pe_locatar * numar_locuitori;
    }

    void print(std::ostream& os) const override {
        CladireRezidentiala::print(os);
        os << ", ocupata=" << (ocupata ? "da" : "nu");
    }

    [[nodiscard]] std::unique_ptr<CladireRezidentiala> clone() const override {
        return std::make_unique<Casa>(*this);
    }
};

#endif //OOP_CLADIREREZIDENTIALA_H
