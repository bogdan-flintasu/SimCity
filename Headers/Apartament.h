//
// Created by flint on 1/5/2026.
//

#ifndef OOP_APARTAMENT_H
#define OOP_APARTAMENT_H

class Apartament {
private:
    int id{};
    int camere{};
    int locatari{};
public:
    explicit Apartament(int id_ = 0,
                        int camere_ = 1,
                        int locatari_ = 0);

    [[nodiscard]] int get_id() const;
    [[nodiscard]] int get_locatari() const;

    void seteaza_locatari(int x);
};


#endif //OOP_APARTAMENT_H