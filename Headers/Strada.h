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

    static int next_id;
    static int gen_id();

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


    // operator<<
    friend std::ostream& operator<<(std::ostream& os, const Strada& s);
};

#endif //OOP_STRUCTURI_H