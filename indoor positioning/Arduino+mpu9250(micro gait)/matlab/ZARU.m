% 1.ZARU(零角速度更新)：此时的角速度理论上为[0 0 0]',计算角速度的误差并送入EKF中
% 1.ZARU (zero angle speed update): at this time the angular velocity is theoretically [0 0 0]', 
% and the error of the angular velocity is calculated and sent into the EKF
function delta_w = ZARU(gyro_data)
    delta_w = gyro_data - [0 0 0]';
end
