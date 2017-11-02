
#include <include/symbolic_functions.h>
#include <include/amici.h>
#include <include/amici_model.h>
#include <string.h>
#include <include/tdata.h>
#include <include/udata.h>
#include "model_robertson_w.h"

using namespace amici;

void M_model_robertson(realtype t, N_Vector x, N_Vector dx, void *user_data) {
TempData *tdata = (TempData*) user_data;
Model *model = (Model*) tdata->model;
UserData *udata = (UserData*) tdata->udata;
realtype *x_tmp = nullptr;
if(x)
    x_tmp = N_VGetArrayPointer(x);
realtype *dx_tmp = nullptr;
if(dx)
    dx_tmp = N_VGetArrayPointer(dx);
memset(tdata->M,0,sizeof(realtype)*9);
w_model_robertson(t,x,dx,tdata);
  tdata->M[0+0*3] = 1.0;
  tdata->M[1+1*3] = 1.0;
return;

}


