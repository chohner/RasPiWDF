#ifndef DELAYLINE_H
#define DELAYLINE_H

#include <iostream>
#include <cmath>

class DelayLine
{
private:

    int     nCoef;
    int     l_delayLine;
    double  *dl_l;
    double  *dl_r;
    double   damp;

    double filt[9] =
    {
        0.0172076703967365,
        0.0475656475141038,
        0.122129203877853,
        0.198133104120303,
        0.229928748182009,
        0.198133104120303,
        0.122129203877853,
        0.0475656475141038,
        0.0172076703967365
    };

public:

    DelayLine(int l_delayLine);

    /// overload this function
    void shift(int shiftFac);
    void shift(double shiftFac);

    double getOutputAt(int pos);

    double interpolate(double fP, double *x);

    void init();
};

#endif // DELAYLINE_H
