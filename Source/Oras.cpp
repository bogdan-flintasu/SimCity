//
// Created by flint on 10/28/2025.
//

#include <iostream>
#include <algorithm>
#include "Clamp.h"


#include "../Headers/Oras.h"

#include "Bloc.h"
#include "Casa.h"
#include "ChallangeManager.h"
#include "CladireEducatie.h"
#include "CladireServicii.h"
#include "Fabrica.h"
#include "SpatiuComercial.h"
#include "SpatiuVerde.h"
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

Oras::Oras(std::string nume, const double buget, const double fericire_init)
    : nume_oras(std::move(nume)),
      luni_mandat(1),
      luni_consecutive_excelenta(0),
      stare_joc(0),
      buget_curent(buget),
      indice_fericire(fericire_init),
      buget_initial(buget),
      fericire_initiala(fericire_init),
      luni_fara_proiect(0),
      proiect_implementat_luna_curenta(false)
{}



void swap(Oras& a, Oras& b) noexcept {
    using std::swap;
    swap(a.nume_oras, b.nume_oras);
    swap(a.buget_curent, b.buget_curent);
    swap(a.indice_fericire, b.indice_fericire);
    swap(a.zone, b.zone);
}

double Oras::get_buget() const {
    return buget_curent;
}

int Oras::get_populatie() const {
    int total_oras = 0;
    for (const auto& zona : zone) {
        total_oras += zona.calcul_populatie_zona();
    }
    return total_oras;
}

double Oras::get_fericire() const {
    return indice_fericire;
}

bool Oras::get_proiect_implementat() const {
    return proiect_implementat_luna_curenta;
}

int Oras::get_luna_curenta() const {
    return luni_mandat;
}

int Oras::get_luni_excelenta() const {
    return luni_consecutive_excelenta;
}

int Oras::get_stare_joc() const {
    return stare_joc;
}

void Oras::set_proiect_implementat() {
    proiect_implementat_luna_curenta = true;
}

void Oras::set_nume(const std::string& nume) {
    this -> nume_oras = nume;
}

void Oras::set_stare_joc(const int stare) {
    this -> stare_joc = stare;
}


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




bool Oras::implementare_proiect_stradal(const Proiect& p, const Strada& s, const std::string& nume_zona_proiect) {
    if (p.get_tip() != Proiecte::STRADA) return false;

    Zona* zona_tinta = cautare_zona(nume_zona_proiect);
    if (zona_tinta == nullptr) throw ExceptieZonaInexistenta(nume_zona_proiect);

    const Amanunte actiune = p.get_detalii();
    double cost_final = p.get_cost_estimat();

    if (actiune == Amanunte::DEMOLARE ) {
        cost_final = cost_final * 0.25;
    }

    if (buget_curent < cost_final)
        throw ExceptieBugetInsuficient(buget_curent, cost_final);

    if (actiune == Amanunte::DE_LA_ZERO) {
        buget_curent -= cost_final;
        zona_tinta->adauga_strada(s);
        indice_fericire = std::min(1.0, indice_fericire + 0.02);
    }
    else if (actiune == Amanunte::DEMOLARE) {
        if (zona_tinta->stergere_strada(s.get_ID())) {
            buget_curent -= cost_final;
            indice_fericire = std::max(0.0, indice_fericire - 0.03);
        } else {
            throw ExceptieIDInexistent(s.get_ID());
        }
    }

    std::cout << "SUCCES: Proiect stradal '" << amtostr(actiune) << "'. Cost: " << cost_final << "\n";
    return true;
}


