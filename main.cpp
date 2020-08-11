#include <iostream>
#include <math.h>
#include <tuple>

using namespace std;

double new_mean, new_var;

tuple<double, double> measurement_update(double mean1, double var1, double mean2, double var2)
{
    new_mean = (var2 * mean1 + var1 * mean2) / (var1 + var2);
    new_var = 1 / (1 / var1 + 1 / var2);
    return make_tuple(new_mean, new_var);
}

tuple<double, double> state_prediction(double mean1, double var1, double mean2, double var2)
{
    new_mean = mean1 + mean2;
    new_var = var1 + var2;
    return make_tuple(new_mean, new_var);
}

int main()
{
    //Measurements and measurement variance
    double measurements[5] = { 5, 6, 7, 9, 10 };
    double measurement_sig = 4;

    //Motions and motion variance
    double motion[5] = { 1, 1, 2, 1, 1 };
    double motion_sig = 2;

    //Initial state
    double mu = 10;
    double sig = 1;

    //######TODO: Put your code here below this line######//

    for (int i = 0; i < sizeof(measurements)/sizeof(*measurements); i++){
        auto data = measurement_update(mu, sig, measurements[i], measurement_sig);
        mu = get<0>(data);
        sig = get<1>(data);
        printf("update:  [%f, %f]\n", mu, sig);
        data = state_prediction(mu, sig, motion[i], motion_sig);
        mu = get<0>(data);
        sig = get<1>(data);
        printf("predict: [%f, %f]\n", mu, sig);
    }
    return 0;
}
