#ifndef AMICI_SOLVER_H
#define AMICI_SOLVER_H

#include "amici/vector.h"
#include "amici/defines.h"
#include "amici/misc.h"
#include "amici/exception.h"
#include "amici/symbolic_functions.h"

#include <nvector/nvector_serial.h>   // DlsMat
#include <sundials/sundials_sparse.h> // SlsMat
#include <memory>
#include <functional>

namespace amici {

class ReturnData;
class ForwardProblem;
class BackwardProblem;
class Model;
class Solver;
} // namespace amici


// for serialization friend in Solver
namespace boost { namespace serialization {
template <class Archive>
void serialize(Archive &ar, amici::Solver &u, const unsigned int version);
}}


namespace amici {

/** Solver class.
 * provides a generic interface to CVode and IDA solvers, individual realizations
 * are realized in the CVodeSolver and the IDASolver class.
 */
class Solver {
  public:
    Solver() = default;

    /**
     * @brief Solver copy constructor
     * @param other
     */
    Solver(const Solver &other) : Solver()
    {
        sensi = other.sensi;
        atol = other.atol;
        rtol = other.rtol;
        quad_atol = other.quad_atol;
        quad_rtol = other.quad_rtol;
        maxsteps = other.maxsteps;
        maxstepsB = other.maxstepsB;
        newton_maxsteps = other.newton_maxsteps;
        newton_maxlinsteps = other.newton_maxlinsteps;
        newton_preeq = other.newton_preeq;
        ism = other.ism;
        sensi_meth = other.sensi_meth;
        linsol = other.linsol;
        interpType = other.interpType;
        lmm = other.lmm;
        iter = other.iter;
        stldet = other.stldet;
        ordering = other.ordering;
        ism = other.ism;
    }

    virtual ~Solver() = default;

    /**
     * @brief Clone this instance
     * @return The clone
     */
    virtual Solver* clone() const = 0;

    void setup(AmiVector *x, AmiVector *dx, AmiVectorArray *sx, AmiVectorArray *sdx, Model *model);

    void setupAMIB(BackwardProblem *bwd, Model *model);

    /**
     * getSens extracts diagnosis information from solver memory block and
     * writes them into the return data instance
     *
     * @param tret time at which the sensitivities should be computed
     * @param yySout vector with sensitivities
     */
    virtual void getSens(realtype *tret, AmiVectorArray *yySout) const = 0;

    /**
     * getDiagnosis extracts diagnosis information from solver memory block and
     * writes them into the return data object
     *
     * @param it time-point index
     * @param rdata pointer to the return data object
     */
    void getDiagnosis(const int it, ReturnData *rdata) const;

    /**
     * getDiagnosisB extracts diagnosis information from solver memory block and
     * writes them into the return data object for the backward problem
     *
     * @param it time-point index
     * @param rdata pointer to the return data object
     * @param which identifier of the backwards problem
     */
    void getDiagnosisB(const int it, ReturnData *rdata, int which) const;

    /**
     * getRootInfo extracts information which event occured
     *
     * @param rootsfound array with flags indicating whether the respective
     * event occured
     */
    virtual void getRootInfo(int *rootsfound) const = 0;

    /**
     * ReInit reinitializes the states in the solver after an event occurence
     *
     * @param t0 new timepoint
     * @param yy0 new state variables
     * @param yp0 new derivative state variables (DAE only)
     */
    virtual void reInit(realtype t0, AmiVector *yy0, AmiVector *yp0) = 0;

    /**
     * SensReInit reinitializes the state sensitivites in the solver after an
     * event occurence
     *
     * @param yS0 new state sensitivity
     * @param ypS0 new derivative state sensitivities (DAE only)
     */
    virtual void sensReInit(AmiVectorArray *yS0, AmiVectorArray *ypS0) = 0;

    /**
     * CalcIC calculates consistent initial conditions, assumes initial
     * states to be correct (DAE only)
     *
     * @param tout1 next timepoint to be computed (sets timescale)
     * @param x initial state variables
     * @param dx initial derivative state variables (DAE only)
     */
    virtual void calcIC(realtype tout1, AmiVector *x, AmiVector *dx) = 0;

