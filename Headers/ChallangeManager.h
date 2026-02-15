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

    int m_maxLuni = 24;
    double m_tintaFericire = 0.80;
    double m_bugetMinim = 0.0;

public:
    ChallengeManager(const ChallengeManager&) = delete;
    void operator=(const ChallengeManager&) = delete;

    static ChallengeManager& getInstance() {
        static ChallengeManager instance;
        return instance;
    }

    // cppcheck-suppress unusedFunction
    static std::string getTitle() { return "SCENARIU: SALVEAZA ORASUL!"; }

    // cppcheck-suppress unusedFunction
    static std::string getDescription() {
        return "Esti primar de criza.\n\n"
               "CONDITII:\n"
               "1. Timp limita: 24 luni\n"
               "2. Tinta Fericire: > 80%\n"
               "3. Buget: Nu intra pe minus!\n\n"
               "Daca nu reusesti, vei fi demis.";
    }

    void update(Oras& oras) const {
        if (oras.get_buget() < m_bugetMinim) {
            oras.set_stare_joc(-1);
            return;
        }

        if (oras.get_luna_curenta() > m_maxLuni) {
            if (oras.get_fericire() < m_tintaFericire) {
                oras.set_stare_joc(-1);
            } else {
                oras.set_stare_joc(1);
            }
            return;
        }

        if (oras.get_fericire() >= m_tintaFericire) {
            oras.set_stare_joc(1);
        }
    }
};

#endif //OOP_CHALLANGEMANAGER_H