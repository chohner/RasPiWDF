#include "fftman.h"

FftMan::FftMan(int bs, int hs, double *f, std::complex<  double> *F)
{
    blocksize = bs;

    /// Get pointers to objects
    frame       = f;
    FRAME       = F;

    /// Make the FFT-plan!
    pFFT    = fftw_plan_dft_r2c_1d(blocksize , frame, reinterpret_cast<fftw_complex*>(&FRAME[0]), FFTW_ESTIMATE);
}

FftMan::~FftMan()
{
    fftw_destroy_plan(pFFT);
    free(FRAME);
}


void FftMan::transform()
{
    fftw_execute(pFFT);
}