    /**
      * CalcIBC calculates consistent initial conditions for the backwards
     * problem, assumes initial states to be correct (DAE only)
      *
      * @param which identifier of the backwards problem
      * @param tout1 next timepoint to be computed (sets timescale)
      * @param xB states of final solution of the forward problem
      * @param dxB derivative states of final solution of the forward
     * problem (DAE only)
      */
    virtual void calcICB(int which, realtype tout1, AmiVector *xB,
                           AmiVector *dxB) = 0;

    /**
      * Solve solves the forward problem until a predefined timepoint
      *
      * @param tout timepoint until which simulation should be performed
     *
      * @param yret states
      * @param ypret derivative states (DAE only)
      * @param tret pointer to the time variable
      * @param itask task identifier, can be CV_NORMAL or CV_ONE_STEP
     * @return status flag indicating success of execution
      */
    virtual int solve(realtype tout, AmiVector *yret, AmiVector *ypret,
                         realtype *tret, int itask) = 0;

    /**
      * SolveF solves the forward problem until a predefined timepoint
     * (adjoint only)
      *
      * @param tout timepoint until which simulation should be performed
     *
      * @param yret states
      * @param ypret derivative states (DAE only)
      * @param tret pointer to the time variable
      * @param itask task identifier, can be CV_NORMAL or CV_ONE_STEP
      * @param ncheckPtr pointer to a number that counts the internal
     * checkpoints
     * @return status flag indicating success of execution
      */
    virtual int solveF(realtype tout, AmiVector *yret, AmiVector *ypret,
                          realtype *tret, int itask, int *ncheckPtr) = 0;

    /**
      * SolveB solves the backward problem until a predefined timepoint
     * (adjoint only)
      *
      * @param tBout timepoint until which simulation should be performed
     *
      * @param itaskB task identifier, can be CV_NORMAL or CV_ONE_STEP
      */
    virtual void solveB(realtype tBout, int itaskB) = 0;

    /**
      * SetStopTime sets a timepoint at which the simulation will be stopped
      *
      * @param tstop timepoint until which simulation should be performed
     *
      */
    virtual void setStopTime(realtype tstop) = 0;

    //    virtual void AMIRootInit(int nrtfn, RootFn ptr) = 0;

    /**
      * ReInitB reinitializes the adjoint states after an event occurence
      *
      * @param which identifier of the backwards problem
      * @param tB0 new timepoint
      * @param yyB0 new adjoint state variables
      * @param ypB0 new adjoint derivative state variables (DAE only)
      */
    virtual void reInitB(int which, realtype tB0, AmiVector *yyB0,
                           AmiVector *ypB0) = 0;

    /**
      * getB returns the current adjoint states
      *
      * @param which identifier of the backwards problem
      * @param tret time at which the adjoint states should be computed
      * @param yy adjoint state variables
      * @param yp adjoint derivative state variables (DAE only)
      */
    virtual void getB(int which, realtype *tret, AmiVector *yy,
                        AmiVector *yp) const = 0;

    /**
      * getQuadB returns the current adjoint states
      *
      * @param which identifier of the backwards problem
      * @param tret time at which the adjoint states should be computed
      * @param qB adjoint quadrature state variables
      */
    virtual void getQuadB(int which, realtype *tret, AmiVector *qB) const = 0;

    /**
      * ReInitB reinitializes the adjoint states after an event occurence
      *
      * @param which identifier of the backwards problem
      * @param yQB0 new adjoint quadrature state variables
      */
    virtual void quadReInitB(int which, AmiVector *yQB0) = 0;

    /**
      * turnOffRootFinding disables rootfinding
      */
    virtual void turnOffRootFinding() = 0;

    /** sensitivity method
     * @return method enum
     */
    SensitivityMethod getSensitivityMethod() const;

    /**
     * @brief setSensitivityMethod
     * @param sensi_meth
     */
    void setSensitivityMethod(SensitivityMethod sensi_meth);

