#include "DecayTree.C"

TCanvas *Canvas= new TCanvas("Canvas","Histogram Canvas",20,20,1920,1080);

extern TH1F *Hist1, *Hist2, *Hist3, *Hist4, *Hist5, *Hist6, *Hist7, *Hist8;
extern TGraph *DataXY, *DataXY2;

int dirIndex;
int subVolIndex;

void Efficiency()
{
   for (subVolIndex = 0; subVolIndex < 8; subVolIndex++)
   {
      char  outName[64], outNameStart[64], outNameEnd[64];
      sprintf(outName,"TrueMC_SV%d.pdf", subVolIndex);
      sprintf(outNameStart,"%s(", outName);
      sprintf(outNameEnd,"%s)", outName);

      for (dirIndex = 1; dirIndex <= 2; dirIndex++)
      {
         DecayTree t;
         t.Loop();
      }

      Hist1->Draw();
      Canvas->Print( outNameStart, "pdf");

      Hist2->Draw();
      Canvas->Print( outName, "pdf");

      Hist3->Draw();
      Canvas->Print( outName, "pdf");

      Hist4->Draw();
      Canvas->Print( outName, "pdf");

      Hist5->Draw();
      Canvas->Print( outName, "pdf");

      Hist6->Draw();
      Canvas->Print( outName, "pdf");

      Hist7->Draw();
      Canvas->Print( outName, "pdf");

      Hist8->Draw();
      Canvas->Print( outNameEnd, "pdf");

      Hist1->Reset("ICESM");
      Hist2->Reset("ICESM");
      Hist3->Reset("ICESM");
      Hist4->Reset("ICESM");
      Hist5->Reset("ICESM");
      Hist6->Reset("ICESM");
      Hist7->Reset("ICESM");
      Hist8->Reset("ICESM");
   }

   DataXY->SetTitle("Matched Vertex X vs Y Scatter Plot; Vertex X; Vertex Y");
   DataXY->GetXaxis()->SetLimits(-7500, 7500);
   DataXY->GetHistogram()->SetMaximum(7500);
   DataXY->GetHistogram()->SetMinimum(-7500);
   DataXY->Draw("AP");
   Canvas->Print( "ScatterPlot.pdf(", "pdf");

   DataXY2->SetTitle("Not Matched Vertex X vs Y Scatter Plot; Vertex X; Vertex Y");
   DataXY2->GetXaxis()->SetLimits(-7500, 7500);
   DataXY2->GetHistogram()->SetMaximum(7500);
   DataXY2->GetHistogram()->SetMinimum(-7500);
   DataXY2->Draw("AP");
   Canvas->Print( "ScatterPlot.pdf)", "pdf");
}