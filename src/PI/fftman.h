/**
 * \class FftMan
 *
 *
 * \brief Class for performing the sinusoidal modeling of a signal block.
 *
 * This class takes a signal block, transforms it to the frequency domain.
 *
* \todo Implement sinusoidal analysis!
 *
 *
 * \author Henrik von Coler
 *
 * \version $Revision: 0.5 $
 *
 * \date $Date: 2005/04/14 14:16:20 $
 *
 * Contact: von_coler@intelligent-noise-solutions.de
 *
 *
 */

#ifndef FFTMAN_H
#define FFTMAN_H

#include <stdlib.h>
#include <cmath>
#include <complex>  // USE THIS before FFTW
#include <fftw3.h>

class FftMan
{
public:
    FftMan(int bs, int hs,   double *f, std::complex<double> *F);
    ~FftMan();
    void fetchData();
    void transform();


private:

    int blocksize;

    double *frame;
    std::complex<  double> *FRAME;


    fftw_plan pFFT;


};

#endif // FFTMAN_H
