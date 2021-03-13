function y = exp(x, k)
    y = 0;
    for i = 1:k
        y = y + (pow(x, i)/fact(i));
    end
end

