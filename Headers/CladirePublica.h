//
// Created by flint on 12/4/2025.
//

#ifndef OOP_CLADIREPUBLICA_H
#define OOP_CLADIREPUBLICA_H

#include <string>
#include <memory>

#include "Proiect.h"


class CladirePublica {
protected:
    int ID{};
    std::string nume;
    double cost_construire;
    double cost_intretinere;
    int capacitate_servicii;
    bool inchiriat{false};
    static int next_id;
    static int gen_id();
    static void reset_id(int start = 1);

public:
    explicit CladirePublica(int id = 0, std::string  n = "", double cost_c = 0, double cost_i = 0, int capacitate = 0, bool inchiriat_ = false);

    CladirePublica(const CladirePublica& other);
    CladirePublica& operator=(const CladirePublica& other);
    virtual ~CladirePublica();

    [[nodiscard]] int get_ID() const;
    [[nodiscard]] double get_cost_intretinere() const;
    [[nodiscard]] const std::string& get_nume() const;
    [[nodiscard]] int get_capacitate() const;
    [[nodiscard]] bool get_inchiriat() const;

    [[nodiscard]] virtual double incasari() const = 0;
    virtual void print(std::ostream& os) const;

    [[nodiscard]] virtual std::unique_ptr<CladirePublica> clone() const = 0;

    [[nodiscard]] virtual double impact_fericire(Amanunte actiune) const = 0;



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

#endif //OOP_CLADIREPUBLICA_H
