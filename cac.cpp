#include "cac.h"



Cac::Cac(QWidget *parent) :
    QWidget(parent)
{


}

bool Cac::intervalCalculation()
{


}

bool Cac:: calibrationCalculation( resultVal  *   result ,QString Name,unsigned char type,unsigned int *W,unsigned int *R,unsigned int * G,unsigned int *B,unsigned int* rgbResult)
{
    QString w,r,g,b;
unsigned int JIEGUO[14]={0};
    for(int i=0;i<13;i++)
    {

    printf("cac rgb: count:%d   W: %d  R: %d  G: %d  B: %d\n",i,result[i].wrgb_value[0],result[i].wrgb_value[1],result[i].wrgb_value[2],result[i].wrgb_value[3]);
    }

   printf("cac wb:   W:%d  R:%d  G:%d B:%d  \n",result[0].white_value[0],
                                                                       result[0].white_value[1],
                                                                       result[0].white_value[2],
                                                                       result[0].white_value[3]
              );


    switch(type)
    {
        case R10T:
//                        int index;

//                        switch(index)
//                        {
//                        case 0:
//                              //  uiShowRgb(result[10].wrgb_value[0],result[10].wrgb_value[1],result[10].wrgb_value[2],result[10].wrgb_value[3]);

//                        break;

//                        case 1:
//                             //     uiShowRgb(result[9].wrgb_value[0],result[9].wrgb_value[1],result[9].wrgb_value[2],result[9].wrgb_value[3]);
//                        break;

//                        case 2:
//                         //     uiShowRgb(result[8].wrgb_value[0],result[8].wrgb_value[1],result[8].wrgb_value[2],result[8].wrgb_value[3]);
//                        break;

//                        case 3:
//                            //      uiShowRgb(result[7].wrgb_value[0],result[7].wrgb_value[1],result[7].wrgb_value[2],result[7].wrgb_value[3]);
//                        break;

//                        case 4:
//                             //  uiShowRgb(result[6].wrgb_value[0],result[6].wrgb_value[1],result[6].wrgb_value[2],result[6].wrgb_value[3]);
//                        break;

//                        case 5:
//                            //  uiShowRgb(result[5].wrgb_value[0],result[5].wrgb_value[1],result[5].wrgb_value[2],result[5].wrgb_value[3]);
//                        break;

//                        case 6:
//                           //  uiShowRgb(result[4].wrgb_value[0],result[4].wrgb_value[1],result[4].wrgb_value[2],result[4].wrgb_value[3]);
//                        break;

//                        case 7:
//                            //   uiShowRgb(result[3].wrgb_value[0],result[3].wrgb_value[1],result[3].wrgb_value[2],result[3].wrgb_value[3]);
//                        break;

//                        case 8:
//                          //  uiShowRgb(result[2].wrgb_value[0],result[2].wrgb_value[1],result[2].wrgb_value[2],result[2].wrgb_value[3]);
//                        break;

//                        case 9:
//                             //    uiShowRgb(result[1].wrgb_value[0],result[1].wrgb_value[1],result[1].wrgb_value[2],result[1].wrgb_value[3]);
//                        break;

//                        case 10:
//                               // uiShowRgb(result[0].wrgb_value[0],result[0].wrgb_value[1],result[0].wrgb_value[2],result[0].wrgb_value[3]);
//                        break;

//                        default:break;
//                        }
        break;


        case R113:
                        //BIL
                        if(Name ==QString::fromLocal8Bit("BIL")) {
                            rgbCalculation(  2,0,
                                                       result[12].wrgb_value,
                                                       result[0].white_value,
                                                       result[0].wrgb_value,
                                                       JIEGUO );

                                    *W=result[12].wrgb_value[0];
                                    *R=result[12].wrgb_value[1];
                                    *G=result[12].wrgb_value[2];
                                    *B=result[12].wrgb_value[3];
                                    *rgbResult=JIEGUO[1];
                                    printf("[debug]---->BIL %d %d %d %d %d \n",*W,*R,*G,*B,*rgbResult);
                            }

                        //URO
                        if(Name ==QString::fromLocal8Bit("URO")){

                                  rgbCalculation(  2,1,
                                                                    result[11].wrgb_value,
                                                                    result[0].white_value,
                                                                    result[0].wrgb_value,
                                                                    JIEGUO );

                                 *W =result[11].wrgb_value[0];
                                 *R = result[11].wrgb_value[1];
                                 *G= result[11].wrgb_value[2];
                                 *B= result[11].wrgb_value[3];
                                *rgbResult  =JIEGUO[0];
                          }


                        //KET
                        if(Name ==QString::fromLocal8Bit("KET")) {
                                 rgbCalculation(  2,2,
                                                                          result[10].wrgb_value,
                                                                          result[0].white_value,
                                                                          result[0].wrgb_value,
                                                                          JIEGUO );

                                   * W = result[10].wrgb_value[0],
                                    *R = result[10].wrgb_value[1],
                                    *G = result[10].wrgb_value[2],
                                    *B = result[10].wrgb_value[3],
                                    *rgbResult = JIEGUO[2];
                          }


                        //BLD
                        if(Name ==QString::fromLocal8Bit("BLD")){
                                 rgbCalculation(  2,3,
                                                                          result[9].wrgb_value,
                                                                          result[0].white_value,
                                                                          result[0].wrgb_value,
                                                                          JIEGUO );
                            *W=result[9].wrgb_value[0];
                            *R=result[9].wrgb_value[1];
                            *G=result[9].wrgb_value[2];
                            *B=result[9].wrgb_value[3];
                            *rgbResult=JIEGUO[3];
                        }


                            //PRO
                     if(Name ==QString::fromLocal8Bit("PRO")){
                                 rgbCalculation(  2,4,
                                                                          result[8].wrgb_value,
                                                                          result[0].white_value,
                                                                          result[0].wrgb_value,
                                                                          JIEGUO );


                                 *W=result[8].wrgb_value[0];
                                 *R=result[8].wrgb_value[1];
                                 *G=result[8].wrgb_value[2];
                                 *B=result[8].wrgb_value[3];
                                 *rgbResult=JIEGUO[4];
                           }

                        //NIT
                        if(Name ==QString::fromLocal8Bit("NIT")){
                                rgbCalculation(  2,5,
                                                                         result[7].wrgb_value,
                                                                         result[0].white_value,
                                                                         result[0].wrgb_value,
                                                                         JIEGUO );


                                *W=result[7].wrgb_value[0];
                                *R=result[7].wrgb_value[1];
                                *G=result[7].wrgb_value[2];
                                *B=result[7].wrgb_value[3];
                                *rgbResult=JIEGUO[5];

                        }


                          //WBC
                         if(Name ==QString::fromLocal8Bit("WBC")){
                                 rgbCalculation(  2,6,
                                                                          result[6].wrgb_value,
                                                                          result[0].white_value,
                                                                          result[0].wrgb_value,
                                                                          JIEGUO );

                                *W=result[6].wrgb_value[0];
                                 *R=result[6].wrgb_value[1];
                                 *G=result[6].wrgb_value[2];
                                 *B=result[6].wrgb_value[3];
                                 *rgbResult=JIEGUO[6];
                            }


                            if(Name ==QString::fromLocal8Bit("GLU")){ //GLU
                                    rgbCalculation(  2,7,
                                                                            result[5].wrgb_value,
                                                                            result[0].white_value,
                                                                            result[0].wrgb_value,
                                                                            JIEGUO );
                                    *W=result[5].wrgb_value[0];
                                    *R=result[5].wrgb_value[1];
                                    *G=result[5].wrgb_value[2];
                                    *B=result[5].wrgb_value[3];
                                    *rgbResult=JIEGUO[7];

                            }


                        //SG
                            if(Name ==QString::fromLocal8Bit("SG")){
                                    rgbCalculation(  2,8,
                                                                             result[4].wrgb_value,
                                                                             result[0].white_value,
                                                                             result[0].wrgb_value,
                                                                             JIEGUO );

                                        *W=result[4].wrgb_value[0];
                                        *R=result[4].wrgb_value[1];
                                        *G=result[4].wrgb_value[2];
                                        *B=result[4].wrgb_value[3];
                                        *rgbResult=JIEGUO[8];

                                }

                        //PH
                          if(Name ==QString::fromLocal8Bit("PH")){
                                   rgbCalculation(  2,9,
                                                                             result[3].wrgb_value,
                                                                             result[0].white_value,
                                                                             result[0].wrgb_value,
                                                                             JIEGUO );
                                   *W=result[3].wrgb_value[0];
                                   *R=result[3].wrgb_value[1];
                                   *G=result[3].wrgb_value[2];
                                   *B=result[3].wrgb_value[3];
                                   *rgbResult=JIEGUO[9];

                            }


                        //VC
                                if(Name ==QString::fromLocal8Bit("VC")){
                                        rgbCalculation(  2,10,
                                                                         result[2].wrgb_value,
                                                                         result[0].white_value,
                                                                         result[0].wrgb_value,
                                                                         JIEGUO );

                                       *W=result[2].wrgb_value[0];
                                        *R=result[2].wrgb_value[1];
                                        *G=result[2].wrgb_value[2];
                                        *B=result[2].wrgb_value[3];
                                        *rgbResult=JIEGUO[10];
                                }


                                //CC
                                if(Name ==QString::fromLocal8Bit("CC")){
                                             rgbCalculation(  2,11,
                                                                                      result[1].wrgb_value,
                                                                                      result[0].white_value,
                                                                                      result[0].wrgb_value,
                                                                                      JIEGUO );

                                                     *W=result[1].wrgb_value[0];
                                                     *R=result[1].wrgb_value[1];
                                                     *G=result[1].wrgb_value[2];
                                                     *B=result[1].wrgb_value[3];
                                                     *rgbResult = JIEGUO[11];
                                            }

                                              //BPH
                                             //                              uiShowRgb(result[0].wrgb_value[0],result[0].wrgb_value[1],result[0].wrgb_value[2],result[0].wrgb_value[3],result[0].wrgb_value[0]);
                                              //                                printf(" BPH CAC  IS:%d  \n",result[0].wrgb_value[0]);
                            break;

        default:break;
    }
}

