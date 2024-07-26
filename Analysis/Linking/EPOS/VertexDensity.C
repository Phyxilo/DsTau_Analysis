#include <iostream>
#include <vector>
#include <cmath>

#include "TROOT.h"
#include "TFile.h"
#include "TTree.h"
#include "TBrowser.h"
#include "TH2.h"

using namespace std;

const int subAreaNum = 5;
const int tungstenNum = 8;

float calculateMean(float (*array)[8], int rows, int col) {
    float sum = 0.0;
    for (int i = 0; i < rows; i++) {
        sum += array[i][col];
    }
    return sum / rows;
}

float calculateStdDev(float (*array)[8], int rows, int col, float mean) {
    float sum = 0.0;
    for (int i = 0; i < rows; i++) {
        sum += (array[i][col] - mean) * (array[i][col] - mean);
    }
    return sqrt(sum / rows);
}

double* DataEndPoints(TTree *data);
double DataMean(TTree *data);
void CreateTexTable(float arr[subAreaNum][tungstenNum], const char* name);
void CreateTexTableMulti(float vtxArr[subAreaNum][tungstenNum], float priArr[subAreaNum][tungstenNum], float proArr[subAreaNum][tungstenNum], const char* name);

TCanvas *Canvas;
TFile *Data;

float vtxIntArr [subAreaNum][tungstenNum];
float priIntArr [subAreaNum][tungstenNum];
float proArr [subAreaNum][tungstenNum];

float migCut = 18;

float posXMin = 57000, posXMax = 73000;
float posYMin = 57000, posYMax = 73000;

char dir [128];

float area = 2.25; //Transverse area in cm^2

void VertexDensity()
{
    for (int k = 0; k <= subAreaNum; k++)
    {
        int firstIntPar = 0, firstTotPar = 0, firstTotProtons = 0;

        for (int j = 0; j < 8; j++)
        {
            int IntPar = 0, TotalPar = 0;

            if (j < 7){snprintf(dir, 128, "../../../EPOSSM_v2.1/Linked/RootOut_3Sigma_Old/pl0%d1_%02d0.root", j, j+3);}
            else {snprintf(dir, 128, "../../../EPOSSM_v2.1/Linked/RootOut_3Sigma_Old/pl071_105.root");}

            //cout << dir << endl;

            //Data = TFile::Open("../Root/Geant4_p006.root");
            Data = TFile::Open(dir);
            
            TTree *parData = (TTree*)Data->Get("PAR");
            TTree *vtxData = (TTree*)Data->Get("VTX");
            TTree *ptrkData = (TTree*)Data->Get("US_PTRK");

            double *endArr = DataEndPoints(vtxData);
            double mean = DataMean(vtxData);

            for (int i = 0; i < parData->GetEntriesFast(); i++)
            {
                parData->GetEntry(i);
                vtxData->GetEntry(i);

                TLeaf *vx = parData->GetLeaf("vx");
                TLeaf *vy = parData->GetLeaf("vy");
                TLeaf *vz = parData->GetLeaf("vz");
                TLeaf *plt = parData->GetLeaf("plt_of_1seg");
                TLeaf *flagp = parData->GetLeaf("flagp");
                TLeaf *plmin = parData->GetLeaf("pl_up1ry_plmin");
                TLeaf *plmax = parData->GetLeaf("pl_up1ry_plmax");

                TLeaf *pNum = vtxData->GetLeaf("n_1ry_parent_dmin_cut");
                TLeaf *area1 = vtxData->GetLeaf("area1");
                TLeaf *flagw = vtxData->GetLeaf("flagw");

                float VX = vx->GetValue();
                float VY = vy->GetValue();
                int Plt = plt->GetValue();
                int fp = flagp->GetValue();

                if (area1->GetValue() == k && (flagw->GetValue() == 1))
                {
                    if (vz->GetValue() > mean - (250-migCut) && vz->GetValue() < mean + (250-migCut))
                    {
                        if (fp >= 1)
                        {
                            IntPar++;
                        }

                        TotalPar++;
                    }
                }
                if (area1->GetValue() > k) break;

            }
            int totProtons = 0;

            for (int i = 0; i < ptrkData->GetEntriesFast(); i++)
            {
                ptrkData->GetEntry(i);

                TLeaf *area1 = ptrkData->GetLeaf("area1");
                TLeaf *pltFirst = ptrkData->GetLeaf("US_plt_of_1seg");

                if(area1->GetValue() == k){totProtons++;}
            }

            vtxIntArr[k][j] = TotalPar/area;
            priIntArr[k][j] = IntPar/area;
            proArr[k][j] = totProtons/area;

            cout << "SubArea: " << k << ", Tungsten: " << j << ", Vertex Density: " << TotalPar/area << ", Primary Density: " << IntPar/area << ", Proton Density: " << totProtons/area << endl;
            
        }
    }

    //CreateTexTable(vtxIntArr, "VertexDensityTable.tex");
    //CreateTexTable(priIntArr, "PrimaryDensityTable.tex");
    //CreateTexTable(proArr, "ProtonDensityTable.tex");

    CreateTexTableMulti(vtxIntArr, priIntArr, proArr, "EPOSNew_Density_Old.tex");
}

