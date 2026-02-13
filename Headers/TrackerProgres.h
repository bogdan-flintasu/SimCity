//
// Created by flint on 2/13/2026.
//

#ifndef OOP_TRACKERPROGRES_H
#define OOP_TRACKERPROGRES_H

#include <utility>
#include <vector>
#include <iostream>
#include <string>

template <typename T>
class TrackerProgres {
private:
    std::string nume_obiectiv;
    T prag_tinta;
    std::vector<T> istoric_atingeri;
    int contor_consecutiv;

public:
    TrackerProgres(std::string nume, T prag)
        : nume_obiectiv(std::move(nume)), prag_tinta(prag), contor_consecutiv(0) {}

    void inregistreaza_valoare(T valoare_actuala) {
        if (valoare_actuala >= prag_tinta) {
            contor_consecutiv++;
            istoric_atingeri.push_back(valoare_actuala);
        } else {
            contor_consecutiv = 0;
        }
    }

    [[nodiscard]] int get_consecutiv() const { return contor_consecutiv; }
    const std::vector<T>& get_istoric() const { return istoric_atingeri; }

    void reseteaza() {
        contor_consecutiv = 0;
        istoric_atingeri.clear();
    }

    template <typename U>
    friend void afiseaza_raport_tracker(const TrackerProgres<U>& tracker);
};

template <typename T>
void afiseaza_raport_tracker(const TrackerProgres<T>& tracker) {
    std::cout << "[TRACKER] Obiectiv: " << tracker.nume_obiectiv
              << " | Progres consecutiv: " << tracker.contor_consecutiv
              << " | Total atingeri prag: " << tracker.istoric_atingeri.size() << "\n";
}

#endif //OOP_TRACKERPROGRES_H