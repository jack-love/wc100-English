#include "cac.h"

#define DEBUG_CAC  1

Cac::Cac(QWidget *parent) :
    QWidget(parent)
{


}


void Cac::get_CalculationResult(struct RESULT buf[], QString Name,struct resultRGB*  tmp){

        if (0 == QString::compare("11-III",App::TestPapertype)){
            QStringList strList;
            strList  << "BIL" << "URO" << "KET" << "BLD"<<"PRO"<<"NIT"<<"WBC"<<"GLU"<<"SG"<<"PH"<<"VC";
            int index = strList.indexOf(Name);

           tmp->W =buf[index].wrgb_value[0];
           tmp->R = buf[index].wrgb_value[1];
           tmp->G = buf[index].wrgb_value[2];
           tmp->B = buf[index].wrgb_value[3];
           tmp->Result = buf[index].calculation_results;
           strncpy(tmp->unit,buf[index].unit,10);

           printf("[get_CalculationResult 11-III:]W:%d , R:%d , G:%d  , B:%d , result:%d , unit:%s \n",
                  buf[index].wrgb_value[0],
                  buf[index].wrgb_value[1],
                  buf[index].wrgb_value[2],
                  buf[index].wrgb_value[3],
                  buf[index].calculation_results,
                  buf[index].unit);

        }else   if (0 == QString::compare("10T",   App::TestPapertype)){

        }else if (0 == QString::compare("12MA", App::TestPapertype) ){

        }

}


void Cac::interval_Calculation(struct RESULT buf[])
{
         unsigned int i,j;

                                                      // 0     1         2          3        4        5         6          7         8        9      10     11         12      13   14     15
          char name_buf[16][6]= {"URO","BIL","KET","BLD","PRO","NIT","WBC","LEU","GLU","SG","PH","MALB","CRE","CA","VC","ACR"};

#if  DEBUG_CAC
                          for(i = 0;i < buf[0].block_num; i++)
                              {

                                  for(j = 0;j < 4; j++)
                                  {

                                      printf("[cac]---> buf[%d].wrgb_value[%d]:%d \n",i,j,buf[i].wrgb_value[j]);

                                  }
                                  printf("[cac]---->buf[%d].name:%s \n",i,buf[i].name);
                              }

                              for(i = 0; i < buf[0].block_num; i++)
                                {

                                  for(j = 0; j < 8; j++){

                                        printf("[cac]--->i:[%d],j:[%d],calibration:[%d] \n",i,j ,buf[i].calibration[j]);
                                        printf("[cac]--->i:[%d],j:[%d],item_value:[%s]\n",i,j ,buf[i].item_value[j]);
                                    }
                                }

#endif

                    for(i = 0; i < buf[0].block_num; i++)//i是某一项
                    {
                             for(j = 0; j < 15; j++)
                            {
                                     unsigned int  flag = strcmp(buf[i].name, name_buf[j]);
                                    if(flag == 0)
                                    {
                                        buf[i].calculation_results = wc100_algorithm(buf,i, j);
                                    }
                            }
                    }


                    //unit
                    for(i = 0; i < buf[0].block_num; i++)
                    {
                        if(i == 8)
                        {
                            for(j = 0; j < 8; j++)
                            {
                                if(buf[i].calculation_results <= buf[i].calibration[j])//某一项里面的 8个梯度进行比较
                                {
//    #ifdef DEBUG
//                                    printf("1.buf[%d]wrgb_result_value == %d and buf[%d].calibration[%d] == %d\n", i, buf[i].wrgb_result_value, i, j, buf[i].calibration[j]);
//    #endif
                                    strncpy(buf[i].unit, buf[i].item_value[j], 10);
                                    if(j != 0)
                                        buf[i].flag = '*';
                                    else
                                        buf[i].flag = 0;
                                    j = 8;
                                }
                            }

                        }
                        else
                        {
                            for(j = 0; j < 8; j++)
                            {
                                if(buf[i].calculation_results > buf[i].calibration[j])
                                {
//    #ifdef DEBUG
//                                    printf("2. buf[%d]wrgb_result_value == %d and buf[%d].calibration[%d] == %d \n", i, buf[i].wrgb_result_value, i, j, buf[i].calibration[j]);
//    #endif
                                    strncpy(buf[i].unit, buf[i].item_value[j], 10);
                                    if(j != 0)
                                        buf[i].flag = '*';
                                    else
                                        buf[i].flag = 0;
                                    j = 8;
                                }
                            }
                        }
                    }

#if DEBUG_CAC
                    for(i = 0; i < buf[0].block_num; i++){
                        printf("[cac]--->buf[%d].calculation_results = %d\n", i, buf[i].calculation_results);
                     }

                    for(i = 0;i < buf[0].block_num; i++){
                               printf("[debug]--->unit:%s\n", buf[i].unit);
                    }
#endif
}



