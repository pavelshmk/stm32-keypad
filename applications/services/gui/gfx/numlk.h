#pragma once
const uint16_t numlk_w = 19;
const uint16_t numlk_h = 10;
const uint8_t numlk_data[] = { 127, 255, 192, 255, 255, 224, 218, 215, 96, 202, 210, 96, 210, 213, 96, 218, 213, 96, 218, 215, 96, 219, 55, 96, 255, 255, 224, 127, 255, 192 };
const CanvasBitmapDef numlk_def = { .w = numlk_w, .h = numlk_h, .data = numlk_data, };
const CanvasBitmapDef *numlk = &numlk_def;
