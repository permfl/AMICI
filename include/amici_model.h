#ifndef MODEL_H
#define MODEL_H

#include <nvector/nvector_serial.h>
#include <sundials/sundials_direct.h>
#include <sundials/sundials_sparse.h>
#include <include/amici.h>

class UserData;
class ExpData;

/**
 * @brief The Model class represents an AMICI ODE model.
 * The model does not contain any data, its state should never change.
 */
class Model
{
public:
    Model() :
        np(0), nk(0),
        nx(0), nxtrue(0),
        ny(0), nytrue(0),
        nz(0), nztrue(0),
        ne(0), nw(0),
        ndwdx(0), ndwdp(0),
        nnz(0), nJ(0),
        ubw(0), lbw(0),
        o2mode(AMICI_O2MODE_NONE) {}

    Model(int np,
          int nx, int nxtrue,
          int nk,
          int ny, int nytrue,
          int nz, int nztrue,
          int ne, int nJ,
          int nw, int ndwdx, int ndwdp, int nnz,
          int ubw, int lbw,
          AMICI_o2mode o2mode) :
        np(np), nk(nk),
        nx(nx), nxtrue(nxtrue),
        ny(ny), nytrue(nytrue),
        nz(nz), nztrue(nztrue),
        ne(ne), nw(nw),
        ndwdx(ndwdx), ndwdp(ndwdp),
        nnz(nnz),nJ(nJ),
        ubw(ubw), lbw(lbw),
        o2mode(o2mode) {}

    virtual Solver *getSolver() { return NULL; }

    virtual int fx0(N_Vector x0, void *user_data) { return AMICI_ERROR_NOT_IMPLEMENTED; }

    virtual int fdx0(N_Vector x0, N_Vector dx0, void *user_data) { return AMICI_SUCCESS; }

//    virtual int fdx0(const realtype *k, realtype *x) { return AMICI_ERROR_NOT_IMPLEMENTED; }

    virtual int fsx0(N_Vector *sx0, N_Vector x, N_Vector dx, void *user_data) { return AMICI_ERROR_NOT_IMPLEMENTED; }

    virtual int fsdx0(N_Vector *sdx0, N_Vector x, N_Vector dx, void *user_data) { return AMICI_SUCCESS; }

    virtual int fJ(long int N, realtype t, realtype cj, N_Vector x, N_Vector dx, N_Vector xdot, DlsMat J, void *user_data, N_Vector tmp1, N_Vector tmp2, N_Vector tmp3) { return AMICI_ERROR_NOT_IMPLEMENTED; }

    virtual int fJB(long int NeqBdot, realtype t, N_Vector x, N_Vector xB, N_Vector xBdot, DlsMat JB, void *user_data, N_Vector tmp1B, N_Vector tmp2B, N_Vector tmp3B) { return AMICI_ERROR_NOT_IMPLEMENTED; }

    virtual int fJDiag(realtype t, N_Vector JDiag, N_Vector x, void *user_data)  { return AMICI_ERROR_NOT_IMPLEMENTED; }

    virtual int fJv(N_Vector v, N_Vector Jv, realtype t, N_Vector x, N_Vector xdot, void *user_data, N_Vector tmp)  { return AMICI_ERROR_NOT_IMPLEMENTED; }

    virtual int froot(realtype t, N_Vector x, N_Vector dx, realtype *root, void *user_data) { return AMICI_ERROR_NOT_IMPLEMENTED; }

    virtual int frz(realtype t, int ie, N_Vector x, TempData *tdata, ReturnData *rdata) { return AMICI_ERROR_NOT_IMPLEMENTED; }

    virtual int fsrz(realtype t, int ie, N_Vector x, N_Vector *sx, TempData *tdata, ReturnData *rdata) { return AMICI_ERROR_NOT_IMPLEMENTED; }

    virtual int fstau(realtype t, int ie, N_Vector x, N_Vector *sx, TempData *tdata) { return AMICI_ERROR_NOT_IMPLEMENTED; }

    virtual int fy(realtype t, int it, N_Vector x, void *user_data, ReturnData *rdata) { return AMICI_ERROR_NOT_IMPLEMENTED; }

    virtual int fdydp(realtype t, int it, N_Vector x, TempData *tdata) { return AMICI_ERROR_NOT_IMPLEMENTED; }

    virtual int fdydx(realtype t, int it, N_Vector x, TempData *tdata) { return AMICI_ERROR_NOT_IMPLEMENTED; }

