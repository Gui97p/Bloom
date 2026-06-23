int parse(char* line, char** argv, int maxArgs) {
    int argc = 0;

    while (*line && argc < maxArgs) {
        while (*line == ' ')
            line++;

        if (!*line)
            break;

        if (*line == '"') {
            line++;

            argv[argc++] = line;

            while (*line && *line != '"')
                line++;

            if (*line) {
                *line = '\0';
                line++;
            }
        } else {
            argv[argc++] = line;

            while (*line && *line != ' ')
                line++;

            if (*line) {
                *line = '\0';
                line++;
            }
        }
    }

    return argc;
}