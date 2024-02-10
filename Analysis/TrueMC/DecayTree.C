#define DecayTree_cxx
#include "DecayTree.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>

float dif = 10;
extern int subVolIndex;

//TCanvas *Canvas= new TCanvas("Canvas","Histogram Canvas",20,20,1920,1080);

TH1F *Hist1 = new TH1F("Hist1","Distance Distribution",dif,0,dif);
TH1F *Hist2 = new TH1F("Hist2","# of Matching Vertices",10,0,10);
TH1F *Hist3 = new TH1F("Hist3","VZ Distribution",200,0,80000);

TH1F *Hist4 = new TH1F("Hist4","TrueMC VX Distribution",200,-7500,7500);
TH1F *Hist5 = new TH1F("Hist5","TrueMC VY Distribution",200,-7500,7500);
TH1F *Hist6 = new TH1F("Hist6","TrueMC VZ Distribution",200,0,80000);

TH1F *Hist7 = new TH1F("Hist7","Not Matched TrueMC VZ Distribution",200,0,80000);
TH1F *Hist8 = new TH1F("Hist7","Not Matched Multiplicity Distribution",50,0,50);

TGraph *DataXY = new TGraph();
TGraph *DataXY2 = new TGraph();

vector<int> NotMacthingVTXId;

void DecayTree::Loop()
{
   vector<tuple<int, float, float, float, int>> NotMacthingEvent;
   char VertexingName[64];
   
   if (subVolIndex < 7) {sprintf(VertexingName,"../../EPOSSM_v2.1/Linked/RootOut_3Sigma/pl0%02d_0%02d.root", subVolIndex*10 + 1, subVolIndex*10 + 30);}
   else {sprintf(VertexingName,"../../EPOSSM_v2.1/Linked/RootOut_3Sigma/pl071_105.root");}

   TFile *Data = TFile::Open(VertexingName);
   
   TTree *treeDataVtx = (TTree*)Data->Get("VTX");

   int zMin = treeDataVtx->GetMinimum("vz");
   int zMax = treeDataVtx->GetMaximum("vz");

   TLeaf *VX = treeDataVtx->GetLeaf("vx");
   TLeaf *VY = treeDataVtx->GetLeaf("vy");
   TLeaf *VZ = treeDataVtx->GetLeaf("vz");
   TLeaf *W = treeDataVtx->GetLeaf("flagw");
   TLeaf *P = treeDataVtx->GetLeaf("intType");
   TLeaf *PN = treeDataVtx->GetLeaf("n_1ry_parent_dmin_cut");

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

      float vx = IntVtx[0]*10000;
      float vy = IntVtx[1]*10000;
      float vz = IntVtx[2]*10000;

      if (vz > zMin && vz < zMax && vx > -7500 && vx < 7500 && vy > -7500 && vy < 7500 && Region == 4 && Flag == 111)
      {
         Hist4->Fill(vx);
         Hist5->Fill(vy);
         Hist6->Fill(vz);

         //NotMacthingVTXId.push_back(Event);
         NotMacthingEvent.push_back(make_tuple(Event, vx, vy, vz, Multip));

         for (int i = 0; i < treeDataVtx->GetEntries(); i++)
         {
            treeDataVtx->GetEntry(i);

            if (W->GetValue() == 1 && PN->GetValue() > 0/* && P->GetValue() == 1*/)
            {
               float xDif = (vx - VX->GetValue());
               float yDif = (vy - VY->GetValue());
               float zDif = (vz - VZ->GetValue());

               mag = sqrt(xDif*xDif + yDif*yDif + zDif*zDif);

               if (mag <= dif)
               {
                  Hist1->Fill(mag);
                  Hist2->Fill(matchVtxNum);
                  Hist3->Fill(VZ->GetValue());
                  DataXY->SetPoint(matchedIndex, VX->GetValue(), VY->GetValue());

                  matchVtxNum++;
                  matchedIndex++;

                  int eNum = Event;

                  //NotMacthingVTXId.erase(find(NotMacthingVTXId.begin(), NotMacthingVTXId.end(), Event));
                  auto iter = find_if(NotMacthingEvent.begin(), NotMacthingEvent.end(), [eNum](const tuple<int, float, float, float, int>& sTuple) 
                  {
                     return get<0>(sTuple) == eNum;
                  });
                  NotMacthingEvent.erase(iter);

                  auto it = unique(NotMacthingEvent.begin(), NotMacthingEvent.end());
                  auto dist = distance(NotMacthingEvent.begin(), it);
                  NotMacthingEvent.resize(dist);

                  //cout << mag << endl;
               }
            }

            //cout << "DecayTree: " << IntVtx[2] << ", Vertexing: " << VZ->GetValue() << endl;
         }
      }     
      //cout << "X: " << IntVtx[0] << ", Y: " << IntVtx[1] << ", Z: " << IntVtx[2] << endl;

      //if (matchVtxNum != 0) cout << matchVtxNum << endl;
      //if (jentry%10000 == 0) cout << jentry << "/" << nentries << endl;
   }

   for (int i = 0; i < NotMacthingEvent.size(); i++)
   {
      Hist7->Fill(get<3>(NotMacthingEvent[i]));
      Hist8->Fill(get<4>(NotMacthingEvent[i]));

      DataXY2->SetPoint(i, get<1>(NotMacthingEvent[i]), get<2>(NotMacthingEvent[i]));
   }
}