    virtual int fz(realtype t, int ie, N_Vector x, TempData *tdata, ReturnData *rdata) { return AMICI_ERROR_NOT_IMPLEMENTED; }

    virtual int fsz(realtype t, int ie, N_Vector x, N_Vector *sx, TempData *tdata, ReturnData *rdata) { return AMICI_ERROR_NOT_IMPLEMENTED; }

    virtual int fdzdp(realtype t, int ie, N_Vector x, TempData *tdata) { return AMICI_ERROR_NOT_IMPLEMENTED; }

    virtual int fdzdx(realtype t, int ie, N_Vector x, TempData *tdata) { return AMICI_ERROR_NOT_IMPLEMENTED; }

    virtual int fdrzdp(realtype t, int ie, N_Vector x, TempData *tdata) { return AMICI_ERROR_NOT_IMPLEMENTED; }

    virtual int fdrzdx(realtype t, int ie, N_Vector x, TempData *tdata) { return AMICI_ERROR_NOT_IMPLEMENTED; }

    virtual int fxdot(realtype t, N_Vector x, N_Vector dx, N_Vector xdot, void *user_data) { return AMICI_ERROR_NOT_IMPLEMENTED; }

    virtual int fxBdot(realtype t, N_Vector x, N_Vector xB, N_Vector xBdot, void *user_data) { return AMICI_ERROR_NOT_IMPLEMENTED; }

    virtual int fqBdot(realtype t, N_Vector x, N_Vector xB, N_Vector qBdot, void *user_data) { return AMICI_ERROR_NOT_IMPLEMENTED; }

    virtual int fdxdotdp(realtype t, N_Vector x, N_Vector dx, void *user_data) { return AMICI_ERROR_NOT_IMPLEMENTED; }

    virtual int fdeltax(realtype t, int ie, N_Vector x, N_Vector xdot, N_Vector xdot_old, TempData *tdata) { return AMICI_ERROR_NOT_IMPLEMENTED; }

    virtual int fdeltasx(realtype t, int ie, N_Vector x, N_Vector xdot, N_Vector xdot_old, N_Vector *sx, TempData *tdata) { return AMICI_ERROR_NOT_IMPLEMENTED; }

    virtual int fdeltaxB(realtype t, int ie, N_Vector x, N_Vector xB, N_Vector xdot, N_Vector xdot_old, TempData *tdata) { return AMICI_ERROR_NOT_IMPLEMENTED; }

    virtual int fdeltaqB(realtype t, int ie, N_Vector x, N_Vector xB, N_Vector qBdot, N_Vector xdot, N_Vector xdot_old, TempData *tdata) { return AMICI_ERROR_NOT_IMPLEMENTED; }

    virtual int fsigma_y(realtype t, TempData *tdata) { return AMICI_ERROR_NOT_IMPLEMENTED; }

    virtual int fdsigma_ydp(realtype t, TempData *tdata) { return AMICI_ERROR_NOT_IMPLEMENTED; }

    virtual int fsigma_z(realtype t, int ie, TempData *tdata) { return AMICI_ERROR_NOT_IMPLEMENTED; }

    virtual int fdsigma_zdp(realtype t, int ie, TempData *tdata) { return AMICI_ERROR_NOT_IMPLEMENTED; }

    virtual int fJy(realtype t, int it, N_Vector x, TempData *tdata, const ExpData *edata, ReturnData *rdata) { return AMICI_ERROR_NOT_IMPLEMENTED; }

    virtual int fJz(realtype t, int ie, N_Vector x, TempData *tdata, const ExpData *edata, ReturnData *rdata) { return AMICI_ERROR_NOT_IMPLEMENTED; }

    virtual int fJrz(realtype t, int ie, N_Vector x, TempData *tdata, const ExpData *edata, ReturnData *rdata) { return AMICI_ERROR_NOT_IMPLEMENTED; }

    virtual int fdJydy(realtype t, int it, N_Vector x, TempData *tdata, const ExpData *edata, ReturnData *rdata) { return AMICI_ERROR_NOT_IMPLEMENTED; }

    virtual int fdJydsigma(realtype t, int it, N_Vector x, TempData *tdata, const ExpData *edata, ReturnData *rdata) { return AMICI_ERROR_NOT_IMPLEMENTED; }

    virtual int fdJzdz(realtype t, int ie, N_Vector x, TempData *tdata, const ExpData *edata, ReturnData *rdata) { return AMICI_ERROR_NOT_IMPLEMENTED; }

