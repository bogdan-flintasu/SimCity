//
// Created by flint on 10/28/2025.
//

#include <iostream>
#include <algorithm>
#include "Clamp.h"


#include "../Headers/Oras.h"
#include "../Headers/ExceptieOras.h"

Zona* Oras::cautare_zona(const std::string& nume) {
    for (Zona& z : zone) {
        if (z.get_nume() == nume) {
            return &z;
        }
    }
    return nullptr;
}

const Zona* Oras::cautare_zona(const std::string& nume) const{
    for (const Zona& z : zone) {
        if (z.get_nume() == nume) {
            return &z;
        }
    }
    return nullptr;
}

Oras::Oras(std::string nume, const double buget, const double fericire_init): nume_oras(std::move(nume)), buget_curent(buget), indice_fericire(fericire_init) {}

Oras::Oras(const Oras& other) = default;

void swap(Oras& a, Oras& b) noexcept {
    using std::swap;
    swap(a.nume_oras, b.nume_oras);
    swap(a.buget_curent, b.buget_curent);
    swap(a.indice_fericire, b.indice_fericire);
    swap(a.zone, b.zone);
}

Oras& Oras::operator=(Oras other) {
    swap(*this, other);
    return *this;
}


Oras::~Oras() = default;

void Oras::adauga_zona(Zona z) { zone.push_back(std::move(z)); }

double Oras::calcul_cost_intretinere_total() const {
    double total = 0;
    for (const Zona& z : zone) {
        total += z.calcul_cost_intretinere_zona();
    }
    return total;
}

double Oras::calcul_incasari_totale() const {
    double total = 0;
    for (const Zona& z : zone) {
        total += z.calcul_incasari_zona();
    }
    return total;
}

int Oras::calcul_numar_total_masini() const {
    int total = 0;
    for (const Zona& z : zone) {
        total += z.calcul_numar_masini_zona();
    }
    return total;
}

double Oras::get_buget() const { return buget_curent; }
double Oras::get_fericire() const { return indice_fericire; }



bool Oras::implementare_proiect_stradal(const Proiect& p, const Strada& s, const std::string& nume_zona_proiect) {
    if (p.get_tip() != Proiecte::STRADA) return false;

    if (buget_curent < p.get_cost_estimat())
        throw ExceptieBugetInsuficient(buget_curent, p.get_cost_estimat());

    Zona* zona_tinta = cautare_zona(nume_zona_proiect);
    if (zona_tinta == nullptr)
        throw ExceptieZonaInexistenta(nume_zona_proiect);

    buget_curent -= p.get_cost_estimat();

    Amanunte actiune = p.get_detalii();
    bool succes = false;

    if (actiune == Amanunte::DE_LA_ZERO) {
        zona_tinta->adauga_strada(s);
        indice_fericire = std::min(1.0, indice_fericire + 0.02);
        succes = true;
    }
    else if (actiune == Amanunte::DEMOLARE) {
        if (zona_tinta->stergere_strada(s.get_ID())) {
            indice_fericire = std::max(0.0, indice_fericire - 0.03);
            succes = true;
        } else {
            buget_curent += p.get_cost_estimat();
            throw ExceptieIDInexistent(s.get_ID());
        }
    }
    else if (actiune == Amanunte::IMBUNATATIRE) {
        if (zona_tinta->modifica_strada(s.get_ID(), s)) {
            indice_fericire = std::min(1.0, indice_fericire + 0.01);
            succes = true;
        } else {
            buget_curent += p.get_cost_estimat();
            throw ExceptieIDInexistent(s.get_ID());
        }
    }

    std::cout << "SUCCES: Proiect stradal '" << amtostr(actiune) << "' finalizat.\n";
    return succes;
}


bool Oras::implementare_proiect_rezidential(const Proiect& p,
                                            std::unique_ptr<CladireRezidentiala> cr,
                                            const std::string& nume_zona_proiect) {
    if (p.get_tip() != Proiecte::REZIDENTIAL) return false;

    if (buget_curent < p.get_cost_estimat())
        throw ExceptieBugetInsuficient(buget_curent, p.get_cost_estimat());

    Zona* zona_tinta = cautare_zona(nume_zona_proiect);
    if (!zona_tinta)
        throw ExceptieZonaInexistenta(nume_zona_proiect);

    if (!cr)
        throw ExceptieDateInvalide("implementare_proiect_rezidential: cr null");

    const Amanunte actiune = p.get_detalii();
    const int id_tinta = cr->get_ID();

    const double delta = cr->impact_fericire(actiune);

    buget_curent -= p.get_cost_estimat();

    if (actiune == Amanunte::DE_LA_ZERO) {
        zona_tinta->adauga_cladire_rezidentiala(std::move(cr));
        indice_fericire = clamp01(indice_fericire + delta);
        std::cout << "SUCCES: Proiect rezidential '" << amtostr(actiune) << "' finalizat.\n";
        return true;
    }

    if (actiune == Amanunte::IMBUNATATIRE) {
        if (!zona_tinta->modifica_rezidentiala(id_tinta, std::move(cr))) {
            buget_curent += p.get_cost_estimat();
            throw ExceptieIDInexistent(id_tinta);
        }
        indice_fericire = clamp01(indice_fericire + delta);
        std::cout << "SUCCES: Proiect rezidential '" << amtostr(actiune) << "' finalizat.\n";
        return true;
    }

    if (!zona_tinta->stergere_rezidentiala(id_tinta)) {
        buget_curent += p.get_cost_estimat();
        throw ExceptieIDInexistent(id_tinta);
    }
    indice_fericire = clamp01(indice_fericire + delta);
    std::cout << "SUCCES: Proiect rezidential '" << amtostr(actiune) << "' finalizat.\n";
    return true;
}


