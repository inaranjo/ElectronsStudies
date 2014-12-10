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

//   std::string fSigName = "/data_CMS/cms/ivo/AntiEMVA/Trees/MVAOutput/V10V11V12/MvaOutput_AntiEMVA-v11EleVeto-DYJetsIvo_Signal.root";
//   std::string fSigName = "/data_CMS/cms/ivo/AntiEMVA/Trees/MVAOutput/MvaOutput_AntiEMVA-v11DYEleVeto-DYJetsIvo_Signal.root";
//   std::string fSigName = "/data_CMS/cms/ivo/AntiEMVA/Trees/MVAOutput/MvaOutput_AntiEMVA-v11DYEleVeto-GeneralIvo_Signal.root";
//   std::string fSigName = "/data_CMS/cms/ivo/AntiEMVA/Trees/MVAOutput/MvaOutput_AntiEMVA-v12EleVeto-DYJetsIvo_Signal.root";
//   std::string fSigName = "/data_CMS/cms/ivo/AntiEMVA/Trees/MVAOutput/V13/MvaOutput_AntiEMVA-v13EleVeto-DYJets_Signal.root";
//   std::string fSigName = "/data_CMS/cms/ivo/AntiEMVA/Trees/MVAOutput/V13/MvaOutput_AntiEMVA-v13EleVeto-All_Signal.root";
  std::string fSigName = "/data_CMS/cms/ivo/AntiEMVANewTraining/MVAOutput/V14/MvaOutput_AntiEMVA-v14EleVeto-DYJets_Signal.root";
  TFile* fSig = new TFile (fSigName.data(),"READ") ;
  TTree* tSig = (TTree*)fSig->Get("tree");

//   std::string fBkgName = "/data_CMS/cms/ivo/AntiEMVA/Trees/MVAOutput/V10V11V12/MvaOutput_AntiEMVA-v11EleVeto-DYJetsIvo_Backgrd.root";
//   std::string fBkgName = "/data_CMS/cms/ivo/AntiEMVA/Trees/MVAOutput/MvaOutput_AntiEMVA-v11DYEleVeto-DYJetsIvo_Backgrd.root";
//   std::string fBkgName = "/data_CMS/cms/ivo/AntiEMVA/Trees/MVAOutput/MvaOutput_AntiEMVA-v11DYEleVeto-GeneralIvo_Backgrd.root";
//   std::string fBkgName = "/data_CMS/cms/ivo/AntiEMVA/Trees/MVAOutput/MvaOutput_AntiEMVA-v12EleVeto-DYJetsIvo_Backgrd.root";
//   std::string fBkgName = "/data_CMS/cms/ivo/AntiEMVA/Trees/MVAOutput/V13/MvaOutput_AntiEMVA-v13EleVeto-DYJets_Backgrd.root";
//   std::string fBkgName = "/data_CMS/cms/ivo/AntiEMVA/Trees/MVAOutput/V13/MvaOutput_AntiEMVA-v13EleVeto-All_Backgrd.root";
  std::string fSigName = "/data_CMS/cms/ivo/AntiEMVANewTraining/MVAOutput/V14/MvaOutput_AntiEMVA-v14EleVeto-DYJets_Backgrd.root";
  TFile* fBkg = new TFile (fBkgName.data(),"READ") ;
  TTree* tBkg = (TTree*)fBkg->Get("tree");

//   //v9EleVeto S/B :1 : Eff : 0.99652666 : FR : 0.60377842
//     float NoEleMatch_woGwoGSF_Barrel_Cut = -0.99514163;
//     float NoEleMatch_woGwGSF_Barrel_Cut = -0.99792099;
//     float NoEleMatch_wGwoGSF_Barrel_Cut = -0.99858534;
//     float NoEleMatch_wGwGSF_Barrel_Cut = -0.99970978;
//     float woGwoGSF_Barrel_Cut = -0.99570972;
//     float woGwGSF_Barrel_Cut = 0.007460949;
//     float wGwoGSF_Barrel_Cut = -0.27813321;
//     float wGwGSF_Barrel_Cut = -0.99918205;
//     float NoEleMatch_woGwoGSF_Endcap_Cut = -0.98613274;
//     float NoEleMatch_woGwGSF_Endcap_Cut = -0.99979705;
//     float NoEleMatch_wGwoGSF_Endcap_Cut = -0.57240993;
//     float NoEleMatch_wGwGSF_Endcap_Cut = -0.99989498;
//     float woGwoGSF_Endcap_Cut = -0.75940013;
//     float woGwGSF_Endcap_Cut = 0.3233715;
//     float wGwoGSF_Endcap_Cut = -0.22858185;
//     float wGwGSF_Endcap_Cut = -0.80000138;

  //v9EleVeto S/B :2 : Eff : 0.99138033 : FR : 0.37382454
  //   float NoEleMatch_woGwoGSF_Barrel_Cut = -0.99514163;
  //   float NoEleMatch_woGwGSF_Barrel_Cut = -0.99792099;
  //   float NoEleMatch_wGwoGSF_Barrel_Cut = -0.99858534;
  //   float NoEleMatch_wGwGSF_Barrel_Cut = -0.99970978;
  //   float woGwoGSF_Barrel_Cut = -0.34389529;
  //   float woGwGSF_Barrel_Cut = 0.50434816;
  //   float wGwoGSF_Barrel_Cut = 0.61492729;
  //   float wGwGSF_Barrel_Cut = -0.94620699;
  //   float NoEleMatch_woGwoGSF_Endcap_Cut = -0.6224522;
  //   float NoEleMatch_woGwGSF_Endcap_Cut = -0.99979705;
  //   float NoEleMatch_wGwoGSF_Endcap_Cut = -0.054619547;
  //   float NoEleMatch_wGwGSF_Endcap_Cut = -0.67392665;
  //   float woGwoGSF_Endcap_Cut = 0.36682361;
  //   float woGwGSF_Endcap_Cut = 0.65626621;
  //   float wGwoGSF_Endcap_Cut = 0.57953638;
  //   float wGwGSF_Endcap_Cut = -0.31554517;

//   //v9EleVeto  S/B :4 : Eff : 0.98009402 : FR : 0.21462926
//   float NoEleMatch_woGwoGSF_Barrel_Cut = -0.99514163;
//   float NoEleMatch_woGwGSF_Barrel_Cut = -0.99792099;
//   float NoEleMatch_wGwoGSF_Barrel_Cut = -0.99858534;
//   float NoEleMatch_wGwGSF_Barrel_Cut = -0.99970978;
//   float woGwoGSF_Barrel_Cut = 0.72124052;
//   float woGwGSF_Barrel_Cut = 0.78548437;
//   float wGwoGSF_Barrel_Cut = 0.86475259;
//   float wGwGSF_Barrel_Cut = -0.38946921;
//   float NoEleMatch_woGwoGSF_Endcap_Cut = 0.11682635;
//   float NoEleMatch_woGwGSF_Endcap_Cut = -0.99979705;
//   float NoEleMatch_wGwoGSF_Endcap_Cut = 0.40512887;
//   float NoEleMatch_wGwGSF_Endcap_Cut = 0.41516754;
//   float woGwoGSF_Endcap_Cut = 0.8345843;
//   float woGwGSF_Endcap_Cut = 0.83660918;
//   float wGwoGSF_Endcap_Cut = 0.8663137;
//   float wGwGSF_Endcap_Cut = 0.37145087;

//   //v9EleVeto  S/B :10 : Eff : 0.94370252 : FR : 0.094349712
//     float NoEleMatch_woGwoGSF_Barrel_Cut = 0.28400883;
//     float NoEleMatch_woGwGSF_Barrel_Cut = 0.42266643;
//     float NoEleMatch_wGwoGSF_Barrel_Cut = 0.075681731;
//     float NoEleMatch_wGwGSF_Barrel_Cut = 0.21887204;
//     float woGwoGSF_Barrel_Cut = 0.95214969;
//     float woGwGSF_Barrel_Cut = 0.92765212;
//     float wGwoGSF_Barrel_Cut = 0.96380407;
//     float wGwGSF_Barrel_Cut = 0.80316907;
//     float NoEleMatch_woGwoGSF_Endcap_Cut = 0.47315782;
//     float NoEleMatch_woGwGSF_Endcap_Cut = 0.43190524;
//     float NoEleMatch_wGwoGSF_Endcap_Cut = 0.79107821;
//     float NoEleMatch_wGwGSF_Endcap_Cut = 0.90272015;
//     float woGwoGSF_Endcap_Cut = 0.99030459;
//     float woGwGSF_Endcap_Cut = 0.95997018;
//     float wGwoGSF_Endcap_Cut = 0.97353137;
//     float wGwGSF_Endcap_Cut = 0.79732442;

// //   //v9EleVeto   S/B :12 : Eff : 0.9294309 : FR : 0.077419043
//   float NoEleMatch_woGwoGSF_Barrel_Cut = 0.66569889;
//   float NoEleMatch_woGwGSF_Barrel_Cut = 0.66882163;
//   float NoEleMatch_wGwoGSF_Barrel_Cut = 0.52157754;
//   float NoEleMatch_wGwGSF_Barrel_Cut = 0.61000198;
//   float woGwoGSF_Barrel_Cut = 0.97031105;
//   float woGwGSF_Barrel_Cut = 0.94224882;
//   float wGwoGSF_Barrel_Cut = 0.97159237;
//   float wGwGSF_Barrel_Cut = 0.86773866;
//   float NoEleMatch_woGwoGSF_Endcap_Cut = 0.5325464;
//   float NoEleMatch_woGwGSF_Endcap_Cut = 0.65089029;
//   float NoEleMatch_wGwoGSF_Endcap_Cut = 0.84772396;
//   float NoEleMatch_wGwGSF_Endcap_Cut = 0.93411714;
//   float woGwoGSF_Endcap_Cut = 0.99430257;
//   float woGwGSF_Endcap_Cut = 0.96756774;
//   float wGwoGSF_Endcap_Cut = 0.97731781;
//   float wGwGSF_Endcap_Cut = 0.84431046;

//   //v9EleVeto   S/B :15 : Eff : 0.90778679 : FR : 0.060457151
//     float NoEleMatch_woGwoGSF_Barrel_Cut = 0.79718542;
//     float NoEleMatch_woGwGSF_Barrel_Cut = 0.81807327;
//     float NoEleMatch_wGwoGSF_Barrel_Cut = 0.7624132;
//     float NoEleMatch_wGwGSF_Barrel_Cut = 0.81916457;
//     float woGwoGSF_Barrel_Cut = 0.98188645;
//     float woGwGSF_Barrel_Cut = 0.95684552;
//     float wGwoGSF_Barrel_Cut = 0.97698426;
//     float wGwGSF_Barrel_Cut = 0.91051853;
//     float NoEleMatch_woGwoGSF_Endcap_Cut = 0.59948266;
//     float NoEleMatch_woGwGSF_Endcap_Cut = 0.80407983;
//     float NoEleMatch_wGwoGSF_Endcap_Cut = 0.90476871;
//     float NoEleMatch_wGwGSF_Endcap_Cut = 0.95511508;
//     float woGwoGSF_Endcap_Cut = 0.99450243;
//     float woGwGSF_Endcap_Cut = 0.97456557;
//     float wGwoGSF_Endcap_Cut = 0.98469156;
//     float wGwGSF_Endcap_Cut = 0.89249617;
 

  // //v9EleVeto  S/B :20 : Eff : 0.86698782 : FR : 0.043293644
  //   float NoEleMatch_woGwoGSF_Barrel_Cut = 0.9029333;
  //   float NoEleMatch_woGwGSF_Barrel_Cut = 0.9049868;
  //   float NoEleMatch_wGwoGSF_Barrel_Cut = 0.88073248;
  //   float NoEleMatch_wGwGSF_Barrel_Cut = 0.92554551;
  //   float woGwoGSF_Barrel_Cut = 0.98847246;
  //   float woGwGSF_Barrel_Cut = 0.96664327;
  //   float wGwoGSF_Barrel_Cut = 0.98756844;
  //   float wGwGSF_Barrel_Cut = 0.94310313;
  //   float NoEleMatch_woGwoGSF_Endcap_Cut = 0.67893225;
  //   float NoEleMatch_woGwGSF_Endcap_Cut = 0.90747279;
  //   float NoEleMatch_wGwoGSF_Endcap_Cut = 0.95722586;
  //   float NoEleMatch_wGwGSF_Endcap_Cut = 0.97591305;
  //   float woGwoGSF_Endcap_Cut = 0.99470234;
  //   float woGwGSF_Endcap_Cut = 0.9839626;
  //   float wGwoGSF_Endcap_Cut = 0.99385887;
  //   float wGwGSF_Endcap_Cut = 0.93388391;

//   // //v9EleVeto   S/B :22 : Eff : 0.8498981 : FR : 0.038578156
//   float NoEleMatch_woGwoGSF_Barrel_Cut = 0.92587858;
//   float NoEleMatch_woGwGSF_Barrel_Cut = 0.92236954;
//   float NoEleMatch_wGwoGSF_Barrel_Cut = 0.90211791;
//   float NoEleMatch_wGwGSF_Barrel_Cut = 0.94194257;
//   float woGwoGSF_Barrel_Cut = 0.99066782;
//   float woGwGSF_Barrel_Cut = 0.97024244;
//   float wGwoGSF_Barrel_Cut = 0.9883672;
//   float wGwGSF_Barrel_Cut = 0.9502998;
//   float NoEleMatch_woGwoGSF_Endcap_Cut = 0.70594513;
//   float NoEleMatch_woGwGSF_Endcap_Cut = 0.92227179;
//   float NoEleMatch_wGwoGSF_Endcap_Cut = 0.96959221;
//   float NoEleMatch_wGwGSF_Endcap_Cut = 0.98011267;
//   float woGwoGSF_Endcap_Cut = 0.99470234;
//   float woGwGSF_Endcap_Cut = 0.98876107;
//   float wGwoGSF_Endcap_Cut = 0.99385887;
//   float wGwGSF_Endcap_Cut = 0.94548047;

  // // //v9EleVeto    S/B :25 : Eff : 0.82346207 : FR : 0.032893345
  //   float NoEleMatch_woGwoGSF_Barrel_Cut = 0.94503295;
  //   float NoEleMatch_woGwGSF_Barrel_Cut = 0.93955249;
  //   float NoEleMatch_wGwoGSF_Barrel_Cut = 0.92510223;
  //   float NoEleMatch_wGwGSF_Barrel_Cut = 0.95873958;
  //   float woGwoGSF_Barrel_Cut = 0.99386102;
  //   float woGwGSF_Barrel_Cut = 0.97584116;
  //   float wGwoGSF_Barrel_Cut = 0.9883672;
  //   float wGwGSF_Barrel_Cut = 0.95809609;
  //   float NoEleMatch_woGwoGSF_Endcap_Cut = 0.73355389;
  //   float NoEleMatch_woGwGSF_Endcap_Cut = 0.93907064;
  //   float NoEleMatch_wGwoGSF_Endcap_Cut = 0.97976452;
  //   float NoEleMatch_wGwGSF_Endcap_Cut = 0.98451221;
  //   float woGwoGSF_Endcap_Cut = 0.99470234;
  //   float woGwGSF_Endcap_Cut = 0.98916095;
  //   float wGwoGSF_Endcap_Cut = 0.99385887;
  //   float wGwGSF_Endcap_Cut = 0.95887649;

