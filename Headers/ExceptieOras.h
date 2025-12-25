//
// Created by flint on 12/24/2025.
//

#ifndef OOP_EXCEPTIEORAS_H
#define OOP_EXCEPTIEORAS_H

#include <stdexcept>
#include <string>

class ExceptieOras : public std::runtime_error {
public:
    explicit ExceptieOras(const std::string& msg) : std::runtime_error(msg) {}
};

class ExceptieZonaInexistenta final : public ExceptieOras {
public:
    explicit ExceptieZonaInexistenta(const std::string& nume)
        : ExceptieOras("Zona inexistenta: " + nume) {}
};

class ExceptieBugetInsuficient : public ExceptieOras {
public:
    explicit ExceptieBugetInsuficient(double buget, double cost)
        : ExceptieOras("Buget insuficient. Buget=" + std::to_string(buget) +
                       ", cost=" + std::to_string(cost)) {}
};

class ExceptieIDInexistent final : public ExceptieOras {
public:
    explicit ExceptieIDInexistent(int id)
        : ExceptieOras("ID inexistent: " + std::to_string(id)) {}
};

class ExceptieTipIncompatibil final : public ExceptieOras {
public:
    explicit ExceptieTipIncompatibil(const std::string& msg)
        : ExceptieOras("Tip incompatibil: " + msg) {}
};

class ExceptieDateInvalide final : public ExceptieOras {
public:
    explicit ExceptieDateInvalide(const std::string& msg)
        : ExceptieOras("Date invalide: " + msg) {}
};

#endif //OOP_EXCEPTIEORAS_H