#include <TFile.h>
#include <TTree.h>
#include <iostream>

void ReadRootBranch() 
{
    const char* filePath = "../../PythiaCharmSM_v2.1/Linked/RootOut/pl001_030.root";

    // Open the ROOT file
    TFile* file = TFile::Open(filePath);
    if (!file || file->IsZombie()) {
        std::cerr << "Error: Could not open file " << filePath << std::endl;
        return;
    }

    // Get the tree named "DsFinal"
    TTree* tree = nullptr;
    file->GetObject("DsFinal", tree);
    if (!tree) {
        std::cerr << "Error: Tree 'DsFinal' not found in file " << filePath << std::endl;
        file->Close();
        return;
    }

    // Set up a variable to hold the branch data
    Int_t parent_pdgID;
    tree->SetBranchAddress("parent_pdgID", &parent_pdgID);

    // Loop over all entries in the tree and print the parent_pdgID
    Long64_t nEntries = tree->GetEntries();
    for (Long64_t i = 0; i < nEntries; ++i) {
        tree->GetEntry(i);
        if (i == -421)
          std::cout << "Entry " << i << ": parent_pdgID = " << parent_pdgID << std::endl;
    }

    // Clean up
    file->Close();
    delete file;
}