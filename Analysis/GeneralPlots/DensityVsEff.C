#include <TCanvas.h>
#include <TGraph.h>
#include <TF1.h>
#include <TAxis.h>

void DensityVsEff() {
    // Vertexing Data
    double track_density[] = {88284, 98261, 100902, 111954, 116309, 128696, 133910, 147448, 153990, 168655, 175443, 192257, 199477, 217850, 224584, 245572};
    double efficiency[] = {77.27, 75.74, 75.66, 76.06, 76.30, 74.47, 75.38, 75.16, 75.25, 74.02, 74.86, 74.17, 73.93, 73.69, 74.08, 72.42};

    // Total Data
    //double track_density[] = {88284, 98261, 100902, 111954, 116309, 128696, 133910, 147448, 153990, 168655, 175443, 192257, 199477, 217850, 224584, 245572};
    //double efficiency[] = {71.96, 71.74, 69.51, 71.50, 70.09, 69.39, 67.76, 69.13, 67.24, 66.89, 65.96, 65.60, 64.22, 64.56, 62.74, 61.97};

    // PLink Data
    //double track_density[] = {88284, 98261, 100902, 111954, 116309, 128696, 133910, 147448, 153990, 168655, 175443, 192257, 199477, 217850, 224584, 245572};
    //double efficiency[] = {93.35, 93.13, 93.41, 93.32, 93.32, 93.34, 93.11, 93.26, 92.75, 92.99, 92.20, 92.53, 91.45, 91.88, 90.37, 91.18};

    for (int i = 0; i < 16; ++i) 
    {
        efficiency[i] /= 100.0;
    }

    // Create a TGraph
    TGraph *graph = new TGraph(16, track_density, efficiency);
    graph->SetTitle(" ;Track Density;Vertexing Efficiency");
    graph->SetMarkerStyle(20);
    graph->SetMarkerSize(2.0);
    graph->SetMarkerColor(kBlue);

    // Create a canvas
    TCanvas *Canvas = new TCanvas("Canvas", "Scatter Plot with Linear Fit", 800*2, 600*2);
    graph->Draw("AP");
    graph->GetYaxis()->SetRangeUser(0.0, 1.0); 

    // Create a linear fit function
    TF1 *fit = new TF1("fit", "pol1", 80000, 250000);
    fit->SetNpx(10000);
    graph->Fit(fit, "R");

    // Draw the fit
    fit->SetLineColor(kRed);
    fit->SetLineWidth(4.0);
    fit->Draw("same");

    // Update the canvas
    Canvas->SetGrid();
    Canvas->Update();
    Canvas->Print("VertexingEffVsDensity.png", "png");
}