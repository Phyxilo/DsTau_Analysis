#include <TH1.h>
#include <TCanvas.h>
#include <TFile.h>
#include <iostream>

void test() {
    // Create or load two histograms
    TH1F *h1 = new TH1F("h1", "Histogram 1", 100, 0, 10);
    TH1F *h2 = new TH1F("h2", "Histogram 2", 100, 0, 10);

    // Fill histograms with some data
    for (int i = 0; i < 1000; ++i) {
        h1->Fill(gRandom->Gaus(4.5, 1)); // Gaussian with mean 5, sigma 1
        h2->Fill(gRandom->Gaus(5, 1)); // Gaussian with mean 5, sigma 1
    }

    // Perform the Kolmogorov test
    double pValue = h1->KolmogorovTest(h2);

    // Print the result
    std::cout << "Kolmogorov Test p-value: " << pValue << std::endl;

    // Optional: Draw the histograms for visualization
    TCanvas *c = new TCanvas("c", "Histogram Comparison", 800, 600);
    h1->SetLineColor(kRed);
    h2->SetLineColor(kBlue);
    h1->Draw();
    h2->Draw("SAME");
}
