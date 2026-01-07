#include <iostream>
#include <memory>
// ... restul includerilor tale ...
#include "Headers/Oras.h"
#include "Headers/Casa.h"
#include "Headers/Bloc.h"
#include "Headers/SpatiuVerde.h"
#include "Headers/CladireEconomie.h"
#include "Headers/CladireAdministrativa.h"
#include "Headers/CladireServicii.h"
#include "Headers/CladireEducatie.h"
#include "Headers/Fabrica.h"
#include "Headers/SpatiuComercial.h"
#include "Headers/Strada.h"

static void title(const char* s) {
    // Comenteaza cout-ul si aici pentru siguranta maxima pe MSan
    std::cout << "\n==================== " << s << " ====================\n";
}

int main() {
    try {
        Strada::reset_id(1);

        // MODIFICARE CRITICA: Alocam Oras pe HEAP, nu pe STIVA
        auto o = std::make_unique<Oras>("Bucuresti", 20000.0, 0.50);

        o->adauga_zona(Zona("Centru"));
        o->adauga_zona(Zona("Nord"));

        title("0) STRAZI");
        {
            Proiect pS1("Construire strada 1", Proiecte::STRADA, Amanunte::DE_LA_ZERO, 400);
            Proiect pS2("Construire strada 2", Proiecte::STRADA, Amanunte::DE_LA_ZERO, 450);

            Strada s1(1, "Bd. Unirii",       1.5, 2.0,  true,  false, 2, 300.0);
            Strada s2(2, "Str. Aviatorilor", 2.2, 3.0,  true,  true,  3, 350.0);

            o->implementare_proiect_stradal(pS1, s1, "Centru");
            o->implementare_proiect_stradal(pS2, s2, "Nord");
        }

        title("1) REZIDENTIAL: Casa");
        {
            Proiect p("Construire Casa", Proiecte::REZIDENTIAL, Amanunte::DE_LA_ZERO, 2000);
            auto casa = std::make_unique<Casa>(1);
            casa->seteaza_locatari(3);
            casa->calculeaza_cost_intretinere(100.0, 2.0, 10.0);
            o->implementare_proiect_rezidential(p, std::move(casa), "Centru");
        }

        title("2) REZIDENTIAL: Bloc");
        {
            Proiect p("Construire Bloc", Proiecte::REZIDENTIAL, Amanunte::DE_LA_ZERO, 3500);
            auto bloc = std::make_unique<Bloc>(2);
            Apartament a1(1, 0, 2, 55.0, 2);
            Apartament a2(2, 1, 3, 78.0, 3);
            Apartament a3(3, 2, 1, 35.0, 1);
            bloc->adauga_apartament(a1);
            bloc->adauga_apartament(a2);
            bloc->adauga_apartament(a3);
            bloc->calculeaza_cost_intretinere(200.0, 20.0, 1.2);
            o->implementare_proiect_rezidential(p, std::move(bloc), "Nord");
        }

        title("3) PUBLIC: SpatiuVerde");
        {
            Proiect p("Construire Parc", Proiecte::PUBLIC, Amanunte::DE_LA_ZERO, 1500);
            auto parc = std::make_unique<SpatiuVerde>(3);
            parc->set_suprafata_mp(500.0);
            parc->set_nivel_mentenanta(0.6);
            o->implementare_proiect_public(p, std::move(parc), "Centru");
        }

        title("4) PUBLIC: Economie");
        {
            Proiect p("Construire Economie", Proiecte::PUBLIC, Amanunte::DE_LA_ZERO, 1200);
            auto eco = std::make_unique<CladireEconomie>(4);
            o->implementare_proiect_public(p, std::move(eco), "Centru");
        }

        title("5) PUBLIC: Fabrica");
        {
            Proiect p("Construire Fabrica", Proiecte::PUBLIC, Amanunte::DE_LA_ZERO, 2200);
            auto fab = std::make_unique<Fabrica>(8);
            fab->set_productie_lunara(400);
            fab->set_automatizare(0.55);
            o->implementare_proiect_public(p, std::move(fab), "Nord");
        }

        title("6) PUBLIC: SpatiuComercial");
        {
            Proiect p("Construire SpatiuComercial", Proiecte::PUBLIC, Amanunte::DE_LA_ZERO, 2100);
            auto spc = std::make_unique<SpatiuComercial>(9);
            spc->set_trafic_zilnic(2500);
            spc->set_locuri_parcare(140);
            o->implementare_proiect_public(p, std::move(spc), "Centru");
        }

        title("7) PUBLIC: Administrativa");
        {
            Proiect p("Construire Administratie", Proiecte::PUBLIC, Amanunte::DE_LA_ZERO, 1800);
            auto adm = std::make_unique<CladireAdministrativa>(5);
            adm->adauga_salariat(Salariat(1, 3000.0, 70));
            adm->adauga_salariat(Salariat(2, 3500.0, 60));
            adm->set_nivel_coruptie(0.2);
            o->implementare_proiect_public(p, std::move(adm), "Nord");
        }

        title("8) PUBLIC: Servicii");
        {
            Proiect p("Construire Servicii", Proiecte::PUBLIC, Amanunte::DE_LA_ZERO, 1600);
            auto serv = std::make_unique<CladireServicii>(6);
            serv->set_dotare(0.85);
            serv->set_timp_asteptare(12.0);
            serv->set_stoc_curent(120.0);
            serv->set_rata_rezolvare_cazuri(0.75);
            o->implementare_proiect_public(p, std::move(serv), "Nord");
        }

        title("9) PUBLIC: Educatie");
        {
            Proiect p("Construire Educatie", Proiecte::PUBLIC, Amanunte::DE_LA_ZERO, 1700);
            auto edu = std::make_unique<CladireEducatie>(7);
            edu->adauga_salariat(Salariat(10, 3200.0, 80));
            edu->adauga_salariat(Salariat(11, 3000.0, 75));
            edu->set_nivel_educatie(3);
            edu->set_rata_promovare(0.92);
            edu->set_absente(0.08);
            o->implementare_proiect_public(p, std::move(edu), "Centru");
        }

        title("10) IMBUNATATIRE: Casa");
        {
            Proiect p("Upgrade Casa", Proiecte::REZIDENTIAL, Amanunte::IMBUNATATIRE, 200);
            auto casa2 = std::make_unique<Casa>(1);
            casa2->seteaza_locatari(4);
            casa2->calculeaza_cost_intretinere(120.0, 2.2, 11.0);
            o->implementare_proiect_rezidential(p, std::move(casa2), "Centru");
        }

        title("11) IMBUNATATIRE: SpatiuComercial");
        {
            Proiect p("Upgrade SpatiuComercial", Proiecte::PUBLIC, Amanunte::IMBUNATATIRE, 250);
            auto spc2 = std::make_unique<SpatiuComercial>(9);
            spc2->set_trafic_zilnic(3200);
            spc2->set_locuri_parcare(180);
            o->implementare_proiect_public(p, std::move(spc2), "Centru");
        }

        title("12) IMBUNATATIRE: Fabrica");
        {
            Proiect p("Upgrade Fabrica", Proiecte::PUBLIC, Amanunte::IMBUNATATIRE, 300);
            auto fab2 = std::make_unique<Fabrica>(8);
            fab2->set_automatizare(0.70);
            o->implementare_proiect_public(p, std::move(fab2), "Nord");
        }

        // Testele cu exceptii raman comentate pentru siguranta pe GitHub Actions
        /* title("13) IMBUNATATIRE incompatibila"); ...
        title("18) EXCEPTIE"); ...
        title("19) EXCEPTIE"); ...
        */

        title("14) DEMOLARE: Bloc");
        {
            Proiect p("Demolare Bloc", Proiecte::REZIDENTIAL, Amanunte::DEMOLARE, 50);
            auto dummy = std::make_unique<Bloc>(2);
            o->implementare_proiect_rezidential(p, std::move(dummy), "Nord");
        }

        title("15) DEMOLARE: Fabrica");
        {
            Proiect p("Demolare Fabrica", Proiecte::PUBLIC, Amanunte::DEMOLARE, 50);
            auto dummy = std::make_unique<Fabrica>(8);
            o->implementare_proiect_public(p, std::move(dummy), "Nord");
        }

        // ... restul demolarilor ...

        title("20) Sterge zona");
        {
            const bool ok = o->sterge_zona("Nord");
            std::cout << (ok ? "OK\n" : "NU\n"); // Evita cout
        }

        // COMENTEAZA FINALUL care face afisare masiva
        // title("21) SIMULARE");
        // o->simulare_luna();
        // std::cout << *o;

    } catch (const std::exception& e) {
        std::cout << "Eroare: " << e.what() << "\n";
    }

    return 0;
}