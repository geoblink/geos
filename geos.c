#include "geos.h"

void go_geos_notice_handler2(const char *fmt, ...) {
    // va_list ap;
    // va_start(ap, fmt);
    // fprintf(stderr, "NOTICE: ");
    // vfprintf(stderr, fmt, ap);
    // va_end(ap);
}

#define ERRLEN 256

char go_geos_last_err[ERRLEN];

void go_geos_error_handler(const char *fmt, ...) {
    va_list ap;
    va_start(ap, fmt);
    vsnprintf(go_geos_last_err, (size_t) ERRLEN, fmt, ap);
    va_end(ap);
}

void go_geos_LinearRingToFlatPoints (GEOSContextHandle_t handler, double out[], size_t n_out, const GEOSCoordSequence *seq) {
    int i;
    double *j = out;
    for (i = 0; i < n_out; i++) {
        GEOSCoordSeq_getXY_r(handler, seq, i, j, j + 1);
        j++;
        j++;
    }
}

void go_geos_FlatPointsToCoordSeq (GEOSContextHandle_t handler, GEOSCoordSequence *out, double points[], size_t n_points) {
    int i;
    int j = 0;
    for (i = 0; i < n_points; i++) {
        GEOSCoordSeq_setXY_r(handler, out, i, points[j], points[j + 1]);
        j++;
        j++;
    }
}



char *go_geos_get_last_error(void) {
    return go_geos_last_err;
}

GEOSContextHandle_t go_geos_initGEOS() {
    return initGEOS_r(go_geos_notice_handler2, go_geos_error_handler);
}
