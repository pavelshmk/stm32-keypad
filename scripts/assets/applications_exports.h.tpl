#pragma once

// cstr_exports
% for entry in services + apps:
% for symb in entry['cstr_exports']:
extern const char *${symb};
% endfor
% endfor

// app names
% for entry in apps:
extern const char *${entry['id']};
% endfor

// service start flags
% for i, entry in enumerate(services):
#define SVC_${entry['id'].upper()}_RUNNING (1 << ${i})
% endfor
