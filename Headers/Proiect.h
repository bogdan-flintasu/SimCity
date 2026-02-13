//
// Created by flint on 10/28/2025.
//

#ifndef OOP_PROIECT_H
#define OOP_PROIECT_H

enum class Proiecte {
    STRADA,
    REZIDENTIAL,
    PUBLIC
};

enum class Amanunte {
    DEMOLARE,
    DE_LA_ZERO
};

inline std::string prtostr(Proiecte p) {
    switch (p) {
        case Proiecte::STRADA: return "Strada";
        case Proiecte::REZIDENTIAL: return "Rezidential";
        case Proiecte::PUBLIC: return "Public";
        default: return "Proiect neidentificat";
    }
}


inline std::string amtostr(Amanunte am) {
    switch (am) {
        case Amanunte::DE_LA_ZERO: return "De construit de la zero";
        case Amanunte::DEMOLARE: return "Demolare";
        default: return "Amanunte neidentificate";
    }
}


class Proiect {
private:
    std::string nume_proiect;
    Proiecte tip;
    Amanunte detalii;
    double cost_estimat;
    int id_tinta;
public:
    explicit Proiect(std::string  nume = "", Proiecte tip_ = Proiecte::STRADA, Amanunte det = Amanunte::DE_LA_ZERO, int cost = 0, int tinta = 0);

    Proiect(const Proiect& other);
    Proiect& operator=(const Proiect& other);
    ~Proiect();

    [[nodiscard]] const std::string& get_nume() const;
    [[nodiscard]] Proiecte get_tip() const;
    [[nodiscard]] Amanunte get_detalii() const;
    [[nodiscard]] double get_cost_estimat() const;
    [[nodiscard]] int get_id_tinta() const;

    friend std::ostream& operator<<(std::ostream& os, const Proiect& p);
};

#endif //OOP_PROIECT_H