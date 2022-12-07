#!/usr/bin/env python

import sys
import click
from PIL import Image


def convert_color(r, g, b):
    c = r >> 3
    c <<= 6
    c |= g >> 2
    c <<= 5
    c |= b >> 3
    c &= 0xFFFF
    return (c >> 8 | c << 8) & 0xFFFF


@click.command()
@click.argument('image', type=click.Path(exists=True, dir_okay=False))
@click.argument('name', type=str)
@click.argument('mode', type=str)
def convert(image: str, name: str, mode: str):
    im = Image.open(image)  # type: Image.Image
    im = im.convert('RGBA')
    width = im.width
    height = im.height
    name = name.replace('.', '_')
    result = []
    if mode == '1':
        tmp = 0
        bit = 0
        for y in range(height):
            for x in range(width):
                pixel = 0
                r, g, b, a = im.getpixel((x, y))
                if any((r, g, b)):
                    pixel = 1
                tmp = (tmp << 1) | pixel
                bit += 1
                if bit == 8:
                    result.append(tmp)
                    tmp = bit = 0
            if bit != 0:
                tmp <<= 8 - bit
                result.append(tmp)
                tmp = bit = 0
        if bit != 0:
            tmp <<= 8 - bit
            result.append(tmp)
        result_str = f'const uint8_t {name}_data[] = {{ {", ".join(str(v) for v in result)} }};'
    elif mode == '16':
        for y in range(height):
            for x in range(width):
                r, g, b, a = im.getpixel((x, y))
                result.append(convert_color(r, g, b))
        result_str = f'const uint16_t {name}_data[] = {{ {", ".join(str(v) for v in result)} }};'
    elif mode == 'palette':
        palette = []
        for y in range(height):
            for x in range(width):
                r, g, b, a = im.getpixel((x, y))
                color = convert_color(r, g, b)
                if color not in palette:
                    palette.append(color)
                result.append(palette.index(color))
        result_str = f'const uint8_t {name}_data[] = {{ {", ".join(str(v) for v in result)} }};\n' \
                     f'const uint16_t {name}_dp[] = {{ {", ".join(str(v) for v in palette)} }};'
    else:
        raise ValueError('unsupported mode')

    result = [
        f'#pragma once',
        f'const uint16_t {name}_w = {width};',
        f'const uint16_t {name}_h = {height};',
        result_str,
        f'const CanvasBitmapDef {name}_def = {{ .w = {name}_w, .h = {name}_h, .data = {name}_data, }};',
        f'const CanvasBitmapDef *{name} = &{name}_def;'
    ]
    print('\n'.join(result))


if __name__ == '__main__':
    convert()
