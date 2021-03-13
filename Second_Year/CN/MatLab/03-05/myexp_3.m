function y = myexp_3(x,k)
    sign = 1;
    if(x < 0)
        x = -x;
        sign = 0;
    end
    
    prev = 1;
    y = 1;
    for i = 1:k
        prev = prev * (x/i);
        y = y + prev;
    end
    
    if(sign == 0)
        y = 1/y;
    end
end