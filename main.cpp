#include <iomanip>
#include <iostream>
#include <string>

#include "Headers/Strada.h"
#include "Headers/Proiect.h"
#include "Headers/Zona.h"
#include "Headers/Oras.h"
#include "Headers/CladirePublica.h"
#include "Headers/CladireRezidentiala.h"

constexpr double COST_IMBUNATATIRE = 15000.00;
constexpr double COST_DEMOLARE = 5000.00;
constexpr double BUGET_START = 100000.00;

int main() {
    std::cout << std::fixed << std::setprecision(2);
    std::cout << "================================================\n";
    std::cout << ">>> SCENARIU TESTARE COMPLET <<<\n";
    std::cout << "================================================\n";

    // Initializare
    Strada str_principala(100, "Bd. Unirii", 50000.0, 1000.0, true, false, 4, 2500.0);
    CladireRezidentiala bloc_a1(200, "Bloc A1", 100000.0, 500.0, CladiriRezidentiale::BLOC, 70.0, 4, 120);
    CladirePublica spital_jud(300, "Spital Judetean", 300000.0, 8000.0, CladiriPublice::SPITAL, 250, true);
    CladirePublica parc_central(301, "Parcul Central", 80000.0, 500.0, CladiriPublice::PARC, 10000, false);

    Zona zona_centru("Centru");
    zona_centru.adauga_strada(str_principala);
    zona_centru.adauga_cladire_publica(spital_jud);
    zona_centru.adauga_cladire_publica(parc_central);
    Zona zona_rezidentiala("Cartier Sud");
    zona_rezidentiala.adauga_cladire_rezidentiala(bloc_a1);

    Oras simCity("SimCity Test", BUGET_START, 0.75);
    simCity.adauga_zona(zona_centru);
    simCity.adauga_zona(zona_rezidentiala);

    std::cout << "Buget initial: " << simCity.get_buget() << " RON.\n";

    // Testare functii
    std::cout << "\n--- 1. FUNCTII DE CALCUL ȘI STARE ---\n";
    std::cout << "FN #1 (Cost Total): " << simCity.calcul_cost_intretinere_total() << " RON\n";
    std::cout << "FN #2 (Incasari Totale): " << simCity.calcul_incasari_totale() << " RON\n";
    std::cout << "FN #3 (Numar Masini): " << simCity.calcul_numar_total_masini() << " masini\n";
    std::cout << "Fericire Curenta (FN Get): " << simCity.get_fericire() << "\n";

    // Adaugare DE_LA_ZERO
    std::cout << "\n--- 2. TEST ADĂUGARE & DEMOLARE ---\n";
    Proiect p_scoala("Scoala Noua", Proiecte::PUBLIC, Amanunte::DE_LA_ZERO, 10000.0);
    CladirePublica scoala_noua(400, "Scoala Generala 7", 0.0, 100.0, CladiriPublice::SCOALA, 500, false);
    if(simCity.implementare_proiect_public(p_scoala, scoala_noua, "Cartier Sud")) {
         std::cout << "SUCCES: Scoala adaugata.\n";
    }

    // Imbunatatire
    Proiect p_imb_strada("Modernizare Bd. Unirii", Proiecte::STRADA, Amanunte::IMBUNATATIRE, COST_IMBUNATATIRE, 100);
    Strada str_imbunatatita(100, "Bd. Unirii", 0.0, 500.0, true, false, 6, 2500.0);
    if(simCity.implementare_proiect_stradal(p_imb_strada, str_imbunatatita, "Centru")) {
         std::cout << "SUCCES: Strada 100 imbunatatita.\n";
    }

    // Demolare
    Proiect p_dem_bloc("Demolare Bloc A1", Proiecte::REZIDENTIAL, Amanunte::DEMOLARE, COST_DEMOLARE, 200);
    CladireRezidentiala dummy_rez;
    if(simCity.implementare_proiect_rezidential(p_dem_bloc, dummy_rez, "Cartier Sud")) {
         std::cout << "SUCCES: Bloc A1 (ID 200) demolat.\n";
    }

    // Esec
    Proiect p_faliment("Proiect Faliment", Proiecte::REZIDENTIAL, Amanunte::DE_LA_ZERO, 2000000.0);
    if(!simCity.implementare_proiect_rezidential(p_faliment, dummy_rez, "Cartier Sud")) {
         std::cout << "ESEC AȘTEPTAT: Proiect Faliment (Buget insuficient).\n";
    }

    // Simulare luna
    simCity.simulare_luna();

    std::cout << "\n--- STARE FINALĂ A ORASULUI ---\n";
    std::cout << simCity;

    // Afisare copii
    Oras copie_oras = simCity;
    std::cout << "\n--- TEST COPIE (Buget): " << copie_oras.get_buget() << " RON ---\n";

    return 0;
}