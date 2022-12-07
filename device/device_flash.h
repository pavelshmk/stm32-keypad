//
// Created by bakatrouble on 09/11/22.
//

#ifndef HAL_DEVICE_FLASH_H
#define HAL_DEVICE_FLASH_H

#include "device.h"

/*----------------------------------------------- 命名参数宏 -------------------------------------------*/

#define QSPI_W25Qxx_OK           		0		// W25Qxx通信正常
#define W25Qxx_ERROR_INIT         		-1		// 初始化错误
#define W25Qxx_ERROR_WriteEnable       -2		// 写使能错误
#define W25Qxx_ERROR_AUTOPOLLING       -3		// 轮询等待错误，无响应
#define W25Qxx_ERROR_Erase         		-4		// 擦除错误
#define W25Qxx_ERROR_TRANSMIT         	-5		// 传输错误
#define W25Qxx_ERROR_MemoryMapped		-6    // 内存映射模式错误
#define W25Qxx_ERROR_Enter4ByteMode		-7    // 内存映射模式错误

#define W25Qxx_CMD_EnableReset  		0x66		// 使能复位
#define W25Qxx_CMD_ResetDevice   	0x99		// 复位器件
#define W25Qxx_CMD_JedecID 			0x9F		// JEDEC ID
#define W25Qxx_CMD_WriteEnable		0X06		// 写使能
#define W25Qxx_CMD_Enter4ByteMode   0xB7

#define W25Qxx_CMD_SectorErase 		0x21		// 扇区擦除，4K字节， 参考擦除时间 45ms
#define W25Qxx_CMD_BlockErase_32K 	0x52		// 块擦除，  32K字节，参考擦除时间 120ms
#define W25Qxx_CMD_BlockErase_64K 	0xDC		// 块擦除，  64K字节，参考擦除时间 150ms
#define W25Qxx_CMD_ChipErase 			0xC7		// 整片擦除，参考擦除时间 20S

#define W25Qxx_CMD_QuadInputPageProgram  	0x34  		// 1-1-4模式下(1线指令1线地址4线数据)，页编程指令，参考写入时间 0.4ms
#define W25Qxx_CMD_FastReadQuad_IO       	0xEC  		// 1-4-4模式下(1线指令4线地址4线数据)，快速读取指令

#define W25Qxx_CMD_ReadStatus_REG1			0x05			// 读状态寄存器1
#define W25Qxx_CMD_ReadStatus_REG3			0x15			// 读状态寄存器1
#define W25Qxx_Status_REG1_BUSY  			0x01			// 读状态寄存器1的第0位（只读），Busy标志位，当正在擦除/写入数据/写命令时会被置1
#define W25Qxx_Status_REG1_WEL  				0x02			// 读状态寄存器1的第1位（只读），WEL写使能标志位，该标志位为1时，代表可以进行写操作
#define W25Qxx_Status_REG3_ADS  				0x01			// 读状态寄存器1的第1位（只读），WEL写使能标志位，该标志位为1时，代表可以进行写操作

#define W25Qxx_PageSize       				256			// 页大小，256字节
#define W25Qxx_FlashSize       				0x2000000		// W25Q64大小，8M字节
#define W25Qxx_FLASH_ID           			0xEF4020    // W25Q512 JEDEC ID
#define W25Qxx_ChipErase_TIMEOUT_MAX		200000U		// 超时等待时间，W25Q64整片擦除所需最大时间是100S
#define W25Qxx_Mem_Addr							0x90000000 	// 内存映射模式的地址


/*----------------------------------------------- 函数声明 ---------------------------------------------------*/

int8_t	QSPI_W25Qxx_Init(void);						// W25Qxx初始化
int8_t 	flash_reset(void);					// 复位器件
uint32_t flash_read_id(void);					// 读取器件ID
int8_t  flash_enter_4byte_mode(void);
int8_t 	flash_memory_mapped_mode(void);		// 进入内存映射模式

int8_t 	flash_sector_erase(uint32_t SectorAddress);		// 扇区擦除，4K字节， 参考擦除时间 45ms
int8_t 	flash_block_erase_32k (uint32_t SectorAddress);	// 块擦除，  32K字节，参考擦除时间 120ms
int8_t 	flash_block_erase_64k (uint32_t SectorAddress);	// 块擦除，  64K字节，参考擦除时间 150ms，实际使用建议使用64K擦除，擦除的时间最快
int8_t 	flash_chip_erase (void);                         // 整片擦除，参考擦除时间 20S

int8_t	flash_write_page(uint8_t* pBuffer, uint32_t WriteAddr, uint16_t NumByteToWrite);	// 按页写入，最大256字节
int8_t	flash_write_buffer(uint8_t* pBuffer, uint32_t WriteAddr, uint32_t Size);				// 写入数据，最大不能超过flash芯片的大小
int8_t 	flash_read_buffer(uint8_t* pBuffer, uint32_t ReadAddr, uint32_t NumByteToRead);
void flash_overwrite_random(uint8_t *buf, uint32_t address, uint32_t n);

#endif //HAL_DEVICE_FLASH_H