    /**
     * @brief getNewtonMaxSteps
     * @return
     */
    int getNewtonMaxSteps() const;

    /**
     * @brief setNewtonMaxSteps
     * @param newton_maxsteps
     */
    void setNewtonMaxSteps(int newton_maxsteps);

    /**
     * @brief getNewtonPreequilibration
     * @return
     */
    bool getNewtonPreequilibration() const;

    /**
     * @brief setNewtonPreequilibration
     * @param newton_preeq
     */
    void setNewtonPreequilibration(bool newton_preeq);

    /**
     * @brief getNewtonMaxLinearSteps
     * @return
     */
    int getNewtonMaxLinearSteps() const;

    /**
     * @brief setNewtonMaxLinearSteps
     * @param newton_maxlinsteps
     */
    void setNewtonMaxLinearSteps(int newton_maxlinsteps);

    /**
     * @brief returns the sensitvity order
     * @return sensitivity order
     */
    SensitivityOrder getSensitivityOrder() const;

    /**
     * @brief sets the sensitvity order
     * @param sensi sensitivity order
     */
    void setSensitivityOrder(SensitivityOrder sensi);

    /**
     * @brief returns the relative tolerances for the forward & backward problem
     * @return relative tolerances
     */
    double getRelativeTolerance() const;

    /**
     * @brief sets the relative tolerances for the forward & backward problem
     * @param rtol relative tolerance (non-negative number)
     */
    void setRelativeTolerance(double rtol);
    
    /**
     * @brief returns the absolute tolerances for the forward & backward problem
     * @return absolute tolerances
     */
    double getAbsoluteTolerance() const;

    /**
     * @brief sets the absolute tolerances for the forward & backward problem
     * @param atol absolute tolerance (non-negative number)
     */
    void setAbsoluteTolerance(double atol);

    /**
     * @brief returns the relative tolerance for the quadrature problem
     * @return relative tolerance
     */
    double getRelativeToleranceQuadratures() const;

    /**
     * @brief sets the relative tolerance for the quadrature problem
     * @param rtol relative tolerance (non-negative number)
     */
    void setRelativeToleranceQuadratures(double rtol);

    /**
     * @brief returns the absolute tolerance for the quadrature problem
     * @return absolute tolerance
     */
    double getAbsoluteToleranceQuadratures() const;

    /**
     * @brief sets the absolute tolerance for the quadrature problem
     * @param atol absolute tolerance (non-negative number)
     */
    void setAbsoluteToleranceQuadratures(double atol);

    /**
     * @brief returns the maximum number of solver steps for the forward problem
     * @return maximum number of solver steps
     */
    int getMaxSteps() const;

    /**
     * @brief sets the maximum number of solver steps for the forward problem
     * @param maxsteps maximum number of solver steps (non-negative number)
     */
    void setMaxSteps(int maxsteps);

    /**
     * @brief returns the maximum number of solver steps for the backward problem
     * @return maximum number of solver steps
     */
    int getMaxStepsBackwardProblem() const;
    /**
     * @brief sets the maximum number of solver steps for the backward problem
     * @param maxsteps maximum number of solver steps (non-negative number)
     */
    void setMaxStepsBackwardProblem(int maxsteps);

    /**
     * @brief returns the linear system multistep method
     * @return linear system multistep method
     */
    LinearMultistepMethod getLinearMultistepMethod() const;

    /**
     * @brief sets the linear system multistep method
     * @param lmm linear system multistep method
     */
    void setLinearMultistepMethod(LinearMultistepMethod lmm);

    /**
     * @brief returns the nonlinear system solution method
     * @return
     */
    NonlinearSolverIteration getNonlinearSolverIteration() const;

    /**
     * @brief sets the nonlinear system solution method
     * @param iter nonlinear system solution method
     */
    void setNonlinearSolverIteration(NonlinearSolverIteration iter);

    /**
     * @brief getInterpolationType
     * @return
     */
    InterpolationType getInterpolationType() const;