//sys/class/leds/beeper-pwm/device/leds/beeper-pwm
unsigned char Cac::rgbCalculation (unsigned char SHZHXH,unsigned char weizhi,unsigned int *CLCORNO, unsigned int *BPH,unsigned int *JSBPH,unsigned int  *JIEGUO)
{
   //unsigned char weizhi=0;
  volatile unsigned int CESHIZHI[5]={0};
  volatile long zwfwzh;
  volatile long zwfwbzh;
  volatile long zwfwzhb;

 unsigned char  printxh[5][12]={
    0,1,2,3,4,5,6,7,8,9,11,12,//11MA
    0,1,2,3,4,5,6,7,8,9,10,11,//12MA
    1,0,2,3,4,5,6,7,8,9,10,12,//11-3
    6,5,0,4,9,3,8,2,1,7,12,12,//10T
    13,1,2,3,4,5,6,7,8,9,10,11,
    };

//printf("SHZHXH:%d , weizhi:%d\n",SHZHXH,weizhi);
printf("CLCORNO:  %d %d %d %d\n",CLCORNO[0],CLCORNO[1],CLCORNO[2],CLCORNO[3]);
printf("BPH:   %d %d %d %d\n",BPH[0],BPH[1],BPH[2],BPH[3]);
printf("JSBPH: %d %d %d %d\n",JSBPH[0],JSBPH[1],JSBPH[2],JSBPH[3]);
// if(SHZHXH==3)        //URS-10T
//           weizhi=10;
// else if( SHZHXH==1 )//12MA
//          weizhi=12;
// else if ( SHZHXH==2 ) //11-3试纸顺序
//          weizhi=12;

//    while((weizhi>0)) {

                    switch(printxh[SHZHXH][weizhi])
                      {
                          case 0://尿胆原--G

                                        CESHIZHI[0]=0;

                                        CESHIZHI[1]=CLCORNO[0]*3000/JSBPH[0];

                                        CESHIZHI[2]=CLCORNO[1]*1000/JSBPH[1];

                                        CESHIZHI[3]=CLCORNO[2]*1000/JSBPH[2];

                                        CESHIZHI[4]=CLCORNO[3]*1000/JSBPH[3];

                                        CESHIZHI[0]=CESHIZHI[3]*3;//JG = G *3

                                        if( CESHIZHI[0]>6000 )
                                        CESHIZHI[0]=6000;

                                        if(CESHIZHI[2]<100)
                                        CESHIZHI[0]=50;

                                        JIEGUO[0]=0;
                                        JIEGUO[0]=CESHIZHI[0];
                                        printf(" URO CAC  IS:%d  \n",JIEGUO[0]);
                                break;

                        case 1://胆红素--r

                                        CESHIZHI[0]=0;

                                        CESHIZHI[1]=CLCORNO[0]*3000/JSBPH[0];

                                        CESHIZHI[2]=CLCORNO[1]*1000/JSBPH[1];

                                        CESHIZHI[3]=CLCORNO[2]*1000/JSBPH[2];

                                        CESHIZHI[4]=CLCORNO[3]*1000/JSBPH[3];

                                        CESHIZHI[0]=2*(CESHIZHI[3]+CESHIZHI[4])*BPH[0]/JSBPH[0];

                                        if(CESHIZHI[0]>9500)
                                        CESHIZHI[0]=9500;

                                        if(CESHIZHI[2]<100)
                                        CESHIZHI[0]=50;

                                        JIEGUO[1]=0;
                                        JIEGUO[1]=CESHIZHI[0];
                                        printf(" BIL CAC  IS:%d  \n",JIEGUO[1]);

                                    break;

                            case 2://酮体--G/R
                                        CESHIZHI[0]=0;

                                        CESHIZHI[1]=CLCORNO[0]*3000/JSBPH[0];

                                        CESHIZHI[2]=CLCORNO[1]*1000/JSBPH[1];

                                        CESHIZHI[3]=CLCORNO[2]*1000/JSBPH[2];

                                        CESHIZHI[4]=CLCORNO[3]*1000/JSBPH[3];

                                        CESHIZHI[0]=(CESHIZHI[3]+CESHIZHI[2])*BPH[0]/JSBPH[0];

                                        if( CESHIZHI[0]>9000 )
                                                 CESHIZHI[0]=9000;

                                        if(CESHIZHI[2]<100)
                                                 CESHIZHI[0]=50;

                                        JIEGUO[2]=0;
                                        JIEGUO[2]=CESHIZHI[0];
                                        printf(" KET CAC  IS:%d  \n",JIEGUO[2]);

                                    break;

                            case 3://血--R
                                        CESHIZHI[0]=0;
                                        CESHIZHI[1]=CLCORNO[0]*3000/JSBPH[0];
                                        CESHIZHI[2]=CLCORNO[1]*1000/JSBPH[1];
                                        CESHIZHI[3]=CLCORNO[2]*1000/JSBPH[2];
                                        CESHIZHI[4]=CLCORNO[3]*1000/JSBPH[3];

                                        CESHIZHI[0]= CESHIZHI[2]*2*BPH[0]/JSBPH[0];
                                         if( CESHIZHI[0]>9000 )
                                                 CESHIZHI[0]=9000;
                                         if(CESHIZHI[2]<100)
                                                 CESHIZHI[0]=50;
                                        JIEGUO[3]=0;
                                        JIEGUO[3]=CESHIZHI[0];
                                        printf(" BLD CAC  IS:%d  \n",JIEGUO[3]);
                                    break;

                            case 4://蛋白质--R*G
                                        CESHIZHI[0]=0;
                                        CESHIZHI[1]=CLCORNO[0]*3000/JSBPH[0];
                                        CESHIZHI[2]=CLCORNO[1]*1000/JSBPH[1];
                                        CESHIZHI[3]=CLCORNO[2]*1000/JSBPH[2];
                                        CESHIZHI[4]=CLCORNO[3]*1000/JSBPH[3];

                                        CESHIZHI[0]=CESHIZHI[2]*5 ;//R*G/B
                                        if(CESHIZHI[0]>8500)
                                                CESHIZHI[0]=6800;
                                        if(CESHIZHI[0]<100)
                                                CESHIZHI[0]=50;
                                        JIEGUO[4]=0;
                                        JIEGUO[4]=CESHIZHI[0];
                                        printf(" PRO CAC  IS:%d  \n",JIEGUO[4]);
                                    break;

                            case 5://亚硝酸盐--G
                                        CESHIZHI[0]=0;
                                        CESHIZHI[1]=CLCORNO[0]*3000/JSBPH[0];
                                        CESHIZHI[2]=CLCORNO[1]*1000/JSBPH[1];
                                        CESHIZHI[3]=CLCORNO[2]*1000/JSBPH[2];
                                        CESHIZHI[4]=CLCORNO[3]*1000/JSBPH[3];

                                        CESHIZHI[0]= CESHIZHI[3]*3*BPH[0]/JSBPH[0];
                                        if(CESHIZHI[0]>7000)
                                                CESHIZHI[0]=7000;
                                        if(CESHIZHI[2]<100)
                                                CESHIZHI[0]=50;
                                        JIEGUO[5]=0;
                                        JIEGUO[5]=CESHIZHI[0];
                                        printf(" NIT CAC  IS:%d  \n",JIEGUO[5]);
                                    break;

                            case 6:	//白细胞--G
                                        if( (SHZHXH==1)||( SHZHXH==3 ) )
                                        {
                                            CESHIZHI[0]=0;
                                            CESHIZHI[1]=CLCORNO[0];//*3000/JSBPH[0];
                                            CESHIZHI[2]=CLCORNO[1];//*1000/JSBPH[1];
                                            CESHIZHI[3]=CLCORNO[2];//*1000/JSBPH[2];
                                            CESHIZHI[4]=CLCORNO[3];//*1000/JSBPH[3];

                                            CESHIZHI[0]=2*BPH[0]-BPH[0]*CESHIZHI[2]/CESHIZHI[3]+2*CESHIZHI[3];
                                        }
                                        else if( SHZHXH==2 )
                                        {
                                            CESHIZHI[0]=0;
                                            CESHIZHI[1]=CLCORNO[0]*3000/JSBPH[0];
                                            CESHIZHI[2]=CLCORNO[1]*1000/JSBPH[1];
                                            CESHIZHI[3]=CLCORNO[2]*1000/JSBPH[2];
                                            CESHIZHI[4]=CLCORNO[3]*1000/JSBPH[3];

                                            CESHIZHI[0]=2*CESHIZHI[3]*BPH[0]/JSBPH[1];
                                        }

                                         if(CESHIZHI[0]>9000)
                                                CESHIZHI[0]=9000;
                                        if(CESHIZHI[2]<100)
                                                CESHIZHI[0]=50;
                                        JIEGUO[6]=0;
                                        JIEGUO[6]=CESHIZHI[0];
                                        printf(" WBC CAC  IS:%d  \n",JIEGUO[6]);
                                    break;
                            case 7://葡萄糖--G
                                    if((SHZHXH==1)||(SHZHXH==3) )
                                    {
                                             CESHIZHI[0]=0;
                                             CESHIZHI[1]=CLCORNO[0]*3000/JSBPH[0];
                                             CESHIZHI[2]=CLCORNO[1]*1000/JSBPH[1];
                                             CESHIZHI[3]=CLCORNO[2]*1000/JSBPH[2];
                                             CESHIZHI[4]=CLCORNO[3]*1000/JSBPH[3];

                                            CESHIZHI[0]=CESHIZHI[2]+CESHIZHI[3];
                                    }
                                    else if( SHZHXH==2 )
                                    {
                                        CESHIZHI[0]=0;
                                        CESHIZHI[1]=CLCORNO[0];//*3000/JSBPH[0];
                                         CESHIZHI[2]=CLCORNO[1];//*1000/JSBPH[1];
                                         CESHIZHI[3]=CLCORNO[2];//*1000/JSBPH[2];
                                         CESHIZHI[4]=CLCORNO[3];//*1000/JSBPH[3];
                    //				  CESHIZHI[0]=2*CESHIZHI[3]*CESHIZHI[2]/CESHIZHI[4];//*BPH[SHZHXH]/JSBPH[0];//R*R/B;
                                      CESHIZHI[0]=2*CESHIZHI[3]*CESHIZHI[2]/500;//*BPH[SHZHXH]/JSBPH[0];//R*R/B;

                                    }
                                      if(CESHIZHI[0]>9200)
                                             CESHIZHI[0]=9200;
                                        if(CESHIZHI[0]<100)
                                             CESHIZHI[0]=50;
                                        JIEGUO[7]=0;
                                        JIEGUO[7]=CESHIZHI[0];
                                        printf(" GLU CAC  IS:%d  \n",JIEGUO[7]);
                                    break;

                            case 8://比重--R*G
                                    CESHIZHI[0]=0;
                                    CESHIZHI[1]=CLCORNO[0]*3000/JSBPH[0];
                                    CESHIZHI[2]=CLCORNO[1]*1000/JSBPH[1];
                                    CESHIZHI[3]=CLCORNO[2]*1000/JSBPH[2];
                                    CESHIZHI[4]=CLCORNO[3]*1000/JSBPH[3];

                                    CESHIZHI[0]=5*CESHIZHI[2]+4*CESHIZHI[3]-500;//CESHIZHI[0]=CESHIZHI[2]*3*BPH[SHZHXH]/JSBPH[0];//R*2000/B;
                                    if(CESHIZHI[0]>9000)
                                        CESHIZHI[0]=9000;
                                    if(CESHIZHI[2]<100)
                                        CESHIZHI[0]=50;
                                    JIEGUO[8]=0;
                                    JIEGUO[8]=CESHIZHI[0];
                                    printf(" SG CAC  IS:%d  \n",JIEGUO[8]);
                                break;

                        case 9://PH--R

                                        CESHIZHI[0]=0;
                                        CESHIZHI[1]=CLCORNO[0]*3000/JSBPH[0];
                                        CESHIZHI[2]=CLCORNO[1]*1000/JSBPH[1];
                                        CESHIZHI[3]=CLCORNO[2]*1000/JSBPH[2];
                                        CESHIZHI[4]=CLCORNO[3]*1000/JSBPH[3];

                                            if((CESHIZHI[2]>850)&&(CESHIZHI[3]>850)&&(CESHIZHI[4]>850))
                                            {
                                                    CESHIZHI[0]= 9000;
                                            }
                                            else if(CESHIZHI[2]<100)
                                            {
                                                 CESHIZHI[0]=50;
                                            }
                                            else
                                            {
                                                    CESHIZHI[0]=CESHIZHI[2]*2000/CESHIZHI[4]*BPH[0]/JSBPH[0];//R*2000/B  //CESHIZHI[0]=CESHIZHI[2]*3*BPH[0]/JSBPH[0];
                                            }
                                            JIEGUO[9]=0;
                                            JIEGUO[9]=CESHIZHI[0];
                                            printf(" PH  CAC  IS:%x  \n",JIEGUO[9]);
                                break;

                        case 10://VC
                                        CESHIZHI[0]=0;
                                        CESHIZHI[1]=CLCORNO[0]*3000/JSBPH[0];
                                        CESHIZHI[2]=CLCORNO[1]*1000/JSBPH[1];
                                        CESHIZHI[3]=CLCORNO[2]*1000/JSBPH[2];
                                        CESHIZHI[4]=CLCORNO[3]*1000/JSBPH[3];

                                        CESHIZHI[0]=CESHIZHI[0]*7000/JSBPH[0]*BPH[0]/JSBPH[0]; //W
                                        if(CESHIZHI[0]>9000)
                                            CESHIZHI[0]=9000;
                                        if(CESHIZHI[2]<100)
                                              CESHIZHI[0]=50;

                                        JIEGUO[10]=0;
                                        JIEGUO[10]=CESHIZHI[0];
                                        printf(" VC  CAC  IS:%d  \n",JIEGUO[10]);
                                break;

                            case 11:
                                        CESHIZHI[0]=0;
                                        CESHIZHI[1]=CLCORNO[0]*3000/JSBPH[0];
                                        CESHIZHI[2]=CLCORNO[1]*1000/JSBPH[1];
                                        CESHIZHI[3]=CLCORNO[2]*1000/JSBPH[2];
                                        CESHIZHI[4]=CLCORNO[3]*1000/JSBPH[3];

                                        CESHIZHI[0]=((CESHIZHI[3]+CESHIZHI[2])*BPH[0]/JSBPH[0]);			//	CESHIZHI[0]=((5*CESHIZHI[3]+2*CESHIZHI[2])*2*BPH[0]/JSBPH[0])-13000;
                                        if(CESHIZHI[0]>9000)
                                                CESHIZHI[0]=9000;
                                        if(CESHIZHI[2]<100)
                                                    CESHIZHI[0]=50;
                                        JIEGUO[11]=0;
                                        JIEGUO[11]=CESHIZHI[0];
                                         printf(" MALB  CAC  IS:%d  \n",JIEGUO[11]);
                                    break;

                            case 12:
                                         zwfwbzh='T';
                                         CESHIZHI[0]=0;

                                         CESHIZHI[1]=CLCORNO[0]*3000/JSBPH[0];
                                         zwfwzhb=CLCORNO[0];

                                         CESHIZHI[2]=CLCORNO[1]*1000/JSBPH[1];
                                         CESHIZHI[3]=CLCORNO[2]*1000/JSBPH[2];
                                         CESHIZHI[4]=CLCORNO[3]*1000/JSBPH[3];

                                        CESHIZHI[0]=((CESHIZHI[3]+CESHIZHI[2]))/2;
                                        zwfwzh = zwfwzh*1000/zwfwzhb;
                                        JIEGUO[12]=0;
                                        JIEGUO[12]=zwfwzh;
                                                printf(" CC  CAC  IS:%d  \n",JIEGUO[12]);
                                    break;

                            default: break;
                         }
// }

}

