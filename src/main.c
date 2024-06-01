#include <getopt.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#include "drop_calc.h"

#define DEFAULT_PROB 0.2
#define TIME_TO_SIM (int)1e6
#define FIRST_TIME_UNITS 1.0
#define SECOND_TIME_UNITS 0.8

typedef struct {
    int func_type;
    union {
        drops_t (*one_boss)(double, unsigned int, double);
        drops_t (*two_boss)(double, unsigned int, double, double);
    };
    double prob;
    unsigned int times;
    double first_time;
    double second_time;
} thread_info_t;

void* thread_calc(void* args) {
    thread_info_t* info = (thread_info_t*)args;
    drops_t* res = malloc(sizeof(drops_t));

    if (info->func_type == 0)
        *res = info->one_boss(info->prob, info->times, info->first_time);
    else
        *res = info->two_boss(info->prob, info->times, info->first_time, info->second_time);

    return res;
}

int main(int argc, char* argv[]) {
    double prob = DEFAULT_PROB;
    int sim_times = TIME_TO_SIM;
    double first_time_units = FIRST_TIME_UNITS;
    double second_time_units = SECOND_TIME_UNITS;
    unsigned int seed = time(NULL);
    int opt;

    while ((opt = getopt(argc, argv, "s:p:f:s:t:")) != -1) {
        switch (opt) {
            case 'r':
                seed = strtoul(optarg, NULL, 10);
                break;
            case 'p':
                prob = atof(optarg);
                break;
            case 'f':
                first_time_units = atof(optarg);
                break;
            case 's':
                second_time_units = atof(optarg);
                break;
            case 't':
                sim_times = atoi(optarg);
                break;
            case '?':
                return -1;
        }
    }

    srand(seed);

    pthread_t thread1, thread2;
    pthread_create(&thread1, NULL, thread_calc,
                   (void*)&(thread_info_t){.func_type = 0,
                                           .one_boss = simulate_one_boss,
                                           .prob = prob,
                                           .times = sim_times,
                                           .first_time = first_time_units});
    pthread_create(&thread2, NULL, thread_calc,
                   (void*)&(thread_info_t){.func_type = 1,
                                           .two_boss = simulate_two_boss,
                                           .prob = prob,
                                           .times = sim_times,
                                           .first_time = first_time_units,
                                           .second_time = second_time_units});

    drops_t one_boss, two_boss;
    void* res;

    pthread_join(thread1, &res);
    one_boss = *(drops_t*)res;
    free(res);
    pthread_join(thread2, &res);
    two_boss = *(drops_t*)res;
    free(res);

    printf("Farming one boss dropped %d/%d -> %.2f%%\n", one_boss.first_boss_drops, one_boss.times_first,
           (double)one_boss.first_boss_drops / sim_times * 100);
    printf("Over a period of %.2f time units\n", one_boss.time_units);
    printf("- Resulting in %.2f time units spent per main boss drop\n\n",
           one_boss.time_units / one_boss.first_boss_drops);

    printf("Farming two bosses dropped %d, %d\nResulting in overall drop rate: %.2f%%\n", two_boss.first_boss_drops,
           two_boss.second_boss_drops,
           (double)(two_boss.first_boss_drops + two_boss.second_boss_drops) / sim_times * 100);
    printf("First boss drop rate %d/%d -> %.2f%%\n", two_boss.first_boss_drops, two_boss.times_first,
           (double)two_boss.first_boss_drops / two_boss.times_first * 100);
    printf("Second boss drop rate %d/%d -> %.2f%%\n", two_boss.second_boss_drops, two_boss.times_second,
           (double)two_boss.second_boss_drops / two_boss.times_second * 100);
    printf("Over a total period of %.2f time units\n", two_boss.time_units);
    printf("- Resulting in %.2f time units spent per main boss drop\n",
           two_boss.time_units / two_boss.first_boss_drops);
    printf("- And %.2f time units spent per secondary boss drop\n", two_boss.time_units / two_boss.second_boss_drops);
    printf("- But %.2f time units for any boss drop\n",
           two_boss.time_units / (two_boss.first_boss_drops + two_boss.second_boss_drops));

    return 0;
}