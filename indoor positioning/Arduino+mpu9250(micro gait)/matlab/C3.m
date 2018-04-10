%Judge static condition by using gyroscope data
function ret = C3(data_gyro)
    threshold_w_max = 50;
    w = (data_gyro(1)^2 + data_gyro(2)^2 + data_gyro(3)^2)^0.5;
    if(w < deg2rad(threshold_w_max))
        ret = 1;
    else
        ret = 0;
    end
end