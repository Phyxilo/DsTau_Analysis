#include <iostream>
#include <vector>
#include <cmath>

#include "TROOT.h"
#include "TFile.h"
#include "TTree.h"
#include "TBrowser.h"
#include "TH2.h"

#include "TPaveStats.h"
#include "TPaveText.h"
#include "TText.h"
#include "TPavesText.h"
#include "TGraphErrors.h"

using namespace std;

#ifndef ARTICLEKNO_H
#define ARTICLEKNO_H

// Arrays for Charged topology, Corrected number of events, and errors
const int dataSize = 16;
int ChargedTopology[dataSize] = {2, 4, 6, 8, 10, 12, 14, 16, 18, 20, 22, 24, 26, 28, 30, 32};
int CorrectedEvents[dataSize] = {510, 1238, 1490, 1590, 1539, 1404, 1078, 734, 478, 312, 170, 97, 43, 27, 11, 6};
int AbsoluteErrors[dataSize] = {191, 35, 39, 40, 39, 37, 33, 27, 22, 18, 13, 10, 7, 5, 3, 3};

TH1F* ArticleKNO()
{
    // Calculate percentage errors
    double PercentageErrors[dataSize];
    for (int i = 0; i < dataSize; i++)
    {
        if (CorrectedEvents[i] != 0)
        {
            PercentageErrors[i] = (static_cast<double>(AbsoluteErrors[i]) / CorrectedEvents[i]) * 100.0;
        } else
        {
            PercentageErrors[i] = 0.0; // Avoid division by zero
        }
    }

    // Define histogram with 16 bins (one for each ChargedTopology value)
    TH1F *hist = new TH1F("hist", "Charged Topology vs Corrected Events with Percentage Errors", dataSize, 0, 34);

    // Fill histogram bins with CorrectedEvents and set bin errors as percentage errors
    for (int i = 0; i < dataSize; i++)
    {
        float index = float(ChargedTopology[i]/(2));

        hist->SetBinContent(index, CorrectedEvents[i]); // Set bin content
        hist->SetBinError(index, (CorrectedEvents[i] * PercentageErrors[i]) / 100.0); // Set error as a fraction of the bin value
    }

    // Customize the histogram appearance
    hist->SetStats(0); // Remove statistics box
    hist->SetLineColor(kBlue);
    hist->SetLineWidth(2);
    hist->SetFillColorAlpha(kBlue, 0.3); // Add a translucent fill color

    float ScalingFactor = 0;
    for (int i = 0; i < dataSize; i++) {ScalingFactor += CorrectedEvents[i];}

    // Set axis labels
    hist->GetXaxis()->SetTitle("Charged Topology");
    hist->GetYaxis()->SetTitle("Corrected Number of Events");

    // Retrieve the number of bins
    int nBins = hist->GetNbinsX();
    float MultipMean = hist->GetMean();

    // Create a new histogram to store the scaled values (optional)
    TH1F *scaledHist = new TH1F("scaledHist", "", nBins,
                                hist->GetXaxis()->GetXmin() / MultipMean,
                                hist->GetXaxis()->GetXmax() / MultipMean);

    // Iterate over the bins and update values
    for (int i = 1; i <= nBins; ++i)
    {
        double binContent = hist->GetBinContent(i);
        double binError = hist->GetBinError(i);
        double binCenter = hist->GetBinCenter(i) / MultipMean;

        // Set the bin content in the new histogram
        int binIndex = scaledHist->FindBin(binCenter);
        scaledHist->SetBinContent(binIndex, binContent);
        scaledHist->SetBinError(binIndex, binError);
    }
    
    scaledHist->Scale((MultipMean)/ScalingFactor);
    scaledHist->SetStats(0);

    return scaledHist;
}

#endif