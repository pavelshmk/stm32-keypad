#!/usr/bin/env python
import json
from pathlib import Path
from jsonschema import validate, ValidationError
from yaml import load as yaml_load, Loader as YAMLLoader, YAMLError
from mako.template import Template


def main():
    root = Path(__file__).parent.parent
    schema = json.load((root / 'scripts' / 'assets' / 'manifest.schema.json').open())

    apps = []
    services = []

    for manifest in (root / 'applications').glob('**/manifest.yaml'):
        try:
            manifest_data: dict = yaml_load(manifest.open(), YAMLLoader)
        except YAMLError:
            print(f'Invalid YAML:\n{manifest}')
            return

        try:
            validate(manifest_data, schema)
        except ValidationError as e:
            print(f'Manifest validation error:\n{manifest}\n{e.message}')
            return

        if manifest_data['stack'] % 4 != 0:
            print(f'Stack size should be a multiple of 4:\n{manifest}')
            return

        manifest_data['directory'] = str(manifest.parent.relative_to(root / 'applications'))
        manifest_data.setdefault('cstr_exports', [])
        if manifest_data['type'] == 'APPLICATION':
            apps.append(manifest_data)
        elif manifest_data['type'] == 'SERVICE':
            manifest_data.setdefault('order', 0xFFFFFFFF)
            services.append(manifest_data)

    services.sort(key=lambda m: m['order'])

    with (root / 'applications' / 'applications.c').open('w') as f:
        f.write(Template(filename=str(root / 'scripts' / 'assets' / 'applications.c.tpl')).render(
            apps=apps,
            services=services,
        ))

    with (root / 'applications' / 'applications.cmake').open('w') as f:
        f.write(Template(filename=str(root / 'scripts' / 'assets' / 'applications.cmake.tpl')).render(
            apps=apps,
            services=services,
        ))

    with (root / 'applications' / 'applications_exports.h').open('w') as f:
        f.write(Template(filename=str(root / 'scripts' / 'assets' / 'applications_exports.h.tpl')).render(
            apps=apps,
            services=services,
        ))


if __name__ == '__main__':
    main()
