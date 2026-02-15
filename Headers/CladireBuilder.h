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

    [[maybe_unused]] CladireBuilder& setNume(std::string n);
    [[maybe_unused]] CladireBuilder& setCost(double c);
    [[maybe_unused]] CladireBuilder& setSuprafata(double s);
    [[maybe_unused]] CladireBuilder& setCapacitate(int cap);
    [[maybe_unused]] CladireBuilder& setInchiriat(bool inc);
    [[maybe_unused]] CladireBuilder& setRating(double r);
    [[maybe_unused]] CladireBuilder& setPoluare(double p);
    [[maybe_unused]] CladireBuilder& setMentenanta(double m);

    [[maybe_unused]] std::unique_ptr<Fabrica> buildFabrica();
    [[maybe_unused]] std::unique_ptr<CladireEducatie> buildScoala();
    [[maybe_unused]] std::unique_ptr<CladireServicii> buildServicii();
    [[maybe_unused]] std::unique_ptr<SpatiuComercial> buildComercial();
    [[maybe_unused]] std::unique_ptr<SpatiuVerde> buildSpatiuVerde();
    [[maybe_unused]] std::unique_ptr<CladireAdministrativa> buildAdmin();
};

#endif