bool Oras::implementare_proiect_rezidential(const Proiect& p,
                                            std::unique_ptr<CladireRezidentiala> cr,
                                            const std::string& nume_zona_proiect) {
    if (p.get_tip() != Proiecte::REZIDENTIAL) return false;

    Zona* zona_tinta = cautare_zona(nume_zona_proiect);
    if (!zona_tinta) throw ExceptieZonaInexistenta(nume_zona_proiect);

    const Amanunte actiune = p.get_detalii();

    int id_tinta = (actiune == Amanunte::DEMOLARE) ? p.get_id_tinta() : (cr ? cr->get_ID() : -1);

    const double delta = (cr && actiune != Amanunte::DEMOLARE) ? cr->impact_fericire(actiune) : 0.0;

    double cost_final = p.get_cost_estimat();
    if (actiune == Amanunte::DEMOLARE) {
        cost_final = cost_final * 0.25;
    }

    if (buget_curent < cost_final)
        throw ExceptieBugetInsuficient(buget_curent, cost_final);

    if (actiune == Amanunte::DE_LA_ZERO) {
        if (!cr) throw ExceptieDateInvalide("implementare_proiect_rezidential: cr null pentru constructie");
        buget_curent -= cost_final;
        zona_tinta->adauga_cladire_rezidentiala(std::move(cr));
        indice_fericire = clamp01(indice_fericire + delta);
    }

    else if (actiune == Amanunte::DEMOLARE) {
        if (zona_tinta->stergere_rezidentiala(id_tinta)) {
            buget_curent -= cost_final;
            indice_fericire = clamp01(indice_fericire - 0.03);
        } else {
            throw ExceptieIDInexistent(id_tinta);
        }
    }

    std::cout << "SUCCES: Proiect rezidential '" << amtostr(actiune) << "'. Cost: " << cost_final << "\n";
    return true;
}


bool Oras::implementare_proiect_public(const Proiect& p,
                                       std::unique_ptr<CladirePublica> cp,
                                       const std::string& nume_zona_proiect) {
    if (p.get_tip() != Proiecte::PUBLIC) return false;

    Zona* zona_tinta = cautare_zona(nume_zona_proiect);
    if (!zona_tinta) throw ExceptieZonaInexistenta(nume_zona_proiect);

    const Amanunte actiune = p.get_detalii();
    int id_tinta = (actiune == Amanunte::DEMOLARE) ? p.get_id_tinta() : (cp ? cp->get_ID() : -1);
    const double delta = (cp && actiune != Amanunte::DEMOLARE) ? cp->impact_fericire(actiune) : 0.0;

    double cost_final = p.get_cost_estimat();
    if (actiune == Amanunte::DEMOLARE) {
        cost_final = cost_final * 0.25;
    }

    if (buget_curent < cost_final)
        throw ExceptieBugetInsuficient(buget_curent, cost_final);

    if (actiune == Amanunte::DE_LA_ZERO) {
        if (!cp) throw ExceptieDateInvalide("implementare_proiect_public: cp null pentru constructie");
        buget_curent -= cost_final;
        if (auto* f = dynamic_cast<Fabrica*>(cp.get())) {
            double bonusAutomatizare = 0.0;
            for (const auto& cladireExistenta : zona_tinta->get_cladiri_publice()) {
                if (dynamic_cast<CladireServicii*>(cladireExistenta.get())) {
                    bonusAutomatizare += 0.15;
                }
            }
            if (bonusAutomatizare > 0) {
                f->set_automatizare(0.5 + bonusAutomatizare);
                std::cout << "Fabrica " << f->get_nume()
                          << " beneficiaza de un spor de eficienta de " << bonusAutomatizare * 100 << "%\n";
            }
        }
        else if (const auto* edu = dynamic_cast<CladireEducatie*>(cp.get())) {
            double bonusRating = 0.0;
            for (const auto& cladireExistenta : zona_tinta->get_cladiri_publice()) {
                if (dynamic_cast<SpatiuVerde*>(cladireExistenta.get())) {
                    bonusRating += 0.5;
                }
            }
            if (bonusRating > 0) {
                std::cout << "Scoala " << edu->get_nume()
                          << " are un rating mai bun datorita parcurilor din jur (+ " << bonusRating << ").\n";
            }
        }
        else if (const auto* sv = dynamic_cast<SpatiuVerde*>(cp.get())) {
            if (const int nrLocuinte = static_cast<int>(zona_tinta->get_cladiri_rezidentiale().size()); nrLocuinte > 3) {
                std::cout << "Parcul " << sv->get_nume()
                          << " ofera un bonus de fericire crescut datorita densitatii zonale!\n";
                indice_fericire = clamp01(indice_fericire + 0.02);
            }
        }
        zona_tinta->adauga_cladire_publica(std::move(cp));
        indice_fericire = clamp01(indice_fericire + delta);
    }

    else if (actiune == Amanunte::DEMOLARE) {
        if (zona_tinta->stergere_publica(id_tinta)) {
            buget_curent -= cost_final;
            indice_fericire = clamp01(indice_fericire + delta);
        } else {
            throw ExceptieIDInexistent(id_tinta);
        }
    }

    std::cout << "SUCCES: Proiect public '" << amtostr(actiune) << "'. Cost: " << cost_final << "\n";
    return true;
}

