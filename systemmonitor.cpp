#include "systemmonitor.h"
#include <sys/ioctl.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <time.h>
#include "i2c-dev.h"
#include<stdio.h>
#include<unistd.h>
#include <QProcess>
#include <QDebug>
#include"App.h"
int fd = -1;
int ret = 0;
volatile char tmp;

systemMonitor::systemMonitor(QObject *parent) :QThread(parent)
{
//    shellProcess("echo 132 > /sys/class/gpio/export");
//    msleep(2000);
//    shellProcess("sync");
//    shellProcess("echo in > /sys/class/gpio/gpio132/direction");
//    msleep(2000);
//    shellProcess("sync");
//    qDebug()<<"systemMonitor";
}
/*
 (BANK − 1) × 32 + N

echo 39 > /sys/class/gpio/export
echo out  > /sys/class/gpio/gpio39/direction
echo 0 > /sys/class/gpio/gpio39/value

cat ./sys/devices/platform/analog-i2c/i2c-4/4-0048/hwmon/hwmon0/temp1_input     //温度读取

是否充电
echo 132 > /sys/class/gpio/export
echo in > /sys/class/gpio/gpio132/direction
cat /sys/class/gpio/gpio132/value
*/

void systemMonitor::run()
{
       while (1){
         msleep(2000);
         rt9428_Getsoc();
         rt9428_GetChargstate();
       }
}


QString systemMonitor::shellProcess(QString cmd){
   QProcess process;
   process.start(cmd);
   process.waitForFinished();
   QByteArray output = process.readAllStandardOutput();
   QString str_output = output;
  return str_output;
}

void systemMonitor::msleep(long s){
    QThread::msleep(s);
}

bool systemMonitor::rt9428_open(){

        if ((fd = open(DEVICE,O_RDWR))< 0) {
                perror("open rt9428 error !\n");
                return false;
            }

                if(!rt9428_Config()){
                 return false;
               }

               if(!rt9428_QuickSensing()){
                return false;
               }
               return true;
}

bool systemMonitor::rt9428_QuickSensing(){
    char tbuf[]={
        0x06,0x04,0x00,
    };
    int  ret = rt9428_write(fd,tbuf,sizeof(tbuf));
                if (ret != 0){
                        printf("[rt9428] QuickSensing failed\n");
                       return false;
                }
                else{
                         printf("[rt9428] QuickSensing ok\n");
                         return true;
                  }
}

bool systemMonitor::rt9428_Config() {
    char tbuf[]={
        0x0c,0x32,0x40,
    };
            int  ret = rt9428_write(fd,tbuf,sizeof(tbuf));
            if (ret != 0){
                    printf("[rt9428] write config Address failed\n");
                   return false;
            }
            else{
                     printf("[rt9428] write config Address ok\n");
                     return true;
           }
}

void  systemMonitor::rt9428_Getsoc()
{
    char rbuf;
    char reg  = 0x04;

int  ret = rt9428_read (fd,&reg,&rbuf,1);
        if(ret < 0){
               printf("[rt9428]  Soc failed\n");
        }
        else{
               if(tmp != rbuf ) {
                    tmp = rbuf;
                    printf("[rt9428] soc  is  : [%d]\n",rbuf);

                    App::Electric_quantity = tmp;
                        emit soc_Signal(rbuf);
               }
        }

}

void systemMonitor::rt9428_GetChargstate()
{
    int  Charging = shellProcess("cat /sys/class/gpio/gpio132/value").toInt();

    if((Charging == 0) &&(tmp < 100)){
         emit charg_Signal(true);
      }else{
         emit charg_Signal(false);
    }

}


int  systemMonitor::rt9428_read(int fd,  char *reg,  char *rbuf, int len) {
    struct i2c_rdwr_ioctl_data i2c_data;
        struct i2c_msg msgs[2];
        int ret = 0;

        i2c_data.nmsgs = 2;
        i2c_data.msgs = msgs;

        msgs[0].flags = 0;
        msgs[0].addr  = RT9428_ADDR >> 1;
        msgs[0].len   = 1;
        msgs[0].buf   = reg;

        msgs[1].flags = I2C_M_RD;
        msgs[1].addr  = RT9428_ADDR >> 1;
        msgs[1].len   = len;
        msgs[1].buf   = rbuf;

        ret =ioctl(fd, I2C_RDWR, (unsigned long) &i2c_data);
        if (ret < 0){
           printf("rt9428_read ioctl fail\n");
            return ret;
        }
        return 0;
}

int  systemMonitor::rt9428_write(int fd,  char *tbuf, int len) {
    struct i2c_rdwr_ioctl_data i2c_data;
        struct i2c_msg msgs;
        int ret = 0;
       // printf("len:%d %x,%x\n",len,tbuf[0],tbuf[1],tbuf[2]);
        i2c_data.nmsgs = 1;
        i2c_data.msgs = &msgs;

        msgs.flags = 0;
        msgs.addr  = RT9428_ADDR >> 1;
        msgs.len   = len;
        msgs.buf   = tbuf;

        ret = ioctl(fd, I2C_RDWR, (unsigned long) &i2c_data);
        if (ret < 0){
            printf("rt9428_write ioctl fail\n");
            return ret;
        }

        return 0;
}

