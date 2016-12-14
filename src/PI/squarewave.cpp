/**
 * \class Sinusoid
 *
 *
 * \brief Simple sinusoid handler class.
 *
 *
 *
 * \author Henrik von Coler
 *
 * \version $Revision: 0.5 $
 *
 * \date $Date: 2016/08/01 14:16:20 $
 *
 * Contact: von_coler@intelligent-noise-solutions.de
 *
 *
 */

#include "squarewave.h"

SquareWave::SquareWave(double f, double a, double p,  int fS)
{
    freq    = f;
    amp     = a;
    phi     = p;
    fs      = fS;
}

double SquareWave::getNextSample()
{

    /// This method gets the next sample of the sinusoid.
    /// The amplitude is applied and the angle of the
    /// sinusoid is increased, according to the sample rate.

    // get next square value


    // apply amplitude
    thisVal = thisVal*amp;

    // rotate to next step
    phi += 2.0*M_PI * freq * (1.0/fs);

    // wrap to 2 pi
    if(phi>=2*M_PI)
        phi=0;



    return thisVal;

}


double SquareWave::frequency()
{
    return freq;
}

double SquareWave::amplitude()
{
    return amp;
}

double SquareWave::phase()
{
    return phi;
}

void SquareWave::frequency(double f)
{
    freq = f;
}

void SquareWave::amplitude(double a)
{
    amp = a;
}

void SquareWave::phase(double p)
{
    phi = p;
}
