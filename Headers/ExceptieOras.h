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

class ExceptieBugetInsuficient : public ExceptieOras {
private:
    double m_bugetActual;
    double m_costNecesar;
public:
    explicit ExceptieBugetInsuficient(double buget, double cost)
        : ExceptieOras("Fonduri insuficiente pentru finalizarea proiectului."),
          m_bugetActual(buget), m_costNecesar(cost) {}

    [[nodiscard]] double getLipsa() const { return m_costNecesar - m_bugetActual; }
    [[nodiscard]] double getBuget() const { return m_bugetActual; }
    [[nodiscard]] double getCost() const { return m_costNecesar; }
};

class ExceptieIDInexistent : public ExceptieOras {
private:
    int m_idProblema;
public:
    explicit ExceptieIDInexistent(const int id)
        : ExceptieOras("ID-ul solicitat nu a fost gasit in baza de date a orasului."),
          m_idProblema(id) {}

    [[nodiscard]] int getID() const { return m_idProblema; }
};

class ExceptieZonaInexistenta : public ExceptieOras {
private:
    std::string m_numeZona;
public:
    explicit ExceptieZonaInexistenta(std::string nume)
        : ExceptieOras("Zona specificata nu exista."), m_numeZona(std::move(nume)) {}

    [[nodiscard]] const std::string& getNumeZona() const { return m_numeZona; }
};

class ExceptieDateInvalide : public ExceptieOras {
public:
    explicit ExceptieDateInvalide(const std::string& msg)
        : ExceptieOras("Datele introduse sunt invalide: " + msg) {}
};

#endif //OOP_EXCEPTIEORAS_H