void Oras::simulare_luna() {
    std::cout << "\n>>> SIMULARE LUNA... <<<\n";
    luni_mandat++;

    istoricBuget.inregistreaza(luni_mandat, buget_curent);

    if (indice_fericire <= 0.001) {
        stare_joc = -1;
        std::cout << "\n=== GAME OVER ===\nCetatenii s-au revoltat (Fericire 0%). Ai fost demis!\nVor avea loc alegeri anticipate. Mai candidezi?\n";
        std::cout << genereaza_raport_final();
    }
    else if (luni_consecutive_excelenta >= 6) {
        stare_joc = 1;
        std::cout << "\n=== VICTORIE! ===\nAi castigat admiratia locuitorilor! Orasul te iubeste.\n";
        std::cout << genereaza_raport_final();
    }
    else if (luni_mandat > 48) {
        stare_joc = -1;
        std::cout << "\n=== GAME OVER ===\nMandatul s-a terminat (4 ani) fara rezultate notabile.\nVor avea loc noi alegeri. Mai candidezi?\n";
        std::cout << genereaza_raport_final();
    }

    std::cout << "Luna Mandat: " << luni_mandat << "/48\n";

    const double cost_lunar = calcul_cost_intretinere_total();
    const double venit_lunar = calcul_incasari_totale();
    const int masini = calcul_numar_total_masini();

    std::cout << "Masini in oras: " << masini << "\n";
    std::cout << "Cost intretinere lunar: " << cost_lunar << " RON\n";
    std::cout << "Venit lunar (taxe+chirii): " << venit_lunar << " RON\n";

    const double sold = venit_lunar - cost_lunar;
    buget_curent += sold;

    if (buget_curent < 0) indice_fericire -= 0.05;
    else if (sold < 0) indice_fericire -= 0.01;
    else indice_fericire += 0.01;

    if (proiect_implementat_luna_curenta) {
        luni_fara_proiect = 0;
        proiect_implementat_luna_curenta = false;

        std::cout << "Proiect implementat! Cetatenii apreciaza activitatea.\n";
    }
    else {
        luni_fara_proiect++;
        const double penalizare = 0.02 * luni_fara_proiect;
        indice_fericire -= penalizare;

        std::cout << "Niciun proiect luna asta (" << luni_fara_proiect
                  << " la rand). Fericirea scade cu " << penalizare << ".\n";
    }

    indice_fericire = clamp01(indice_fericire);

    if (stare_joc == 0) {
        ChallengeManager::getInstance().update(*this);
    }

    std::cout << "Sold lunar: " << sold
              << " RON.\nBuget nou: " << buget_curent
              << " RON.\nFericire noua: " << (indice_fericire * 100) << "%\n";
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

void Oras::reset() {
    std::cout << "Se reseteaza orasul la valorile initiale...\n";

    this->buget_curent = this->buget_initial;
    this->indice_fericire = this->fericire_initiala;

    this->luni_mandat = 1;
    this->luni_consecutive_excelenta = 0;
    this->stare_joc = 0;
    this->luni_fara_proiect = 0;
    this->proiect_implementat_luna_curenta = false;
    this->istoricBuget.reset();

    this->zone.clear();
}

void Oras::incarca_preset_challenge() {
    reset();

    nume_oras = "Faliment Total";
    buget_curent = 25000.0;
    indice_fericire = 0.15;

    buget_initial = 25000.0;
    fericire_initiala = 0.15;

    Zona zInd("Zona Industriala");

    auto f1 = std::make_unique<Fabrica>(0, "Otelaria Veche", 15000, 35000, 6000, 500, false, 95.0, 15.0, 1000);
    zInd.adauga_cladire_publica(std::move(f1));

    auto f2 = std::make_unique<Fabrica>(1, "Textila Falimentara", 8000, 15000, 2000, 200, false, 40.0, 5.0, 500);
    zInd.adauga_cladire_publica(std::move(f2));

    auto f3 = std::make_unique<Fabrica>(2, "Uzina Chimica", 20000, 40000, 8000, 300, true, 99.0, 40.0, 800);
    zInd.adauga_cladire_publica(std::move(f3));

    zInd.adauga_strada(Strada(0, "Bd. Fumului", 5000, 2000, false, false, 4, 2000));
    zInd.adauga_strada(Strada(1, "Str. Depozitului", 2000, 1000, true, false, 2, 1000));

    zone.push_back(std::move(zInd));
    Zona zRez("Cartierul Speranta");

    zRez.adauga_strada(Strada(0, "Aleea Blocului", 1000, 500, true, true, 1, 500));
    zRez.adauga_strada(Strada(1, "Bd. Tineretului", 3000, 1500, false, true, 2, 1500));

    for(int i=0; i<6; ++i) {
        auto b = std::make_unique<Bloc>(i, "Bloc Parasit " + std::to_string(i+1), 4000, 2500, 2);
        zRez.adauga_cladire_rezidentiala(std::move(b));
    }

    zRez.adauga_cladire_rezidentiala(std::make_unique<Casa>(6, "Casa 1", 1000, 800, 1, 1));
    zRez.adauga_cladire_rezidentiala(std::make_unique<Casa>(7, "Casa 2", 1000, 800, 1, 1));

    zone.push_back(std::move(zRez));


    Zona zCom("Centrul Vechi");

    zCom.adauga_strada(Strada(0, "Calea Victoriei", 4000, 2000, false, true, 2, 1000));

    auto mall = std::make_unique<SpatiuComercial>(0, "Mall Parasit", 10000, 20000, 50, 100, 80, 2500, 200);
    zCom.adauga_cladire_publica(std::move(mall));

    auto piata = std::make_unique<SpatiuComercial>(1, "Piata Centrala", 2000, 2000, 100, 20, 50, 800, 20);
    zCom.adauga_cladire_publica(std::move(piata));

    zone.push_back(std::move(zCom));

    std::cout << "[CHALLENGE] Scenariul APOCALIPSA FINANCIARA a fost incarcat.\n";
}

std::string Oras::genereaza_raport_final() const {
    std::string raport = "--- REZUMATUL EVOLUTIEI ORASULUI ---\n\n";
    const auto date = istoricBuget.get_istoric();

    if (date.empty()) {
        return raport + "Nu exista date inregistrate.";
    }

    for (const auto&[fst, snd] : date) {
        raport += "Luna " + std::to_string(fst) +
                  ": " + std::to_string(static_cast<int>(snd)) + " EUR\n";
    }

    const double initial = date.front().second;
    const double final = date.back().second;
    const double profit = final - initial;

    raport += "\n-----------------------------------\n";
    raport += "Evolutie totala: " + std::to_string(static_cast<int>(profit)) + " EUR";

    return raport;
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
