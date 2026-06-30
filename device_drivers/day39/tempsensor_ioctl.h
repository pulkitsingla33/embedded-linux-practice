#ifndef TEMPSENSOR_IOCTL_H
#define TEMPSENSOR_IOCTL_H

#include <linux/ioctl.h>
#include <linux/types.h>

#define TEMPSENSOR_MAGIC 't'
#define TEMPSENSOR_SET_INTERVAL _IOW(TEMPSENSOR_MAGIC, 1, unsigned int)

typedef struct
{
    uint64_t samples_generated;
    uint64_t read_operations;
    uint64_t blocked_reads;
    uint64_t wakeups;
} SensorStats;

#define TEMPSENSOR_GET_STATS    _IOR(TEMPSENSOR_MAGIC, 2, SensorStats)
#define TEMPSENSOR_RESET_STATS  _IO(TEMPSENSOR_MAGIC, 3)

#define TEMPSENSOR_SET_NOISE    _IOW(TEMPSENSOR_MAGIC, 4, unsigned int)

#endif
