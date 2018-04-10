%Processing data in the case of a known starting point and an end point
clear;
clc;
data=load('C:\Users\Desktop\testData.txt');
N = length(data);
data2=data;

%store start point and stop point
starts=[759 1069 1861 2348 2508];
stops=[766 1076 1871 2359 2518];

%process data
for k=1:length(starts)
start=starts(k);
stop=stops(k);

%Monotonous increasing
if data2(start)<data2(stop)
    for i=start:stop
        if data2(i)>data2(i+1)
            data2(i+1)=data2(i);
        end
    end
end

%Monotonous decreasing  
if data2(start)>data2(stop)
    for i=start:stop
        if data2(i)<data2(i+1)
            data2(i+1)=data2(i);
        end
    end
end

end

%store data
allData=[data' data2'];
fileID1 = fopen(strcat('C:\Users\Desktop\UpdateTestData.txt'),'w');
for i=1:length(allData)
    fprintf( fileID1,'%f\t', allData(i,1));
    fprintf( fileID1,'%f\t\n', allData(i,2));
end
fclose(fileID1);

%plot result
for i=1:length(starts)
    figure;
    hold on;
    start=starts(i);
    stop=stops(i);
    plot(allData(start:stop,1),'color','r');
    plot(allData(start:stop,2),'color','b');
    hold off;
end
