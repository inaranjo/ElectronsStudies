//--------------------------------------------------------------------------------------------------
// computeDiscriminator
//
// Macro computing the Efficiency and fake rate from the tmva optimization tesTree
// First do AntiEMVAApplication.C
//
// Authors: I.Naranjo
//--------------------------------------------------------------------------------------------------
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

#define DEBUG false			      

void compute(std::string WP = "0p92",
	      float NoEleMatch_woGwoGSF_Barrel_Cut = 0.92,
	      float NoEleMatch_woGwGSF_Barrel_Cut = 0.92,
	      float NoEleMatch_wGwoGSF_Barrel_Cut = 0.92,
	      float NoEleMatch_wGwGSF_Barrel_Cut = 0.92,
	      float woGwoGSF_Barrel_Cut = 0.92,
	      float woGwGSF_Barrel_Cut = 0.92,
	      float wGwoGSF_Barrel_Cut = 0.92,
	      float wGwGSF_Barrel_Cut = 0.92,
	      float NoEleMatch_woGwoGSF_Endcap_Cut = 0.92,
	      float NoEleMatch_woGwGSF_Endcap_Cut = 0.92,
	      float NoEleMatch_wGwoGSF_Endcap_Cut = 0.92,
	      float NoEleMatch_wGwGSF_Endcap_Cut = 0.92,
	      float woGwoGSF_Endcap_Cut = 0.92,
	      float woGwGSF_Endcap_Cut = 0.92,
	      float wGwoGSF_Endcap_Cut = 0.92,
	      float wGwGSF_Endcap_Cut = 0.92
	      )
{

  bool details = false;

//   std::string fSigName = "/data_CMS/cms/ivo/AntiEMVANewTraining/MVAOutput/V14/MvaOutput_AntiEMVA-v14EleVeto-All_Signal.root";
//   std::string fSigName = "/data_CMS/cms/ivo/AntiEMVA/Trees/MVAOutput/V13/MvaOutput_AntiEMVA-v13EleVeto-DYJets_Signal.root";
//   std::string fSigName = "/data_CMS/cms/ivo/AntiEMVANewTraining/MVAOutput/V14/MvaOutput_AntiEMVA-v14EleVeto-DYJetsIter2_Signal.root";
//   std::string fSigName = "/data_CMS/cms/ivo/AntiEMVANewTraining/MVAOutput/V16/MvaOutput_AntiEMVA-v16EleVeto-DYJets_Signal.root";
//   std::string fSigName = "/data_CMS/cms/ivo/AntiEMVANewTraining/MVAOutput/V16/MvaOutput_AntiEMVA-v16EleVeto-All_Signal.root";
//   std::string fSigName = "/data_CMS/cms/ivo/AntiEMVANewTraining/MVAOutput/V16/MvaOutput_AntiEMVA-v16EleVeto-AllFromTraining_Signal.root";
//   std::string fSigName = "/data_CMS/cms/ivo/AntiEMVANewTraining/MVAOutput/V17/MvaOutput_AntiEMVA-v17EleVeto-DY_Signal.root";
//   std::string fSigName = "/data_CMS/cms/ivo/AntiEMVANewTraining/MVAOutput/V17/MvaOutput_AntiEMVA-v17EleVeto-All_Signal.root";
//   std::string fSigName = "/data_CMS/cms/ivo/AntiEMVANewTraining/MVAOutput/V18/MvaOutput_AntiEMVA-v18EleVeto-All_Signal.root";
  std::string fSigName = "/data_CMS/cms/ivo/AntiEMVANewTraining/MVAOutput/V18/MvaOutput_AntiEMVA-v18EleVeto-All_Signal.root";

  TFile* fSig = new TFile (fSigName.data(),"READ") ;
  TTree* tSig = (TTree*)fSig->Get("tree");

//   std::string fBkgName = "/data_CMS/cms/ivo/AntiEMVANewTraining/MVAOutput/V14/MvaOutput_AntiEMVA-v14EleVeto-DYJetsIter2_Backgrd.root";
//   std::string fBkgName = "/data_CMS/cms/ivo/AntiEMVANewTraining/MVAOutput/V14/MvaOutput_AntiEMVA-v14EleVeto-All_Backgrd.root";
//   std::string fBkgName = "/data_CMS/cms/ivo/AntiEMVA/Trees/MVAOutput/V13/MvaOutput_AntiEMVA-v13EleVeto-DYJets_Backgrd.root";
//   std::string fBkgName = "/data_CMS/cms/ivo/AntiEMVANewTraining/MVAOutput/V16/MvaOutput_AntiEMVA-v16EleVeto-DYJets_Backgrd.root";
//   std::string fBkgName = "/data_CMS/cms/ivo/AntiEMVANewTraining/MVAOutput/V16/MvaOutput_AntiEMVA-v16EleVeto-All_Backgrd.root";
//   std::string fBkgName = "/data_CMS/cms/ivo/AntiEMVANewTraining/MVAOutput/V16/MvaOutput_AntiEMVA-v16EleVeto-AllFromTraining_Backgrd.root";
//   std::string fBkgName = "/data_CMS/cms/ivo/AntiEMVANewTraining/MVAOutput/V17/MvaOutput_AntiEMVA-v17EleVeto-DY_Backgrd.root";
//   std::string fBkgName = "/data_CMS/cms/ivo/AntiEMVANewTraining/MVAOutput/V17/MvaOutput_AntiEMVA-v17EleVeto-All_Backgrd.root";
//   std::string fBkgName = "/data_CMS/cms/ivo/AntiEMVANewTraining/MVAOutput/V18/MvaOutput_AntiEMVA-v18EleVeto-All_Backgrd.root";
  std::string fBkgName = "/data_CMS/cms/ivo/AntiEMVANewTraining/MVAOutput/V18/MvaOutput_AntiEMVA-v18EleVeto-All_Backgrd.root";
  TFile* fBkg = new TFile (fBkgName.data(),"READ") ;
  TTree* tBkg = (TTree*)fBkg->Get("tree");

  TCut CutEleVeto =Form("Tau_LooseComb3HitsIso>0.5 && Tau_isInEcalCrack<0.5 && Tau_MatchElePassVeto<0.5 && NoEleMatch_woGwoGSF_Barrel>%f && NoEleMatch_woGwGSF_Barrel>%f && NoEleMatch_wGwoGSF_Barrel>%f && NoEleMatch_wGwGSF_Barrel>%f  && woGwoGSF_Barrel>%f && woGwGSF_Barrel>%f && wGwoGSF_Barrel>%f && wGwGSF_Barrel>%f && NoEleMatch_woGwoGSF_Endcap>%f && NoEleMatch_woGwGSF_Endcap>%f && NoEleMatch_wGwoGSF_Endcap>%f && NoEleMatch_wGwGSF_Endcap>%f  && woGwoGSF_Endcap>%f && woGwGSF_Endcap>%f && wGwoGSF_Endcap>%f && wGwGSF_Endcap>%f" ,
			NoEleMatch_woGwoGSF_Barrel_Cut,
			NoEleMatch_woGwGSF_Barrel_Cut,
			NoEleMatch_wGwoGSF_Barrel_Cut,
			NoEleMatch_wGwGSF_Barrel_Cut,
			woGwoGSF_Barrel_Cut,
			woGwGSF_Barrel_Cut,
			wGwoGSF_Barrel_Cut,
			wGwGSF_Barrel_Cut,
			NoEleMatch_woGwoGSF_Endcap_Cut,
			NoEleMatch_woGwGSF_Endcap_Cut,
			NoEleMatch_wGwoGSF_Endcap_Cut,
			NoEleMatch_wGwGSF_Endcap_Cut,
			woGwoGSF_Endcap_Cut,
			woGwGSF_Endcap_Cut,
			wGwoGSF_Endcap_Cut,
			wGwGSF_Endcap_Cut
			);


  TCut Cut =Form("Tau_LooseComb3HitsIso>0.5 && Tau_isInEcalCrack<0.5  && NoEleMatch_woGwoGSF_Barrel>%f && NoEleMatch_woGwGSF_Barrel>%f && NoEleMatch_wGwoGSF_Barrel>%f && NoEleMatch_wGwGSF_Barrel>%f  && woGwoGSF_Barrel>%f && woGwGSF_Barrel>%f && wGwoGSF_Barrel>%f && wGwGSF_Barrel>%f && NoEleMatch_woGwoGSF_Endcap>%f && NoEleMatch_woGwGSF_Endcap>%f && NoEleMatch_wGwoGSF_Endcap>%f && NoEleMatch_wGwGSF_Endcap>%f  && woGwoGSF_Endcap>%f && woGwGSF_Endcap>%f && wGwoGSF_Endcap>%f && wGwGSF_Endcap>%f" ,
		 NoEleMatch_woGwoGSF_Barrel_Cut,
		 NoEleMatch_woGwGSF_Barrel_Cut,
		 NoEleMatch_wGwoGSF_Barrel_Cut,
		 NoEleMatch_wGwGSF_Barrel_Cut,
		 woGwoGSF_Barrel_Cut,
		 woGwGSF_Barrel_Cut,
		 wGwoGSF_Barrel_Cut,
		 wGwGSF_Barrel_Cut,
		 NoEleMatch_woGwoGSF_Endcap_Cut,
		 NoEleMatch_woGwGSF_Endcap_Cut,
		 NoEleMatch_wGwoGSF_Endcap_Cut,
		 NoEleMatch_wGwGSF_Endcap_Cut,
		 woGwoGSF_Endcap_Cut,
		 woGwGSF_Endcap_Cut,
		 wGwoGSF_Endcap_Cut,
		 wGwGSF_Endcap_Cut
		 );

  TH1F* hSig = new TH1F("hSig","",1,-10,10);
  tSig->Draw("Tau_GenEleMatch>>hSig","Tau_LooseComb3HitsIso>0.5 && Tau_isInEcalCrack<0.5");
  float nSig = hSig->GetEntries();

  float nSig0 = 0;
  float nSig1 = 0;
  float nSig2 = 0;
  float nSig3 = 0;
  float nSig4 = 0;
  float nSig5 = 0;
  float nSig6 = 0;
  float nSig7 = 0;
  float nSig8 = 0;
  float nSig9 = 0;
  float nSig10 = 0;
  float nSig11 = 0;
  float nSig12 = 0;
  float nSig13 = 0;
  float nSig14 = 0;
  float nSig15 = 0;
  float nSigEleVeto0 = 0;
  float nSigEleVeto1 = 0;
  float nSigEleVeto2 = 0;
  float nSigEleVeto3 = 0;
  float nSigEleVeto4 = 0;
  float nSigEleVeto5 = 0;
  float nSigEleVeto6 = 0;
  float nSigEleVeto7 = 0;
  float nSigEleVeto8 = 0;
  float nSigEleVeto9 = 0;
  float nSigEleVeto10 = 0;
  float nSigEleVeto11 = 0;
  float nSigEleVeto12 = 0;
  float nSigEleVeto13 = 0;
  float nSigEleVeto14 = 0;
  float nSigEleVeto15 = 0;
  float nBkg0 = 0;
  float nBkg1 = 0;
  float nBkg2 = 0;
  float nBkg3 = 0;
  float nBkg4 = 0;
  float nBkg5 = 0;
  float nBkg6 = 0;
  float nBkg7 = 0;
  float nBkg8 = 0;
  float nBkg9 = 0;
  float nBkg10 = 0;
  float nBkg11 = 0;
  float nBkg12 = 0;
  float nBkg13 = 0;
  float nBkg14 = 0;
  float nBkg15 = 0;
  float nBkgEleVeto0 = 0;
  float nBkgEleVeto1 = 0;
  float nBkgEleVeto2 = 0;
  float nBkgEleVeto3 = 0;
  float nBkgEleVeto4 = 0;
  float nBkgEleVeto5 = 0;
  float nBkgEleVeto6 = 0;
  float nBkgEleVeto7 = 0;
  float nBkgEleVeto8 = 0;
  float nBkgEleVeto9 = 0;
  float nBkgEleVeto10 = 0;
  float nBkgEleVeto11 = 0;
  float nBkgEleVeto12 = 0;
  float nBkgEleVeto13 = 0;
  float nBkgEleVeto14 = 0;
  float nBkgEleVeto15 = 0;


  if(details){
    tSig->Draw("Tau_GenEleMatch>>hSig","Tau_LooseComb3HitsIso>0.5 && Tau_isInEcalCrack<0.5 && Category==0");
    nSig0 = hSig->GetEntries();
    tSig->Draw("Tau_GenEleMatch>>hSig","Tau_LooseComb3HitsIso>0.5 && Tau_isInEcalCrack<0.5 && Category==1");
    nSig1 = hSig->GetEntries();
    tSig->Draw("Tau_GenEleMatch>>hSig","Tau_LooseComb3HitsIso>0.5 && Tau_isInEcalCrack<0.5 && Category==2");
    nSig2 = hSig->GetEntries();
    tSig->Draw("Tau_GenEleMatch>>hSig","Tau_LooseComb3HitsIso>0.5 && Tau_isInEcalCrack<0.5 && Category==3");
    nSig3 = hSig->GetEntries();
    tSig->Draw("Tau_GenEleMatch>>hSig","Tau_LooseComb3HitsIso>0.5 && Tau_isInEcalCrack<0.5 && Category==4");
    nSig4 = hSig->GetEntries();
    tSig->Draw("Tau_GenEleMatch>>hSig","Tau_LooseComb3HitsIso>0.5 && Tau_isInEcalCrack<0.5 && Category==5");
    nSig5 = hSig->GetEntries();
    tSig->Draw("Tau_GenEleMatch>>hSig","Tau_LooseComb3HitsIso>0.5 && Tau_isInEcalCrack<0.5 && Category==6");
    nSig6 = hSig->GetEntries();
    tSig->Draw("Tau_GenEleMatch>>hSig","Tau_LooseComb3HitsIso>0.5 && Tau_isInEcalCrack<0.5 && Category==7");
    nSig7 = hSig->GetEntries();
    tSig->Draw("Tau_GenEleMatch>>hSig","Tau_LooseComb3HitsIso>0.5 && Tau_isInEcalCrack<0.5 && Category==8");
    nSig8 = hSig->GetEntries();
    tSig->Draw("Tau_GenEleMatch>>hSig","Tau_LooseComb3HitsIso>0.5 && Tau_isInEcalCrack<0.5 && Category==9");
    nSig9 = hSig->GetEntries();
    tSig->Draw("Tau_GenEleMatch>>hSig","Tau_LooseComb3HitsIso>0.5 && Tau_isInEcalCrack<0.5 && Category==10");
    nSig10 = hSig->GetEntries();
    tSig->Draw("Tau_GenEleMatch>>hSig","Tau_LooseComb3HitsIso>0.5 && Tau_isInEcalCrack<0.5 && Category==11");
    nSig11 = hSig->GetEntries();
    tSig->Draw("Tau_GenEleMatch>>hSig","Tau_LooseComb3HitsIso>0.5 && Tau_isInEcalCrack<0.5 && Category==12");
    nSig12 = hSig->GetEntries();
    tSig->Draw("Tau_GenEleMatch>>hSig","Tau_LooseComb3HitsIso>0.5 && Tau_isInEcalCrack<0.5 && Category==13");
    nSig13 = hSig->GetEntries();
    tSig->Draw("Tau_GenEleMatch>>hSig","Tau_LooseComb3HitsIso>0.5 && Tau_isInEcalCrack<0.5 && Category==14");
    nSig14 = hSig->GetEntries();
    tSig->Draw("Tau_GenEleMatch>>hSig","Tau_LooseComb3HitsIso>0.5 && Tau_isInEcalCrack<0.5 && Category==15");
    nSig15 = hSig->GetEntries();
  }
  tSig->Draw("Tau_GenEleMatch>>hSig","Tau_LooseComb3HitsIso>0.5 && Tau_MatchElePassVeto<0.5 && Tau_isInEcalCrack<0.5 ");
  float nSigEleVeto = hSig->GetEntries();
  tSig->Draw("Tau_GenEleMatch>>hSig","Tau_LooseComb3HitsIso>0.5 && Tau_isInEcalCrack>0.5 ");
  float nSigCrack = hSig->GetEntries();
  if(details){
    tSig->Draw("Tau_GenEleMatch>>hSig","Tau_LooseComb3HitsIso>0.5 && Tau_isInEcalCrack<0.5 && Tau_MatchElePassVeto<0.5 && Category==0");
    nSigEleVeto0 = hSig->GetEntries();
    tSig->Draw("Tau_GenEleMatch>>hSig","Tau_LooseComb3HitsIso>0.5 && Tau_isInEcalCrack<0.5 && Tau_MatchElePassVeto<0.5 && Category==1");
    nSigEleVeto1 = hSig->GetEntries();
    tSig->Draw("Tau_GenEleMatch>>hSig","Tau_LooseComb3HitsIso>0.5 && Tau_isInEcalCrack<0.5 && Tau_MatchElePassVeto<0.5 && Category==2");
    nSigEleVeto2 = hSig->GetEntries();
    tSig->Draw("Tau_GenEleMatch>>hSig","Tau_LooseComb3HitsIso>0.5 && Tau_isInEcalCrack<0.5 && Tau_MatchElePassVeto<0.5 && Category==3");
    nSigEleVeto3 = hSig->GetEntries();
    tSig->Draw("Tau_GenEleMatch>>hSig","Tau_LooseComb3HitsIso>0.5 && Tau_isInEcalCrack<0.5 && Tau_MatchElePassVeto<0.5 && Category==4");
    nSigEleVeto4 = hSig->GetEntries();
    tSig->Draw("Tau_GenEleMatch>>hSig","Tau_LooseComb3HitsIso>0.5 && Tau_isInEcalCrack<0.5 && Tau_MatchElePassVeto<0.5 && Category==5");
    nSigEleVeto5 = hSig->GetEntries();
    tSig->Draw("Tau_GenEleMatch>>hSig","Tau_LooseComb3HitsIso>0.5 && Tau_isInEcalCrack<0.5 && Tau_MatchElePassVeto<0.5 && Category==6");
    nSigEleVeto6 = hSig->GetEntries();
    tSig->Draw("Tau_GenEleMatch>>hSig","Tau_LooseComb3HitsIso>0.5 && Tau_isInEcalCrack<0.5 && Tau_MatchElePassVeto<0.5 && Category==7");
    nSigEleVeto7 = hSig->GetEntries();
    tSig->Draw("Tau_GenEleMatch>>hSig","Tau_LooseComb3HitsIso>0.5 && Tau_isInEcalCrack<0.5 && Tau_MatchElePassVeto<0.5 && Category==8");
    nSigEleVeto8 = hSig->GetEntries();
    tSig->Draw("Tau_GenEleMatch>>hSig","Tau_LooseComb3HitsIso>0.5 && Tau_isInEcalCrack<0.5 && Tau_MatchElePassVeto<0.5 && Category==9");
    nSigEleVeto9 = hSig->GetEntries();
    tSig->Draw("Tau_GenEleMatch>>hSig","Tau_LooseComb3HitsIso>0.5 && Tau_isInEcalCrack<0.5 && Tau_MatchElePassVeto<0.5 && Category==10");
    nSigEleVeto10 = hSig->GetEntries();
    tSig->Draw("Tau_GenEleMatch>>hSig","Tau_LooseComb3HitsIso>0.5 && Tau_isInEcalCrack<0.5 && Tau_MatchElePassVeto<0.5 && Category==11");
    nSigEleVeto11 = hSig->GetEntries();
    tSig->Draw("Tau_GenEleMatch>>hSig","Tau_LooseComb3HitsIso>0.5 && Tau_isInEcalCrack<0.5 && Tau_MatchElePassVeto<0.5 && Category==12");
    nSigEleVeto12 = hSig->GetEntries();
    tSig->Draw("Tau_GenEleMatch>>hSig","Tau_LooseComb3HitsIso>0.5 && Tau_isInEcalCrack<0.5 && Tau_MatchElePassVeto<0.5 && Category==13");
    nSigEleVeto13 = hSig->GetEntries();
    tSig->Draw("Tau_GenEleMatch>>hSig","Tau_LooseComb3HitsIso>0.5 && Tau_isInEcalCrack<0.5 && Tau_MatchElePassVeto<0.5 && Category==14");
    nSigEleVeto14 = hSig->GetEntries();
    tSig->Draw("Tau_GenEleMatch>>hSig","Tau_LooseComb3HitsIso>0.5 && Tau_isInEcalCrack<0.5 && Tau_MatchElePassVeto<0.5 && Category==15");
    nSigEleVeto15 = hSig->GetEntries();
  }


  TH1F* hBkg = new TH1F("hBkg","",1,-10,10);
  tBkg->Draw("Tau_GenEleMatch>>hBkg","Tau_LooseComb3HitsIso>0.5 && Tau_isInEcalCrack<0.5 ");
  float nBkg = hBkg->GetEntries();
  if(details){
    tBkg->Draw("Tau_GenEleMatch>>hBkg","Tau_LooseComb3HitsIso>0.5 && Tau_isInEcalCrack<0.5 && Category==0");
    nBkg0 = hBkg->GetEntries();
    tBkg->Draw("Tau_GenEleMatch>>hBkg","Tau_LooseComb3HitsIso>0.5 && Tau_isInEcalCrack<0.5 && Category==1");
    nBkg1 = hBkg->GetEntries();
    tBkg->Draw("Tau_GenEleMatch>>hBkg","Tau_LooseComb3HitsIso>0.5 && Tau_isInEcalCrack<0.5 && Category==2");
    nBkg2 = hBkg->GetEntries();
    tBkg->Draw("Tau_GenEleMatch>>hBkg","Tau_LooseComb3HitsIso>0.5 && Tau_isInEcalCrack<0.5 && Category==3");
    nBkg3 = hBkg->GetEntries();
    tBkg->Draw("Tau_GenEleMatch>>hBkg","Tau_LooseComb3HitsIso>0.5 && Tau_isInEcalCrack<0.5 && Category==4");
    nBkg4 = hBkg->GetEntries();
    tBkg->Draw("Tau_GenEleMatch>>hBkg","Tau_LooseComb3HitsIso>0.5 && Tau_isInEcalCrack<0.5 && Category==5");
    nBkg5 = hBkg->GetEntries();
    tBkg->Draw("Tau_GenEleMatch>>hBkg","Tau_LooseComb3HitsIso>0.5 && Tau_isInEcalCrack<0.5 && Category==6");
    nBkg6 = hBkg->GetEntries();
    tBkg->Draw("Tau_GenEleMatch>>hBkg","Tau_LooseComb3HitsIso>0.5 && Tau_isInEcalCrack<0.5 && Category==7");
    nBkg7 = hBkg->GetEntries();
    tBkg->Draw("Tau_GenEleMatch>>hBkg","Tau_LooseComb3HitsIso>0.5 && Tau_isInEcalCrack<0.5 && Category==8");
    nBkg8 = hBkg->GetEntries();
    tBkg->Draw("Tau_GenEleMatch>>hBkg","Tau_LooseComb3HitsIso>0.5 && Tau_isInEcalCrack<0.5 && Category==9");
    nBkg9 = hBkg->GetEntries();
    tBkg->Draw("Tau_GenEleMatch>>hBkg","Tau_LooseComb3HitsIso>0.5 && Tau_isInEcalCrack<0.5 && Category==10");
    nBkg10 = hBkg->GetEntries();
    tBkg->Draw("Tau_GenEleMatch>>hBkg","Tau_LooseComb3HitsIso>0.5 && Tau_isInEcalCrack<0.5 && Category==11");
    nBkg11 = hBkg->GetEntries();
    tBkg->Draw("Tau_GenEleMatch>>hBkg","Tau_LooseComb3HitsIso>0.5 && Tau_isInEcalCrack<0.5 && Category==12");
    nBkg12 = hBkg->GetEntries();
    tBkg->Draw("Tau_GenEleMatch>>hBkg","Tau_LooseComb3HitsIso>0.5 && Tau_isInEcalCrack<0.5 && Category==13");
    nBkg13 = hBkg->GetEntries();
    tBkg->Draw("Tau_GenEleMatch>>hBkg","Tau_LooseComb3HitsIso>0.5 && Tau_isInEcalCrack<0.5 && Category==14");
    nBkg14 = hBkg->GetEntries();
    tBkg->Draw("Tau_GenEleMatch>>hBkg","Tau_LooseComb3HitsIso>0.5 && Tau_isInEcalCrack<0.5 && Category==15");
    nBkg15 = hBkg->GetEntries();
  }

  tBkg->Draw("Tau_GenEleMatch>>hBkg","Tau_LooseComb3HitsIso>0.5 && Tau_MatchElePassVeto<0.5 && Tau_isInEcalCrack<0.5 ");
  float nBkgEleVeto = hBkg->GetEntries();
  tBkg->Draw("Tau_GenEleMatch>>hBkg","Tau_LooseComb3HitsIso>0.5 && Tau_isInEcalCrack>0.5 ");
  float nBkgCrack = hBkg->GetEntries();
  if(details){
    tBkg->Draw("Tau_GenEleMatch>>hBkg","Tau_LooseComb3HitsIso>0.5 && Tau_isInEcalCrack<0.5 && Tau_MatchElePassVeto<0.5 && Category==0");
    nBkgEleVeto0 = hBkg->GetEntries();
    tBkg->Draw("Tau_GenEleMatch>>hBkg","Tau_LooseComb3HitsIso>0.5 && Tau_isInEcalCrack<0.5 && Tau_MatchElePassVeto<0.5 && Category==1");
    nBkgEleVeto1 = hBkg->GetEntries();
    tBkg->Draw("Tau_GenEleMatch>>hBkg","Tau_LooseComb3HitsIso>0.5 && Tau_isInEcalCrack<0.5 && Tau_MatchElePassVeto<0.5 && Category==2");
    nBkgEleVeto2 = hBkg->GetEntries();
    tBkg->Draw("Tau_GenEleMatch>>hBkg","Tau_LooseComb3HitsIso>0.5 && Tau_isInEcalCrack<0.5 && Tau_MatchElePassVeto<0.5 && Category==3");
    nBkgEleVeto3 = hBkg->GetEntries();
    tBkg->Draw("Tau_GenEleMatch>>hBkg","Tau_LooseComb3HitsIso>0.5 && Tau_isInEcalCrack<0.5 && Tau_MatchElePassVeto<0.5 && Category==4");
    nBkgEleVeto4 = hBkg->GetEntries();
    tBkg->Draw("Tau_GenEleMatch>>hBkg","Tau_LooseComb3HitsIso>0.5 && Tau_isInEcalCrack<0.5 && Tau_MatchElePassVeto<0.5 && Category==5");
    nBkgEleVeto5 = hBkg->GetEntries();
    tBkg->Draw("Tau_GenEleMatch>>hBkg","Tau_LooseComb3HitsIso>0.5 && Tau_isInEcalCrack<0.5 && Tau_MatchElePassVeto<0.5 && Category==6");
    nBkgEleVeto6 = hBkg->GetEntries();
    tBkg->Draw("Tau_GenEleMatch>>hBkg","Tau_LooseComb3HitsIso>0.5 && Tau_isInEcalCrack<0.5 && Tau_MatchElePassVeto<0.5 && Category==7");
    nBkgEleVeto7 = hBkg->GetEntries();
    tBkg->Draw("Tau_GenEleMatch>>hBkg","Tau_LooseComb3HitsIso>0.5 && Tau_isInEcalCrack<0.5 && Tau_MatchElePassVeto<0.5 && Category==8");
    nBkgEleVeto8 = hBkg->GetEntries();
    tBkg->Draw("Tau_GenEleMatch>>hBkg","Tau_LooseComb3HitsIso>0.5 && Tau_isInEcalCrack<0.5 && Tau_MatchElePassVeto<0.5 && Category==9");
    nBkgEleVeto9 = hBkg->GetEntries();
    tBkg->Draw("Tau_GenEleMatch>>hBkg","Tau_LooseComb3HitsIso>0.5 && Tau_isInEcalCrack<0.5 && Tau_MatchElePassVeto<0.5 && Category==10");
    nBkgEleVeto10 = hBkg->GetEntries();
    tBkg->Draw("Tau_GenEleMatch>>hBkg","Tau_LooseComb3HitsIso>0.5 && Tau_isInEcalCrack<0.5 && Tau_MatchElePassVeto<0.5 && Category==11");
    nBkgEleVeto11 = hBkg->GetEntries();
    tBkg->Draw("Tau_GenEleMatch>>hBkg","Tau_LooseComb3HitsIso>0.5 && Tau_isInEcalCrack<0.5 && Tau_MatchElePassVeto<0.5 && Category==12");
    nBkgEleVeto12 = hBkg->GetEntries();
    tBkg->Draw("Tau_GenEleMatch>>hBkg","Tau_LooseComb3HitsIso>0.5 && Tau_isInEcalCrack<0.5 && Tau_MatchElePassVeto<0.5 && Category==13");
    nBkgEleVeto13 = hBkg->GetEntries();
    tBkg->Draw("Tau_GenEleMatch>>hBkg","Tau_LooseComb3HitsIso>0.5 && Tau_isInEcalCrack<0.5 && Tau_MatchElePassVeto<0.5 && Category==14");
    nBkgEleVeto14 = hBkg->GetEntries();
    tBkg->Draw("Tau_GenEleMatch>>hBkg","Tau_LooseComb3HitsIso>0.5 && Tau_isInEcalCrack<0.5 && Tau_MatchElePassVeto<0.5 && Category==15");
    nBkgEleVeto15 = hBkg->GetEntries();
  }


  TH1F* hSigPassCat = new TH1F("hSigPassCat","",1,-10,10);
  TH1F* hBkgPassCat = new TH1F("hBkgPassCat","",1,-10,10);
  float nSigPass0 = 0;
  float nSigPass1 = 0;
  float nSigPass2 = 0;
  float nSigPass3 = 0;
  float nSigPass4 = 0;
  float nSigPass5 = 0;
  float nSigPass6 = 0;
  float nSigPass7 = 0;
  float nSigPass8 = 0;
  float nSigPass9 = 0;
  float nSigPass10 = 0;
  float nSigPass11 = 0;
  float nSigPass12 = 0;
  float nSigPass13 = 0;
  float nSigPass14 = 0;
  float nSigPass15 = 0;
  float nSigPassEleVeto0 = 0;
  float nSigPassEleVeto1 = 0;
  float nSigPassEleVeto2 = 0;
  float nSigPassEleVeto3 = 0;
  float nSigPassEleVeto4 = 0;
  float nSigPassEleVeto5 = 0;
  float nSigPassEleVeto6 = 0;
  float nSigPassEleVeto7 = 0;
  float nSigPassEleVeto8 = 0;
  float nSigPassEleVeto9 = 0;
  float nSigPassEleVeto10 = 0;
  float nSigPassEleVeto11 = 0;
  float nSigPassEleVeto12 = 0;
  float nSigPassEleVeto13 = 0;
  float nSigPassEleVeto14 = 0;
  float nSigPassEleVeto15 = 0;
  float nBkgPass0 = 0;
  float nBkgPass1 = 0;
  float nBkgPass2 = 0;
  float nBkgPass3 = 0;
  float nBkgPass4 = 0;
  float nBkgPass5 = 0;
  float nBkgPass6 = 0;
  float nBkgPass7 = 0;
  float nBkgPass8 = 0;
  float nBkgPass9 = 0;
  float nBkgPass10 = 0;
  float nBkgPass11 = 0;
  float nBkgPass12 = 0;
  float nBkgPass13 = 0;
  float nBkgPass14 = 0;
  float nBkgPass15 = 0;
  float nBkgPassEleVeto0 = 0;
  float nBkgPassEleVeto1 = 0;
  float nBkgPassEleVeto2 = 0;
  float nBkgPassEleVeto3 = 0;
  float nBkgPassEleVeto4 = 0;
  float nBkgPassEleVeto5 = 0;
  float nBkgPassEleVeto6 = 0;
  float nBkgPassEleVeto7 = 0;
  float nBkgPassEleVeto8 = 0;
  float nBkgPassEleVeto9 = 0;
  float nBkgPassEleVeto10 = 0;
  float nBkgPassEleVeto11 = 0;
  float nBkgPassEleVeto12 = 0;
  float nBkgPassEleVeto13 = 0;
  float nBkgPassEleVeto14 = 0;
  float nBkgPassEleVeto15 = 0;

  if(details){
    tSig->Draw("Tau_GenEleMatch>>hSigPassCat",Cut*"Category==0");
    nSigPass0 = hSigPassCat->GetEntries();
    tSig->Draw("Tau_GenEleMatch>>hSigPassCat",Cut*"Category==1");
    nSigPass1 = hSigPassCat->GetEntries();
    tSig->Draw("Tau_GenEleMatch>>hSigPassCat",Cut*"Category==2");
    nSigPass2 = hSigPassCat->GetEntries();
    tSig->Draw("Tau_GenEleMatch>>hSigPassCat",Cut*"Category==3");
    nSigPass3 = hSigPassCat->GetEntries();
    tSig->Draw("Tau_GenEleMatch>>hSigPassCat",Cut*"Category==4");
    nSigPass4 = hSigPassCat->GetEntries();
    tSig->Draw("Tau_GenEleMatch>>hSigPassCat",Cut*"Category==5");
    nSigPass5 = hSigPassCat->GetEntries();
    tSig->Draw("Tau_GenEleMatch>>hSigPassCat",Cut*"Category==6");
    nSigPass6 = hSigPassCat->GetEntries();
    tSig->Draw("Tau_GenEleMatch>>hSigPassCat",Cut*"Category==7");
    nSigPass7 = hSigPassCat->GetEntries();
    tSig->Draw("Tau_GenEleMatch>>hSigPassCat",Cut*"Category==8");
    nSigPass8 = hSigPassCat->GetEntries();
    tSig->Draw("Tau_GenEleMatch>>hSigPassCat",Cut*"Category==9");
    nSigPass9 = hSigPassCat->GetEntries();
    tSig->Draw("Tau_GenEleMatch>>hSigPassCat",Cut*"Category==10");
    nSigPass10 = hSigPassCat->GetEntries();
    tSig->Draw("Tau_GenEleMatch>>hSigPassCat",Cut*"Category==11");
    nSigPass11 = hSigPassCat->GetEntries();
    tSig->Draw("Tau_GenEleMatch>>hSigPassCat",Cut*"Category==12");
    nSigPass12 = hSigPassCat->GetEntries();
    tSig->Draw("Tau_GenEleMatch>>hSigPassCat",Cut*"Category==13");
    nSigPass13 = hSigPassCat->GetEntries();
    tSig->Draw("Tau_GenEleMatch>>hSigPassCat",Cut*"Category==14");
    nSigPass14 = hSigPassCat->GetEntries();
    tSig->Draw("Tau_GenEleMatch>>hSigPassCat",Cut*"Category==15");
    nSigPass15 = hSigPassCat->GetEntries();

    tSig->Draw("Tau_GenEleMatch>>hSigPassCat",CutEleVeto*"Category==0");
    nSigPassEleVeto0 = hSigPassCat->GetEntries();
    tSig->Draw("Tau_GenEleMatch>>hSigPassCat",CutEleVeto*"Category==1");
    nSigPassEleVeto1 = hSigPassCat->GetEntries();
    tSig->Draw("Tau_GenEleMatch>>hSigPassCat",CutEleVeto*"Category==2");
    nSigPassEleVeto2 = hSigPassCat->GetEntries();
    tSig->Draw("Tau_GenEleMatch>>hSigPassCat",CutEleVeto*"Category==3");
    nSigPassEleVeto3 = hSigPassCat->GetEntries();
    tSig->Draw("Tau_GenEleMatch>>hSigPassCat",CutEleVeto*"Category==4");
    nSigPassEleVeto4 = hSigPassCat->GetEntries();
    tSig->Draw("Tau_GenEleMatch>>hSigPassCat",CutEleVeto*"Category==5");
    nSigPassEleVeto5 = hSigPassCat->GetEntries();
    tSig->Draw("Tau_GenEleMatch>>hSigPassCat",CutEleVeto*"Category==6");
    nSigPassEleVeto6 = hSigPassCat->GetEntries();
    tSig->Draw("Tau_GenEleMatch>>hSigPassCat",CutEleVeto*"Category==7");
    nSigPassEleVeto7 = hSigPassCat->GetEntries();
    tSig->Draw("Tau_GenEleMatch>>hSigPassCat",CutEleVeto*"Category==8");
    nSigPassEleVeto8 = hSigPassCat->GetEntries();
    tSig->Draw("Tau_GenEleMatch>>hSigPassCat",CutEleVeto*"Category==9");
    nSigPassEleVeto9 = hSigPassCat->GetEntries();
    tSig->Draw("Tau_GenEleMatch>>hSigPassCat",CutEleVeto*"Category==10");
    nSigPassEleVeto10 = hSigPassCat->GetEntries();
    tSig->Draw("Tau_GenEleMatch>>hSigPassCat",CutEleVeto*"Category==11");
    nSigPassEleVeto11 = hSigPassCat->GetEntries();
    tSig->Draw("Tau_GenEleMatch>>hSigPassCat",CutEleVeto*"Category==12");
    nSigPassEleVeto12 = hSigPassCat->GetEntries();
    tSig->Draw("Tau_GenEleMatch>>hSigPassCat",CutEleVeto*"Category==13");
    nSigPassEleVeto13 = hSigPassCat->GetEntries();
    tSig->Draw("Tau_GenEleMatch>>hSigPassCat",CutEleVeto*"Category==14");
    nSigPassEleVeto14 = hSigPassCat->GetEntries();
    tSig->Draw("Tau_GenEleMatch>>hSigPassCat",CutEleVeto*"Category==15");
    nSigPassEleVeto15 = hSigPassCat->GetEntries();
  }

  if(details){
    tBkg->Draw("Tau_GenEleMatch>>hBkgPassCat",Cut*"Category==0");
    nBkgPass0 = hBkgPassCat->GetEntries();
    tBkg->Draw("Tau_GenEleMatch>>hBkgPassCat",Cut*"Category==1");
    nBkgPass1 = hBkgPassCat->GetEntries();
    tBkg->Draw("Tau_GenEleMatch>>hBkgPassCat",Cut*"Category==2");
    nBkgPass2 = hBkgPassCat->GetEntries();
    tBkg->Draw("Tau_GenEleMatch>>hBkgPassCat",Cut*"Category==3");
    nBkgPass3 = hBkgPassCat->GetEntries();
    tBkg->Draw("Tau_GenEleMatch>>hBkgPassCat",Cut*"Category==4");
    nBkgPass4 = hBkgPassCat->GetEntries();
    tBkg->Draw("Tau_GenEleMatch>>hBkgPassCat",Cut*"Category==5");
    nBkgPass5 = hBkgPassCat->GetEntries();
    tBkg->Draw("Tau_GenEleMatch>>hBkgPassCat",Cut*"Category==6");
    nBkgPass6 = hBkgPassCat->GetEntries();
    tBkg->Draw("Tau_GenEleMatch>>hBkgPassCat",Cut*"Category==7");
    nBkgPass7 = hBkgPassCat->GetEntries();
    tBkg->Draw("Tau_GenEleMatch>>hBkgPassCat",Cut*"Category==8");
    nBkgPass8 = hBkgPassCat->GetEntries();
    tBkg->Draw("Tau_GenEleMatch>>hBkgPassCat",Cut*"Category==9");
    nBkgPass9 = hBkgPassCat->GetEntries();
    tBkg->Draw("Tau_GenEleMatch>>hBkgPassCat",Cut*"Category==10");
    nBkgPass10 = hBkgPassCat->GetEntries();
    tBkg->Draw("Tau_GenEleMatch>>hBkgPassCat",Cut*"Category==11");
    nBkgPass11 = hBkgPassCat->GetEntries();
    tBkg->Draw("Tau_GenEleMatch>>hBkgPassCat",Cut*"Category==12");
    nBkgPass12 = hBkgPassCat->GetEntries();
    tBkg->Draw("Tau_GenEleMatch>>hBkgPassCat",Cut*"Category==13");
    nBkgPass13 = hBkgPassCat->GetEntries();
    tBkg->Draw("Tau_GenEleMatch>>hBkgPassCat",Cut*"Category==14");
    nBkgPass14 = hBkgPassCat->GetEntries();
    tBkg->Draw("Tau_GenEleMatch>>hBkgPassCat",Cut*"Category==15");
    nBkgPass15 = hBkgPassCat->GetEntries();

    tBkg->Draw("Tau_GenEleMatch>>hBkgPassCat",CutEleVeto*"Category==0");
    nBkgPassEleVeto0 = hBkgPassCat->GetEntries();
    tBkg->Draw("Tau_GenEleMatch>>hBkgPassCat",CutEleVeto*"Category==1");
    nBkgPassEleVeto1 = hBkgPassCat->GetEntries();
    tBkg->Draw("Tau_GenEleMatch>>hBkgPassCat",CutEleVeto*"Category==2");
    nBkgPassEleVeto2 = hBkgPassCat->GetEntries();
    tBkg->Draw("Tau_GenEleMatch>>hBkgPassCat",CutEleVeto*"Category==3");
    nBkgPassEleVeto3 = hBkgPassCat->GetEntries();
    tBkg->Draw("Tau_GenEleMatch>>hBkgPassCat",CutEleVeto*"Category==4");
    nBkgPassEleVeto4 = hBkgPassCat->GetEntries();
    tBkg->Draw("Tau_GenEleMatch>>hBkgPassCat",CutEleVeto*"Category==5");
    nBkgPassEleVeto5 = hBkgPassCat->GetEntries();
    tBkg->Draw("Tau_GenEleMatch>>hBkgPassCat",CutEleVeto*"Category==6");
    nBkgPassEleVeto6 = hBkgPassCat->GetEntries();
    tBkg->Draw("Tau_GenEleMatch>>hBkgPassCat",CutEleVeto*"Category==7");
    nBkgPassEleVeto7 = hBkgPassCat->GetEntries();
    tBkg->Draw("Tau_GenEleMatch>>hBkgPassCat",CutEleVeto*"Category==8");
    nBkgPassEleVeto8 = hBkgPassCat->GetEntries();
    tBkg->Draw("Tau_GenEleMatch>>hBkgPassCat",CutEleVeto*"Category==9");
    nBkgPassEleVeto9 = hBkgPassCat->GetEntries();
    tBkg->Draw("Tau_GenEleMatch>>hBkgPassCat",CutEleVeto*"Category==10");
    nBkgPassEleVeto10 = hBkgPassCat->GetEntries();
    tBkg->Draw("Tau_GenEleMatch>>hBkgPassCat",CutEleVeto*"Category==11");
    nBkgPassEleVeto11 = hBkgPassCat->GetEntries();
    tBkg->Draw("Tau_GenEleMatch>>hBkgPassCat",CutEleVeto*"Category==12");
    nBkgPassEleVeto12 = hBkgPassCat->GetEntries();
    tBkg->Draw("Tau_GenEleMatch>>hBkgPassCat",CutEleVeto*"Category==13");
    nBkgPassEleVeto13 = hBkgPassCat->GetEntries();
    tBkg->Draw("Tau_GenEleMatch>>hBkgPassCat",CutEleVeto*"Category==14");
    nBkgPassEleVeto14 = hBkgPassCat->GetEntries();
    tBkg->Draw("Tau_GenEleMatch>>hBkgPassCat",CutEleVeto*"Category==15");
    nBkgPassEleVeto15 = hBkgPassCat->GetEntries();
  }

  TH1F* hSigPass = new TH1F("hSigPass","",1,-10,10);
  tSig->Draw("Tau_GenEleMatch>>hSigPass",Cut);
  float nSigPass = hSigPass->GetEntries();
  tSig->Draw("Tau_GenEleMatch>>hSigPass",CutEleVeto);
  float nSigPassEleVeto = hSigPass->GetEntries();

  tSig->Draw("Tau_GenEleMatch>>hSigPass","Tau_LooseComb3HitsIso>0.5 && Tau_isInEcalCrack<0.5 &&  Tau_MatchElePassVeto<0.5 && Tau_AntiELooseMVA3>0.5");
  float nSigPassLooseMVA3EleVeto = hSigPass->GetEntries();
  tSig->Draw("Tau_GenEleMatch>>hSigPass","Tau_LooseComb3HitsIso>0.5 && Tau_isInEcalCrack<0.5 &&  Tau_AntiELooseMVA3>0.5");
  float nSigPassLooseMVA3= hSigPass->GetEntries();
  tSig->Draw("Tau_GenEleMatch>>hSigPass","Tau_LooseComb3HitsIso>0.5 && Tau_isInEcalCrack<0.5 &&  Tau_MatchElePassVeto<0.5 && Tau_AntiEMediumMVA3>0.5");
  float nSigPassMediumMVA3EleVeto = hSigPass->GetEntries();
  tSig->Draw("Tau_GenEleMatch>>hSigPass","Tau_LooseComb3HitsIso>0.5 && Tau_isInEcalCrack<0.5 &&  Tau_AntiEMediumMVA3>0.5");
  float nSigPassMediumMVA3= hSigPass->GetEntries();
  tSig->Draw("Tau_GenEleMatch>>hSigPass","Tau_LooseComb3HitsIso>0.5 && Tau_isInEcalCrack<0.5 &&  Tau_MatchElePassVeto<0.5 && Tau_AntiETightMVA3>0.5");
  float nSigPassTightMVA3EleVeto = hSigPass->GetEntries();
  tSig->Draw("Tau_GenEleMatch>>hSigPass","Tau_LooseComb3HitsIso>0.5 && Tau_isInEcalCrack<0.5 &&  Tau_AntiETightMVA3>0.5");
  float nSigPassTightMVA3= hSigPass->GetEntries();
  tSig->Draw("Tau_GenEleMatch>>hSigPass","Tau_LooseComb3HitsIso>0.5 && Tau_isInEcalCrack<0.5 &&  Tau_MatchElePassVeto<0.5 && Tau_AntiEVTightMVA3>0.5");
  float nSigPassVTightMVA3EleVeto = hSigPass->GetEntries();
  tSig->Draw("Tau_GenEleMatch>>hSigPass","Tau_LooseComb3HitsIso>0.5 && Tau_isInEcalCrack<0.5 &&  Tau_AntiEVTightMVA3>0.5");
  float nSigPassVTightMVA3= hSigPass->GetEntries();

  tSig->Draw("Tau_GenEleMatch>>hSigPass","Tau_LooseComb3HitsIso>0.5 && Tau_isInEcalCrack<0.5 &&  Tau_MatchElePassVeto<0.5 && Tau_AntiELoose>0.5");
  float nSigPassLooseEleVeto = hSigPass->GetEntries();
  tSig->Draw("Tau_GenEleMatch>>hSigPass","Tau_LooseComb3HitsIso>0.5 && Tau_isInEcalCrack<0.5 &&  Tau_AntiELoose>0.5");
  float nSigPassLoose = hSigPass->GetEntries();
  tSig->Draw("Tau_GenEleMatch>>hSigPass","Tau_LooseComb3HitsIso>0.5 && Tau_isInEcalCrack<0.5 &&  Tau_MatchElePassVeto<0.5 && Tau_AntiEMedium>0.5");
  float nSigPassMediumEleVeto = hSigPass->GetEntries();
  tSig->Draw("Tau_GenEleMatch>>hSigPass","Tau_LooseComb3HitsIso>0.5 && Tau_isInEcalCrack<0.5 &&  Tau_AntiEMedium>0.5");
  float nSigPassMedium = hSigPass->GetEntries(); 
  tSig->Draw("Tau_GenEleMatch>>hSigPass","Tau_LooseComb3HitsIso>0.5 && Tau_isInEcalCrack<0.5 &&  Tau_MatchElePassVeto<0.5 && Tau_AntiETight>0.5");
  float nSigPassTightEleVeto = hSigPass->GetEntries();
  tSig->Draw("Tau_GenEleMatch>>hSigPass","Tau_LooseComb3HitsIso>0.5 && Tau_isInEcalCrack<0.5 &&  Tau_AntiETight>0.5");
  float nSigPassTight = hSigPass->GetEntries();

  TH1F* hBkgPass = new TH1F("hBkgPass","",1,-10,10);
  tBkg->Draw("Tau_GenEleMatch>>hBkgPass",Cut);
  float nBkgPass = hBkgPass->GetEntries();
  tBkg->Draw("Tau_GenEleMatch>>hBkgPass",CutEleVeto);
  float nBkgPassEleVeto = hBkgPass->GetEntries();

  tBkg->Draw("Tau_GenEleMatch>>hBkgPass","Tau_LooseComb3HitsIso>0.5 && Tau_isInEcalCrack<0.5 &&  Tau_MatchElePassVeto<0.5 && Tau_AntiELooseMVA3>0.5");
  float nBkgPassLooseMVA3EleVeto = hBkgPass->GetEntries();
  tBkg->Draw("Tau_GenEleMatch>>hBkgPass","Tau_LooseComb3HitsIso>0.5 && Tau_isInEcalCrack<0.5 &&  Tau_AntiELooseMVA3>0.5");
  float nBkgPassLooseMVA3= hBkgPass->GetEntries();
  tBkg->Draw("Tau_GenEleMatch>>hBkgPass","Tau_LooseComb3HitsIso>0.5 && Tau_isInEcalCrack<0.5 &&  Tau_MatchElePassVeto<0.5 && Tau_AntiEMediumMVA3>0.5");
  float nBkgPassMediumMVA3EleVeto = hBkgPass->GetEntries();
  tBkg->Draw("Tau_GenEleMatch>>hBkgPass","Tau_LooseComb3HitsIso>0.5 && Tau_isInEcalCrack<0.5 &&  Tau_AntiEMediumMVA3>0.5");
  float nBkgPassMediumMVA3= hBkgPass->GetEntries();
  tBkg->Draw("Tau_GenEleMatch>>hBkgPass","Tau_LooseComb3HitsIso>0.5 && Tau_isInEcalCrack<0.5 &&  Tau_MatchElePassVeto<0.5 && Tau_AntiETightMVA3>0.5");
  float nBkgPassTightMVA3EleVeto = hBkgPass->GetEntries();
  tBkg->Draw("Tau_GenEleMatch>>hBkgPass","Tau_LooseComb3HitsIso>0.5 && Tau_isInEcalCrack<0.5 &&  Tau_AntiETightMVA3>0.5");
  float nBkgPassTightMVA3= hBkgPass->GetEntries();
  tBkg->Draw("Tau_GenEleMatch>>hBkgPass","Tau_LooseComb3HitsIso>0.5 && Tau_isInEcalCrack<0.5 &&  Tau_MatchElePassVeto<0.5 && Tau_AntiEVTightMVA3>0.5");
  float nBkgPassVTightMVA3EleVeto = hBkgPass->GetEntries();
  tBkg->Draw("Tau_GenEleMatch>>hBkgPass","Tau_LooseComb3HitsIso>0.5 && Tau_isInEcalCrack<0.5 &&  Tau_AntiEVTightMVA3>0.5");
  float nBkgPassVTightMVA3= hBkgPass->GetEntries();

  tBkg->Draw("Tau_GenEleMatch>>hBkgPass","Tau_LooseComb3HitsIso>0.5 && Tau_isInEcalCrack<0.5 &&  Tau_MatchElePassVeto<0.5 && Tau_AntiELoose>0.5");
  float nBkgPassLooseEleVeto = hBkgPass->GetEntries();
  tBkg->Draw("Tau_GenEleMatch>>hBkgPass","Tau_LooseComb3HitsIso>0.5 && Tau_isInEcalCrack<0.5 &&  Tau_AntiELoose>0.5");
  float nBkgPassLoose = hBkgPass->GetEntries();
  tBkg->Draw("Tau_GenEleMatch>>hBkgPass","Tau_LooseComb3HitsIso>0.5 && Tau_isInEcalCrack<0.5 &&  Tau_MatchElePassVeto<0.5 && Tau_AntiEMedium>0.5");
  float nBkgPassMediumEleVeto = hBkgPass->GetEntries();
  tBkg->Draw("Tau_GenEleMatch>>hBkgPass","Tau_LooseComb3HitsIso>0.5 && Tau_isInEcalCrack<0.5 &&  Tau_AntiEMedium>0.5");
  float nBkgPassMedium = hBkgPass->GetEntries(); 
  tBkg->Draw("Tau_GenEleMatch>>hBkgPass","Tau_LooseComb3HitsIso>0.5 && Tau_isInEcalCrack<0.5 &&  Tau_MatchElePassVeto<0.5 && Tau_AntiETight>0.5");
  float nBkgPassTightEleVeto = hBkgPass->GetEntries();
  tBkg->Draw("Tau_GenEleMatch>>hBkgPass","Tau_LooseComb3HitsIso>0.5 && Tau_isInEcalCrack<0.5 &&  Tau_AntiETight>0.5");
  float nBkgPassTight = hBkgPass->GetEntries();

  if (DEBUG){
//     if(details){
//       cout<<"============================"<<endl;
//       cout<<"============================"<<endl;
      cout<<"Proba (Cat) No EleVeto : "<<endl;
      cout<<"Taus: "<<endl;
      cout<<"ProbaSig 0 :"<<nSig0/nSig<<endl;
      cout<<"ProbaSig 1 :"<<nSig1/nSig<<endl;
      cout<<"ProbaSig 2 :"<<nSig2/nSig<<endl;
      cout<<"ProbaSig 3 :"<<nSig3/nSig<<endl;
      cout<<"ProbaSig 4 :"<<nSig4/nSig<<endl;
      cout<<"ProbaSig 5 :"<<nSig5/nSig<<endl;
      cout<<"ProbaSig 6 :"<<nSig6/nSig<<endl;
      cout<<"ProbaSig 7 :"<<nSig7/nSig<<endl;
      cout<<"ProbaSig 8 :"<<nSig8/nSig<<endl;
      cout<<"ProbaSig 9 :"<<nSig9/nSig<<endl;
      cout<<"ProbaSig 10 :"<<nSig10/nSig<<endl;
      cout<<"ProbaSig 11 :"<<nSig11/nSig<<endl;
      cout<<"ProbaSig 12 :"<<nSig12/nSig<<endl;
      cout<<"ProbaSig 13 :"<<nSig13/nSig<<endl;
      cout<<"ProbaSig 14 :"<<nSig14/nSig<<endl;
      cout<<"ProbaSig 15 :"<<nSig15/nSig<<endl;
      cout<<"Total : "<<(nSig0+nSig1+nSig2+nSig3+nSig4+nSig5+nSig6+nSig7+nSig8+nSig9+nSig10+nSig11+nSig12+nSig13+nSig14+nSig15)/nSig<<endl;
      cout<<"Electrons: "<<endl;
      cout<<"ProbaBkg 0 :"<<nBkg0/nBkg<<endl;
      cout<<"ProbaBkg 1 :"<<nBkg1/nBkg<<endl;
      cout<<"ProbaBkg 2 :"<<nBkg2/nBkg<<endl;
      cout<<"ProbaBkg 3 :"<<nBkg3/nBkg<<endl;
      cout<<"ProbaBkg 4 :"<<nBkg4/nBkg<<endl;
      cout<<"ProbaBkg 5 :"<<nBkg5/nBkg<<endl;
      cout<<"ProbaBkg 6 :"<<nBkg6/nBkg<<endl;
      cout<<"ProbaBkg 7 :"<<nBkg7/nBkg<<endl;
      cout<<"ProbaBkg 8 :"<<nBkg8/nBkg<<endl;
      cout<<"ProbaBkg 9 :"<<nBkg9/nBkg<<endl;
      cout<<"ProbaBkg 10 :"<<nBkg10/nBkg<<endl;
      cout<<"ProbaBkg 11 :"<<nBkg11/nBkg<<endl;
      cout<<"ProbaBkg 12 :"<<nBkg12/nBkg<<endl;
      cout<<"ProbaBkg 13 :"<<nBkg13/nBkg<<endl;
      cout<<"ProbaBkg 14 :"<<nBkg14/nBkg<<endl;
      cout<<"ProbaBkg 15 :"<<nBkg15/nBkg<<endl;
      cout<<"Total : "<<(nBkg0+nBkg1+nBkg2+nBkg3+nBkg4+nBkg5+nBkg6+nBkg7+nBkg8+nBkg9+nBkg10+nBkg11+nBkg12+nBkg13+nBkg14+nBkg15)/nBkg<<endl;
      cout<<endl;
//       cout<<"Eff for each category : "<<endl;
//       cout<<"Eff0*probaSig0 :"<<nSigPass0/nSig0<<"*"<<nSig0/nSig<<" = "<<nSigPass0/nSig<<endl;
//       cout<<"Eff1*probaSig1 :"<<nSigPass1/nSig1<<"*"<<nSig1/nSig<<" = "<<nSigPass1/nSig<<endl;
//       cout<<"Eff2*probaSig2 :"<<nSigPass2/nSig2<<"*"<<nSig2/nSig<<" = "<<nSigPass2/nSig<<endl;
//       cout<<"Eff3*probaSig3 :"<<nSigPass3/nSig3<<"*"<<nSig3/nSig<<" = "<<nSigPass3/nSig<<endl;
//       cout<<"Eff4*probaSig4 :"<<nSigPass4/nSig4<<"*"<<nSig4/nSig<<" = "<<nSigPass4/nSig<<endl;
//       cout<<"Eff5*probaSig5 :"<<nSigPass5/nSig5<<"*"<<nSig5/nSig<<" = "<<nSigPass5/nSig<<endl;
//       cout<<"Eff6*probaSig6 :"<<nSigPass6/nSig6<<"*"<<nSig6/nSig<<" = "<<nSigPass6/nSig<<endl;
//       cout<<"Eff7*probaSig7 :"<<nSigPass7/nSig7<<"*"<<nSig7/nSig<<" = "<<nSigPass7/nSig<<endl;
//       cout<<"Eff8*probaSig8 :"<<nSigPass8/nSig8<<"*"<<nSig8/nSig<<" = "<<nSigPass8/nSig<<endl;
//       cout<<"Eff9*probaSig9 :"<<nSigPass9/nSig9<<"*"<<nSig9/nSig<<" = "<<nSigPass9/nSig<<endl;
//       cout<<"Eff10*probaSig10 :"<<nSigPass10/nSig10<<"*"<<nSig10/nSig<<" = "<<nSigPass10/nSig<<endl;
//       cout<<"Eff11*probaSig11 :"<<nSigPass11/nSig11<<"*"<<nSig11/nSig<<" = "<<nSigPass11/nSig<<endl;
//       cout<<"Eff12*probaSig12 :"<<nSigPass12/nSig12<<"*"<<nSig12/nSig<<" = "<<nSigPass12/nSig<<endl;
//       cout<<"Eff13*probaSig13 :"<<nSigPass13/nSig13<<"*"<<nSig13/nSig<<" = "<<nSigPass13/nSig<<endl;
//       cout<<"Eff14*probaSig14 :"<<nSigPass14/nSig14<<"*"<<nSig14/nSig<<" = "<<nSigPass14/nSig<<endl;
//       cout<<"Eff15*probaSig15 :"<<nSigPass15/nSig15<<"*"<<nSig15/nSig<<" = "<<nSigPass15/nSig<<endl;
//       cout<<"Total : "<<(nSigPass0+nSigPass1+nSigPass2+nSigPass3+nSigPass4+nSigPass5+nSigPass6+nSigPass7+nSigPass8+nSigPass9+nSigPass10+nSigPass11+nSigPass12+nSigPass13+nSigPass14+nSigPass15)/nSig<<endl;
//       cout<<"FR for each category : "<<endl;
//       cout<<"FR0*probaBkg0 :"<<nBkgPass0/nBkg0<<"*"<<nBkg0/nBkg<<" = "<<nBkgPass0/nBkg<<endl;
//       cout<<"FR1*probaBkg1 :"<<nBkgPass1/nBkg1<<"*"<<nBkg1/nBkg<<" = "<<nBkgPass1/nBkg<<endl;
//       cout<<"FR2*probaBkg2 :"<<nBkgPass2/nBkg2<<"*"<<nBkg2/nBkg<<" = "<<nBkgPass2/nBkg<<endl;
//       cout<<"FR3*probaBkg3 :"<<nBkgPass3/nBkg3<<"*"<<nBkg3/nBkg<<" = "<<nBkgPass3/nBkg<<endl;
//       cout<<"FR4*probaBkg4 :"<<nBkgPass4/nBkg4<<"*"<<nBkg4/nBkg<<" = "<<nBkgPass4/nBkg<<endl;
//       cout<<"FR5*probaBkg5 :"<<nBkgPass5/nBkg5<<"*"<<nBkg5/nBkg<<" = "<<nBkgPass5/nBkg<<endl;
//       cout<<"FR6*probaBkg6 :"<<nBkgPass6/nBkg6<<"*"<<nBkg6/nBkg<<" = "<<nBkgPass6/nBkg<<endl;
//       cout<<"FR7*probaBkg7 :"<<nBkgPass7/nBkg7<<"*"<<nBkg7/nBkg<<" = "<<nBkgPass7/nBkg<<endl;
//       cout<<"FR8*probaBkg8 :"<<nBkgPass8/nBkg8<<"*"<<nBkg8/nBkg<<" = "<<nBkgPass8/nBkg<<endl;
//       cout<<"FR9*probaBkg9 :"<<nBkgPass9/nBkg9<<"*"<<nBkg9/nBkg<<" = "<<nBkgPass9/nBkg<<endl;
//       cout<<"FR10*probaBkg10 :"<<nBkgPass10/nBkg10<<"*"<<nBkg10/nBkg<<" = "<<nBkgPass10/nBkg<<endl;
//       cout<<"FR11*probaBkg11 :"<<nBkgPass11/nBkg11<<"*"<<nBkg11/nBkg<<" = "<<nBkgPass11/nBkg<<endl;
//       cout<<"FR12*probaBkg12 :"<<nBkgPass12/nBkg12<<"*"<<nBkg12/nBkg<<" = "<<nBkgPass12/nBkg<<endl;
//       cout<<"FR13*probaBkg13 :"<<nBkgPass13/nBkg13<<"*"<<nBkg13/nBkg<<" = "<<nBkgPass13/nBkg<<endl;
//       cout<<"FR14*probaBkg14 :"<<nBkgPass14/nBkg14<<"*"<<nBkg14/nBkg<<" = "<<nBkgPass14/nBkg<<endl;
//       cout<<"FR15*probaBkg15 :"<<nBkgPass15/nBkg15<<"*"<<nBkg15/nBkg<<" = "<<nBkgPass15/nBkg<<endl;
//       cout<<"Total : "<<(nBkgPass0+nBkgPass1+nBkgPass2+nBkgPass3+nBkgPass4+nBkgPass5+nBkgPass6+nBkgPass7+nBkgPass8+nBkgPass9+nBkgPass10+nBkgPass11+nBkgPass12+nBkgPass13+nBkgPass14+nBkgPass15)/nBkg<<endl;
//     }





    if(details){
      cout<<"============================"<<endl;
      cout<<"============================"<<endl;
      cout<<"Proba (Cat) EleVeto: "<<endl;
      cout<<"Taus: "<<endl;
      cout<<"ProbaSig 0 :"<<nSigEleVeto0<<"/"<<nSigEleVeto<<" = "<<nSigEleVeto0/nSigEleVeto<<endl;
      cout<<"ProbaSig 1 :"<<nSigEleVeto1<<"/"<<nSigEleVeto<<" = "<<nSigEleVeto1/nSigEleVeto<<endl;
      cout<<"ProbaSig 2 :"<<nSigEleVeto2<<"/"<<nSigEleVeto<<" = "<<nSigEleVeto2/nSigEleVeto<<endl;
      cout<<"ProbaSig 3 :"<<nSigEleVeto3<<"/"<<nSigEleVeto<<" = "<<nSigEleVeto3/nSigEleVeto<<endl;
      cout<<"ProbaSig 4 :"<<nSigEleVeto4<<"/"<<nSigEleVeto<<" = "<<nSigEleVeto4/nSigEleVeto<<endl;
      cout<<"ProbaSig 5 :"<<nSigEleVeto5<<"/"<<nSigEleVeto<<" = "<<nSigEleVeto5/nSigEleVeto<<endl;
      cout<<"ProbaSig 6 :"<<nSigEleVeto6<<"/"<<nSigEleVeto<<" = "<<nSigEleVeto6/nSigEleVeto<<endl;
      cout<<"ProbaSig 7 :"<<nSigEleVeto7<<"/"<<nSigEleVeto<<" = "<<nSigEleVeto7/nSigEleVeto<<endl;
      cout<<"ProbaSig 8 :"<<nSigEleVeto8<<"/"<<nSigEleVeto<<" = "<<nSigEleVeto8/nSigEleVeto<<endl;
      cout<<"ProbaSig 9 :"<<nSigEleVeto9<<"/"<<nSigEleVeto<<" = "<<nSigEleVeto9/nSigEleVeto<<endl;
      cout<<"ProbaSig 10 :"<<nSigEleVeto10<<"/"<<nSigEleVeto<<" = "<<nSigEleVeto10/nSigEleVeto<<endl;
      cout<<"ProbaSig 11 :"<<nSigEleVeto11<<"/"<<nSigEleVeto<<" = "<<nSigEleVeto11/nSigEleVeto<<endl;
      cout<<"ProbaSig 12 :"<<nSigEleVeto12<<"/"<<nSigEleVeto<<" = "<<nSigEleVeto12/nSigEleVeto<<endl;
      cout<<"ProbaSig 13 :"<<nSigEleVeto13<<"/"<<nSigEleVeto<<" = "<<nSigEleVeto13/nSigEleVeto<<endl;
      cout<<"ProbaSig 14 :"<<nSigEleVeto14<<"/"<<nSigEleVeto<<" = "<<nSigEleVeto14/nSigEleVeto<<endl;
      cout<<"ProbaSig 15 :"<<nSigEleVeto15<<"/"<<nSigEleVeto<<" = "<<nSigEleVeto15/nSigEleVeto<<endl;
      cout<<"Total : "<<(nSigEleVeto0+nSigEleVeto1+nSigEleVeto2+nSigEleVeto3+nSigEleVeto4+nSigEleVeto5+nSigEleVeto6+nSigEleVeto7+nSigEleVeto8+nSigEleVeto9+nSigEleVeto10+nSigEleVeto11+nSigEleVeto12+nSigEleVeto13+nSigEleVeto14+nSigEleVeto15)/nSigEleVeto<<endl;
      cout<<"Electrons: "<<endl;
      cout<<"ProbaBkg 0 :"<<nBkgEleVeto0<<"/"<<nBkgEleVeto<<" = "<<nBkgEleVeto0/nBkgEleVeto<<endl;
      cout<<"ProbaBkg 1 :"<<nBkgEleVeto1<<"/"<<nBkgEleVeto<<" = "<<nBkgEleVeto1/nBkgEleVeto<<endl;
      cout<<"ProbaBkg 2 :"<<nBkgEleVeto2<<"/"<<nBkgEleVeto<<" = "<<nBkgEleVeto2/nBkgEleVeto<<endl;
      cout<<"ProbaBkg 3 :"<<nBkgEleVeto3<<"/"<<nBkgEleVeto<<" = "<<nBkgEleVeto3/nBkgEleVeto<<endl;
      cout<<"ProbaBkg 4 :"<<nBkgEleVeto4<<"/"<<nBkgEleVeto<<" = "<<nBkgEleVeto4/nBkgEleVeto<<endl;
      cout<<"ProbaBkg 5 :"<<nBkgEleVeto5<<"/"<<nBkgEleVeto<<" = "<<nBkgEleVeto5/nBkgEleVeto<<endl;
      cout<<"ProbaBkg 6 :"<<nBkgEleVeto6<<"/"<<nBkgEleVeto<<" = "<<nBkgEleVeto6/nBkgEleVeto<<endl;
      cout<<"ProbaBkg 7 :"<<nBkgEleVeto7<<"/"<<nBkgEleVeto<<" = "<<nBkgEleVeto7/nBkgEleVeto<<endl;
      cout<<"ProbaBkg 8 :"<<nBkgEleVeto8<<"/"<<nBkgEleVeto<<" = "<<nBkgEleVeto8/nBkgEleVeto<<endl;
      cout<<"ProbaBkg 9 :"<<nBkgEleVeto9<<"/"<<nBkgEleVeto<<" = "<<nBkgEleVeto9/nBkgEleVeto<<endl;
      cout<<"ProbaBkg 10 :"<<nBkgEleVeto10<<"/"<<nBkgEleVeto<<" = "<<nBkgEleVeto10/nBkgEleVeto<<endl;
      cout<<"ProbaBkg 11 :"<<nBkgEleVeto11<<"/"<<nBkgEleVeto<<" = "<<nBkgEleVeto11/nBkgEleVeto<<endl;
      cout<<"ProbaBkg 12 :"<<nBkgEleVeto12<<"/"<<nBkgEleVeto<<" = "<<nBkgEleVeto12/nBkgEleVeto<<endl;
      cout<<"ProbaBkg 13 :"<<nBkgEleVeto13<<"/"<<nBkgEleVeto<<" = "<<nBkgEleVeto13/nBkgEleVeto<<endl;
      cout<<"ProbaBkg 14 :"<<nBkgEleVeto14<<"/"<<nBkgEleVeto<<" = "<<nBkgEleVeto14/nBkgEleVeto<<endl;
      cout<<"ProbaBkg 15 :"<<nBkgEleVeto15<<"/"<<nBkgEleVeto<<" = "<<nBkgEleVeto15/nBkgEleVeto<<endl;
      cout<<"Total : "<<(nBkgEleVeto0+nBkgEleVeto1+nBkgEleVeto2+nBkgEleVeto3+nBkgEleVeto4+nBkgEleVeto5+nBkgEleVeto6+nBkgEleVeto7+nBkgEleVeto8+nBkgEleVeto9+nBkgEleVeto10+nBkgEleVeto11+nBkgEleVeto12+nBkgEleVeto13+nBkgEleVeto14+nBkgEleVeto15)/nBkgEleVeto<<endl;
      cout<<endl;
      cout<<"Eff for each category : "<<endl;
      cout<<"Eff0*probaSig0 :"<<nSigPassEleVeto0/nSigEleVeto0<<"*"<<nSigEleVeto0/nSigEleVeto<<" = "<<nSigPassEleVeto0/nSigEleVeto<<endl;
      cout<<"Eff1*probaSig1 :"<<nSigPassEleVeto1/nSigEleVeto1<<"*"<<nSigEleVeto1/nSigEleVeto<<" = "<<nSigPassEleVeto1/nSigEleVeto<<endl;
      cout<<"Eff2*probaSig2 :"<<nSigPassEleVeto2/nSigEleVeto2<<"*"<<nSigEleVeto2/nSigEleVeto<<" = "<<nSigPassEleVeto2/nSigEleVeto<<endl;
      cout<<"Eff3*probaSig3 :"<<nSigPassEleVeto3/nSigEleVeto3<<"*"<<nSigEleVeto3/nSigEleVeto<<" = "<<nSigPassEleVeto3/nSigEleVeto<<endl;
      cout<<"Eff4*probaSig4 :"<<nSigPassEleVeto4/nSigEleVeto4<<"*"<<nSigEleVeto4/nSigEleVeto<<" = "<<nSigPassEleVeto4/nSigEleVeto<<endl;
      cout<<"Eff5*probaSig5 :"<<nSigPassEleVeto5/nSigEleVeto5<<"*"<<nSigEleVeto5/nSigEleVeto<<" = "<<nSigPassEleVeto5/nSigEleVeto<<endl;
      cout<<"Eff6*probaSig6 :"<<nSigPassEleVeto6/nSigEleVeto6<<"*"<<nSigEleVeto6/nSigEleVeto<<" = "<<nSigPassEleVeto6/nSigEleVeto<<endl;
      cout<<"Eff7*probaSig7 :"<<nSigPassEleVeto7/nSigEleVeto7<<"*"<<nSigEleVeto7/nSigEleVeto<<" = "<<nSigPassEleVeto7/nSigEleVeto<<endl;
      cout<<"Eff8*probaSig8 :"<<nSigPassEleVeto8/nSigEleVeto8<<"*"<<nSigEleVeto8/nSigEleVeto<<" = "<<nSigPassEleVeto8/nSigEleVeto<<endl;
      cout<<"Eff9*probaSig9 :"<<nSigPassEleVeto9/nSigEleVeto9<<"*"<<nSigEleVeto9/nSigEleVeto<<" = "<<nSigPassEleVeto9/nSigEleVeto<<endl;
      cout<<"Eff10*probaSig10 :"<<nSigPassEleVeto10/nSigEleVeto10<<"*"<<nSigEleVeto10/nSigEleVeto<<" = "<<nSigPassEleVeto10/nSigEleVeto<<endl;
      cout<<"Eff11*probaSig11 :"<<nSigPassEleVeto11/nSigEleVeto11<<"*"<<nSigEleVeto11/nSigEleVeto<<" = "<<nSigPassEleVeto11/nSigEleVeto<<endl;
      cout<<"Eff12*probaSig12 :"<<nSigPassEleVeto12/nSigEleVeto12<<"*"<<nSigEleVeto12/nSigEleVeto<<" = "<<nSigPassEleVeto12/nSigEleVeto<<endl;
      cout<<"Eff13*probaSig13 :"<<nSigPassEleVeto13/nSigEleVeto13<<"*"<<nSigEleVeto13/nSigEleVeto<<" = "<<nSigPassEleVeto13/nSigEleVeto<<endl;
      cout<<"Eff14*probaSig14 :"<<nSigPassEleVeto14/nSigEleVeto14<<"*"<<nSigEleVeto14/nSigEleVeto<<" = "<<nSigPassEleVeto14/nSigEleVeto<<endl;
      cout<<"Eff15*probaSig15 :"<<nSigPassEleVeto15/nSigEleVeto15<<"*"<<nSigEleVeto15/nSigEleVeto<<" = "<<nSigPassEleVeto15/nSigEleVeto<<endl;
      cout<<"Total : "<<(nSigPassEleVeto0+nSigPassEleVeto1+nSigPassEleVeto2+nSigPassEleVeto3+nSigPassEleVeto4+nSigPassEleVeto5+nSigPassEleVeto6+nSigPassEleVeto7+nSigPassEleVeto8+nSigPassEleVeto9+nSigPassEleVeto10+nSigPassEleVeto11+nSigPassEleVeto12+nSigPassEleVeto13+nSigPassEleVeto14+nSigPassEleVeto15)/nSigEleVeto<<endl;
      cout<<"FR for each category : "<<endl;
      cout<<"FR0*probaBkg0 :"<<nBkgPassEleVeto0/nBkgEleVeto0<<"*"<<nBkgEleVeto0/nBkgEleVeto<<" = "<<nBkgPassEleVeto0/nBkgEleVeto<<endl;
      cout<<"FR1*probaBkg1 :"<<nBkgPassEleVeto1/nBkgEleVeto1<<"*"<<nBkgEleVeto1/nBkgEleVeto<<" = "<<nBkgPassEleVeto1/nBkgEleVeto<<endl;
      cout<<"FR2*probaBkg2 :"<<nBkgPassEleVeto2/nBkgEleVeto2<<"*"<<nBkgEleVeto2/nBkgEleVeto<<" = "<<nBkgPassEleVeto2/nBkgEleVeto<<endl;
      cout<<"FR3*probaBkg3 :"<<nBkgPassEleVeto3/nBkgEleVeto3<<"*"<<nBkgEleVeto3/nBkgEleVeto<<" = "<<nBkgPassEleVeto3/nBkgEleVeto<<endl;
      cout<<"FR4*probaBkg4 :"<<nBkgPassEleVeto4/nBkgEleVeto4<<"*"<<nBkgEleVeto4/nBkgEleVeto<<" = "<<nBkgPassEleVeto4/nBkgEleVeto<<endl;
      cout<<"FR5*probaBkg5 :"<<nBkgPassEleVeto5/nBkgEleVeto5<<"*"<<nBkgEleVeto5/nBkgEleVeto<<" = "<<nBkgPassEleVeto5/nBkgEleVeto<<endl;
      cout<<"FR6*probaBkg6 :"<<nBkgPassEleVeto6/nBkgEleVeto6<<"*"<<nBkgEleVeto6/nBkgEleVeto<<" = "<<nBkgPassEleVeto6/nBkgEleVeto<<endl;
      cout<<"FR7*probaBkg7 :"<<nBkgPassEleVeto7/nBkgEleVeto7<<"*"<<nBkgEleVeto7/nBkgEleVeto<<" = "<<nBkgPassEleVeto7/nBkgEleVeto<<endl;
      cout<<"FR8*probaBkg8 :"<<nBkgPassEleVeto8/nBkgEleVeto8<<"*"<<nBkgEleVeto8/nBkgEleVeto<<" = "<<nBkgPassEleVeto8/nBkgEleVeto<<endl;
      cout<<"FR9*probaBkg9 :"<<nBkgPassEleVeto9/nBkgEleVeto9<<"*"<<nBkgEleVeto9/nBkgEleVeto<<" = "<<nBkgPassEleVeto9/nBkgEleVeto<<endl;
      cout<<"FR10*probaBkg10 :"<<nBkgPassEleVeto10/nBkgEleVeto10<<"*"<<nBkgEleVeto10/nBkgEleVeto<<" = "<<nBkgPassEleVeto10/nBkgEleVeto<<endl;
      cout<<"FR11*probaBkg11 :"<<nBkgPassEleVeto11/nBkgEleVeto11<<"*"<<nBkgEleVeto11/nBkgEleVeto<<" = "<<nBkgPassEleVeto11/nBkgEleVeto<<endl;
      cout<<"FR12*probaBkg12 :"<<nBkgPassEleVeto12/nBkgEleVeto12<<"*"<<nBkgEleVeto12/nBkgEleVeto<<" = "<<nBkgPassEleVeto12/nBkgEleVeto<<endl;
      cout<<"FR13*probaBkg13 :"<<nBkgPassEleVeto13/nBkgEleVeto13<<"*"<<nBkgEleVeto13/nBkgEleVeto<<" = "<<nBkgPassEleVeto13/nBkgEleVeto<<endl;
      cout<<"FR14*probaBkg14 :"<<nBkgPassEleVeto14/nBkgEleVeto14<<"*"<<nBkgEleVeto14/nBkgEleVeto<<" = "<<nBkgPassEleVeto14/nBkgEleVeto<<endl;
      cout<<"FR15*probaBkg15 :"<<nBkgPassEleVeto15/nBkgEleVeto15<<"*"<<nBkgEleVeto15/nBkgEleVeto<<" = "<<nBkgPassEleVeto15/nBkgEleVeto<<endl;
      cout<<"Total : "<<(nBkgPassEleVeto0+nBkgPassEleVeto1+nBkgPassEleVeto2+nBkgPassEleVeto3+nBkgPassEleVeto4+nBkgPassEleVeto5+nBkgPassEleVeto6+nBkgPassEleVeto7+nBkgPassEleVeto8+nBkgPassEleVeto9+nBkgPassEleVeto10+nBkgPassEleVeto11+nBkgPassEleVeto12+nBkgPassEleVeto13+nBkgPassEleVeto14+nBkgPassEleVeto15)/nBkgEleVeto<<endl;
    }
  }
    cout<<endl;
    cout<<"============================"<<endl;
    cout<<"WP : "<<WP.data() <<endl;
    cout<<"Eff and FR : "<<endl;
    cout<<"============================"<<endl;
    cout<<"Eff and FR : "<<endl;
    cout<<"No secondEleVeto: "<<endl;
    cout<<" Efficiency -> "<<nSigPass/nSig<<endl;
    cout<<" Efficiency LooseMVA3-> "<<nSigPassLooseMVA3/nSig<<endl;
    cout<<" Efficiency MediumMVA3-> "<<nSigPassMediumMVA3/nSig<<endl;
    cout<<" Efficiency TightMVA3-> "<<nSigPassTightMVA3/nSig<<endl;
    cout<<" Efficiency VTightMVA3-> "<<nSigPassVTightMVA3/nSig<<endl;
    cout<<" Efficiency Loose-> "<<nSigPassLoose/nSig<<endl;
    cout<<" Efficiency Medium-> "<<nSigPassMedium/nSig<<endl;
    cout<<" Efficiency Tight-> "<<nSigPassTight/nSig<<endl;
    cout<<" FakeRate -> "<<nBkgPass/nBkg<<endl;
    cout<<" FakeRate LooseMVA3-> "<<nBkgPassLooseMVA3/nBkg<<endl;
    cout<<" FakeRate MediumMVA3-> "<<nBkgPassMediumMVA3/nBkg<<endl;
    cout<<" FakeRate TightMVA3-> "<<nBkgPassTightMVA3/nBkg<<endl;
    cout<<" FakeRate VTightMVA3-> "<<nBkgPassVTightMVA3/nBkg<<endl;
    cout<<" FakeRate Loose-> "<<nBkgPassLoose/nBkg<<endl;
    cout<<" FakeRate Medium-> "<<nBkgPassMedium/nBkg<<endl;
    cout<<" FakeRate Tight-> "<<nBkgPassTight/nBkg<<endl;
    cout<<endl;
    cout<<"============================"<<endl;
    cout<<"WP : "<<WP.data() <<endl;
    cout<<"Eff and FR : "<<endl;
    cout<<"After secondEleVeto: "<<endl;
    cout<<" Efficiency -> "<<nSigPassEleVeto/nSigEleVeto<<endl;
    cout<<" Efficiency LooseMVA3-> "<<nSigPassLooseMVA3EleVeto/nSigEleVeto<<endl;
    cout<<" Efficiency MediumMVA3-> "<<nSigPassMediumMVA3EleVeto/nSigEleVeto<<endl;
    cout<<" Efficiency TightMVA3-> "<<nSigPassTightMVA3EleVeto/nSigEleVeto<<endl;
    cout<<" Efficiency VTightMVA3-> "<<nSigPassVTightMVA3EleVeto/nSigEleVeto<<endl;
    cout<<" Efficiency Loose-> "<<nSigPassLooseEleVeto/nSigEleVeto<<endl;
    cout<<" Efficiency Medium-> "<<nSigPassMediumEleVeto/nSigEleVeto<<endl;
    cout<<" Efficiency Tight-> "<<nSigPassTightEleVeto/nSigEleVeto<<endl;
    cout<<" FakeRate -> "<<nBkgPassEleVeto/nBkgEleVeto<<endl;
    cout<<" FakeRate LooseMVA3-> "<<nBkgPassLooseMVA3EleVeto/nBkgEleVeto<<endl;
    cout<<" FakeRate MediumMVA3-> "<<nBkgPassMediumMVA3EleVeto/nBkgEleVeto<<endl;
    cout<<" FakeRate TightMVA3-> "<<nBkgPassTightMVA3EleVeto/nBkgEleVeto<<endl;
    cout<<" FakeRate VTightMVA3-> "<<nBkgPassVTightMVA3EleVeto/nBkgEleVeto<<endl;
    cout<<" FakeRate Loose-> "<<nBkgPassLooseEleVeto/nBkgEleVeto<<endl;
    cout<<" FakeRate Medium-> "<<nBkgPassMediumEleVeto/nBkgEleVeto<<endl;
    cout<<" FakeRate Tight-> "<<nBkgPassTightEleVeto/nBkgEleVeto<<endl;



//     cout<<"============================"<<endl;
//     cout<<"Proba to pass Second Ele Veto : "<<endl;
//     cout<<"Signal : "<<nSigEleVeto/nSig<<endl;
//     cout<<"Bkg : "<<nBkgEleVeto/nBkg<<endl;

//     cout<<"============================"<<endl;
//     cout<<"Proba to enterEcalCrack : "<<endl;
//     cout<<"Signal : "<<nSigCrack/nSig<<endl;
//     cout<<"Bkg : "<<nBkgCrack/nBkg<<endl;
//   }
  fSig->Close();
  fBkg->Close();

  return;
}

