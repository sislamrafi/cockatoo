#ifndef __KALMAN_H__
#define __KALMAN_H__

#include "../libs/mpu6050/mpu6050.h"


typedef struct {
    double roll;
    double pitch;
    double yaw;
} Angle_t;

void get_angles_complementary(Angle_t* angle);



#endif

