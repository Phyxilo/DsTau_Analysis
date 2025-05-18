#include "TROOT.h"
#include <iostream>

void Test() {
    TGraph *g1 = new TGraph();
    TCanvas *c1 = new TCanvas("c1", "Canvas", 1920, 1080);
    c1->SetGrid();

    int totalDuplicates = 0;
    int totalEntries = 0;

    for (int i = 0; i < 8; i++) {
        
        int numDuplicates = 0;
        int numEntries = 0;

        char name[64];
        int prevArea1 = 0, prevArea2 = 0, prevI = 0;
        
        if (i < 7) {
            snprintf(name, 64, "Linked/RootOut/pl%03d_%03d.root", i * 10 + 1, 30 + 10 * i);
        } else {
            snprintf(name, 64, "Linked/RootOut/pl071_105.root");
        }
        // std::cout << "Opening file: " << name << std::endl;

        TFile *file = TFile::Open(name);

        if (file && file->IsOpen()) {
            std::cout << "Opening file: " << name << std::endl;

            TTree *dsFinal = (TTree*)file->Get("DsFinal");
            TLeaf *ds_area1 = dsFinal->GetLeaf("area1");
            TLeaf *ds_area2 = dsFinal->GetLeaf("area2");
            TLeaf *ds_i = dsFinal->GetLeaf("i");
            TLeaf *ds_vID = dsFinal->GetLeaf("vID");

            TTree *dsVTX = (TTree*)file->Get("VTX");
            TLeaf *ds_iType = dsVTX->GetLeaf("intType");

            Long64_t nentries = dsFinal->GetEntries();
            for (Long64_t entry = 0; entry < nentries; ++entry) {
                dsFinal->GetEntry(entry);
                double area1 = ds_area1->GetValue();
                double area2 = ds_area2->GetValue();
                double ind = ds_i->GetValue();

                if (ds_vID->GetValue() > 0) {
                    dsVTX->GetEntry(ds_vID->GetValue());
                    if (ds_iType->GetValue() == 1) {
                        if(prevArea1 == area1 && prevArea2 == area2 && prevI == ind) {
                            numDuplicates++;
                            totalDuplicates++;
                            // std::cout << "Duplicate entry found: " << area1 << ", " << area2 << ", " << ind << std::endl;
                        }
                    }
                }

                if(prevArea1 == area1 && prevArea2 == area2 && prevI == ind) {
                    // numDuplicates++;
                    // totalDuplicates++;
                    // std::cout << "Duplicate entry found: " << area1 << ", " << area2 << ", " << ind << std::endl;
                }

                prevArea1 = area1;
                prevArea2 = area2;
                prevI = ind;

                numEntries++;
                totalEntries++;
            }

        } else {
            std::cout << "Failed to open file." << std::endl;
            return;
        }

        double percentage = (double)numDuplicates / numEntries * 100;
        g1->SetPoint(i, i, percentage);
        TLatex *latex = new TLatex(i, percentage + 0.5, Form("%.2f%%", percentage));
        latex->SetTextSize(0.03);
        latex->SetTextAlign(22); // Center alignment
        latex->Draw();
    }

    g1->SetTitle("Percentage of doubles");
    g1->GetXaxis()->SetTitle("Subvolume");
    g1->GetYaxis()->SetTitle("Percentage of doubles");
    g1->SetMarkerStyle(20);
    g1->SetMarkerColor(kRed);
    g1->SetMarkerSize(2.5);
    g1->SetMaximum(30);
    g1->SetMinimum(0);
    g1->GetXaxis()->SetNdivisions(10);
    g1->GetYaxis()->SetNdivisions(10);
    g1->Draw("AP");      
    
    c1->SaveAs("doubles.pdf"); // Save the canvas as a PDF file

    double totalPercentage = (double)totalDuplicates / totalEntries * 100;
    std::cout << "Total percentage of duplicates: " << totalPercentage << "%" << std::endl;

    //std::cout << "Number of duplicates: " << numDuplicates << std::endl;
    //std::cout << "Total entries: " << numEntries << std::endl;
    //std::cout << "Percentage of duplicates: " << (double)numDuplicates / numEntries * 100 << "%" << std::endl;
}