void CreateTexTable(float arr[subAreaNum][tungstenNum], const char* name)
{
    FILE *VtxTable = fopen(name, "w");

    // Include the graphicx package and use resizebox to ensure the table fits within the page width
    fprintf(VtxTable, "\\documentclass{article}\n");
    fprintf(VtxTable, "\\usepackage[landscape, margin=1in]{geometry}\n");
    fprintf(VtxTable, "\\usepackage{graphicx}\n");
    fprintf(VtxTable, "\\begin{document}\n");
    fprintf(VtxTable, "\\renewcommand{\\arraystretch}{1.2}\n"); // Adjust row height if needed
    fprintf(VtxTable, "\\begin{table}[!htbp]\n");
    fprintf(VtxTable, "\\centering\n");
    fprintf(VtxTable, "\\resizebox{\\textwidth}{!}{%%\n");

    fprintf(VtxTable, "\\begin{tabular}{ |p{3cm}|| p{3cm} | p{3cm} | p{3cm} | p{3cm} | p{3cm} | p{3cm} | p{3cm} | p{3cm}| } \n");
    fprintf(VtxTable, "\\multicolumn{9}{c}{Density} \\\\ \n");
    fprintf(VtxTable, "\\hline\n");
    fprintf(VtxTable, " Subarea &  Tungsten 1 &  Tungsten 2 &  Tungsten 3 &  Tungsten 4 &  Tungsten 5 &  Tungsten 6 &  Tungsten 7 &  Tungsten 8 \\\\ \n");
    fprintf(VtxTable, "\\hline\n");

    // Loop through the array and add the contents to the table
    for (int i = 1; i <= subAreaNum; i++) {
        fprintf(VtxTable, " %d", i);  // Subarea label
        for (int j = 0; j < 8; j++) {
            fprintf(VtxTable, " & %.1f", arr[i][j]);  // Data values
        }
        fprintf(VtxTable, " \\\\ \n");  // End of the row
        fprintf(VtxTable, "\\hline\n");
    }

    fprintf(VtxTable, "\\end{tabular}%%\n");
    fprintf(VtxTable, "}\n");
    fprintf(VtxTable, "\\end{table}\n");
    fprintf(VtxTable, "\\end{document}\n");

    fclose(VtxTable);
}