unsigned int Cac::wc100_algorithm(struct RESULT buf[15],unsigned int i, unsigned int position)
{
                                                // 0     1         2          3        4        5         6          7         8        9      10     11         12      13   14     15
//char name_buf[16][6]= {"URO","BIL","KET","BLD","PRO","NIT","WBC","LEU","GLU","SG","PH","MALB","CRE","CA","VC","ACR"};

      unsigned  int result;
      unsigned   int CESHIZHI[5];
        CESHIZHI[1] = buf[i].wrgb_value[0];
        CESHIZHI[2] = buf[i].wrgb_value[1];
        CESHIZHI[3] = buf[i].wrgb_value[2];
        CESHIZHI[4] = buf[i].wrgb_value[3];


        switch(position)
        {
            case 0://尿胆原--G URO
                CESHIZHI[0]=CESHIZHI[2]*2;
                printf("URO \n");
                break;
            case 1://胆红素--r
                CESHIZHI[0]=3*CESHIZHI[2]-2000;
                printf("BIL \n");
                break;
            case 2://酮体--G/R
                CESHIZHI[0]=CESHIZHI[2]*2;//*7000/CESHIZHI[4]*BPH[SHZHXH]/JSBPH[0]-4000;//R*7000/B-4000;
                printf("KET \n");
                break;
            case 3://血--R
                CESHIZHI[0]=CESHIZHI[2];
                printf("BLD \n");
                break;
            case 4://蛋白质--R*G PRO
                CESHIZHI[0]=CESHIZHI[2]*2;//R*G/B
                printf("PRO \n");
                break;
            case 5://亚硝酸盐--G
                if(((CESHIZHI[3]*CESHIZHI[3])<(CESHIZHI[2]*CESHIZHI[4]*0.972))&(CESHIZHI[3]<(CESHIZHI[4]*1.05))&(CESHIZHI[2]>99))
                {
                    CESHIZHI[0]= CESHIZHI[3]*3;//R*100/(B-G)
                }
                else if(CESHIZHI[2]<100)
                {
                    CESHIZHI[0]=50;
                }
                else
                {
                    CESHIZHI[0]=7000;
                }
                printf("NIT \n");
                break;
            case 6:	//白细胞--G
                CESHIZHI[0]=CESHIZHI[2]*3;//R*G/B
                printf("WBC \n");
                break;
            case 7:	//白细胞--G
                if(((CESHIZHI[2]>(CESHIZHI[4]*1.45))|(CESHIZHI[2]<1.12*CESHIZHI[4]))&(CESHIZHI[3]>CESHIZHI[4]*1.008)&(CESHIZHI[2]>99))
                {
                    CESHIZHI[0] = 9000;
                }
                else if(CESHIZHI[2]<100)
                {
                    CESHIZHI[0]=50;
                }
                else if((CESHIZHI[2]>900)&(CESHIZHI[3]>900)&(CESHIZHI[4]>900))
                {
                    CESHIZHI[0] = 9000;
                }
                else
                {
                    if(CESHIZHI[3]<CESHIZHI[4]*1.040)
                    {
                        CESHIZHI[0]=2*CESHIZHI[3];//R*G/B;
                    }
                    else
                    {
                        CESHIZHI[0]=4500;
                    }
                }
                printf("LEU \n");
                break;
            case 8://葡萄糖--G
                CESHIZHI[0]=CESHIZHI[2]*3;//R*R/B;
                printf("GLU \n");
                break;
            case 9://比重--R*G
                CESHIZHI[0]=CESHIZHI[2]*4;//R*2000/B;
                printf("SG \n");
                break;
            case 10://PH--R
                CESHIZHI[0]=CESHIZHI[2]*4;
                printf("PH \n");
                break;
            case 11://肌酐
                CESHIZHI[0]=5*CESHIZHI[2]+4*CESHIZHI[3]-500;//CESHIZHI[0]=CESHIZHI[2]*3*BPH[SHZHXH]/JSBPH[0];//R*2000/B;
                if(CESHIZHI[0]>9000)
                    CESHIZHI[0]=9000;
                if(CESHIZHI[2]<100)
                    CESHIZHI[0]=50;
                printf("MALB \n");
                break;
            case 12://
                printf("CRE \n");
                CESHIZHI[0]=8000;
                break;
            case 13:
                if((CESHIZHI[2]>850)&(CESHIZHI[3]>850)&(CESHIZHI[4]>850))
                {
                    CESHIZHI[0]= 9000;
                }
                else if(CESHIZHI[2]<100)
                {
                    CESHIZHI[0]=50;
                }
                else
                {
                    CESHIZHI[0]=CESHIZHI[2]*7;//JSBPH[0]; //W
                }
                printf("CA\n");
                break;
            case 14://VC
                CESHIZHI[0]=6000-CESHIZHI[2]*2;
                printf("VC\n");
                break;
            case 15:
                CESHIZHI[0]=8000;
                printf("ACR\n");
                break;
            default:
                break;
        }
        result = CESHIZHI[0];

   // #ifdef DEBUG
  //      printf("result == %d\n", result);
   // #endif
        return result;
    }


