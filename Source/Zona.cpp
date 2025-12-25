//
// Created by flint on 10/28/2025.
//

#include <string>
#include <iostream>
#include <utility>

#include "../Headers/Zona.h"
#include "../Headers/ExceptieOras.h"

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

Zona& Zona::operator=(Zona other) {
    swap(*this, other);
    return *this;
}

Zona::~Zona() = default;

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

double Zona::calcul_incasari_zona() const {
    double total = 0.0;

    for (const auto& cr : cladiri_rezidentiale) {
        const std::string_view tip = cr->tip_cladire();
        if (tip == "Casa")
            total += cr->get_numar_locuitori() * 15.0;
        else if (tip == "Bloc")
            total += cr->get_numar_locuitori() * 10.0;
    }

    for (const auto& cp : cladiri_publice) {
        total += cp->incasari();
    }

    for (const Strada& s : strazi) {
        double taxa = s.get_numar_benzi() * 7.0 * s.get_lungime() * 0.5;
        if (!s.get_sens_unic())
            taxa *= 2.0;
        total += taxa;
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

bool Zona::modifica_strada(int id_tinta, const Strada &date_noi) {
    for (Strada& s : strazi) {
        if (s.get_ID() == id_tinta) {
            s = date_noi;
            return true;
        }
    }
    return false;
}

bool Zona::modifica_rezidentiala(int id_tinta, std::unique_ptr<CladireRezidentiala> date_noi) {
    for (auto& cr : cladiri_rezidentiale) {
        if (cr->get_ID() != id_tinta) continue;

        if (dynamic_cast<Casa*>(cr.get())) {
            if (!dynamic_cast<Casa*>(date_noi.get()))
                throw ExceptieTipIncompatibil("rezidential ID=" + std::to_string(id_tinta));
        } else if (dynamic_cast<Bloc*>(cr.get())) {
            if (!dynamic_cast<Bloc*>(date_noi.get()))
                throw ExceptieTipIncompatibil("rezidential ID=" + std::to_string(id_tinta));
        } else {
            throw ExceptieTipIncompatibil("rezidential ID=" + std::to_string(id_tinta));
        }

        cr = std::move(date_noi);
        return true;
    }
    return false;
}



bool Zona::modifica_publica(int id_tinta, std::unique_ptr<CladirePublica> date_noi) {
    for (auto& cp : cladiri_publice) {
        if (cp->get_ID() != id_tinta) continue;

        if (dynamic_cast<CladireServicii*>(cp.get())) {
            if (!dynamic_cast<CladireServicii*>(date_noi.get()))
                throw ExceptieTipIncompatibil("public ID=" + std::to_string(id_tinta));
        } else if (dynamic_cast<CladireEducatie*>(cp.get())) {
            if (!dynamic_cast<CladireEducatie*>(date_noi.get()))
                throw ExceptieTipIncompatibil("public ID=" + std::to_string(id_tinta));
        } else if (dynamic_cast<SpatiuVerde*>(cp.get())) {
            if (!dynamic_cast<SpatiuVerde*>(date_noi.get()))
                throw ExceptieTipIncompatibil("public ID=" + std::to_string(id_tinta));
        } else if (dynamic_cast<CladireAdministrativa*>(cp.get())) {
            if (!dynamic_cast<CladireAdministrativa*>(date_noi.get()))
                throw ExceptieTipIncompatibil("public ID=" + std::to_string(id_tinta));
            if (dynamic_cast<CladireServicii*>(date_noi.get()))
                throw ExceptieTipIncompatibil("public ID=" + std::to_string(id_tinta));
        } else {
            throw ExceptieTipIncompatibil("public ID=" + std::to_string(id_tinta));
        }

        cp = std::move(date_noi);
        return true;
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
