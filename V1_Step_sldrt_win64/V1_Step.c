/*
 * V1_Step.c
 *
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * Code generation for model "V1_Step".
 *
 * Model version              : 6.2
 * Simulink Coder version : 9.5 (R2021a) 14-Nov-2020
 * C source code generated on : Tue Mar 28 13:14:52 2023
 *
 * Target selection: sldrt.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: Intel->x86-64 (Windows64)
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "V1_Step.h"
#include "V1_Step_private.h"
#include "V1_Step_dt.h"

/* options for Simulink Desktop Real-Time board 0 */
static double SLDRTBoardOptions0[] = {
  0.0,
  0.0,
  0.0,
  0.0,
  0.0,
  0.0,
  0.0,
};

/* list of Simulink Desktop Real-Time timers */
const int SLDRTTimerCount = 1;
const double SLDRTTimers[2] = {
  0.01, 0.0,
};

/* list of Simulink Desktop Real-Time boards */
const int SLDRTBoardCount = 1;
SLDRTBOARD SLDRTBoards[1] = {
  { "National_Instruments/PCIe-6321", 4294967295U, 7, SLDRTBoardOptions0 },
};

/* Block signals (default storage) */
B_V1_Step_T V1_Step_B;

/* Continuous states */
X_V1_Step_T V1_Step_X;

/* Block states (default storage) */
DW_V1_Step_T V1_Step_DW;

/* Real-time model */
static RT_MODEL_V1_Step_T V1_Step_M_;
RT_MODEL_V1_Step_T *const V1_Step_M = &V1_Step_M_;

/*
 * This function updates continuous states using the ODE1 fixed-step
 * solver algorithm
 */
static void rt_ertODEUpdateContinuousStates(RTWSolverInfo *si )
{
  time_T tnew = rtsiGetSolverStopTime(si);
  time_T h = rtsiGetStepSize(si);
  real_T *x = rtsiGetContStates(si);
  ODE1_IntgData *id = (ODE1_IntgData *)rtsiGetSolverData(si);
  real_T *f0 = id->f[0];
  int_T i;
  int_T nXc = 1;
  rtsiSetSimTimeStep(si,MINOR_TIME_STEP);
  rtsiSetdX(si, f0);
  V1_Step_derivatives();
  rtsiSetT(si, tnew);
  for (i = 0; i < nXc; ++i) {
    x[i] += h * f0[i];
  }

  rtsiSetSimTimeStep(si,MAJOR_TIME_STEP);
}

