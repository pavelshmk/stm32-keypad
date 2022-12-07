#include "stm32f4xx_hal.h"
#include "device.h"
#include "device_display.h"

/*** Redefine if necessary ***/
#define SSD1351_SPI_PORT hspi
extern SPI_HandleTypeDef SSD1351_SPI_PORT;

#define SSD1351_RES_Pin       GPIO_PIN_14
#define SSD1351_RES_GPIO_Port GPIOB
#define SSD1351_CS_Pin        GPIO_PIN_12
#define SSD1351_CS_GPIO_Port  GPIOB
#define SSD1351_DC_Pin        GPIO_PIN_15
#define SSD1351_DC_GPIO_Port  GPIOB
#define SSD1351_PWR_Pin        GPIO_PIN_10
#define SSD1351_PWR_GPIO_Port  GPIOB

// default orientation
#define SSD1351_WIDTH  128
#define SSD1351_HEIGHT 128

static uint16_t display_framebuffer[128 * 128];

static void display_select() {
    HAL_GPIO_WritePin(SSD1351_CS_GPIO_Port, SSD1351_CS_Pin, GPIO_PIN_RESET);
}

void display_unselect() {
    HAL_GPIO_WritePin(SSD1351_CS_GPIO_Port, SSD1351_CS_Pin, GPIO_PIN_SET);
}

static void display_reset() {
    HAL_GPIO_WritePin(SSD1351_RES_GPIO_Port, SSD1351_RES_Pin, GPIO_PIN_SET);
//    HAL_Delay(120);
    HAL_GPIO_WritePin(SSD1351_RES_GPIO_Port, SSD1351_RES_Pin, GPIO_PIN_RESET);
//    HAL_Delay(120);
    HAL_GPIO_WritePin(SSD1351_RES_GPIO_Port, SSD1351_RES_Pin, GPIO_PIN_SET);
//    HAL_Delay(120);
}

static void display_write_command(uint8_t cmd) {
    HAL_GPIO_WritePin(SSD1351_DC_GPIO_Port, SSD1351_DC_Pin, GPIO_PIN_RESET);
    HAL_SPI_Transmit(&SSD1351_SPI_PORT, &cmd, sizeof(cmd), HAL_MAX_DELAY);
}

static void display_write_data(uint8_t* buff, size_t buff_size) {
    HAL_GPIO_WritePin(SSD1351_DC_GPIO_Port, SSD1351_DC_Pin, GPIO_PIN_SET);

    // split data in small chunks because HAL can't send more then 64K at once
    while(buff_size > 0) {
        uint16_t chunk_size = buff_size > 32768 ? 32768 : buff_size;
        HAL_SPI_Transmit(&SSD1351_SPI_PORT, buff, chunk_size, HAL_MAX_DELAY);
//        HAL_SPI_Transmit_DMA(&SSD1351_SPI_PORT, buff, chunk_size);
//        while(HAL_DMA_GetState(SSD1351_SPI_PORT.hdmatx) != HAL_DMA_STATE_READY);
        buff += chunk_size;
        buff_size -= chunk_size;
    }
}

static void display_set_address_window(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1) {
    // column address set
    display_write_command(0x15); // SETCOLUMN
    {
        uint8_t data[] = { x0 & 0xFF, x1 & 0xFF };
        display_write_data(data, sizeof(data));
    }

    // row address set
    display_write_command(0x75); // SETROW
    {
        uint8_t data[] = { y0 & 0xFF, y1 & 0xFF };
        display_write_data(data, sizeof(data));
    }

    // write to RAM
    display_write_command(0x5C); // WRITERAM
}

