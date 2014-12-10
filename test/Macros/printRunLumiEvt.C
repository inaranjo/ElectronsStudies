#include "TTree.h"
#include "TBranch.h"
#include "TString.h"
#include "TPad.h"
#include <TFile.h>
#include <TString.h>
#include <TH1.h>
#include <TH2.h>
#include <TAxis.h>
#include <TGraphAsymmErrors.h>
#include <TF1.h>
#include <TCanvas.h>
#include <TLegend.h>
#include <TPaveText.h>
#include <TMath.h>
#include <TROOT.h>
#include <TStyle.h>
#include "TCut.h"

#include <string>
#include <map>
#include <iostream>
#include <iomanip>

			      

void print()
{


  std::string fSigName = "/data_CMS/cms/ivo/AntiEMVANewTraining/root/test/tree_AntiEMVA-DY_woGwGSF_Elec_Barrel.root";
//  std::string fSigName = "/data_CMS/cms/ivo/AntiEMVANewTraining/root/test/tree_AntiEMVA-DY_woGwGSF_Elec_Endcap.root";

  TFile* fSig = new TFile (fSigName.data(),"READ") ;
  TTree* tSig = (TTree*)fSig->Get("tree");

  int nEntries = tSig->GetEntries();

  ULong64_t run,event,lumi;

  tSig->SetBranchAddress("run", &run);
  tSig->SetBranchAddress("event", &event);
  tSig->SetBranchAddress("lumi", &lumi);
  cout<< "Number of entries : "<<nEntries<<endl;

  cout<<"run:lumi:evt"<<endl; 

  for (int iEntry = 0; iEntry<nEntries ; iEntry++){
//     if(iEntry%100000==0) cout << iEntry  <<"/"<<nEntries << endl;
    tSig->GetEntry(iEntry);

    cout<<"'"<<run<<":"<<lumi<<":"<<event<<"',"<<endl; 

  }

  fSig->Close();

  return;
}
