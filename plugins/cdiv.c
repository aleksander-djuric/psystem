#include <math.h>
#include "../cplugin.h"

const char key() { return 'D'; }
const int code() { return 100; }

const char * name() { return "Div"; }
const char * caption() { return "Divide two complex numbers"; }
const char * role() { return "Division of two complex numbers"; }

_complex action(_complex a, _complex b) {
    _complex res;
    double ratio, denom;

    if (fabs(b.re) >= fabs(b.im)) {
	ratio = b.im / b.re;
	denom = b.re + ratio * b.im;
	res.re = (a.re + ratio * a.im) / denom;
	res.im = (a.im - ratio * a.re) / denom;
    } else {
	ratio = b.re / b.im;
	denom = b.im + ratio * b.re;
	res.re = (ratio * a.re + a.im) / denom;
	res.im = (ratio * a.im - a.re) / denom;
    }

    return res;
}