//   //v9EleVeto   S/B :30 : Eff : 0.77621508 : FR : 0.025833424
//     float NoEleMatch_woGwoGSF_Barrel_Cut = 0.95780247;
//     float NoEleMatch_woGwGSF_Barrel_Cut = 0.95773441;
//     float NoEleMatch_wGwoGSF_Barrel_Cut = 0.94928575;
//     float NoEleMatch_wGwGSF_Barrel_Cut = 0.97493666;
//     float woGwoGSF_Barrel_Cut = 0.99964869;
//     float woGwGSF_Barrel_Cut = 0.98403931;
//     float wGwoGSF_Barrel_Cut = 0.98876661;
//     float wGwGSF_Barrel_Cut = 0.9676916;
//     float NoEleMatch_woGwoGSF_Endcap_Cut = 0.77129245;
//     float NoEleMatch_woGwGSF_Endcap_Cut = 0.95826936;
//     float NoEleMatch_wGwoGSF_Endcap_Cut = 0.9915325;
//     float NoEleMatch_wGwGSF_Endcap_Cut = 0.99011171;
//     float woGwoGSF_Endcap_Cut = 0.99630153;
//     float woGwGSF_Endcap_Cut = 0.99235994;
//     float wGwoGSF_Endcap_Cut = 0.99385887;
//     float wGwGSF_Endcap_Cut = 0.97107285;

// // //   v9EleVeto  S/B :35 : Eff : 0.73212928 : FR : 0.020830903
//     float NoEleMatch_woGwoGSF_Barrel_Cut = 0.96438682;  
//     float NoEleMatch_woGwGSF_Barrel_Cut = 0.96952266;  
//     float NoEleMatch_wGwoGSF_Barrel_Cut = 0.96327621;  
//     float NoEleMatch_wGwGSF_Barrel_Cut = 0.98193538;  
//     float woGwoGSF_Barrel_Cut = 0.99964869;  
//     float woGwGSF_Barrel_Cut = 0.98843831;  
//     float wGwoGSF_Barrel_Cut = 0.99016452;  
//     float wGwGSF_Barrel_Cut = 0.97388864;
//     float NoEleMatch_woGwoGSF_Endcap_Cut = 0.80307227;  
//     float NoEleMatch_woGwGSF_Endcap_Cut = 0.97146845;  
//     float NoEleMatch_wGwoGSF_Endcap_Cut = 0.99651891;  
//     float NoEleMatch_wGwGSF_Endcap_Cut = 0.99311137;  
//     float woGwoGSF_Endcap_Cut = 0.99630153;  
//     float woGwGSF_Endcap_Cut = 0.99335963;  
//     float wGwoGSF_Endcap_Cut = 0.99585176;  
//     float wGwGSF_Endcap_Cut = 0.97847068;

// // //   v9EleVeto  S/B :40 : Eff : 0.69137436 : FR : 0.017240895
//     float NoEleMatch_woGwoGSF_Barrel_Cut = 0.96857679;
//     float NoEleMatch_woGwGSF_Barrel_Cut = 0.97611612;
//     float NoEleMatch_wGwoGSF_Barrel_Cut = 0.97306949;
//     float NoEleMatch_wGwGSF_Barrel_Cut = 0.98613465;
//     float woGwoGSF_Barrel_Cut = 0.99964869;
//     float woGwGSF_Barrel_Cut = 0.99043787;
//     float wGwoGSF_Barrel_Cut = 0.99156243;
//     float wGwGSF_Barrel_Cut = 0.97848648;
//     float NoEleMatch_woGwoGSF_Endcap_Cut = 0.82650989;
//     float NoEleMatch_woGwGSF_Endcap_Cut = 0.97826797;
//     float NoEleMatch_wGwoGSF_Endcap_Cut = 0.99811459;
//     float NoEleMatch_wGwGSF_Endcap_Cut = 0.99571115;
//     float woGwoGSF_Endcap_Cut = 0.99810058;
//     float woGwGSF_Endcap_Cut = 0.99335963;
//     float wGwoGSF_Endcap_Cut = 0.99585176;
//     float wGwGSF_Endcap_Cut = 0.9836691;


  //v9EleVeto  S/B :50 : Eff : 0.59508294 : FR : 0.011858136
  //   float NoEleMatch_woGwoGSF_Barrel_Cut = 0.97416347;
  //   float NoEleMatch_woGwGSF_Barrel_Cut = 0.98510718;
  //   float NoEleMatch_wGwoGSF_Barrel_Cut = 0.98446172;
  //   float NoEleMatch_wGwGSF_Barrel_Cut = 0.99093378;
  //   float woGwoGSF_Barrel_Cut = 0.99964869;
  //   float woGwGSF_Barrel_Cut = 0.99203753;
  //   float wGwoGSF_Barrel_Cut = 0.99156243;
  //   float wGwGSF_Barrel_Cut = 0.98608291;
  //   float NoEleMatch_woGwoGSF_Endcap_Cut = 0.90039802;
  //   float NoEleMatch_woGwGSF_Endcap_Cut = 0.98586744;
  //   float NoEleMatch_wGwoGSF_Endcap_Cut = 0.9999097;
  //   float NoEleMatch_wGwGSF_Endcap_Cut = 0.9985109;
  //   float woGwoGSF_Endcap_Cut = 0.99810058;
  //   float woGwGSF_Endcap_Cut = 0.99735832;
  //   float wGwoGSF_Endcap_Cut = 0.99585176;
  //   float wGwGSF_Endcap_Cut = 0.99266642;
 






//   //v9NoEleVeto  S/B :1 : Eff : 0.99756312 : FR : 0.52818871
//   float NoEleMatch_woGwoGSF_Barrel_Cut = -0.99431771;
//   float NoEleMatch_woGwGSF_Barrel_Cut = -0.99827558;
//   float NoEleMatch_wGwoGSF_Barrel_Cut = -0.99921471;
//   float NoEleMatch_wGwGSF_Barrel_Cut = -0.99982131;
//   float woGwoGSF_Barrel_Cut = -0.9986673;
//   float woGwGSF_Barrel_Cut = -0.9092682;
//   float wGwoGSF_Barrel_Cut = -0.9978289;
//   float wGwGSF_Barrel_Cut = -0.99986529;
//   float NoEleMatch_woGwoGSF_Endcap_Cut = -0.99223208;
//   float NoEleMatch_woGwGSF_Endcap_Cut = -0.99894977;
//   float NoEleMatch_wGwoGSF_Endcap_Cut = -0.99767154;
//   float NoEleMatch_wGwGSF_Endcap_Cut = -0.99987018;
//   float woGwoGSF_Endcap_Cut = -0.99906206;
//   float woGwGSF_Endcap_Cut = -0.70578009;
//   float wGwoGSF_Endcap_Cut = -0.99732733;
//   float wGwGSF_Endcap_Cut = -0.99677861;

// //   //v9NoEleVeto  S/B :4 : Eff : 0.99246597 : FR : 0.15351129
//     float NoEleMatch_woGwoGSF_Barrel_Cut = -0.99431771;
//     float NoEleMatch_woGwGSF_Barrel_Cut = -0.99827558;
//     float NoEleMatch_wGwoGSF_Barrel_Cut = -0.99921471;
//     float NoEleMatch_wGwGSF_Barrel_Cut = -0.99982131;
//     float woGwoGSF_Barrel_Cut = -0.9986673;
//     float woGwGSF_Barrel_Cut = -0.35193792;
//     float wGwoGSF_Barrel_Cut = -0.74784195;
//     float wGwGSF_Barrel_Cut = -0.987266;
//     float NoEleMatch_woGwoGSF_Endcap_Cut = -0.99223208;
//     float NoEleMatch_woGwGSF_Endcap_Cut = -0.99894977;
//     float NoEleMatch_wGwoGSF_Endcap_Cut = -0.99767154;
//     float NoEleMatch_wGwGSF_Endcap_Cut = -0.99987018;
//     float woGwoGSF_Endcap_Cut = -0.97827148;
//     float woGwGSF_Endcap_Cut = -0.085452579;
//     float wGwoGSF_Endcap_Cut = -0.6445986;
//     float wGwGSF_Endcap_Cut = -0.8983857;

// //   //v9NoEleVeto S/B :75 : Eff : 0.92679173 : FR : 0.012354638
//   float NoEleMatch_woGwoGSF_Barrel_Cut = -0.12255929;
//   float NoEleMatch_woGwGSF_Barrel_Cut = -0.0034994152;
//   float NoEleMatch_wGwoGSF_Barrel_Cut = -0.4686318;
//   float NoEleMatch_wGwGSF_Barrel_Cut = -0.45475432;
//   float woGwoGSF_Barrel_Cut = 0.92187202;
//   float woGwGSF_Barrel_Cut = 0.90210515;
//   float wGwoGSF_Barrel_Cut = 0.96472818;
//   float wGwGSF_Barrel_Cut = 0.72643727;
//   float NoEleMatch_woGwoGSF_Endcap_Cut = 0.3707284;
//   float NoEleMatch_woGwGSF_Endcap_Cut = 0.088685371;
//   float NoEleMatch_wGwoGSF_Endcap_Cut = 0.70823318;
//   float NoEleMatch_wGwGSF_Endcap_Cut = 0.86101729;
//   float woGwoGSF_Endcap_Cut = 0.98144037;
//   float woGwGSF_Endcap_Cut = 0.95562571;
//   float wGwoGSF_Endcap_Cut = 0.94617426;
//   float wGwGSF_Endcap_Cut = 0.7976926;
 

//  // //   //v9NoEleVeto S/B :100 : Eff : 0.90636307 : FR : 0.0090611335
//   float NoEleMatch_woGwoGSF_Barrel_Cut = 0.50348729;
//   float NoEleMatch_woGwGSF_Barrel_Cut = 0.59880179;
//   float NoEleMatch_wGwoGSF_Barrel_Cut = 0.37662232;
//   float NoEleMatch_wGwGSF_Barrel_Cut = 0.48121721;
//   float woGwoGSF_Barrel_Cut = 0.95085299;
//   float woGwGSF_Barrel_Cut = 0.93130147;
//   float wGwoGSF_Barrel_Cut = 0.97790641;
//   float wGwGSF_Barrel_Cut = 0.84983033;
//   float NoEleMatch_woGwoGSF_Endcap_Cut = 0.4583914;
//   float NoEleMatch_woGwGSF_Endcap_Cut = 0.56443828;
//   float NoEleMatch_wGwoGSF_Endcap_Cut = 0.81731194;
//   float NoEleMatch_wGwGSF_Endcap_Cut = 0.92261356;
//   float woGwoGSF_Endcap_Cut = 0.99503422;
//   float woGwGSF_Endcap_Cut = 0.97402358;
//   float wGwoGSF_Endcap_Cut = 0.95875031;
//   float wGwGSF_Endcap_Cut = 0.85588837;

// // //   v9NoEleVeto S/B :160 : Eff : 0.85380638 : FR : 0.005331208
//   float NoEleMatch_woGwoGSF_Barrel_Cut = 0.86627126;
//   float NoEleMatch_woGwGSF_Barrel_Cut = 0.8835659;
//   float NoEleMatch_wGwoGSF_Barrel_Cut = 0.84822935;
//   float NoEleMatch_wGwGSF_Barrel_Cut = 0.8935166;
//   float woGwoGSF_Barrel_Cut = 0.9750371;
//   float woGwGSF_Barrel_Cut = 0.96229762;
//   float wGwoGSF_Barrel_Cut = 0.98928761;
//   float wGwGSF_Barrel_Cut = 0.92962581;
//   float NoEleMatch_woGwoGSF_Endcap_Cut = 0.57613873;
//   float NoEleMatch_woGwGSF_Endcap_Cut = 0.86668134;
//   float NoEleMatch_wGwoGSF_Endcap_Cut = 0.94257277;
//   float NoEleMatch_wGwGSF_Endcap_Cut = 0.96921074;
//   float woGwoGSF_Endcap_Cut = 0.99743313;
//   float woGwGSF_Endcap_Cut = 0.98542225;
//   float wGwoGSF_Endcap_Cut = 0.97232449;
//   float wGwGSF_Endcap_Cut = 0.93028307;
  

//  // //   v9NoEleVetoS/B :270 : Eff : 0.74152601 : FR : 0.0027435496
//   float NoEleMatch_woGwoGSF_Barrel_Cut = 0.95861262;
//   float NoEleMatch_woGwGSF_Barrel_Cut = 0.95730484;
//   float NoEleMatch_wGwoGSF_Barrel_Cut = 0.95038754;
//   float NoEleMatch_wGwGSF_Barrel_Cut = 0.97629637;
//   float woGwoGSF_Barrel_Cut = 0.99122649;
//   float woGwGSF_Barrel_Cut = 0.98529476;
//   float wGwoGSF_Barrel_Cut = 0.99288166;
//   float wGwGSF_Barrel_Cut = 0.96502382;
//   float NoEleMatch_woGwoGSF_Endcap_Cut = 0.71998578;
//   float NoEleMatch_woGwGSF_Endcap_Cut = 0.96403074;
//   float NoEleMatch_wGwoGSF_Endcap_Cut = 0.99491465;
//   float NoEleMatch_wGwGSF_Endcap_Cut = 0.98960954;
//   float woGwoGSF_Endcap_Cut = 0.99863255;
//   float woGwGSF_Endcap_Cut = 0.99742085;
//   float wGwoGSF_Endcap_Cut = 0.98330361;
//   float wGwGSF_Endcap_Cut = 0.97427988;
 

// // //   v9NoEleVeto S/B :300 : Eff : 0.71256781 : FR : 0.002370839
//   float NoEleMatch_woGwoGSF_Barrel_Cut = 0.96339923;
//   float NoEleMatch_woGwGSF_Barrel_Cut = 0.96549809;
//   float NoEleMatch_wGwoGSF_Barrel_Cut = 0.96058339;
//   float NoEleMatch_wGwGSF_Barrel_Cut = 0.98129517;
//   float woGwoGSF_Barrel_Cut = 0.9988215;
//   float woGwGSF_Barrel_Cut = 0.98789442;
//   float wGwoGSF_Barrel_Cut = 0.99288166;
//   float wGwGSF_Barrel_Cut = 0.96962357;
//   float NoEleMatch_woGwoGSF_Endcap_Cut = 0.75285941;
//   float NoEleMatch_woGwGSF_Endcap_Cut = 0.97102714;
//   float NoEleMatch_wGwoGSF_Endcap_Cut = 0.99691242;
//   float NoEleMatch_wGwGSF_Endcap_Cut = 0.99220937;
//   float woGwoGSF_Endcap_Cut = 0.99863255;
//   float woGwGSF_Endcap_Cut = 0.99762082;
//   float wGwoGSF_Endcap_Cut = 0.98729599;
//   float wGwGSF_Endcap_Cut = 0.97947955;
 



  // //v10EleVeto   S/B :1 : Eff : 0.99692291 : FR : 0.60411906