//unsigned char Cac::rgbCalculation (unsigned char SHZHXH,unsigned char weizhi,unsigned int *CLCORNO, unsigned int *BPH,unsigned int *JSBPH,unsigned int  *JIEGUO){

//   //unsigned char weizhi=0;
//  volatile unsigned int CESHIZHI[5]={0};
//  volatile long zwfwzh;
//  volatile long zwfwbzh;
//  volatile long zwfwzhb;

// unsigned char  printxh[5][12]={
//    0,1,2,3,4,5,6,7,8,9,11,12,//11MA
//    0,1,2,3,4,5,6,7,8,9,10,11,//12MA
//    1,0,2,3,4,5,6,7,8,9,10,12,//11-3
//    6,5,0,4,9,3,8,2,1,7,12,12,//10T
//    13,1,2,3,4,5,6,7,8,9,10,11,
//    };

////printf("SHZHXH:%d , weizhi:%d\n",SHZHXH,weizhi);
//printf("CLCORNO:  %d %d %d %d\n",CLCORNO[0],CLCORNO[1],CLCORNO[2],CLCORNO[3]);
//printf("BPH:   %d %d %d %d\n",BPH[0],BPH[1],BPH[2],BPH[3]);
//printf("JSBPH: %d %d %d %d\n",JSBPH[0],JSBPH[1],JSBPH[2],JSBPH[3]);
//// if(SHZHXH==3)        //URS-10T
////           weizhi=10;
//// else if( SHZHXH==1 )//12MA
////          weizhi=12;
//// else if ( SHZHXH==2 ) //11-3试纸顺序
////          weizhi=12;

////    while((weizhi>0)) {

//                    switch(printxh[SHZHXH][weizhi])
//                      {
//                          case 0://尿胆原--G

//                                        CESHIZHI[0]=0;

//                                        CESHIZHI[1]=CLCORNO[0]*3000/JSBPH[0];

//                                        CESHIZHI[2]=CLCORNO[1]*1000/JSBPH[1];

//                                        CESHIZHI[3]=CLCORNO[2]*1000/JSBPH[2];

//                                        CESHIZHI[4]=CLCORNO[3]*1000/JSBPH[3];

//                                        CESHIZHI[0]=CESHIZHI[3]*3;//JG = G *3

//                                        if( CESHIZHI[0]>6000 )
//                                        CESHIZHI[0]=6000;

//                                        if(CESHIZHI[2]<100)
//                                        CESHIZHI[0]=50;

//                                        JIEGUO[0]=0;
//                                        JIEGUO[0]=CESHIZHI[0];
//                                        printf(" URO CAC  IS:%d  \n",JIEGUO[0]);
//                                break;

//                        case 1://胆红素--r

//                                        CESHIZHI[0]=0;

//                                        CESHIZHI[1]=CLCORNO[0]*3000/JSBPH[0];

//                                        CESHIZHI[2]=CLCORNO[1]*1000/JSBPH[1];

//                                        CESHIZHI[3]=CLCORNO[2]*1000/JSBPH[2];

//                                        CESHIZHI[4]=CLCORNO[3]*1000/JSBPH[3];

//                                        CESHIZHI[0]=2*(CESHIZHI[3]+CESHIZHI[4])*BPH[0]/JSBPH[0];

//                                        if(CESHIZHI[0]>9500)
//                                        CESHIZHI[0]=9500;