    /**
     * @brief sets the interpolation of the forward solution that is used for the backwards problem
     * @param interpType interpolation type
     */
    void setInterpolationType(InterpolationType interpType);

    /**
     * @brief sets KLU state ordering mode
     * @return
     */
    StateOrdering getStateOrdering() const;

    /**
     * @brief sets KLU state ordering mode (only applies when linsol is set to amici.AMICI_KLU)
     * @param ordering state ordering
     */
    void setStateOrdering(StateOrdering ordering);

    /**
     * @brief returns stability limit detection mode
     * @return stldet can be amici.FALSE (deactivated) or amici.TRUE (activated)
     */
    int getStabilityLimitFlag() const;

    /**
     * @brief set stability limit detection mode
     * @param stldet can be amici.FALSE (deactivated) or amici.TRUE (activated)
     */
    void setStabilityLimitFlag(int stldet);

    /**
     * @brief getLinearSolver
     * @return
     */
    LinearSolver getLinearSolver() const;

    /**
     * @brief setLinearSolver
     * @param linsol
     */
    void setLinearSolver(LinearSolver linsol);

    /**
     * @brief returns the internal sensitivity method
     * @return internal sensitivity method
     */
    InternalSensitivityMethod getInternalSensitivityMethod() const;

    /**
     * @brief sets the internal sensitivity method
     * @param ism internal sensitivity method
     */
    void setInternalSensitivityMethod(InternalSensitivityMethod ism);

    /**
     * @brief Serialize Solver (see boost::serialization::serialize)
     * @param ar Archive to serialize to
     * @param r Data to serialize
     * @param version Version number
     */
    template <class Archive>
    friend void boost::serialization::serialize(Archive &ar, Solver &r, const unsigned int version);

    /**
     * @brief Check equality of data members
     * @param a
     * @param b
     * @return
     */
    friend bool operator ==(const Solver &a, const Solver &b);

  protected:
    /**
     * init initialises the states at the specified initial timepoint
     *
     * @param x initial state variables
     * @param dx initial derivative state variables (DAE only)
     * @param t initial timepoint
     */
    virtual void init(AmiVector *x, AmiVector *dx, realtype t) = 0;

    /**
     * binit initialises the adjoint states at the specified final timepoint
     *
     * @param which identifier of the backwards problem
     * @param xB initial adjoint state variables
     * @param dxB initial adjoint derivative state variables (DAE only)
     * @param t final timepoint
     */
    virtual void binit(int which, AmiVector *xB, AmiVector *dxB, realtype t) = 0;

    /**
     * qbinit initialises the quadrature states at the specified final timepoint
     *
     * @param which identifier of the backwards problem
     * @param qBdot initial adjoint quadrature state variables
     */
    virtual void qbinit(int which, AmiVector *qBdot) = 0;

    /**
     * RootInit initialises the rootfinding for events
     *
     * @param ne number of different events
     */
    virtual void rootInit(int ne) = 0;

    /**
     * SensInit1 initialises the sensitivities at the specified initial
     * timepoint
     *
     * @param sx initial state sensitivities
     * @param sdx initial derivative state sensitivities (DAE only)
     * @param nplist number parameter wrt which sensitivities are to be computed
     */
    virtual void sensInit1(AmiVectorArray *sx, AmiVectorArray *sdx, int nplist) = 0;

    /**
     * SetDenseJacFn sets the dense Jacobian function
     *
     */
    virtual void setDenseJacFn() = 0;

    /**
     * SetSparseJacFn sets the sparse Jacobian function
     *
     */
    virtual void setSparseJacFn() = 0;

    /**
     * SetBandJacFn sets the banded Jacobian function
     *
     */
    virtual void setBandJacFn() = 0;

    /**
     * SetJacTimesVecFn sets the Jacobian vector multiplication function
     *
     */
    virtual void setJacTimesVecFn() = 0;

    /**
     * SetDenseJacFn sets the dense Jacobian function
     *
     * @param which identifier of the backwards problem
     */
    virtual void setDenseJacFnB(int which) = 0;

