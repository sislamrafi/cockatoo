#ifndef __I2C_H__
#define __I2C_H__


#include "../../../core/stm32f446re/registers/external/peripherals.h"
#include "../../../core/stm32f446re/registers/internal/peripherals.h"

#define I2C_TIMEOUT 10

void I2C_Config(void);
void I2C_Reset();
void I2C_Start(void);
void I2C_Write(uint8_t data);
void I2C_Address(uint8_t address);
void I2C_Stop(void);
void I2C_WriteMulti(uint8_t* data, uint8_t size);
void I2C_Read(uint8_t Address, uint8_t* buffer, uint8_t size);
void MPU_Read(uint8_t Address, uint8_t Reg, uint8_t* buffer, uint8_t size);
void MPU_Write(uint8_t Address, uint8_t Reg, uint8_t Data);

#endif