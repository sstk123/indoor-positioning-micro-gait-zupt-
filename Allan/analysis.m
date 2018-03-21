clc;  
clear;  
data = load('大直线.txt');
data = data(:, 2:4)*3600;
%Get the standard deviation of Allan, and describe it with 100 points
[A, B] = allan(data, 100, 100);         %求Allan标准差，用100个点来描述  
%Double logarithmic coordinate drawing  
loglog(A, B, 'o');                  %画双对数坐标图  
xlabel('平均时间:sec');                
ylabel('Allan标准差:deg/h');              
legend('X axis','Y axis','Z axis'); 
grid on;                           
hold on;                           
%fitting  
C(1, :) = nihe(A', (B(:,1)').^2, 2)';   %拟合  
C(2, :) = nihe(A', (B(:,2)').^2, 2)';  
C(3, :) = nihe(A', (B(:,3)').^2, 2)';  
  
Q = sqrt(abs(C(:, 1) / 3));          %Quantization noise, unit: deg/h, curvature -1量化噪声，单位：deg/h  ，  曲率-1
N = sqrt(abs(C(:, 2) / 1)) / 60;    %Angle random walk, unit: deg/h^0.5 curvature -1/2角度随机游走，单位：deg/h^0.5  曲率-1/2
Bs = sqrt(abs(C(:, 3))) / 0.6643;   %Zero offset instability, unit: deg/h curvature 0零偏不稳定性，单位：deg/h      曲率0
K = sqrt(abs(C(:, 4) * 3)) * 60;    %Angular rate wandering, unit: deg/h/h^0.5角速率游走，单位：deg/h/h^0.5  
R = sqrt(abs(C(:, 5) * 2)) * 3600;  %Rate slope, unit: deg/h/h速率斜坡，单位：deg/h/h  
  
fprintf('量化噪声      X轴：%f Y轴：%f Z轴：%f  单位：deg/h\n', Q(1), Q(2), Q(3));  
fprintf('角度随机游走  X轴：%f Y轴：%f Z轴：%f  单位：deg/h^0.5\n', N(1), N(2), N(3));  
fprintf('零偏不稳定性  X轴：%f Y轴：%f Z轴：%f  单位：deg/h\n', Bs(1), Bs(2), Bs(3));  
fprintf('角速率游走    X轴：%f Y轴：%f Z轴：%f  单位：deg/h/h^0.5\n', K(1), K(2), K(3));  
fprintf('速率斜坡      X轴：%f Y轴：%f Z轴：%f  单位：deg/h/h\n', R(1), R(2), R(3));  
  
D(:, 1) = sqrt(C(1,1)*A.^(-2) + C(1,2)*A.^(-1) + C(1,3)*A.^(0) + C(1,4)*A.^(1) + C(1,5)*A.^(2));    %生成拟合函数  
D(:, 2) = sqrt(C(2,1)*A.^(-2) + C(2,2)*A.^(-1) + C(2,3)*A.^(0) + C(2,4)*A.^(1) + C(2,5)*A.^(2));  
D(:, 3) = sqrt(C(3,1)*A.^(-2) + C(3,2)*A.^(-1) + C(3,3)*A.^(0) + C(3,4)*A.^(1) + C(3,5)*A.^(2));  
  
loglog(A, D);  