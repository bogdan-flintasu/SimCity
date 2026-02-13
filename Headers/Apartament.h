//
// Created by flint on 1/5/2026.
//

#ifndef OOP_APARTAMENT_H
#define OOP_APARTAMENT_H

class Apartament {
private:
    int id{};
    int etaj{};
    int camere{};
    double mp_total{};
    int locatari{};
    bool vacant{true};
public:
    explicit Apartament(int id_ = 0,
                        int etaj_ = 0,
                        int camere_ = 1,
                        double mp_total_ = 0.0,
                        int locatari_ = 0);

    [[nodiscard]] int get_id() const;
    [[nodiscard]] double get_mp_total() const;
    [[nodiscard]] int get_locatari() const;
    [[nodiscard]] bool este_vacant() const;

    void seteaza_locatari(int x);
    void seteaza_vacant(bool v);
};


#endif //OOP_APARTAMENT_H