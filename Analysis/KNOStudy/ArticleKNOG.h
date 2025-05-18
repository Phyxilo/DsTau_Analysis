#include <TCanvas.h>
#include <TGraphErrors.h>
#include <TAxis.h>
#include <TLegend.h>
#include <TF1.h>
#include <TPaveStats.h>
#include <TStyle.h>
#include <TVirtualFitter.h>

#ifndef ARTICLEKNOG_H
#define ARTICLEKNOG_H

TH1F* ArticleKNOG() 
{
    const int nBins = 18;
    double xMin = 0.0;
    double xMax = 3.0;

    // Data points for proton-proton (pp) interactions
    const int n_pp = 18;
    double x_pp[n_pp] = {0.11068630497718314, 0.32748327581412845, 0.41465349449614813, 0.5441453082320613, 0.761923649389097,
                         0.9732862820785423, 1.1880714437593025, 1.2341713145455437, 1.4013968170889284, 1.455838335595937, 1.6248180375864831,
                         1.8424737074535076, 2.0551366558170727, 2.271381605848967, 2.4894420909730286,
                         2.704828341974844, 2.876163332733607, 2.923404046516953};
    double y_pp[n_pp] = {0.21279174576294335, 0.5255725659970228, 0.5066543299236579, 0.6376070360405884, 0.6845697390164294,
                         0.6594034661240321, 0.6008767736913265, 0.5285531868402005, 0.4670766016142469, 0.3862311022492933, 0.31091665187167966,
                         0.20098193190664138, 0.12938557557051747, 0.06589118173251575, 0.03741652213102441,
                         0.012578015104543655, 0.007487401499528837, 0.0026528549772612433};

    // Define error arrays for x and y
    double x_err[n_pp] = {0}; // Assuming no error in x-values
    double y_err[n_pp] = {0.05, 0.015, 0.015, 0.015, 0.015, 0.02, 0.015, 0.015, 0.015, 0.015, 0.015, 0.015, 0.015, 0.015, 0.015, 0.015, 0.015, 0.015};

    // Create a histogram
    TH1F *hist_pp = new TH1F("hist_pp", "", n_pp, xMin, xMax);

    // Fill the histogram with data points
    for (int i = 0; i < n_pp; ++i)
    {
        hist_pp->SetBinContent(i+1, y_pp[i]);
        hist_pp->SetBinError(i+1, y_err[i]);
    }

    return hist_pp;
}

#endif