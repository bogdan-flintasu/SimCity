//
// Created by flint on 10/28/2025.
//

#include <string>
#include <iostream>

#include "../Headers/Zona.h"

Zona::Zona(std::string  nume) : nume_zona(std::move(nume)) {}

Zona::Zona(const Zona& other) = default;

Zona& Zona::operator=(const Zona& other) {
    if (this != &other) {
        nume_zona = other.nume_zona;
        strazi = other.strazi;
        cladiri_rezidentiale = other.cladiri_rezidentiale;
        cladiri_publice = other.cladiri_publice;
    }
    return *this;
}

Zona::~Zona() = default;

void Zona::adauga_strada(const Strada& s) { strazi.push_back(s); }
void Zona::adauga_cladire_rezidentiala(const CladireRezidentiala& cr) { cladiri_rezidentiale.push_back(cr); }
void Zona::adauga_cladire_publica(const CladirePublica& cp) { cladiri_publice.push_back(cp); }

double Zona::calcul_cost_intretinere_zona() const {
    double total = 0;

    for (const Strada& s : strazi) {
        total += s.get_cost_intretinere();
    }

    for (const CladireRezidentiala& cr : cladiri_rezidentiale) {
        total += cr.get_cost_intretinere();
    }

    for (const CladirePublica& cp : cladiri_publice) {
        total += cp.get_cost_intretinere();
    }

    return total;
}

int Zona::calcul_numar_masini_zona() const {
    int nr_locuitori = 0;
    for (const CladireRezidentiala& cr : this -> cladiri_rezidentiale) {
        nr_locuitori += cr.get_numar_locuitori();
    }

    return nr_locuitori / 2;
}

double Zona::calcul_incasari_zona() const {
    double total = 0;

    for (const CladireRezidentiala& cr : cladiri_rezidentiale) {
        if (cr.get_tip() == CladiriRezidentiale::CASA) {
            total += cr.get_numar_locuitori() * 15;
        }
        else if (cr.get_tip() == CladiriRezidentiale::BLOC) {
            total += cr.get_numar_locuitori() * 10;
        }
    }

    for (const CladirePublica& cp : cladiri_publice) {
        if (cp.get_inchiriat()) {
            CladiriPublice tip_cladire = cp.get_tip();
            if (tip_cladire == CladiriPublice::SPATIU_COMERCIAL) {
                total += cp.get_capacitate() * 200;
            } else if (tip_cladire == CladiriPublice::CLADIRE_BIROURI) {
                total += cp.get_capacitate() * 300;
            } else if (tip_cladire == CladiriPublice::SCOALA || tip_cladire == CladiriPublice::SPITAL || tip_cladire == CladiriPublice::UNIVERSITATE) {
                total += cp.get_capacitate() * 25;
            }
            else {
                total += cp.get_capacitate() * 100;
            }
        }
    }

    for (const Strada& s : strazi) {
        double taxa = s.get_numar_benzi() * 7 * s.get_lungime() * 0.5;
        if (!s.get_sens_unic())
            taxa *= 2.0;
        total += taxa;
    }

    return total;
}

[[nodiscard]] bool Zona::stergere_strada(int id_tinta) {
    for (auto it = strazi.begin(); it != strazi.end(); ++it) {
        if (it -> get_ID() == id_tinta) {
            strazi.erase(it);
            return true;
        }
    }
    return false;
}

[[nodiscard]] bool Zona::stergere_rezidentiala(int id_tinta) {
    for (auto it = cladiri_rezidentiale.begin(); it != cladiri_rezidentiale.end(); ++it) {
        if (it -> get_ID() == id_tinta) {
            cladiri_rezidentiale.erase(it);
            return true;
        }
    }
    return false;
}

[[nodiscard]] bool Zona::stergere_publica(int id_tinta) {
    for (auto it = cladiri_publice.begin(); it != cladiri_publice.end(); ++it) {
        if (it -> get_ID() == id_tinta) {
            cladiri_publice.erase(it);
            return true;
        }
    }
    return false;
}

bool Zona::modifica_strada(int id_tinta, const Strada &date_noi) {
    for (Strada& s : strazi) {
        if (s.get_ID() == id_tinta) {
            s.set_cost_intretinere(date_noi.get_cost_intretinere());
            s.set_numar_benzi(date_noi.get_numar_benzi());
            s.set_lungime(date_noi.get_lungime());
            s.set_sens(date_noi.get_sens_unic());
            s.set_trotuar(date_noi.get_trotuar());
            return true;
        }
    }
    return false;
}

bool Zona::modifica_rezidentiala(int id_tinta, const CladireRezidentiala &date_noi) {
    for (CladireRezidentiala& cr : cladiri_rezidentiale) {
        if (cr.get_ID() == id_tinta) {
            cr.set_cost_intretinere(date_noi.get_cost_intretinere());
            cr.set_numar_locuitori(date_noi.get_numar_locuitori());
            return true;
        }
    }
    return false;
}

bool Zona::modifica_publica(int id_tinta, const CladirePublica &date_noi) {
    for (CladirePublica& cp : cladiri_publice) {
        if (cp.get_ID() == id_tinta) {
            cp.set_cost_intretinere(date_noi.get_cost_intretinere());
            cp.set_capacitate(date_noi.get_capacitate());
            return true;
        }
    }
    return false;
}

const std::string& Zona::get_nume() const { return nume_zona; }
const std::vector<CladireRezidentiala>& Zona::get_cladiri_rezidentiale() const {
    return cladiri_rezidentiale;
}
std::vector<Strada>& Zona::get_strazi_modificabile() { return strazi; }
std::vector<CladireRezidentiala>& Zona::get_cladiri_rezidentiale_modificabile() { return cladiri_rezidentiale; }
std::vector<CladirePublica>& Zona::get_cladiri_publice_modificabile() { return cladiri_publice; }

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
        for (const CladireRezidentiala& cr : z.cladiri_rezidentiale) {
            os << cr << "\n";
        }
    }

    os << "  Cladiri Publice (" << z.cladiri_publice.size() << "):\n";
    if (z.cladiri_publice.empty()) {
        os << "Nicio cladire publica\n";
    } else {
        for (const CladirePublica& cp : z.cladiri_publice) {
            os << cp << "\n";
        }
    }

    return os;
}
