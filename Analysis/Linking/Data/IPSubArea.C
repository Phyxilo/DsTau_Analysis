#include <iostream>
#include <vector>

#include "TROOT.h"
#include "TFile.h"
#include "TTree.h"
#include "TBrowser.h"
#include "TH2.h"

using namespace std;

TCanvas *Canvas;

TFile *Data;

const int acceptanceArray[21] = 
{
    29, 30, 31, 32, 33, 34, 35,
    38, 39, 40, 41, 42, 43, 44,
    47, 48, 49, 50, 51, 52, 53
};

float posXMin = 57000, posXMax = 73000;
float posYMin = 57000, posYMax = 73000;

char dir [128];

TH1F *IPDist29V1 = new TH1F("IPDist29V1","IP Distribution Area 29 SV1",100,0,10);
TH1F *IPDist30V1 = new TH1F("IPDist30V1","IP Distribution Area 30 SV1",100,0,10);
TH1F *IPDist31V1 = new TH1F("IPDist31V1","IP Distribution Area 31 SV1",100,0,10);
TH1F *IPDist32V1 = new TH1F("IPDist32V1","IP Distribution Area 32 SV1",100,0,10);
TH1F *IPDist33V1 = new TH1F("IPDist33V1","IP Distribution Area 33 SV1",100,0,10);
TH1F *IPDist34V1 = new TH1F("IPDist34V1","IP Distribution Area 34 SV1",100,0,10);
TH1F *IPDist35V1 = new TH1F("IPDist35V1","IP Distribution Area 35 SV1",100,0,10);
TH1F *IPDist38V1 = new TH1F("IPDist38V1","IP Distribution Area 38 SV1",100,0,10);
TH1F *IPDist39V1 = new TH1F("IPDist39V1","IP Distribution Area 39 SV1",100,0,10);
TH1F *IPDist40V1 = new TH1F("IPDist40V1","IP Distribution Area 40 SV1",100,0,10);
TH1F *IPDist41V1 = new TH1F("IPDist41V1","IP Distribution Area 41 SV1",100,0,10);
TH1F *IPDist42V1 = new TH1F("IPDist42V1","IP Distribution Area 42 SV1",100,0,10);
TH1F *IPDist43V1 = new TH1F("IPDist43V1","IP Distribution Area 43 SV1",100,0,10);
TH1F *IPDist44V1 = new TH1F("IPDist44V1","IP Distribution Area 44 SV1",100,0,10);
TH1F *IPDist47V1 = new TH1F("IPDist47V1","IP Distribution Area 47 SV1",100,0,10);
TH1F *IPDist48V1 = new TH1F("IPDist48V1","IP Distribution Area 48 SV1",100,0,10);
TH1F *IPDist49V1 = new TH1F("IPDist49V1","IP Distribution Area 49 SV1",100,0,10);
TH1F *IPDist50V1 = new TH1F("IPDist50V1","IP Distribution Area 50 SV1",100,0,10);
TH1F *IPDist51V1 = new TH1F("IPDist51V1","IP Distribution Area 51 SV1",100,0,10);
TH1F *IPDist52V1 = new TH1F("IPDist52V1","IP Distribution Area 52 SV1",100,0,10);
TH1F *IPDist53V1 = new TH1F("IPDist53V1","IP Distribution Area 53 SV1",100,0,10);