//   float NoEleMatch_woGwoGSF_Barrel_Cut = -0.99211824;
//   float NoEleMatch_woGwGSF_Barrel_Cut = -0.99158919;
//   float NoEleMatch_wGwoGSF_Barrel_Cut = -0.99785674;
//   float NoEleMatch_wGwGSF_Barrel_Cut = -0.99977869;
//   float woGwoGSF_Barrel_Cut = -0.99947101;
//   float woGwGSF_Barrel_Cut = -0.024472265;
//   float wGwoGSF_Barrel_Cut = -0.27064276;
//   float wGwGSF_Barrel_Cut = -0.99939859;
//   float NoEleMatch_woGwoGSF_Endcap_Cut = -0.98237437;
//   float NoEleMatch_woGwGSF_Endcap_Cut = -0.99954861;
//   float NoEleMatch_wGwoGSF_Endcap_Cut = -0.6839624;
//   float NoEleMatch_wGwGSF_Endcap_Cut = -0.99962133;
//   float woGwoGSF_Endcap_Cut = -0.80409384;
//   float woGwGSF_Endcap_Cut = 0.39818013;
//   float wGwoGSF_Endcap_Cut = -0.14252703;
//   float wGwGSF_Endcap_Cut = -0.91505283;

//  //v10EleVeto S/B :4 : Eff : 0.98095977 : FR : 0.21483207
//   float NoEleMatch_woGwoGSF_Barrel_Cut = -0.99211824;
//   float NoEleMatch_woGwGSF_Barrel_Cut = -0.99158919;
//   float NoEleMatch_wGwoGSF_Barrel_Cut = -0.99785674;
//   float NoEleMatch_wGwGSF_Barrel_Cut = -0.99977869;
//   float woGwoGSF_Barrel_Cut = 0.70011103;
//   float woGwGSF_Barrel_Cut = 0.78517616;
//   float wGwoGSF_Barrel_Cut = 0.87343103;
//   float wGwGSF_Barrel_Cut = -0.54014736;
//   float NoEleMatch_woGwoGSF_Endcap_Cut = -0.15152179;
//   float NoEleMatch_woGwGSF_Endcap_Cut = -0.99954861;
//   float NoEleMatch_wGwoGSF_Endcap_Cut = 0.97203249;
//   float NoEleMatch_wGwGSF_Endcap_Cut = 0.75609964;
//   float woGwoGSF_Endcap_Cut = 0.90932918;
//   float woGwGSF_Endcap_Cut = 0.85137534;
//   float wGwoGSF_Endcap_Cut = 0.89368826;
//   float wGwGSF_Endcap_Cut = 0.32127407;


//   //v10EleVeto S/B :12 : Eff : 0.92499787 : FR : 0.077000886
//   float NoEleMatch_woGwoGSF_Barrel_Cut = 0.24963723;
//   float NoEleMatch_woGwGSF_Barrel_Cut = 0.81346148;
//   float NoEleMatch_wGwoGSF_Barrel_Cut = 0.36052552;
//   float NoEleMatch_wGwGSF_Barrel_Cut = 0.60474181;
//   float woGwoGSF_Barrel_Cut = 0.96204662;
//   float woGwGSF_Barrel_Cut = 0.94674587;
//   float wGwoGSF_Barrel_Cut = 0.97342771;
//   float wGwGSF_Barrel_Cut = 0.79242104;
//   float NoEleMatch_woGwoGSF_Endcap_Cut = 0.98661345;
//   float NoEleMatch_woGwGSF_Endcap_Cut = 0.87488145;
//   float NoEleMatch_wGwoGSF_Endcap_Cut = 0.9959861;
//   float NoEleMatch_wGwGSF_Endcap_Cut = 0.97364032;
//   float woGwoGSF_Endcap_Cut = 0.99990922;
//   float woGwGSF_Endcap_Cut = 0.96912217;
//   float wGwoGSF_Endcap_Cut = 0.97619396;
//   float wGwGSF_Endcap_Cut = 0.9179492;

 //  //v10EleVeto S/B :22 : Eff : 0.84695876 : FR : 0.038371261
//   float NoEleMatch_woGwoGSF_Barrel_Cut = 0.96604228;
//   float NoEleMatch_woGwGSF_Barrel_Cut = 0.96343422;
//   float NoEleMatch_wGwoGSF_Barrel_Cut = 0.89157128;
//   float NoEleMatch_wGwGSF_Barrel_Cut = 0.94708216;
//   float woGwoGSF_Barrel_Cut = 0.99063957;
//   float woGwGSF_Barrel_Cut = 0.97534055;
//   float wGwoGSF_Barrel_Cut = 0.98660094;
//   float wGwGSF_Barrel_Cut = 0.93717414;
//   float NoEleMatch_woGwoGSF_Endcap_Cut = 0.99632752;
//   float NoEleMatch_woGwGSF_Endcap_Cut = 0.97126245;
//   float NoEleMatch_wGwoGSF_Endcap_Cut = 0.99778265;
//   float NoEleMatch_wGwGSF_Endcap_Cut = 0.99163538;
//   float woGwoGSF_Endcap_Cut = 0.99990922;
//   float woGwGSF_Endcap_Cut = 0.98431528;
//   float wGwoGSF_Endcap_Cut = 0.99497247;
//   float wGwGSF_Endcap_Cut = 0.97052062;

 //  //v10EleVeto2 S/B :22 : Eff : 0.8834489 : FR : 0.040102936
//   float NoEleMatch_woGwoGSF_Barrel_Cut = 0.9445262;
//   float NoEleMatch_woGwGSF_Barrel_Cut = 0.91822332;
//   float NoEleMatch_wGwoGSF_Barrel_Cut = 0.90735477;
//   float NoEleMatch_wGwGSF_Barrel_Cut = 0.95548075;
//   float woGwoGSF_Barrel_Cut = 0.99423867;
//   float woGwGSF_Barrel_Cut = 0.9791398;
//   float wGwoGSF_Barrel_Cut = 0.98779851;
//   float wGwGSF_Barrel_Cut = 0.9509697;
//   float NoEleMatch_woGwoGSF_Endcap_Cut = -0.25302416;
//   float NoEleMatch_woGwGSF_Endcap_Cut = 0.94746715;
//   float NoEleMatch_wGwoGSF_Endcap_Cut = 0.97023594;
//   float NoEleMatch_wGwGSF_Endcap_Cut = 0.98263788;
//   float woGwoGSF_Endcap_Cut = 0.99990922;
//   float woGwGSF_Endcap_Cut = 0.98431528;
//   float wGwoGSF_Endcap_Cut = 0.99497247;
//   float wGwGSF_Endcap_Cut = 0.9499318;

  //v10EleVeto S/B :35 : Eff : 0.74521267 : FR : 0.021220656
//   float NoEleMatch_woGwoGSF_Barrel_Cut = 0.98018712;
//   float NoEleMatch_woGwGSF_Barrel_Cut = 0.9861393;
//   float NoEleMatch_wGwoGSF_Barrel_Cut = 0.96309662;
//   float NoEleMatch_wGwGSF_Barrel_Cut = 0.98367584;
//   float woGwoGSF_Barrel_Cut = 0.99763787;
//   float woGwGSF_Barrel_Cut = 0.98493874;
//   float wGwoGSF_Barrel_Cut = 0.98979443;
//   float wGwGSF_Barrel_Cut = 0.97296256;
//   float NoEleMatch_woGwoGSF_Endcap_Cut = 0.99831003;
//   float NoEleMatch_woGwGSF_Endcap_Cut = 0.98885894;
//   float NoEleMatch_wGwoGSF_Endcap_Cut = 0.99818188;
//   float NoEleMatch_wGwGSF_Endcap_Cut = 0.9960342;
//   float woGwoGSF_Endcap_Cut = 0.99990922;
//   float woGwGSF_Endcap_Cut = 0.99311131;
//   float wGwoGSF_Endcap_Cut = 0.99497247;
//   float wGwGSF_Endcap_Cut = 0.98571235;



//   //v11EleVetoTrain S/B :1 : Eff : 0.99661684 : FR : 0.6068331
//   float NoEleMatch_woGwoGSF_Barrel_Cut = -1;
//   float NoEleMatch_woGwGSF_Barrel_Cut = -1;
//   float NoEleMatch_wGwoGSF_Barrel_Cut = -1;
//   float NoEleMatch_wGwGSF_Barrel_Cut = -1;
//   float woGwoGSF_Barrel_Cut = -1;
//   float woGwGSF_Barrel_Cut = 0.097454898;
//   float wGwoGSF_Barrel_Cut = -0.089112297;
//   float wGwGSF_Barrel_Cut = -1;
//   float NoEleMatch_woGwoGSF_Endcap_Cut = -1;
//   float NoEleMatch_woGwGSF_Endcap_Cut = -1;
//   float NoEleMatch_wGwoGSF_Endcap_Cut = -1;
//   float NoEleMatch_wGwGSF_Endcap_Cut = -1;
//   float woGwoGSF_Endcap_Cut = -0.90658611;
//   float woGwGSF_Endcap_Cut = 0.39041549;
//   float wGwoGSF_Endcap_Cut = -0.26986191;
//   float wGwGSF_Endcap_Cut = -0.9791041;


//   //v11EleVetoTrain  S/B :4 : Eff : 0.98456049 : FR : 0.20498811
//   float NoEleMatch_woGwoGSF_Barrel_Cut = -1;
//   float NoEleMatch_woGwGSF_Barrel_Cut = -1;
//   float NoEleMatch_wGwoGSF_Barrel_Cut = -1;
//   float NoEleMatch_wGwGSF_Barrel_Cut = -1;
//   float woGwoGSF_Barrel_Cut = 0.37920451;
//   float woGwGSF_Barrel_Cut = 0.82233191;
//   float wGwoGSF_Barrel_Cut = 0.88555789;
//   float wGwGSF_Barrel_Cut = -0.36490291;
//   float NoEleMatch_woGwoGSF_Endcap_Cut = -1;
//   float NoEleMatch_woGwGSF_Endcap_Cut = -1;
//   float NoEleMatch_wGwoGSF_Endcap_Cut = -1;
//   float NoEleMatch_wGwGSF_Endcap_Cut = 0.39332429;
//   float woGwoGSF_Endcap_Cut = 0.074224897;
//   float woGwGSF_Endcap_Cut = 0.83012909;
//   float wGwoGSF_Endcap_Cut = 0.8247155;
//   float wGwGSF_Endcap_Cut = -0.043480501;


//   //v11EleVeto S/B :12 : Eff : 0.94900656 : FR : 0.079052091
//   float NoEleMatch_woGwoGSF_Barrel_Cut = -0.57152867;
//   float NoEleMatch_woGwGSF_Barrel_Cut = 0.2915971;
//   float NoEleMatch_wGwoGSF_Barrel_Cut = 0.52442229;
//   float NoEleMatch_wGwGSF_Barrel_Cut = 0.69085008;
//   float woGwoGSF_Barrel_Cut = 0.83899689;
//   float woGwGSF_Barrel_Cut = 0.95395511;
//   float wGwoGSF_Barrel_Cut = 0.97716492;
//   float wGwGSF_Barrel_Cut = 0.8347953;
//   float NoEleMatch_woGwoGSF_Endcap_Cut = -1;
//   float NoEleMatch_woGwGSF_Endcap_Cut = 0.5389865;
//   float NoEleMatch_wGwoGSF_Endcap_Cut = 0.76161069;
//   float NoEleMatch_wGwGSF_Endcap_Cut = 0.94229972;
//   float woGwoGSF_Endcap_Cut = 0.51024193;
//   float woGwGSF_Endcap_Cut = 0.96033829;
//   float wGwoGSF_Endcap_Cut = 0.95284408;
//   float wGwGSF_Endcap_Cut = 0.83980489;


//   //v11EleVeto S/B :22 : Eff : 0.88314116 : FR : 0.040124979
//   float NoEleMatch_woGwoGSF_Barrel_Cut = 0.94147152;
//   float NoEleMatch_woGwGSF_Barrel_Cut = 0.9025057;
//   float NoEleMatch_wGwoGSF_Barrel_Cut = 0.9099797;
//   float NoEleMatch_wGwGSF_Barrel_Cut = 0.95033932;
//   float woGwoGSF_Barrel_Cut = 0.91173708;
//   float woGwGSF_Barrel_Cut = 0.98269969;
//   float wGwoGSF_Barrel_Cut = 0.9891637;
//   float wGwGSF_Barrel_Cut = 0.94945049;
//   float NoEleMatch_woGwoGSF_Endcap_Cut = -0.2687307;
//   float NoEleMatch_woGwGSF_Endcap_Cut = 0.92959392;
//   float NoEleMatch_wGwoGSF_Endcap_Cut = 0.96120691;
//   float NoEleMatch_wGwGSF_Endcap_Cut = 0.9809019;
//   float woGwoGSF_Endcap_Cut = 0.81972611;
//   float woGwGSF_Endcap_Cut = 0.98181093;
//   float wGwoGSF_Endcap_Cut = 0.97734672;
//   float wGwGSF_Endcap_Cut = 0.9468447;

//   //v11EleVeto S/B :24 : Eff : 0.87241733 : FR : 0.036230154
//   float NoEleMatch_woGwoGSF_Barrel_Cut = 0.95205629;
//   float NoEleMatch_woGwGSF_Barrel_Cut = 0.91949391;
//   float NoEleMatch_wGwoGSF_Barrel_Cut = 0.92490751;
//   float NoEleMatch_wGwGSF_Barrel_Cut = 0.96173209;
//   float woGwoGSF_Barrel_Cut = 0.9220795;
//   float woGwGSF_Barrel_Cut = 0.98530549;
//   float wGwoGSF_Barrel_Cut = 0.98968887;
//   float wGwGSF_Barrel_Cut = 0.95718712;
//   float NoEleMatch_woGwoGSF_Endcap_Cut = -0.1932029;
//   float NoEleMatch_woGwGSF_Endcap_Cut = 0.9450267;
//   float NoEleMatch_wGwoGSF_Endcap_Cut = 0.96823651;
//   float NoEleMatch_wGwGSF_Endcap_Cut = 0.98459852;
//   float woGwoGSF_Endcap_Cut = 0.81972611;
//   float woGwGSF_Endcap_Cut = 0.98579031;
//   float wGwoGSF_Endcap_Cut = 0.9792859;
//   float wGwGSF_Endcap_Cut = 0.95361167;


 //  //v11EleVeto S/B :32 : Eff : 0.80315357 : FR : 0.025088476
