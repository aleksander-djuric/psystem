#include "../cplugin.h"

const char key() { return 'A'; }
const int code() { return 97; }

const char * name() { return "Add"; }
const char * caption() { return "Add two complex numbers"; }
const char * role() { return "Sum of two complex numbers"; }

_complex action(_complex a, _complex b) {
    _complex res;
    res.re = a.re + b.re;
    res.im = a.im + b.im;
    return res;
}