    /**
     * SetSparseJacFn sets the sparse Jacobian function
     *
     * @param which identifier of the backwards problem
     */
    virtual void setSparseJacFnB(int which) = 0;

    /**
     * SetBandJacFn sets the banded Jacobian function
     *
     * @param which identifier of the backwards problem
     */
    virtual void setBandJacFnB(int which) = 0;

    /**
     * SetJacTimesVecFn sets the Jacobian vector multiplication function
     *
     * @param which identifier of the backwards problem
     */
    virtual void setJacTimesVecFnB(int which) = 0;

    static void wrapErrHandlerFn(int error_code, const char *module,
                                 const char *function, char *msg,
                                 void *eh_data);

    /**
     * Create specifies solver method and initializes solver memory for the
     * forward problem
     */
    virtual void allocateSolver() = 0;

    /**
     * SStolerances sets scalar relative and absolute tolerances for the forward
     * problem
     *
     * @param rtol relative tolerances
     * @param atol absolute tolerances
     */
    virtual void setSStolerances(double rtol, double atol) = 0;

    /**
     * SensSStolerances activates sets scalar relative and absolute tolerances for the
     * sensitivity variables
     *
     * @param rtol relative tolerances
     * @param atol array of absolute tolerances for every sensitivy variable
     */
    virtual void setSensSStolerances(double rtol, double *atol) = 0;

    /**
     * SetSensErrCon specifies whether error control is also enforced for
     * sensitivities for the forward problem
     *
     * @param error_corr activation flag
     */
    virtual void setSensErrCon(bool error_corr) = 0;

    /**
     * SetSensErrCon specifies whether error control is also enforced for the
     * backward quadrature problem
     *
     * @param which identifier of the backwards problem
     * @param flag activation flag
     */
    virtual void setQuadErrConB(int which, bool flag) = 0;

    /**
     * SetErrHandlerFn attaches the error handler function (errMsgIdAndTxt)
     * to the solver
     *
     */
    virtual void setErrHandlerFn() = 0;

    /**
     * SetUserData attaches the user data instance (here this is a Model) to the forward problem
     *
     * @param model Model instance,
     */
    virtual void setUserData(Model *model) = 0;

    /**
     * SetUserDataB attaches the user data instance (here this is a Model) to the backward problem
     *
     * @param which identifier of the backwards problem
     * @param model Model instance,
     */
    virtual void setUserDataB(int which, Model *model) = 0;

    /**
     * SetMaxNumSteps specifies the maximum number of steps for the forward
     * problem
     *
     * @param mxsteps number of steps
     */
    virtual void setMaxNumSteps(long int mxsteps) = 0;

    /**
     * SetMaxNumStepsB specifies the maximum number of steps for the forward
     * problem
     *
     * @param which identifier of the backwards problem
     * @param mxstepsB number of steps
     */
    virtual void setMaxNumStepsB(int which, long int mxstepsB) = 0;

    /**
     * SetStabLimDet activates stability limit detection for the forward
     * problem
     *
     * @param stldet flag for stability limit detection (TRUE or FALSE)
     *
     */
    virtual void setStabLimDet(int stldet) = 0;

    /**
     * SetStabLimDetB activates stability limit detection for the backward
     * problem
     *
     * @param which identifier of the backwards problem
     * @param stldet flag for stability limit detection (TRUE or FALSE)
     *
     */
    virtual void setStabLimDetB(int which, int stldet) = 0;

    /**
     * SetId specify algebraic/differential components (DAE only)
     *
     * @param model model specification
     */
    virtual void setId(Model *model) = 0;

    /**
     * SetId deactivates error control for algebraic components (DAE only)
     *
     * @param flag deactivation flag
     */
    virtual void setSuppressAlg(bool flag) = 0;

    /**
     * SetSensParams specifies the scaling and indexes for sensitivity
     * computation
     *
     * @param p paramaters
     * @param pbar parameter scaling constants
     * @param plist parameter index list
     */
    virtual void setSensParams(realtype *p, realtype *pbar, int *plist) = 0;

