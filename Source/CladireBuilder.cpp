//
// Created by flint on 2/15/2026.
//

#include "../Headers/CladireBuilder.h"

CladireBuilder& CladireBuilder::setNume(std::string n) { nume = std::move(n); return *this; }
CladireBuilder& CladireBuilder::setCost(const double c) { cost = c; return *this; }
CladireBuilder& CladireBuilder::setSuprafata(const double s) { suprafata = s; return *this; }
CladireBuilder& CladireBuilder::setCapacitate(const int cap) { capacitate = cap; return *this; }
CladireBuilder& CladireBuilder::setInchiriat(const bool inc) { inchiriat = inc; return *this; }
CladireBuilder& CladireBuilder::setRating(const double r) { rating = r; return *this; }
CladireBuilder& CladireBuilder::setPoluare(const double p) { poluare = p; return *this; }
CladireBuilder& CladireBuilder::setMentenanta(const double m) { mentenanta = m; return *this; }

std::unique_ptr<Fabrica> CladireBuilder::buildFabrica() {
    return std::make_unique<Fabrica>(id, nume, cost, 2000.0, suprafata, capacitate, inchiriat, poluare, 10, 0.5);
}

std::unique_ptr<CladireEducatie> CladireBuilder::buildScoala() {
    return std::make_unique<CladireEducatie>(id, nume, cost, 1500.0, capacitate, 4, 85, 9.5, 10, rating, inchiriat);
}

std::unique_ptr<CladireServicii> CladireBuilder::buildServicii() {
    return std::make_unique<CladireServicii>(id, nume, cost, 1200.0, capacitate, inchiriat, 15, 100, 50, 20, 50, 80);
}

std::unique_ptr<SpatiuComercial> CladireBuilder::buildComercial() {
    return std::make_unique<SpatiuComercial>(id, nume, cost, 1800.0, capacitate, inchiriat, 50, 20, 100);
}

std::unique_ptr<SpatiuVerde> CladireBuilder::buildSpatiuVerde() {
    return std::make_unique<SpatiuVerde>(id, nume, cost, 200.0, suprafata, inchiriat, mentenanta, 0.9);
}

std::unique_ptr<CladireAdministrativa> CladireBuilder::buildAdmin() {
    return std::make_unique<CladireAdministrativa>(id, nume, cost, 2500.0, capacitate, inchiriat, 80, 10, 5);
}