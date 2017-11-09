#include "../cplugin.h"

const char key() { return 'S'; }
const int code() { return 115; }

const char * name() { return "Sub"; }
const char * caption() { return "Subtract two complex numbers"; }
const char * role() { return "Difference of two complex numbers"; }

_complex action(_complex a, _complex b) { 
    _complex res;
    res.re = a.re - b.re;
    res.im = a.im - b.im;
    return res;
}