//   float NoEleMatch_woGwoGSF_Barrel_Cut = 0.9702363;
//   float NoEleMatch_woGwGSF_Barrel_Cut = 0.96613568;
//   float NoEleMatch_wGwoGSF_Barrel_Cut = 0.95989388;
//   float NoEleMatch_wGwGSF_Barrel_Cut = 0.98261893;
//   float woGwoGSF_Barrel_Cut = 0.99956667;
//   float woGwGSF_Barrel_Cut = 0.9889819;
//   float wGwoGSF_Barrel_Cut = 0.98966873;
//   float wGwGSF_Barrel_Cut = 0.97474092;
//   float NoEleMatch_woGwoGSF_Endcap_Cut = 0.1232503;
//   float NoEleMatch_woGwGSF_Endcap_Cut = 0.97619528;
//   float NoEleMatch_wGwoGSF_Endcap_Cut = 0.9867599;
//   float NoEleMatch_wGwGSF_Endcap_Cut = 0.99156749;
//   float woGwoGSF_Endcap_Cut = 0.9996475;
//   float woGwGSF_Endcap_Cut = 0.99611253;
//   float wGwoGSF_Endcap_Cut = 0.99473888;
//   float wGwGSF_Endcap_Cut = 0.97431672;



//   //v11EleVeto S/B :35 : Eff : 0.78086108 : FR : 0.022293443
//   float NoEleMatch_woGwoGSF_Barrel_Cut = 0.97302389;
//   float NoEleMatch_woGwGSF_Barrel_Cut = 0.9722361;
//   float NoEleMatch_wGwoGSF_Barrel_Cut = 0.96813548;
//   float NoEleMatch_wGwGSF_Barrel_Cut = 0.9857499;
//   float woGwoGSF_Barrel_Cut = 0.99956667;
//   float woGwGSF_Barrel_Cut = 0.98991108;
//   float wGwoGSF_Barrel_Cut = 0.98966873;
//   float wGwGSF_Barrel_Cut = 0.97799307;
//   float NoEleMatch_woGwoGSF_Endcap_Cut = -0.31264549;
//   float NoEleMatch_woGwGSF_Endcap_Cut = 0.98007369;
//   float NoEleMatch_wGwoGSF_Endcap_Cut = 0.98904252;
//   float NoEleMatch_wGwGSF_Endcap_Cut = 0.99324411;
//   float woGwoGSF_Endcap_Cut = 0.9996475;
//   float woGwGSF_Endcap_Cut = 0.99611253;
//   float wGwoGSF_Endcap_Cut = 0.99473888;
//   float wGwGSF_Endcap_Cut = 0.97779107;

//   //v11EleVeto S/B :37 : Eff : 0.77365923 : FR : 0.020891594
//   float NoEleMatch_woGwoGSF_Barrel_Cut = 0.97360969;
//   float NoEleMatch_woGwGSF_Barrel_Cut = 0.97138768;
//   float NoEleMatch_wGwoGSF_Barrel_Cut = 0.97274113;
//   float NoEleMatch_wGwGSF_Barrel_Cut = 0.98538631;
//   float woGwoGSF_Barrel_Cut = 0.93690628;
//   float woGwGSF_Barrel_Cut = 0.99490052;
//   float wGwoGSF_Barrel_Cut = 0.99213308;
//   float wGwGSF_Barrel_Cut = 0.98025548;
//   float NoEleMatch_woGwoGSF_Endcap_Cut = 0.29832369;
//   float NoEleMatch_woGwGSF_Endcap_Cut = 0.97825569;
//   float NoEleMatch_wGwoGSF_Endcap_Cut = 0.98657811;
//   float NoEleMatch_wGwGSF_Endcap_Cut = 0.99245632;
//   float woGwoGSF_Endcap_Cut = 0.86937767;
//   float woGwGSF_Endcap_Cut = 0.99209273;
//   float wGwoGSF_Endcap_Cut = 0.98330569;
//   float wGwGSF_Endcap_Cut = 0.97625589;



// //   v11DYEleVeto S/B :1 : Eff : 0.99707431 : FR : 0.60044116
//   float NoEleMatch_woGwoGSF_Barrel_Cut = -1;
//   float NoEleMatch_woGwGSF_Barrel_Cut = -1;
//   float NoEleMatch_wGwoGSF_Barrel_Cut = -1;
//   float NoEleMatch_wGwGSF_Barrel_Cut = -1;
//   float woGwoGSF_Barrel_Cut = -1;
//   float woGwGSF_Barrel_Cut = -0.4648121;
//   float wGwoGSF_Barrel_Cut = -0.90630329;
//   float wGwGSF_Barrel_Cut = -0.9984355;
//   float NoEleMatch_woGwoGSF_Endcap_Cut = -1;
//   float NoEleMatch_woGwGSF_Endcap_Cut = -1;
//   float NoEleMatch_wGwoGSF_Endcap_Cut = -1;
//   float NoEleMatch_wGwGSF_Endcap_Cut = -1;
//   float woGwoGSF_Endcap_Cut = -0.99997067;
//   float woGwGSF_Endcap_Cut = -0.28529471;
//   float wGwoGSF_Endcap_Cut = -0.97025651;
//   float wGwGSF_Endcap_Cut = -1;

//   //v11DYEleVeto S/B :4 : Eff : 0.99122095 : FR : 0.20285448
//   float NoEleMatch_woGwoGSF_Barrel_Cut = -1;
//   float NoEleMatch_woGwGSF_Barrel_Cut = -0.89763749;
//   float NoEleMatch_wGwoGSF_Barrel_Cut = -1;
//   float NoEleMatch_wGwGSF_Barrel_Cut = -0.99980909;
//   float woGwoGSF_Barrel_Cut = -1;
//   float woGwGSF_Barrel_Cut = 0.32603809;
//   float wGwoGSF_Barrel_Cut = 0.14890429;
//   float wGwGSF_Barrel_Cut = -0.8059901;
//   float NoEleMatch_woGwoGSF_Endcap_Cut = -1;
//   float NoEleMatch_woGwGSF_Endcap_Cut = -1;
//   float NoEleMatch_wGwoGSF_Endcap_Cut = -1;
//   float NoEleMatch_wGwGSF_Endcap_Cut = -0.3576915;
//   float woGwoGSF_Endcap_Cut = -0.96272188;
//   float woGwGSF_Endcap_Cut = 0.4293611;
//   float wGwoGSF_Endcap_Cut = 0.018674901;
//   float wGwGSF_Endcap_Cut = -0.73440129;

//   //v11DYEleVeto  S/B :12 : Eff : 0.97302771 : FR : 0.079442091
//   float NoEleMatch_woGwoGSF_Barrel_Cut = -0.87077153;
//   float NoEleMatch_woGwGSF_Barrel_Cut = 0.4342899;
//   float NoEleMatch_wGwoGSF_Barrel_Cut = -0.44592509;
//   float NoEleMatch_wGwGSF_Barrel_Cut = 0.2424303;
//   float woGwoGSF_Barrel_Cut = -0.93514889;
//   float woGwGSF_Barrel_Cut = 0.73575473;
//   float wGwoGSF_Barrel_Cut = 0.8120501;
//   float wGwGSF_Barrel_Cut = 0.3365421;
//   float NoEleMatch_woGwoGSF_Endcap_Cut = -1;
//   float NoEleMatch_woGwGSF_Endcap_Cut = 0.17781051;
//   float NoEleMatch_wGwoGSF_Endcap_Cut = -0.59326392;
//   float NoEleMatch_wGwGSF_Endcap_Cut = 0.69701111;
//   float woGwoGSF_Endcap_Cut = -0.8614189;
//   float woGwGSF_Endcap_Cut = 0.76361048;
//   float wGwoGSF_Endcap_Cut = 0.6659435;
//   float wGwGSF_Endcap_Cut = 0.2559441;

//   //v11DYEleVeto S/B :22 : Eff : 0.94560456 : FR : 0.042968474
//   float NoEleMatch_woGwoGSF_Barrel_Cut = 0.55280328;
//   float NoEleMatch_woGwGSF_Barrel_Cut = 0.74355191;
//   float NoEleMatch_wGwoGSF_Barrel_Cut = 0.5530659;
//   float NoEleMatch_wGwGSF_Barrel_Cut = 0.72179651;
//   float woGwoGSF_Barrel_Cut = -0.73494673;
//   float woGwGSF_Barrel_Cut = 0.84402668;
//   float wGwoGSF_Barrel_Cut = 0.90387928;
//   float wGwGSF_Barrel_Cut = 0.74054211;
//   float NoEleMatch_woGwoGSF_Endcap_Cut = -0.92413992;
//   float NoEleMatch_woGwGSF_Endcap_Cut = 0.7497533;
//   float NoEleMatch_wGwoGSF_Endcap_Cut = 0.4294419;
//   float NoEleMatch_wGwGSF_Endcap_Cut = 0.87323588;
//   float woGwoGSF_Endcap_Cut = -0.80392969;
//   float woGwGSF_Endcap_Cut = 0.85299551;
//   float wGwoGSF_Endcap_Cut = 0.81697887;
//   float wGwGSF_Endcap_Cut = 0.68642628;


// //   //v11DYEleVeto S/B :35 : Eff : 0.90448797 : FR : 0.025821876
//   float NoEleMatch_woGwoGSF_Barrel_Cut = 0.86937767;
//   float NoEleMatch_woGwGSF_Barrel_Cut = 0.85907573;
//   float NoEleMatch_wGwoGSF_Barrel_Cut = 0.80233389;
//   float NoEleMatch_wGwGSF_Barrel_Cut = 0.86741829;
//   float woGwoGSF_Barrel_Cut = -0.63091671;
//   float woGwGSF_Barrel_Cut = 0.90486908;
//   float wGwoGSF_Barrel_Cut = 0.9480567;
//   float wGwGSF_Barrel_Cut = 0.87444788;
//   float NoEleMatch_woGwoGSF_Endcap_Cut = -0.59726351;
//   float NoEleMatch_woGwGSF_Endcap_Cut = 0.87820512;
//   float NoEleMatch_wGwoGSF_Endcap_Cut = 0.82243288;
//   float NoEleMatch_wGwGSF_Endcap_Cut = 0.93088669;
//   float woGwoGSF_Endcap_Cut = -0.75813627;
//   float woGwGSF_Endcap_Cut = 0.9099595;
//   float wGwoGSF_Endcap_Cut = 0.8958599;
//   float wGwGSF_Endcap_Cut = 0.84037048;

// //   //v11DYEleVeto S/B :55 : Eff : 0.84608918 : FR : 0.015367909
//   float NoEleMatch_woGwoGSF_Barrel_Cut = 0.92539233;
//   float NoEleMatch_woGwGSF_Barrel_Cut = 0.9196555;
//   float NoEleMatch_wGwoGSF_Barrel_Cut = 0.91006052;
//   float NoEleMatch_wGwGSF_Barrel_Cut = 0.93145227;
//   float woGwoGSF_Barrel_Cut = -0.4009397;
//   float woGwGSF_Barrel_Cut = 0.94272387;
//   float wGwoGSF_Barrel_Cut = 0.97514492;
//   float wGwGSF_Barrel_Cut = 0.93561351;
//   float NoEleMatch_woGwoGSF_Endcap_Cut = -0.30234349;
//   float NoEleMatch_woGwGSF_Endcap_Cut = 0.91915047;
//   float NoEleMatch_wGwoGSF_Endcap_Cut = 0.92476612;
//   float NoEleMatch_wGwGSF_Endcap_Cut = 0.96573168;
//   float woGwoGSF_Endcap_Cut = -0.6929307;
//   float woGwGSF_Endcap_Cut = 0.93664372;
//   float wGwoGSF_Endcap_Cut = 0.93302792;
//   float wGwGSF_Endcap_Cut = 0.91981709;


// //   //v11DYEleVeto S/B :75 : Eff : 0.79999501 : FR : 0.010653391
//   float NoEleMatch_woGwoGSF_Barrel_Cut = 0.94753152;
//   float NoEleMatch_woGwGSF_Barrel_Cut =0.94278449;
//   float NoEleMatch_wGwoGSF_Barrel_Cut =0.94854152;
//   float NoEleMatch_wGwGSF_Barrel_Cut =0.95322788;
//   float woGwoGSF_Barrel_Cut =-0.22919931;
//   float woGwGSF_Barrel_Cut = 0.95458132;
//   float wGwoGSF_Barrel_Cut = 0.98160893;
//   float wGwGSF_Barrel_Cut = 0.95555091;
//   float NoEleMatch_woGwoGSF_Endcap_Cut =0.1660137;
//   float NoEleMatch_woGwGSF_Endcap_Cut =0.94761229;
//   float NoEleMatch_wGwoGSF_Endcap_Cut = 0.95427829;
//   float NoEleMatch_wGwGSF_Endcap_Cut = 0.97603369;
//   float woGwoGSF_Endcap_Cut = -0.6929307;
//   float woGwGSF_Endcap_Cut = 0.95246029;
//   float wGwoGSF_Endcap_Cut = 0.94688511;
//   float wGwGSF_Endcap_Cut = 0.94662249;




  //v12EleVeto S/B :1 : Eff : 0.99695164 : FR : 0.6027258
//   float NoEleMatch_woGwoGSF_Barrel_Cut = -1;
//   float NoEleMatch_woGwGSF_Barrel_Cut = -1;
//   float NoEleMatch_wGwoGSF_Barrel_Cut = -1;
//   float NoEleMatch_wGwGSF_Barrel_Cut = -1;
//   float woGwoGSF_Barrel_Cut = -1;
//   float woGwGSF_Barrel_Cut = 0.1001011;
//   float wGwoGSF_Barrel_Cut = -0.3958897;
//   float wGwGSF_Barrel_Cut = -1;
//   float NoEleMatch_woGwoGSF_Endcap_Cut = -1;
//   float NoEleMatch_woGwGSF_Endcap_Cut = -1;
//   float NoEleMatch_wGwoGSF_Endcap_Cut = -1;
//   float NoEleMatch_wGwGSF_Endcap_Cut = -1;
//   float woGwoGSF_Endcap_Cut = -0.94009793;
//   float woGwGSF_Endcap_Cut = 0.3858099;
//   float wGwoGSF_Endcap_Cut = -0.3683773;
//   float wGwGSF_Endcap_Cut = -0.97661948;

