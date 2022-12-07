#!/usr/bin/env python
import codecs

import click


@click.command()
@click.argument('file', type=click.Path(exists=True, dir_okay=False))
@click.argument('name', type=str)
def convert(file: str, name: str):
    name = name.replace('.', '_')
    print('#pragma once')
    with open(file, 'rb') as f:
        stream = f.read()
        print(f'const int {name}_size = {len(stream)};')
        print(f'const uint8_t {name}[] = {{{", ".join(str(b) for b in stream)}}};')


if __name__ == '__main__':
    convert()
