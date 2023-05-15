#include "kalman.h"

void get_angles_complementary(Angle_t* angle) {
    MPU6050_gyro_t gyro_data;
    MPU6050_accel_t accel_data;
    MPU6050_Read_Accel(&accel_data);
    MPU6050_Read_Gyro(&gyro_data);

    angle->roll = gyro_data.Gx;
    angle->pitch = gyro_data.Gy;
    angle->yaw = gyro_data.Gz;

}