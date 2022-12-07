#pragma once
const uint16_t scrllk_w = 23;
const uint16_t scrllk_h = 10;
const uint8_t scrllk_data[] = { 127, 255, 252, 255, 255, 254, 227, 17, 190, 222, 246, 190, 230, 246, 190, 250, 241, 190, 250, 246, 190, 199, 22, 134, 255, 255, 254, 127, 255, 252 };
const CanvasBitmapDef scrllk_def = { .w = scrllk_w, .h = scrllk_h, .data = scrllk_data, };
const CanvasBitmapDef *scrllk = &scrllk_def;