TH1F *IPDist29V2 = new TH1F("IPDist29V2","IP Distribution Area 29 SV2",100,0,10);
TH1F *IPDist30V2 = new TH1F("IPDist30V2","IP Distribution Area 30 SV2",100,0,10);
TH1F *IPDist31V2 = new TH1F("IPDist31V2","IP Distribution Area 31 SV2",100,0,10);
TH1F *IPDist32V2 = new TH1F("IPDist32V2","IP Distribution Area 32 SV2",100,0,10);
TH1F *IPDist33V2 = new TH1F("IPDist33V2","IP Distribution Area 33 SV2",100,0,10);
TH1F *IPDist34V2 = new TH1F("IPDist34V2","IP Distribution Area 34 SV2",100,0,10);
TH1F *IPDist35V2 = new TH1F("IPDist35V2","IP Distribution Area 35 SV2",100,0,10);
TH1F *IPDist38V2 = new TH1F("IPDist38V2","IP Distribution Area 38 SV2",100,0,10);
TH1F *IPDist39V2 = new TH1F("IPDist39V2","IP Distribution Area 39 SV2",100,0,10);
TH1F *IPDist40V2 = new TH1F("IPDist40V2","IP Distribution Area 40 SV2",100,0,10);
TH1F *IPDist41V2 = new TH1F("IPDist41V2","IP Distribution Area 41 SV2",100,0,10);
TH1F *IPDist42V2 = new TH1F("IPDist42V2","IP Distribution Area 42 SV2",100,0,10);
TH1F *IPDist43V2 = new TH1F("IPDist43V2","IP Distribution Area 43 SV2",100,0,10);
TH1F *IPDist44V2 = new TH1F("IPDist44V2","IP Distribution Area 44 SV2",100,0,10);
TH1F *IPDist47V2 = new TH1F("IPDist47V2","IP Distribution Area 47 SV2",100,0,10);
TH1F *IPDist48V2 = new TH1F("IPDist48V2","IP Distribution Area 48 SV2",100,0,10);
TH1F *IPDist49V2 = new TH1F("IPDist49V2","IP Distribution Area 49 SV2",100,0,10);
TH1F *IPDist50V2 = new TH1F("IPDist50V2","IP Distribution Area 50 SV2",100,0,10);
TH1F *IPDist51V2 = new TH1F("IPDist51V2","IP Distribution Area 51 SV2",100,0,10);
TH1F *IPDist52V2 = new TH1F("IPDist52V2","IP Distribution Area 52 SV2",100,0,10);
TH1F *IPDist53V2 = new TH1F("IPDist53V2","IP Distribution Area 53 SV2",100,0,10);

TH1F *IPDist29V3 = new TH1F("IPDist29V3","IP Distribution Area 29 SV3",100,0,10);
TH1F *IPDist30V3 = new TH1F("IPDist30V3","IP Distribution Area 30 SV3",100,0,10);
TH1F *IPDist31V3 = new TH1F("IPDist31V3","IP Distribution Area 31 SV3",100,0,10);
TH1F *IPDist32V3 = new TH1F("IPDist32V3","IP Distribution Area 32 SV3",100,0,10);
TH1F *IPDist33V3 = new TH1F("IPDist33V3","IP Distribution Area 33 SV3",100,0,10);
TH1F *IPDist34V3 = new TH1F("IPDist34V3","IP Distribution Area 34 SV3",100,0,10);
TH1F *IPDist35V3 = new TH1F("IPDist35V3","IP Distribution Area 35 SV3",100,0,10);
TH1F *IPDist38V3 = new TH1F("IPDist38V3","IP Distribution Area 38 SV3",100,0,10);
TH1F *IPDist39V3 = new TH1F("IPDist39V3","IP Distribution Area 39 SV3",100,0,10);
TH1F *IPDist40V3 = new TH1F("IPDist40V3","IP Distribution Area 40 SV3",100,0,10);
TH1F *IPDist41V3 = new TH1F("IPDist41V3","IP Distribution Area 41 SV3",100,0,10);
TH1F *IPDist42V3 = new TH1F("IPDist42V3","IP Distribution Area 42 SV3",100,0,10);
TH1F *IPDist43V3 = new TH1F("IPDist43V3","IP Distribution Area 43 SV3",100,0,10);
TH1F *IPDist44V3 = new TH1F("IPDist44V3","IP Distribution Area 44 SV3",100,0,10);
TH1F *IPDist47V3 = new TH1F("IPDist47V3","IP Distribution Area 47 SV3",100,0,10);
TH1F *IPDist48V3 = new TH1F("IPDist48V3","IP Distribution Area 48 SV3",100,0,10);
TH1F *IPDist49V3 = new TH1F("IPDist49V3","IP Distribution Area 49 SV3",100,0,10);
TH1F *IPDist50V3 = new TH1F("IPDist50V3","IP Distribution Area 50 SV3",100,0,10);
TH1F *IPDist51V3 = new TH1F("IPDist51V3","IP Distribution Area 51 SV3",100,0,10);
TH1F *IPDist52V3 = new TH1F("IPDist52V3","IP Distribution Area 52 SV3",100,0,10);
TH1F *IPDist53V3 = new TH1F("IPDist53V3","IP Distribution Area 53 SV3",100,0,10);

