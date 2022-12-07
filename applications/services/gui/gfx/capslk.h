#pragma once
const uint16_t capslk_w = 23;
const uint16_t capslk_h = 10;
const uint8_t capslk_data[] = { 127, 255, 252, 255, 255, 254, 227, 49, 198, 222, 214, 190, 222, 214, 206, 222, 17, 246, 222, 215, 246, 226, 215, 142, 255, 255, 254, 127, 255, 252 };
const CanvasBitmapDef capslk_def = { .w = capslk_w, .h = capslk_h, .data = capslk_data, };
const CanvasBitmapDef *capslk = &capslk_def;