//                                        if(CESHIZHI[2]<100)
//                                        CESHIZHI[0]=50;

//                                        JIEGUO[1]=0;
//                                        JIEGUO[1]=CESHIZHI[0];
//                                        printf(" BIL CAC  IS:%d  \n",JIEGUO[1]);

//                                    break;

//                            case 2://酮体--G/R
//                                        CESHIZHI[0]=0;

//                                        CESHIZHI[1]=CLCORNO[0]*3000/JSBPH[0];

//                                        CESHIZHI[2]=CLCORNO[1]*1000/JSBPH[1];

//                                        CESHIZHI[3]=CLCORNO[2]*1000/JSBPH[2];

//                                        CESHIZHI[4]=CLCORNO[3]*1000/JSBPH[3];

//                                        CESHIZHI[0]=(CESHIZHI[3]+CESHIZHI[2])*BPH[0]/JSBPH[0];

//                                        if( CESHIZHI[0]>9000 )
//                                                 CESHIZHI[0]=9000;

//                                        if(CESHIZHI[2]<100)
//                                                 CESHIZHI[0]=50;

//                                        JIEGUO[2]=0;
//                                        JIEGUO[2]=CESHIZHI[0];
//                                        printf(" KET CAC  IS:%d  \n",JIEGUO[2]);

//                                    break;

//                            case 3://血--R
//                                        CESHIZHI[0]=0;
//                                        CESHIZHI[1]=CLCORNO[0]*3000/JSBPH[0];
//                                        CESHIZHI[2]=CLCORNO[1]*1000/JSBPH[1];
//                                        CESHIZHI[3]=CLCORNO[2]*1000/JSBPH[2];
//                                        CESHIZHI[4]=CLCORNO[3]*1000/JSBPH[3];

//                                        CESHIZHI[0]= CESHIZHI[2]*2*BPH[0]/JSBPH[0];
//                                         if( CESHIZHI[0]>9000 )
//                                                 CESHIZHI[0]=9000;
//                                         if(CESHIZHI[2]<100)
//                                                 CESHIZHI[0]=50;
//                                        JIEGUO[3]=0;
//                                        JIEGUO[3]=CESHIZHI[0];
//                                        printf(" BLD CAC  IS:%d  \n",JIEGUO[3]);
//                                    break;

//                            case 4://蛋白质--R*G
//                                        CESHIZHI[0]=0;
//                                        CESHIZHI[1]=CLCORNO[0]*3000/JSBPH[0];
//                                        CESHIZHI[2]=CLCORNO[1]*1000/JSBPH[1];
//                                        CESHIZHI[3]=CLCORNO[2]*1000/JSBPH[2];
//                                        CESHIZHI[4]=CLCORNO[3]*1000/JSBPH[3];

//                                        CESHIZHI[0]=CESHIZHI[2]*5 ;//R*G/B
//                                        if(CESHIZHI[0]>8500)
//                                                CESHIZHI[0]=6800;
//                                        if(CESHIZHI[0]<100)
//                                                CESHIZHI[0]=50;
//                                        JIEGUO[4]=0;
//                                        JIEGUO[4]=CESHIZHI[0];
//                                        printf(" PRO CAC  IS:%d  \n",JIEGUO[4]);
//                                    break;

//                            case 5://亚硝酸盐--G
//                                        CESHIZHI[0]=0;
//                                        CESHIZHI[1]=CLCORNO[0]*3000/JSBPH[0];
//                                        CESHIZHI[2]=CLCORNO[1]*1000/JSBPH[1];
//                                        CESHIZHI[3]=CLCORNO[2]*1000/JSBPH[2];
//                                        CESHIZHI[4]=CLCORNO[3]*1000/JSBPH[3];

//                                        CESHIZHI[0]= CESHIZHI[3]*3*BPH[0]/JSBPH[0];
//                                        if(CESHIZHI[0]>7000)
//                                                CESHIZHI[0]=7000;
//                                        if(CESHIZHI[2]<100)
//                                                CESHIZHI[0]=50;
//                                        JIEGUO[5]=0;
//                                        JIEGUO[5]=CESHIZHI[0];
//                                        printf(" NIT CAC  IS:%d  \n",JIEGUO[5]);
//                                    break;

//                            case 6:	//白细胞--G
//                                        if( (SHZHXH==1)||( SHZHXH==3 ) )
//                                        {
//                                            CESHIZHI[0]=0;
//                                            CESHIZHI[1]=CLCORNO[0];//*3000/JSBPH[0];
//                                            CESHIZHI[2]=CLCORNO[1];//*1000/JSBPH[1];
//                                            CESHIZHI[3]=CLCORNO[2];//*1000/JSBPH[2];
//                                            CESHIZHI[4]=CLCORNO[3];//*1000/JSBPH[3];

