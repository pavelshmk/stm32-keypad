${'%'}define slot-name name
%%define hash-function-name keycode_hash
%%define lookup-function-name keycode_lookup
%%readonly-tables
%%includes
%%struct-type
%%switch=10
%%{
#include <stdint.h>
%%}
struct keycode { char *name; uint16_t keycode; };
%%%
% for name, keycode in keycodes:
${name}, ${keycode}
% endfor