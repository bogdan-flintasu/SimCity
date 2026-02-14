//
// Created by flint on 2/15/2026.
//

#ifndef OOP_CLADIREBUILDER_H
#define OOP_CLADIREBUILDER_H

#include <string>
#include <memory>
#include "Fabrica.h"
#include "CladireEducatie.h"
#include "CladireServicii.h"
#include "SpatiuComercial.h"
#include "SpatiuVerde.h"
#include "CladireAdministrativa.h"

class CladireBuilder {
private:
    int id = 0;
    std::string nume = "Implicit";
    double cost = 0.0;
    double suprafata = 0.0;
    int capacitate = 0;
    bool inchiriat = false;
    double rating = 0.0;
    double poluare = 0.0;
    double mentenanta = 0.0;

public:
    CladireBuilder() = default;

    // Metode de tip Builder (Method Chaining)
    CladireBuilder& setNume(std::string n);
    CladireBuilder& setCost(double c);
    CladireBuilder& setSuprafata(double s);
    CladireBuilder& setCapacitate(int cap);
    CladireBuilder& setInchiriat(bool inc);
    CladireBuilder& setRating(double r);
    CladireBuilder& setPoluare(double p);
    CladireBuilder& setMentenanta(double m);

    // Functii de asamblare finala
    std::unique_ptr<Fabrica> buildFabrica();
    std::unique_ptr<CladireEducatie> buildScoala();
    std::unique_ptr<CladireServicii> buildServicii();
    std::unique_ptr<SpatiuComercial> buildComercial();
    std::unique_ptr<SpatiuVerde> buildSpatiuVerde();
    std::unique_ptr<CladireAdministrativa> buildAdmin();
};

#endif