    /**
     * getDky interpolates the (derivative of the) solution at the requested
     * timepoint
     *
     * @param t timepoint
     * @param k derivative order
     * @param dky interpolated solution
     */
    virtual void getDky(realtype t, int k, AmiVector *dky) const = 0;

    /**
     * AdjInit initializes the adjoint problem
     *
     */
    virtual void adjInit() = 0;
    
    /**
     * specifies solver method and initializes solver memory for the
     * backward problem
     *
     * @param which identifier of the backwards problem
     */
    virtual void allocateSolverB(int *which) = 0;

    /**
     * SStolerancesB sets relative and absolute tolerances for the backward
     * problem
     *
     * @param which identifier of the backwards problem
     * @param relTolB relative tolerances
     * @param absTolB absolute tolerances
     */
    virtual void setSStolerancesB(int which, realtype relTolB,
                                 realtype absTolB) = 0;

    /**
     * SStolerancesB sets relative and absolute tolerances for the quadrature
     * backward problem
     *
     * @param which identifier of the backwards problem
     * @param reltolQB relative tolerances
     * @param abstolQB absolute tolerances
     */
    virtual void quadSStolerancesB(int which, realtype reltolQB,
                                     realtype abstolQB) = 0;

    /**
     * Dense attaches a dense linear solver to the forward problem
     *
     * @param nx number of state variables
     */
    virtual void dense(int nx) = 0;

    /**
     * DenseB attaches a dense linear solver to the backward problem
     *
     * @param which identifier of the backwards problem
     * @param nx number of state variables
     */
    virtual void denseB(int which, int nx) = 0;

    /**
     * Band attaches a banded linear solver to the forward problem
     *
     * @param nx number of state variables
     * @param ubw upper matrix bandwidth
     * @param lbw lower matrix bandwidth
     */
    virtual void band(int nx, int ubw, int lbw) = 0;

    /**
     * BandB attaches a banded linear solver to the backward problem
     *
     * @param which identifier of the backwards problem
     * @param nx number of state variables
     * @param ubw upper matrix bandwidth
     * @param lbw lower matrix bandwidth
     */
    virtual void bandB(int which, int nx, int ubw, int lbw) = 0;

    /**
     * Diag attaches a diagonal linear solver to the forward problem
     *
     */
    virtual void diag() = 0;

    /**
     * DiagB attaches a diagonal linear solver to the backward problem
     *
     * @param which identifier of the backwards problem
     */
    virtual void diagB(int which) = 0;

    /**
     * DAMISpgmr attaches a scaled predonditioned GMRES linear solver to the
     * forward problem
     *
     * @param prectype preconditioner type PREC_NONE, PREC_LEFT, PREC_RIGHT
     * or PREC_BOTH
     * @param maxl maximum Kryloc subspace dimension
     */
    virtual void spgmr(int prectype, int maxl) = 0;

    /**
     * DAMISpgmrB attaches a scaled predonditioned GMRES linear solver to the
     * backward problem
     *
     * @param which identifier of the backwards problem
     * @param prectype preconditioner type PREC_NONE, PREC_LEFT, PREC_RIGHT
     * or PREC_BOTH
     * @param maxl maximum Kryloc subspace dimension
     */
    virtual void spgmrB(int which, int prectype, int maxl) = 0;

    /**
     * Spbcg attaches a scaled predonditioned Bi-CGStab linear solver to the
     * forward problem
     *
     * @param prectype preconditioner type PREC_NONE, PREC_LEFT, PREC_RIGHT
     * or PREC_BOTH
     * @param maxl maximum Kryloc subspace dimension
     */
    virtual void spbcg(int prectype, int maxl) = 0;

    /**
     * SpbcgB attaches a scaled predonditioned Bi-CGStab linear solver to the
     * backward problem
     *
     * @param which identifier of the backwards problem
     * @param prectype preconditioner type PREC_NONE, PREC_LEFT, PREC_RIGHT
     * or PREC_BOTH
     * @param maxl maximum Kryloc subspace dimension
     */
    virtual void spbcgB(int which, int prectype, int maxl) = 0;

