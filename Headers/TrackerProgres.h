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

    const std::vector<std::pair<U, T>>& get_istoric() const {
        return istoric;
    }

    void reset() {
        istoric.clear();
    }
};

#endif