    virtual int fdJzdsigma(realtype t, int ie, N_Vector x, TempData *tdata, const ExpData *edata, ReturnData *rdata) { return AMICI_ERROR_NOT_IMPLEMENTED; }

    virtual int fdJrzdz(realtype t, int ie, N_Vector x, TempData *tdata, const ExpData *edata, ReturnData *rdata) { return AMICI_ERROR_NOT_IMPLEMENTED; }

    virtual int fdJrzdsigma(realtype t, int ie, N_Vector x, TempData *tdata, const ExpData *edata, ReturnData *rdata) { return AMICI_ERROR_NOT_IMPLEMENTED; }

    virtual int fsxdot(int Ns, realtype t, N_Vector x, N_Vector xdot,int ip,  N_Vector sx, N_Vector sxdot, void *user_data, N_Vector tmp1, N_Vector tmp2) { return AMICI_ERROR_NOT_IMPLEMENTED; }

    virtual int fJSparse(realtype t, N_Vector x, N_Vector xdot, SlsMat J, void *user_data, N_Vector tmp1, N_Vector tmp2, N_Vector tmp3) { return AMICI_ERROR_NOT_IMPLEMENTED; }

    virtual int fJBand(long int N, long int mupper, long int mlower, realtype t, N_Vector x, N_Vector xdot, DlsMat J, void *user_data, N_Vector tmp1, N_Vector tmp2, N_Vector tmp3) { return AMICI_ERROR_NOT_IMPLEMENTED; }

    virtual int fJBandB(long int NeqBdot, long int mupper, long int mlower, realtype t, N_Vector x, N_Vector xB, N_Vector xBdot, DlsMat JB, void *user_data, N_Vector tmp1B, N_Vector tmp2B, N_Vector tmp3B) { return AMICI_ERROR_NOT_IMPLEMENTED; }

    virtual int fJvB(N_Vector vB, N_Vector JvB, realtype t, N_Vector x, N_Vector xB, N_Vector xBdot, void *user_data, N_Vector tmpB) { return AMICI_ERROR_NOT_IMPLEMENTED; }

    virtual int fJSparseB(realtype t, N_Vector x, N_Vector xB, N_Vector xBdot, SlsMat JB, void *user_data, N_Vector tmp1B, N_Vector tmp2B, N_Vector tmp3B) { return AMICI_ERROR_NOT_IMPLEMENTED; }

    virtual ~Model();

    // Generic implementations
    int fsy(int it, TempData *tdata, ReturnData *rdata);

    int fsz_tf(int ie, TempData *tdata, ReturnData *rdata);

    int fsJy(int it, TempData *tdata, ReturnData *rdata);

    int fdJydp(int it, TempData *tdata, const ExpData *edata, ReturnData *rdata);

    int fdJydx(int it, TempData *tdata, const ExpData *edata);

    int fsJz(int ie, TempData *tdata, const ReturnData *rdata);

    int fdJzdp(int ie, TempData *tdata, const ExpData *edata, ReturnData *rdata);

    int fdJzdx(int ie, TempData *tdata, const ExpData *edata);

    int initialize(UserData *udata, TempData *tdata);

    int initializeStates(double *x0data, TempData *tdata);

    int initHeaviside(TempData *tdata);

    /* Model dimensions */
    /** total number of model parameters */
    const int np;
    /** number of fixed parameters */
    const int nk;
    /** number of states */
    const int nx;
    /** number of states in the unaugmented system */
    const int nxtrue;
    /** number of observables */
    const int ny;
    /** number of observables in the unaugmented system */
    const int nytrue;
    /** number of event outputs */
    const int nz;
    /** number of event outputs in the unaugmented system */
    const int nztrue;
    /** number of events */
    const int ne;
    /** number of common expressions */
    const int nw;
    /** number of derivatives of common expressions wrt x */
    const int ndwdx;
    /** number of derivatives of common expressions wrt p */
    const int ndwdp;
    /** number of nonzero entries in jacobian */
    const int nnz;
    /** dimension of the augmented objective function for 2nd order ASA */
    const int nJ;
    /** upper bandwith of the jacobian */
    const int ubw;
    /** lower bandwith of the jacobian */
    const int lbw;
    /** flag indicating whether for sensi == AMICI_SENSI_ORDER_SECOND directional or full second order derivative will be computed */
    const AMICI_o2mode o2mode;
    /** index indicating to which event an event output belongs */
    int *z2event = nullptr;
    /** flag array for DAE equations */
    realtype *idlist = nullptr;

};

#endif // MODEL_H
