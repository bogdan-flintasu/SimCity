//
// Created by flint on 10/28/2025.
//

#include <string>
#include <utility>
#include <ostream>


#include "../Headers/Zona.h"
#include "../Headers/ExceptieOras.h"
#include "../Headers/Casa.h"
#include "../Headers/Bloc.h"
#include "../Headers/CladireAdministrativa.h"
#include "../Headers/CladireServicii.h"
#include "../Headers/CladireEconomie.h"
#include "../Headers/CladireEducatie.h"
#include "../Headers/SpatiuVerde.h"
#include "../Headers/Fabrica.h"
#include "../Headers/SpatiuComercial.h"

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
        const double v = cr->incasari_lunare();
        std::cout << "[INCASARI REZ] ID=" << cr->get_ID() << " v=" << v << "\n";
        total += v;
    }

    for (const auto& cp : cladiri_publice) {
        const double v = cp->incasari();
        std::cout << "[INCASARI PUB] ID=" << cp->get_ID() << " v=" << v << "\n";
        total += v;
    }

    for (const Strada& s : strazi) {
        double taxa = s.get_numar_benzi() * 7.0 * s.get_lungime() * 0.5;
        if (!s.get_sens_unic()) taxa *= 2.0;
        std::cout << "[TAXA STR] ID=" << s.get_ID() << " taxa=" << taxa << "\n";
        total += taxa;
    }

    std::cout << "[INCASARI ZONA TOTAL] " << total << "\n";
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
    if (!date_noi) throw ExceptieDateInvalide("modifica_rezidentiala: date_noi null");

    for (auto& cr : cladiri_rezidentiale) {
        if (!cr || cr->get_ID() != id_tinta) continue;

        const std::string msg = "rezidential ID=" + std::to_string(id_tinta);

        try {
            try {
                (void)dynamic_cast<Casa&>(*cr);
                (void)dynamic_cast<Casa&>(*date_noi);
            } catch (const std::bad_cast&) {
                try {
                    (void)dynamic_cast<Bloc&>(*cr);
                    (void)dynamic_cast<Bloc&>(*date_noi);
                } catch (const std::bad_cast&) {
                    throw ExceptieTipIncompatibil(msg);
                }
            }
        } catch (const ExceptieOras&) {
            throw;
        }

        cr = std::move(date_noi);
        return true;
    }
    return false;
}





bool Zona::modifica_publica(int id_tinta, std::unique_ptr<CladirePublica> date_noi) {
    if (!date_noi) throw ExceptieDateInvalide("modifica_publica: date_noi null");

    for (auto& cp : cladiri_publice) {
        if (!cp || cp->get_ID() != id_tinta) continue;

        const std::string msg = "public ID=" + std::to_string(id_tinta);

        try {
            (void)dynamic_cast<CladireServicii&>(*cp);
            (void)dynamic_cast<CladireServicii&>(*date_noi);
        } catch (const std::bad_cast&) {
            try {
                (void)dynamic_cast<CladireEducatie&>(*cp);
                (void)dynamic_cast<CladireEducatie&>(*date_noi);
            } catch (const std::bad_cast&) {
                try {
                    (void)dynamic_cast<SpatiuVerde&>(*cp);
                    (void)dynamic_cast<SpatiuVerde&>(*date_noi);
                } catch (const std::bad_cast&) {
                    try {
                        // DACA AI: Fabrica : public CladireEconomie
                        (void)dynamic_cast<Fabrica&>(*cp);
                        (void)dynamic_cast<Fabrica&>(*date_noi);
                    } catch (const std::bad_cast&) {
                        try {
                            // DACA AI: SpatiuComercial : public CladireEconomie
                            (void)dynamic_cast<SpatiuComercial&>(*cp);
                            (void)dynamic_cast<SpatiuComercial&>(*date_noi);
                        } catch (const std::bad_cast&) {
                            try {
                                (void)dynamic_cast<CladireAdministrativa&>(*cp);
                                (void)dynamic_cast<CladireAdministrativa&>(*date_noi);
                            } catch (const std::bad_cast&) {
                                throw ExceptieTipIncompatibil(msg);
                            }
                        }
                    }
                }
            }
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
