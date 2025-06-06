/**
 * Advanced options example for argus
 * 
 * Demonstrates dependencies (REQUIRES), conflicts (CONFLICTS),
 * and exclusive option groups (FLAG_EXCLUSIVE)
 */

#include "argus.h"
#include <stdio.h>
#include <stdlib.h>

ARGUS_OPTIONS(
    options,
    HELP_OPTION(FLAGS(FLAG_EXIT)),
    VERSION_OPTION(FLAGS(FLAG_EXIT)),
    
    // Required option
    OPTION_STRING('i', "input", HELP("Input file"), FLAGS(FLAG_REQUIRED)),
    
    // Compression options in an exclusive group (only one can be selected)
    GROUP_START("Compression", GROUP_DESC("Compression options"), 
                FLAGS(FLAG_EXCLUSIVE)),
        OPTION_FLAG('z', "gzip", HELP("Use gzip compression")),
        OPTION_FLAG('j', "bzip2", HELP("Use bzip2 compression")),
        OPTION_FLAG('Z', "lzma", HELP("Use lzma compression")),
    GROUP_END(),
    
    // Compression level requires one of the compression options
    OPTION_INT('l', "level", HELP("Compression level"), 
              DEFAULT(6), RANGE(1, 9),
              REQUIRES("gzip", "bzip2", "lzma")),
    
    // Options that conflict with each other
    OPTION_FLAG('v', "verbose", HELP("Enable verbose output"), 
               CONFLICTS("quiet")),
    OPTION_FLAG('q', "quiet", HELP("Suppress all output"), 
               CONFLICTS("verbose")),
    
    // Options that require each other
    OPTION_STRING('u', "username", HELP("Username for authentication"), 
                 REQUIRES("password")),
    OPTION_STRING('p', "password", HELP("Password for authentication"), 
                 REQUIRES("username"))
)

int main(int argc, char **argv)
{
    argus_t argus = argus_init(options, "advanced_options", "1.0.0"); 
    argus.description = "Example of advanced options";
    
    int status = argus_parse(&argus, argc, argv);
    if (status != ARGUS_SUCCESS) {
        return status;
    }
    
    // Access input
    const char* input = argus_get(argus, "input").as_string;
    printf("Processing file: %s\n", input);
    
    // Check compression options
    if (argus_is_set(argus, "gzip")) {
        printf("Using gzip compression");
    } else if (argus_is_set(argus, "bzip2")) {
        printf("Using bzip2 compression");
    } else if (argus_is_set(argus, "lzma")) {
        printf("Using lzma compression");
    } else {
        printf("No compression selected");
    }
    
    // Show compression level if any compression is selected
    if (argus_is_set(argus, "gzip") || 
        argus_is_set(argus, "bzip2") || 
        argus_is_set(argus, "lzma")) {
        int level = argus_get(argus, "level").as_int;
        printf(" (level %d)\n", level);
    } else {
        printf("\n");
    }
    
    // Check authentication
    if (argus_is_set(argus, "username")) {
        const char* username = argus_get(argus, "username").as_string;
        printf("Authenticated as: %s\n", username);
    }
    
    // Check output mode
    if (argus_is_set(argus, "verbose")) {
        printf("Verbose mode enabled\n");
    } else if (argus_is_set(argus, "quiet")) {
        // In a real app, we would suppress output
    }
    
    argus_free(&argus);
    return 0;
}