TH1F *IPDist29V4 = new TH1F("IPDist29V4","IP Distribution Area 29 SV4",100,0,10);
TH1F *IPDist30V4 = new TH1F("IPDist30V4","IP Distribution Area 30 SV4",100,0,10);
TH1F *IPDist31V4 = new TH1F("IPDist31V4","IP Distribution Area 31 SV4",100,0,10);
TH1F *IPDist32V4 = new TH1F("IPDist32V4","IP Distribution Area 32 SV4",100,0,10);
TH1F *IPDist33V4 = new TH1F("IPDist33V4","IP Distribution Area 33 SV4",100,0,10);
TH1F *IPDist34V4 = new TH1F("IPDist34V4","IP Distribution Area 34 SV4",100,0,10);
TH1F *IPDist35V4 = new TH1F("IPDist35V4","IP Distribution Area 35 SV4",100,0,10);
TH1F *IPDist38V4 = new TH1F("IPDist38V4","IP Distribution Area 38 SV4",100,0,10);
TH1F *IPDist39V4 = new TH1F("IPDist39V4","IP Distribution Area 39 SV4",100,0,10);
TH1F *IPDist40V4 = new TH1F("IPDist40V4","IP Distribution Area 40 SV4",100,0,10);
TH1F *IPDist41V4 = new TH1F("IPDist41V4","IP Distribution Area 41 SV4",100,0,10);
TH1F *IPDist42V4 = new TH1F("IPDist42V4","IP Distribution Area 42 SV4",100,0,10);
TH1F *IPDist43V4 = new TH1F("IPDist43V4","IP Distribution Area 43 SV4",100,0,10);
TH1F *IPDist44V4 = new TH1F("IPDist44V4","IP Distribution Area 44 SV4",100,0,10);
TH1F *IPDist47V4 = new TH1F("IPDist47V4","IP Distribution Area 47 SV4",100,0,10);
TH1F *IPDist48V4 = new TH1F("IPDist48V4","IP Distribution Area 48 SV4",100,0,10);
TH1F *IPDist49V4 = new TH1F("IPDist49V4","IP Distribution Area 49 SV4",100,0,10);
TH1F *IPDist50V4 = new TH1F("IPDist50V4","IP Distribution Area 50 SV4",100,0,10);
TH1F *IPDist51V4 = new TH1F("IPDist51V4","IP Distribution Area 51 SV4",100,0,10);
TH1F *IPDist52V4 = new TH1F("IPDist52V4","IP Distribution Area 52 SV4",100,0,10);
TH1F *IPDist53V4 = new TH1F("IPDist53V4","IP Distribution Area 53 SV4",100,0,10);

