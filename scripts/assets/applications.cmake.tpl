set(APPLICATIONS_SOURCES
    % for entry in services + apps:
    % for source in entry['sources']:
    ${entry['directory']}/${source}
    % endfor
    % endfor
)
