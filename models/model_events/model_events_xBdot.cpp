
#include "amici/symbolic_functions.h"
#include "amici/defines.h" //realtype definition
typedef amici::realtype realtype;
#include <cmath> 

using namespace amici;

void xBdot_model_events(realtype *xBdot, const realtype t, const realtype *x, const realtype *p, const realtype *k, const realtype *h, const realtype *xB, const realtype *w, const realtype *dwdx) {
  xBdot[0] = -p[0]*xB[0]*(h[3]-1.0)-p[1]*xB[1]*exp(t*(-1.0/1.0E1));
  xBdot[1] = p[2]*xB[1];
  xBdot[2] = xB[2];
}

