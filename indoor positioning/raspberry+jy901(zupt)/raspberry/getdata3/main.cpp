#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <sstream>
#include <fstream>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include "JY-901B.cpp"
#include "time.h"
#include <sys/time.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<netdb.h>
#include<string.h>
#include<errno.h>
#include <arpa/inet.h>
#include <deque>
#include <string>
#include <cstring>
using namespace std;
//global variable LinkList.
const double pi = 3.1415926;
deque<string> data;
char ip[100];
int PORT;
//Two threads,one for data collection,one for data transmission and for data deletion
void* thread1(void* s)
{
    //sensor message configuration
    int nbytes;

    struct timeval tv;
    gettimeofday(&tv,NULL);
/*    string a1;
    cin>>a1;
    printf("JY901 test start!\n");

  */
    CJY901 sensor = CJY901(1, 0x50);
    bool a = sensor.Open();
    //get time
    time_t rawtime;
    struct tm * timeinfo;
    time (&rawtime);
    //printf("%d\n",rawtime); //using the time to create the file(name)
    //get the piancha(acc and gyro)
    sensor.GetAcc_bias();
    sensor.GetGyro_bias();
    float accx,accy,accz,gyx,gyy,gyz,anglex,angley,anglez;
    while(a)
    {
        gettimeofday(&tv,NULL);
        //get the gyro data
        sensor.GetGyro();
        gyx = (float) sensor.stcGyro.w[0] / 32768 * 2000/180*pi;
        gyy = (float) sensor.stcGyro.w[1] / 32768 * 2000/180*pi;
        gyz = (float) sensor.stcGyro.w[2] / 32768 * 2000/180*pi;
        //printf("x:%f, y:%f, z:%f\n",gyx,gyy,gyz);
        sensor.GetAcc();
        accx = (float) sensor.stcAcc.a[0]/32768*16*9.8;
        accy = (float) sensor.stcAcc.a[1]/32768*16*9.8;
        accz = (float) sensor.stcAcc.a[2]/32768*16*9.8;
        //get the rotation matrix
        sensor.GetAngle();
        anglex = (float)sensor.stcAngle.Angle[0]/32768*180;
        angley = (float)sensor.stcAngle.Angle[1]/32768*180;
        anglez = (float)sensor.stcAngle.Angle[2]/32768*180;
        long time1 = tv.tv_sec*1000000 + tv.tv_usec;//get the time

        char ctime1[200];
        char cgyx[200];
        char cgyy[200];
        char cgyz[200];
        char caccx[200];
        char caccy[200];
        char caccz[200];
        char canglex[200];
        char cangley[200];
        char canglez[200];
        sprintf(ctime1,"%ld ",time1);
        sprintf(cgyx,"%f ",gyx);
        sprintf(cgyy,"%f ",gyy);
        sprintf(cgyz,"%f ",gyz);
        sprintf(caccx,"%f ",accx);
        sprintf(caccy,"%f ",accy);
        sprintf(caccz,"%f ",accz);
        sprintf(canglex,"%f ",anglex);
        sprintf(cangley,"%f ",angley);
        sprintf(cangley,"%f",anglez);
        strcat(ctime1,caccx);
        strcat(ctime1,caccy);
        strcat(ctime1,caccz);
        strcat(ctime1,cgyx);
        strcat(ctime1,cgyy);
        strcat(ctime1,cgyz);
        data.push_back(ctime1);
        cout<<ctime1<<endl;
    }

}
void* thread2(void* s)
{
    int client_sockfd;
    int len;
    struct sockaddr_in remote_addr; //Server network address structure
    int sin_size;
    char buf[100];  //Buffer  for data transmission
    memset(&remote_addr,0,sizeof(remote_addr)); //Data initialization -- clear zero
    remote_addr.sin_family=AF_INET; //Set up to IP communication
    remote_addr.sin_addr.s_addr=inet_addr(ip);//Server IP address
    remote_addr.sin_port=htons(PORT); //Server port number

    /*Creating a client socket --IPv4 protocol for connectionless communication, UDP protocol*/
    if((client_sockfd = socket(AF_INET, SOCK_DGRAM, 0)) == -1)
    {
        perror("socket error");
        return NULL;
    }
    sin_size=sizeof(struct sockaddr_in);



    while(true)
    {
    int num = data.size();
    if(num>0){

     printf("%d\n",data.size());
        strcpy(buf,data.front().c_str());
        data.pop_front();
        printf("%d\n",data.size());
        if((len=sendto(client_sockfd,buf,strlen(buf),0,(struct sockaddr *)&remote_addr,sizeof(struct sockaddr)))<0)
        {
            perror("recvfrom");
//            return NULL;
        }


    }
    }
    close(client_sockfd);
    return NULL;

}
int main()
{
    printf("please input the ip\n");
    cin>>ip;
    printf("please input the PORT\n");
    cin>>PORT;
    printf("IP is : %s:%d\n",ip,PORT);
    pthread_t id1,id2;
    void *a1,*a2;
    int  ret1,ret2;
    int number = 1;
    ret1 = pthread_create(&id1,NULL,thread1,NULL);
    ret2 = pthread_create(&id2,NULL,thread2,NULL);
    if(ret1!=0)
    {
        printf("create pthread1 error!\n");
        exit(1);
    }
    if(ret2!=0)
    {
        printf("create pthread1 error!\n");
        exit(1);
    }
    pthread_join(id2,&a2); 
    pthread_join(id1,&a1);  
  
    return 0;
}






