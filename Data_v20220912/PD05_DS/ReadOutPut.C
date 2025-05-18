#include <TFile.h>
#include <TTree.h>
#include <TH1F.h>  // Include for histogram
#include <iostream>
#include <cmath>   // Include for sqrt

float CalculateFlightLength(float X1, float X2, float Y1, float Y2, float Z1, float Z2)
{
    float f = sqrt((X1-X2)*(X1-X2) + (Y1-Y2)*(Y1-Y2) + (Z1-Z2)*(Z1-Z2));
    return f;
}

void ReadOutPut() {
    TH1F *f_length = new TH1F("f_length", "Flight Length Distribution", 100, 0, 10000);

    TFile *fileOut = TFile::Open("Output.root", "RECREATE");
    fileOut->cd(); 

    TTree *outputTree = new TTree("MergedTree", "Merged Data with Flight Length");

    // Variables to hold data
    int i_sumfinal, area1_sumfinal, area2_sumfinal, c1, c2, c3, n2, n3, n4;
    int i_final, area1_final, area2_final;
    float VX, VY, VZ, Vx, Vy, Vz, vx, vy, vz, flen;

    // Set branches in the output tree
    outputTree->Branch("i_sumfinal", &i_sumfinal, "i_sumfinal/I");
    outputTree->Branch("area1_sumfinal", &area1_sumfinal, "area1_sumfinal/I");
    outputTree->Branch("area2_sumfinal", &area2_sumfinal, "area2_sumfinal/I");
    outputTree->Branch("c1", &c1, "c1/I");
    outputTree->Branch("c2", &c2, "c2/I");
    outputTree->Branch("c3", &c3, "c3/I");
    outputTree->Branch("n2", &n2, "n2/I");
    outputTree->Branch("n3", &n3, "n3/I");
    outputTree->Branch("n4", &n4, "n4/I");
    outputTree->Branch("VX", &VX, "VX/F");
    outputTree->Branch("VY", &VY, "VY/F");
    outputTree->Branch("VZ", &VZ, "VZ/F");
    outputTree->Branch("i_final", &i_final, "i_final/I");
    outputTree->Branch("area1_final", &area1_final, "area1_final/I");
    outputTree->Branch("area2_final", &area2_final, "area2_final/I");
    outputTree->Branch("Vx", &Vx, "Vx/F");
    outputTree->Branch("Vy", &Vy, "Vy/F");
    outputTree->Branch("Vz", &Vz, "Vz/F");
    outputTree->Branch("vx", &vx, "vx/F");
    outputTree->Branch("vy", &vy, "vy/F");
    outputTree->Branch("vz", &vz, "vz/F");
    outputTree->Branch("flightLength", &flen, "flightLength/F");
    
    for (int dirIndex = 0; dirIndex < 1; dirIndex++) {
        char inputFile[256];
        snprintf(inputFile, 256, "/Users/emin/Desktop/Workspace/Matching2Root/DataRootOutFinal/p%03d.root", dirIndex*10 + 6);

        // Open the ROOT file
        TFile *file = TFile::Open(inputFile, "READ");

        if (!file || file->IsOpen() == false) {
            std::cerr << "Error: Could not open the file!" << std::endl;
            return;  // Remove return value for void function
        }

        TTree *ds_sumfinal_tree = (TTree*)file->Get("ds_sumfinal_tree");
        TTree *ds_final_tree = (TTree*)file->Get("ds_final_tree");

        if (!ds_sumfinal_tree || !ds_final_tree) {
            std::cerr << "Error: Trees not found in the file!" << std::endl;
            return;  // Remove return value for void function
        }

        // Set branch addresses for ds_sumfinal_tree
        ds_sumfinal_tree->SetBranchAddress("i", &i_sumfinal);
        ds_sumfinal_tree->SetBranchAddress("area1", &area1_sumfinal);
        ds_sumfinal_tree->SetBranchAddress("area2", &area2_sumfinal);
        ds_sumfinal_tree->SetBranchAddress("c1", &c1);
        ds_sumfinal_tree->SetBranchAddress("c2", &c2);
        ds_sumfinal_tree->SetBranchAddress("c3", &c3);
        ds_sumfinal_tree->SetBranchAddress("n2", &n2);
        ds_sumfinal_tree->SetBranchAddress("n3", &n3);
        ds_sumfinal_tree->SetBranchAddress("n4", &n4);
        ds_sumfinal_tree->SetBranchAddress("1ry_vx", &VX);
        ds_sumfinal_tree->SetBranchAddress("1ry_vy", &VY);
        ds_sumfinal_tree->SetBranchAddress("1ry_vz", &VZ);

        // Set branch addresses for ds_final_tree
        ds_final_tree->SetBranchAddress("i", &i_final);
        ds_final_tree->SetBranchAddress("area1", &area1_final);
        ds_final_tree->SetBranchAddress("area2", &area2_final);
        ds_final_tree->SetBranchAddress("1ry_vx", &Vx);
        ds_final_tree->SetBranchAddress("1ry_vy", &Vy);
        ds_final_tree->SetBranchAddress("1ry_vz", &Vz);
        ds_final_tree->SetBranchAddress("2ry_vx", &vx);
        ds_final_tree->SetBranchAddress("2ry_vy", &vy);
        ds_final_tree->SetBranchAddress("2ry_vz", &vz);

        // Loop over the entries in ds_sumfinal_tree
        Long64_t nEntriesFinal = ds_final_tree->GetEntries();
        for (Long64_t entryFinal = 0; entryFinal < nEntriesFinal; ++entryFinal) {
            ds_final_tree->GetEntry(entryFinal);
            
            Long64_t nEntriesSumFinal = ds_sumfinal_tree->GetEntries();
            for (Long64_t entrySumFinal = 0; entrySumFinal < nEntriesSumFinal; ++entrySumFinal) {
                ds_sumfinal_tree->GetEntry(entrySumFinal);

                if (c1 == 0 && c2 == 0 && c3 != 0 && n2 != 0 && n3 == 0 && n4 == 0) {
                    if (i_sumfinal == i_final && area1_sumfinal == area1_final && area2_sumfinal == area2_final) {
                        float flen = CalculateFlightLength(VX, vx, VY, vy, VZ, vz);
                        cout << flen << ", " << entryFinal << ", " << entrySumFinal << endl;
                        fileOut->cd(); 
                        outputTree->Fill();
                        break;
                    }
                }
            }
        }
        file->Close();
    }

    fileOut->cd(); 
    // Write output tree to file
    outputTree->Write();
    fileOut->Close();
}