#include <iostream>
#include <memory>

#include "Headers/Oras.h"
#include "Headers/ExceptieOras.h"
#include "Headers/CladireRezidentiala.h"
#include "Headers/CladirePublica.h"

int main() {
     try {
          Oras o("Bucuresti", 10000.0, 0.5);
          o.adauga_zona(Zona("Centru"));

          const Proiect p1("Construire casa", Proiecte::REZIDENTIAL, Amanunte::DE_LA_ZERO, 2000);
          auto casa = std::make_unique<Casa>(0, "Casa1", 1000, 120, 1, 3);
          casa->calculeaza_cost_intretinere(100, 2.0, 10.0);

          o.implementare_proiect_rezidential(p1, std::move(casa), "Centru");

          const Proiect p2("Construire parc", Proiecte::PUBLIC, Amanunte::DE_LA_ZERO, 1500);
          auto parc = std::make_unique<SpatiuVerde>(0, "Parc", 1000, 200, 0, false, 0, 500, 0.6);
          o.implementare_proiect_public(p2, std::move(parc), "Centru");

          // test dynamic_cast / incompatibilitate
          const Proiect p3("Imbunatatire rezidential", Proiecte::REZIDENTIAL, Amanunte::IMBUNATATIRE, 100);
          auto bloc = std::make_unique<Bloc>(0, "BlocX", 1000, 300, 5); // tip diferit fata de casa
          o.implementare_proiect_rezidential(p3, std::move(bloc), "Centru"); // ar trebui sa ajunga in Zona::modifica_rezidentiala daca folosesti id_tinta

          o.simulare_luna();
          std::cout << o;

     } catch (const ExceptieOras& e) {
          std::cout << "Exceptie Oras: " << e.what() << "\n";
     } catch (const std::exception& e) {
          std::cout << "Exceptie std: " << e.what() << "\n";
     }
}
