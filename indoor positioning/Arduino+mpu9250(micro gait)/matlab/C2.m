%Judge stance condition by acceleration variance
function ret = C2(acc_b, k,acc_size)
    threshold_var_a = 3;
    s = 15;
    
    if(k <= 15)
        s = k - 1;
    end
    
    if(k > (acc_size-15))
        s = acc_size - k;
    end
    
    a_sum = [ 0 0 0]';
    
    for i = (k-s) : (k+s)
        a_sum = a_sum + acc_b(:,i);
    end
    a_ = a_sum/(2*s+1);
    
    a_var_sum = 0;
    for i = k-s : k+s
        a_var_sum = a_var_sum + dot((acc_b(:,i) - a_),(acc_b(:,i) - a_));
    end
    a_var = sqrt((a_var_sum/(2*s+1)));
    
    if(a_var < threshold_var_a)
        ret = 1;
    else
        ret = 0;
    end;
end