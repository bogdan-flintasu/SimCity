//
// Created by flint on 10/28/2025.
//

#include <iostream>

#include "../Headers/Oras.h"

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

Oras::Oras(std::string nume, double buget, double fericire_init): nume_oras(std::move(nume)), buget_curent(buget), indice_fericire(fericire_init) {}

Oras::Oras(const Oras& other) = default;

Oras& Oras::operator=(const Oras& other) {
    if (this != &other) {
        nume_oras = other.nume_oras;
        buget_curent = other.buget_curent;
        indice_fericire = other.indice_fericire;
        zone = other.zone;
    }
    return *this;
}

Oras::~Oras() = default;

void Oras::adauga_zona(const Zona& z) { zone.push_back(z); }

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

double calcul_fericire(CladiriPublice tip, Amanunte actiune) {
    if (actiune == Amanunte::DE_LA_ZERO) {
        if (tip == CladiriPublice::FABRICA) return -0.03;
        if (tip == CladiriPublice::BISERICA) return 0.04;
        if (tip == CladiriPublice::SPATIU_COMERCIAL) return 0.08;
        if (tip == CladiriPublice::PARC) return 0.05;
        if (tip == CladiriPublice::SPITAL) return 0.07;
        if (tip == CladiriPublice::CLADIRE_BIROURI) return 0.02;
        if (tip == CladiriPublice::POMPIERI) return 0.03;
        if (tip == CladiriPublice::POLITIE) return 0.02;
        if (tip == CladiriPublice::SCOALA) return 0.02;
        if (tip == CladiriPublice::UNIVERSITATE) return 0.04;
    } else if (actiune == Amanunte::IMBUNATATIRE) {
        if (tip == CladiriPublice::FABRICA) return 0.02;
        if (tip == CladiriPublice::BISERICA) return 0.03;
        if (tip == CladiriPublice::SPATIU_COMERCIAL) return 0.05;
        if (tip == CladiriPublice::PARC) return 0.02;
        if (tip == CladiriPublice::SPITAL) return 0.06;
        if (tip == CladiriPublice::CLADIRE_BIROURI) return 0.01;
        if (tip == CladiriPublice::POMPIERI) return 0.03;
        if (tip == CladiriPublice::POLITIE) return 0.02;
        if (tip == CladiriPublice::SCOALA) return 0.02;
        if (tip == CladiriPublice::UNIVERSITATE) return 0.03;
    } else if (actiune == Amanunte::DEMOLARE) {
        if (tip == CladiriPublice::FABRICA) return 0.04;
        if (tip == CladiriPublice::BISERICA) return -0.07;
        if (tip == CladiriPublice::SPATIU_COMERCIAL) return -0.1;
        if (tip == CladiriPublice::PARC) return -0.07;
        if (tip == CladiriPublice::SPITAL) return -0.08;
        if (tip == CladiriPublice::CLADIRE_BIROURI) return -0.04;
        if (tip == CladiriPublice::POMPIERI) return -0.02;
        if (tip == CladiriPublice::POLITIE) return -0.01;
        if (tip == CladiriPublice::SCOALA) return -0.04;
        if (tip == CladiriPublice::UNIVERSITATE) return -0.05;
    }
    return 0.0;
}

[[nodiscard]] bool Oras::implementare_proiect_stradal(const Proiect& p, const Strada& s, const std::string& nume_zona_proiect) {
    if (p.get_tip() != Proiecte::STRADA) return false;
    if (buget_curent < p.get_cost_estimat()) return false;
    Zona* zona_tinta = cautare_zona(nume_zona_proiect);
    if (zona_tinta == nullptr) return false;

    buget_curent -= p.get_cost_estimat();

    Amanunte actiune = p.get_detalii();
    bool succes = false;

    if (actiune == Amanunte::DE_LA_ZERO) {
        zona_tinta -> adauga_strada(s);
        indice_fericire = std::min(1.0, indice_fericire + 0.02);
        succes = true;
    }
    else if (actiune == Amanunte::DEMOLARE) {
        if (zona_tinta -> stergere_strada(s.get_ID())) {
            indice_fericire = std::max(0.0, indice_fericire - 0.03);
            succes = true;
        }
    }
    else if (actiune == Amanunte::IMBUNATATIRE) {
        if (zona_tinta->modifica_strada(s.get_ID(), s)) {
            indice_fericire = std::min(1.0, indice_fericire + 0.01);
            succes = true;
        }
    }

    if (succes) {
        std::cout << "SUCCES: Proiect stradal '" << amtostr(actiune) << "' finalizat.\n";
    } else {
        buget_curent += p.get_cost_estimat();
        std::cout << "ESEC: Actiunea '" << amtostr(actiune) << "' nu a putut fi efectuata pe ID-ul tintit.\n";
    }

    return succes;
}