//   //v12EleVeto S/B :4 : Eff : 0.98688775 : FR : 0.20394285
//   float NoEleMatch_woGwoGSF_Barrel_Cut = -1;
//   float NoEleMatch_woGwGSF_Barrel_Cut = -1;
//   float NoEleMatch_wGwoGSF_Barrel_Cut = -1;
//   float NoEleMatch_wGwGSF_Barrel_Cut = -1;
//   float woGwoGSF_Barrel_Cut = 0.3322193;
//   float woGwGSF_Barrel_Cut = 0.82087749;
//   float wGwoGSF_Barrel_Cut = 0.88285112;
//   float wGwGSF_Barrel_Cut = -0.40881771;
//   float NoEleMatch_woGwoGSF_Endcap_Cut = -1;
//   float NoEleMatch_woGwGSF_Endcap_Cut = -1;
//   float NoEleMatch_wGwoGSF_Endcap_Cut = -1;
//   float NoEleMatch_wGwGSF_Endcap_Cut = 0.3689833;
//   float woGwoGSF_Endcap_Cut = -0.1235937;
//   float woGwGSF_Endcap_Cut = 0.8511371;
//   float wGwoGSF_Endcap_Cut = 0.8023743;
//   float wGwGSF_Endcap_Cut = -0.0422685;

//   //v12EleVeto S/B :12 : Eff : 0.95740771 : FR : 0.079729713
//   float NoEleMatch_woGwoGSF_Barrel_Cut = -0.44669271;
//   float NoEleMatch_woGwGSF_Barrel_Cut = -0.1560147;
//   float NoEleMatch_wGwoGSF_Barrel_Cut = 0.3993237;
//   float NoEleMatch_wGwGSF_Barrel_Cut = 0.57736647;
//   float woGwoGSF_Barrel_Cut = 0.79896051;
//   float woGwGSF_Barrel_Cut = 0.95332891;
//   float wGwoGSF_Barrel_Cut = 0.9712261;
//   float wGwGSF_Barrel_Cut = 0.81811011;
//   float NoEleMatch_woGwoGSF_Endcap_Cut = -1;
//   float NoEleMatch_woGwGSF_Endcap_Cut = 0.51018131;
//   float NoEleMatch_wGwoGSF_Endcap_Cut = 0.69303173;
//   float NoEleMatch_wGwGSF_Endcap_Cut = 0.9384011;
//   float woGwoGSF_Endcap_Cut = 0.3054139;
//   float woGwGSF_Endcap_Cut = 0.95557112;
//   float wGwoGSF_Endcap_Cut = 0.9535107;
//   float wGwGSF_Endcap_Cut = 0.82015032;

//  //v12EleVeto  S/B :22 : Eff : 0.90455395 : FR : 0.041099213
//   float NoEleMatch_woGwoGSF_Barrel_Cut = 0.94438028;
//   float NoEleMatch_woGwGSF_Barrel_Cut = 0.8547731;
//   float NoEleMatch_wGwoGSF_Barrel_Cut = 0.88810313;
//   float NoEleMatch_wGwGSF_Barrel_Cut = 0.93440151;
//   float woGwoGSF_Barrel_Cut = 0.89612252;
//   float woGwGSF_Barrel_Cut = 0.97981107;
//   float wGwoGSF_Barrel_Cut = 0.98350769;
//   float wGwGSF_Barrel_Cut = 0.94823849;
//   float NoEleMatch_woGwoGSF_Endcap_Cut = -0.25960031;
//   float NoEleMatch_woGwGSF_Endcap_Cut = 0.9218775;
//   float NoEleMatch_wGwoGSF_Endcap_Cut = 0.95421767;
//   float NoEleMatch_wGwGSF_Endcap_Cut = 0.97876072;
//   float woGwoGSF_Endcap_Cut = 0.51331228;
//   float woGwGSF_Endcap_Cut = 0.97645789;
//   float wGwoGSF_Endcap_Cut = 0.97637713;
//   float wGwGSF_Endcap_Cut = 0.94280469;

//  //v12EleVeto S/B :35 : Eff : 0.82084465 : FR : 0.023435647
//   float NoEleMatch_woGwoGSF_Barrel_Cut = 0.96979189;
//   float NoEleMatch_woGwGSF_Barrel_Cut = 0.95298553;
//   float NoEleMatch_wGwoGSF_Barrel_Cut = 0.95908588;
//   float NoEleMatch_wGwGSF_Barrel_Cut = 0.98162907;
//   float woGwoGSF_Barrel_Cut = 0.92464489;
//   float woGwGSF_Barrel_Cut = 0.99294108;
//   float wGwoGSF_Barrel_Cut = 0.99011308;
//   float wGwGSF_Barrel_Cut = 0.97700328;
//   float NoEleMatch_woGwoGSF_Endcap_Cut = 0.1305829;
//   float NoEleMatch_woGwGSF_Endcap_Cut = 0.97338748;
//   float NoEleMatch_wGwoGSF_Endcap_Cut = 0.97981107;
//   float NoEleMatch_wGwGSF_Endcap_Cut = 0.9912039;
//   float woGwoGSF_Endcap_Cut = 0.70799989;
//   float woGwGSF_Endcap_Cut = 0.9915877;
//   float wGwoGSF_Endcap_Cut = 0.98821431;
//   float wGwGSF_Endcap_Cut = 0.97338748;

//  //v12EleVeto  S/B :55 : Eff : 0.70827711 : FR : 0.012865499
//   float NoEleMatch_woGwoGSF_Barrel_Cut = 0.98078072;
//   float NoEleMatch_woGwGSF_Barrel_Cut = 0.98360872;
//   float NoEleMatch_wGwoGSF_Barrel_Cut = 0.98478031;
//   float NoEleMatch_wGwGSF_Barrel_Cut = 0.99249673;
//   float woGwoGSF_Barrel_Cut = 0.95474291;
//   float woGwGSF_Barrel_Cut = 0.99611253;
//   float wGwoGSF_Barrel_Cut = 0.99431467;
//   float wGwGSF_Barrel_Cut = 0.98867887;
//   float NoEleMatch_woGwoGSF_Endcap_Cut = 0.8200897;
//   float NoEleMatch_woGwGSF_Endcap_Cut = 0.98908287;
//   float NoEleMatch_wGwoGSF_Endcap_Cut = 0.99114329;
//   float NoEleMatch_wGwGSF_Endcap_Cut = 0.99708211;
//   float woGwoGSF_Endcap_Cut = 0.71521127;
//   float woGwGSF_Endcap_Cut = 0.99352688;
//   float wGwoGSF_Endcap_Cut = 0.99124432;
//   float wGwGSF_Endcap_Cut = 0.98686087;

//  //  //v12EleVeto S/B :75 : Eff : 0.59261227 : FR : 0.007882637
//   float NoEleMatch_woGwoGSF_Barrel_Cut = 0.98783052;
//   float NoEleMatch_woGwGSF_Barrel_Cut = 0.99183011;
//   float NoEleMatch_wGwoGSF_Barrel_Cut = 0.99277949;
//   float NoEleMatch_wGwGSF_Barrel_Cut = 0.99572867;
//   float woGwoGSF_Barrel_Cut = 0.97591251;
//   float woGwGSF_Barrel_Cut = 0.99851632;
//   float wGwoGSF_Barrel_Cut = 0.9954257;
//   float wGwGSF_Barrel_Cut = 0.99346632;
//   float NoEleMatch_woGwoGSF_Endcap_Cut = 0.96817589;
//   float NoEleMatch_woGwGSF_Endcap_Cut = 0.99405211;
//   float NoEleMatch_wGwoGSF_Endcap_Cut = 0.9938097;
//   float NoEleMatch_wGwGSF_Endcap_Cut = 0.99766791;
//   float woGwoGSF_Endcap_Cut = 0.82726067;
//   float woGwGSF_Endcap_Cut = 0.99397129;
//   float wGwoGSF_Endcap_Cut = 0.99314308;
//   float wGwGSF_Endcap_Cut = 0.99164832;

//   float NoEleMatch_woGwoGSF_Barrel_Cut = 0.;
//   float NoEleMatch_woGwGSF_Barrel_Cut = 0.;
//   float NoEleMatch_wGwoGSF_Barrel_Cut = 0.;
//   float NoEleMatch_wGwGSF_Barrel_Cut = 0.;
//   float woGwoGSF_Barrel_Cut = 0.;
//   float woGwGSF_Barrel_Cut = 0.;
//   float wGwoGSF_Barrel_Cut = 0.;
//   float wGwGSF_Barrel_Cut = 0.;
//   float NoEleMatch_woGwoGSF_Endcap_Cut = 0.;
//   float NoEleMatch_woGwGSF_Endcap_Cut = 0.;
//   float NoEleMatch_wGwoGSF_Endcap_Cut = 0.;
//   float NoEleMatch_wGwGSF_Endcap_Cut = 0.;
//   float woGwoGSF_Endcap_Cut = 0.;
//   float woGwGSF_Endcap_Cut = 0.;
//   float wGwoGSF_Endcap_Cut = 0.;
//   float wGwGSF_Endcap_Cut = 0.;


// //   //v13EleVeto S/B :12 : Eff : 0.95158702 : FR : 0.079186447 LooseMVA3WP
//   float NoEleMatch_woGwoGSF_Barrel_Cut = 0.1816889;
//   float NoEleMatch_woGwGSF_Barrel_Cut = 0.1538533;
//   float NoEleMatch_wGwoGSF_Barrel_Cut = 0.5605197;
//   float NoEleMatch_wGwGSF_Barrel_Cut = 0.66321647;
//   float woGwoGSF_Barrel_Cut = 0.86337829;
//   float woGwGSF_Barrel_Cut = 0.94084531;
//   float wGwoGSF_Barrel_Cut = 0.98025548;
//   float wGwGSF_Barrel_Cut = 0.80039471;
//   float NoEleMatch_woGwoGSF_Endcap_Cut = -1;
//   float NoEleMatch_woGwGSF_Endcap_Cut = 0.49787951;
//   float NoEleMatch_wGwoGSF_Endcap_Cut = 0.74751109;
//   float NoEleMatch_wGwGSF_Endcap_Cut = 0.94486511;
//   float woGwoGSF_Endcap_Cut = 0.63645148;
//   float woGwGSF_Endcap_Cut = 0.9575507;
//   float wGwoGSF_Endcap_Cut = 0.9549247;
//   float wGwGSF_Endcap_Cut = 0.83487612;



//   //v13EleVeto S/B :22 : Eff : 0.90216041 : FR : 0.040997349 // MediumMVA3WP
//   float NoEleMatch_woGwoGSF_Barrel_Cut = 0.5577119;
//   float NoEleMatch_woGwGSF_Barrel_Cut = 0.7271899;
//   float NoEleMatch_wGwoGSF_Barrel_Cut = 0.90410149;
//   float NoEleMatch_wGwGSF_Barrel_Cut = 0.94858187;
//   float woGwoGSF_Barrel_Cut = 0.95044029;
//   float woGwGSF_Barrel_Cut = 0.97195327;
//   float wGwoGSF_Barrel_Cut = 0.99229473;
//   float wGwGSF_Barrel_Cut = 0.92997772;
//   float NoEleMatch_woGwoGSF_Endcap_Cut = -0.3049897;
//   float NoEleMatch_woGwGSF_Endcap_Cut = 0.92191792;
//   float NoEleMatch_wGwoGSF_Endcap_Cut = 0.96017671;
//   float NoEleMatch_wGwGSF_Endcap_Cut = 0.98126549;
//   float woGwoGSF_Endcap_Cut = 0.80912107;
//   float woGwGSF_Endcap_Cut = 0.98326528;
//   float wGwoGSF_Endcap_Cut = 0.97490251;
//   float wGwGSF_Endcap_Cut = 0.94708711;
 
// //   //v13EleVeto 0.95
//   float NoEleMatch_woGwoGSF_Barrel_Cut = 0.95;
//   float NoEleMatch_woGwGSF_Barrel_Cut = 0.95;
//   float NoEleMatch_wGwoGSF_Barrel_Cut = 0.95;
//   float NoEleMatch_wGwGSF_Barrel_Cut = 0.95;
//   float woGwoGSF_Barrel_Cut = 0.95;
//   float woGwGSF_Barrel_Cut = 0.95;
//   float wGwoGSF_Barrel_Cut = 0.95;
//   float wGwGSF_Barrel_Cut = 0.95;
//   float NoEleMatch_woGwoGSF_Endcap_Cut = 0.95;
//   float NoEleMatch_woGwGSF_Endcap_Cut = 0.95;
//   float NoEleMatch_wGwoGSF_Endcap_Cut = 0.95;
//   float NoEleMatch_wGwGSF_Endcap_Cut = 0.95;
//   float woGwoGSF_Endcap_Cut = 0.95;
//   float woGwGSF_Endcap_Cut = 0.95;
//   float wGwoGSF_Endcap_Cut = 0.95;
//   float wGwGSF_Endcap_Cut = 0.95;

//   //v13EleVeto  S/B :35 : Eff : 0.82554311 : FR : 0.023563908 // TightMVA3WP
//   float NoEleMatch_woGwoGSF_Barrel_Cut = 0.78914332;
//   float NoEleMatch_woGwGSF_Barrel_Cut = 0.91818088;
//   float NoEleMatch_wGwoGSF_Barrel_Cut = 0.96754968;
//   float NoEleMatch_wGwGSF_Barrel_Cut = 0.98437631;
//   float woGwoGSF_Barrel_Cut = 0.96684271;
//   float woGwGSF_Barrel_Cut = 0.99065852;
//   float wGwoGSF_Barrel_Cut = 0.99797088;
//   float wGwGSF_Barrel_Cut = 0.96952927;
//   float NoEleMatch_woGwoGSF_Endcap_Cut = 0.1180589;
//   float NoEleMatch_woGwGSF_Endcap_Cut = 0.9714281;
//   float NoEleMatch_wGwoGSF_Endcap_Cut = 0.98451769;
//   float NoEleMatch_wGwGSF_Endcap_Cut = 0.99372888;
//   float woGwoGSF_Endcap_Cut = 0.84681427;
//   float woGwGSF_Endcap_Cut = 0.98940611;
//   float wGwoGSF_Endcap_Cut = 0.98308349;
//   float wGwGSF_Endcap_Cut = 0.97482169;

//   //v13EleVeto  // VTightMVA3WP
//   float NoEleMatch_woGwoGSF_Barrel_Cut = 0.89307231;
//   float NoEleMatch_woGwGSF_Barrel_Cut = 0.96239871;
//   float NoEleMatch_wGwoGSF_Barrel_Cut = 0.98247749;
//   float NoEleMatch_wGwGSF_Barrel_Cut = 0.99013329;
//   float woGwoGSF_Barrel_Cut = 0.9768821;
//   float woGwGSF_Barrel_Cut = 0.9958095;
//   float wGwoGSF_Barrel_Cut = 0.99797088;
//   float wGwGSF_Barrel_Cut = 0.98120493;
//   float NoEleMatch_woGwoGSF_Endcap_Cut = 0.60025311;
//   float NoEleMatch_woGwGSF_Endcap_Cut = 0.98320472;
//   float NoEleMatch_wGwoGSF_Endcap_Cut = 0.9897899;
//   float NoEleMatch_wGwGSF_Endcap_Cut = 0.9964357;
//   float woGwoGSF_Endcap_Cut = 0.88230568;
//   float woGwGSF_Endcap_Cut = 0.99132508;
//   float wGwoGSF_Endcap_Cut = 0.98467928;
//   float wGwGSF_Endcap_Cut = 0.98235631;

