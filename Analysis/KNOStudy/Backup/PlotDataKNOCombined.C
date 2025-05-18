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

#include "ArticleKNO.h"
#include "ArticleKNOG.h"
#include "DataKNO.h"


using namespace std;

Double_t KNOGFunc1 (Double_t *x, Double_t *par);

// ROOT canvas
TCanvas *Canvas = new TCanvas("Canvas", "Histogram Canvas", 800, 600);

void PlotDataKNOCombined()
{
    // Define the fit function
    //TF1 *KNOG1 = new TF1("KNOGFunc1", KNOGFunc1, 0, 3, 3); // Full range fit
    TF1 *KNOG1 = new TF1("KNOGFunc1", KNOGFunc1, 0.5, 3, 3);

    // Retrieve histograms
    auto articleHist = ArticleKNOG();
    auto dataHist = DataKNO();

    articleHist->SetMarkerColor(kRed);
    dataHist->SetMarkerColor(kBlue);

    articleHist->SetMarkerStyle(22);

    // Draw histograms
    articleHist->Draw("PE1");
    dataHist->Draw("SAMESPE1");

    float highEnergyPoints [18] = {1, 1, 0, 1, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1};

    for (int i = 1; i <= 18; ++i) {
        if (highEnergyPoints[i-1] == 1)
        {
            double x = articleHist->GetBinCenter(i);
            double y = articleHist->GetBinContent(i);
            TMarker *marker = new TMarker(x, y, 21);
            marker->SetMarkerColor(kRed);
            marker->Draw();
        }
    }

    // Fit histograms
    articleHist->Fit("KNOGFunc1", "R");
    dataHist->Fit("KNOGFunc1", "R");

    TF1 *articleFit = articleHist->GetFunction("KNOGFunc1");
    TF1 *dataFit = dataHist->GetFunction("KNOGFunc1");
    
    if (articleFit) {articleFit->SetLineColor(kRed);}
    if (dataFit) {dataFit->SetLineColor(kBlue);}

    // Update canvas to reflect changes
    Canvas->Update();

    // Find and adjust the first statistics box
    TPaveStats *StatBox1 = (TPaveStats*)dataHist->FindObject("stats");
    StatBox1->SetName("StatBox1");
    StatBox1->SetY1NDC(0.95);
    StatBox1->SetY2NDC(0.75);
    StatBox1->SetX1NDC(0.70);
    StatBox1->SetX2NDC(1.0);
    StatBox1->SetTextColor(kBlue);
    StatBox1->SetOptStat(0);

    // Add a second statistics box for articleHist
    TPaveStats *StatBox2 = (TPaveStats*)articleHist->FindObject("stats");
    StatBox2->SetName("StatBox2");
    StatBox2->SetY1NDC(0.75); // Adjust position below the first box
    StatBox2->SetY2NDC(0.55);
    StatBox2->SetX1NDC(0.70);
    StatBox2->SetX2NDC(1.0);
    StatBox2->SetTextColor(kRed);
    StatBox2->SetOptStat(0);

    // Draw legend
    TLegend *legend1 = new TLegend(0.28, 0.85, 0.08, 0.95);
    legend1->AddEntry(dataHist, "Data Histogram", "fel");
    legend1->AddEntry(articleHist, "Article Histogram", "fel");
    legend1->Draw();

    // Set y-axis range
    articleHist->GetYaxis()->SetRangeUser(0, 1);

    // Save canvas
    Canvas->SaveAs("CombinedHistogramKNO.pdf");

    // Print histogram mean
    cout << "\nHistogram Mean: " << articleHist->GetMean() << endl;
}

Double_t KNOGFunc1 (Double_t *x, Double_t *par)
{
  double n = x[0];
  double fitMean = 15.9177;
  double meanRatio = (fitMean + par[3])/fitMean;
  double funct = par[0]*pow(n, par[2])*exp(-par[1]*(n)*(n));

  return funct;
}