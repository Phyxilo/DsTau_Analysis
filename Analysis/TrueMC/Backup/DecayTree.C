#define DecayTree_cxx
#include "DecayTree.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>

float dif = 10;

TCanvas *Canvas= new TCanvas("Canvas","Histogram Canvas",20,20,1920,1080);

TH1F *Hist1 = new TH1F("Hist1","Distance Distribution",dif,0,dif);
TH1F *Hist2 = new TH1F("Hist2","# of Matching Vertices",10,0,10);
TH1F *Hist3 = new TH1F("Hist3","VZ Distribution",200,0,10000);
TGraph *DataXY = new TGraph();

TH1F *Hist4 = new TH1F("Hist4","TrueMC VX Distribution",200,-7500,7500);
TH1F *Hist5 = new TH1F("Hist5","TrueMC VY Distribution",200,-7500,7500);
TH1F *Hist6 = new TH1F("Hist6","TrueMC VZ Distribution",200,2300,8000);
TGraph *DataXY2 = new TGraph();

void DecayTree::Loop()
{
   TFile *Data = TFile::Open("../../EPOS_v2.1/Linked/RootOut_3Sigma/pl001_030.root");
   
   TTree *treeDataVtx = (TTree*)Data->Get("VTX");

   TLeaf *VX = treeDataVtx->GetLeaf("vx");
   TLeaf *VY = treeDataVtx->GetLeaf("vy");
   TLeaf *VZ = treeDataVtx->GetLeaf("vz");
   TLeaf *W = treeDataVtx->GetLeaf("flagw");
   TLeaf *P = treeDataVtx->GetLeaf("intType");
   TLeaf *PN = treeDataVtx->GetLeaf("n_1ry_parent_dmin_cut");

   char  outName[64], outNameStart[64], outNameEnd[64];
   sprintf(outName,"TrueMC.pdf");
   sprintf(outNameStart,"%s(", outName);
   sprintf(outNameEnd,"%s)", outName);

   int matchedIndex = 0;

   if (fChain == 0) return;

   Long64_t nentries = fChain->GetEntriesFast();

   Long64_t nbytes = 0, nb = 0;
   for (Long64_t jentry=0; jentry<nentries;jentry++) 
   {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;
      // if (Cut(ientry) < 0) continue;

      float mag = 0;
      int matchVtxNum = 0;

      int vx = IntVtx[0]*10000;
      int vy = IntVtx[1]*10000;
      int vz = IntVtx[2]*10000;

      if (vz > 2340 && vz < 8000 && vx > -7500 && vx < 7500 && vy > -7500 && vy < 7500 && Region == 4 && Flag == 111)
      {
         Hist4->Fill(vx);
         Hist5->Fill(vy);
         Hist6->Fill(vz);

         DataXY2->SetPoint(jentry, vx, vy);

         for (int i = 0; i < treeDataVtx->GetEntries(); i++)
         {
            treeDataVtx->GetEntry(i);

            if (W->GetValue() == 1 && PN->GetValue() > 0 && P->GetValue() == 1)
            {
               float xDif = (vx - VX->GetValue());
               float yDif = (vy - VY->GetValue());
               float zDif = (vz - VZ->GetValue());

               mag = sqrt(xDif*xDif + yDif*yDif + zDif*zDif);

               if (mag <= dif)
               //if (xDif <= dif && xDif >= -dif && yDif <= dif && yDif >= -dif)
               {
                  Hist1->Fill(mag);
                  Hist2->Fill(matchVtxNum);
                  Hist3->Fill(VZ->GetValue());
                  DataXY->SetPoint(matchedIndex, VX->GetValue(), VY->GetValue());

                  matchVtxNum++;
                  matchedIndex++;

                  //cout << mag << endl;

                  //cout << IntVtx[2]*1000 << ", " << VZ->GetValue() << endl;
               }
            }

            //cout << "DecayTree: " << IntVtx[2] << ", Vertexing: " << VZ->GetValue() << endl;
         }
      }     
      //cout << "X: " << IntVtx[0] << ", Y: " << IntVtx[1] << ", Z: " << IntVtx[2] << endl;

      //if (matchVtxNum != 0) cout << matchVtxNum << endl;
      if (jentry%10000 == 0) cout << jentry << "/" << nentries << endl;
   }

   Hist1->Draw();
   Canvas->Print( outNameStart, "pdf");

   Hist2->Draw();
   Canvas->Print( outName, "pdf");

   Hist3->Draw();
   Canvas->Print( outName, "pdf");

   DataXY->SetTitle("Vertex X vs Y Scatter Plot; Vertex X; Vertex Y");
   DataXY->GetXaxis()->SetLimits(-7500, 7500);
   DataXY->GetHistogram()->SetMaximum(7500);
   DataXY->GetHistogram()->SetMinimum(-7500);
   DataXY->Draw("AP");
   Canvas->Print( outName, "pdf");

   Hist4->Draw();
   Canvas->Print( outName, "pdf");

   Hist5->Draw();
   Canvas->Print( outName, "pdf");

   Hist6->Draw();
   Canvas->Print( outName, "pdf");

   DataXY2->SetTitle("Vertex X vs Y Scatter Plot; Vertex X; Vertex Y");
   DataXY2->GetXaxis()->SetLimits(-7500, 7500);
   DataXY2->GetHistogram()->SetMaximum(7500);
   DataXY2->GetHistogram()->SetMinimum(-7500);
   DataXY2->Draw("AP");
   Canvas->Print( outNameEnd, "pdf");
}