/* Model output function */
void V1_Step_output(void)
{
  real_T lastTime;
  real_T rtb_ud;
  real_T rtb_up;
  real_T *lastU;
  if (rtmIsMajorTimeStep(V1_Step_M)) {
    /* set solver stop time */
    if (!(V1_Step_M->Timing.clockTick0+1)) {
      rtsiSetSolverStopTime(&V1_Step_M->solverInfo,
                            ((V1_Step_M->Timing.clockTickH0 + 1) *
        V1_Step_M->Timing.stepSize0 * 4294967296.0));
    } else {
      rtsiSetSolverStopTime(&V1_Step_M->solverInfo,
                            ((V1_Step_M->Timing.clockTick0 + 1) *
        V1_Step_M->Timing.stepSize0 + V1_Step_M->Timing.clockTickH0 *
        V1_Step_M->Timing.stepSize0 * 4294967296.0));
    }
  }                                    /* end MajorTimeStep */

  /* Update absolute time of base rate at minor time step */
  if (rtmIsMinorTimeStep(V1_Step_M)) {
    V1_Step_M->Timing.t[0] = rtsiGetT(&V1_Step_M->solverInfo);
  }

  /* Step: '<Root>/Step' */
  if (V1_Step_M->Timing.t[0] < V1_Step_P.Step_Time) {
    /* Step: '<Root>/Step' */
    V1_Step_B.w = V1_Step_P.Step_Y0;
  } else {
    /* Step: '<Root>/Step' */
    V1_Step_B.w = V1_Step_P.Step_YFinal;
  }

  /* End of Step: '<Root>/Step' */
  if (rtmIsMajorTimeStep(V1_Step_M)) {
    /* S-Function (sldrtai): '<Root>/Analog Input' */
    /* S-Function Block: <Root>/Analog Input */
    {
      ANALOGIOPARM parm;
      parm.mode = (RANGEMODE) V1_Step_P.AnalogInput_RangeMode;
      parm.rangeidx = V1_Step_P.AnalogInput_VoltRange;
      RTBIO_DriverIO(0, ANALOGINPUT, IOREAD, 1, &V1_Step_P.AnalogInput_Channels,
                     &V1_Step_B.y, &parm);
    }
  }

  /* Gain: '<Root>/K_R' incorporates:
   *  Sum: '<Root>/Sum'
   */
  rtb_up = (V1_Step_B.w - V1_Step_B.y) * V1_Step_P.K_R;

  /* Gain: '<Root>/T_D' */
  V1_Step_B.T_D = V1_Step_P.T_D * rtb_up;

  /* Derivative: '<Root>/Derivative' */
  rtb_ud = V1_Step_M->Timing.t[0];
  if ((V1_Step_DW.TimeStampA >= rtb_ud) && (V1_Step_DW.TimeStampB >= rtb_ud)) {
    rtb_ud = 0.0;
  } else {
    lastTime = V1_Step_DW.TimeStampA;
    lastU = &V1_Step_DW.LastUAtTimeA;
    if (V1_Step_DW.TimeStampA < V1_Step_DW.TimeStampB) {
      if (V1_Step_DW.TimeStampB < rtb_ud) {
        lastTime = V1_Step_DW.TimeStampB;
        lastU = &V1_Step_DW.LastUAtTimeB;
      }
    } else if (V1_Step_DW.TimeStampA >= rtb_ud) {
      lastTime = V1_Step_DW.TimeStampB;
      lastU = &V1_Step_DW.LastUAtTimeB;
    }

    rtb_ud = (V1_Step_B.T_D - *lastU) / (rtb_ud - lastTime);
  }

  /* End of Derivative: '<Root>/Derivative' */

  /* ManualSwitch: '<Root>/Manual Switch' incorporates:
   *  Integrator: '<Root>/Integrator'
   */
  if (V1_Step_P.ManualSwitch_CurrentSetting == 1) {
    lastTime = V1_Step_X.Integrator_CSTATE;
  } else {
    lastTime = 0.0;
  }

  /* End of ManualSwitch: '<Root>/Manual Switch' */

  /* ManualSwitch: '<Root>/Manual Switch1' */
  if (V1_Step_P.ManualSwitch1_CurrentSetting == 1) {
    rtb_ud = 0.0;
  }

  /* End of ManualSwitch: '<Root>/Manual Switch1' */

  /* Sum: '<Root>/Sum1' */
  rtb_ud += rtb_up + lastTime;

  /* Saturate: '<Root>/Saturation' */
  if (rtb_ud > V1_Step_P.Saturation_UpperSat) {
    /* Saturate: '<Root>/Saturation' */
    V1_Step_B.u = V1_Step_P.Saturation_UpperSat;
  } else if (rtb_ud < V1_Step_P.Saturation_LowerSat) {
    /* Saturate: '<Root>/Saturation' */
    V1_Step_B.u = V1_Step_P.Saturation_LowerSat;
  } else {
    /* Saturate: '<Root>/Saturation' */
    V1_Step_B.u = rtb_ud;
  }

  /* End of Saturate: '<Root>/Saturation' */
  if (rtmIsMajorTimeStep(V1_Step_M)) {
    /* S-Function (sldrtao): '<Root>/Analog Output' */
    /* S-Function Block: <Root>/Analog Output */
    {
      {
        ANALOGIOPARM parm;
        parm.mode = (RANGEMODE) V1_Step_P.AnalogOutput_RangeMode;
        parm.rangeidx = V1_Step_P.AnalogOutput_VoltRange;
        RTBIO_DriverIO(0, ANALOGOUTPUT, IOWRITE, 1,
                       &V1_Step_P.AnalogOutput_Channels, ((real_T*)
          (&V1_Step_B.u)), &parm);
      }
    }
  }

  /* Gain: '<Root>/1//T_I' */
  V1_Step_B.uT_I = 1.0 / V1_Step_P.T_I * rtb_up;
}