//                                            CESHIZHI[0]=2*BPH[0]-BPH[0]*CESHIZHI[2]/CESHIZHI[3]+2*CESHIZHI[3];
//                                        }
//                                        else if( SHZHXH==2 )
//                                        {
//                                            CESHIZHI[0]=0;
//                                            CESHIZHI[1]=CLCORNO[0]*3000/JSBPH[0];
//                                            CESHIZHI[2]=CLCORNO[1]*1000/JSBPH[1];
//                                            CESHIZHI[3]=CLCORNO[2]*1000/JSBPH[2];
//                                            CESHIZHI[4]=CLCORNO[3]*1000/JSBPH[3];

//                                            CESHIZHI[0]=2*CESHIZHI[3]*BPH[0]/JSBPH[1];
//                                        }

//                                         if(CESHIZHI[0]>9000)
//                                                CESHIZHI[0]=9000;
//                                        if(CESHIZHI[2]<100)
//                                                CESHIZHI[0]=50;
//                                        JIEGUO[6]=0;
//                                        JIEGUO[6]=CESHIZHI[0];
//                                        printf(" WBC CAC  IS:%d  \n",JIEGUO[6]);
//                                    break;
//                            case 7://葡萄糖--G
//                                    if((SHZHXH==1)||(SHZHXH==3) )
//                                    {
//                                             CESHIZHI[0]=0;
//                                             CESHIZHI[1]=CLCORNO[0]*3000/JSBPH[0];
//                                             CESHIZHI[2]=CLCORNO[1]*1000/JSBPH[1];
//                                             CESHIZHI[3]=CLCORNO[2]*1000/JSBPH[2];
//                                             CESHIZHI[4]=CLCORNO[3]*1000/JSBPH[3];

//                                            CESHIZHI[0]=CESHIZHI[2]+CESHIZHI[3];
//                                    }
//                                    else if( SHZHXH==2 )
//                                    {
//                                        CESHIZHI[0]=0;
//                                        CESHIZHI[1]=CLCORNO[0];//*3000/JSBPH[0];
//                                         CESHIZHI[2]=CLCORNO[1];//*1000/JSBPH[1];
//                                         CESHIZHI[3]=CLCORNO[2];//*1000/JSBPH[2];
//                                         CESHIZHI[4]=CLCORNO[3];//*1000/JSBPH[3];
//                    //				  CESHIZHI[0]=2*CESHIZHI[3]*CESHIZHI[2]/CESHIZHI[4];//*BPH[SHZHXH]/JSBPH[0];//R*R/B;
//                                      CESHIZHI[0]=2*CESHIZHI[3]*CESHIZHI[2]/500;//*BPH[SHZHXH]/JSBPH[0];//R*R/B;

//                                    }
//                                      if(CESHIZHI[0]>9200)
//                                             CESHIZHI[0]=9200;
//                                        if(CESHIZHI[0]<100)
//                                             CESHIZHI[0]=50;
//                                        JIEGUO[7]=0;
//                                        JIEGUO[7]=CESHIZHI[0];
//                                        printf(" GLU CAC  IS:%d  \n",JIEGUO[7]);
//                                    break;

//                            case 8://比重--R*G
//                                    CESHIZHI[0]=0;
//                                    CESHIZHI[1]=CLCORNO[0]*3000/JSBPH[0];
//                                    CESHIZHI[2]=CLCORNO[1]*1000/JSBPH[1];
//                                    CESHIZHI[3]=CLCORNO[2]*1000/JSBPH[2];
//                                    CESHIZHI[4]=CLCORNO[3]*1000/JSBPH[3];

//                                    CESHIZHI[0]=5*CESHIZHI[2]+4*CESHIZHI[3]-500;//CESHIZHI[0]=CESHIZHI[2]*3*BPH[SHZHXH]/JSBPH[0];//R*2000/B;
//                                    if(CESHIZHI[0]>9000)
//                                        CESHIZHI[0]=9000;
//                                    if(CESHIZHI[2]<100)
//                                        CESHIZHI[0]=50;
//                                    JIEGUO[8]=0;
//                                    JIEGUO[8]=CESHIZHI[0];
//                                    printf(" SG CAC  IS:%d  \n",JIEGUO[8]);
//                                break;