TH1F *IPDist29V5 = new TH1F("IPDist29V5","IP Distribution Area 29 SV5",100,0,10);
TH1F *IPDist30V5 = new TH1F("IPDist30V5","IP Distribution Area 30 SV5",100,0,10);
TH1F *IPDist31V5 = new TH1F("IPDist31V5","IP Distribution Area 31 SV5",100,0,10);
TH1F *IPDist32V5 = new TH1F("IPDist32V5","IP Distribution Area 32 SV5",100,0,10);
TH1F *IPDist33V5 = new TH1F("IPDist33V5","IP Distribution Area 33 SV5",100,0,10);
TH1F *IPDist34V5 = new TH1F("IPDist34V5","IP Distribution Area 34 SV5",100,0,10);
TH1F *IPDist35V5 = new TH1F("IPDist35V5","IP Distribution Area 35 SV5",100,0,10);
TH1F *IPDist38V5 = new TH1F("IPDist38V5","IP Distribution Area 38 SV5",100,0,10);
TH1F *IPDist39V5 = new TH1F("IPDist39V5","IP Distribution Area 39 SV5",100,0,10);
TH1F *IPDist40V5 = new TH1F("IPDist40V5","IP Distribution Area 40 SV5",100,0,10);
TH1F *IPDist41V5 = new TH1F("IPDist41V5","IP Distribution Area 41 SV5",100,0,10);
TH1F *IPDist42V5 = new TH1F("IPDist42V5","IP Distribution Area 42 SV5",100,0,10);
TH1F *IPDist43V5 = new TH1F("IPDist43V5","IP Distribution Area 43 SV5",100,0,10);
TH1F *IPDist44V5 = new TH1F("IPDist44V5","IP Distribution Area 44 SV5",100,0,10);
TH1F *IPDist47V5 = new TH1F("IPDist47V5","IP Distribution Area 47 SV5",100,0,10);
TH1F *IPDist48V5 = new TH1F("IPDist48V5","IP Distribution Area 48 SV5",100,0,10);
TH1F *IPDist49V5 = new TH1F("IPDist49V5","IP Distribution Area 49 SV5",100,0,10);
TH1F *IPDist50V5 = new TH1F("IPDist50V5","IP Distribution Area 50 SV5",100,0,10);
TH1F *IPDist51V5 = new TH1F("IPDist51V5","IP Distribution Area 51 SV5",100,0,10);
TH1F *IPDist52V5 = new TH1F("IPDist52V5","IP Distribution Area 52 SV5",100,0,10);
TH1F *IPDist53V5 = new TH1F("IPDist53V5","IP Distribution Area 53 SV5",100,0,10);

TH1F *IPDist29V6 = new TH1F("IPDist29V6","IP Distribution Area 29 SV6",100,0,10);
TH1F *IPDist30V6 = new TH1F("IPDist30V6","IP Distribution Area 30 SV6",100,0,10);
TH1F *IPDist31V6 = new TH1F("IPDist31V6","IP Distribution Area 31 SV6",100,0,10);
TH1F *IPDist32V6 = new TH1F("IPDist32V6","IP Distribution Area 32 SV6",100,0,10);
TH1F *IPDist33V6 = new TH1F("IPDist33V6","IP Distribution Area 33 SV6",100,0,10);
TH1F *IPDist34V6 = new TH1F("IPDist34V6","IP Distribution Area 34 SV6",100,0,10);
TH1F *IPDist35V6 = new TH1F("IPDist35V6","IP Distribution Area 35 SV6",100,0,10);
TH1F *IPDist38V6 = new TH1F("IPDist38V6","IP Distribution Area 38 SV6",100,0,10);
TH1F *IPDist39V6 = new TH1F("IPDist39V6","IP Distribution Area 39 SV6",100,0,10);
TH1F *IPDist40V6 = new TH1F("IPDist40V6","IP Distribution Area 40 SV6",100,0,10);
TH1F *IPDist41V6 = new TH1F("IPDist41V6","IP Distribution Area 41 SV6",100,0,10);
TH1F *IPDist42V6 = new TH1F("IPDist42V6","IP Distribution Area 42 SV6",100,0,10);
TH1F *IPDist43V6 = new TH1F("IPDist43V6","IP Distribution Area 43 SV6",100,0,10);
TH1F *IPDist44V6 = new TH1F("IPDist44V6","IP Distribution Area 44 SV6",100,0,10);
TH1F *IPDist47V6 = new TH1F("IPDist47V6","IP Distribution Area 47 SV6",100,0,10);
TH1F *IPDist48V6 = new TH1F("IPDist48V6","IP Distribution Area 48 SV6",100,0,10);
TH1F *IPDist49V6 = new TH1F("IPDist49V6","IP Distribution Area 49 SV6",100,0,10);
TH1F *IPDist50V6 = new TH1F("IPDist50V6","IP Distribution Area 50 SV6",100,0,10);
TH1F *IPDist51V6 = new TH1F("IPDist51V6","IP Distribution Area 51 SV6",100,0,10);
TH1F *IPDist52V6 = new TH1F("IPDist52V6","IP Distribution Area 52 SV6",100,0,10);
TH1F *IPDist53V6 = new TH1F("IPDist53V6","IP Distribution Area 53 SV6",100,0,10);

