#pragma once
const uint16_t scrllk_inactive_w = 23;
const uint16_t scrllk_inactive_h = 10;
const uint8_t scrllk_inactive_data[] = { 127, 255, 252, 128, 0, 2, 156, 238, 66, 161, 9, 66, 153, 9, 66, 133, 14, 66, 133, 9, 66, 184, 233, 122, 128, 0, 2, 127, 255, 252 };
const CanvasBitmapDef scrllk_inactive_def = { .w = scrllk_inactive_w, .h = scrllk_inactive_h, .data = scrllk_inactive_data, };
const CanvasBitmapDef *scrllk_inactive = &scrllk_inactive_def;