//   //v13EleVeto 0.92
//   float NoEleMatch_woGwoGSF_Barrel_Cut = 0.92;
//   float NoEleMatch_woGwGSF_Barrel_Cut = 0.92;
//   float NoEleMatch_wGwoGSF_Barrel_Cut = 0.92;
//   float NoEleMatch_wGwGSF_Barrel_Cut = 0.92;
//   float woGwoGSF_Barrel_Cut = 0.92;
//   float woGwGSF_Barrel_Cut = 0.92;
//   float wGwoGSF_Barrel_Cut = 0.92;
//   float wGwGSF_Barrel_Cut = 0.92;
//   float NoEleMatch_woGwoGSF_Endcap_Cut = 0.92;
//   float NoEleMatch_woGwGSF_Endcap_Cut = 0.92;
//   float NoEleMatch_wGwoGSF_Endcap_Cut = 0.92;
//   float NoEleMatch_wGwGSF_Endcap_Cut = 0.92;
//   float woGwoGSF_Endcap_Cut = 0.92;
//   float woGwGSF_Endcap_Cut = 0.92;
//   float wGwoGSF_Endcap_Cut = 0.92;
//   float wGwGSF_Endcap_Cut = 0.92;

//V13 differentialWP 

// //signal efficiency = 0.900006, fake-rate = 0.0350902(S/B = 25.6484)
//   float NoEleMatch_woGwoGSF_Barrel_Cut = 0.942;
//   float NoEleMatch_woGwGSF_Barrel_Cut = 0.945;
//   float NoEleMatch_wGwoGSF_Barrel_Cut = 0.944;
//   float NoEleMatch_wGwGSF_Barrel_Cut = 0.953;
//   float woGwoGSF_Barrel_Cut = 0.968;
//   float woGwGSF_Barrel_Cut = 0.928;
//   float wGwoGSF_Barrel_Cut = 0.94;
//   float wGwGSF_Barrel_Cut = 0.939;
//   float NoEleMatch_woGwoGSF_Endcap_Cut = 0.969;
//   float NoEleMatch_woGwGSF_Endcap_Cut = 0.953;
//   float NoEleMatch_wGwoGSF_Endcap_Cut = 0.95;
//   float NoEleMatch_wGwGSF_Endcap_Cut = 0.946;
//   float woGwoGSF_Endcap_Cut = 0.968;
//   float woGwGSF_Endcap_Cut = 0.969;
//   float wGwoGSF_Endcap_Cut = 0.9999;
//   float wGwGSF_Endcap_Cut = 0.941;

// //signal efficiency = 0.91002, fake-rate = 0.0383506(S/B = 23.729)
//   float NoEleMatch_woGwoGSF_Barrel_Cut = 0.942;
//   float NoEleMatch_woGwGSF_Barrel_Cut = 0.927;
//   float NoEleMatch_wGwoGSF_Barrel_Cut = 0.932;
//   float NoEleMatch_wGwGSF_Barrel_Cut = 0.939;
//   float woGwoGSF_Barrel_Cut = 0.958;
//   float woGwGSF_Barrel_Cut = 0.926;
//   float wGwoGSF_Barrel_Cut = 0.936;
//   float wGwGSF_Barrel_Cut = 0.927;
//   float NoEleMatch_woGwoGSF_Endcap_Cut = 0.962;
//   float NoEleMatch_woGwGSF_Endcap_Cut = 0.953;
//   float NoEleMatch_wGwoGSF_Endcap_Cut = 0.945;
//   float NoEleMatch_wGwGSF_Endcap_Cut = 0.946;
//   float woGwoGSF_Endcap_Cut = 0.968;
//   float woGwGSF_Endcap_Cut = 0.958;
//   float wGwoGSF_Endcap_Cut = 0.9999;
//   float wGwGSF_Endcap_Cut = 0.934;

// // // signal efficiency = 0.920062, fake-rate = 0.0423286(S/B = 21.7362)
//   float NoEleMatch_woGwoGSF_Barrel_Cut = 0.924;
//   float NoEleMatch_woGwGSF_Barrel_Cut = 0.927;
//   float NoEleMatch_wGwoGSF_Barrel_Cut = 0.918;
//   float NoEleMatch_wGwGSF_Barrel_Cut = 0.931;
//   float woGwoGSF_Barrel_Cut = 0.958;
//   float woGwGSF_Barrel_Cut = 0.915;
//   float wGwoGSF_Barrel_Cut = 0.936;
//   float wGwGSF_Barrel_Cut = 0.914;
//   float NoEleMatch_woGwoGSF_Endcap_Cut = 0.962;
//   float NoEleMatch_woGwGSF_Endcap_Cut = 0.943;
//   float NoEleMatch_wGwoGSF_Endcap_Cut = 0.945;
//   float NoEleMatch_wGwGSF_Endcap_Cut = 0.939;
//   float woGwoGSF_Endcap_Cut = 0.968;
//   float woGwGSF_Endcap_Cut = 0.937;
//   float wGwoGSF_Endcap_Cut = 0.9999;
//   float wGwGSF_Endcap_Cut = 0.909;

// // // signal efficiency = 0.920014, fake-rate = 0.0418472(S/B = 21.9851)
//   float NoEleMatch_woGwoGSF_Barrel_Cut = 0.924;
//   float NoEleMatch_woGwGSF_Barrel_Cut = 0.908;
//   float NoEleMatch_wGwoGSF_Barrel_Cut = 0.921;
//   float NoEleMatch_wGwGSF_Barrel_Cut = 0.922;
//   float woGwoGSF_Barrel_Cut = 0.914;
//   float woGwGSF_Barrel_Cut = 0.915;
//   float wGwoGSF_Barrel_Cut = 0.935;
//   float wGwGSF_Barrel_Cut = 0.921;
//   float NoEleMatch_woGwoGSF_Endcap_Cut = 0.915;
//   float NoEleMatch_woGwGSF_Endcap_Cut = 0.943;
//   float NoEleMatch_wGwoGSF_Endcap_Cut = 0.924;
//   float NoEleMatch_wGwGSF_Endcap_Cut = 0.922;
//   float woGwoGSF_Endcap_Cut = 0.897;
//   float woGwGSF_Endcap_Cut = 0.93;
//   float wGwoGSF_Endcap_Cut = 0.923;
//   float wGwGSF_Endcap_Cut = 0.918;

// // // // signal efficiency = 0.925042, fake-rate = 0.0439979(S/B = 21.0247)
//   float NoEleMatch_woGwoGSF_Barrel_Cut = 0.901;
//   float NoEleMatch_woGwGSF_Barrel_Cut = 0.895;
//   float NoEleMatch_wGwoGSF_Barrel_Cut = 0.917;
//   float NoEleMatch_wGwGSF_Barrel_Cut = 0.919;
//   float woGwoGSF_Barrel_Cut = 0.913;
//   float woGwGSF_Barrel_Cut = 0.906;
//   float wGwoGSF_Barrel_Cut = 0.905;
//   float wGwGSF_Barrel_Cut = 0.915;
//   float NoEleMatch_woGwoGSF_Endcap_Cut = 0.911;
//   float NoEleMatch_woGwGSF_Endcap_Cut = 0.932;
//   float NoEleMatch_wGwoGSF_Endcap_Cut = 0.92;
//   float NoEleMatch_wGwGSF_Endcap_Cut = 0.917;
//   float woGwoGSF_Endcap_Cut = 0.897;
//   float woGwGSF_Endcap_Cut = 0.926;
//   float wGwoGSF_Endcap_Cut = 0.918;
//   float wGwGSF_Endcap_Cut = 0.91;


//   // // signal efficiency = 0.925009, fake-rate = 0.0446222(S/B = 20.7298)
//   float NoEleMatch_woGwoGSF_Barrel_Cut = 0.921;
//   float NoEleMatch_woGwGSF_Barrel_Cut = 0.917;
//   float NoEleMatch_wGwoGSF_Barrel_Cut = 0.912;
//   float NoEleMatch_wGwGSF_Barrel_Cut = 0.913;
//   float woGwoGSF_Barrel_Cut = 0.958;
//   float woGwGSF_Barrel_Cut = 0.912;
//   float wGwoGSF_Barrel_Cut = 0.935;
//   float wGwGSF_Barrel_Cut = 0.905;
//   float NoEleMatch_woGwoGSF_Endcap_Cut = 0.955;
//   float NoEleMatch_woGwGSF_Endcap_Cut = 0.938;
//   float NoEleMatch_wGwoGSF_Endcap_Cut = 0.916;
//   float NoEleMatch_wGwGSF_Endcap_Cut = 0.929;
//   float woGwoGSF_Endcap_Cut = 0.968;
//   float woGwGSF_Endcap_Cut = 0.937;
//   float wGwoGSF_Endcap_Cut = 0.999999;
//   float wGwGSF_Endcap_Cut = 0.909;

