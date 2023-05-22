#pragma once

#ifdef DEBUG
#define PRINT_DEBUG(str) do { std::cout << str << std::endl; } while( false )
#else
#define PRINT_DEBUG(str) do { } while ( false )
#endif