bool Oras::implementare_proiect_public(const Proiect& p,
                                       std::unique_ptr<CladirePublica> cp,
                                       const std::string& nume_zona_proiect) {
    if (p.get_tip() != Proiecte::PUBLIC) return false;

    if (buget_curent < p.get_cost_estimat())
        throw ExceptieBugetInsuficient(buget_curent, p.get_cost_estimat());

    Zona* zona_tinta = cautare_zona(nume_zona_proiect);
    if (!zona_tinta)
        throw ExceptieZonaInexistenta(nume_zona_proiect);

    if (!cp)
        throw ExceptieDateInvalide("implementare_proiect_public: cp null");

    const Amanunte actiune = p.get_detalii();
    const int id_tinta = cp->get_ID();

    const double delta = cp->impact_fericire(actiune);

    buget_curent -= p.get_cost_estimat();

    if (actiune == Amanunte::DE_LA_ZERO) {
        zona_tinta->adauga_cladire_publica(std::move(cp));
        indice_fericire = clamp01(indice_fericire + delta);
        std::cout << "SUCCES: Proiect public '" << amtostr(actiune) << "' finalizat.\n";
        return true;
    }

    if (actiune == Amanunte::IMBUNATATIRE) {
        if (!zona_tinta->modifica_publica(id_tinta, std::move(cp))) {
            buget_curent += p.get_cost_estimat();
            throw ExceptieIDInexistent(id_tinta);
        }
        indice_fericire = clamp01(indice_fericire + delta);
        std::cout << "SUCCES: Proiect public '" << amtostr(actiune) << "' finalizat.\n";
        return true;
    }

    if (!zona_tinta->stergere_publica(id_tinta)) {
        buget_curent += p.get_cost_estimat();
        throw ExceptieIDInexistent(id_tinta);
    }
    indice_fericire = clamp01(indice_fericire + delta);
    std::cout << "SUCCES: Proiect public '" << amtostr(actiune) << "' finalizat.\n";
    return true;
}




void Oras::simulare_luna() {
    std::cout << "\n>>> SIMULARE LUNA... <<<\n";
    const double cost_lunar = calcul_cost_intretinere_total();
    const double venit_lunar = calcul_incasari_totale();

    std::cout << "Cost intretinere lunar: " << cost_lunar << " RON\n";
    std::cout << "Venit lunar (taxe+chirii): " << venit_lunar << " RON\n";

    const double sold = venit_lunar - cost_lunar;
    buget_curent += sold;

    if (buget_curent < 0) indice_fericire = clamp01(indice_fericire - 0.05);
    else if (sold < 0)    indice_fericire = clamp01(indice_fericire - 0.01);
    else                  indice_fericire = clamp01(indice_fericire + 0.01);

    std::cout << "Sold lunar: " << sold
              << " RON.\nBuget nou: " << buget_curent
              << " RON.\nFericire noua: " << (indice_fericire * 100) << "%\n";
}

const std::vector<Zona>& Oras::get_zone() const {
    return zone;
}

bool Oras::sterge_zona(const std::string& nume) {
    for (auto it = zone.begin(); it != zone.end(); ++it) {
        if (it->get_nume() == nume) {
            zone.erase(it);
            return true;
        }
    }
    return false;
}


std::ostream& operator<<(std::ostream& os, const Oras& o) {
    os << "========================================\n";
    os << "Raportul orasului: " << o.nume_oras << "\n";
    os << "========================================\n";
    os << "Buget Curent: " << o.buget_curent << " RON\n";
    os << "Indice Fericire: " << (o.indice_fericire * 100) << "%\n";
    os << "----------------------------------------\n";
    os << "Zone (" << o.zone.size() << "):\n\n";
    if (o.zone.empty()) {
        os << "(Orasul este gol)\n";
    } else {
        for (const Zona& z : o.zone) {
            os << z << "\n";
        }
    }
    os << "========================================\n";
    return os;
}
