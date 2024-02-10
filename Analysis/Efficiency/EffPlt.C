#include <iostream>
#include <vector>

//EPOS Full Z < 25, Transverse < 2.5 Track Selection
//float MC1trueArr [8] = {12379, 12047, 11865, 11665, 11633, 11605, 11093, 10961};
//float MC1vtxArr [8] = {10389, 9990, 9889, 9681, 9559, 9521, 9018, 8850};
//float MC1pLinkArr1 [8] = {9682, 9189, 9045, 8691, 8512, 8382, 7823, 7484};

//EPOS Full Z < 18, Transverse < 1.8 Track Selection
float MC1trueArr [8] = {12379, 12047, 11865, 11665, 11633, 11605, 11093, 10961};
float MC1vtxArr [8] = {10231, 9820, 9728, 9500, 9392, 9345, 8843, 8704};
float MC1pLinkArr1 [8] = {9541, 9037, 8915, 8538, 8366, 8235, 7687, 7358};

float MC1grVtxArrX[8], MC1grVtxArrY[8], MC1errVtxArrX[8], MC1errVtxArrY[8];
float MC1grPLink1ArrX[8], MC1grPLink1ArrY[8], MC1errPLink1ArrX[8], MC1errPLink1ArrY[8];
float MC1grPLink2ArrX[8], MC1grPLink2ArrY[8], MC1errPLink2ArrX[8], MC1errPLink2ArrY[8];

//Pythia
float MC2trueArr [8] = {2370, 2442, 2341, 2437, 2297, 2338, 2207, 2216};
float MC2vtxArr [8] = {2110, 2144, 2036, 2168, 1964, 2005, 1886, 1893};
float MC2pLinkArr1 [8] = {2001, 1996, 1904, 1979, 1787, 1781, 1639, 1650};

float MC2grVtxArrX[8], MC2grVtxArrY[8], MC2errVtxArrX[8], MC2errVtxArrY[8];
float MC2grPLink1ArrX[8], MC2grPLink1ArrY[8], MC2errPLink1ArrX[8], MC2errPLink1ArrY[8];
float MC2grPLink2ArrX[8], MC2grPLink2ArrY[8], MC2errPLink2ArrX[8], MC2errPLink2ArrY[8];

/*
//Geant4
float MC3trueArr [8] = {1217, 1198, 1223, 1084, 1138, 1141, 1112, 1055};
float MC3vtxArr [8] = {1068, 1051, 1086, 938, 971, 968, 964, 869};
float MC3pLinkArr1 [8] = {994, 963, 968, 863, 853, 858, 817, 735};
*/

//Geant4
float MC3trueArr [8] = {2450, 2441, 2394, 2217, 2306, 2288, 2195, 2128};
float MC3vtxArr [8] = {2141, 2112, 2114, 1918, 1977, 1947, 1880, 1767};
float MC3pLinkArr1 [8] = {2002, 1946, 1920, 1767, 1727, 1726, 1587, 1481};

float MC3grVtxArrX[8], MC3grVtxArrY[8], MC3errVtxArrX[8], MC3errVtxArrY[8];
float MC3grPLink1ArrX[8], MC3grPLink1ArrY[8], MC3errPLink1ArrX[8], MC3errPLink1ArrY[8];
float MC3grPLink2ArrX[8], MC3grPLink2ArrY[8], MC3errPLink2ArrX[8], MC3errPLink2ArrY[8];

float MC1sumVtx = 0, MC1sumPLink1 = 0, MC1sumPLink2 = 0;
float MC2sumVtx = 0, MC2sumPLink1 = 0, MC2sumPLink2 = 0;
float MC3sumVtx = 0, MC3sumPLink1 = 0, MC3sumPLink2 = 0;

float MC1normVtxErr = 0, MC1normPLink1Err = 0, MC1normPLink2Err = 0;

float errCalc(float N0, float N);

