#include <iostream>
#include <iomanip>
#include <string>

// Include headerele proiectului
#include "Headers/Structuri.h"
#include "Headers/Proiect.h"
#include "Headers/Zona.h"
#include "Headers/Oras.h"

// --- CONSTANTE DE TESTARE ---
constexpr double COST_PROIECT_NOU = 50000.00;
constexpr double COST_IMBUNATATIRE = 15000.00;
constexpr double COST_DEMOLARE = 5000.00;
constexpr double BUGET_START = 100000.00;


int main() {
    std::cout << std::fixed << std::setprecision(2);
    std::cout << "================================================\n";
    std::cout << ">>> SCENARIU TESTARE: ADĂUGARE/DEMOLARE/MODIFICARE <<<\n";
    std::cout << "================================================\n";

    // --- 1. INITIALIZARE STATICA (Macheta Oras) ---
    Strada str_principala(100, "Bd. Unirii", 50000.0, 1000.0, true, false, 4, 2500.0);
    CladireRezidentiala bloc_a1(200, "Bloc A1", 100000.0, 500.0, CladiriRezidentiale::BLOC, 70.0, 4, 120);
    CladirePublica spital_jud(300, "Spital Judetean", 300000.0, 8000.0, CladiriPublice::SPITAL, 250, true);

    Zona zona_centru("Centru");
    zona_centru.adauga_strada(str_principala);
    zona_centru.adauga_cladire_publica(spital_jud);
    Zona zona_rezidentiala("Cartier Sud");
    zona_rezidentiala.adauga_cladire_rezidentiala(bloc_a1);

    Oras simCity("SimCity Test", BUGET_START, 0.75);
    simCity.adauga_zona(zona_centru);
    simCity.adauga_zona(zona_rezidentiala);

    std::cout << "Buget initial: " << simCity.get_buget() << " RON.\n";
    std::cout << "----------------------------------------\n";


    // =============================================================
    // I. TESTARE LOGICĂ STRADALĂ (ID 100)
    // =============================================================
    std::cout << "\n--- TESTARE STRADAL (ID 100) ---\n";

    // 1. ADĂUGARE (DE_LA_ZERO) - FAIL (Buget insuficient)
    Proiect p_str_noua("Strada Noua", Proiecte::STRADA, Amanunte::DE_LA_ZERO, 150000.0, 0);
    Strada str_test_noua(150, "Aleea Noua", 0.0, 200.0, false, true, 2, 500.0);
    if (!simCity.implementare_proiect_stradal(p_str_noua, str_test_noua, "Centru")) {
        std::cout << "1. Adaugare: ESEC (Buget insuficient, AȘTEPTAT).\n";
    }

    // 2. ÎMBUNĂTĂȚIRE (IMBUNATATIRE)
    Proiect p_str_imb("Imbunatatire Bd. Unirii", Proiecte::STRADA, Amanunte::IMBUNATATIRE, COST_IMBUNATATIRE, 100);
    Strada str_imbunatatita(100, "", 0.0, 500.0, true, false, 6, 2500.0); // Cost intretinere nou 500
    std::cout << "2. Imbunatatire: ";
    if(simCity.implementare_proiect_stradal(p_str_imb, str_imbunatatita, "Centru")) {
         std::cout << "SUCCES. (Intretinere Bd. Unirii ar trebui sa fie 500.00 RON).\n";
    }

    // 3. DEMOLARE (DEMOLARE)
    Proiect p_str_dem("Demolare Bd. Unirii", Proiecte::STRADA, Amanunte::DEMOLARE, COST_DEMOLARE, 100);
    std::cout << "3. Demolare: ";
    if(simCity.implementare_proiect_stradal(p_str_dem, Strada(), "Centru")) {
         std::cout << "SUCCES. (Strada 100 eliminata).\n";
    }

    // =============================================================
    // II. TESTARE LOGICĂ PUBLICĂ (ID 300)
    // =============================================================
    std::cout << "\n--- TESTARE PUBLIC (ID 300) ---\n";

    // 1. ADĂUGARE (DE_LA_ZERO) - FAIL (pentru a avea un buget curat)
    Proiect p_pub_noua("Primarie", Proiecte::PUBLIC, Amanunte::DE_LA_ZERO, 10000.0);
    CladirePublica primarie(500, "Primaria", 0.0, 1000.0, CladiriPublice::CLADIRE_BIROURI, 200, false);
    if (simCity.implementare_proiect_public(p_pub_noua, primarie, "Centru")) {
         std::cout << "1. Adaugare: SUCCES (Primărie adaugata).\n";
    }

    // 2. ÎMBUNĂTĂȚIRE (IMBUNATATIRE)
    Proiect p_pub_imb("Eficientizare Spital", Proiecte::PUBLIC, Amanunte::IMBUNATATIRE, COST_IMBUNATATIRE, 300);
    CladirePublica spital_imb(300, "Spital Judetean", 0, 1000.0, CladiriPublice::SPITAL, 300, true); // Cost intretinere nou 1000, capacitate 300
    std::cout << "2. Imbunatatire: ";
    if(simCity.implementare_proiect_public(p_pub_imb, spital_imb, "Centru")) {
         std::cout << "SUCCES. (Intretinere Spital ar trebui sa fie 1000.00 RON).\n";
    }

    // 3. DEMOLARE (DEMOLARE)
    Proiect p_pub_dem("Demolare Spital", Proiecte::PUBLIC, Amanunte::DEMOLARE, COST_DEMOLARE, 300);
    std::cout << "3. Demolare: ";
    if(simCity.implementare_proiect_public(p_pub_dem, CladirePublica(), "Centru")) {
         std::cout << "SUCCES. (Spital 300 eliminat).\n";
    }

    // --- 5. AFISARE STARE FINALĂ ---
    std::cout << "\n--- STARE FINALĂ (Buget: " << simCity.get_buget() << " RON) ---\n";
    std::cout << simCity;

    return 0;
}