void computeAll()
{
//   compute("NewMediumHibWP",
// 	   0.933,
// 	   0.921,
// 	   0.944,
// 	   0.945,
// 	   0.918,
// 	   0.941,
// 	   0.981,
// 	   0.943,
// 	   0.956,
// 	   0.947,
// 	   0.951,
// 	   0.95,
// 	   0.897,
// 	   0.958,
// 	   0.955,
// 	   0.942);
//   compute("NewTightHibWP",
// 	   0.96,
// 	   0.968,
// 	   0.971,
// 	   0.972,
// 	   0.969,
// 	   0.959,
// 	   0.981,
// 	   0.965,
// 	   0.975,
// 	   0.972,
// 	   0.974,
// 	   0.971,
// 	   0.897,
// 	   0.971,
// 	   0.961,
// 	   0.97);
//   compute("LooseMVA3WP",
// 	   0.1816889,
// 	   0.1538533,
// 	   0.5605197,
// 	   0.66321647,
// 	   0.86337829,
// 	   0.94084531,
// 	   0.98025548,
// 	   0.80039471,
// 	   -1,
// 	   0.49787951,
// 	   0.74751109,
// 	   0.94486511,
// 	   0.63645148,
// 	   0.9575507,
// 	   0.9549247,
// 	   0.83487612
// 	   );
//   compute("MediumMVA3WP",
// 	   0.5577119,
// 	   0.7271899,
// 	   0.90410149,
// 	   0.94858187,
// 	   0.95044029,
// 	   0.97195327,
// 	   0.99229473,
// 	   0.92997772,
// 	   -0.3049897,
// 	   0.92191792,
// 	   0.96017671,
// 	   0.98126549,
// 	   0.80912107,
// 	   0.98326528,
// 	   0.97490251,
// 	   0.94708711
// 	   );
//   compute("TightMVA3WP",
// 	   0.78914332,
// 	   0.91818088,
// 	   0.96754968,
// 	   0.98437631,
// 	   0.96684271,
// 	   0.99065852,
// 	   0.99797088,
// 	   0.96952927,
// 	   0.1180589,
// 	   0.9714281,
// 	   0.98451769,
// 	   0.99372888,
// 	   0.84681427,
// 	   0.98940611,
// 	   0.98308349,
// 	   0.97482169
// 	   );
//   compute("VTightMVA3WP",
// 	   0.89307231,
// 	   0.96239871,
// 	   0.98247749,
// 	   0.99013329,
// 	   0.9768821,
// 	   0.9958095,
// 	   0.99797088,
// 	   0.98120493,
// 	   0.60025311,
// 	   0.98320472,
// 	   0.9897899,
// 	   0.9964357,
// 	   0.88230568,
// 	   0.99132508,
// 	   0.98467928,
// 	   0.98235631
// 	   );
//   compute("0p92",
// 	   0.92,
// 	   0.92,
// 	   0.92,
// 	   0.92,
// 	   0.92,
// 	   0.92,
// 	   0.92,
// 	   0.92,
// 	   0.92,
// 	   0.92,
// 	   0.92,
// 	   0.92,
// 	   0.92,
// 	   0.92,
// 	   0.92,
// 	   0.92
// 	   );

  //V18 ALL
/////signal efficiency = 0.750558, fake-rate = 0.0132861(S/B = 56.4919)
 compute("WP75",
	 0.99,
	 0.986,
	 0.986,
	 0.989,
	 0.98,
	 0.984,
	 0.99,
	 0.986,
	 0.986,
	 0.989,
	 0.988,
	 0.989,
	 0.969,
	 0.99,
	 0.983,
	 0.983
	 );

/////signal efficiency = 0.800246, fake-rate = 0.016803(S/B = 47.6252)
 compute("WP80",
	 0.986,
	 0.977,
	 0.98,
	 0.985,
	 0.977,
	 0.979,
	 0.983,
	 0.98,
	 0.982,
	 0.986,
	 0.984,
	 0.983,
	 0.968,
	 0.973,
	 0.981,
	 0.979
	 );

/////signal efficiency = 0.850139, fake-rate = 0.0222583(S/B = 38.1943)
 compute("WP85",
	 0.969,
	 0.967,
	 0.972,
	 0.974,
	 0.965,
	 0.966,
	 0.973,
	 0.971,
	 0.975,
	 0.972,
	 0.975,
	 0.975,
	 0.968,
	 0.972,
	 0.962,
	 0.971
	 );

 compute("WP90",
	   0.932,
	   0.944,
	   0.949,
	   0.949,
	   0.94,
	   0.935,
	   0.943,
	   0.951,
	   0.965,
	   0.959,
	   0.952,
	   0.954,
	   0.966,
	   0.963,
	   0.943,
	   0.958);

/////signal efficiency = 0.950017, fake-rate = 0.0557451(S/B = 17.0422)
 compute("WP95",
	 0.841,
	 0.853,
	 0.862,
	 0.864,
	 0.858,
	 0.838,
	 0.834,
	 0.864,
	 0.887,
	 0.866,
	 0.846,
	 0.869,
	 0.889,
	 0.857,
	 0.882,
	 0.863);


	   }
