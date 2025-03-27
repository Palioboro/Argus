# cargs

![CI/CD Pipeline](https://github.com/lucocozz/cargs/actions/workflows/ci.yml/badge.svg)
![CodeQL Analysis](https://github.com/lucocozz/cargs/actions/workflows/codeql.yml/badge.svg)
[![License: MIT](https://img.shields.io/badge/License-MIT-blue.svg)](https://opensource.org/licenses/MIT)

> Modern C library for command-line argument parsing with an elegant, macro-based API.

**cargs** is a powerful C library for handling command-line arguments, designed to be both simple to use and flexible enough for advanced usage scenarios.

## ✨ Features

- 📋 **Help generation**: automatic formatted help and usage display
- 🔄 **Typed options**: booleans, integers, strings, floats, arrays, maps
- 🎨 **Flexible format parsing**: supports multiple option formats (--option=value, --option value, -ovalue, etc.)
- 🌳 **Subcommands**: Git/Docker-style nested command support
- ⚠️ **Clear error reporting**: detailed and user-friendly error messages for invalid options or values
- ✨ **Elegant design**: define options with concise, expressive macros
- 🔍 **Built-in validators**: built-in range, choices, regex patterns with comprehensive predefined sets
- 📦 **Organized option grouping**: visually group related options in help displays
- 🔗 **Option relationships**: define dependencies and conflicts between options
- 🚦 **Smart validation**: comprehensive option structure checking during development to prevent runtime errors, with a release mode for optimal performance in production
- 🌐 **Environment variables**: automatic ENV configuration
- 🚀 **Memory efficiency**: minimizes heap allocations for better performance and reliability
- 🧰 **Easy option customization**: create your own option types and handlers
- 🛡️ **Custom validation pipeline**: design your own validators with flexible pre/post processing

## Quick Example

```c
#include "cargs.h"
#include <stdio.h>

// Define options
CARGS_OPTIONS(
    options,
    HELP_OPTION(FLAGS(FLAG_EXIT)),
    VERSION_OPTION(FLAGS(FLAG_EXIT)),
    OPTION_FLAG('v', "verbose", "Enable verbose output"),
    OPTION_STRING('o', "output", "Output file", DEFAULT("output.txt")),
    OPTION_INT('p', "port", "Port number", RANGE(1, 65535), DEFAULT(8080)),
    POSITIONAL_STRING("input", "Input file")
)

int main(int argc, char **argv)
{
    // Initialize cargs
    cargs_t cargs = cargs_init(options, "my_program", "1.0.0");
    cargs.description = "cargs demonstrator";

    // Parse arguments
    if (cargs_parse(&cargs, argc, argv) != CARGS_SUCCESS) {
        return 1;
    }

    // Access parsed values
    const char *input = cargs_get(cargs, "input").as_string;
    const char *output = cargs_get(cargs, "output").as_string;
    int port = cargs_get(cargs, "port").as_int;
    bool verbose = cargs_get(cargs, "verbose").as_bool;

    printf("Configuration:\n");
    printf("  Input: %s\n", input);
    printf("  Output: %s\n", output);
    printf("  Port: %d\n", port);
    printf("  Verbose: %s\n", verbose ? "yes" : "no");

    // Free resources
    cargs_free(&cargs);
    return 0;
}
```

## 🚀 Getting Started

- [Installation](guide/installation.md) - How to install the cargs library
- [Quick Start](guide/quickstart.md) - Create your first application with cargs
- [Examples](examples/basic.md) - Explore usage examples

## 📚 Documentation

The documentation is organized as follows:

- **[User Guide](guide/installation.md)** - Detailed instructions for using cargs
- **[API Reference](api/overview.md)** - Complete reference of the cargs API
- **[Examples](examples/basic.md)** - Practical code examples
- **[Advanced Features](advanced/custom-handlers.md)** - Using advanced features
