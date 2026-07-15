# get_next_line

A C function that reads a line from a file descriptor, one call at a time — including the bonus version that keeps track of multiple file descriptors simultaneously, regardless of the `BUFFER_SIZE` used.

## About

`get_next_line` returns a single line read from a file descriptor every time it is called, without losing track of where it left off between calls. This requires the function to keep its internal state (a static or persistent buffer) alive across multiple invocations, since a single `read()` call is not guaranteed to return a full line — or may return several lines at once.

The mandatory part handles one file descriptor at a time. The bonus part extends this to handle several file descriptors independently and in parallel, without mixing up their internal buffers.

## Files

| File | Description |
|---|---|
| `get_next_line.c` | Mandatory implementation — reads and returns one line at a time from a single fd |
| `get_next_line.h` | Header for the mandatory version |
| `get_next_line_utils.c` | Helper functions (string joining, length, duplication, etc.) used by the mandatory version |
| `get_next_line_bonus.c` | Bonus implementation — supports multiple file descriptors simultaneously |
| `get_next_line_bonus.h` | Header for the bonus version |
| `get_next_line_utils_bonus.c` | Helper functions used by the bonus version |

## Compilation

```bash
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 get_next_line.c get_next_line_utils.c main.c -o gnl
```

`BUFFER_SIZE` can be set to any value at compile time and the function must behave correctly regardless of it.

For the bonus version:

```bash
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 get_next_line_bonus.c get_next_line_utils_bonus.c main.c -o gnl_bonus
```

## Usage

```c
#include "get_next_line.h"

int main(void)
{
    int fd;
    char *line;

    fd = open("file.txt", O_RDONLY);
    while ((line = get_next_line(fd)) != NULL)
    {
        printf("%s", line);
        free(line);
    }
    close(fd);
    return (0);
}
```

## Resources

While building and debugging this project, the following resources were especially helpful:

- **[Bash Reference Manual / GNU User Manuals](https://www.gnu.org/software/bash/manual/)** — used for understanding file descriptors, redirection, and how the shell handles I/O, which helped clarify the behavior `get_next_line` needed to replicate.
- **[Stack Overflow](https://stackoverflow.com/)** — used to research static variable persistence across function calls, correct usage of `read()`, buffer/memory management edge cases, and handling multiple file descriptors for the bonus part.

## Author

[bckblt](https://github.com/bckblt) — 42 School