    /**
     * Sptfqmr attaches a scaled predonditioned TFQMR linear solver to the
     * forward problem
     *
     * @param prectype preconditioner type PREC_NONE, PREC_LEFT, PREC_RIGHT
     * or PREC_BOTH
     * @param maxl maximum Kryloc subspace dimension
     */
    virtual void sptfqmr(int prectype, int maxl) = 0;

    /**
     * SptfqmrB attaches a scaled predonditioned TFQMR linear solver to the
     * backward problem
     *
     * @param which identifier of the backwards problem
     * @param prectype preconditioner type PREC_NONE, PREC_LEFT, PREC_RIGHT
     * or PREC_BOTH
     * @param maxl maximum Kryloc subspace dimension
     */
    virtual void sptfqmrB(int which, int prectype, int maxl) = 0;

    /**
     * KLU attaches a sparse linear solver to the forward problem
     *
     * @param nx number of state variables
     * @param nnz number of nonzero entries in the jacobian
     * @param sparsetype sparse storage type, CSC_MAT for column matrix,
     * CSR_MAT for row matrix
     */
    virtual void klu(int nx, int nnz, int sparsetype) = 0;

    /**
     * KLUSetOrdering sets the ordering for the sparse linear solver of the
     * forward problem
     *
     * @param ordering ordering algorithm to reduce fill 0:AMD 1:COLAMD 2:
     * natural ordering
     */
    virtual void kluSetOrdering(int ordering) = 0;

    /**
     * KLUSetOrderingB sets the ordering for the sparse linear solver of the
     * backward problem
     *
     * @param which identifier of the backwards problem
     * @param ordering ordering algorithm to reduce fill 0:AMD 1:COLAMD 2:
     * natural ordering
     */
    virtual void kluSetOrderingB(int which, int ordering) = 0;

    /**
     * KLUB attaches a sparse linear solver to the forward problem
     *
     * @param which identifier of the backwards problem
     * @param nx number of state variables
     * @param nnz number of nonzero entries in the jacobian
     * @param sparsetype sparse storage type, CSC_MAT for column matrix,
     * CSR_MAT for row matrix
     */
    virtual void kluB(int which, int nx, int nnz, int sparsetype) = 0;

    /**
     * getNumSteps reports the number of solver steps
     *
     * @param ami_mem pointer to the solver memory instance (can be from
     * forward or backward problem)
     * @param numsteps output array
     */
    virtual void getNumSteps(void *ami_mem, long int *numsteps) const = 0;

    /**
     * getNumRhsEvals reports the number of right hand evaluations
     *
     * @param ami_mem pointer to the solver memory instance (can be from
     * forward or backward problem)
     * @param numrhsevals output array
     */
    virtual void getNumRhsEvals(void *ami_mem, long int *numrhsevals) const = 0;

    /**
     * getNumErrTestFails reports the number of local error test failures
     *
     * @param ami_mem pointer to the solver memory instance (can be from
     * forward or backward problem)
     * @param numerrtestfails output array
     */
    virtual void getNumErrTestFails(void *ami_mem,
                                      long int *numerrtestfails) const = 0;

    /**
     * getNumNonlinSolvConvFails reports the number of nonlinear convergence
     * failures
     *
     * @param ami_mem pointer to the solver memory instance (can be from
     * forward or backward problem)
     * @param numnonlinsolvconvfails output array
     */
    virtual void
    getNumNonlinSolvConvFails(void *ami_mem,
                                 long int *numnonlinsolvconvfails) const = 0;

    /**
     * Reports the order of the integration method during the
     * last internal step
     *
     * @param ami_mem pointer to the solver memory instance (can be from
     * forward or backward problem)
     * @param order output array
     */
    virtual void getLastOrder(void *ami_mem, int *order) const = 0;

    void initializeLinearSolver(const Model *model);
    void initializeLinearSolverB(const Model *model, const int which);
    