/* Model update function */
void V1_Step_update(void)
{
  real_T *lastU;

  /* Update for Derivative: '<Root>/Derivative' */
  if (V1_Step_DW.TimeStampA == (rtInf)) {
    V1_Step_DW.TimeStampA = V1_Step_M->Timing.t[0];
    lastU = &V1_Step_DW.LastUAtTimeA;
  } else if (V1_Step_DW.TimeStampB == (rtInf)) {
    V1_Step_DW.TimeStampB = V1_Step_M->Timing.t[0];
    lastU = &V1_Step_DW.LastUAtTimeB;
  } else if (V1_Step_DW.TimeStampA < V1_Step_DW.TimeStampB) {
    V1_Step_DW.TimeStampA = V1_Step_M->Timing.t[0];
    lastU = &V1_Step_DW.LastUAtTimeA;
  } else {
    V1_Step_DW.TimeStampB = V1_Step_M->Timing.t[0];
    lastU = &V1_Step_DW.LastUAtTimeB;
  }

  *lastU = V1_Step_B.T_D;

  /* End of Update for Derivative: '<Root>/Derivative' */
  if (rtmIsMajorTimeStep(V1_Step_M)) {
    rt_ertODEUpdateContinuousStates(&V1_Step_M->solverInfo);
  }

  /* Update absolute time for base rate */
  /* The "clockTick0" counts the number of times the code of this task has
   * been executed. The absolute time is the multiplication of "clockTick0"
   * and "Timing.stepSize0". Size of "clockTick0" ensures timer will not
   * overflow during the application lifespan selected.
   * Timer of this task consists of two 32 bit unsigned integers.
   * The two integers represent the low bits Timing.clockTick0 and the high bits
   * Timing.clockTickH0. When the low bit overflows to 0, the high bits increment.
   */
  if (!(++V1_Step_M->Timing.clockTick0)) {
    ++V1_Step_M->Timing.clockTickH0;
  }

  V1_Step_M->Timing.t[0] = rtsiGetSolverStopTime(&V1_Step_M->solverInfo);

  {
    /* Update absolute timer for sample time: [0.01s, 0.0s] */
    /* The "clockTick1" counts the number of times the code of this task has
     * been executed. The absolute time is the multiplication of "clockTick1"
     * and "Timing.stepSize1". Size of "clockTick1" ensures timer will not
     * overflow during the application lifespan selected.
     * Timer of this task consists of two 32 bit unsigned integers.
     * The two integers represent the low bits Timing.clockTick1 and the high bits
     * Timing.clockTickH1. When the low bit overflows to 0, the high bits increment.
     */
    if (!(++V1_Step_M->Timing.clockTick1)) {
      ++V1_Step_M->Timing.clockTickH1;
    }

    V1_Step_M->Timing.t[1] = V1_Step_M->Timing.clockTick1 *
      V1_Step_M->Timing.stepSize1 + V1_Step_M->Timing.clockTickH1 *
      V1_Step_M->Timing.stepSize1 * 4294967296.0;
  }
}

/* Derivatives for root system: '<Root>' */
void V1_Step_derivatives(void)
{
  XDot_V1_Step_T *_rtXdot;
  _rtXdot = ((XDot_V1_Step_T *) V1_Step_M->derivs);

  /* Derivatives for Integrator: '<Root>/Integrator' */
  _rtXdot->Integrator_CSTATE = V1_Step_B.uT_I;
}

/* Model initialize function */
void V1_Step_initialize(void)
{
  /* Start for S-Function (sldrtao): '<Root>/Analog Output' */

  /* S-Function Block: <Root>/Analog Output */
  {
    {
      ANALOGIOPARM parm;
      parm.mode = (RANGEMODE) V1_Step_P.AnalogOutput_RangeMode;
      parm.rangeidx = V1_Step_P.AnalogOutput_VoltRange;
      RTBIO_DriverIO(0, ANALOGOUTPUT, IOWRITE, 1,
                     &V1_Step_P.AnalogOutput_Channels,
                     &V1_Step_P.AnalogOutput_InitialValue, &parm);
    }
  }

  /* InitializeConditions for Integrator: '<Root>/Integrator' */
  V1_Step_X.Integrator_CSTATE = V1_Step_P.Integrator_IC;

  /* InitializeConditions for Derivative: '<Root>/Derivative' */
  V1_Step_DW.TimeStampA = (rtInf);
  V1_Step_DW.TimeStampB = (rtInf);
}

/* Model terminate function */
void V1_Step_terminate(void)
{
  /* Terminate for S-Function (sldrtao): '<Root>/Analog Output' */

  /* S-Function Block: <Root>/Analog Output */
  {
    {
      ANALOGIOPARM parm;
      parm.mode = (RANGEMODE) V1_Step_P.AnalogOutput_RangeMode;
      parm.rangeidx = V1_Step_P.AnalogOutput_VoltRange;
      RTBIO_DriverIO(0, ANALOGOUTPUT, IOWRITE, 1,
                     &V1_Step_P.AnalogOutput_Channels,
                     &V1_Step_P.AnalogOutput_FinalValue, &parm);
    }
  }
}

/*========================================================================*
 * Start of Classic call interface                                        *
 *========================================================================*/

/* Solver interface called by GRT_Main */
#ifndef USE_GENERATED_SOLVER

