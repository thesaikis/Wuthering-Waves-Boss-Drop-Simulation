#include "drop_calc.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

drops_t simulate_one_boss(double drop_prob, unsigned int times, double first_time_unit) {
    drops_t res = {0};
    bool do_pity = false;

    for (unsigned int i = 0; i < times; i++) {
        double roll = (double)rand() / RAND_MAX;
        res.times_first++;
        res.time_units += first_time_unit;

        if (roll < drop_prob || do_pity) {
            res.first_boss_drops += 1;
            do_pity = false;
        } else {
            do_pity = true;
        }
    }

    return res;
}

drops_t simulate_two_boss(double drop_prob, unsigned int times, double first_time_unit, double second_time_unit) {
    drops_t res = {0};
    int target_boss = 1;  // 0 for boss one, 1 for boss two
    bool do_pity = false;

    for (unsigned int i = 0; i < times; i++) {
        double roll = (double)rand() / RAND_MAX;
        if (target_boss == 0) {
            res.times_first++;
            res.time_units += first_time_unit;
        } else {
            res.times_second++;
            res.time_units += second_time_unit;
        }

        if (roll < drop_prob || do_pity) {
            if (target_boss == 0) {
                res.first_boss_drops += 1;
                target_boss = 1;
            } else
                res.second_boss_drops += 1;

            do_pity = false;
        } else {
            target_boss = !target_boss;  // Swap from 0 to 1, or 1 to 0
            do_pity = true;
        }
    }

    return res;
}