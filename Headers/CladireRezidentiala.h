//
// Created by flint on 12/4/2025.
//

#ifndef OOP_CLADIREREZIDENTIALA_H
#define OOP_CLADIREREZIDENTIALA_H


#include <string>
#include <memory>

#include "Proiect.h"

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
    [[nodiscard]] virtual int get_numar_locuitori() const = 0;

    virtual void print(std::ostream& os) const;

    [[nodiscard]] virtual std::unique_ptr<CladireRezidentiala> clone() const = 0;

    [[nodiscard]] virtual double impact_fericire(Amanunte actiune) const = 0;
    [[nodiscard]] virtual double incasari_lunare() const = 0;

    friend std::ostream& operator<<(std::ostream& os, const CladireRezidentiala& cr);
};

#endif //OOP_CLADIREREZIDENTIALA_H
