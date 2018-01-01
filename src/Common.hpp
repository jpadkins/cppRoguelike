///////////////////////////////////////////////////////////////////////////////
/// @file   Common.hpp
/// @author Jacob Adkins (jpadkins)
/// @brief  Defines commonly used macros and interfaces
///////////////////////////////////////////////////////////////////////////////

#ifndef ROGUELIKE__COMMON_HPP
#define ROGUELIKE__COMMON_HPP

///////////////////////////////////////////////////////////////////////////////
/// Headers
///////////////////////////////////////////////////////////////////////////////

#include <iostream>

///////////////////////////////////////////////////////////////////////////////
/// Logging
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// @brief Logs an informational message
///
/// @param msg  Message to log
///////////////////////////////////////////////////////////////////////////////
#define log_info(msg) std::clog << "[EXIT]["    \
    << __FILE__ << "]["                         \
    << __func__ << "]["                         \
    << __LINE__ << "]: "                        \
    << (msg) << std::endl;

///////////////////////////////////////////////////////////////////////////////
/// @brief Logs a message indicating a recoverable runtime error
///
/// @param msg  Message to log
///////////////////////////////////////////////////////////////////////////////
#define log_warn(msg) std::cerr << "[EXIT]["    \
    << __FILE__ << "]["                         \
    << __func__ << "]["                         \
    << __LINE__ << "]: "                        \
    << (msg) << std::endl;

///////////////////////////////////////////////////////////////////////////////
/// @brief Logs a message indicating a programming error
///
/// std::exit(-1) is called after the message is logged.
///
/// @param msg  Message to log
///////////////////////////////////////////////////////////////////////////////
#define log_exit(msg) std::cerr << "[EXIT]["    \
    << __FILE__ << "]["                         \
    << __func__ << "]["                         \
    << __LINE__ << "]: "                        \
    << (msg) << std::endl;                      \
    std::exit(-1);                              \

///////////////////////////////////////////////////////////////////////////////
/// Misc
///////////////////////////////////////////////////////////////////////////////
#define UNUSED(x) (void)x

#endif
