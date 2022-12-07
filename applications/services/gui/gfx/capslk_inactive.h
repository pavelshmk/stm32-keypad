#pragma once
const uint16_t capslk_inactive_w = 23;
const uint16_t capslk_inactive_h = 10;
const uint8_t capslk_inactive_data[] = { 127, 255, 252, 128, 0, 2, 156, 206, 58, 161, 41, 66, 161, 41, 50, 161, 238, 10, 161, 40, 10, 157, 40, 114, 128, 0, 2, 127, 255, 252 };
const CanvasBitmapDef capslk_inactive_def = { .w = capslk_inactive_w, .h = capslk_inactive_h, .data = capslk_inactive_data, };
const CanvasBitmapDef *capslk_inactive = &capslk_inactive_def;
