//
// Created by flint on 10/28/2025.
//

#include <string>
#include <utility>
#include <ostream>


#include "../Headers/Zona.h"
#include "../Headers/ExceptieOras.h"
#include "../Headers/Bloc.h"
#include "../Headers/CladireAdministrativa.h"
#include "../Headers/CladireEconomie.h"
#include "../Headers/CladireRezidentiala.h"

Zona::Zona(std::string  nume) : nume_zona(std::move(nume)) {}

Zona::Zona(const Zona& other)
    : nume_zona(other.nume_zona),
      strazi(other.strazi) {
    cladiri_rezidentiale.reserve(other.cladiri_rezidentiale.size());
    for (const auto& cr : other.cladiri_rezidentiale)
        cladiri_rezidentiale.push_back(cr ? cr->clone() : nullptr);

    cladiri_publice.reserve(other.cladiri_publice.size());
    for (const auto& cp : other.cladiri_publice)
        cladiri_publice.push_back(cp ? cp->clone() : nullptr);
}

void swap(Zona& a, Zona& b) noexcept {
    using std::swap;
    swap(a.nume_zona, b.nume_zona);
    swap(a.strazi, b.strazi);
    swap(a.cladiri_rezidentiale, b.cladiri_rezidentiale);
    swap(a.cladiri_publice, b.cladiri_publice);
}

Zona& Zona::operator=(const Zona& other) {
    if (this != &other) {
        Zona tmp(other);
        swap(*this, tmp);
    }
    return *this;
}


Zona::~Zona() = default;

Strada *Zona::get_strada_dupa_id(const int id) {
    for (auto& s : strazi) {
        if (s.get_ID() == id) return &s;
    }
    throw ExceptieIDInexistent(id);
}

std::unique_ptr<CladireRezidentiala> Zona::get_rezidentiala_dupa_id(const int id) {
    for (auto it = cladiri_rezidentiale.begin(); it != cladiri_rezidentiale.end(); ++it) {
        if ((*it)->get_ID() == id) {
            std::unique_ptr<CladireRezidentiala> res = std::move(*it);
            cladiri_rezidentiale.erase(it);
            return res;
        }
    }
    throw ExceptieIDInexistent(id);
}

std::unique_ptr<CladirePublica> Zona::get_publica_dupa_id(const int id) {
    for (auto it = cladiri_publice.begin(); it != cladiri_publice.end(); ++it) {
        if ((*it)->get_ID() == id) {
            std::unique_ptr<CladirePublica> res = std::move(*it);
            cladiri_publice.erase(it);
            return res;
        }
    }
    throw ExceptieIDInexistent(id);
}

int Zona::get_ultimul_id_strada() const {
    return strazi.empty() ? -1 : strazi.back().get_ID();
}

int Zona::get_ultimul_id_rezidentiala() const {
    return cladiri_rezidentiale.empty() ? -1 : cladiri_rezidentiale.back()->get_ID();
}

int Zona::get_ultimul_id_publica() const {
    return cladiri_publice.empty() ? -1 : cladiri_publice.back()->get_ID();
}

const std::vector<Strada>& Zona::get_strazi() const {
    return strazi;
}

const std::vector<std::unique_ptr<CladireRezidentiala>>& Zona::get_cladiri_rezidentiale() const {
    return cladiri_rezidentiale;
}

const std::vector<std::unique_ptr<CladirePublica>>& Zona::get_cladiri_publice() const {
    return cladiri_publice;
}


void Zona::adauga_strada(const Strada& s) { strazi.push_back(s); }
void Zona::adauga_cladire_rezidentiala(std::unique_ptr<CladireRezidentiala> cr) { cladiri_rezidentiale.push_back(std::move(cr)); }
void Zona::adauga_cladire_publica(std::unique_ptr<CladirePublica> cp) { cladiri_publice.push_back(std::move(cp)); }
double Zona::calcul_cost_intretinere_zona() const {
    double total = 0;

    for (const Strada& s : strazi) {
        total += s.get_cost_intretinere();
    }

    for (const auto& cr : cladiri_rezidentiale) {
        total += cr->get_cost_intretinere();
    }

    for (const auto& cp : cladiri_publice) {
        total += cp->get_cost_intretinere();
    }

    return total;
}

int Zona::calcul_numar_masini_zona() const {
    int nr_locuitori = 0;
    for (const auto& cr : this -> cladiri_rezidentiale) {
        nr_locuitori += cr->get_numar_locuitori();
    }

    return nr_locuitori / 2;
}

#include <iostream>

double Zona::calcul_incasari_zona() const {
    double total = 0.0;
    for (const auto& cr : cladiri_rezidentiale) {
        total += cr->incasari_lunare();
    }
    for (const auto& cp : cladiri_publice) {
        total += cp->incasari();
    }
    for (const Strada& s : strazi) {
        double taxa = s.get_numar_benzi() * 7.0 * s.get_lungime() * 0.5;
        if (!s.get_sens_unic()) taxa *= 2.0;
        total += taxa;
    }
    return total;
}

int Zona::calcul_populatie_zona() const {
    int total = 0;
    for (const auto& cr : cladiri_rezidentiale) {
        total += cr->get_numar_locuitori();
    }
    return total;
}

bool Zona::stergere_strada(int id_tinta) {
    for (auto it = strazi.begin(); it != strazi.end(); ++it) {
        if (it -> get_ID() == id_tinta) {
            strazi.erase(it);
            return true;
        }
    }
    return false;
}

bool Zona::stergere_rezidentiala(int id_tinta) {
    for (auto it = cladiri_rezidentiale.begin(); it != cladiri_rezidentiale.end(); ++it) {
        if ((*it)->get_ID() == id_tinta) {
            cladiri_rezidentiale.erase(it);
            return true;
        }
    }
    return false;
}

bool Zona::stergere_publica(int id_tinta) {
    for (auto it = cladiri_publice.begin(); it != cladiri_publice.end(); ++it) {
        if ((*it)->get_ID() == id_tinta) {
            cladiri_publice.erase(it);
            return true;
        }
    }
    return false;
}

const std::string& Zona::get_nume() const { return nume_zona; }

std::ostream& operator<<(std::ostream& os, const Zona& z) {
    os << " Zona: " << z.nume_zona << "\n\n";

    os << " Strazi (" << z.strazi.size() << "):\n";
    if (z.strazi.empty()) {
        os << "Nicio strada\n";
    } else {
        for (const Strada& s : z.strazi) {
            os << s << "\n";
        }
    }

    os << "  Cladiri Rezidentiale (" << z.cladiri_rezidentiale.size() << "):\n";
    if (z.cladiri_rezidentiale.empty()) {
        os << "Nicio cladire rezidentiala\n";
    } else {
        for (const auto& cr : z.cladiri_rezidentiale) {
            os << *cr << "\n";
        }
    }

    os << "  Cladiri Publice (" << z.cladiri_publice.size() << "):\n";
    if (z.cladiri_publice.empty()) {
        os << "Nicio cladire publica\n";
    } else {
        for (const auto& cp : z.cladiri_publice) {
            os << *cp << "\n";
        }
    }

    return os;
}
