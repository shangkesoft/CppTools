#pragma once

/**
 * @brief
 *
 */

#ifndef BREAK_ON_FALSE

// If you don't want to use the logger, you can comment out the following line. eg. //#include "logger.h"
#include "logger.h"

#ifndef LOG_ERROR
#define LOG_ERROR( msg ) printf( "%s:%d %s()  %s\n", __FILE__, __LINE__, __FUNCTION__, msg );
#endif // SDK_LOG_ERROR

#if defined(__GNUC__)
    #define     CONDITION(cond)             ((__builtin_expect((cond)!=0, 0)))
    #define     LIKELY(x)                   ((__builtin_expect(!!(x), 1)))  // x is likely true
    #define     UNLIKELY(x)                 ((__builtin_expect(!!(x), 0)))  // x is likely false
#else
    #define     CONDITION(cond)             ((cond))
    #define     LIKELY(x)                   ((x))
    #define     UNLIKELY(x)                 ((x))
#endif


#define _LOOP_ACT_( action, error_info, msg ) \
{ \
    std::string msg1 = std::string(#action) + error_info; \
    struct _ss_get_msg_t { static std::string _ss_get_msg(const std::string& str = ""){return str;}; }; \
    std::string msg2 = _ss_get_msg_t::_ss_get_msg(msg); \
    if( msg2.size() ) msg1 += " msg:" + msg2; \
    LOG_ERROR( msg1.c_str() ); \
    action; \
}

#define BREAK_ON_FALSE( a, ... ) if(UNLIKELY(!(a)))_LOOP_ACT_( break, "! (" #a ")==false", __VA_ARGS__ );
#define BREAK_ON_NULL( a, ... )  if(UNLIKELY(!(a)))_LOOP_ACT_( break, "! (" #a ")==NULL",  __VA_ARGS__ );
#define BREAK_ON_TRUE( a, ... )  {long v=(long)(a); if(UNLIKELY(v))   _LOOP_ACT_( break, "! (" #a ")!=0:" + std::to_string(v), __VA_ARGS__ )};
#define BREAK_ON_NEGATIVE( a, ... ) {long v=(long)(a); if(UNLIKELY(v<0)) _LOOP_ACT_( break, "! (" #a ")<0:"  + std::to_string(v), __VA_ARGS__ )};

#define CONTINUE_ON_FALSE( a, ... ) if(UNLIKELY(!(a)))_LOOP_ACT_( continue, "! (" #a ")==false", __VA_ARGS__ );
#define CONTINUE_ON_NULL( a, ... )  if(UNLIKELY(!(a)))_LOOP_ACT_( continue, "! (" #a ")==NULL",  __VA_ARGS__ );
#define CONTINUE_ON_TRUE( a, ... )  {long v=(long)(a); if(UNLIKELY(v))   _LOOP_ACT_( continue, "! (" #a ")!=0:" + std::to_string(v), __VA_ARGS__ )};
#define CONTINUE_ON_NEGATIVE( a, ... ) {long v=(long)(a); if(UNLIKELY(v<0)) _LOOP_ACT_( continue, "! (" #a ")<0:"  + std::to_string(v), __VA_ARGS__ )};

#define DEL_MEM( a ) if ( NULL != (a) ) { delete a; a = NULL; }
#define DEL_MEM_ARY( a ) if ( NULL != (a) ) { delete[] a; a = NULL; }

#define UNUSED(var)			do { (void)(var); } while(0)

#endif // ifndef BREAK_ON_FALSE
