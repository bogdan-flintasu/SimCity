#ifndef OOP_TRACKERPROGRES_H
#define OOP_TRACKERPROGRES_H

#include <vector>
#include <utility>

template <typename T, typename U = int>
class TrackerProgres {
private:
    std::vector<std::pair<U, T>> istoric;

public:
    TrackerProgres() = default;

    void inregistreaza(U moment, T valoare) {
        istoric.push_back({moment, valoare});
    }

    T get_ultima_valoare() const {
        if (istoric.empty()) return T{};
        return istoric.back().second;
    }

    const std::vector<std::pair<U, T>>& get_istoric() const {
        return istoric;
    }

    void reset() {
        istoric.clear();
    }
};

#endif