void CreateTexTableMulti(float vtxArr[subAreaNum][tungstenNum], float priArr[subAreaNum][tungstenNum], float proArr[subAreaNum][tungstenNum], const char* name)
{
    FILE *VtxTable = fopen(name, "w");

    // Include the graphicx package and use resizebox to ensure the table fits within the page width
    fprintf(VtxTable, "\\documentclass{article}\n");
    fprintf(VtxTable, "\\usepackage[landscape, margin=1in]{geometry}\n");
    fprintf(VtxTable, "\\usepackage{graphicx}\n");
    fprintf(VtxTable, "\\begin{document}\n");
    fprintf(VtxTable, "\\renewcommand{\\arraystretch}{1.2}\n"); // Adjust row height if needed
    fprintf(VtxTable, "\\begin{table}[!htbp]\n");
    fprintf(VtxTable, "\\centering\n");
    fprintf(VtxTable, "\\resizebox{\\textwidth}{!}{%%\n");

    fprintf(VtxTable, "\\begin{tabular}{ |p{3cm}|| p{3cm} | p{3cm} | p{3cm} | p{3cm} | p{3cm} | p{3cm} | p{3cm} | p{3cm}| } \n");
    fprintf(VtxTable, "\\multicolumn{9}{c}{Vertex Density} \\\\ \n");
    fprintf(VtxTable, "\\hline\n");
    fprintf(VtxTable, " Subarea &  Tungsten 1 &  Tungsten 2 &  Tungsten 3 &  Tungsten 4 &  Tungsten 5 &  Tungsten 6 &  Tungsten 7 &  Tungsten 8 \\\\ \n");
    fprintf(VtxTable, "\\hline\n");

    // Loop through the array and add the contents to the table
    for (int i = 0; i <= subAreaNum; i++) {
        fprintf(VtxTable, " %d", i);  // Subarea label
        for (int j = 0; j < tungstenNum; j++) {
            fprintf(VtxTable, " & %.1f", vtxArr[i][j]);  // Data values
        }
        fprintf(VtxTable, " \\\\ \n");  // End of the row
        fprintf(VtxTable, "\\hline\n");
    }
    
    fprintf(VtxTable, "Mean");
    for (int j = 0; j < tungstenNum; j++) {
        float mean = calculateMean(vtxArr, subAreaNum, j);
        fprintf(VtxTable, " & %.2f", mean);
    }
    fprintf(VtxTable, " \\\\ \n");
    fprintf(VtxTable, "\\hline\n");

    fprintf(VtxTable, "Std Dev");
    for (int j = 0; j < 8; j++) {
        float mean = calculateMean(vtxArr, subAreaNum, j);
        float stddev = calculateStdDev(vtxArr, subAreaNum, j, mean);
        fprintf(VtxTable, " & %.2f", stddev);
    }
    fprintf(VtxTable, " \\\\ \n");
    fprintf(VtxTable, "\\hline\n");

    fprintf(VtxTable, "\\end{tabular}%%\n");
    fprintf(VtxTable, "}\n");
    fprintf(VtxTable, "\\end{table}\n");
    fprintf(VtxTable, "\\newpage\n\n");

    fprintf(VtxTable, "\\begin{table}[!htbp]\n");
    fprintf(VtxTable, "\\centering\n");
    fprintf(VtxTable, "\\resizebox{\\textwidth}{!}{%%\n");

    fprintf(VtxTable, "\\begin{tabular}{ |p{3cm}|| p{3cm} | p{3cm} | p{3cm} | p{3cm} | p{3cm} | p{3cm} | p{3cm} | p{3cm}| } \n");
    fprintf(VtxTable, "\\multicolumn{9}{c}{Primary Vertex Density} \\\\ \n");
    fprintf(VtxTable, "\\hline\n");
    fprintf(VtxTable, " Subarea &  Tungsten 1 &  Tungsten 2 &  Tungsten 3 &  Tungsten 4 &  Tungsten 5 &  Tungsten 6 &  Tungsten 7 &  Tungsten 8 \\\\ \n");
    fprintf(VtxTable, "\\hline\n");

    // Loop through the array and add the contents to the table
    for (int i = 0; i <= subAreaNum; i++) {
        fprintf(VtxTable, " %d", i);  // Subarea label
        for (int j = 0; j < tungstenNum; j++) {
            fprintf(VtxTable, " & %.1f", priArr[i][j]);  // Data values
        }
        fprintf(VtxTable, " \\\\ \n");  // End of the row
        fprintf(VtxTable, "\\hline\n");
    }

    fprintf(VtxTable, "Mean");
    for (int j = 0; j < tungstenNum; j++) {
        float mean = calculateMean(priArr, subAreaNum, j);
        fprintf(VtxTable, " & %.2f", mean);
    }
    fprintf(VtxTable, " \\\\ \n");
    fprintf(VtxTable, "\\hline\n");

    fprintf(VtxTable, "Std Dev");
    for (int j = 0; j < tungstenNum; j++) {
        float mean = calculateMean(priArr, subAreaNum, j);
        float stddev = calculateStdDev(priArr, subAreaNum, j, mean);
        fprintf(VtxTable, " & %.2f", stddev);
    }
    fprintf(VtxTable, " \\\\ \n");
    fprintf(VtxTable, "\\hline\n");

    fprintf(VtxTable, "\\end{tabular}%%\n");
    fprintf(VtxTable, "}\n");
    fprintf(VtxTable, "\\end{table}\n");
    fprintf(VtxTable, "\\newpage\n\n");

    fprintf(VtxTable, "\\begin{table}[!htbp]\n");
    fprintf(VtxTable, "\\centering\n");
    fprintf(VtxTable, "\\resizebox{\\textwidth}{!}{%%\n");

    fprintf(VtxTable, "\\begin{tabular}{ |p{3cm}|| p{3cm} | p{3cm} | p{3cm} | p{3cm} | p{3cm} | p{3cm} | p{3cm} | p{3cm}| } \n");
    fprintf(VtxTable, "\\multicolumn{9}{c}{Proton Density} \\\\ \n");
    fprintf(VtxTable, "\\hline\n");
    fprintf(VtxTable, " Subarea &  Tungsten 1 &  Tungsten 2 &  Tungsten 3 &  Tungsten 4 &  Tungsten 5 &  Tungsten 6 &  Tungsten 7 &  Tungsten 8 \\\\ \n");
    fprintf(VtxTable, "\\hline\n");

    // Loop through the array and add the contents to the table
    for (int i = 0; i <= subAreaNum; i++) {
        fprintf(VtxTable, " %d", i);  // Subarea label
        for (int j = 0; j < tungstenNum; j++) {
            fprintf(VtxTable, " & %.1f", proArr[i][j]);  // Data values
        }
        fprintf(VtxTable, " \\\\ \n");  // End of the row
        fprintf(VtxTable, "\\hline\n");
    }
    
    fprintf(VtxTable, "Mean");
    for (int j = 0; j < tungstenNum; j++) {
        float mean = calculateMean(proArr, subAreaNum, j);
        fprintf(VtxTable, " & %.2f", mean);
    }
    fprintf(VtxTable, " \\\\ \n");
    fprintf(VtxTable, "\\hline\n");

    fprintf(VtxTable, "Std Dev");
    for (int j = 0; j < tungstenNum; j++) {
        float mean = calculateMean(proArr, subAreaNum, j);
        float stddev = calculateStdDev(proArr, subAreaNum, j, mean);
        fprintf(VtxTable, " & %.2f", stddev);
    }
    fprintf(VtxTable, " \\\\ \n");
    fprintf(VtxTable, "\\hline\n");

    fprintf(VtxTable, "\\end{tabular}%%\n");
    fprintf(VtxTable, "}\n");
    fprintf(VtxTable, "\\end{table}\n");
    fprintf(VtxTable, "\\end{document}\n");

    fclose(VtxTable);
}

