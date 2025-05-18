#include <TCanvas.h>
#include <TGraphErrors.h>
#include <TAxis.h>
#include <TLegend.h>
#include <TF1.h>
#include <TPaveStats.h>
#include <TStyle.h>
#include <TVirtualFitter.h>

Double_t KNOGFunc1(Double_t *x, Double_t *par);

void KNORef() 
{
    TF1 *KNOG1 = new TF1("KNOGFunc1", KNOGFunc1, 0.5, 3, 3);
    KNOG1->SetNpx(1000);  // Set smoothness by increasing the number of points
    
    // Set initial parameters
    KNOG1->SetParameter(0, 1.19);
    KNOG1->SetParameter(1, 0.62);
    KNOG1->SetParameter(2, 0.66);

    TVirtualFitter::SetMaxIterations(10); // Increase to 10,000 iterations

    // Data points for proton-proton (pp) interactions
    /*
    const int n_pp = 14;
    double x_pp[n_pp] = {0.11068630497718314, 0.32748327581412845, 0.5441453082320613, 0.761923649389097,
                         0.9732862820785423, 1.1880714437593025, 1.4013968170889284, 1.6248180375864831,
                         1.8424737074535076, 2.0551366558170727, 2.271381605848967, 2.4894420909730286,
                         2.704828341974844, 2.923404046516953};
    double y_pp[n_pp] = {0.21279174576294335, 0.5255725659970228, 0.6376070360405884, 0.6845697390164294,
                         0.6594034661240321, 0.6008767736913265, 0.4670766016142469, 0.31091665187167966,
                         0.20098193190664138, 0.12938557557051747, 0.06589118173251575, 0.03741652213102441,
                         0.012578015104543655, 0.0026528549772612433};
    */
    const int n_pp = 18;
    double x_pp[n_pp] = {0.11068630497718314, 0.32748327581412845, 0.41465349449614813, 0.5441453082320613, 0.761923649389097,
                         0.9732862820785423, 1.1880714437593025, 1.2341713145455437, 1.4013968170889284, 1.455838335595937, 1.6248180375864831,
                         1.8424737074535076, 2.0551366558170727, 2.271381605848967, 2.4894420909730286,
                         2.704828341974844, 2.876163332733607, 2.923404046516953};
    double y_pp[n_pp] = {0.21279174576294335, 0.5255725659970228, 0.5066543299236579, 0.6376070360405884, 0.6845697390164294,
                         0.6594034661240321, 0.6008767736913265, 0.5285531868402005, 0.4670766016142469, 0.3862311022492933, 0.31091665187167966,
                         0.20098193190664138, 0.12938557557051747, 0.06589118173251575, 0.03741652213102441,
                         0.012578015104543655, 0.007487401499528837, 0.0026528549772612433};

    // Create canvas
    TCanvas *c1 = new TCanvas("c1", "Proton-Proton Interactions with KNO-G Fit", 800, 600);

    // Define error arrays for x and y
    double x_err[n_pp] = {0}; // Assuming no error in x-values
    double y_err[n_pp] = {0.05, 0.015, 0.015, 0.015, 0.015, 0.02, 0.015, 0.015, 0.015, 0.015, 0.015, 0.015, 0.015, 0.015, 0.015, 0.015, 0.015, 0.015};
    /*
    double y_err[n_pp];
    for (int i = 0; i < n_pp; ++i) {
        y_err[i] = y_pp[i] * 0.05; // Example: 5% error on y-values
    }
    */

    // Create TGraphErrors for proton-proton data with error bars
    TGraphErrors *graph_pp = new TGraphErrors(n_pp, x_pp, y_pp, x_err, y_err);
    graph_pp->SetMarkerStyle(21);
    graph_pp->SetMarkerColor(kBlue);
    graph_pp->SetTitle("Proton-Proton Interaction with KNO-G Fit");
    graph_pp->GetXaxis()->SetTitle("z");
    graph_pp->GetYaxis()->SetTitle("Multiplicity");

    // Set axis ranges
    graph_pp->GetXaxis()->SetRangeUser(0, 3);  // Set x-axis (z-axis) range from 0 to 3
    graph_pp->GetYaxis()->SetRangeUser(0, 0.8);  // Set y-axis range from 0 to 0.8

    // Fit the graph with KNO-G function
    graph_pp->Fit("KNOGFunc1", "R+");

    // Draw the graph
    graph_pp->Draw("AP");

    // Get fit statistics and display chi-square in the stats box
    c1->Update();
    TPaveStats *statBox = (TPaveStats*)graph_pp->FindObject("stats");
    if (statBox) {
        statBox->SetName("StatBox1");
        statBox->SetY1NDC(0.75);  // Move box to top right corner
        statBox->SetY2NDC(0.95);
        statBox->SetX1NDC(0.7);
        statBox->SetX2NDC(0.95);
        statBox->SetTextColor(kRed);
        gStyle->SetStatFontSize(0.02);
        statBox->SetOptStat(0);
        statBox->SetOptFit(1111);  // Show fit parameters and chi-square
    }

    // Add legend
    TLegend *legend1 = new TLegend(0.28, 0.85, 0.08, 0.95);
    legend1->AddEntry(graph_pp, "pp Interaction", "lp");
    legend1->AddEntry(KNOG1, "KNO-G Scaling (#Psi_{1})", "l");
    legend1->Draw();

    // Save the output as a PDF
    c1->SaveAs("KNORef.pdf");

    // Display the canvas
    c1->Update();
}

Double_t KNOGFunc1(Double_t *x, Double_t *par)
{
    double n = x[0];
    double funct = par[0] * pow(n, par[2]) * exp(-par[1] * n * n);
    return funct;
}
