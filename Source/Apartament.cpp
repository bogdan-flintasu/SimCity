//
// Created by flint on 1/5/2026.
//

#include "Apartament.h"
#include "ExceptieOras.h"

Apartament::Apartament(const int id_, const int etaj_, const int camere_, const double mp_total_, const int locatari_)
    : id(id_), etaj(etaj_), camere(camere_), mp_total(mp_total_), locatari(locatari_) {

    if (id < 0) throw ExceptieDateInvalide("Apartament: id negativ");
    if (etaj < 0) throw ExceptieDateInvalide("Apartament: etaj negativ");
    if (camere <= 0) throw ExceptieDateInvalide("Apartament: camere <= 0");
    if (mp_total < 0.0) throw ExceptieDateInvalide("Apartament: mp_total negativ");
    if (locatari < 0) throw ExceptieDateInvalide("Apartament: locatari negativi");

}

int Apartament::get_id() const { return id; }
int Apartament::get_etaj() const { return etaj; }
int Apartament::get_camere() const { return camere; }
double Apartament::get_mp_total() const { return mp_total; }
int Apartament::get_locatari() const { return locatari; }
bool Apartament::este_vacant() const { return vacant; }

void Apartament::seteaza_locatari(int x) {
    if (x < 0) x = 0;
    locatari = x;
}

void Apartament::seteaza_vacant(bool v) {
    vacant = v;
    if (vacant) locatari = 0;
}