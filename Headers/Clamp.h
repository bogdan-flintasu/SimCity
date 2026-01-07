//
// Created by flint on 1/6/2026.
//

#ifndef OOP_CLAMP_H
#define OOP_CLAMP_H

inline double clamp01(const double x) {
    if (x < 0.0) return 0.0;
    if (x > 1.0) return 1.0;
    return x;
}

#endif //OOP_CLAMP_H