TH1F *IPDist29V7 = new TH1F("IPDist29V7","IP Distribution Area 29 SV7",100,0,10);
TH1F *IPDist30V7 = new TH1F("IPDist30V7","IP Distribution Area 30 SV7",100,0,10);
TH1F *IPDist31V7 = new TH1F("IPDist31V7","IP Distribution Area 31 SV7",100,0,10);
TH1F *IPDist32V7 = new TH1F("IPDist32V7","IP Distribution Area 32 SV7",100,0,10);
TH1F *IPDist33V7 = new TH1F("IPDist33V7","IP Distribution Area 33 SV7",100,0,10);
TH1F *IPDist34V7 = new TH1F("IPDist34V7","IP Distribution Area 34 SV7",100,0,10);
TH1F *IPDist35V7 = new TH1F("IPDist35V7","IP Distribution Area 35 SV7",100,0,10);
TH1F *IPDist38V7 = new TH1F("IPDist38V7","IP Distribution Area 38 SV7",100,0,10);
TH1F *IPDist39V7 = new TH1F("IPDist39V7","IP Distribution Area 39 SV7",100,0,10);
TH1F *IPDist40V7 = new TH1F("IPDist40V7","IP Distribution Area 40 SV7",100,0,10);
TH1F *IPDist41V7 = new TH1F("IPDist41V7","IP Distribution Area 41 SV7",100,0,10);
TH1F *IPDist42V7 = new TH1F("IPDist42V7","IP Distribution Area 42 SV7",100,0,10);
TH1F *IPDist43V7 = new TH1F("IPDist43V7","IP Distribution Area 43 SV7",100,0,10);
TH1F *IPDist44V7 = new TH1F("IPDist44V7","IP Distribution Area 44 SV7",100,0,10);
TH1F *IPDist47V7 = new TH1F("IPDist47V7","IP Distribution Area 47 SV7",100,0,10);
TH1F *IPDist48V7 = new TH1F("IPDist48V7","IP Distribution Area 48 SV7",100,0,10);
TH1F *IPDist49V7 = new TH1F("IPDist49V7","IP Distribution Area 49 SV7",100,0,10);
TH1F *IPDist50V7 = new TH1F("IPDist50V7","IP Distribution Area 50 SV7",100,0,10);
TH1F *IPDist51V7 = new TH1F("IPDist51V7","IP Distribution Area 51 SV7",100,0,10);
TH1F *IPDist52V7 = new TH1F("IPDist52V7","IP Distribution Area 52 SV7",100,0,10);
TH1F *IPDist53V7 = new TH1F("IPDist53V7","IP Distribution Area 53 SV7",100,0,10);

