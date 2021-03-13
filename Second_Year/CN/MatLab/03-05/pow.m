function y = pow(x, n)
    y = 1;
    for k = 1:n
        y = x*y;
    end
end

