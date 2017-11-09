#include "../cplugin.h"

const char key() { return 'M'; }
const int code() { return 109; }

const char * name() { return "Mul"; }
const char * caption() { return "Multiply two complex numbers"; }
const char * role() { return "Multiplication of two complex numbers"; }

_complex action(_complex a, _complex b) {
    _complex res;
    res.re = a.re * b.re - a.im * b.im;
    res.im = a.re * b.im + a.im * b.re;
    return res;
}