TH1F *IPDist29V8 = new TH1F("IPDist29V8","IP Distribution Area 29 SV8",100,0,10);
TH1F *IPDist30V8 = new TH1F("IPDist30V8","IP Distribution Area 30 SV8",100,0,10);
TH1F *IPDist31V8 = new TH1F("IPDist31V8","IP Distribution Area 31 SV8",100,0,10);
TH1F *IPDist32V8 = new TH1F("IPDist32V8","IP Distribution Area 32 SV8",100,0,10);
TH1F *IPDist33V8 = new TH1F("IPDist33V8","IP Distribution Area 33 SV8",100,0,10);
TH1F *IPDist34V8 = new TH1F("IPDist34V8","IP Distribution Area 34 SV8",100,0,10);
TH1F *IPDist35V8 = new TH1F("IPDist35V8","IP Distribution Area 35 SV8",100,0,10);
TH1F *IPDist38V8 = new TH1F("IPDist38V8","IP Distribution Area 38 SV8",100,0,10);
TH1F *IPDist39V8 = new TH1F("IPDist39V8","IP Distribution Area 39 SV8",100,0,10);
TH1F *IPDist40V8 = new TH1F("IPDist40V8","IP Distribution Area 40 SV8",100,0,10);
TH1F *IPDist41V8 = new TH1F("IPDist41V8","IP Distribution Area 41 SV8",100,0,10);
TH1F *IPDist42V8 = new TH1F("IPDist42V8","IP Distribution Area 42 SV8",100,0,10);
TH1F *IPDist43V8 = new TH1F("IPDist43V8","IP Distribution Area 43 SV8",100,0,10);
TH1F *IPDist44V8 = new TH1F("IPDist44V8","IP Distribution Area 44 SV8",100,0,10);
TH1F *IPDist47V8 = new TH1F("IPDist47V8","IP Distribution Area 47 SV8",100,0,10);
TH1F *IPDist48V8 = new TH1F("IPDist48V8","IP Distribution Area 48 SV8",100,0,10);
TH1F *IPDist49V8 = new TH1F("IPDist49V8","IP Distribution Area 49 SV8",100,0,10);
TH1F *IPDist50V8 = new TH1F("IPDist50V8","IP Distribution Area 50 SV8",100,0,10);
TH1F *IPDist51V8 = new TH1F("IPDist51V8","IP Distribution Area 51 SV8",100,0,10);
TH1F *IPDist52V8 = new TH1F("IPDist52V8","IP Distribution Area 52 SV8",100,0,10);
TH1F *IPDist53V8 = new TH1F("IPDist53V8","IP Distribution Area 53 SV8",100,0,10);

TH1F *HistArr[8][21] = 
{
    {
        IPDist29V1, IPDist30V1, IPDist31V1, IPDist32V1, IPDist33V1, IPDist34V1, IPDist35V1,
        IPDist38V1, IPDist39V1, IPDist40V1, IPDist41V1, IPDist42V1, IPDist43V1, IPDist44V1,
        IPDist47V1, IPDist48V1, IPDist49V1, IPDist50V1, IPDist51V1, IPDist52V1, IPDist53V1
    },
    
    {
        IPDist29V2, IPDist30V2, IPDist31V2, IPDist32V2, IPDist33V2, IPDist34V2, IPDist35V2,
        IPDist38V2, IPDist39V2, IPDist40V2, IPDist41V2, IPDist42V2, IPDist43V2, IPDist44V2,
        IPDist47V2, IPDist48V2, IPDist49V2, IPDist50V2, IPDist51V2, IPDist52V2, IPDist53V2
    },

    {
        IPDist29V3, IPDist30V3, IPDist31V3, IPDist32V3, IPDist33V3, IPDist34V3, IPDist35V3,
        IPDist38V3, IPDist39V3, IPDist40V3, IPDist41V3, IPDist42V3, IPDist43V3, IPDist44V3,
        IPDist47V3, IPDist48V3, IPDist49V3, IPDist50V3, IPDist51V3, IPDist52V3, IPDist53V3
    },

    {
        IPDist29V4, IPDist30V4, IPDist31V4, IPDist32V4, IPDist33V4, IPDist34V4, IPDist35V4,
        IPDist38V4, IPDist39V4, IPDist40V4, IPDist41V4, IPDist42V4, IPDist43V4, IPDist44V4,
        IPDist47V4, IPDist48V4, IPDist49V4, IPDist50V4, IPDist51V4, IPDist52V4, IPDist53V4
    },

    {
        IPDist29V5, IPDist30V5, IPDist31V5, IPDist32V5, IPDist33V5, IPDist34V5, IPDist35V5,
        IPDist38V5, IPDist39V5, IPDist40V5, IPDist41V5, IPDist42V5, IPDist43V5, IPDist44V5,
        IPDist47V5, IPDist48V5, IPDist49V5, IPDist50V5, IPDist51V5, IPDist52V5, IPDist53V5
    },

    {
        IPDist29V6, IPDist30V6, IPDist31V6, IPDist32V6, IPDist33V6, IPDist34V6, IPDist35V6,
        IPDist38V6, IPDist39V6, IPDist40V6, IPDist41V6, IPDist42V6, IPDist43V6, IPDist44V6,
        IPDist47V6, IPDist48V6, IPDist49V6, IPDist50V6, IPDist51V6, IPDist52V6, IPDist53V6
    },

    {
        IPDist29V7, IPDist30V7, IPDist31V7, IPDist32V7, IPDist33V7, IPDist34V7, IPDist35V7,
        IPDist38V7, IPDist39V7, IPDist40V7, IPDist41V7, IPDist42V7, IPDist43V7, IPDist44V7,
        IPDist47V7, IPDist48V7, IPDist49V7, IPDist50V7, IPDist51V7, IPDist52V7, IPDist53V7
    },

    {
        IPDist29V8, IPDist30V8, IPDist31V8, IPDist32V8, IPDist33V8, IPDist34V8, IPDist35V8,
        IPDist38V8, IPDist39V8, IPDist40V8, IPDist41V8, IPDist42V8, IPDist43V8, IPDist44V8,
        IPDist47V8, IPDist48V8, IPDist49V8, IPDist50V8, IPDist51V8, IPDist52V8, IPDist53V8
    },
};