//                        case 9://PH--R

//                                        CESHIZHI[0]=0;
//                                        CESHIZHI[1]=CLCORNO[0]*3000/JSBPH[0];
//                                        CESHIZHI[2]=CLCORNO[1]*1000/JSBPH[1];
//                                        CESHIZHI[3]=CLCORNO[2]*1000/JSBPH[2];
//                                        CESHIZHI[4]=CLCORNO[3]*1000/JSBPH[3];

//                                            if((CESHIZHI[2]>850)&&(CESHIZHI[3]>850)&&(CESHIZHI[4]>850))
//                                            {
//                                                    CESHIZHI[0]= 9000;
//                                            }
//                                            else if(CESHIZHI[2]<100)
//                                            {
//                                                 CESHIZHI[0]=50;
//                                            }
//                                            else
//                                            {
//                                                    CESHIZHI[0]=CESHIZHI[2]*2000/CESHIZHI[4]*BPH[0]/JSBPH[0];//R*2000/B  //CESHIZHI[0]=CESHIZHI[2]*3*BPH[0]/JSBPH[0];
//                                            }
//                                            JIEGUO[9]=0;
//                                            JIEGUO[9]=CESHIZHI[0];
//                                            printf(" PH  CAC  IS:%x  \n",JIEGUO[9]);
//                                break;

//                        case 10://VC
//                                        CESHIZHI[0]=0;
//                                        CESHIZHI[1]=CLCORNO[0]*3000/JSBPH[0];
//                                        CESHIZHI[2]=CLCORNO[1]*1000/JSBPH[1];
//                                        CESHIZHI[3]=CLCORNO[2]*1000/JSBPH[2];
//                                        CESHIZHI[4]=CLCORNO[3]*1000/JSBPH[3];

//                                        CESHIZHI[0]=CESHIZHI[0]*7000/JSBPH[0]*BPH[0]/JSBPH[0]; //W
//                                        if(CESHIZHI[0]>9000)
//                                            CESHIZHI[0]=9000;
//                                        if(CESHIZHI[2]<100)
//                                              CESHIZHI[0]=50;

//                                        JIEGUO[10]=0;
//                                        JIEGUO[10]=CESHIZHI[0];
//                                        printf(" VC  CAC  IS:%d  \n",JIEGUO[10]);
//                                break;

//                            case 11:
//                                        CESHIZHI[0]=0;
//                                        CESHIZHI[1]=CLCORNO[0]*3000/JSBPH[0];
//                                        CESHIZHI[2]=CLCORNO[1]*1000/JSBPH[1];
//                                        CESHIZHI[3]=CLCORNO[2]*1000/JSBPH[2];
//                                        CESHIZHI[4]=CLCORNO[3]*1000/JSBPH[3];

//                                        CESHIZHI[0]=((CESHIZHI[3]+CESHIZHI[2])*BPH[0]/JSBPH[0]);			//	CESHIZHI[0]=((5*CESHIZHI[3]+2*CESHIZHI[2])*2*BPH[0]/JSBPH[0])-13000;
//                                        if(CESHIZHI[0]>9000)
//                                                CESHIZHI[0]=9000;
//                                        if(CESHIZHI[2]<100)
//                                                    CESHIZHI[0]=50;
//                                        JIEGUO[11]=0;
//                                        JIEGUO[11]=CESHIZHI[0];
//                                         printf(" MALB  CAC  IS:%d  \n",JIEGUO[11]);
//                                    break;

//                            case 12:
//                                         zwfwbzh='T';
//                                         CESHIZHI[0]=0;

//                                         CESHIZHI[1]=CLCORNO[0]*3000/JSBPH[0];
//                                         zwfwzhb=CLCORNO[0];

//                                         CESHIZHI[2]=CLCORNO[1]*1000/JSBPH[1];
//                                         CESHIZHI[3]=CLCORNO[2]*1000/JSBPH[2];
//                                         CESHIZHI[4]=CLCORNO[3]*1000/JSBPH[3];

//                                        CESHIZHI[0]=((CESHIZHI[3]+CESHIZHI[2]))/2;
//                                        zwfwzh = zwfwzh*1000/zwfwzhb;
//                                        JIEGUO[12]=0;
//                                        JIEGUO[12]=zwfwzh;
//                                                printf(" CC  CAC  IS:%d  \n",JIEGUO[12]);
//                                    break;

//                            default: break;
//                         }
//// }

//}

