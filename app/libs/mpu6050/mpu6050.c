#include "mpu6050.h"

#define RAD_TO_DEG 57.295779513082320876798154814105

#define PWR_MGMT_1_REG 0x6B
#define SMPLRT_DIV_REG 0x19
#define ACCEL_CONFIG_REG 0x1C
#define ACCEL_XOUT_H_REG 0x3B
#define TEMP_OUT_H_REG 0x41
#define GYRO_CONFIG_REG 0x1B
#define GYRO_XOUT_H_REG 0x43
#define MPU6050_ADDR 0xD0
const uint16_t i2c_timeout = 100;
const double Accel_Z_corrector = 14418.0;

uint8_t MPU6050_Init() {
    uint8_t check;
    uint8_t Data;

    // check device ID WHO_AM_I
    // HAL_I2C_Mem_Read(MPU6050_ADDR, MPU6050_RA_WHO_AM_I, 1, &check, 1, i2c_timeout);
    MPU_Read(MPU6050_ADDR, MPU6050_RA_WHO_AM_I, &check, 1);

    if (check == 104)  // 0x68 will be returned by the sensor if everything goes well
    {
        // power management register 0X6B we should write all 0's to wake the sensor up
        Data = 0;
        MPU_Write(MPU6050_ADDR, PWR_MGMT_1_REG, Data);

        // Set DATA RATE of 1KHz by writing SMPLRT_DIV register
        Data = 0x07;
        MPU_Write(MPU6050_ADDR, SMPLRT_DIV_REG, Data);

        // Set accelerometer configuration in ACCEL_CONFIG Register
        // XA_ST=0,YA_ST=0,ZA_ST=0, FS_SEL=0 -> ? 2g
        Data = 0x00;
        MPU_Write(MPU6050_ADDR, ACCEL_CONFIG_REG, Data);

        // Set Gyroscopic configuration in GYRO_CONFIG Register
        // XG_ST=0,YG_ST=0,ZG_ST=0, FS_SEL=0 -> ? 250 ?/s
        Data = 0x00;
        MPU_Write(MPU6050_ADDR, GYRO_CONFIG_REG, Data);
    }
    return 1;
}

void MPU6050_Read_Accel(MPU6050_accel_t* data) {
    uint8_t Rec_Data[6];

    // Read 6 BYTES of data starting from ACCEL_XOUT_H register

    // HAL_I2C_Mem_Read(I2Cx, MPU6050_ADDR, ACCEL_XOUT_H_REG, 1, Rec_Data, 6, i2c_timeout);
    MPU_Read(MPU6050_ADDR, ACCEL_XOUT_H_REG, Rec_Data, 6);


    data->Accel_X_RAW = (int16_t)(Rec_Data[0] << 8 | Rec_Data[1]);
    data->Accel_Y_RAW = (int16_t)(Rec_Data[2] << 8 | Rec_Data[3]);
    data->Accel_Z_RAW = (int16_t)(Rec_Data[4] << 8 | Rec_Data[5]);

    /*** convert the RAW values into acceleration in 'g'
         we have to divide according to the Full scale value set in FS_SEL
         I have configured FS_SEL = 0. So I am dividing by 16384.0
         for more details check ACCEL_CONFIG Register              ****/

    data->Ax = data->Accel_X_RAW / 16384.0;
    data->Ay = data->Accel_Y_RAW / 16384.0;
    data->Az = data->Accel_Z_RAW / Accel_Z_corrector;
}

void MPU6050_Read_Gyro(MPU6050_gyro_t* data) {
    uint8_t Rec_Data[6];

    // Read 6 BYTES of data starting from GYRO_XOUT_H register

    // HAL_I2C_Mem_Read(I2Cx, MPU6050_ADDR, GYRO_XOUT_H_REG, 1, Rec_Data, 6, i2c_timeout);
    MPU_Read(MPU6050_ADDR, GYRO_XOUT_H_REG, Rec_Data, 6);

    data->Gyro_X_RAW = (int16_t)(Rec_Data[0] << 8 | Rec_Data[1]);
    data->Gyro_Y_RAW = (int16_t)(Rec_Data[2] << 8 | Rec_Data[3]);
    data->Gyro_Z_RAW = (int16_t)(Rec_Data[4] << 8 | Rec_Data[5]);

    /*** convert the RAW values into dps (rad/s)
         we have to divide according to the Full scale value set in FS_SEL
         I have configured FS_SEL = 0. So I am dividing by 131.0
         for more details check GYRO_CONFIG Register              ****/

    data->Gx = data->Gyro_X_RAW / 131.0;
    data->Gy = data->Gyro_Y_RAW / 131.0;
    data->Gz = data->Gyro_Z_RAW / 131.0;
}

void MPU_Read(uint8_t Address, uint8_t Reg, uint8_t* buffer, uint8_t size)
{
    I2C_Start();
    I2C_Address(Address);
    I2C_Write(Reg);
    I2C_Start();  // repeated start
    I2C_Read(Address + 0x01, buffer, size);
    I2C_Stop();
}

void MPU_Write(uint8_t Address, uint8_t Reg, uint8_t Data)
{
    I2C_Start();
    I2C_Address(Address);
    I2C_Write(Reg);
    I2C_Write(Data);
    I2C_Stop();
}