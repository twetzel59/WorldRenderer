#ifndef DAYNIGHT_HPP_INCLUDED
#define DAYNIGHT_HPP_INCLUDED

class DayNight {
    private:
        //Inverse relationship. Higher value for shorter day
        static constexpr float k_day_length_multiplier = 0.15;

        double m_uptime;
    public:
        struct DayLight {
            float light;
            float goldenness;

            DayLight(float l, float g)
                :   light(l),
                    goldenness(g)
                {}
        };

        DayNight() : m_uptime(0.0) {}

        DayLight getDaylight() const;

        inline void update(double uptime) { m_uptime = uptime; }
};

#endif // DAYNIGHT_HPP_INCLUDED