void EffPlt()
{
    char  outName[64], outNameStart[64], outNameEnd[64];

    sprintf(outName,"Efficiency.png");
    sprintf(outNameStart,"%s(", outName);
    sprintf(outNameEnd,"%s)", outName);

    for (int i = 0; i < 8; i++)
    {
        MC1grVtxArrX[i] = i+1;
        MC1grVtxArrY[i] = MC1vtxArr[i]/MC1trueArr[i];
        MC1errVtxArrX[i] = 0;
        //MC1errVtxArrY[i] = errCalc(MC1trueArr[i], MC1grVtxArrY[i]);
        MC1errVtxArrY[i] = errCalc(MC1trueArr[i], MC1vtxArr[i]);
        //cout << errVtxArrY[i] << endl;

        MC1grPLink1ArrX[i] = i+1;
        MC1grPLink1ArrY[i] = MC1pLinkArr1[i]/MC1trueArr[i];
        MC1errPLink1ArrX[i] = 0;
        MC1errPLink1ArrY[i] = errCalc(MC1trueArr[i], MC1pLinkArr1[i]);

        MC1grPLink2ArrX[i] = i+1;
        MC1grPLink2ArrY[i] = MC1pLinkArr1[i]/MC1vtxArr[i];
        MC1errPLink2ArrX[i] = 0;
        MC1errPLink2ArrY[i] = errCalc(MC1trueArr[i], MC1pLinkArr1[i]);

        MC1sumVtx += MC1grVtxArrY[i];
        MC1sumPLink1 += MC1grPLink1ArrY[i];
        MC1sumPLink2 += MC1grPLink2ArrY[i];

        MC1normVtxErr += MC1errVtxArrY[i]*MC1errVtxArrY[i];
        MC1normPLink1Err += MC1errPLink1ArrY[i]*MC1errPLink1ArrY[i];
        MC1normPLink2Err += MC1errPLink2ArrY[i]*MC1errPLink2ArrY[i];

        cout << "Vtx: " << MC1grVtxArrY[i]*100 << " ± " << MC1errVtxArrY[i]*100 << ", PLink: " << MC1grPLink2ArrY[i]*100 << " ± " << MC1errPLink2ArrY[i]*100 << ", Total: " << MC1grPLink1ArrY[i]*100 << " ± " << MC1errPLink1ArrY[i]*100 << endl;
    }

    MC1normVtxErr = sqrt(MC1normVtxErr)/8;
    MC1normPLink1Err = sqrt(MC1normPLink1Err)/8;
    MC1normPLink2Err = sqrt(MC1normPLink2Err)/8;

    cout << "Mean -- Vtx: " << (MC1sumVtx/8)*100 << " ± " << MC1normVtxErr*100 << ", PLink: " << (MC1sumPLink2/8)*100 << " ± " << MC1normPLink1Err*100 << ", Total: " << (MC1sumPLink1/8)*100 << " ± " << MC1normPLink2Err*100 << endl;

    for (int i = 0; i < 8; i++)
    {
        MC2grVtxArrX[i] = i+1;
        MC2grVtxArrY[i] = MC2vtxArr[i]/MC2trueArr[i];
        MC2errVtxArrX[i] = 0;
        MC2errVtxArrY[i] = errCalc(MC2trueArr[i], MC2grVtxArrY[i]);
        //cout << errVtxArrY[i] << endl;

        MC2grPLink1ArrX[i] = i+1;
        MC2grPLink1ArrY[i] = MC2pLinkArr1[i]/MC2trueArr[i];
        MC2errPLink1ArrX[i] = 0;
        MC2errPLink1ArrY[i] = errCalc(MC2trueArr[i], MC2grPLink1ArrY[i]);

        MC2grPLink2ArrX[i] = i+1;
        MC2grPLink2ArrY[i] = MC2pLinkArr1[i]/MC2vtxArr[i];
        MC2errPLink2ArrX[i] = 0;
        MC2errPLink2ArrX[i] = errCalc(MC2trueArr[i], MC2grPLink2ArrY[i]);

        MC2sumVtx += MC2grVtxArrY[i];
        MC2sumPLink1 += MC2grPLink1ArrY[i];
        MC2sumPLink2 += MC2grPLink2ArrY[i];
    }

    for (int i = 0; i < 8; i++)
    {
        MC3grVtxArrX[i] = i+1;
        MC3grVtxArrY[i] = MC3vtxArr[i]/MC3trueArr[i];
        MC3errVtxArrX[i] = 0;
        MC3errVtxArrY[i] = errCalc(MC3trueArr[i], MC3grVtxArrY[i]);
        //cout << errVtxArrY[i] << endl;

        MC3grPLink1ArrX[i] = i+1;
        MC3grPLink1ArrY[i] = MC3pLinkArr1[i]/MC3trueArr[i];
        MC3errPLink1ArrX[i] = 0;
        MC3errPLink1ArrY[i] = errCalc(MC3trueArr[i], MC3grPLink1ArrY[i]);

        MC3grPLink2ArrX[i] = i+1;
        MC3grPLink2ArrY[i] = MC3pLinkArr1[i]/MC3vtxArr[i];
        MC3errPLink2ArrX[i] = 0;
        MC3errPLink2ArrX[i] = errCalc(MC3trueArr[i], MC3grPLink2ArrY[i]);

        MC3sumVtx += MC3grVtxArrY[i];
        MC3sumPLink1 += MC3grPLink1ArrY[i];
        MC3sumPLink2 += MC3grPLink2ArrY[i];
    }

    TCanvas *Canvas= new TCanvas("Canvas","Histogram Canvas",20,20,1920,1080);

    TGraphErrors *MC1GraphErVtx = new TGraphErrors(8, MC1grVtxArrX, MC1grVtxArrY, MC1errVtxArrX, MC1errVtxArrY);
    TGraphErrors *MC2GraphErVtx = new TGraphErrors(8, MC2grVtxArrX, MC2grVtxArrY, MC2errVtxArrX, MC2errVtxArrY);
    TGraphErrors *MC3GraphErVtx = new TGraphErrors(8, MC3grVtxArrX, MC3grVtxArrY, MC3errVtxArrX, MC3errVtxArrY);

    gPad->SetGrid(100);
    
    //GraphErVtx->Fit("pol1");

    MC1GraphErVtx->SetMarkerColor(kRed);
    //MC1GraphErVtx->SetMarkerStyle(107);
    MC1GraphErVtx->SetTitle("; Sub-volume; #varepsilon;");
    MC1GraphErVtx->SetMarkerSize(2.0);
    MC1GraphErVtx->SetMarkerStyle(kFullCircle);
    MC1GraphErVtx->SetMinimum(0.7);
    MC1GraphErVtx->SetMaximum(1.0);
    MC1GraphErVtx->Draw("AP");

    MC2GraphErVtx->SetMarkerColor(kGreen);
    //MC2GraphErVtx->SetMarkerStyle(108);
    MC2GraphErVtx->SetTitle("; Sub-volume; #varepsilon;");
    MC2GraphErVtx->SetMarkerSize(2.0);
    MC2GraphErVtx->SetMarkerStyle(kFullCircle);
    MC2GraphErVtx->SetMinimum(0.7);
    MC2GraphErVtx->SetMaximum(1.0);
    //MC2GraphErVtx->Draw("p same");

    MC3GraphErVtx->SetMarkerColor(kBlue);
    //MC3GraphErVtx->SetMarkerStyle(109);
    MC3GraphErVtx->SetTitle("; Sub-volume; #varepsilon;");
    MC3GraphErVtx->SetMarkerSize(2.0);
    MC3GraphErVtx->SetMarkerStyle(kFullCircle);
    MC3GraphErVtx->SetMinimum(0.7);
    MC3GraphErVtx->SetMaximum(1.0);
    //MC3GraphErVtx->Draw("p same");

    /*
    TLegend *legend1 = new TLegend(0.75, 0.85, 0.95, 0.95);

    legend1->AddEntry(MC1GraphErVtx,"EPOS","p");
    legend1->AddEntry(MC2GraphErVtx,"Pythia","p");
    legend1->AddEntry(MC3GraphErVtx,"Geant4","p");
    legend1->Draw();
    */
    Canvas->Print( "EffVtx.png", "png");
    delete Canvas;
    
    Canvas= new TCanvas("Canvas","Histogram Canvas",20,20,1920,1080);

    TGraphErrors *MC1GraphErPLink1 = new TGraphErrors(8, MC1grPLink1ArrX, MC1grPLink1ArrY, MC1errPLink1ArrX, MC1errPLink1ArrY);
    TGraphErrors *MC2GraphErPLink1 = new TGraphErrors(8, MC2grPLink1ArrX, MC2grPLink1ArrY, MC2errPLink1ArrX, MC2errPLink1ArrY);
    TGraphErrors *MC3GraphErPLink1 = new TGraphErrors(8, MC3grPLink1ArrX, MC3grPLink1ArrY, MC3errPLink1ArrX, MC3errPLink1ArrY);

    gPad->SetGrid(100);

    //GraphErPLink1->Fit("pol1");

    MC1GraphErPLink1->SetMarkerColor(kRed);
    //MC1GraphErPLink1->SetMarkerStyle(107);
    MC1GraphErPLink1->SetTitle("; Sub-volume; #varepsilon;");
    MC1GraphErPLink1->SetMarkerSize(2.0);
    MC1GraphErPLink1->SetMarkerStyle(kFullCircle);
    MC1GraphErPLink1->SetMinimum(0.7);
    MC1GraphErPLink1->SetMaximum(1.0);
    MC1GraphErPLink1->Draw("AP");

    MC2GraphErPLink1->SetMarkerColor(kGreen);
    //MC2GraphErPLink1->SetMarkerStyle(108);
    MC2GraphErPLink1->SetTitle("; Sub-volume; #varepsilon;");
    MC2GraphErPLink1->SetMarkerSize(2.0);
    MC2GraphErPLink1->SetMarkerStyle(kFullCircle);
    MC2GraphErPLink1->SetMinimum(0.7);
    MC2GraphErPLink1->SetMaximum(1.0);
    //MC2GraphErPLink1->Draw("p same");

    MC3GraphErPLink1->SetMarkerColor(kBlue);
    //MC3GraphErPLink1->SetMarkerStyle(109);
    MC3GraphErPLink1->SetTitle("; Sub-volume; #varepsilon;");
    MC3GraphErPLink1->SetMarkerSize(2.0);
    MC3GraphErPLink1->SetMarkerStyle(kFullCircle);
    MC3GraphErPLink1->SetMinimum(0.7);
    MC3GraphErPLink1->SetMaximum(1.0);
    //MC3GraphErPLink1->Draw("p same");
    /*
    TLegend *legend2 = new TLegend(0.75, 0.85, 0.95, 0.95);

    legend2->AddEntry(MC1GraphErPLink1,"EPOS","p");
    legend2->AddEntry(MC2GraphErPLink1,"Pythia","p");
    legend2->AddEntry(MC3GraphErPLink1,"Geant4","p");
    legend2->Draw();
    */
    Canvas->Print( "EffPLink1.png", "png");
    delete Canvas;

    Canvas= new TCanvas("Canvas","Histogram Canvas",20,20,1920,1080);
    
    TGraphErrors *MC1GraphErPLink2 = new TGraphErrors(8, MC1grPLink2ArrX, MC1grPLink2ArrY, MC1errPLink2ArrX, MC1errPLink2ArrY);
    TGraphErrors *MC2GraphErPLink2 = new TGraphErrors(8, MC2grPLink2ArrX, MC2grPLink2ArrY, MC2errPLink2ArrX, MC2errPLink2ArrY);
    TGraphErrors *MC3GraphErPLink2 = new TGraphErrors(8, MC3grPLink2ArrX, MC3grPLink2ArrY, MC3errPLink2ArrX, MC3errPLink2ArrY);

    gPad->SetGrid(100);

    //GraphErPLink2->Fit("pol1");

    MC1GraphErPLink2->SetMarkerColor(kRed);
    //MC1GraphErPLink2->SetMarkerStyle(107);
    MC1GraphErPLink2->SetTitle("; Sub-volume; #varepsilon;");
    MC1GraphErPLink2->SetMarkerSize(2.0);
    MC1GraphErPLink2->SetMarkerStyle(kFullCircle);
    MC1GraphErPLink2->SetMinimum(0.7);
    MC1GraphErPLink2->SetMaximum(1.0);
    MC1GraphErPLink2->Draw("ap");

    MC2GraphErPLink2->SetMarkerColor(kGreen);
    //MC2GraphErPLink2->SetMarkerStyle(108);
    MC2GraphErPLink2->SetTitle("; Sub-volume; #varepsilon;");
    MC2GraphErPLink2->SetMarkerSize(2.0);
    MC2GraphErPLink2->SetMarkerStyle(kFullCircle);
    MC2GraphErPLink2->SetMinimum(0.7);
    MC2GraphErPLink2->SetMaximum(1.0);
    //MC2GraphErPLink2->Draw("p same");

    MC3GraphErPLink2->SetMarkerColor(kBlue);
    //MC3GraphErPLink2->SetMarkerStyle(109);
    MC3GraphErPLink2->SetTitle("; Sub-volume; #varepsilon;");
    MC3GraphErPLink2->SetMarkerSize(2.0);
    MC3GraphErPLink2->SetMarkerStyle(kFullCircle);
    MC3GraphErPLink2->SetMinimum(0.7);
    MC3GraphErPLink2->SetMaximum(1.0);
    ///MC3GraphErPLink2->Draw("p same");

    /*
    TLegend *legend3 = new TLegend(0.75, 0.85, 0.95, 0.95);

    legend3->AddEntry(MC1GraphErPLink2,"EPOS","p");
    legend3->AddEntry(MC2GraphErPLink2,"Pythia","p");
    legend3->AddEntry(MC3GraphErPLink2,"Geant4","p");
    legend3->Draw();
    */
    Canvas->Print( "EffPLink2.png", "png");
    delete Canvas;

    cout << "EPOS -- Mean Vertex Efficiency: " << MC1sumVtx/8 << ", Mean ProtonLinking Efficiency: " << MC1sumPLink2/8 << ", Mean Total Efficiency: " << MC1sumPLink1/8 << endl;
    cout << "Pythia -- Mean Vertex Efficiency: " << MC2sumVtx/8 << ", Mean ProtonLinking Efficiency: " << MC2sumPLink2/8 << ", Mean Total Efficiency: " << MC2sumPLink1/8 << endl;
    cout << "Geant4 -- Mean Vertex Efficiency: " << MC3sumVtx/8 << ", Mean ProtonLinking Efficiency: " << MC3sumPLink2/8 << ", Mean Total Efficiency: " << MC3sumPLink1/8 << endl;
}

float errCalc(float N0, float N)
{
    float epsilon = N/N0;
    
    return sqrt((epsilon*(1-epsilon))/N0);
}