#include <stdio.h>
#include <math.h>

#include <dbDefs.h>
#include <registryFunction.h>
#include <subRecord.h>
#include <aSubRecord.h>
#include <epicsExport.h>

int mySubDebug;


//Integrators
static double TempDeltaSat_ant,
              TempIntegral_ant,HumIntegral_ant,
              MistMaker_ant, MistMaker_saturated_ant;


//Predictors
static double HumPredictor_ant, TempPredictor_ant;

// RMSE
static double RMSE_thetaT_ant, RMSE_Temp_P_ant,RMSE_Temp_K_ant ,
              RMSE_thetaH_ant, RMSE_Hum_P_ant,RMSE_Hum_K_ant ;


static long mySubInit(subRecord *precord)
{
    // if (mySubDebug)
        // printf("Record %s called mySubInit(%p)\n",precord->name, (void*) precord);

    return 0;
}

static long mySubProcess(subRecord *precord)
{
    // if (mySubDebug)
        // printf("Record %s called mySubProcess(%p)\n",precord->name, (void*) precord);
    return 0;
}

static long myAsubInit(aSubRecord *precord)
{
    if (mySubDebug)
        printf("Record %s called myAsubInit(%p)\n",
               precord->name, (void*) precord);


     TempDeltaSat_ant=0;

  TempIntegral_ant =0;
  HumIntegral_ant = 0;
  MistMaker_ant=0; MistMaker_saturated_ant=0;

   HumPredictor_ant=50;
   TempPredictor_ant = 25;


   RMSE_Temp_P_ant = 1000;
   RMSE_Temp_K_ant = 0.9999;
   RMSE_thetaT_ant = 0;

   RMSE_Hum_P_ant = 1000;
   RMSE_Hum_K_ant = 0.9999;
   RMSE_thetaT_ant = 0;


    return 0;
}

