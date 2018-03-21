function ret = C1(data_acc)
    threshold_a_min = 9;
    threshold_a_max = 11;
    a = sqrt(data_acc(1)^2 + data_acc(2)^2 + data_acc(3)^2);
    if(a>threshold_a_min && a<threshold_a_max)
        ret = 1;
    else
        ret = 0;
    end
end