void IPSubArea()
{
    //Canvas->SetWindowSize(1920, 1080);
    //Canvas->SetCanvasSize(192*6, 108*6);

    char  outName[64], outNameStart[64], outNameEnd[64];

    int maxSubArea = 21;

    snprintf(outName, 64, "IPSubArea.pdf");
    snprintf(outNameStart, 64, "%s(", outName);
    snprintf(outNameEnd, 64, "%s)", outName);

    for (int k = 0; k < maxSubArea; k++)
    {
        int subA = acceptanceArray[k];

        for (int j = 0; j < 8; j++)
        {
            int IntPar = 0, TotalPar = 0;

            snprintf(dir, 128, "../../../Data_v20220912/PD05/Linked/RootOut_3Sigma/p0%d6.root", j);

            Data = TFile::Open(dir);
            
            TTree *trkData = (TTree*)Data->Get("TRK");
            TTree *vtxData = (TTree*)Data->Get("VTX");

            for (int i = 0; i < trkData->GetEntriesFast(); i++)
            {
                trkData->GetEntry(i);

                TLeaf *ip = trkData->GetLeaf("ip_to_1ry_using_1stseg");
                TLeaf *vID = trkData->GetLeaf("vID");
                TLeaf *iMed = trkData->GetLeaf("intMed");
                TLeaf *area1 = trkData->GetLeaf("area1");

                vtxData->GetEntry(vID->GetValue());

                TLeaf *iType = vtxData->GetLeaf("intType");

                float IP = ip->GetValue();

                int intMed = iMed->GetValue();
                int subArea = area1->GetValue();
                int intType = iType->GetValue();

                if (subArea == subA && intMed == 1)
                {
                    HistArr[j][k]->Fill(IP);
                }

                if (area1->GetValue() > subA) break;

            }
            
        }
    }

    /*
    for (auto& arr : subAreaArr) 
    {
        for (auto& el : arr)
            cout << el << ' ';
    }
    */

    Canvas = new TCanvas("Canvas","Graph Canvas",20,20,1920,1080);

    for (int k = 0; k < maxSubArea; k++)
    {
        //TLegend *legend = new TLegend(0.80, 0.05, 0.95, 0.30);
        
        for (int j = 0; j < 8; j++)
        {
            if (j == 0){HistArr[j][k]->Draw();}
            else {HistArr[j][k]->Draw("SAMES");}

            if (j != 4) HistArr[j][k]->SetLineColor(j+1);
            else HistArr[j][k]->SetLineColor(41);
        }
        /*
        legend->AddEntry(HistArr[0][k],"SubVol 1","f");
        legend->AddEntry(HistArr[1][k],"SubVol 2","f");
        legend->AddEntry(HistArr[2][k],"SubVol 3","f");
        legend->AddEntry(HistArr[3][k],"SubVol 4","f");
        legend->AddEntry(HistArr[4][k],"SubVol 5","f");
        legend->AddEntry(HistArr[5][k],"SubVol 6","f");
        legend->AddEntry(HistArr[6][k],"SubVol 7","f");
        legend->AddEntry(HistArr[7][k],"SubVol 8","f");
        legend->Draw();
        */

        //gStyle->SetOptStat(110);

        Canvas->Modified(); Canvas->Update();
        TPaveStats *StatBox1 = (TPaveStats*)Canvas->GetPrimitive("stats");
        StatBox1->SetName("SubVol 1");
        StatBox1->SetY1NDC(0.9);
        StatBox1->SetY2NDC(0.8);
        StatBox1->SetTextColor(1);
        StatBox1->Draw();

        TPaveStats *StatBox2 = (TPaveStats*)Canvas->GetPrimitive("stats");
        StatBox2->SetName("SubVol 2");
        StatBox2->SetY1NDC(0.8);
        StatBox2->SetY2NDC(0.7);
        StatBox2->SetTextColor(2);
        StatBox2->Draw();

        TPaveStats *StatBox3 = (TPaveStats*)Canvas->GetPrimitive("stats");
        StatBox3->SetName("SubVol 3");
        StatBox3->SetY1NDC(0.7);
        StatBox3->SetY2NDC(0.6);
        StatBox3->SetTextColor(3);
        StatBox3->Draw();

        TPaveStats *StatBox4 = (TPaveStats*)Canvas->GetPrimitive("stats");
        StatBox4->SetName("SubVol 4");
        StatBox4->SetY1NDC(0.6);
        StatBox4->SetY2NDC(0.5);
        StatBox4->SetTextColor(4);
        StatBox4->Draw();

        TPaveStats *StatBox5 = (TPaveStats*)Canvas->GetPrimitive("stats");
        StatBox5->SetName("SubVol 5");
        StatBox5->SetY1NDC(0.5);
        StatBox5->SetY2NDC(0.4);
        StatBox5->SetTextColor(41);
        StatBox5->Draw();

        TPaveStats *StatBox6 = (TPaveStats*)Canvas->GetPrimitive("stats");
        StatBox6->SetName("SubVol 6");
        StatBox6->SetY1NDC(0.4);
        StatBox6->SetY2NDC(0.3);
        StatBox6->SetTextColor(6);
        StatBox6->Draw();

        TPaveStats *StatBox7 = (TPaveStats*)Canvas->GetPrimitive("stats");
        StatBox7->SetName("SubVol 7");
        StatBox7->SetY1NDC(0.3);
        StatBox7->SetY2NDC(0.2);
        StatBox7->SetTextColor(7);
        StatBox7->Draw();

        TPaveStats *StatBox8 = (TPaveStats*)Canvas->GetPrimitive("stats");
        StatBox8->SetName("SubVol 8");
        StatBox8->SetY1NDC(0.2);
        StatBox8->SetY2NDC(0.1);
        StatBox8->SetTextColor(8);
        StatBox8->Draw();
        
        if (k == 0) {Canvas->Print(outNameStart,"pdf");}
        else if (k == maxSubArea-1) {Canvas->Print(outNameEnd,"pdf");}
        else {Canvas->Print(outName,"pdf");}
    }
}