#include <iostream>

using namespace std;

TCanvas *Canvas= new TCanvas("Canvas","Histogram Canvas",20,20,1920,1080);

char dir [128];

//Old
/*
float totalSeg [7] = 
{
    63910,
    59856,
    56764,
    53746,
    50556,
    47152,
    43752
};

float nonProtonSeg [7] = 
{
    565,
    1120,
    1508,
    1875,
    2230,
    2435,
    2675
};
*/

//3Sigma
/*
float totalSeg [7] = 
{
    44969,
    42413,
    39815,
    37425,
    34789,
    32084,
    29806
};

float nonProtonSeg [7] = 
{
    88,
    173,
    226,
    258,
    306,
    319,
    319
};
*/
/*
//2Sigma
float totalSeg [7] = 
{
    34960,
    32742,
    30783,
    28747,
    26531,
    24903,
    23184
};

float nonProtonSeg [7] = 
{
    59,
    87,
    102,
    101,
    138,
    128,
    114
};
*/
/*
//4Sigma
float totalSeg [7] = 
{
    46304,
    43760,
    41145,
    38798,
    36068,
    33361,
    30974
};

float nonProtonSeg [7] = 
{
    140,
    294,
    399,
    473,
    535,
    581,
    586
};
*/
//3Sigma Full
float totalSeg [7] = 
{
    47524+48371+47889+47983+48588+47452+48095+48102+47650+47720+47903+47833+48100+48073+47698,
    46568+47256+46901+47020+47596+46997+47559+47276+46837+46751+47187+47054+47244+47461+46871,
    45517+45861+45984+46064+46701+45986+46534+46024+45932+46014+46258+45794+46229+46133+45823,
    44502+45257+44978+45036+45589+44420+45502+44987+45196+44782+45104+44570+45028+45393+44869,
    43370+43958+43834+43889+44202+43587+44205+43769+43608+43818+44133+43614+43964+44424+43734,
    42156+42786+42551+42855+43105+42805+42892+42820+42973+43075+42518+42094+41533+42443+42442,
    41314+41282+41149+41449+41702+41196+41458+41834+41573+41294+41136+41142+41487+41137+41628
};

float nonProtonSeg [7] = 
{
    92+105+138+88+103+98+114+174+148+123+145+101+155+155+137,
    215+198+224+159+180+133+264+247+178+214+228+207+235+255+191,
    300+378+303+230+284+207+378+303+345+259+299+316+298+329+350,
    394+347+454+352+397+356+452+354+332+376+387+385+393+478+400,
    500+350+478+419+494+472+522+425+454+409+444+512+403+516+480,
    516+434+539+529+573+415+604+509+409+489+539+521+574+529+535,
    640+664+597+561+620+564+633+548+426+517+602+505+571+550+506
};

float protonPer [7], wArr [7];
float sumProtonPer = 0;

void Purity()
{
    char outName[64] = "Purity.png";

    float dataSize = 0;

    for (int i = 0; i < 7; i++)
    {
        protonPer[i] = (totalSeg[i] - nonProtonSeg[i])/totalSeg[i];
        wArr[i] = i+1;
        
        sumProtonPer += protonPer[i];
    }
    
    Canvas->SetGrid();

    TGraph *PurGraph = new TGraph (7, wArr, protonPer);

    PurGraph->Draw("AP");
    PurGraph->SetTitle("");
    PurGraph->GetXaxis()->SetTitle("Sub-volume");
    PurGraph->GetYaxis()->SetTitle("Percentage");
    PurGraph->SetMarkerSize(1.5);
    PurGraph->SetMarkerStyle(kFullCircle);

    PurGraph->GetXaxis()->SetLimits(0,8);

    PurGraph->SetMaximum(1);
    PurGraph->SetMinimum(0.9);

    cout << "Mean: " << sumProtonPer/7 << endl;
    
    Canvas->Print(outName,"png");
    delete Canvas;
}