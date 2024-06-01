#ifndef DROP_CALC_H
#define DROP_CALC_H

typedef struct {
    int first_boss_drops;
    int second_boss_drops;

    int times_first;
    int times_second;

    double time_units;
} drops_t;

drops_t simulate_one_boss(double drop_prob, unsigned int times, double first_time_unit);
drops_t simulate_two_boss(double drop_prob, unsigned int times, double first_time_unit, double second_time_unit);

#endif