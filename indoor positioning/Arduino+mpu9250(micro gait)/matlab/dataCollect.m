%Using MATLAB to collect mpu9250 data
clear;
clc;
delete(instrfindall);
delay = .000001;   

rawData=[];
flag=true;

%Open Serial COM Port
serialPort = 'COM8'; 
s = serial(serialPort, 'BaudRate', 115200);
fclose(s);
fopen(s);
disp('Start...');
ti=tic;

%collect data
while (flag==true)
   rawData = fscanf(s,'%f')';
   %Each group of data includes acceleration, angular velocity and timestamp, seven
   if length(rawData)==7 
          fileID1 = fopen(strcat('C:\Users\LiZe\Desktop\gongyanRawData\','staticData_',num2str(ti),'.txt'),'a');
          
             fprintf( fileID1,'%f\t', rawData(1));
             fprintf( fileID1,'%f\t', rawData(2));
             fprintf( fileID1,'%f\t', rawData(3));
          
             fprintf( fileID1,'%f\t', rawData(4));
             fprintf( fileID1,'%f\t', rawData(5));
             fprintf( fileID1,'%f\t', rawData(6));
             
             fprintf( fileID1,'%f\t\n', rawData(7));
            
          fclose(fileID1);
          disp(rawData(2));
   end
  pause(delay);
end
fclose(s);