void display_init() {
    gpio_pin_init(GPIOB, GPIO_PIN_10 | GPIO_PIN_12 | GPIO_PIN_14 | GPIO_PIN_15, GPIO_MODE_OUTPUT_PP, GPIO_NOPULL,
                  GPIO_SPEED_FREQ_VERY_HIGH, 0);
//    gpio_pin_init(GPIOB, GPIO_Pins(10, 12, 14, 15), GPIO_Output_PushPull_100MHz);
    HAL_GPIO_WritePin(SSD1351_PWR_GPIO_Port, SSD1351_PWR_Pin, GPIO_PIN_SET);
//    HAL_Delay(1000);

    display_select();
    display_reset();

    // command list is based on https://github.com/adafruit/Adafruit-SSD1351-library

    display_write_command(0xFD); // COMMANDLOCK
    {
        uint8_t data[] = { 0x12 };
        display_write_data(data, sizeof(data));
    }
    display_write_command(0xFD); // COMMANDLOCK
    {
        uint8_t data[] = { 0xB1 };
        display_write_data(data, sizeof(data));
    }
    display_write_command(0xAE); // DISPLAYOFF
    display_write_command(0xB3); // CLOCKDIV
    display_write_command(0xF1); // 7:4 = Oscillator Frequency, 3:0 = CLK Div Ratio (A[3:0]+1 = 1..16)
    display_write_command(0xCA); // MUXRATIO
    {
        uint8_t data[] = { 0x7F }; // 127
        display_write_data(data, sizeof(data));
    }
    display_write_command(0xA0); // SETREMAP
    {
        uint8_t data[] = { 0x74 };
        display_write_data(data, sizeof(data));
    }
    display_write_command(0x15); // SETCOLUMN
    {
        uint8_t data[] = { 0x00, 0x7F };
        display_write_data(data, sizeof(data));
    }
    display_write_command(0x75); // SETROW
    {
        uint8_t data[] = { 0x00, 0x7F };
        display_write_data(data, sizeof(data));
    }
    display_write_command(0xA1); // STARTLINE
    {
        uint8_t data[] = { 0x00 }; // 96 if display height == 96
        display_write_data(data, sizeof(data));
    }
    display_write_command(0xA2); // DISPLAYOFFSET
    {
        uint8_t data[] = { 0x00 };
        display_write_data(data, sizeof(data));
    }
    display_write_command(0xB5); // SETGPIO
    {
        uint8_t data[] = { 0x00 };
        display_write_data(data, sizeof(data));
    }
    display_write_command(0xAB); // FUNCTIONSELECT
    {
        uint8_t data[] = { 0x01 };
        display_write_data(data, sizeof(data));
    }
    display_write_command(0xB1); // PRECHARGE
    {
        uint8_t data[] = { 0x32 };
        display_write_data(data, sizeof(data));
    }
    display_write_command(0xBE); // VCOMH
    {
        uint8_t data[] = { 0x05 };
        display_write_data(data, sizeof(data));
    }
    display_write_command(0xA6); // NORMALDISPLAY (don't invert)
    display_write_command(0xC1); // CONTRASTABC
    {
        uint8_t data[] = { 0xC8, 0x80, 0xC8 };
        display_write_data(data, sizeof(data));
    }
    display_write_command(0xC7); // CONTRASTMASTER
    {
        uint8_t data[] = { 0x0F };
        display_write_data(data, sizeof(data));
    }
    display_write_command(0xB4); // SETVSL
    {
        uint8_t data[] = { 0xA0, 0xB5, 0x55 };
        display_write_data(data, sizeof(data));
    }
    display_write_command(0xB6); // PRECHARGE2
    {
        uint8_t data[] = { 0x01 };
        display_write_data(data, sizeof(data));
    }

    display_fill_screen(0x0000);
    display_update_no_dma();

    display_select();
    display_write_command(0xAF); // DISPLAYON
    display_unselect();
}

void display_draw_pixel(uint16_t x, uint16_t y, uint16_t color) {
    if((x >= SSD1351_WIDTH) || (y >= SSD1351_HEIGHT))
        return;

    display_framebuffer[x + y * SSD1351_WIDTH] = color;

//    display_select();
//
//    display_set_address_window(x, y, x+1, y+1);
//    uint8_t data[] = { color >> 8, color & 0xFF };
//    display_write_data(data, sizeof(data));
//
//    display_unselect();
}

static void display_write_char(uint16_t x, uint16_t y, char ch, FontDef font, uint16_t color, uint16_t bgcolor) {
    uint32_t i, b, j;

    display_set_address_window(x, y, x + font.width - 1, y + font.height - 1);

    for(i = 0; i < font.height; i++) {
        b = font.data[(ch - 32) * font.height + i];
        for(j = 0; j < font.width; j++) {
            if((b << j) & 0x8000)  {
                display_framebuffer[(x + j) + (y + i) * SSD1351_WIDTH] = color;
//                uint8_t data[] = { color >> 8, color & 0xFF };
//                display_write_data(data, sizeof(data));
            } else {
                display_framebuffer[(x + j) + (y + i) * SSD1351_WIDTH] = bgcolor;
//                uint8_t data[] = { bgcolor >> 8, bgcolor & 0xFF };
//                display_write_data(data, sizeof(data));
            }
        }
    }
}

