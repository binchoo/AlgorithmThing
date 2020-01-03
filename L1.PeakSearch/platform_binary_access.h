#define DTYPE int
#define RTNTYPE DTYPE

RTNTYPE platform_binary_access(DTYPE* arr, unsigned long length) {
    
    unsigned long middle = (int) (length / 2);
    unsigned long left_length, right_length;
    
    DTYPE* left_arr = arr;
    DTYPE* right_arr = arr + middle + 1;
    
    left_length = middle;
    right_length = length - middle - 1;
    
    if (!(left_length > 0 && right_length > 0)) {
        RTNTYPE base_calc;
        return base_calc;
    }
    if (left_length > 0) {
        RTNTYPE left_calc = platform_binary_access(left_arr, left_length);
        return left_calc;
    }
    if (right_length > 0) {
        RTNTYPE right_calc =platform_binary_access(right_arr, right_length);
        return right_calc;
    }   
}