    #include <stdarg.h>

    int va_sum(int count, ...){
        // va_list is the type for varadic arguments
        va_list ap;
        // every va_list must be initialized with va_start!
        va_start(ap, count);
        //             |- - - > last non-variadic argument
        int sum = 0;
        for(int i = 0; i < count; i++)
            sum += va_arg(ap, int); // gets the next argument
                    /*    |    |- - > type of the arg, must be known statically!
                          |- - > va_list
                    */
        // every va_list must be "freed" with va_end
        va_end(ap);
    }