void display_write_string(uint16_t x, uint16_t y, const char* str, FontDef font, uint16_t color, uint16_t bgcolor) {
//    display_select();
    color = (color << 8) | (color >> 8);
    bgcolor = (bgcolor << 8) | (bgcolor >> 8);

    while(*str) {
        if(x + font.width >= SSD1351_WIDTH) {
            x = 0;
            y += font.height;
            if(y + font.height >= SSD1351_HEIGHT) {
                break;
            }

            if(*str == ' ') {
                // skip spaces in the beginning of the new line
                str++;
                continue;
            }
        }

        display_write_char(x, y, *str, font, color, bgcolor);
        x += font.width;
        str++;
    }

//    display_unselect();
}

void display_fill_rectangle(uint16_t x_, uint16_t y_, uint16_t w, uint16_t h, uint16_t color) {
    color = (color << 8) | (color >> 8);

    // clipping
    if((x_ >= SSD1351_WIDTH) || (y_ >= SSD1351_HEIGHT)) return;
    if((x_ + w - 1) >= SSD1351_WIDTH) w = SSD1351_WIDTH - x_;
    if((y_ + h - 1) >= SSD1351_HEIGHT) h = SSD1351_HEIGHT - y_;

    for (uint8_t x=x_; x < x_ + w; x++) {
        for (uint8_t y=y_; y < y_ + h; y++) {
            display_framebuffer[x + y * SSD1351_WIDTH] = color;
        }
    }

//    display_select();
//    display_set_address_window(x_, y_, x_+w-1, y_+h-1);
//
//    uint8_t data[] = { color >> 8, color & 0xFF };
//    HAL_GPIO_WritePin(SSD1351_DC_GPIO_Port, SSD1351_DC_Pin, GPIO_PIN_SET);
//    for(y_ = h; y_ > 0; y_--) {
//        for(x_ = w; x_ > 0; x_--) {
//            HAL_SPI_Transmit(&SSD1351_SPI_PORT, data, sizeof(data), HAL_MAX_DELAY);
//        }
//    }
//
//    display_unselect();
}

void display_fill_screen(uint16_t color) {
    display_fill_rectangle(0, 0, SSD1351_WIDTH, SSD1351_HEIGHT, color);
}

void display_draw_bitmap(uint16_t x, uint16_t y, uint16_t w, uint16_t h, const uint16_t* data) {
    if((x >= SSD1351_WIDTH) || (y >= SSD1351_HEIGHT)) return;
    if((x + w - 1) >= SSD1351_WIDTH) return;
    if((y + h - 1) >= SSD1351_HEIGHT) return;

    display_select();
    display_set_address_window(x, y, x + w - 1, y + h - 1);
    display_write_data((uint8_t *) data, sizeof(uint16_t) * w * h);
    display_unselect();
}

void display_invert_colors(bool invert) {
    display_select();
    display_write_command(invert ? 0xA7 /* INVERTDISPLAY */ : 0xA6 /* NORMALDISPLAY */);
    display_unselect();
}

void display_update(void) {
    display_select();
    display_set_address_window(0, 0, SSD1351_WIDTH - 1, SSD1351_HEIGHT - 1);
    HAL_GPIO_WritePin(SSD1351_DC_GPIO_Port, SSD1351_DC_Pin, GPIO_PIN_SET);
    spi_transmit_dma(display_framebuffer, 128 * 128 * 2, true);
    display_unselect();
}

void display_update_no_dma(void) {
    display_select();
    display_set_address_window(0, 0, SSD1351_WIDTH - 1, SSD1351_HEIGHT - 1);
    HAL_GPIO_WritePin(SSD1351_DC_GPIO_Port, SSD1351_DC_Pin, GPIO_PIN_SET);
    spi_transmit(display_framebuffer, 128 * 128 * 2);
    display_unselect();
}

void display_draw_bitmap_1(uint16_t x_, uint16_t y_, uint8_t *bitmap, uint16_t w, uint16_t h, uint16_t color, uint16_t bgcolor) {
    color = (color << 8) | (color >> 8);
    bgcolor = (bgcolor << 8) | (bgcolor >> 8);
    uint8_t bit = 0;
    for (uint16_t y=y_; y < y_ + h; y++) {
        for (uint16_t x=x_; x < x_ + w; x++) {
            display_draw_pixel(x, y, ((*bitmap >> (7 - bit++)) & 1) ? color : bgcolor);
            if (bit == 8) {
                bit = 0;
                bitmap++;
            }
        }
        if (bit != 0) {
            bit = 0;
            bitmap++;
        }
    }
}


