//
// Created by flint on 1/5/2026.
//

#include "Apartament.h"
#include "ExceptieOras.h"

Apartament::Apartament(const int id_, const int camere_, const int locatari_)
    : id(id_), camere(camere_), locatari(locatari_) {

    if (id < 0) throw ExceptieDateInvalide("Apartament: id negativ");
    if (camere <= 0) throw ExceptieDateInvalide("Apartament: camere <= 0");
    if (locatari < 0) throw ExceptieDateInvalide("Apartament: locatari negativi");

}

int Apartament::get_locatari() const { return locatari; }

void Apartament::seteaza_locatari(int x) {
    if (x < 0) x = 0;
    locatari = x;
}