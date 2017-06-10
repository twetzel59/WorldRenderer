#include "daynight.hpp"
#include <iostream>
#include <algorithm>
#include <cmath>
#include <glm/trigonometric.hpp>

auto DayNight::getDaylight() const -> DayLight {
    float light = std::sin(m_uptime * k_day_length_multiplier);
    float goldenness = 0.0f;

    if(light < -0.5f) {
        light = -0.5f;
    } else if(light > 0.5f) {
        light = 0.5f;
    } else {
        std::cout << "light: " << light << '\n';
        goldenness = 0.5f - light;
    }

    light *= 2.0f;

    return DayLight(light, goldenness);
}