//   // // signal efficiency = 0.930001, fake-rate = 0.0470746(S/B = 19.7559)
//   float NoEleMatch_woGwoGSF_Barrel_Cut = 0.895;
//   float NoEleMatch_woGwGSF_Barrel_Cut = 0.908;
//   float NoEleMatch_wGwoGSF_Barrel_Cut = 0.901;
//   float NoEleMatch_wGwGSF_Barrel_Cut = 0.913;
//   float woGwoGSF_Barrel_Cut = 0.958;
//   float woGwGSF_Barrel_Cut = 0.898;
//   float wGwoGSF_Barrel_Cut = 0.892;
//   float wGwGSF_Barrel_Cut = 0.901;
//   float NoEleMatch_woGwoGSF_Endcap_Cut = 0.941;
//   float NoEleMatch_woGwGSF_Endcap_Cut = 0.934;
//   float NoEleMatch_wGwoGSF_Endcap_Cut = 0.916;
//   float NoEleMatch_wGwGSF_Endcap_Cut = 0.911;
//   float woGwoGSF_Endcap_Cut = 0.968;
//   float woGwGSF_Endcap_Cut = 0.933;
//   float wGwoGSF_Endcap_Cut = 0.999999;
//   float wGwGSF_Endcap_Cut = 0.898;






  TCut CutEleVeto =Form("Tau_isInEcalCrack<0.5 && Tau_MatchElePassVeto<0.5 && NoEleMatch_woGwoGSF_Barrel>%f && NoEleMatch_woGwGSF_Barrel>%f && NoEleMatch_wGwoGSF_Barrel>%f && NoEleMatch_wGwGSF_Barrel>%f  && woGwoGSF_Barrel>%f && woGwGSF_Barrel>%f && wGwoGSF_Barrel>%f && wGwGSF_Barrel>%f && NoEleMatch_woGwoGSF_Endcap>%f && NoEleMatch_woGwGSF_Endcap>%f && NoEleMatch_wGwoGSF_Endcap>%f && NoEleMatch_wGwGSF_Endcap>%f  && woGwoGSF_Endcap>%f && woGwGSF_Endcap>%f && wGwoGSF_Endcap>%f && wGwGSF_Endcap>%f" ,
//   TCut CutEleVeto =Form("Tau_MatchElePassVeto<0.5 && NoEleMatch_woGwoGSF_Barrel>%f && NoEleMatch_woGwGSF_Barrel>%f && NoEleMatch_wGwoGSF_Barrel>%f && NoEleMatch_wGwGSF_Barrel>%f  && woGwoGSF_Barrel>%f && woGwGSF_Barrel>%f && wGwoGSF_Barrel>%f && wGwGSF_Barrel>%f && NoEleMatch_woGwoGSF_Endcap>%f && NoEleMatch_woGwGSF_Endcap>%f && NoEleMatch_wGwoGSF_Endcap>%f && NoEleMatch_wGwGSF_Endcap>%f  && woGwoGSF_Endcap>%f && woGwGSF_Endcap>%f && wGwoGSF_Endcap>%f && wGwGSF_Endcap>%f" ,
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


  TCut Cut =Form("Tau_isInEcalCrack<0.5  && NoEleMatch_woGwoGSF_Barrel>%f && NoEleMatch_woGwGSF_Barrel>%f && NoEleMatch_wGwoGSF_Barrel>%f && NoEleMatch_wGwGSF_Barrel>%f  && woGwoGSF_Barrel>%f && woGwGSF_Barrel>%f && wGwoGSF_Barrel>%f && wGwGSF_Barrel>%f && NoEleMatch_woGwoGSF_Endcap>%f && NoEleMatch_woGwGSF_Endcap>%f && NoEleMatch_wGwoGSF_Endcap>%f && NoEleMatch_wGwGSF_Endcap>%f  && woGwoGSF_Endcap>%f && woGwGSF_Endcap>%f && wGwoGSF_Endcap>%f && wGwGSF_Endcap>%f" ,
//   TCut Cut =Form("NoEleMatch_woGwoGSF_Barrel>%f && NoEleMatch_woGwGSF_Barrel>%f && NoEleMatch_wGwoGSF_Barrel>%f && NoEleMatch_wGwGSF_Barrel>%f  && woGwoGSF_Barrel>%f && woGwGSF_Barrel>%f && wGwoGSF_Barrel>%f && wGwGSF_Barrel>%f && NoEleMatch_woGwoGSF_Endcap>%f && NoEleMatch_woGwGSF_Endcap>%f && NoEleMatch_wGwoGSF_Endcap>%f && NoEleMatch_wGwGSF_Endcap>%f  && woGwoGSF_Endcap>%f && woGwGSF_Endcap>%f && wGwoGSF_Endcap>%f && wGwGSF_Endcap>%f" ,
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


//   TCut Cut = "Tau_AntiEMVA>0.5";
//   TCut CutEleVeto = "Tau_isInEcalCrack<0.5 && Tau_isInEcalCrack2<0.5 && Tau_MatchElePassVeto<0.5 && Tau_AntiEMVA>0.5";



  TH1F* hSig = new TH1F("hSig","",1,-10,10);
  tSig->Draw("Tau_GenEleMatch>>hSig","Tau_isInEcalCrack<0.5");
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
    tSig->Draw("Tau_GenEleMatch>>hSig","Category==0");
    nSig0 = hSig->GetEntries();
    tSig->Draw("Tau_GenEleMatch>>hSig","Category==1");
    nSig1 = hSig->GetEntries();
    tSig->Draw("Tau_GenEleMatch>>hSig","Category==2");
    nSig2 = hSig->GetEntries();
    tSig->Draw("Tau_GenEleMatch>>hSig","Category==3");
    nSig3 = hSig->GetEntries();
    tSig->Draw("Tau_GenEleMatch>>hSig","Category==4");
    nSig4 = hSig->GetEntries();
    tSig->Draw("Tau_GenEleMatch>>hSig","Category==5");
    nSig5 = hSig->GetEntries();
    tSig->Draw("Tau_GenEleMatch>>hSig","Category==6");
    nSig6 = hSig->GetEntries();
    tSig->Draw("Tau_GenEleMatch>>hSig","Category==7");
    nSig7 = hSig->GetEntries();
    tSig->Draw("Tau_GenEleMatch>>hSig","Category==8");
    nSig8 = hSig->GetEntries();
    tSig->Draw("Tau_GenEleMatch>>hSig","Category==9");
    nSig9 = hSig->GetEntries();
    tSig->Draw("Tau_GenEleMatch>>hSig","Category==10");
    nSig10 = hSig->GetEntries();
    tSig->Draw("Tau_GenEleMatch>>hSig","Category==11");
    nSig11 = hSig->GetEntries();
    tSig->Draw("Tau_GenEleMatch>>hSig","Category==12");
    nSig12 = hSig->GetEntries();
    tSig->Draw("Tau_GenEleMatch>>hSig","Category==13");
    nSig13 = hSig->GetEntries();
    tSig->Draw("Tau_GenEleMatch>>hSig","Category==14");
    nSig14 = hSig->GetEntries();
    tSig->Draw("Tau_GenEleMatch>>hSig","Category==15");
    nSig15 = hSig->GetEntries();
  }
  tSig->Draw("Tau_GenEleMatch>>hSig","Tau_MatchElePassVeto<0.5 && Tau_isInEcalCrack<0.5 ");
//   tSig->Draw("Tau_GenEleMatch>>hSig","Tau_MatchElePassVeto<0.5");
  float nSigEleVeto = hSig->GetEntries();
  tSig->Draw("Tau_GenEleMatch>>hSig","Tau_isInEcalCrack>0.5 ");
  float nSigCrack = hSig->GetEntries();
  if(details){
    tSig->Draw("Tau_GenEleMatch>>hSig","Tau_MatchElePassVeto<0.5 && Category==0");
    nSigEleVeto0 = hSig->GetEntries();
    tSig->Draw("Tau_GenEleMatch>>hSig","Tau_MatchElePassVeto<0.5 && Category==1");
    nSigEleVeto1 = hSig->GetEntries();
    tSig->Draw("Tau_GenEleMatch>>hSig","Tau_MatchElePassVeto<0.5 && Category==2");
    nSigEleVeto2 = hSig->GetEntries();
    tSig->Draw("Tau_GenEleMatch>>hSig","Tau_MatchElePassVeto<0.5 && Category==3");
    nSigEleVeto3 = hSig->GetEntries();
    tSig->Draw("Tau_GenEleMatch>>hSig","Tau_MatchElePassVeto<0.5 && Category==4");
    nSigEleVeto4 = hSig->GetEntries();
    tSig->Draw("Tau_GenEleMatch>>hSig","Tau_MatchElePassVeto<0.5 && Category==5");
    nSigEleVeto5 = hSig->GetEntries();
    tSig->Draw("Tau_GenEleMatch>>hSig","Tau_MatchElePassVeto<0.5 && Category==6");
    nSigEleVeto6 = hSig->GetEntries();
    tSig->Draw("Tau_GenEleMatch>>hSig","Tau_MatchElePassVeto<0.5 && Category==7");
    nSigEleVeto7 = hSig->GetEntries();
    tSig->Draw("Tau_GenEleMatch>>hSig","Tau_MatchElePassVeto<0.5 && Category==8");
    nSigEleVeto8 = hSig->GetEntries();
    tSig->Draw("Tau_GenEleMatch>>hSig","Tau_MatchElePassVeto<0.5 && Category==9");
    nSigEleVeto9 = hSig->GetEntries();
    tSig->Draw("Tau_GenEleMatch>>hSig","Tau_MatchElePassVeto<0.5 && Category==10");
    nSigEleVeto10 = hSig->GetEntries();
    tSig->Draw("Tau_GenEleMatch>>hSig","Tau_MatchElePassVeto<0.5 && Category==11");
    nSigEleVeto11 = hSig->GetEntries();
    tSig->Draw("Tau_GenEleMatch>>hSig","Tau_MatchElePassVeto<0.5 && Category==12");
    nSigEleVeto12 = hSig->GetEntries();
    tSig->Draw("Tau_GenEleMatch>>hSig","Tau_MatchElePassVeto<0.5 && Category==13");
    nSigEleVeto13 = hSig->GetEntries();
    tSig->Draw("Tau_GenEleMatch>>hSig","Tau_MatchElePassVeto<0.5 && Category==14");
    nSigEleVeto14 = hSig->GetEntries();
    tSig->Draw("Tau_GenEleMatch>>hSig","Tau_MatchElePassVeto<0.5 && Category==15");
    nSigEleVeto15 = hSig->GetEntries();
  }


  TH1F* hBkg = new TH1F("hBkg","",1,-10,10);
  tBkg->Draw("Tau_GenEleMatch>>hBkg","Tau_isInEcalCrack<0.5 ");
//   tBkg->Draw("Tau_GenEleMatch>>hBkg","");
  float nBkg = hBkg->GetEntries();
  if(details){
    tBkg->Draw("Tau_GenEleMatch>>hBkg","Category==0");
    nBkg0 = hBkg->GetEntries();
    tBkg->Draw("Tau_GenEleMatch>>hBkg","Category==1");
    nBkg1 = hBkg->GetEntries();
    tBkg->Draw("Tau_GenEleMatch>>hBkg","Category==2");
    nBkg2 = hBkg->GetEntries();
    tBkg->Draw("Tau_GenEleMatch>>hBkg","Category==3");
    nBkg3 = hBkg->GetEntries();
    tBkg->Draw("Tau_GenEleMatch>>hBkg","Category==4");
    nBkg4 = hBkg->GetEntries();
    tBkg->Draw("Tau_GenEleMatch>>hBkg","Category==5");
    nBkg5 = hBkg->GetEntries();
    tBkg->Draw("Tau_GenEleMatch>>hBkg","Category==6");
    nBkg6 = hBkg->GetEntries();
    tBkg->Draw("Tau_GenEleMatch>>hBkg","Category==7");
    nBkg7 = hBkg->GetEntries();
    tBkg->Draw("Tau_GenEleMatch>>hBkg","Category==8");
    nBkg8 = hBkg->GetEntries();
    tBkg->Draw("Tau_GenEleMatch>>hBkg","Category==9");
    nBkg9 = hBkg->GetEntries();
    tBkg->Draw("Tau_GenEleMatch>>hBkg","Category==10");
    nBkg10 = hBkg->GetEntries();
    tBkg->Draw("Tau_GenEleMatch>>hBkg","Category==11");
    nBkg11 = hBkg->GetEntries();
    tBkg->Draw("Tau_GenEleMatch>>hBkg","Category==12");
    nBkg12 = hBkg->GetEntries();
    tBkg->Draw("Tau_GenEleMatch>>hBkg","Category==13");
    nBkg13 = hBkg->GetEntries();
    tBkg->Draw("Tau_GenEleMatch>>hBkg","Category==14");
    nBkg14 = hBkg->GetEntries();
    tBkg->Draw("Tau_GenEleMatch>>hBkg","Category==15");
    nBkg15 = hBkg->GetEntries();
  }

  tBkg->Draw("Tau_GenEleMatch>>hBkg","Tau_MatchElePassVeto<0.5 && Tau_isInEcalCrack<0.5 ");
//   tBkg->Draw("Tau_GenEleMatch>>hBkg","Tau_MatchElePassVeto<0.5");
  float nBkgEleVeto = hBkg->GetEntries();
  tBkg->Draw("Tau_GenEleMatch>>hBkg","Tau_isInEcalCrack>0.5 ");
  float nBkgCrack = hBkg->GetEntries();
  if(details){
    tBkg->Draw("Tau_GenEleMatch>>hBkg","Tau_MatchElePassVeto<0.5 && Category==0");
    nBkgEleVeto0 = hBkg->GetEntries();
    tBkg->Draw("Tau_GenEleMatch>>hBkg","Tau_MatchElePassVeto<0.5 && Category==1");
    nBkgEleVeto1 = hBkg->GetEntries();
    tBkg->Draw("Tau_GenEleMatch>>hBkg","Tau_MatchElePassVeto<0.5 && Category==2");
    nBkgEleVeto2 = hBkg->GetEntries();
    tBkg->Draw("Tau_GenEleMatch>>hBkg","Tau_MatchElePassVeto<0.5 && Category==3");
    nBkgEleVeto3 = hBkg->GetEntries();
    tBkg->Draw("Tau_GenEleMatch>>hBkg","Tau_MatchElePassVeto<0.5 && Category==4");
    nBkgEleVeto4 = hBkg->GetEntries();
    tBkg->Draw("Tau_GenEleMatch>>hBkg","Tau_MatchElePassVeto<0.5 && Category==5");
    nBkgEleVeto5 = hBkg->GetEntries();
    tBkg->Draw("Tau_GenEleMatch>>hBkg","Tau_MatchElePassVeto<0.5 && Category==6");
    nBkgEleVeto6 = hBkg->GetEntries();
    tBkg->Draw("Tau_GenEleMatch>>hBkg","Tau_MatchElePassVeto<0.5 && Category==7");
    nBkgEleVeto7 = hBkg->GetEntries();
    tBkg->Draw("Tau_GenEleMatch>>hBkg","Tau_MatchElePassVeto<0.5 && Category==8");
    nBkgEleVeto8 = hBkg->GetEntries();
    tBkg->Draw("Tau_GenEleMatch>>hBkg","Tau_MatchElePassVeto<0.5 && Category==9");
    nBkgEleVeto9 = hBkg->GetEntries();
    tBkg->Draw("Tau_GenEleMatch>>hBkg","Tau_MatchElePassVeto<0.5 && Category==10");
    nBkgEleVeto10 = hBkg->GetEntries();
    tBkg->Draw("Tau_GenEleMatch>>hBkg","Tau_MatchElePassVeto<0.5 && Category==11");
    nBkgEleVeto11 = hBkg->GetEntries();
    tBkg->Draw("Tau_GenEleMatch>>hBkg","Tau_MatchElePassVeto<0.5 && Category==12");
    nBkgEleVeto12 = hBkg->GetEntries();
    tBkg->Draw("Tau_GenEleMatch>>hBkg","Tau_MatchElePassVeto<0.5 && Category==13");
    nBkgEleVeto13 = hBkg->GetEntries();
    tBkg->Draw("Tau_GenEleMatch>>hBkg","Tau_MatchElePassVeto<0.5 && Category==14");
    nBkgEleVeto14 = hBkg->GetEntries();
    tBkg->Draw("Tau_GenEleMatch>>hBkg","Tau_MatchElePassVeto<0.5 && Category==15");
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
  tSig->Draw("Tau_GenEleMatch>>hSigPass",Cut*"Tau_AntiEMVA>0.5");
  float nSigPassAndMVA = hSigPass->GetEntries();
  tSig->Draw("Tau_GenEleMatch>>hSigPass",CutEleVeto);
  float nSigPassEleVeto = hSigPass->GetEntries();
  tSig->Draw("Tau_GenEleMatch>>hSigPass",CutEleVeto*"Tau_AntiEMVA>0.5");
  float nSigPassEleVetoAndMVA = hSigPass->GetEntries();
  tSig->Draw("Tau_GenEleMatch>>hSigPass"," Tau_MatchElePassVeto<0.5 && Tau_AntiEMVA>0.5");
  float nSigPassLorenzoEleVeto = hSigPass->GetEntries();
  tSig->Draw("Tau_GenEleMatch>>hSigPass"," Tau_AntiEMVA>0.5");
  float nSigPassLorenzo = hSigPass->GetEntries();
  tSig->Draw("Tau_GenEleMatch>>hSigPass"," Tau_MatchElePassVeto<0.5 && Tau_AntiELoose>0.5");
  float nSigPassLooseEleVeto = hSigPass->GetEntries();
  tSig->Draw("Tau_GenEleMatch>>hSigPass"," Tau_AntiELoose>0.5");
  float nSigPassLoose = hSigPass->GetEntries();
  tSig->Draw("Tau_GenEleMatch>>hSigPass"," Tau_MatchElePassVeto<0.5 && Tau_AntiEMedium>0.5");
  float nSigPassMediumEleVeto = hSigPass->GetEntries();
  tSig->Draw("Tau_GenEleMatch>>hSigPass"," Tau_AntiEMedium>0.5");
  float nSigPassMedium = hSigPass->GetEntries(); 
  tSig->Draw("Tau_GenEleMatch>>hSigPass"," Tau_MatchElePassVeto<0.5 && Tau_AntiETight>0.5");
  float nSigPassTightEleVeto = hSigPass->GetEntries();
  tSig->Draw("Tau_GenEleMatch>>hSigPass"," Tau_AntiETight>0.5");
  float nSigPassTight = hSigPass->GetEntries();

  TH1F* hBkgPass = new TH1F("hBkgPass","",1,-10,10);
  tBkg->Draw("Tau_GenEleMatch>>hBkgPass",Cut);
  float nBkgPass = hBkgPass->GetEntries();
  tBkg->Draw("Tau_GenEleMatch>>hBkgPass",Cut*"Tau_AntiEMVA>0.5");
  float nBkgPassAndMVA = hBkgPass->GetEntries();
  tBkg->Draw("Tau_GenEleMatch>>hBkgPass",CutEleVeto);
  float nBkgPassEleVeto = hBkgPass->GetEntries();
  tBkg->Draw("Tau_GenEleMatch>>hBkgPass",CutEleVeto*"Tau_AntiEMVA>0.5");
  float nBkgPassEleVetoAndMVA = hBkgPass->GetEntries();
  tBkg->Draw("Tau_GenEleMatch>>hBkgPass"," Tau_MatchElePassVeto<0.5 && Tau_AntiEMVA>0.5");
  float nBkgPassLorenzoEleVeto = hBkgPass->GetEntries();
  tBkg->Draw("Tau_GenEleMatch>>hBkgPass"," Tau_AntiEMVA>0.5");
  float nBkgPassLorenzo = hBkgPass->GetEntries();
  tBkg->Draw("Tau_GenEleMatch>>hBkgPass"," Tau_MatchElePassVeto<0.5 && Tau_AntiELoose>0.5");
  float nBkgPassLooseEleVeto = hBkgPass->GetEntries();
  tBkg->Draw("Tau_GenEleMatch>>hBkgPass"," Tau_AntiELoose>0.5");
  float nBkgPassLoose = hBkgPass->GetEntries();
  tBkg->Draw("Tau_GenEleMatch>>hBkgPass"," Tau_MatchElePassVeto<0.5 && Tau_AntiEMedium>0.5");
  float nBkgPassMediumEleVeto = hBkgPass->GetEntries();
  tBkg->Draw("Tau_GenEleMatch>>hBkgPass"," Tau_AntiEMedium>0.5");
  float nBkgPassMedium = hBkgPass->GetEntries(); 
  tBkg->Draw("Tau_GenEleMatch>>hBkgPass"," Tau_MatchElePassVeto<0.5 && Tau_AntiETight>0.5");
  float nBkgPassTightEleVeto = hBkgPass->GetEntries();
  tBkg->Draw("Tau_GenEleMatch>>hBkgPass"," Tau_AntiETight>0.5");
  float nBkgPassTight = hBkgPass->GetEntries();

  if (DEBUG){
//     if(details){
//       cout<<"============================"<<endl;
//       cout<<"============================"<<endl;
      cout<<"Proba (Cat): "<<endl;
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
      cout<<"Proba (Cat): "<<endl;
      cout<<"Taus: "<<endl;
      cout<<"ProbaSig 0 :"<<nSigEleVeto0/nSigEleVeto<<endl;
      cout<<"ProbaSig 1 :"<<nSigEleVeto1/nSigEleVeto<<endl;
      cout<<"ProbaSig 2 :"<<nSigEleVeto2/nSigEleVeto<<endl;
      cout<<"ProbaSig 3 :"<<nSigEleVeto3/nSigEleVeto<<endl;
      cout<<"ProbaSig 4 :"<<nSigEleVeto4/nSigEleVeto<<endl;
      cout<<"ProbaSig 5 :"<<nSigEleVeto5/nSigEleVeto<<endl;
      cout<<"ProbaSig 6 :"<<nSigEleVeto6/nSigEleVeto<<endl;
      cout<<"ProbaSig 7 :"<<nSigEleVeto7/nSigEleVeto<<endl;
      cout<<"ProbaSig 8 :"<<nSigEleVeto8/nSigEleVeto<<endl;
      cout<<"ProbaSig 9 :"<<nSigEleVeto9/nSigEleVeto<<endl;
      cout<<"ProbaSig 10 :"<<nSigEleVeto10/nSigEleVeto<<endl;
      cout<<"ProbaSig 11 :"<<nSigEleVeto11/nSigEleVeto<<endl;
      cout<<"ProbaSig 12 :"<<nSigEleVeto12/nSigEleVeto<<endl;
      cout<<"ProbaSig 13 :"<<nSigEleVeto13/nSigEleVeto<<endl;
      cout<<"ProbaSig 14 :"<<nSigEleVeto14/nSigEleVeto<<endl;
      cout<<"ProbaSig 15 :"<<nSigEleVeto15/nSigEleVeto<<endl;
      cout<<"Total : "<<(nSigEleVeto0+nSigEleVeto1+nSigEleVeto2+nSigEleVeto3+nSigEleVeto4+nSigEleVeto5+nSigEleVeto6+nSigEleVeto7+nSigEleVeto8+nSigEleVeto9+nSigEleVeto10+nSigEleVeto11+nSigEleVeto12+nSigEleVeto13+nSigEleVeto14+nSigEleVeto15)/nSigEleVeto<<endl;
      cout<<"Electrons: "<<endl;
      cout<<"ProbaBkg 0 :"<<nBkgEleVeto0/nBkgEleVeto<<endl;
      cout<<"ProbaBkg 1 :"<<nBkgEleVeto1/nBkgEleVeto<<endl;
      cout<<"ProbaBkg 2 :"<<nBkgEleVeto2/nBkgEleVeto<<endl;
      cout<<"ProbaBkg 3 :"<<nBkgEleVeto3/nBkgEleVeto<<endl;
      cout<<"ProbaBkg 4 :"<<nBkgEleVeto4/nBkgEleVeto<<endl;
      cout<<"ProbaBkg 5 :"<<nBkgEleVeto5/nBkgEleVeto<<endl;
      cout<<"ProbaBkg 6 :"<<nBkgEleVeto6/nBkgEleVeto<<endl;
      cout<<"ProbaBkg 7 :"<<nBkgEleVeto7/nBkgEleVeto<<endl;
      cout<<"ProbaBkg 8 :"<<nBkgEleVeto8/nBkgEleVeto<<endl;
      cout<<"ProbaBkg 9 :"<<nBkgEleVeto9/nBkgEleVeto<<endl;
      cout<<"ProbaBkg 10 :"<<nBkgEleVeto10/nBkgEleVeto<<endl;
      cout<<"ProbaBkg 11 :"<<nBkgEleVeto11/nBkgEleVeto<<endl;
      cout<<"ProbaBkg 12 :"<<nBkgEleVeto12/nBkgEleVeto<<endl;
      cout<<"ProbaBkg 13 :"<<nBkgEleVeto13/nBkgEleVeto<<endl;
      cout<<"ProbaBkg 14 :"<<nBkgEleVeto14/nBkgEleVeto<<endl;
      cout<<"ProbaBkg 15 :"<<nBkgEleVeto15/nBkgEleVeto<<endl;
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
//     cout<<" Efficiency Combined with Lorenzo-> "<<nSigPassAndMVA/nSig<<endl;
//     cout<<" Efficiency Lorenzo-> "<<nSigPassLorenzo/nSig<<endl;
    cout<<" Efficiency Loose-> "<<nSigPassLoose/nSig<<endl;
    cout<<" Efficiency Medium-> "<<nSigPassMedium/nSig<<endl;
    cout<<" Efficiency Tight-> "<<nSigPassTight/nSig<<endl;
    cout<<" FakeRate -> "<<nBkgPass/nBkg<<endl;
//     cout<<" FakeRate combined with Lorenzo-> "<<nBkgPassAndMVA/nBkg<<endl;
//     cout<<" FakeRate Lorenzo-> "<<nBkgPassLorenzo/nBkg<<endl;
    cout<<" FakeRate Loose-> "<<nBkgPassLoose/nBkg<<endl;
    cout<<" FakeRate Medium-> "<<nBkgPassMedium/nBkg<<endl;
    cout<<" FakeRate Tight-> "<<nBkgPassTight/nBkg<<endl;
    cout<<endl;
    cout<<"============================"<<endl;
    cout<<"WP : "<<WP.data() <<endl;
    cout<<"Eff and FR : "<<endl;
    cout<<"After secondEleVeto: "<<endl;
    cout<<" Efficiency -> "<<nSigPassEleVeto/nSigEleVeto<<endl;
//     cout<<" Efficiency combined with Lorenzo-> "<<nSigPassEleVetoAndMVA/nSigEleVeto<<endl;
//     cout<<" Efficiency Lorenzo-> "<<nSigPassLorenzoEleVeto/nSigEleVeto<<endl;
    cout<<" Efficiency Loose-> "<<nSigPassLooseEleVeto/nSigEleVeto<<endl;
    cout<<" Efficiency Medium-> "<<nSigPassMediumEleVeto/nSigEleVeto<<endl;
    cout<<" Efficiency Tight-> "<<nSigPassTightEleVeto/nSigEleVeto<<endl;
    cout<<" FakeRate -> "<<nBkgPassEleVeto/nBkgEleVeto<<endl;
//     cout<<" FakeRate combined with Lorenzo-> "<<nBkgPassEleVetoAndMVA/nBkgEleVeto<<endl;
//     cout<<" FakeRate Lorenzo-> "<<nBkgPassLorenzoEleVeto/nBkgEleVeto<<endl;
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
//   compute("WP75",
// 	   0.986,
// 	   0.986,
// 	   0.986,
// 	   0.99,
// 	   0.983,
// 	   0.977,
// 	   0.992,
// 	   0.981,
// 	   0.989,
// 	   0.989,
// 	   0.987,
// 	   0.987,
// 	   0.976,
// 	   0.991,
// 	   0.984,
// 	   0.986);
//   compute("WP76",
// 	   0.986,
// 	   0.984,
// 	   0.985,
// 	   0.989,
// 	   0.983,
// 	   0.977,
// 	   0.991,
// 	   0.98,
// 	   0.988,
// 	   0.988,
// 	   0.986,
// 	   0.986,
// 	   0.975,
// 	   0.988,
// 	   0.983,
// 	   0.985);
//   compute("WP77",
// 	   0.984,
// 	   0.982,
// 	   0.984,
// 	   0.988,
// 	   0.977,
// 	   0.975,
// 	   0.991,
// 	   0.979,
// 	   0.988,
// 	   0.984,
// 	   0.986,
// 	   0.985,
// 	   0.973,
// 	   0.987,
// 	   0.983,
// 	   0.984);
//   compute("WP78",
// 	   0.981,
// 	   0.981,
// 	   0.983,
// 	   0.987,
// 	   0.977,
// 	   0.975,
// 	   0.99,
// 	   0.978,
// 	   0.987,
// 	   0.983,
// 	   0.985,
// 	   0.984,
// 	   0.972,
// 	   0.987,
// 	   0.977,
// 	   0.983);
  compute("WP79",
	   0.978,
	   0.98,
	   0.982,
	   0.985,
	   0.977,
	   0.974,
	   0.989,
	   0.977,
	   0.986,
	   0.983,
	   0.984,
	   0.983,
	   0.971,
	   0.987,
	   0.977,
	   0.981);
//   compute("WP80",
// 	   0.977,
// 	   0.978,
// 	   0.98,
// 	   0.982,
// 	   0.972,
// 	   0.973,
// 	   0.987,
// 	   0.976,
// 	   0.985,
// 	   0.982,
// 	   0.983,
// 	   0.981,
// 	   0.969,
// 	   0.977,
// 	   0.977,
// 	   0.98);
//   compute("WP81",
// 	   0.977,
// 	   0.977,
// 	   0.979,
// 	   0.979,
// 	   0.971,
// 	   0.972,
// 	   0.985,
// 	   0.974,
// 	   0.984,
// 	   0.978,
// 	   0.982,
// 	   0.98,
// 	   0.968,
// 	   0.976,
// 	   0.976,
// 	   0.979);
//   compute("WP82",
// 	   0.974,
// 	   0.976,
// 	   0.978,
// 	   0.978,
// 	   0.971,
// 	   0.969,
// 	   0.982,
// 	   0.972,
// 	   0.982,
// 	   0.977,
// 	   0.981,
// 	   0.978,
// 	   0.897,
// 	   0.976,
// 	   0.975,
// 	   0.977);
//   compute("WP83",
// 	   0.972,
// 	   0.973,
// 	   0.976,
// 	   0.975,
// 	   0.97,
// 	   0.966,
// 	   0.981,
// 	   0.97,
// 	   0.98,
// 	   0.976,
// 	   0.979,
// 	   0.976,
// 	   0.897,
// 	   0.975,
// 	   0.969,
// 	   0.975);
//   compute("WP84",
// 	   0.969,
// 	   0.97,
// 	   0.974,
// 	   0.974,
// 	   0.97,
// 	   0.962,
// 	   0.977,
// 	   0.967,
// 	   0.977,
// 	   0.974,
// 	   0.978,
// 	   0.974,
// 	   0.897,
// 	   0.972,
// 	   0.969,
// 	   0.974);
  compute("WP85",
	   0.96,
	   0.968,
	   0.971,
	   0.972,
	   0.969,
	   0.959,
	   0.977,
	   0.965,
	   0.975,
	   0.972,
	   0.974,
	   0.971,
	   0.897,
	   0.971,
	   0.961,
	   0.97);
//   compute("WP86",
// 	   0.957,
// 	   0.967,
// 	   0.967,
// 	   0.967,
// 	   0.968,
// 	   0.956,
// 	   0.973,
// 	   0.962,
// 	   0.973,
// 	   0.972,
// 	   0.97,
// 	   0.969,
// 	   0.897,
// 	   0.969,
// 	   0.961,
// 	   0.966);
//   compute("WP87",
// 	   0.951,
// 	   0.965,
// 	   0.964,
// 	   0.964,
// 	   0.967,
// 	   0.953,
// 	   0.957,
// 	   0.959,
// 	   0.971,
// 	   0.97,
// 	   0.966,
// 	   0.967,
// 	   0.897,
// 	   0.964,
// 	   0.952,
// 	   0.959);
//   compute("WP88",
// 	   0.948,
// 	   0.95,
// 	   0.96,
// 	   0.962,
// 	   0.967,
// 	   0.95,
// 	   0.952,
// 	   0.953,
// 	   0.971,
// 	   0.969,
// 	   0.96,
// 	   0.964,
// 	   0.897,
// 	   0.958,
// 	   0.949,
// 	   0.957);
//   compute("WP89",
// 	   0.937,
// 	   0.949,
// 	   0.955,
// 	   0.956,
// 	   0.962,
// 	   0.934,
// 	   0.946,
// 	   0.948,
// 	   0.959,
// 	   0.95,
// 	   0.954,
// 	   0.954,
// 	   0.897,
// 	   0.951,
// 	   0.948,
// 	   0.953);
  compute("WP90",
	   0.933,
	   0.921,
	   0.944,
	   0.945,
	   0.918,
	   0.923,
	   0.944,
	   0.943,
	   0.956,
	   0.947,
	   0.951,
	   0.95,
	   0.897,
	   0.942,
	   0.938,
	   0.942);
//   compute("WP91",
// 	   0.931,
// 	   0.917,
// 	   0.937,
// 	   0.941,
// 	   0.915,
// 	   0.921,
// 	   0.942,
// 	   0.929,
// 	   0.944,
// 	   0.946,
// 	   0.948,
// 	   0.947,
// 	   0.897,
// 	   0.934,
// 	   0.931,
// 	   0.936);
//   compute("WP92",
// 	   0.924,
// 	   0.908,
// 	   0.921,
// 	   0.922,
// 	   0.914,
// 	   0.915,
// 	   0.935,
// 	   0.921,
// 	   0.915,
// 	   0.943,
// 	   0.924,
// 	   0.922,
// 	   0.897,
// 	   0.93,
// 	   0.923,
// 	   0.918);
//   compute("WP925",
// 	   0.901,
// 	   0.895,
// 	   0.917,
// 	   0.919,
// 	   0.913,
// 	   0.906,
// 	   0.905,
// 	   0.915,
// 	   0.911,
// 	   0.932,
// 	   0.92,
// 	   0.917,
// 	   0.897,
// 	   0.926,
// 	   0.918,
// 	   0.91);
//   compute("WP93",
// 	   0.884,
// 	   0.886,
// 	   0.91,
// 	   0.902,
// 	   0.894,
// 	   0.898,
// 	   0.897,
// 	   0.907,
// 	   0.908,
// 	   0.931,
// 	   0.917,
// 	   0.914,
// 	   0.897,
// 	   0.913,
// 	   0.882,
// 	   0.9);
//   compute("WP94",
// 	   0.873,
// 	   0.863,
// 	   0.873,
// 	   0.883,
// 	   0.879,
// 	   0.861,
// 	   0.887,
// 	   0.887,
// 	   0.908,
// 	   0.909,
// 	   0.875,
// 	   0.885,
// 	   0.896,
// 	   0.881,
// 	   0.881,
// 	   0.883);
  compute("WP95",
	   0.835,
	   0.831,
	   0.849,
	   0.859,
	   0.873,
	   0.823,
	   0.85,
	   0.855,
	   0.816,
	   0.861,
	   0.862,
	   0.847,
	   0.893,
	   0.82,
	   0.845,
	   0.851);




	   }
