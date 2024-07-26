#include <iostream>

#include "TROOT.h"
#include "TFile.h"
#include "TTree.h"
#include "TBrowser.h"
#include "TH2.h"

using namespace std;

int areaNum = 4;

void ProtonCount()
{
    TFile *Data;

	for (int j = 0; j < 8; j++)
	{
        int protonCnt = 0;
        char dir [128];

		if (j < 7){snprintf(dir, 128, "../../../EPOSSM_v2.1/Linked/RootOut_3Sigma_New/pl0%d1_%02d0.root", j, j+3);}
		else {snprintf(dir, 128, "../../../EPOSSM_v2.1/Linked/RootOut_3Sigma_New/pl071_105.root");}

		cout << dir << endl;

		Data = TFile::Open(dir);

		TTree *ptrkData = (TTree*)Data->Get("US_PTRK");
		
		for (int i = 0; i < ptrkData->GetEntriesFast(); i++)
		{
            ptrkData->GetEntry(i);

            TLeaf *area1 = ptrkData->GetLeaf("area1");

            if (area1->GetValue() == areaNum) protonCnt++;
		}

		cout << "Protons in sub-area " << areaNum << ": " << protonCnt << endl;
    }

    Data->Close();
}