#include "applications.h"

% for entry in services + apps:
extern void ${entry['entrypoint']}(void*);
% endfor

const Application SERVICES[] = {
        % for entry in services:
        {
            .id = "${entry['id']}",
            .name = "${entry['name']}",
            .entrypoint = ${entry['entrypoint']},
            .stack = ${entry['stack']},
        },
        % endfor
};
const size_t SERVICES_COUNT = ${len(services)};

const Application APPS[] = {
        % for entry in apps:
        {
            .id = "${entry['id']}",
            .name = "${entry['name']}",
            .entrypoint = ${entry['entrypoint']},
            .stack = ${entry['stack']},
        },
        % endfor
};
const size_t APPS_COUNT = ${len(apps)};

% for entry in apps:
const char *${entry['id']} = "${entry['id']}";
% endfor
