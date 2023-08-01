
#ifndef RECEIVER_EXPORT_H
#define RECEIVER_EXPORT_H

#ifdef RECEIVER_STATIC_DEFINE
#  define RECEIVER_EXPORT
#  define RECEIVER_NO_EXPORT
#else
#  ifndef RECEIVER_EXPORT
#    ifdef receiver_EXPORTS
        /* We are building this library */
#      define RECEIVER_EXPORT __attribute__((visibility("default")))
#    else
        /* We are using this library */
#      define RECEIVER_EXPORT __attribute__((visibility("default")))
#    endif
#  endif

#  ifndef RECEIVER_NO_EXPORT
#    define RECEIVER_NO_EXPORT __attribute__((visibility("hidden")))
#  endif
#endif

#ifndef RECEIVER_DEPRECATED
#  define RECEIVER_DEPRECATED __attribute__ ((__deprecated__))
#endif

#ifndef RECEIVER_DEPRECATED_EXPORT
#  define RECEIVER_DEPRECATED_EXPORT RECEIVER_EXPORT RECEIVER_DEPRECATED
#endif

#ifndef RECEIVER_DEPRECATED_NO_EXPORT
#  define RECEIVER_DEPRECATED_NO_EXPORT RECEIVER_NO_EXPORT RECEIVER_DEPRECATED
#endif

#if 0 /* DEFINE_NO_DEPRECATED */
#  ifndef RECEIVER_NO_DEPRECATED
#    define RECEIVER_NO_DEPRECATED
#  endif
#endif

#endif /* RECEIVER_EXPORT_H */