[[nodiscard]] bool Oras::implementare_proiect_rezidential(const Proiect& p, const CladireRezidentiala& cr, const std::string& nume_zona_proiect) {
    if (p.get_tip() != Proiecte::REZIDENTIAL) return false;
    if (buget_curent < p.get_cost_estimat()) return false;
    Zona* zona_tinta = cautare_zona(nume_zona_proiect);
    if (zona_tinta == nullptr) return false;

    Amanunte actiune = p.get_detalii();

    buget_curent -= p.get_cost_estimat();
    bool succes = false;

    if (p.get_detalii() == Amanunte::DEMOLARE) {
        if (zona_tinta -> stergere_rezidentiala(cr.get_ID())) {
            if (cr.get_tip() == CladiriRezidentiale::CASA) {
                indice_fericire = std::max(0.0, indice_fericire - 0.01);
            }
            else indice_fericire = std::max(0.0, indice_fericire - 0.05);
            succes = true;
        }
    }
    else if (p.get_detalii() == Amanunte::IMBUNATATIRE) {
        if (zona_tinta -> modifica_rezidentiala(cr.get_ID(), cr)) {
            if (cr.get_tip() == CladiriRezidentiale::CASA) {
                indice_fericire = std::min(1.0, indice_fericire + 0.01);
            }
            else indice_fericire = std::min(1.0, indice_fericire + 0.04);
            succes = true;
        }
    }
    else {
        zona_tinta -> adauga_cladire_rezidentiala(cr);
        if (cr.get_tip() == CladiriRezidentiale::CASA) {
            indice_fericire = std::min(1.0, indice_fericire + 0.02);
        }
        else indice_fericire = std::min(1.0, indice_fericire + 0.04);
        succes = true;
    }

    if (succes) {
        std::cout << "SUCCES: Proiect rezidential '" << amtostr(actiune) << "' finalizat.\n";
    } else {
        buget_curent += p.get_cost_estimat();
        std::cout << "ESEC: Actiunea '" << amtostr(actiune) << "' nu a putut fi efectuata pe ID-ul tintit.\n";
    }

    return succes;
}

[[nodiscard]] bool Oras::implementare_proiect_public(const Proiect& p, const CladirePublica& cp, const std::string& nume_zona_proiect) {
    if (p.get_tip() != Proiecte::PUBLIC) return false;
    if (buget_curent < p.get_cost_estimat()) return false;
    Zona* zona_tinta = cautare_zona(nume_zona_proiect);
    if (zona_tinta == nullptr) return false;

    Amanunte actiune = p.get_detalii();

    buget_curent -= p.get_cost_estimat();
    bool succes = false;

    if (actiune == Amanunte::DEMOLARE) {
        if (zona_tinta -> stergere_publica(cp.get_ID())) {
            succes = true;
        }
    }

    else if (actiune == Amanunte::IMBUNATATIRE) {
        if (zona_tinta -> modifica_publica(cp.get_ID(), cp)) {
            succes = true;
        }
    }

    else {
        zona_tinta -> adauga_cladire_publica(cp);
        succes = true;
    }

    if (succes) {
        std::cout << "SUCCES: Proiect public '" << amtostr(actiune) << "' finalizat.\n";
        double fericire = calcul_fericire(cp.get_tip(), actiune);
        indice_fericire += fericire;
    } else {
        std::cout << "ESEC: Actiunea '" << amtostr(actiune) << "' nu a putut fi efectuata pe ID-ul tintit.\n";
    }

    return succes;
}

void Oras::simulare_luna() {
    std::cout << "\n>>> SIMULARE LUNA... <<<\n";
    double cost_lunar = calcul_cost_intretinere_total();
    double venit_lunar = calcul_incasari_totale();
    std::cout << "Cost intretinere lunar: " << cost_lunar << " RON\n";
    std::cout << "Venit lunar (taxe+chirii): " << venit_lunar << " RON\n";
    double sold = venit_lunar - cost_lunar;
    buget_curent += sold;

    if (buget_curent < 0) indice_fericire = std::max(0.0, indice_fericire - 0.05);
    else if (sold < 0) indice_fericire = std::max(0.0, indice_fericire - 0.01);
    else indice_fericire = std::min(1.0, indice_fericire + 0.01);
    std::cout << "Sold lunar: " << sold << " RON.\nBuget nou: " << buget_curent << " RON.\nFericire noua: " << (indice_fericire*100) << "%\n";
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