static long myAsubProcess(aSubRecord *precord)
{
    double Ts=10,
            TempPID_SAT_UP = 4+100/33, TempPID_SAT_DOWN =0,
            APERTURE_SAT_UP =4, APERTURE_SAT_DOWN=0,
            FAN_SAT_UP = 100  , FAN_SAT_DOWN=0,
            MM_SAT_UP=1       , MM_SAT_DOWN=0;

   double TempLambda = 0.9993; // 0.993 corresponde a depender de cerca de um dia

    // Inuts
    double *TempIn = (double *)precord->a;
    double *TempOut = (double *)precord->b;
    double *TempSetpoint = (double *)precord->c;
    double *HumIn = (double *)precord->d;
    double *HumOut = (double *)precord->e;
    double *Fan = (double *)precord->f;
    double *Aperture = (double *)precord->g;
    // double *MistMaker = (double *)precord->h;
    double *Lum = (double *)precord->i;
    double *HumSetpoint = (double *)precord->j;
    // double *TempPredictor_ant = (double *)precord->j;
    // double *RMSE_thetaT_ant = (double *)precord->k;



    // Outputs
    double *vala = (double *)precord->vala;
    double *valb = (double *)precord->valb;
    double *valc = (double *)precord->valc;
    double *vald = (double *)precord->vald; //HumPredictor_ant
    double *vale = (double *)precord->vale;
    double *valf = (double *)precord->valf;
    double *valg = (double *)precord->valg;
    double *valh = (double *)precord->valh;
    double *vali = (double *)precord->vali;
    //Auxiliar
    double  TempPID,TempPID_sat, TempError, TempIntegral, HumError, HumIntegral,
            AperturePID, AperturePID_saturated, FanPID, FanPID_saturated, MistMaker, MistMaker_saturated,
            TempPredictor, HumPredictor,
            RMSE_Temp, RMSE_Hum,
            RMSE_thetaT, RMSE_Temp_K, RMSE_Temp_P,
            RMSE_thetaH, RMSE_Hum_K, RMSE_Hum_P;

    printf("Record %s called myAsubProcess(%p)\n", precord->name, (void*) precord);

    // Feedback Control Greenhouse Temperature PID Ts10
    const double Kp_temp= -75/5,
              Ki_temp = -0.58/5 ,
              Ksat_temp = -0.01;

    //Temp ERROR
    TempError = *TempSetpoint - *TempIn;
    //Integral term
    TempIntegral = TempIntegral_ant + Ts*Ki_temp*(TempError-Ksat_temp*TempDeltaSat_ant);


    //Temp PID
    TempPID =Kp_temp*TempError + TempIntegral;

    TempPID_sat = TempPID;
    if (TempPID_sat>TempPID_SAT_UP) TempPID_sat =TempPID_SAT_UP;
    if (TempPID_sat<TempPID_SAT_DOWN) TempPID_sat =TempPID_SAT_DOWN;

    TempDeltaSat_ant = TempPID-TempPID_sat;

    //Aperture Saturation
    AperturePID_saturated = TempPID;
    if (AperturePID_saturated>APERTURE_SAT_UP) AperturePID_saturated =APERTURE_SAT_UP;
    if (AperturePID_saturated<APERTURE_SAT_DOWN) AperturePID_saturated =APERTURE_SAT_DOWN;
    //Fan Proportional term
    FanPID = 33*(TempPID - AperturePID_saturated);
    //Fan Saturation
    FanPID_saturated= FanPID;
    if (FanPID>FAN_SAT_UP) FanPID_saturated =FAN_SAT_UP;
    if (FanPID<FAN_SAT_DOWN) FanPID_saturated =FAN_SAT_DOWN;




    // Feedback Control Greenhouse
    const double Kp_hum=0.045*0.8,
              Ki_hum= 0.045*1.2/450*0.4,
              Ksat_hum=5,
              Kp_hum_neg=-20*1.1 /*original: -4*/;

    HumError = *HumSetpoint - *HumIn;
    //Integral term
    // HumIntegral = HumIntegral_ant + Ts*(0.009/60)*(HumError - 40*(MistMaker_ant-MistMaker_saturated_ant));
    HumIntegral = HumIntegral_ant + Ts*Ki_hum*(HumError - Ksat_hum*(MistMaker_ant-MistMaker_saturated_ant));

    // MistMaker = 0.05*HumError +HumIntegral + 0.00799*(FanPID_saturated+AperturePID_saturated);
    MistMaker = Kp_hum*HumError + HumIntegral + 0.00799*(FanPID_saturated+AperturePID_saturated);

    MistMaker_saturated= MistMaker;
    if (MistMaker_saturated>MM_SAT_UP) MistMaker_saturated =MM_SAT_UP;
    // if (MistMaker_saturated<MM_SAT_DOWN) MistMaker_saturated =MM_SAT_DOWN;
    if (MistMaker_saturated<-100) MistMaker_saturated =-100;  // alterado

    if (MistMaker < 0){
      double negativeHumError = Kp_hum_neg*MistMaker;
      double AperturePID_saturated_hum = negativeHumError;
      if (AperturePID_saturated_hum>APERTURE_SAT_UP) AperturePID_saturated_hum =APERTURE_SAT_UP;
      if (AperturePID_saturated_hum<APERTURE_SAT_DOWN) AperturePID_saturated_hum =APERTURE_SAT_DOWN;
      //Fan Proportional term
      double FanPID_hum = (33/8)*(negativeHumError - AperturePID_saturated_hum);
      //Fan Saturation
      double FanPID_saturated_hum= FanPID_hum;
      if (FanPID_saturated_hum>FAN_SAT_UP) FanPID_saturated_hum =FAN_SAT_UP;
      if (FanPID_saturated_hum<FAN_SAT_DOWN) FanPID_saturated_hum =FAN_SAT_DOWN;

      AperturePID_saturated = AperturePID_saturated + AperturePID_saturated_hum;
      FanPID_saturated = FanPID_saturated +FanPID_saturated_hum;
    }



    // MistMaker = *MistMaker ;
    // if(*HumIn>70) MistMaker = 0;
    // else if (*HumIn<60) MistMaker = 1;

    // if (FanPID_saturated>0) MistMaker=0;

    // else  do nothing (mantain previous status)



    //LSQ Control Humidity and Temperature
    // TempError = *TempSetpoint - *TempIn;
    // HumError = *HumSetpoint - *HumIn;
    //
    //
    // AperturePID =-26.1262*TempError + 0.7852*HumError;
    // //Aperture Saturation
    // AperturePID_saturated= AperturePID;
    // if (AperturePID_saturated>APERTURE_SAT_UP) AperturePID_saturated =APERTURE_SAT_UP;
    // if (AperturePID_saturated<APERTURE_SAT_DOWN) AperturePID_saturated =APERTURE_SAT_DOWN;
    // //Fan Proportional term
    // FanPID = 4*(AperturePID - AperturePID_saturated);
    // //Fan Saturation
    // FanPID_saturated= FanPID;
    // if (FanPID>FAN_SAT_UP) FanPID_saturated =FAN_SAT_UP;
    // if (FanPID<FAN_SAT_DOWN) FanPID_saturated =FAN_SAT_DOWN;
    //
    // MistMaker = -1.6959*TempError + 0.0659*HumError;
    //
    // MistMaker_saturated = MistMaker;
    // if (MistMaker>MM_SAT_UP) MistMaker_saturated = MM_SAT_UP;
    // if (MistMaker<MM_SAT_DOWN) MistMaker_saturated = MM_SAT_DOWN;



    printf("TempError = %f\n", TempError);
    printf("TempIntegral = %f\n", TempIntegral);
    printf("TempIntegral_ant = %f\n", TempIntegral_ant);
    printf("TempDeltaSat_ant = %f\n", TempDeltaSat_ant);

    printf("AperturePID_saturated = %f\n", AperturePID_saturated);
    printf("FanPID_saturated = %f\n", FanPID_saturated);

    printf("\n");
    printf("Hum Error = %f\n", HumError);
    printf("HumIntegral = %f\n", HumIntegral);
    printf("HumIntegral_ant = %f\n", HumIntegral_ant);
    printf("MistMaker_saturated = %f\n", MistMaker_saturated);


    //****************************************
                  // Predictors
    //****************************************

    //Predict Greenhouse Temperature
    double thetaT3 = -0.047074 *(*TempIn-*TempOut);
    if ((*TempIn -*TempOut)<0) thetaT3 =0;
    double thetaT4 = -0.0013908*(*TempIn-*TempOut);
    if ((*TempIn -*TempOut)<0 )thetaT4 =0;


    TempPredictor = *TempIn -0.02318764*(*TempIn - *TempOut) + 0.000428227*(*Lum) + thetaT3*(AperturePID_saturated) + thetaT4*(FanPID_saturated)  -0.138*MistMaker_saturated;
    RMSE_Temp = sqrt(pow(TempPredictor_ant - *TempIn,2));

    //Estimate RMSE Temp average using kalman filter theory
    RMSE_Temp_K = RMSE_Temp_P_ant/(TempLambda + RMSE_Temp_P_ant);
    RMSE_Temp_P = (1-RMSE_Temp_K)*RMSE_Temp_P_ant/TempLambda;
    RMSE_thetaT = RMSE_thetaT_ant + RMSE_Temp_K*( RMSE_Temp - RMSE_thetaT_ant);


    // printf("TempPredictor = %f\n", TempPredictor);
    // printf("TempPredictor_ant = %f\n", TempPredictor_ant);
    // printf("RMSE_Temp = %f\n", RMSE_Temp);
    // printf("RMSE_thetaT = %f\n", RMSE_thetaT);




    //Predict Greenhouse Humidity
    // HumPredictor = 0.8006*(*HumIn)+ 0.3435*(*HumOut)-1.1024*(AperturePID) -0.0032*(FanPID) +5.3790*(*MistMaker) -0.0630*(*TempIn);
    // double HumPredictor = 0.8765*(*HumIn)+ 0.2052*(*HumOut)-1.6013*(AperturePID_saturated) -0.0051*(FanPID_saturated) +8.0408*(MistMaker) -0.0398*(*TempIn);
    // double HumPredictor = 0.8765*(*HumIn)+ 0.2052*(*HumOut)-1.6013*(AperturePID_saturated) -0.221*((*HumIn-*HumOut)/27)*(FanPID_saturated) +20.0408*(MistMaker) -0.0398*(*TempIn) +2;
if(*HumIn-*HumOut>=30)
    HumPredictor = 0.8765*(*HumIn)+ 0.2052*(*HumOut)-1.6013*(AperturePID_saturated) -0.221*(FanPID_saturated) +20.0408*(MistMaker_saturated) -0.0398*(*TempIn) +2;
else
    HumPredictor = 0.8765*(*HumIn)+ 0.2052*(*HumOut)-1.6013*((*HumIn-*HumOut)/29)*(AperturePID_saturated) -0.221*((*HumIn-*HumOut)/29)*(FanPID_saturated) +18*(MistMaker_saturated) -0.0398*(*TempIn) +2;

    // TODO: change HumPredictor to be an output and HumPredictor_ant to be an input (likeTemp)
    RMSE_Hum = sqrt(pow(HumPredictor_ant - *HumIn,2));

    //Estimate RMSE Temp average using kalman filter theory
    RMSE_Hum_K = RMSE_Hum_P_ant/(TempLambda + RMSE_Hum_P_ant);
    RMSE_Hum_P = (1-RMSE_Hum_K)*RMSE_Hum_P_ant/TempLambda;
    RMSE_thetaH = RMSE_thetaH_ant + RMSE_Hum_K*( RMSE_Hum - RMSE_thetaH_ant);

    // printf("HumPredictor = %f\n", HumPredictor);
    // printf("HumPredictor_ant = %f\n", HumPredictor_ant);
    // printf("RMSE_Hum = %f\n", RMSE_Hum);
    // printf("RMSE_thetaH = %f\n", RMSE_thetaH);

    //****************************************
    //Data to send to outputs
    //****************************************
    *vala = AperturePID_saturated;
    *valb = FanPID_saturated;
    *valc = TempPredictor_ant;
    *vald = HumPredictor_ant;
    *vale = RMSE_thetaT;
    *valf = MistMaker_saturated;
    *valg = RMSE_Temp;
    *valh = RMSE_Hum;
    *vali = RMSE_thetaH;


    TempIntegral_ant = TempIntegral;
    HumIntegral_ant = HumIntegral;
    MistMaker_ant=MistMaker; MistMaker_saturated_ant = MistMaker_saturated;

    RMSE_Temp_P_ant = RMSE_Temp_P;
    RMSE_Temp_K_ant = RMSE_Temp_K;
    RMSE_thetaT_ant = RMSE_thetaT;

    TempPredictor_ant = TempPredictor;
    HumPredictor_ant = HumPredictor;

    RMSE_Hum_P_ant = RMSE_Hum_P;
    RMSE_Hum_K_ant = RMSE_Hum_K;
    RMSE_thetaH_ant = RMSE_thetaH;
    // RMSE_Temp_ant = RMSE_Temp;
    // printf("VALA after change %d\n", precord->vala);
    return 0;
}

/* Register these symbols for use by IOC code: */

epicsExportAddress(int, mySubDebug);
// epicsExportAddress(int, Ts);
// epicsExportAddress(double, RMSE_Temp_P_ant);
// epicsExportAddress(double, RMSE_Temp_K_ant);

epicsRegisterFunction(mySubInit);
epicsRegisterFunction(mySubProcess);
epicsRegisterFunction(myAsubInit);
epicsRegisterFunction(myAsubProcess);
