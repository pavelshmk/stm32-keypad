#pragma once
const uint16_t numlk_inactive_w = 19;
const uint16_t numlk_inactive_h = 10;
const uint8_t numlk_inactive_data[] = { 127, 255, 192, 128, 0, 32, 165, 40, 160, 181, 45, 160, 173, 42, 160, 165, 42, 160, 165, 40, 160, 164, 200, 160, 128, 0, 32, 127, 255, 192 };
const CanvasBitmapDef numlk_inactive_def = { .w = numlk_inactive_w, .h = numlk_inactive_h, .data = numlk_inactive_data, };
const CanvasBitmapDef *numlk_inactive = &numlk_inactive_def;
