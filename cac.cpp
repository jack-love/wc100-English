#include "cac.h"



Cac::Cac(QWidget *parent) :
    QWidget(parent)
{


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

