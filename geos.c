#include "geos.h"

void go_geos_notice_handler2(const char *fmt, ...) {
    va_list ap;
    va_start(ap, fmt);
    fprintf(stderr, "NOTICE: ");
    vfprintf(stderr, fmt, ap);
    va_end(ap);
}

#define ERRLEN 256

char go_geos_last_err[ERRLEN];

void go_geos_error_handler(const char *fmt, ...) {
    va_list ap;
    va_start(ap, fmt);
    vsnprintf(go_geos_last_err, (size_t) ERRLEN, fmt, ap);
    va_end(ap);
}

char *go_geos_get_last_error(void) {
    return go_geos_last_err;
}

GEOSContextHandle_t go_geos_initGEOS() {
    return initGEOS_r(go_geos_notice_handler2, go_geos_error_handler);
}
