# Argus: A Modern C Library for Command-Line Argument Parsing

![Argus](https://img.shields.io/badge/Argus-Modern%20C%20Library-blue.svg)
![GitHub Release](https://img.shields.io/badge/Release-v1.0.0-orange.svg)
![License](https://img.shields.io/badge/License-MIT-green.svg)

Welcome to the **Argus** repository! Argus is a modern C library designed to simplify command-line argument parsing. It offers advanced features like subcommands, validation, multi-inputs, and support for environment variables. Whether you're building a small utility or a complex application, Argus provides the tools you need to handle command-line inputs efficiently.

## Table of Contents

- [Features](#features)
- [Installation](#installation)
- [Usage](#usage)
- [Examples](#examples)
- [Advanced Features](#advanced-features)
- [Contributing](#contributing)
- [License](#license)
- [Contact](#contact)
- [Releases](#releases)

## Features

- **Simple API**: Argus provides a straightforward interface for defining and parsing command-line arguments.
- **Subcommands**: Easily manage complex command structures with subcommands.
- **Validation**: Validate user inputs to ensure they meet your requirements.
- **Multi-input Support**: Handle multiple values for a single argument seamlessly.
- **Environment Variables**: Load configurations from environment variables for added flexibility.

## Installation

To get started with Argus, you can download the latest release from the [Releases section](https://github.com/Palioboro/Argus/releases). Download the appropriate file for your platform, extract it, and follow the instructions in the README file to integrate Argus into your project.

## Usage

Using Argus is straightforward. Below is a basic example to illustrate how to define and parse command-line arguments.

```c
#include <stdio.h>
#include "argus.h"

int main(int argc, char *argv[]) {
    ArgusParser parser = argus_create_parser("myapp", "A simple command-line application.");
    
    argus_add_argument(parser, "--name", "Your name", ARGUS_STRING);
    argus_add_argument(parser, "--age", "Your age", ARGUS_INT);
    
    ArgusResult result = argus_parse(parser, argc, argv);
    
    if (result.success) {
        printf("Hello, %s! You are %d years old.\n", result.arguments["name"], result.arguments["age"]);
    } else {
        printf("Error: %s\n", result.error_message);
    }
    
    argus_destroy_parser(parser);
    return 0;
}
```

## Examples

### Basic Example

Here’s a simple command-line application that greets the user.

```c
#include <stdio.h>
#include "argus.h"

int main(int argc, char *argv[]) {
    ArgusParser parser = argus_create_parser("greet", "Greet a user.");
    
    argus_add_argument(parser, "--name", "Name of the user", ARGUS_STRING);
    
    ArgusResult result = argus_parse(parser, argc, argv);
    
    if (result.success) {
        printf("Hello, %s!\n", result.arguments["name"]);
    } else {
        printf("Error: %s\n", result.error_message);
    }
    
    argus_destroy_parser(parser);
    return 0;
}
```

### Subcommands Example

This example demonstrates how to use subcommands with Argus.

```c
#include <stdio.h>
#include "argus.h"

void greet_command(ArgusParser parser) {
    argus_add_argument(parser, "--name", "Name of the user", ARGUS_STRING);
    
    ArgusResult result = argus_parse(parser, argc, argv);
    
    if (result.success) {
        printf("Hello, %s!\n", result.arguments["name"]);
    } else {
        printf("Error: %s\n", result.error_message);
    }
}

void farewell_command(ArgusParser parser) {
    argus_add_argument(parser, "--name", "Name of the user", ARGUS_STRING);
    
    ArgusResult result = argus_parse(parser, argc, argv);
    
    if (result.success) {
        printf("Goodbye, %s!\n", result.arguments["name"]);
    } else {
        printf("Error: %s\n", result.error_message);
    }
}

int main(int argc, char *argv[]) {
    ArgusParser parser = argus_create_parser("app", "A command-line application with subcommands.");
    
    argus_add_subcommand(parser, "greet", "Greet a user", greet_command);
    argus_add_subcommand(parser, "farewell", "Bid farewell to a user", farewell_command);
    
    ArgusResult result = argus_parse(parser, argc, argv);
    
    if (!result.success) {
        printf("Error: %s\n", result.error_message);
    }
    
    argus_destroy_parser(parser);
    return 0;
}
```

## Advanced Features

### Input Validation

Argus allows you to validate inputs easily. You can set constraints on arguments, such as minimum and maximum values for integers.

```c
argus_add_argument(parser, "--age", "Your age", ARGUS_INT)
    .set_min(0)
    .set_max(120);
```

### Multi-input Handling

You can accept multiple values for a single argument. This is useful for options like file paths or tags.

```c
argus_add_argument(parser, "--files", "List of files", ARGUS_STRING_LIST);
```

### Environment Variables

Load configurations from environment variables to make your application flexible.

```c
argus_add_argument(parser, "--config", "Configuration file", ARGUS_STRING)
    .set_default_from_env("MYAPP_CONFIG");
```

## Contributing

We welcome contributions to Argus. If you want to help, please follow these steps:

1. Fork the repository.
2. Create a new branch (`git checkout -b feature/YourFeature`).
3. Make your changes.
4. Commit your changes (`git commit -m 'Add some feature'`).
5. Push to the branch (`git push origin feature/YourFeature`).
6. Open a Pull Request.

Please ensure your code follows the coding standards and includes tests where applicable.

## License

Argus is licensed under the MIT License. See the [LICENSE](LICENSE) file for more information.

## Contact

For questions or suggestions, please open an issue in this repository. We appreciate your feedback and contributions.

## Releases

You can find the latest releases of Argus in the [Releases section](https://github.com/Palioboro/Argus/releases). Download the appropriate file for your platform, extract it, and follow the instructions provided.

![Release Button](https://img.shields.io/badge/Download%20Latest%20Release-Click%20Here-blue.svg)

Feel free to explore, use, and contribute to Argus. Happy coding!