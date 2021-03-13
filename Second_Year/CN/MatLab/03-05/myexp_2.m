function y = myexp_2(x,k)
    prev = 1;
    y = 1;
    for i = 1:k
        prev = prev * (x/i);
        y = y + prev;
    end
end