void rt_ODECreateIntegrationData(RTWSolverInfo *si)
{
  UNUSED_PARAMETER(si);
  return;
}                                      /* do nothing */

void rt_ODEDestroyIntegrationData(RTWSolverInfo *si)
{
  UNUSED_PARAMETER(si);
  return;
}                                      /* do nothing */

void rt_ODEUpdateContinuousStates(RTWSolverInfo *si)
{
  UNUSED_PARAMETER(si);
  return;
}                                      /* do nothing */

#endif

void MdlOutputs(int_T tid)
{
  V1_Step_output();
  UNUSED_PARAMETER(tid);
}

void MdlUpdate(int_T tid)
{
  V1_Step_update();
  UNUSED_PARAMETER(tid);
}

void MdlInitializeSizes(void)
{
}

void MdlInitializeSampleTimes(void)
{
}

void MdlInitialize(void)
{
}

void MdlStart(void)
{
  V1_Step_initialize();
}

void MdlTerminate(void)
{
  V1_Step_terminate();
}

/* Registration function */
RT_MODEL_V1_Step_T *V1_Step(void)
{
  /* Registration code */

  /* initialize non-finites */
  rt_InitInfAndNaN(sizeof(real_T));

  /* initialize real-time model */
  (void) memset((void *)V1_Step_M, 0,
                sizeof(RT_MODEL_V1_Step_T));

  {
    /* Setup solver object */
    rtsiSetSimTimeStepPtr(&V1_Step_M->solverInfo, &V1_Step_M->Timing.simTimeStep);
    rtsiSetTPtr(&V1_Step_M->solverInfo, &rtmGetTPtr(V1_Step_M));
    rtsiSetStepSizePtr(&V1_Step_M->solverInfo, &V1_Step_M->Timing.stepSize0);
    rtsiSetdXPtr(&V1_Step_M->solverInfo, &V1_Step_M->derivs);
    rtsiSetContStatesPtr(&V1_Step_M->solverInfo, (real_T **)
                         &V1_Step_M->contStates);
    rtsiSetNumContStatesPtr(&V1_Step_M->solverInfo,
      &V1_Step_M->Sizes.numContStates);
    rtsiSetNumPeriodicContStatesPtr(&V1_Step_M->solverInfo,
      &V1_Step_M->Sizes.numPeriodicContStates);
    rtsiSetPeriodicContStateIndicesPtr(&V1_Step_M->solverInfo,
      &V1_Step_M->periodicContStateIndices);
    rtsiSetPeriodicContStateRangesPtr(&V1_Step_M->solverInfo,
      &V1_Step_M->periodicContStateRanges);
    rtsiSetErrorStatusPtr(&V1_Step_M->solverInfo, (&rtmGetErrorStatus(V1_Step_M)));
    rtsiSetRTModelPtr(&V1_Step_M->solverInfo, V1_Step_M);
  }

  rtsiSetSimTimeStep(&V1_Step_M->solverInfo, MAJOR_TIME_STEP);
  V1_Step_M->intgData.f[0] = V1_Step_M->odeF[0];
  V1_Step_M->contStates = ((real_T *) &V1_Step_X);
  rtsiSetSolverData(&V1_Step_M->solverInfo, (void *)&V1_Step_M->intgData);
  rtsiSetSolverName(&V1_Step_M->solverInfo,"ode1");

  /* Initialize timing info */
  {
    int_T *mdlTsMap = V1_Step_M->Timing.sampleTimeTaskIDArray;
    mdlTsMap[0] = 0;
    mdlTsMap[1] = 1;
    V1_Step_M->Timing.sampleTimeTaskIDPtr = (&mdlTsMap[0]);
    V1_Step_M->Timing.sampleTimes = (&V1_Step_M->Timing.sampleTimesArray[0]);
    V1_Step_M->Timing.offsetTimes = (&V1_Step_M->Timing.offsetTimesArray[0]);

    /* task periods */
    V1_Step_M->Timing.sampleTimes[0] = (0.0);
    V1_Step_M->Timing.sampleTimes[1] = (0.01);

    /* task offsets */
    V1_Step_M->Timing.offsetTimes[0] = (0.0);
    V1_Step_M->Timing.offsetTimes[1] = (0.0);
  }

  rtmSetTPtr(V1_Step_M, &V1_Step_M->Timing.tArray[0]);

  {
    int_T *mdlSampleHits = V1_Step_M->Timing.sampleHitArray;
    mdlSampleHits[0] = 1;
    mdlSampleHits[1] = 1;
    V1_Step_M->Timing.sampleHits = (&mdlSampleHits[0]);
  }

  rtmSetTFinal(V1_Step_M, 15.0);
  V1_Step_M->Timing.stepSize0 = 0.01;
  V1_Step_M->Timing.stepSize1 = 0.01;

  /* External mode info */
  V1_Step_M->Sizes.checksums[0] = (3927101412U);
  V1_Step_M->Sizes.checksums[1] = (1274601295U);
  V1_Step_M->Sizes.checksums[2] = (4093823701U);
  V1_Step_M->Sizes.checksums[3] = (204356423U);

  {
    static const sysRanDType rtAlwaysEnabled = SUBSYS_RAN_BC_ENABLE;
    static RTWExtModeInfo rt_ExtModeInfo;
    static const sysRanDType *systemRan[1];
    V1_Step_M->extModeInfo = (&rt_ExtModeInfo);
    rteiSetSubSystemActiveVectorAddresses(&rt_ExtModeInfo, systemRan);
    systemRan[0] = &rtAlwaysEnabled;
    rteiSetModelMappingInfoPtr(V1_Step_M->extModeInfo,
      &V1_Step_M->SpecialInfo.mappingInfo);
    rteiSetChecksumsPtr(V1_Step_M->extModeInfo, V1_Step_M->Sizes.checksums);
    rteiSetTPtr(V1_Step_M->extModeInfo, rtmGetTPtr(V1_Step_M));
  }

  V1_Step_M->solverInfoPtr = (&V1_Step_M->solverInfo);
  V1_Step_M->Timing.stepSize = (0.01);
  rtsiSetFixedStepSize(&V1_Step_M->solverInfo, 0.01);
  rtsiSetSolverMode(&V1_Step_M->solverInfo, SOLVER_MODE_SINGLETASKING);

  /* block I/O */
  V1_Step_M->blockIO = ((void *) &V1_Step_B);

  {
    V1_Step_B.w = 0.0;
    V1_Step_B.y = 0.0;
    V1_Step_B.T_D = 0.0;
    V1_Step_B.u = 0.0;
    V1_Step_B.uT_I = 0.0;
  }

  /* parameters */
  V1_Step_M->defaultParam = ((real_T *)&V1_Step_P);

  /* states (continuous) */
  {
    real_T *x = (real_T *) &V1_Step_X;
    V1_Step_M->contStates = (x);
    (void) memset((void *)&V1_Step_X, 0,
                  sizeof(X_V1_Step_T));
  }

  /* states (dwork) */
  V1_Step_M->dwork = ((void *) &V1_Step_DW);
  (void) memset((void *)&V1_Step_DW, 0,
                sizeof(DW_V1_Step_T));
  V1_Step_DW.TimeStampA = 0.0;
  V1_Step_DW.LastUAtTimeA = 0.0;
  V1_Step_DW.TimeStampB = 0.0;
  V1_Step_DW.LastUAtTimeB = 0.0;

  /* data type transition information */
  {
    static DataTypeTransInfo dtInfo;
    (void) memset((char_T *) &dtInfo, 0,
                  sizeof(dtInfo));
    V1_Step_M->SpecialInfo.mappingInfo = (&dtInfo);
    dtInfo.numDataTypes = 14;
    dtInfo.dataTypeSizes = &rtDataTypeSizes[0];
    dtInfo.dataTypeNames = &rtDataTypeNames[0];

    /* Block I/O transition table */
    dtInfo.BTransTable = &rtBTransTable;

    /* Parameters transition table */
    dtInfo.PTransTable = &rtPTransTable;
  }

  /* Initialize Sizes */
  V1_Step_M->Sizes.numContStates = (1);/* Number of continuous states */
  V1_Step_M->Sizes.numPeriodicContStates = (0);
                                      /* Number of periodic continuous states */
  V1_Step_M->Sizes.numY = (0);         /* Number of model outputs */
  V1_Step_M->Sizes.numU = (0);         /* Number of model inputs */
  V1_Step_M->Sizes.sysDirFeedThru = (0);/* The model is not direct feedthrough */
  V1_Step_M->Sizes.numSampTimes = (2); /* Number of sample times */
  V1_Step_M->Sizes.numBlocks = (14);   /* Number of blocks */
  V1_Step_M->Sizes.numBlockIO = (5);   /* Number of block outputs */
  V1_Step_M->Sizes.numBlockPrms = (23);/* Sum of parameter "widths" */
  return V1_Step_M;
}

/*========================================================================*
 * End of Classic call interface                                          *
 *========================================================================*/
