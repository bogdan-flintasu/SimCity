//
// Created by flint on 10/28/2025.
//

#ifndef OOP_STRUCTURI_H
#define OOP_STRUCTURI_H


#include <string>

class Strada {
private:
    int ID{};
    std::string nume;
    double cost_construire{};
    double cost_intretinere{};
    bool trotuar{};
    bool sens_unic{};
    int numar_benzi{};
    double lungime{};

public:

    // Constructor de initializare
    explicit Strada(int id = 0, std::string  nume_ = "", double cost_c = 0.0, double cost_i = 0.0, bool trot = false, bool unic = false, int nr_benzi = 1, double lung = 14.0);

    // Constructor de copiere
    Strada(const Strada& other);

    // operator=
    Strada& operator=(const Strada& other);

    // Destructor
    ~Strada();

    // getters
    [[nodiscard]] int get_ID() const;
    [[nodiscard]] double get_cost_intretinere() const;
    [[nodiscard]] const std::string& get_nume() const;
    [[nodiscard]] bool get_sens_unic() const;
    [[nodiscard]] double get_lungime() const;
    [[nodiscard]] int get_numar_benzi() const;
    [[nodiscard]] bool get_trotuar() const;

    // operator<<
    friend std::ostream& operator<<(std::ostream& os, const Strada& s);
};

enum class CladiriRezidentiale{
    CASA,
    BLOC
};

class CladireRezidentiala {
private:
    int ID{};
    std::string nume;
    double cost_construire;
    double cost_intretinere;
    CladiriRezidentiale tip; // casa sau bloc
    double suprafata_utila;
    int numar_etaje;
    int numar_locuitori;

public:

    explicit CladireRezidentiala(int id = 0, std::string  nume_ = "", int cost_c = 0, int cost_i = 0,
                                CladiriRezidentiale  tip_ = CladiriRezidentiale::CASA, int suprafata = 0, int etaje = 0 , int locatari = 0);

    CladireRezidentiala(const CladireRezidentiala& other);
    CladireRezidentiala& operator=(const CladireRezidentiala& other);
    ~CladireRezidentiala();

    [[nodiscard]] int get_ID() const;
    [[nodiscard]] double get_cost_intretinere() const;
    [[nodiscard]] const std::string& get_nume() const;
    [[nodiscard]] CladiriRezidentiale get_tip() const;
    [[nodiscard]] double get_suprafata() const;
    [[nodiscard]] int get_numar_locuitori() const;
    [[nodiscard]] int get_numar_etaje() const;

    friend std::ostream& operator<<(std::ostream& os, const CladireRezidentiala& cr);
};

enum class CladiriPublice {
    SCOALA,
    UNIVERSITATE,
    SPITAL,
    POLITIE,
    POMPIERI,
    SPATIU_COMERCIAL,
    CLADIRE_BIROURI,
    PARC,
    BISERICA,
    FABRICA
};

class CladirePublica {
private:
    int ID{};
    std::string nume;
    double cost_construire;
    double cost_intretinere;
    CladiriPublice tip;
    int capacitate_servicii; // nr elevi, nr paturi spital, suprafata m2 pentru parc etc.
    bool inchiriat;

public:
    explicit CladirePublica(int id = 0, std::string  n = "", int cost_c = 0, int cost_i = 0, CladiriPublice  tip_ = CladiriPublice::POMPIERI, int capacitate = 0, bool inchiriat_ = false);

    CladirePublica(const CladirePublica& other);
    CladirePublica& operator=(const CladirePublica& other);
    ~CladirePublica();

    [[nodiscard]] int get_ID() const;
    [[nodiscard]] double get_cost_intretinere() const;
    [[nodiscard]] const std::string& get_nume() const;
    [[nodiscard]] CladiriPublice get_tip() const;
    [[nodiscard]] int get_capacitate() const;
    [[nodiscard]] bool get_inchiriat() const;

    friend std::ostream& operator<<(std::ostream& os, const CladirePublica& cp);
};

#endif //OOP_STRUCTURI_H