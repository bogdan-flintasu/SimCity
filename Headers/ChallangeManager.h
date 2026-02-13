//
// Created by flint on 2/12/2026.
//

#ifndef OOP_CHALLANGEMANAGER_H
#define OOP_CHALLANGEMANAGER_H

#pragma once
#include "Oras.h"
#include <string>

class ChallengeManager {
private:
    ChallengeManager() = default;

    // Conditiile scenariului
    int m_maxLuni = 24;            // Ai doar 2 ani (24 luni)
    double m_tintaFericire = 0.80; // Trebuie sa ajungi la 80%
    double m_bugetMinim = 0.0;     // Nu ai voie sa intri pe minus

public:
    ChallengeManager(const ChallengeManager&) = delete;
    void operator=(const ChallengeManager&) = delete;

    static ChallengeManager& getInstance() {
        static ChallengeManager instance;
        return instance;
    }

    // Returneaza textul pentru Pop-up-ul de inceput
    static std::string getTitle() { return "SCENARIU: SALVEAZA ORASUL!"; }

    static std::string getDescription() {
        return "Esti primar de criza.\n\n"
               "CONDITII:\n"
               "1. Timp limita: 24 luni\n"
               "2. Tinta Fericire: > 80%\n"
               "3. Buget: Nu intra pe minus!\n\n"
               "Daca nu reusesti, vei fi demis.";
    }

    // Verifica starea si actualizeaza orasul (Game Over / Win)
    void update(Oras& oras) const {
        // 1. Verificare FAIL: Buget
        if (oras.get_buget() < m_bugetMinim) {
            oras.set_stare_joc(-1); // Pierdut
            return;
        }

        // 2. Verificare FAIL: Timp Expirat
        if (oras.get_luna_curenta() > m_maxLuni) {
            // Daca a expirat timpul si n-ai fericirea necesara -> Pierzi
            if (oras.get_fericire() < m_tintaFericire) {
                oras.set_stare_joc(-1);
            } else {
                oras.set_stare_joc(1); // Castigat la limita
            }
            return;
        }

        // 3. Verificare WIN: Ai atins fericirea inainte de termen!
        if (oras.get_fericire() >= m_tintaFericire) {
            oras.set_stare_joc(1); // Victorie!
        }
    }
};

#endif //OOP_CHALLANGEMANAGER_H