    /**
     * Accessor function to the number of sensitivity parameters in the model stored in the user data
     *
     * @return number of sensitivity parameters
     */
    virtual int nplist() const = 0;
    /**
     * Accessor function to the number of state variables in the model stored in the user data
     *
     * @return number of state variables
     */
    virtual int nx() const = 0;
    /**
     * Accessor function to the model stored in the user data
     *
     * @return user data model
     */
    virtual const Model *getModel() const = 0;
    
    /**
     * checks whether memory for the forward problem has been allocated
     *
     * @return solverMemory->(cv|ida)__MallocDone
     */
    virtual bool getMallocDone() const = 0;
    /**
     * checks whether memory for the backward problem has been allocated
     *
     * @return solverMemory->(cv|ida)__adjMallocDone
     */
    virtual bool getAdjMallocDone() const = 0;

protected:
    
    /**
     * getAdjBmem retrieves the solver memory instance for the backward problem
     *
     * @param which identifier of the backwards problem
     * @param ami_mem pointer to the forward solver memory instance
     * @return ami_memB pointer to the backward solver memory instance
     */
    virtual void *getAdjBmem(void *ami_mem, int which) = 0;
        
    /**
     * updates solver tolerances according to the currently specified member variables
     */
    void applyTolerances();
        
    /**
     * updates FSA solver tolerances according to the currently specified member variables
     */
    void applyTolerancesFSA();
        
    /**
     * updates ASA solver tolerances according to the currently specified member variables
     *
     * @param which identifier of the backwards problem
     */
    void applyTolerancesASA(int which);
    
    /**
     * updates ASA quadrature solver tolerances according to the currently specified member variables
     *
     * @param which identifier of the backwards problem
     */
    void applyQuadTolerancesASA(int which);
    
    /**
     * updates all senstivivity solver tolerances according to the currently specified member variables
     */
    void applySensitivityTolerances();
    
    /** pointer to solver memory block */
    std::unique_ptr<void, std::function<void(void *)>> solverMemory;
    
    /** pointer to solver memory block */
    std::vector<std::unique_ptr<void, std::function<void(void *)>>> solverMemoryB;
    
    /** flag indicating whether the solver was called */
    bool solverWasCalled = false;
    
    /** internal sensitivity method flag used to select the sensitivity solution
     * method. Only applies for Forward Sensitivities. */
    InternalSensitivityMethod ism = InternalSensitivityMethod::simultaneous;
    
    /** specifies the linear multistep method.
     */
    LinearMultistepMethod lmm = LinearMultistepMethod::BDF;
    
    /**
     * specifies the type of nonlinear solver iteration
     */
    NonlinearSolverIteration iter = NonlinearSolverIteration::newton;
    
    /** interpolation type for the forward problem solution which
     * is then used for the backwards problem.
     */
    InterpolationType interpType = InterpolationType::hermite;
    
    /** maximum number of allowed integration steps */
    int maxsteps = 10000;

private:
        
    /** method for sensitivity computation */
    SensitivityMethod sensi_meth = SensitivityMethod::forward;

    /** flag controlling stability limit detection */
    booleantype stldet = true;

    /** state ordering */
    StateOrdering ordering = StateOrdering::AMD;


    /** maximum number of allowed Newton steps for steady state computation */
    int newton_maxsteps = 0;

    /** maximum number of allowed linear steps per Newton step for steady state
     * computation */
    int newton_maxlinsteps = 0;

    /** Preequilibration of model via Newton solver? */
    bool newton_preeq = false;

    /** linear solver specification */
    LinearSolver linsol = LinearSolver::KLU;

    /** absolute tolerances for integration */
    double atol = 1e-16;

    /** relative tolerances for integration */
    double rtol = 1e-8;

    /** absolute tolerances for backward quadratures */
    double quad_atol = 1e-12;

    /** relative tolerances for backward quadratures */
    double quad_rtol = 1e-8;

    /** maximum number of allowed integration steps for backward problem */
    int maxstepsB = 0;

    /** flag indicating whether sensitivities are supposed to be computed */
    SensitivityOrder sensi = SensitivityOrder::none;
};

bool operator ==(const Solver &a, const Solver &b);

} // namespace amici

#endif // AMICISOLVER_H
