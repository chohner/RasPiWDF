#include "delayline.h"

DelayLine::DelayLine(int l_dL)
{

    nCoef = 9;

    l_delayLine = l_dL;

    dl_l = new double[l_delayLine];
    dl_r = new double[l_delayLine];

    //    for (int i=0; i<l_delayLine-1; i++)
    //    {
    //        dl_l[i] = 0.0;
    //        dl_r[i] = 0.0;
    //    }

    // initialize delay lines



    for (int i= l_delayLine/2; i<l_delayLine; i++)
    {
        dl_l[i] = ((double) (l_delayLine- i) / (l_delayLine));
        dl_r[i] = ((double) (l_delayLine- i) / (l_delayLine));

    }


}

void DelayLine::init()
{
    for (int i=0; i<l_delayLine-1; i++)
    {
        dl_l[i] = ((double) i / (l_delayLine));
        dl_r[i] = ((double) i / (l_delayLine));
    }

}



void DelayLine::shift(int shiftFac)
{




    // apply filter
    double filtSumL = 0.0;
    double filtSumR = 0.0;


    for (int i=0; i<nCoef; i++)
    {

        filtSumL = filtSumL + dl_l[i] * filt[i];

        filtSumR = filtSumR + dl_r[l_delayLine-i] * filt[nCoef-i];

    }



    double damp     = 0.9;

    /*
    // the decimal part of the position
    double frac 	= shiftFac - floor(shiftFac);

    double lBuf = interpolate(0+frac,dl_l);
    double rBuf = interpolate((double) l_delayLine - -shiftFac ,dl_r);
*/

    //    printf("%lf \n",frac);

    // remember values
    // simple
    double lBuf = dl_l[0];
    double rBuf = dl_r[l_delayLine-1];



    // shift
    for (int i = 0; i < l_delayLine; i++)
    {
        /*
        // Left Line
        double interpVal_L  = interpolate(i+shiftFac,dl_l);
        dl_l[i]             = interpVal_L;

        //

        // right line

        double interpVal_R = interpolate(l_delayLine - i + shiftFac,dl_r);

        dl_r[l_delayLine-i] = interpVal_R;

*/
        // SIMPLE

        dl_l[i] = dl_l[i+1];

        dl_r[l_delayLine-i] = dl_r[l_delayLine-i-1] ;




    }

    /// insert with filter
    dl_l[l_delayLine-1]    = -filtSumR;
    dl_r[0]                = -filtSumL * damp;

}


void DelayLine::shift(double shiftFac)
{


    // shift
    for (int i = 0; i < l_delayLine; i++)
    {
        /*
        // Left Line
        double interpVal_L  = interpolate(i+shiftFac,dl_l);
        dl_l[i]             = interpVal_L;

        //

        // right line

        double interpVal_R = interpolate(l_delayLine - i + shiftFac,dl_r);

        dl_r[l_delayLine-i] = interpVal_R;

*/
    }

}


double DelayLine::getOutputAt(int pos)
{
    double sum = dl_l[l_delayLine-1] + dl_r[0] ;
    return sum;
}

double DelayLine::interpolate(double fP, double* x)
{

    double frac 		= fP- floor(fP);

    int lowerInd 		= floor(fP);
    int upperInd 		= lowerInd +1;
    double lowerVal 	= x[lowerInd];
    double upperVal 	= x[upperInd];
    double interpVal 	= (lowerVal * (1-frac)) + (upperVal * frac);

    // printf("%d %lf %d\n", lowerInd, fP, upperInd);

    return interpVal;

}


// right line
/*
 *

*/



/*

        */