double* DataEndPoints(TTree *data)
{
    TH1F *InterHist = new TH1F("InterHist","Vertex Z",50000,0,50000);

    static double endPoints[2];

    for (int i = 0; i < data->GetEntriesFast(); i++)
    {
        data->GetEntry(i);
        
        TLeaf *vz = data->GetLeaf("vz");
        TLeaf *flagW = data->GetLeaf("flagw");
        TLeaf *area1 = data->GetLeaf("area1");
        TLeaf *parNum = data->GetLeaf("n_1ry_parent_dmin_cut");

        if (parNum->GetValue() == 1)
        {
            if (flagW->GetValue() == 1)
            {
                InterHist->Fill(vz->GetValue());
            }
        }
    }

    endPoints[0] = InterHist->FindFirstBinAbove(0);
    endPoints[1] = InterHist->FindLastBinAbove(0);

    delete InterHist;

    return endPoints;
}

double DataMean(TTree *data)
{
  TH1F *InterHist = new TH1F("InterHist","Vertex Z",50000,0,50000);

  static double mean;

  for (int i = 0; i < data->GetEntriesFast(); i++)
  {
    data->GetEntry(i);
    
    TLeaf *vz = data->GetLeaf("vz");
    TLeaf *intMedium = data->GetLeaf("intMed");
    TLeaf *flagW = data->GetLeaf("flagw");
    TLeaf *area1 = data->GetLeaf("area1");
    TLeaf *parNum = data->GetLeaf("n_1ry_parent_dmin_cut");

    if (parNum->GetValue() == 1)
    {
      if (flagW->GetValue() == 1)
      {
        InterHist->Fill(vz->GetValue());
      }
    }
  }

  mean = InterHist->GetMean();

  delete InterHist;

  return mean;
}