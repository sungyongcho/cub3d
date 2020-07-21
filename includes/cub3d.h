#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
   //define something for Windows (32-bit and 64-bit, this part is common)
   #ifdef _WIN64
      //define something for Windows (64-bit only)
   #else
      //define something for Windows (32-bit only)
   #endif
#elif __APPLE__
    #include <TargetConditionals.h>
    #if TARGET_IPHONE_SIMULATOR
         // iOS Simulator
    #elif TARGET_OS_IPHONE
        // iOS device
    #elif TARGET_OS_MAC
        # include "./minilibx_mms_20200219/mlx.h"
        # define KEY_W 13
        # define KEY_A 0
        # define KEY_S 1
        # define KEY_D 2
    #else
    #   error "Unknown Apple platform"
    #endif
#elif __linux__
    # include "./minilibx-linux/mlx.h"
    # define KEY_W 119
    # define KEY_A 97
    # define KEY_S 115
    # define KEY_D 100
#elif __unix__ // all unices not caught above
    // Unix
#elif defined(_POSIX_VERSION)
    // POSIX
#else
#   error "Unknown compiler"
#endif