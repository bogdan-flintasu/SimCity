#include <iomanip>
#include <iostream>
#include <string>

// INCLUDE DEPENDENȚELE PROIECTULUI
#include "Headers/Structuri.h"
#include "Headers/Proiect.h"
#include "Headers/Zona.h"
#include "Headers/Oras.h"

// --- CONSTANTE DE TESTARE ---
// Le folosim pentru a testa funcțiile
constexpr double COST_IMBUNATATIRE = 15000.00;
constexpr double COST_DEMOLARE = 5000.00;
constexpr double BUGET_START = 100000.00;

// Funcție de testare pentru a folosi toți getterii declarați
void testare_getteri_si_setteri(Strada& s, CladireRezidentiala& cr, CladirePublica& cp) {
    std::cout << "\n--- TESTARE GETTERS/SETTERS (Pentru a elimina warnings) ---\n";

    // Strada: Folosim toți getterii
    std::cout << "ID Strada: " << s.get_ID() << ", Nume: " << s.get_nume() << ", Trotuar: " << s.get_trotuar() << std::endl;
    std::cout << "Cost Construire Strada: " << s.get_cost_construire() << ", Lungime: " << s.get_lungime() << std::endl;

    // Strada: Folosim setteri
    s.set_cost_intretinere(200.00);
    s.set_numar_benzi(8);
    s.set_sens(true);
    s.set_trotuar(false);

    // Rezidentiala: Folosim toți getterii
    std::cout << "Etaje Rezid: " << cr.get_numar_etaje() << ", Suprafata: " << cr.get_suprafata() << std::endl;

    // Rezidentiala: Folosim setteri
    cr.set_cost_intretinere(300.00);
    cr.set_numar_locuitori(150);

    // Publica: Folosim setteri
    cp.set_cost_intretinere(100.00);
    cp.set_capacitate(400);
    cp.set_inchiriat(false);

    std::cout << "Starea interna a fost actualizata.\n";
}


int main() {
    std::cout << std::fixed << std::setprecision(2);
    std::cout << "================================================\n";
    std::cout << ">>> SCENARIU TESTARE COMPLET <<<\n";
    std::cout << "================================================\n";

    // --- 1. INITIALIZARE STATICA ---
    // Notă: Folosim variabile non-const pentru a putea folosi setteri
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

    // --- 2. TESTARE GETTERS & SETTERS (Elimină unusedFunction) ---
    testare_getteri_si_setteri(str_principala, bloc_a1, spital_jud);

    // --- 3. TESTARE FUNCTII NETRIVIALE DE CALCUL (FN #1, #2, #3) ---
    std::cout << "\n--- 3. FUNCTII DE CALCUL ȘI STARE ---\n";
    std::cout << "FN #1 (Cost Total): " << simCity.calcul_cost_intretinere_total() << " RON\n";
    std::cout << "FN #2 (Incasari Totale): " << simCity.calcul_incasari_totale() << " RON\n";
    std::cout << "FN #3 (Numar Masini): " << simCity.calcul_numar_total_masini() << " masini\n";
    std::cout << "Fericire Curenta (FN Get): " << simCity.get_fericire() << "\n";


    // --- 4. TESTARE FLUXURI DE PROIECTE (FN #4, #5, #6) ---

    // CAZ A: ADĂUGARE (DE_LA_ZERO) - FN #4
    std::cout << "\n--- 4. TEST ADĂUGARE & DEMOLARE ---\n";
    Proiect p_scoala("Scoala Noua", Proiecte::PUBLIC, Amanunte::DE_LA_ZERO, 10000.0);
    CladirePublica scoala_noua(400, "Scoala Generala 7", 0.0, 100.0, CladiriPublice::SCOALA, 500, false);
    if(simCity.implementare_proiect_public(p_scoala, scoala_noua, "Cartier Sud")) {
         std::cout << "SUCCES: Scoala adaugata.\n";
    }

    // CAZ B: ÎMBUNĂTĂȚIRE (IMBUNATATIRE) - FN #6
    Proiect p_imb_strada("Modernizare Bd. Unirii", Proiecte::STRADA, Amanunte::IMBUNATATIRE, COST_IMBUNATATIRE, 100); // Ținta ID 100
    Strada str_imbunatatita(100, "Bd. Unirii", 0.0, 500.0, true, false, 6, 2500.0); // Date noi: 6 benzi, intretinere 500
    if(simCity.implementare_proiect_stradal(p_imb_strada, str_imbunatatita, "Centru")) {
         std::cout << "SUCCES: Strada 100 imbunatatita.\n";
    }

    // CAZ C: DEMOLARE (DEMOLARE) - FN #5
    Proiect p_dem_bloc("Demolare Bloc A1", Proiecte::REZIDENTIAL, Amanunte::DEMOLARE, COST_DEMOLARE, 200); // Ținta ID 200
    CladireRezidentiala dummy_rez;
    if(simCity.implementare_proiect_rezidential(p_dem_bloc, dummy_rez, "Cartier Sud")) {
         std::cout << "SUCCES: Bloc A1 (ID 200) demolat.\n";
    }

    // CAZ D: ESEC (Buget insuficient, FN #4)
    Proiect p_faliment("Proiect Faliment", Proiecte::REZIDENTIAL, Amanunte::DE_LA_ZERO, 2000000.0);
    if(!simCity.implementare_proiect_rezidential(p_faliment, dummy_rez, "Cartier Sud")) {
         std::cout << "ESEC AȘTEPTAT: Proiect Faliment (Buget insuficient).\n";
    }

    // --- 5. SIMULARE ȘI AFISARE FINALĂ ---
    simCity.simulare_luna(); // Bonus

    std::cout << "\n--- STARE FINALĂ A ORASULUI ---\n";
    std::cout << simCity;

    // Afisare copii (pentru a folosi obiectele create cu Regula Celor Trei)
    Oras copie_oras = simCity;
    std::cout << "\n--- TEST COPIE (Buget): " << copie_oras.get_buget() << " RON ---\n";

    return 0;
}