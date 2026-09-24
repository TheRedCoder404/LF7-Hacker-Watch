#include "Utility.h"

void Utility::clamp(int& val, int min, int max) {
    if (val < min) {
        val = min;
    }
    if (val > max) {
        val = max;
    }
}
