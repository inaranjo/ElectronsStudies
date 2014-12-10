//--------------------------------------------------------------------------------------------------
// AntiElectronMVAApplication
//
// Macro applying the trained AntiEMVA to the rootTrees of the AntiEMVA Analyzer. 
// It also classifies the ouput Rootfiles in 4 categories. These trees will be used as input of the cut
// optimization (tmva/tmvaAntiElectronOptimization.C)
//
// Authors: I.Naranjo
//--------------------------------------------------------------------------------------------------

#include <TFile.h>
#include <TMath.h>

#include "TMVA/Tools.h"
#include "TMVA/Reader.h"

#include <vector>
#include <string>
#include <iostream>
#include <iomanip>
#include "CondFormats/EgammaObjects/interface/GBRForest.h"
#include "Cintex/Cintex.h"

using namespace std;

int isInEcalCrack(Float_t eta) 
{
  eta = fabs(eta);
  if (eta>1.460 && eta<1.558)return 1.0;
  else return 0.;
}

int isInEcalCrack2(Float_t eta) 
{
  eta = fabs(eta);
  if (eta < 0.018 ||
      (eta>0.423 && eta<0.461) ||
      (eta>0.770 && eta<0.806) ||
      (eta>1.127 && eta<1.163)) return 1.0;
  else return 0.;
}

//useful to compute the signed distance to the closest crack in the barrel
double minimum(double a,double b){
  if(TMath::Abs(b)<TMath::Abs(a)) return b;
  else return a;
}

//compute the unsigned distance to the closest phi-crack in the barrel
double dCrackPhi(double phi, double eta){

  double pi= TMath::Pi();// 3.14159265358979323846;
  
  //Location of the 18 phi-cracks
  static std::vector<double> cPhi;
  if(cPhi.size()==0)
    {
      cPhi.resize(18,0);
      cPhi[0]=2.97025;
      for(unsigned i=1;i<=17;++i) cPhi[i]=cPhi[0]-2*i*pi/18;
    }

  //Shift of this location if eta<0
  double delta_cPhi=0.00638;

  double m; //the result

  if (eta>=- 1.47464 && eta<= 1.47464){

    //the location is shifted
    if(eta<0) phi +=delta_cPhi;

    if (phi>=-pi && phi<=pi){

      //the problem of the extrema
      if (phi<cPhi[17] || phi>=cPhi[0]){
	if (phi<0) phi+= 2*pi;
	m = minimum(phi -cPhi[0],phi-cPhi[17]-2*pi);        	
      }

      //between these extrema...
      else{
	bool OK = false;
	unsigned i=16;
	while(!OK){
	  if (phi<cPhi[i]){
	    m=minimum(phi-cPhi[i+1],phi-cPhi[i]);
	    OK=true;
	  }
	  else i-=1;
	}
      }
    }
    else{
      m=0.;        //if there is a problem, we assum that we are in a crack
      //std::cout<<"Problem in dminphi"<<std::endl;
    }
  }
  else{
    return -99.;       
    std::cout<<"Encap region"<<std::endl;
  }
  
  return TMath::Abs(m);
}

//compute the unsigned distance to the closest phi-crack in the barrel
double dCrackEta(double eta){
  
  //Location of the eta-cracks
  double cracks[5] = {0, 4.44747e-01, 7.92824e-01, 1.14090e+00, 1.47464e+00};
  
  double m=99.; //the result
  
  for(int i=0;i<5;i++){
    double d = minimum(eta-cracks[i], eta+cracks[i]);
    if (TMath::Abs(d)<TMath::Abs(m)){
      m=d;
    }
  }

  return TMath::Abs(m);
}

//Creates rootFile with a TTree with the ouput of MVA in it.
void MVAOutput(string discriminator = "",
	       string Type = "Signal"
	       )
{
//   std::string inputFileName ="/data_CMS/cms/ivo/AntiEMVA/Trees/AntiEMVA_Fall11DYJetsToLL-iter4.root";
//   std::string inputFileName ="/data_CMS/cms/ivo/AntiEMVA/Trees/Trees_ForV4/AntiEMVA_AntiEMVATrees-DYJetsToLL-madgraph-PUS6.root";
//   std::string inputFileName ="/data_CMS/cms/ivo/AntiEMVA/Trees/Trees_ForV4/AntiEMVA_V4.root";
//   std::string inputFileName ="/data_CMS/cms/ivo/AntiEMVA/Trees/Trees_ForV6/AntiEMVA_V6.root";
//   std::string inputFileName ="/data_CMS/cms/ivo/AntiEMVA/Trees/Trees_ForV6AndV7/AntiEMVA_AntiEMVATrees-DYJetsToLL-madgraph-PUS7-Summer12-iter1.root";
//   std::string inputFileName ="/data_CMS/cms/ivo/AntiEMVA/Trees/Trees_ForV9V10V11/AntiEMVA_AntiEMVATrees-DYJetsToLL-madgraph-DR53X-Summer12.root";
//   std::string inputFileName ="/data_CMS/cms/ivo/AntiEMVA/Trees/Trees_ForV9/AntiEMVA_V9.root";
//   std::string inputFileName = Form("/data_CMS/cms/ivo/AntiEMVA/Trees/AntiEMVA_Fall11DYJetsToLL%s-iter3.root",discriminator.data());
  std::string inputFileName ="/data_CMS/cms/ivo/AntiEMVA/Trees/Trees_ForV13/AntiEMVA_AntiEMVATrees-DYJetsToLL-madgraph-DR53X-Summer12-iter2.root";
  TFile* inputFile = new TFile (inputFileName.data(),"READ");
  if(inputFile->IsZombie()){
    cout << "No such file!" << endl;
    return;
  }

  //open input root file
  TFile *fin = new TFile("gbrtest.root","READ");
  if(fin->IsZombie()){
    cout << "No such file!" << endl;
    return;
  }

//   std::string outputFileName = Form("/data_CMS/cms/ivo/AntiEMVA/Trees/MVAOutput/MvaOutput_AntiEMVA-DYJetsToLL_v4%s_%s.root",discriminator.data(),Type.data());
//   std::string outputFileName = Form("/data_CMS/cms/ivo/AntiEMVA/Trees/MVAOutput/MvaOutput_AntiEMVA_v4%s_%s.root",discriminator.data(),Type.data());
//   std::string outputFileName = Form("/data_CMS/cms/ivo/AntiEMVA/Trees/MVAOutput/MvaOutput_AntiEMVA-v5%s_%s.root",discriminator.data(),Type.data());
//   std::string outputFileName = Form("/data_CMS/cms/ivo/AntiEMVA/Trees/MVAOutput/MvaOutput_AntiEMVA-v6%s_%s.root",discriminator.data(),Type.data());
//   std::string outputFileName = Form("/data_CMS/cms/ivo/AntiEMVA/Trees/MVAOutput/TestMvaOutput_AntiEMVA-v6-DYJets%s_%s.root",discriminator.data(),Type.data());
//   std::string outputFileName = Form("/data_CMS/cms/ivo/AntiEMVA/Trees/MVAOutput/TestMvaOutput_AntiEMVA-v7-DYJets%s_%s.root",discriminator.data(),Type.data());
//   std::string outputFileName = Form("/data_CMS/cms/ivo/AntiEMVA/Trees/MVAOutput/TestMvaOutput_AntiEMVA-v8Bis-DYJets%s_%s.root",discriminator.data(),Type.data());
//   std::string outputFileName = Form("/data_CMS/cms/ivo/AntiEMVA/Trees/MVAOutput/MvaOutput_AntiEMVA-v9NoEleVeto-DYJets%s_%s.root",discriminator.data(),Type.data());
//   std::string outputFileName = Form("/data_CMS/cms/ivo/AntiEMVA/Trees/MVAOutput/MvaOutput_AntiEMVA-v9EleVeto-DYJetsIvo%s_%s.root",discriminator.data(),Type.data());
//   std::string outputFileName = Form("/data_CMS/cms/ivo/AntiEMVA/Trees/MVAOutput/MvaOutput_AntiEMVA-v11EleVeto-DYJetsIvo%s_%s.root",discriminator.data(),Type.data());
//   std::string outputFileName = Form("/data_CMS/cms/ivo/AntiEMVA/Trees/MVAOutput/MvaOutput_AntiEMVA-v11DYEleVeto-GeneralIvo%s_%s.root",discriminator.data(),Type.data());
//   std::string outputFileName = Form("/data_CMS/cms/ivo/AntiEMVA/Trees/MVAOutput/MvaOutput_AntiEMVA-v12EleVeto-DYJetsIvo%s_%s.root",discriminator.data(),Type.data());
  std::string outputFileName = Form("/data_CMS/cms/ivo/AntiEMVA/Trees/MVAOutput/GBRForest_MvaOutput_AntiEMVA-v13EleVeto-DYJets%s_%s.root",discriminator.data(),Type.data());
  TFile* outputFile = new TFile (outputFileName.data(),"RECREATE");
  TTree* mytree = new TTree("tree", "tree");

  float t_NoEleMatch_woGwoGSF_Barrel;
  float t_NoEleMatch_woGwGSF_Barrel;
  float t_NoEleMatch_wGwoGSF_Barrel;
  float t_NoEleMatch_wGwGSF_Barrel;
  float t_woGwoGSF_Barrel;
  float t_woGwGSF_Barrel;
  float t_wGwoGSF_Barrel;
  float t_wGwGSF_Barrel;
  float t_NoEleMatch_woGwoGSF_Endcap;
  float t_NoEleMatch_woGwGSF_Endcap;
  float t_NoEleMatch_wGwoGSF_Endcap;
  float t_NoEleMatch_wGwGSF_Endcap;
  float t_woGwoGSF_Endcap;
  float t_woGwGSF_Endcap;
  float t_wGwoGSF_Endcap;
  float t_wGwGSF_Endcap;

  float t_NoEleMatch_woGwoGSF_BarrelXML;
  float t_NoEleMatch_woGwGSF_BarrelXML;
  float t_NoEleMatch_wGwoGSF_BarrelXML;
  float t_NoEleMatch_wGwGSF_BarrelXML;
  float t_woGwoGSF_BarrelXML;
  float t_woGwGSF_BarrelXML;
  float t_wGwoGSF_BarrelXML;
  float t_wGwGSF_BarrelXML;
  float t_NoEleMatch_woGwoGSF_EndcapXML;
  float t_NoEleMatch_woGwGSF_EndcapXML;
  float t_NoEleMatch_wGwoGSF_EndcapXML;
  float t_NoEleMatch_wGwGSF_EndcapXML;
  float t_woGwoGSF_EndcapXML;
  float t_woGwGSF_EndcapXML;
  float t_wGwoGSF_EndcapXML;
  float t_wGwGSF_EndcapXML;

  int t_Elec_GenEleMatch;
  int t_Elec_GenHadMatch;
  int t_Tau_GenEleMatch;
  int t_Tau_GenHadMatch;
  
  float t_Tau_IsoMVALoose;
  float t_Tau_Eta;
  float t_Tau_Pt;

  int t_Tau_AntiELoose;
  int t_Tau_AntiEMedium;
  int t_Tau_AntiETight;
  int t_Tau_AntiEMVA;
  int t_Tau_MatchElePassVeto;
  int t_Tau_isInEcalCrack;
  int t_Tau_isInEcalCrack2;

  int t_Category;
  float t_rawMva;
  float t_rawMvaXML;

  mytree->Branch("NoEleMatch_woGwoGSF_Barrel",&t_NoEleMatch_woGwoGSF_Barrel,"NoEleMatch_woGwoGSF_Barrel/F");
  mytree->Branch("NoEleMatch_woGwGSF_Barrel",&t_NoEleMatch_woGwGSF_Barrel,"NoEleMatch_woGwGSF_Barrel/F");
  mytree->Branch("NoEleMatch_wGwoGSF_Barrel",&t_NoEleMatch_wGwoGSF_Barrel,"NoEleMatch_wGwoGSF_Barrel/F");
  mytree->Branch("NoEleMatch_wGwGSF_Barrel",&t_NoEleMatch_wGwGSF_Barrel,"NoEleMatch_wGwGSF_Barrel/F");
  mytree->Branch("woGwoGSF_Barrel",&t_woGwoGSF_Barrel,"woGwoGSF_Barrel/F");
  mytree->Branch("woGwGSF_Barrel",&t_woGwGSF_Barrel,"woGwGSF_Barrel/F");
  mytree->Branch("wGwoGSF_Barrel",&t_wGwoGSF_Barrel,"wGwoGSF_Barrel/F");
  mytree->Branch("wGwGSF_Barrel",&t_wGwGSF_Barrel,"wGwGSF_Barrel/F");
  mytree->Branch("NoEleMatch_woGwoGSF_Endcap",&t_NoEleMatch_woGwoGSF_Endcap,"NoEleMatch_woGwoGSF_Endcap/F");
  mytree->Branch("NoEleMatch_woGwGSF_Endcap",&t_NoEleMatch_woGwGSF_Endcap,"NoEleMatch_woGwGSF_Endcap/F");
  mytree->Branch("NoEleMatch_wGwoGSF_Endcap",&t_NoEleMatch_wGwoGSF_Endcap,"NoEleMatch_wGwoGSF_Endcap/F");
  mytree->Branch("NoEleMatch_wGwGSF_Endcap",&t_NoEleMatch_wGwGSF_Endcap,"NoEleMatch_wGwGSF_Endcap/F");
  mytree->Branch("woGwoGSF_Endcap",&t_woGwoGSF_Endcap,"woGwoGSF_Endcap/F");
  mytree->Branch("woGwGSF_Endcap",&t_woGwGSF_Endcap,"woGwGSF_Endcap/F");
  mytree->Branch("wGwoGSF_Endcap",&t_wGwoGSF_Endcap,"wGwoGSF_Endcap/F");
  mytree->Branch("wGwGSF_Endcap",&t_wGwGSF_Endcap,"wGwGSF_Endcap/F");

  mytree->Branch("NoEleMatch_woGwoGSF_BarrelXML",&t_NoEleMatch_woGwoGSF_BarrelXML,"NoEleMatch_woGwoGSF_BarrelXML/F");
  mytree->Branch("NoEleMatch_woGwGSF_BarrelXML",&t_NoEleMatch_woGwGSF_BarrelXML,"NoEleMatch_woGwGSF_BarrelXML/F");
  mytree->Branch("NoEleMatch_wGwoGSF_BarrelXML",&t_NoEleMatch_wGwoGSF_BarrelXML,"NoEleMatch_wGwoGSF_BarrelXML/F");
  mytree->Branch("NoEleMatch_wGwGSF_BarrelXML",&t_NoEleMatch_wGwGSF_BarrelXML,"NoEleMatch_wGwGSF_BarrelXML/F");
  mytree->Branch("woGwoGSF_BarrelXML",&t_woGwoGSF_BarrelXML,"woGwoGSF_BarrelXML/F");
  mytree->Branch("woGwGSF_BarrelXML",&t_woGwGSF_BarrelXML,"woGwGSF_BarrelXML/F");
  mytree->Branch("wGwoGSF_BarrelXML",&t_wGwoGSF_BarrelXML,"wGwoGSF_BarrelXML/F");
  mytree->Branch("wGwGSF_BarrelXML",&t_wGwGSF_BarrelXML,"wGwGSF_BarrelXML/F");
  mytree->Branch("NoEleMatch_woGwoGSF_EndcapXML",&t_NoEleMatch_woGwoGSF_EndcapXML,"NoEleMatch_woGwoGSF_EndcapXML/F");
  mytree->Branch("NoEleMatch_woGwGSF_EndcapXML",&t_NoEleMatch_woGwGSF_EndcapXML,"NoEleMatch_woGwGSF_EndcapXML/F");
  mytree->Branch("NoEleMatch_wGwoGSF_EndcapXML",&t_NoEleMatch_wGwoGSF_EndcapXML,"NoEleMatch_wGwoGSF_EndcapXML/F");
  mytree->Branch("NoEleMatch_wGwGSF_EndcapXML",&t_NoEleMatch_wGwGSF_EndcapXML,"NoEleMatch_wGwGSF_EndcapXML/F");
  mytree->Branch("woGwoGSF_EndcapXML",&t_woGwoGSF_EndcapXML,"woGwoGSF_EndcapXML/F");
  mytree->Branch("woGwGSF_EndcapXML",&t_woGwGSF_EndcapXML,"woGwGSF_EndcapXML/F");
  mytree->Branch("wGwoGSF_EndcapXML",&t_wGwoGSF_EndcapXML,"wGwoGSF_EndcapXML/F");
  mytree->Branch("wGwGSF_EndcapXML",&t_wGwGSF_EndcapXML,"wGwGSF_EndcapXML/F");

  mytree->Branch("Elec_GenEleMatch",&t_Elec_GenEleMatch,"Elec_GenEleMatch/I");
  mytree->Branch("Elec_GenHadMatch",&t_Elec_GenHadMatch,"Elec_GenHadMatch/I");
  mytree->Branch("Tau_GenEleMatch",&t_Tau_GenEleMatch,"Tau_GenEleMatch/I");
  mytree->Branch("Tau_GenHadMatch",&t_Tau_GenHadMatch,"Tau_GenHadMatch/I");

  mytree->Branch("Tau_IsoMVALoose",&t_Tau_IsoMVALoose,"Tau_IsoMVALoose/F");
  mytree->Branch("Tau_Eta",&t_Tau_Eta,"Tau_Eta/F");
  mytree->Branch("Tau_Pt",&t_Tau_Pt,"Tau_Pt/F");

  mytree->Branch("Tau_AntiELoose",&t_Tau_AntiELoose,"Tau_AntiELoose/I");
  mytree->Branch("Tau_AntiEMedium",&t_Tau_AntiEMedium,"Tau_AntiEMedium/I");
  mytree->Branch("Tau_AntiETight",&t_Tau_AntiETight,"Tau_AntiETight/I");
  mytree->Branch("Tau_AntiEMVA",&t_Tau_AntiEMVA,"Tau_AntiEMVA/I");
  mytree->Branch("Tau_MatchElePassVeto",&t_Tau_MatchElePassVeto,"Tau_MatchElePassVeto/I");
  mytree->Branch("Tau_isInEcalCrack",&t_Tau_isInEcalCrack,"Tau_isInEcalCrack/I");
  mytree->Branch("Tau_isInEcalCrack2",&t_Tau_isInEcalCrack2,"Tau_isInEcalCrack2/I");

  mytree->Branch("Category",&t_Category,"Category/I");
  mytree->Branch("rawMva",&t_rawMva,"rawMva/F");
  mytree->Branch("rawMvaXML",&t_rawMvaXML,"rawMvaXML/F");

  TTree* inputTree = (TTree*)inputFile->Get("AntiEMVAAnalyzer2/tree");
//   TTree* inputTree = (TTree*)inputFile->Get("AntiEMVAAnalyzer2/tree");
  int nEntries = inputTree->GetEntries();

  ULong64_t run,event,lumi;
  int NumPV;
  int NumGsfEle;
  int NumPFTaus;
  int NumGenEle;
  int NumGenHad;
  int NumGenJet;

  int Tau_GsfEleMatch;
  int Tau_GenEleMatch;
  int Tau_GenEleFromZMatch;
  int Tau_GenEleFromZTauTauMatch;
  int Tau_GenHadMatch;
  int Tau_GenJetMatch;
  float Tau_AbsEta;
  float Tau_Eta;
  float Tau_EtaAtEcalEntrance;
  float Tau_PhiAtEcalEntrance;
  float Tau_Pt;
  float Tau_KFNumHits; 
  float Tau_HasGsf; 
  float Tau_GSFChi2; 
  float Tau_GSFNumHits; 
  float Tau_GSFTrackResol; 
  float Tau_GSFTracklnPt; 
  float Tau_GSFTrackEta; 
  float Tau_EmFraction; 
  float Tau_NumChargedCands;
  float Tau_NumGammaCands; 
  float Tau_HadrHoP; 
  float Tau_HadrEoP; 
  float Tau_VisMass; 
  float Tau_GammaEtaMom;
  float Tau_GammaPhiMom;
  float Tau_GammaEnFrac;
  float Tau_HadrMva; 
  float Tau_IsoMVALoose; 
  float Tau_AntiELoose; 
  float Tau_AntiEMedium; 
  float Tau_AntiETight; 
  float Tau_AntiEMVA; 
//   float Tau_MatchElePassVeto; 

  int Elec_GenEleMatch;
  int Elec_GenEleFromZMatch;
  int Elec_GenEleFromZTauTauMatch;
  int Elec_GenHadMatch;
  int Elec_GenJetMatch;
  float Elec_AbsEta;
  float Elec_Pt;
  float Elec_HasSC;
  float Elec_PFMvaOutput;
  float Elec_EtotOverPin;
  float Elec_EeOverPout;
  float Elec_EgammaOverPdif;
  int Elec_EarlyBrem;//
  int Elec_LateBrem;//
  float Elec_Logsihih;
  float Elec_DeltaEta;
  float Elec_HoHplusE;
  float Elec_Fbrem;
  float Elec_HasGSF;
  float Elec_Chi2GSF;
  float Elec_GSFNumHits;
  float Elec_GSFTrackResol;
  float Elec_GSFTracklnPt;
  float Elec_GSFTrackEta;

  float ElecVeto_Pt;

  inputTree->SetBranchAddress("run", &run);
  inputTree->SetBranchAddress("event", &event);
  inputTree->SetBranchAddress("lumi", &lumi);
  inputTree->SetBranchAddress("NumPV", &NumPV );
  inputTree->SetBranchAddress("NumGsfEle", &NumGsfEle );
  inputTree->SetBranchAddress("NumPFTaus", &NumPFTaus );
  inputTree->SetBranchAddress("NumGenEle", &NumGenEle );
  inputTree->SetBranchAddress("NumGenHad", &NumGenHad );
  inputTree->SetBranchAddress("NumGenJet", &NumGenJet );



  //GsfElectron variables
  inputTree->SetBranchAddress("Elec_GenEleMatch", &Elec_GenEleMatch);
  inputTree->SetBranchAddress("Elec_GenEleFromZMatch", &Elec_GenEleFromZMatch);
  inputTree->SetBranchAddress("Elec_GenEleFromZTauTauMatch", &Elec_GenEleFromZTauTauMatch);
  inputTree->SetBranchAddress("Elec_GenHadMatch", &Elec_GenHadMatch);
  inputTree->SetBranchAddress("Elec_GenJetMatch", &Elec_GenJetMatch);
  inputTree->SetBranchAddress("Elec_AbsEta", &Elec_AbsEta);
  inputTree->SetBranchAddress("Elec_Pt", &Elec_Pt);
  inputTree->SetBranchAddress("Elec_HasSC", &Elec_HasSC);
  inputTree->SetBranchAddress("Elec_PFMvaOutput", &Elec_PFMvaOutput);
  inputTree->SetBranchAddress("Elec_EtotOverPin", &Elec_EtotOverPin);
  inputTree->SetBranchAddress("Elec_EeOverPout", &Elec_EeOverPout);
  inputTree->SetBranchAddress("Elec_EgammaOverPdif", &Elec_EgammaOverPdif);
  inputTree->SetBranchAddress("Elec_EarlyBrem", &Elec_EarlyBrem);
  inputTree->SetBranchAddress("Elec_LateBrem", &Elec_LateBrem);
  inputTree->SetBranchAddress("Elec_Logsihih", &Elec_Logsihih);
  inputTree->SetBranchAddress("Elec_DeltaEta", &Elec_DeltaEta);
  inputTree->SetBranchAddress("Elec_HoHplusE", &Elec_HoHplusE);
  inputTree->SetBranchAddress("Elec_Fbrem", &Elec_Fbrem);
  inputTree->SetBranchAddress("Elec_HasGSF", &Elec_HasGSF);
  inputTree->SetBranchAddress("Elec_Chi2GSF", &Elec_Chi2GSF);
  inputTree->SetBranchAddress("Elec_GSFNumHits", &Elec_GSFNumHits);
  inputTree->SetBranchAddress("Elec_GSFTrackResol", &Elec_GSFTrackResol);
  inputTree->SetBranchAddress("Elec_GSFTracklnPt", &Elec_GSFTracklnPt);
  inputTree->SetBranchAddress("Elec_GSFTrackEta", &Elec_GSFTrackEta);

  //PFTaus variables

  inputTree->SetBranchAddress("Tau_GsfEleMatch", &Tau_GsfEleMatch);
  inputTree->SetBranchAddress("Tau_GenEleMatch", &Tau_GenEleMatch);
  inputTree->SetBranchAddress("Tau_GenEleFromZMatch", &Tau_GenEleFromZMatch);
  inputTree->SetBranchAddress("Tau_GenEleFromZTauTauMatch", &Tau_GenEleFromZTauTauMatch);
  inputTree->SetBranchAddress("Tau_GenHadMatch", &Tau_GenHadMatch);
  inputTree->SetBranchAddress("Tau_GenJetMatch", &Tau_GenJetMatch);
  inputTree->SetBranchAddress("Tau_EtaAtEcalEntrance", &Tau_EtaAtEcalEntrance);
  inputTree->SetBranchAddress("Tau_PhiAtEcalEntrance", &Tau_PhiAtEcalEntrance);
  inputTree->SetBranchAddress("Tau_Pt", &Tau_Pt);
  inputTree->SetBranchAddress("Tau_Eta", &Tau_Eta);
  inputTree->SetBranchAddress("Tau_HasGsf", &Tau_HasGsf); 
  inputTree->SetBranchAddress("Tau_GSFChi2", &Tau_GSFChi2);
  inputTree->SetBranchAddress("Tau_GSFNumHits", &Tau_GSFNumHits);
  inputTree->SetBranchAddress("Tau_GSFTrackResol", &Tau_GSFTrackResol);
  inputTree->SetBranchAddress("Tau_GSFTracklnPt", &Tau_GSFTracklnPt);
  inputTree->SetBranchAddress("Tau_GSFTrackEta", &Tau_GSFTrackEta);
  inputTree->SetBranchAddress("Tau_KFNumHits", &Tau_KFNumHits);
  inputTree->SetBranchAddress("Tau_EmFraction", &Tau_EmFraction); 
  inputTree->SetBranchAddress("Tau_NumChargedCands", &Tau_NumChargedCands);
  inputTree->SetBranchAddress("Tau_NumGammaCands", &Tau_NumGammaCands); 
  inputTree->SetBranchAddress("Tau_HadrHoP", &Tau_HadrHoP); 
  inputTree->SetBranchAddress("Tau_HadrEoP", &Tau_HadrEoP); 
  inputTree->SetBranchAddress("Tau_VisMass", &Tau_VisMass); 
  inputTree->SetBranchAddress("Tau_GammaEtaMom", &Tau_GammaEtaMom);
  inputTree->SetBranchAddress("Tau_GammaPhiMom", &Tau_GammaPhiMom);
  inputTree->SetBranchAddress("Tau_GammaEnFrac", &Tau_GammaEnFrac);
  inputTree->SetBranchAddress("Tau_HadrMva", &Tau_HadrMva);  
  inputTree->SetBranchAddress("Tau_IsoMVALoose", &Tau_IsoMVALoose); 
  inputTree->SetBranchAddress("Tau_AntiELoose", &Tau_AntiELoose); 
  inputTree->SetBranchAddress("Tau_AntiEMedium", &Tau_AntiEMedium); 
  inputTree->SetBranchAddress("Tau_AntiETight", &Tau_AntiETight); 
  inputTree->SetBranchAddress("Tau_AntiEMVA", &Tau_AntiEMVA); 

  inputTree->SetBranchAddress("ElecVeto_Pt",&ElecVeto_Pt);

//   inputTree->SetBranchAddress("Tau_MatchElePassVeto", &Tau_MatchElePassVeto); 

  inputTree->SetBranchStatus("*", 1);

  float Tau_NumHitsVariable = (Tau_GSFNumHits - Tau_KFNumHits)/(Tau_GSFNumHits + Tau_KFNumHits);
  float Tau_dCrackPhi = dCrackPhi(Tau_PhiAtEcalEntrance,Tau_EtaAtEcalEntrance) ;
  float Tau_dCrackEta = dCrackEta(Tau_EtaAtEcalEntrance) ;
  
  //enable root i/o for objects with reflex dictionaries in standalone root mode
  ROOT::Cintex::Cintex::Enable();   

  //read GBRForest from file
  GBRForest *gbr_NoEleMatch_woGwoGSF_BL = (GBRForest *)(fin->Get("gbr_NoEleMatch_woGwoGSF_BL"));
  GBRForest *gbr_NoEleMatch_woGwGSF_BL = (GBRForest *)(fin->Get("gbr_NoEleMatch_woGwGSF_BL"));
  GBRForest *gbr_NoEleMatch_wGwoGSF_BL = (GBRForest *)(fin->Get("gbr_NoEleMatch_wGwoGSF_BL"));
  GBRForest *gbr_NoEleMatch_wGwGSF_BL = (GBRForest *)(fin->Get("gbr_NoEleMatch_wGwGSF_BL"));
  GBRForest *gbr_woGwoGSF_BL = (GBRForest *)(fin->Get("gbr_woGwoGSF_BL"));
  GBRForest *gbr_woGwGSF_BL = (GBRForest *)(fin->Get("gbr_woGwGSF_BL"));
  GBRForest *gbr_wGwoGSF_BL = (GBRForest *)(fin->Get("gbr_wGwoGSF_BL"));
  GBRForest *gbr_wGwGSF_BL = (GBRForest *)(fin->Get("gbr_wGwGSF_BL"));
  GBRForest *gbr_NoEleMatch_woGwoGSF_EC = (GBRForest *)(fin->Get("gbr_NoEleMatch_woGwoGSF_EC"));
  GBRForest *gbr_NoEleMatch_woGwGSF_EC = (GBRForest *)(fin->Get("gbr_NoEleMatch_woGwGSF_EC"));
  GBRForest *gbr_NoEleMatch_wGwoGSF_EC = (GBRForest *)(fin->Get("gbr_NoEleMatch_wGwoGSF_EC"));
  GBRForest *gbr_NoEleMatch_wGwGSF_EC = (GBRForest *)(fin->Get("gbr_NoEleMatch_wGwGSF_EC"));
  GBRForest *gbr_woGwoGSF_EC = (GBRForest *)(fin->Get("gbr_woGwoGSF_EC"));
  GBRForest *gbr_woGwGSF_EC = (GBRForest *)(fin->Get("gbr_woGwGSF_EC"));
  GBRForest *gbr_wGwoGSF_EC = (GBRForest *)(fin->Get("gbr_wGwoGSF_EC"));
  GBRForest *gbr_wGwGSF_EC = (GBRForest *)(fin->Get("gbr_wGwGSF_EC"));
    




  //USING XML FILES

  string Weight_NoEleMatch_woGwoGSF_BL = "../test/Macros/tmva/weights/V13/TMVAClassification_v13EleVeto_NoEleMatch_woGwoGSF_Barrel_BDTG.weights.xml";
  string Weight_NoEleMatch_woGwGSF_BL = "../test/Macros/tmva/weights/V13/TMVAClassification_v13EleVeto_NoEleMatch_woGwGSF_Barrel_BDTG.weights.xml";
  string Weight_NoEleMatch_wGwoGSF_BL = "../test/Macros/tmva/weights/V13/TMVAClassification_v13EleVeto_NoEleMatch_wGwoGSF_Barrel_BDTG.weights.xml";
  string Weight_NoEleMatch_wGwGSF_BL = "../test/Macros/tmva/weights/V13/TMVAClassification_v13EleVeto_NoEleMatch_wGwGSF_Barrel_BDTG.weights.xml";
  string Weight_woGwoGSF_BL = "../test/Macros/tmva/weights/V13/TMVAClassification_v13EleVeto_woGwoGSF_Barrel_BDTG.weights.xml";
  string Weight_woGwGSF_BL = "../test/Macros/tmva/weights/V13/TMVAClassification_v13EleVeto_woGwGSF_Barrel_BDTG.weights.xml";
  string Weight_wGwoGSF_BL = "../test/Macros/tmva/weights/V13/TMVAClassification_v13EleVeto_wGwoGSF_Barrel_BDTG.weights.xml";
  string Weight_wGwGSF_BL = "../test/Macros/tmva/weights/V13/TMVAClassification_v13EleVeto_wGwGSF_Barrel_BDTG.weights.xml";
  string Weight_NoEleMatch_woGwoGSF_EC = "../test/Macros/tmva/weights/V13/TMVAClassification_v13EleVeto_NoEleMatch_woGwoGSF_Endcap_BDTG.weights.xml";
  string Weight_NoEleMatch_woGwGSF_EC = "../test/Macros/tmva/weights/V13/TMVAClassification_v13EleVeto_NoEleMatch_woGwGSF_Endcap_BDTG.weights.xml";
  string Weight_NoEleMatch_wGwoGSF_EC = "../test/Macros/tmva/weights/V13/TMVAClassification_v13EleVeto_NoEleMatch_wGwoGSF_Endcap_BDTG.weights.xml";
  string Weight_NoEleMatch_wGwGSF_EC = "../test/Macros/tmva/weights/V13/TMVAClassification_v13EleVeto_NoEleMatch_wGwGSF_Endcap_BDTG.weights.xml";
  string Weight_woGwoGSF_EC = "../test/Macros/tmva/weights/V13/TMVAClassification_v13EleVeto_woGwoGSF_Endcap_BDTG.weights.xml";
  string Weight_woGwGSF_EC = "../test/Macros/tmva/weights/V13/TMVAClassification_v13EleVeto_woGwGSF_Endcap_BDTG.weights.xml";
  string Weight_wGwoGSF_EC = "../test/Macros/tmva/weights/V13/TMVAClassification_v13EleVeto_wGwoGSF_Endcap_BDTG.weights.xml";
  string Weight_wGwGSF_EC = "../test/Macros/tmva/weights/V13/TMVAClassification_v13EleVeto_wGwGSF_Endcap_BDTG.weights.xml";

  TMVA::Reader *reader_NoEleMatch_woGwoGSF_BL = new TMVA::Reader( "!Color:!Silent:Error" );  
  reader_NoEleMatch_woGwoGSF_BL->AddVariable("Tau_EtaAtEcalEntrance",&Tau_EtaAtEcalEntrance);
  reader_NoEleMatch_woGwoGSF_BL->AddVariable("Tau_Pt",&Tau_Pt);
  reader_NoEleMatch_woGwoGSF_BL->AddVariable("Tau_EmFraction",&Tau_EmFraction);
  reader_NoEleMatch_woGwoGSF_BL->AddVariable("Tau_HadrHoP",&Tau_HadrHoP);
  reader_NoEleMatch_woGwoGSF_BL->AddVariable("Tau_HadrEoP",&Tau_HadrEoP);
  reader_NoEleMatch_woGwoGSF_BL->AddVariable("Tau_VisMass",&Tau_VisMass);
  reader_NoEleMatch_woGwoGSF_BL->AddVariable("Tau_dCrackEta",&Tau_dCrackEta);
  reader_NoEleMatch_woGwoGSF_BL->AddVariable("Tau_dCrackPhi",&Tau_dCrackPhi);
  reader_NoEleMatch_woGwoGSF_BL->SetVerbose(kTRUE);
  reader_NoEleMatch_woGwoGSF_BL->BookMVA("BDTG",Weight_NoEleMatch_woGwoGSF_BL);

  TMVA::Reader *reader_NoEleMatch_woGwGSF_BL = new TMVA::Reader( "!Color:!Silent:Error" );  
  reader_NoEleMatch_woGwGSF_BL->AddVariable("Tau_EtaAtEcalEntrance",&Tau_EtaAtEcalEntrance);
  reader_NoEleMatch_woGwGSF_BL->AddVariable("Tau_Pt",&Tau_Pt);
  reader_NoEleMatch_woGwGSF_BL->AddVariable("Tau_EmFraction",&Tau_EmFraction);
  reader_NoEleMatch_woGwGSF_BL->AddVariable("Tau_HadrHoP",&Tau_HadrHoP);
  reader_NoEleMatch_woGwGSF_BL->AddVariable("Tau_HadrEoP",&Tau_HadrEoP);
  reader_NoEleMatch_woGwGSF_BL->AddVariable("Tau_VisMass",&Tau_VisMass);
  reader_NoEleMatch_woGwGSF_BL->AddVariable("Tau_HadrMva",&Tau_HadrMva);
  reader_NoEleMatch_woGwGSF_BL->AddVariable("Tau_GSFChi2",&Tau_GSFChi2);
  reader_NoEleMatch_woGwGSF_BL->AddVariable("(Tau_GSFNumHits - Tau_KFNumHits)/(Tau_GSFNumHits + Tau_KFNumHits)",&Tau_NumHitsVariable);
  reader_NoEleMatch_woGwGSF_BL->AddVariable("Tau_GSFTrackResol",&Tau_GSFTrackResol);
  reader_NoEleMatch_woGwGSF_BL->AddVariable("Tau_GSFTracklnPt",&Tau_GSFTracklnPt);
  reader_NoEleMatch_woGwGSF_BL->AddVariable("Tau_GSFTrackEta",&Tau_GSFTrackEta);
  reader_NoEleMatch_woGwGSF_BL->AddVariable("Tau_dCrackEta",&Tau_dCrackEta);
  reader_NoEleMatch_woGwGSF_BL->AddVariable("Tau_dCrackPhi",&Tau_dCrackPhi);
  reader_NoEleMatch_woGwGSF_BL->SetVerbose(kTRUE);
  reader_NoEleMatch_woGwGSF_BL->BookMVA("BDTG",Weight_NoEleMatch_woGwGSF_BL);

  TMVA::Reader *reader_NoEleMatch_wGwoGSF_BL = new TMVA::Reader( "!Color:!Silent:Error" );  
  reader_NoEleMatch_wGwoGSF_BL->AddVariable("Tau_EtaAtEcalEntrance",&Tau_EtaAtEcalEntrance);
  reader_NoEleMatch_wGwoGSF_BL->AddVariable("Tau_Pt",&Tau_Pt);
  reader_NoEleMatch_wGwoGSF_BL->AddVariable("Tau_EmFraction",&Tau_EmFraction);
  reader_NoEleMatch_wGwoGSF_BL->AddVariable("Tau_NumGammaCands",&Tau_NumGammaCands);
  reader_NoEleMatch_wGwoGSF_BL->AddVariable("Tau_HadrHoP",&Tau_HadrHoP);
  reader_NoEleMatch_wGwoGSF_BL->AddVariable("Tau_HadrEoP",&Tau_HadrEoP);
  reader_NoEleMatch_wGwoGSF_BL->AddVariable("Tau_VisMass",&Tau_VisMass);
  reader_NoEleMatch_wGwoGSF_BL->AddVariable("Tau_GammaEtaMom",&Tau_GammaEtaMom);
  reader_NoEleMatch_wGwoGSF_BL->AddVariable("Tau_GammaPhiMom",&Tau_GammaPhiMom);
  reader_NoEleMatch_wGwoGSF_BL->AddVariable("Tau_GammaEnFrac",&Tau_GammaEnFrac);
  reader_NoEleMatch_wGwoGSF_BL->AddVariable("Tau_dCrackEta",&Tau_dCrackEta);
  reader_NoEleMatch_wGwoGSF_BL->AddVariable("Tau_dCrackPhi",&Tau_dCrackPhi);
  reader_NoEleMatch_wGwoGSF_BL->SetVerbose(kTRUE);
  reader_NoEleMatch_wGwoGSF_BL->BookMVA("BDTG",Weight_NoEleMatch_wGwoGSF_BL);

  TMVA::Reader *reader_NoEleMatch_wGwGSF_BL = new TMVA::Reader( "!Color:!Silent:Error" );  
  reader_NoEleMatch_wGwGSF_BL->AddVariable("Tau_EtaAtEcalEntrance",&Tau_EtaAtEcalEntrance);
  reader_NoEleMatch_wGwGSF_BL->AddVariable("Tau_Pt",&Tau_Pt);
  reader_NoEleMatch_wGwGSF_BL->AddVariable("Tau_EmFraction",&Tau_EmFraction);
  reader_NoEleMatch_wGwGSF_BL->AddVariable("Tau_NumGammaCands",&Tau_NumGammaCands);
  reader_NoEleMatch_wGwGSF_BL->AddVariable("Tau_HadrHoP",&Tau_HadrHoP);
  reader_NoEleMatch_wGwGSF_BL->AddVariable("Tau_HadrEoP",&Tau_HadrEoP);
  reader_NoEleMatch_wGwGSF_BL->AddVariable("Tau_VisMass",&Tau_VisMass);
  reader_NoEleMatch_wGwGSF_BL->AddVariable("Tau_HadrMva",&Tau_HadrMva);
  reader_NoEleMatch_wGwGSF_BL->AddVariable("Tau_GammaEtaMom",&Tau_GammaEtaMom);
  reader_NoEleMatch_wGwGSF_BL->AddVariable("Tau_GammaPhiMom",&Tau_GammaPhiMom);
  reader_NoEleMatch_wGwGSF_BL->AddVariable("Tau_GammaEnFrac",&Tau_GammaEnFrac);
  reader_NoEleMatch_wGwGSF_BL->AddVariable("Tau_GSFChi2",&Tau_GSFChi2);
  reader_NoEleMatch_wGwGSF_BL->AddVariable("(Tau_GSFNumHits - Tau_KFNumHits)/(Tau_GSFNumHits + Tau_KFNumHits)",&Tau_NumHitsVariable);
  reader_NoEleMatch_wGwGSF_BL->AddVariable("Tau_GSFTrackResol",&Tau_GSFTrackResol);
  reader_NoEleMatch_wGwGSF_BL->AddVariable("Tau_GSFTracklnPt",&Tau_GSFTracklnPt);
  reader_NoEleMatch_wGwGSF_BL->AddVariable("Tau_GSFTrackEta",&Tau_GSFTrackEta);
  reader_NoEleMatch_wGwGSF_BL->AddVariable("Tau_dCrackEta",&Tau_dCrackEta);
  reader_NoEleMatch_wGwGSF_BL->AddVariable("Tau_dCrackPhi",&Tau_dCrackPhi);
  reader_NoEleMatch_wGwGSF_BL->SetVerbose(kTRUE);
  reader_NoEleMatch_wGwGSF_BL->BookMVA("BDTG",Weight_NoEleMatch_wGwGSF_BL);

  TMVA::Reader *reader_woGwoGSF_BL = new TMVA::Reader( "!Color:!Silent:Error" );
  reader_woGwoGSF_BL->AddVariable("Elec_EtotOverPin",&Elec_EtotOverPin);
  reader_woGwoGSF_BL->AddVariable("Elec_EgammaOverPdif",&Elec_EgammaOverPdif);
  reader_woGwoGSF_BL->AddVariable("Elec_Fbrem",&Elec_Fbrem);
  reader_woGwoGSF_BL->AddVariable("Elec_Chi2GSF",&Elec_Chi2GSF);
  reader_woGwoGSF_BL->AddVariable("Elec_GSFNumHits",&Elec_GSFNumHits);
  reader_woGwoGSF_BL->AddVariable("Elec_GSFTrackResol",&Elec_GSFTrackResol);
  reader_woGwoGSF_BL->AddVariable("Elec_GSFTracklnPt",&Elec_GSFTracklnPt);
  reader_woGwoGSF_BL->AddVariable("Elec_GSFTrackEta",&Elec_GSFTrackEta);
  reader_woGwoGSF_BL->AddVariable("Tau_EtaAtEcalEntrance",&Tau_EtaAtEcalEntrance);
  reader_woGwoGSF_BL->AddVariable("Tau_Pt",&Tau_Pt);
  reader_woGwoGSF_BL->AddVariable("Tau_EmFraction",&Tau_EmFraction);
  reader_woGwoGSF_BL->AddVariable("Tau_HadrHoP",&Tau_HadrHoP);
  reader_woGwoGSF_BL->AddVariable("Tau_HadrEoP",&Tau_HadrEoP);
  reader_woGwoGSF_BL->AddVariable("Tau_VisMass",&Tau_VisMass);
  reader_woGwoGSF_BL->AddVariable("Tau_dCrackEta",&Tau_dCrackEta);
  reader_woGwoGSF_BL->AddVariable("Tau_dCrackPhi",&Tau_dCrackPhi);
  reader_woGwoGSF_BL->SetVerbose(kTRUE);
  reader_woGwoGSF_BL->BookMVA("BDTG",Weight_woGwoGSF_BL);

  TMVA::Reader *reader_woGwGSF_BL = new TMVA::Reader( "!Color:!Silent:Error" );  
  reader_woGwGSF_BL->AddVariable("Elec_EtotOverPin",&Elec_EtotOverPin);
  reader_woGwGSF_BL->AddVariable("Elec_EgammaOverPdif",&Elec_EgammaOverPdif);
  reader_woGwGSF_BL->AddVariable("Elec_Fbrem",&Elec_Fbrem);
  reader_woGwGSF_BL->AddVariable("Elec_Chi2GSF",&Elec_Chi2GSF);
  reader_woGwGSF_BL->AddVariable("Elec_GSFNumHits",&Elec_GSFNumHits);
  reader_woGwGSF_BL->AddVariable("Elec_GSFTrackResol",&Elec_GSFTrackResol);
  reader_woGwGSF_BL->AddVariable("Elec_GSFTracklnPt",&Elec_GSFTracklnPt);
  reader_woGwGSF_BL->AddVariable("Elec_GSFTrackEta",&Elec_GSFTrackEta);
  reader_woGwGSF_BL->AddVariable("Tau_EtaAtEcalEntrance",&Tau_EtaAtEcalEntrance);
  reader_woGwGSF_BL->AddVariable("Tau_Pt",&Tau_Pt);
  reader_woGwGSF_BL->AddVariable("Tau_EmFraction",&Tau_EmFraction);
  reader_woGwGSF_BL->AddVariable("Tau_HadrHoP",&Tau_HadrHoP);
  reader_woGwGSF_BL->AddVariable("Tau_HadrEoP",&Tau_HadrEoP);
  reader_woGwGSF_BL->AddVariable("Tau_VisMass",&Tau_VisMass);
  reader_woGwGSF_BL->AddVariable("Tau_HadrMva",&Tau_HadrMva);
  reader_woGwGSF_BL->AddVariable("Tau_GSFChi2",&Tau_GSFChi2);
  reader_woGwGSF_BL->AddVariable("(Tau_GSFNumHits - Tau_KFNumHits)/(Tau_GSFNumHits + Tau_KFNumHits)",&Tau_NumHitsVariable);
  reader_woGwGSF_BL->AddVariable("Tau_GSFTrackResol",&Tau_GSFTrackResol);
  reader_woGwGSF_BL->AddVariable("Tau_GSFTracklnPt",&Tau_GSFTracklnPt);
  reader_woGwGSF_BL->AddVariable("Tau_GSFTrackEta",&Tau_GSFTrackEta);
  reader_woGwGSF_BL->AddVariable("Tau_dCrackEta",&Tau_dCrackEta);
  reader_woGwGSF_BL->AddVariable("Tau_dCrackPhi",&Tau_dCrackPhi);
  reader_woGwGSF_BL->SetVerbose(kTRUE);
  reader_woGwGSF_BL->BookMVA("BDTG",Weight_woGwGSF_BL);

  TMVA::Reader *reader_wGwoGSF_BL = new TMVA::Reader( "!Color:!Silent:Error" );  
  reader_wGwoGSF_BL->AddVariable("Elec_EtotOverPin",&Elec_EtotOverPin);
  reader_wGwoGSF_BL->AddVariable("Elec_EgammaOverPdif",&Elec_EgammaOverPdif);
  reader_wGwoGSF_BL->AddVariable("Elec_Fbrem",&Elec_Fbrem);
  reader_wGwoGSF_BL->AddVariable("Elec_Chi2GSF",&Elec_Chi2GSF);
  reader_wGwoGSF_BL->AddVariable("Elec_GSFNumHits",&Elec_GSFNumHits);
  reader_wGwoGSF_BL->AddVariable("Elec_GSFTrackResol",&Elec_GSFTrackResol);
  reader_wGwoGSF_BL->AddVariable("Elec_GSFTracklnPt",&Elec_GSFTracklnPt);
  reader_wGwoGSF_BL->AddVariable("Elec_GSFTrackEta",&Elec_GSFTrackEta);
  reader_wGwoGSF_BL->AddVariable("Tau_EtaAtEcalEntrance",&Tau_EtaAtEcalEntrance);
  reader_wGwoGSF_BL->AddVariable("Tau_Pt",&Tau_Pt);
  reader_wGwoGSF_BL->AddVariable("Tau_EmFraction",&Tau_EmFraction);
  reader_wGwoGSF_BL->AddVariable("Tau_NumGammaCands",&Tau_NumGammaCands);
  reader_wGwoGSF_BL->AddVariable("Tau_HadrHoP",&Tau_HadrHoP);
  reader_wGwoGSF_BL->AddVariable("Tau_HadrEoP",&Tau_HadrEoP);
  reader_wGwoGSF_BL->AddVariable("Tau_VisMass",&Tau_VisMass);
  reader_wGwoGSF_BL->AddVariable("Tau_GammaEtaMom",&Tau_GammaEtaMom);
  reader_wGwoGSF_BL->AddVariable("Tau_GammaPhiMom",&Tau_GammaPhiMom);
  reader_wGwoGSF_BL->AddVariable("Tau_GammaEnFrac",&Tau_GammaEnFrac);
  reader_wGwoGSF_BL->AddVariable("Tau_dCrackEta",&Tau_dCrackEta);
  reader_wGwoGSF_BL->AddVariable("Tau_dCrackPhi",&Tau_dCrackPhi);
  reader_wGwoGSF_BL->SetVerbose(kTRUE);
  reader_wGwoGSF_BL->BookMVA("BDTG",Weight_wGwoGSF_BL);

  TMVA::Reader *reader_wGwGSF_BL = new TMVA::Reader( "!Color:!Silent:Error" );  
  reader_wGwGSF_BL->AddVariable("Elec_EtotOverPin",&Elec_EtotOverPin);
  reader_wGwGSF_BL->AddVariable("Elec_EgammaOverPdif",&Elec_EgammaOverPdif);
  reader_wGwGSF_BL->AddVariable("Elec_Fbrem",&Elec_Fbrem);
  reader_wGwGSF_BL->AddVariable("Elec_Chi2GSF",&Elec_Chi2GSF);
  reader_wGwGSF_BL->AddVariable("Elec_GSFNumHits",&Elec_GSFNumHits);
  reader_wGwGSF_BL->AddVariable("Elec_GSFTrackResol",&Elec_GSFTrackResol);
  reader_wGwGSF_BL->AddVariable("Elec_GSFTracklnPt",&Elec_GSFTracklnPt);
  reader_wGwGSF_BL->AddVariable("Elec_GSFTrackEta",&Elec_GSFTrackEta);
  reader_wGwGSF_BL->AddVariable("Tau_EtaAtEcalEntrance",&Tau_EtaAtEcalEntrance);
  reader_wGwGSF_BL->AddVariable("Tau_Pt",&Tau_Pt);
  reader_wGwGSF_BL->AddVariable("Tau_EmFraction",&Tau_EmFraction);
  reader_wGwGSF_BL->AddVariable("Tau_NumGammaCands",&Tau_NumGammaCands);
  reader_wGwGSF_BL->AddVariable("Tau_HadrHoP",&Tau_HadrHoP);
  reader_wGwGSF_BL->AddVariable("Tau_HadrEoP",&Tau_HadrEoP);
  reader_wGwGSF_BL->AddVariable("Tau_VisMass",&Tau_VisMass);
  reader_wGwGSF_BL->AddVariable("Tau_HadrMva",&Tau_HadrMva);
  reader_wGwGSF_BL->AddVariable("Tau_GammaEtaMom",&Tau_GammaEtaMom);
  reader_wGwGSF_BL->AddVariable("Tau_GammaPhiMom",&Tau_GammaPhiMom);
  reader_wGwGSF_BL->AddVariable("Tau_GammaEnFrac",&Tau_GammaEnFrac);
  reader_wGwGSF_BL->AddVariable("Tau_GSFChi2",&Tau_GSFChi2);
  reader_wGwGSF_BL->AddVariable("(Tau_GSFNumHits - Tau_KFNumHits)/(Tau_GSFNumHits + Tau_KFNumHits)",&Tau_NumHitsVariable);
  reader_wGwGSF_BL->AddVariable("Tau_GSFTrackResol",&Tau_GSFTrackResol);
  reader_wGwGSF_BL->AddVariable("Tau_GSFTracklnPt",&Tau_GSFTracklnPt);
  reader_wGwGSF_BL->AddVariable("Tau_GSFTrackEta",&Tau_GSFTrackEta);
  reader_wGwGSF_BL->AddVariable("Tau_dCrackEta",&Tau_dCrackEta);
  reader_wGwGSF_BL->AddVariable("Tau_dCrackPhi",&Tau_dCrackPhi);
  reader_wGwGSF_BL->SetVerbose(kTRUE);
  reader_wGwGSF_BL->BookMVA("BDTG",Weight_wGwGSF_BL);

  ////////////////////////

  TMVA::Reader *reader_NoEleMatch_woGwoGSF_EC = new TMVA::Reader( "!Color:!Silent:Error" );  
  reader_NoEleMatch_woGwoGSF_EC->AddVariable("Tau_EtaAtEcalEntrance",&Tau_EtaAtEcalEntrance);
  reader_NoEleMatch_woGwoGSF_EC->AddVariable("Tau_Pt",&Tau_Pt);
  reader_NoEleMatch_woGwoGSF_EC->AddVariable("Tau_EmFraction",&Tau_EmFraction);
  reader_NoEleMatch_woGwoGSF_EC->AddVariable("Tau_HadrHoP",&Tau_HadrHoP);
  reader_NoEleMatch_woGwoGSF_EC->AddVariable("Tau_HadrEoP",&Tau_HadrEoP);
  reader_NoEleMatch_woGwoGSF_EC->AddVariable("Tau_VisMass",&Tau_VisMass);
  reader_NoEleMatch_woGwoGSF_EC->AddVariable("Tau_dCrackEta",&Tau_dCrackEta);
  reader_NoEleMatch_woGwoGSF_EC->SetVerbose(kTRUE);
  reader_NoEleMatch_woGwoGSF_EC->BookMVA("BDTG",Weight_NoEleMatch_woGwoGSF_EC);

  TMVA::Reader *reader_NoEleMatch_woGwGSF_EC = new TMVA::Reader( "!Color:!Silent:Error" );  
  reader_NoEleMatch_woGwGSF_EC->AddVariable("Tau_EtaAtEcalEntrance",&Tau_EtaAtEcalEntrance);
  reader_NoEleMatch_woGwGSF_EC->AddVariable("Tau_Pt",&Tau_Pt);
  reader_NoEleMatch_woGwGSF_EC->AddVariable("Tau_EmFraction",&Tau_EmFraction);
  reader_NoEleMatch_woGwGSF_EC->AddVariable("Tau_HadrHoP",&Tau_HadrHoP);
  reader_NoEleMatch_woGwGSF_EC->AddVariable("Tau_HadrEoP",&Tau_HadrEoP);
  reader_NoEleMatch_woGwGSF_EC->AddVariable("Tau_VisMass",&Tau_VisMass);
  reader_NoEleMatch_woGwGSF_EC->AddVariable("Tau_HadrMva",&Tau_HadrMva);
  reader_NoEleMatch_woGwGSF_EC->AddVariable("Tau_GSFChi2",&Tau_GSFChi2);
  reader_NoEleMatch_woGwGSF_EC->AddVariable("(Tau_GSFNumHits - Tau_KFNumHits)/(Tau_GSFNumHits + Tau_KFNumHits)",&Tau_NumHitsVariable);
  reader_NoEleMatch_woGwGSF_EC->AddVariable("Tau_GSFTrackResol",&Tau_GSFTrackResol);
  reader_NoEleMatch_woGwGSF_EC->AddVariable("Tau_GSFTracklnPt",&Tau_GSFTracklnPt);
  reader_NoEleMatch_woGwGSF_EC->AddVariable("Tau_GSFTrackEta",&Tau_GSFTrackEta);
  reader_NoEleMatch_woGwGSF_EC->AddVariable("Tau_dCrackEta",&Tau_dCrackEta);
  reader_NoEleMatch_woGwGSF_EC->SetVerbose(kTRUE);
  reader_NoEleMatch_woGwGSF_EC->BookMVA("BDTG",Weight_NoEleMatch_woGwGSF_EC);

  TMVA::Reader *reader_NoEleMatch_wGwoGSF_EC = new TMVA::Reader( "!Color:!Silent:Error" );  
  reader_NoEleMatch_wGwoGSF_EC->AddVariable("Tau_EtaAtEcalEntrance",&Tau_EtaAtEcalEntrance);
  reader_NoEleMatch_wGwoGSF_EC->AddVariable("Tau_Pt",&Tau_Pt);
  reader_NoEleMatch_wGwoGSF_EC->AddVariable("Tau_EmFraction",&Tau_EmFraction);
  reader_NoEleMatch_wGwoGSF_EC->AddVariable("Tau_NumGammaCands",&Tau_NumGammaCands);
  reader_NoEleMatch_wGwoGSF_EC->AddVariable("Tau_HadrHoP",&Tau_HadrHoP);
  reader_NoEleMatch_wGwoGSF_EC->AddVariable("Tau_HadrEoP",&Tau_HadrEoP);
  reader_NoEleMatch_wGwoGSF_EC->AddVariable("Tau_VisMass",&Tau_VisMass);
  reader_NoEleMatch_wGwoGSF_EC->AddVariable("Tau_GammaEtaMom",&Tau_GammaEtaMom);
  reader_NoEleMatch_wGwoGSF_EC->AddVariable("Tau_GammaPhiMom",&Tau_GammaPhiMom);
  reader_NoEleMatch_wGwoGSF_EC->AddVariable("Tau_GammaEnFrac",&Tau_GammaEnFrac);
  reader_NoEleMatch_wGwoGSF_EC->AddVariable("Tau_dCrackEta",&Tau_dCrackEta);
  reader_NoEleMatch_wGwoGSF_EC->SetVerbose(kTRUE);
  reader_NoEleMatch_wGwoGSF_EC->BookMVA("BDTG",Weight_NoEleMatch_wGwoGSF_EC);

  TMVA::Reader *reader_NoEleMatch_wGwGSF_EC = new TMVA::Reader( "!Color:!Silent:Error" );  
  reader_NoEleMatch_wGwGSF_EC->AddVariable("Tau_EtaAtEcalEntrance",&Tau_EtaAtEcalEntrance);
  reader_NoEleMatch_wGwGSF_EC->AddVariable("Tau_Pt",&Tau_Pt);
  reader_NoEleMatch_wGwGSF_EC->AddVariable("Tau_EmFraction",&Tau_EmFraction);
  reader_NoEleMatch_wGwGSF_EC->AddVariable("Tau_NumGammaCands",&Tau_NumGammaCands);
  reader_NoEleMatch_wGwGSF_EC->AddVariable("Tau_HadrHoP",&Tau_HadrHoP);
  reader_NoEleMatch_wGwGSF_EC->AddVariable("Tau_HadrEoP",&Tau_HadrEoP);
  reader_NoEleMatch_wGwGSF_EC->AddVariable("Tau_VisMass",&Tau_VisMass);
  reader_NoEleMatch_wGwGSF_EC->AddVariable("Tau_HadrMva",&Tau_HadrMva);
  reader_NoEleMatch_wGwGSF_EC->AddVariable("Tau_GammaEtaMom",&Tau_GammaEtaMom);
  reader_NoEleMatch_wGwGSF_EC->AddVariable("Tau_GammaPhiMom",&Tau_GammaPhiMom);
  reader_NoEleMatch_wGwGSF_EC->AddVariable("Tau_GammaEnFrac",&Tau_GammaEnFrac);
  reader_NoEleMatch_wGwGSF_EC->AddVariable("Tau_GSFChi2",&Tau_GSFChi2);
  reader_NoEleMatch_wGwGSF_EC->AddVariable("(Tau_GSFNumHits - Tau_KFNumHits)/(Tau_GSFNumHits + Tau_KFNumHits)",&Tau_NumHitsVariable);
  reader_NoEleMatch_wGwGSF_EC->AddVariable("Tau_GSFTrackResol",&Tau_GSFTrackResol);
  reader_NoEleMatch_wGwGSF_EC->AddVariable("Tau_GSFTracklnPt",&Tau_GSFTracklnPt);
  reader_NoEleMatch_wGwGSF_EC->AddVariable("Tau_GSFTrackEta",&Tau_GSFTrackEta);
  reader_NoEleMatch_wGwGSF_EC->AddVariable("Tau_dCrackEta",&Tau_dCrackEta);
  reader_NoEleMatch_wGwGSF_EC->SetVerbose(kTRUE);
  reader_NoEleMatch_wGwGSF_EC->BookMVA("BDTG",Weight_NoEleMatch_wGwGSF_EC);

  TMVA::Reader *reader_woGwoGSF_EC = new TMVA::Reader( "!Color:!Silent:Error" );
  reader_woGwoGSF_EC->AddVariable("Elec_EtotOverPin",&Elec_EtotOverPin);
  reader_woGwoGSF_EC->AddVariable("Elec_EgammaOverPdif",&Elec_EgammaOverPdif);
  reader_woGwoGSF_EC->AddVariable("Elec_Fbrem",&Elec_Fbrem);
  reader_woGwoGSF_EC->AddVariable("Elec_Chi2GSF",&Elec_Chi2GSF);
  reader_woGwoGSF_EC->AddVariable("Elec_GSFNumHits",&Elec_GSFNumHits);
  reader_woGwoGSF_EC->AddVariable("Elec_GSFTrackResol",&Elec_GSFTrackResol);
  reader_woGwoGSF_EC->AddVariable("Elec_GSFTracklnPt",&Elec_GSFTracklnPt);
  reader_woGwoGSF_EC->AddVariable("Elec_GSFTrackEta",&Elec_GSFTrackEta);
  reader_woGwoGSF_EC->AddVariable("Tau_EtaAtEcalEntrance",&Tau_EtaAtEcalEntrance);
  reader_woGwoGSF_EC->AddVariable("Tau_Pt",&Tau_Pt);
  reader_woGwoGSF_EC->AddVariable("Tau_EmFraction",&Tau_EmFraction);
  reader_woGwoGSF_EC->AddVariable("Tau_HadrHoP",&Tau_HadrHoP);
  reader_woGwoGSF_EC->AddVariable("Tau_HadrEoP",&Tau_HadrEoP);
  reader_woGwoGSF_EC->AddVariable("Tau_VisMass",&Tau_VisMass);
  reader_woGwoGSF_EC->AddVariable("Tau_dCrackEta",&Tau_dCrackEta);
  reader_woGwoGSF_EC->SetVerbose(kTRUE);
  reader_woGwoGSF_EC->BookMVA("BDTG",Weight_woGwoGSF_EC);

  TMVA::Reader *reader_woGwGSF_EC = new TMVA::Reader( "!Color:!Silent:Error" );  
  reader_woGwGSF_EC->AddVariable("Elec_EtotOverPin",&Elec_EtotOverPin);
  reader_woGwGSF_EC->AddVariable("Elec_EgammaOverPdif",&Elec_EgammaOverPdif);
  reader_woGwGSF_EC->AddVariable("Elec_Fbrem",&Elec_Fbrem);
  reader_woGwGSF_EC->AddVariable("Elec_Chi2GSF",&Elec_Chi2GSF);
  reader_woGwGSF_EC->AddVariable("Elec_GSFNumHits",&Elec_GSFNumHits);
  reader_woGwGSF_EC->AddVariable("Elec_GSFTrackResol",&Elec_GSFTrackResol);
  reader_woGwGSF_EC->AddVariable("Elec_GSFTracklnPt",&Elec_GSFTracklnPt);
  reader_woGwGSF_EC->AddVariable("Elec_GSFTrackEta",&Elec_GSFTrackEta);
  reader_woGwGSF_EC->AddVariable("Tau_EtaAtEcalEntrance",&Tau_EtaAtEcalEntrance);
  reader_woGwGSF_EC->AddVariable("Tau_Pt",&Tau_Pt);
  reader_woGwGSF_EC->AddVariable("Tau_EmFraction",&Tau_EmFraction);
  reader_woGwGSF_EC->AddVariable("Tau_HadrHoP",&Tau_HadrHoP);
  reader_woGwGSF_EC->AddVariable("Tau_HadrEoP",&Tau_HadrEoP);
  reader_woGwGSF_EC->AddVariable("Tau_VisMass",&Tau_VisMass);
  reader_woGwGSF_EC->AddVariable("Tau_HadrMva",&Tau_HadrMva);
  reader_woGwGSF_EC->AddVariable("Tau_GSFChi2",&Tau_GSFChi2);
  reader_woGwGSF_EC->AddVariable("(Tau_GSFNumHits - Tau_KFNumHits)/(Tau_GSFNumHits + Tau_KFNumHits)",&Tau_NumHitsVariable);
  reader_woGwGSF_EC->AddVariable("Tau_GSFTrackResol",&Tau_GSFTrackResol);
  reader_woGwGSF_EC->AddVariable("Tau_GSFTracklnPt",&Tau_GSFTracklnPt);
  reader_woGwGSF_EC->AddVariable("Tau_GSFTrackEta",&Tau_GSFTrackEta);
  reader_woGwGSF_EC->AddVariable("Tau_dCrackEta",&Tau_dCrackEta);
  reader_woGwGSF_EC->SetVerbose(kTRUE);
  reader_woGwGSF_EC->BookMVA("BDTG",Weight_woGwGSF_EC);

  TMVA::Reader *reader_wGwoGSF_EC = new TMVA::Reader( "!Color:!Silent:Error" );  
  reader_wGwoGSF_EC->AddVariable("Elec_EtotOverPin",&Elec_EtotOverPin);
  reader_wGwoGSF_EC->AddVariable("Elec_EgammaOverPdif",&Elec_EgammaOverPdif);
  reader_wGwoGSF_EC->AddVariable("Elec_Fbrem",&Elec_Fbrem);
  reader_wGwoGSF_EC->AddVariable("Elec_Chi2GSF",&Elec_Chi2GSF);
  reader_wGwoGSF_EC->AddVariable("Elec_GSFNumHits",&Elec_GSFNumHits);
  reader_wGwoGSF_EC->AddVariable("Elec_GSFTrackResol",&Elec_GSFTrackResol);
  reader_wGwoGSF_EC->AddVariable("Elec_GSFTracklnPt",&Elec_GSFTracklnPt);
  reader_wGwoGSF_EC->AddVariable("Elec_GSFTrackEta",&Elec_GSFTrackEta);
  reader_wGwoGSF_EC->AddVariable("Tau_EtaAtEcalEntrance",&Tau_EtaAtEcalEntrance);
  reader_wGwoGSF_EC->AddVariable("Tau_Pt",&Tau_Pt);
  reader_wGwoGSF_EC->AddVariable("Tau_EmFraction",&Tau_EmFraction);
  reader_wGwoGSF_EC->AddVariable("Tau_NumGammaCands",&Tau_NumGammaCands);
  reader_wGwoGSF_EC->AddVariable("Tau_HadrHoP",&Tau_HadrHoP);
  reader_wGwoGSF_EC->AddVariable("Tau_HadrEoP",&Tau_HadrEoP);
  reader_wGwoGSF_EC->AddVariable("Tau_VisMass",&Tau_VisMass);
  reader_wGwoGSF_EC->AddVariable("Tau_GammaEtaMom",&Tau_GammaEtaMom);
  reader_wGwoGSF_EC->AddVariable("Tau_GammaPhiMom",&Tau_GammaPhiMom);
  reader_wGwoGSF_EC->AddVariable("Tau_GammaEnFrac",&Tau_GammaEnFrac);
  reader_wGwoGSF_EC->AddVariable("Tau_dCrackEta",&Tau_dCrackEta);
  reader_wGwoGSF_EC->SetVerbose(kTRUE);
  reader_wGwoGSF_EC->BookMVA("BDTG",Weight_wGwoGSF_EC);

  TMVA::Reader *reader_wGwGSF_EC = new TMVA::Reader( "!Color:!Silent:Error" );  
  reader_wGwGSF_EC->AddVariable("Elec_EtotOverPin",&Elec_EtotOverPin);
  reader_wGwGSF_EC->AddVariable("Elec_EgammaOverPdif",&Elec_EgammaOverPdif);
  reader_wGwGSF_EC->AddVariable("Elec_Fbrem",&Elec_Fbrem);
  reader_wGwGSF_EC->AddVariable("Elec_Chi2GSF",&Elec_Chi2GSF);
  reader_wGwGSF_EC->AddVariable("Elec_GSFNumHits",&Elec_GSFNumHits);
  reader_wGwGSF_EC->AddVariable("Elec_GSFTrackResol",&Elec_GSFTrackResol);
  reader_wGwGSF_EC->AddVariable("Elec_GSFTracklnPt",&Elec_GSFTracklnPt);
  reader_wGwGSF_EC->AddVariable("Elec_GSFTrackEta",&Elec_GSFTrackEta);
  reader_wGwGSF_EC->AddVariable("Tau_EtaAtEcalEntrance",&Tau_EtaAtEcalEntrance);
  reader_wGwGSF_EC->AddVariable("Tau_Pt",&Tau_Pt);
  reader_wGwGSF_EC->AddVariable("Tau_EmFraction",&Tau_EmFraction);
  reader_wGwGSF_EC->AddVariable("Tau_NumGammaCands",&Tau_NumGammaCands);
  reader_wGwGSF_EC->AddVariable("Tau_HadrHoP",&Tau_HadrHoP);
  reader_wGwGSF_EC->AddVariable("Tau_HadrEoP",&Tau_HadrEoP);
  reader_wGwGSF_EC->AddVariable("Tau_VisMass",&Tau_VisMass);
  reader_wGwGSF_EC->AddVariable("Tau_HadrMva",&Tau_HadrMva);
  reader_wGwGSF_EC->AddVariable("Tau_GammaEtaMom",&Tau_GammaEtaMom);
  reader_wGwGSF_EC->AddVariable("Tau_GammaPhiMom",&Tau_GammaPhiMom);
  reader_wGwGSF_EC->AddVariable("Tau_GammaEnFrac",&Tau_GammaEnFrac);
  reader_wGwGSF_EC->AddVariable("Tau_GSFChi2",&Tau_GSFChi2);
  reader_wGwGSF_EC->AddVariable("(Tau_GSFNumHits - Tau_KFNumHits)/(Tau_GSFNumHits + Tau_KFNumHits)",&Tau_NumHitsVariable);
  reader_wGwGSF_EC->AddVariable("Tau_GSFTrackResol",&Tau_GSFTrackResol);
  reader_wGwGSF_EC->AddVariable("Tau_GSFTracklnPt",&Tau_GSFTracklnPt);
  reader_wGwGSF_EC->AddVariable("Tau_GSFTrackEta",&Tau_GSFTrackEta);
  reader_wGwGSF_EC->AddVariable("Tau_dCrackEta",&Tau_dCrackEta);
  reader_wGwGSF_EC->SetVerbose(kTRUE);
  reader_wGwGSF_EC->BookMVA("BDTG",Weight_wGwGSF_EC);

  TH1F* hOver = new TH1F("hOver","",16,0,16);
  TH1F* hBelow = new TH1F("hBelow","",16,0,16);

  cout<< "Number of entries : "<<nEntries<<endl;

  for (int iEntry = 0; iEntry<nEntries ; iEntry++){
    if(iEntry%100000==0) cout << iEntry << endl;
    inputTree->GetEntry(iEntry);

    //if(lumi!=1450)continue;
    //if(event>=579598 || event<=579212 )continue;
    if(Tau_IsoMVALoose<0.5)continue;

    t_NoEleMatch_woGwoGSF_Barrel = 1;
    t_NoEleMatch_woGwGSF_Barrel = 1;
    t_NoEleMatch_wGwoGSF_Barrel = 1;
    t_NoEleMatch_wGwGSF_Barrel = 1;
    t_woGwoGSF_Barrel = 1;
    t_woGwGSF_Barrel = 1;
    t_wGwoGSF_Barrel = 1;
    t_wGwGSF_Barrel = 1;
    t_NoEleMatch_woGwoGSF_Endcap = 1;
    t_NoEleMatch_woGwGSF_Endcap = 1;
    t_NoEleMatch_wGwoGSF_Endcap = 1;
    t_NoEleMatch_wGwGSF_Endcap = 1;
    t_woGwoGSF_Endcap = 1;
    t_woGwGSF_Endcap = 1;
    t_wGwoGSF_Endcap = 1;
    t_wGwGSF_Endcap = 1;

    t_NoEleMatch_woGwoGSF_BarrelXML = 1;
    t_NoEleMatch_woGwGSF_BarrelXML = 1;
    t_NoEleMatch_wGwoGSF_BarrelXML = 1;
    t_NoEleMatch_wGwGSF_BarrelXML = 1;
    t_woGwoGSF_BarrelXML = 1;
    t_woGwGSF_BarrelXML = 1;
    t_wGwoGSF_BarrelXML = 1;
    t_wGwGSF_BarrelXML = 1;
    t_NoEleMatch_woGwoGSF_EndcapXML = 1;
    t_NoEleMatch_woGwGSF_EndcapXML = 1;
    t_NoEleMatch_wGwoGSF_EndcapXML = 1;
    t_NoEleMatch_wGwGSF_EndcapXML = 1;
    t_woGwoGSF_EndcapXML = 1;
    t_woGwGSF_EndcapXML = 1;
    t_wGwoGSF_EndcapXML = 1;
    t_wGwGSF_EndcapXML = 1;

    t_Category = -99;
    t_rawMva = -99;

    if (Type.find("Signal")!=std::string::npos && Tau_GenHadMatch!=1)continue;
    if (Type.find("Backgrd")!=std::string::npos && Tau_GenEleMatch!=1)continue;

    Float_t *Var_NoEleMatch_woGwoGSF_Barrel = new Float_t[8];
    Var_NoEleMatch_woGwoGSF_Barrel[0] = Tau_EtaAtEcalEntrance;
    Var_NoEleMatch_woGwoGSF_Barrel[1] = Tau_Pt;
    Var_NoEleMatch_woGwoGSF_Barrel[2] = Tau_EmFraction;
    Var_NoEleMatch_woGwoGSF_Barrel[3] = Tau_HadrHoP;
    Var_NoEleMatch_woGwoGSF_Barrel[4] = Tau_HadrEoP;
    Var_NoEleMatch_woGwoGSF_Barrel[5] = Tau_VisMass;
    Var_NoEleMatch_woGwoGSF_Barrel[6] = Tau_dCrackEta;
    Var_NoEleMatch_woGwoGSF_Barrel[7] = Tau_dCrackPhi;

    Float_t *Var_NoEleMatch_woGwGSF_Barrel = new Float_t[14];
    Var_NoEleMatch_woGwGSF_Barrel[0] = Tau_EtaAtEcalEntrance;
    Var_NoEleMatch_woGwGSF_Barrel[1] = Tau_Pt;
    Var_NoEleMatch_woGwGSF_Barrel[2] = Tau_EmFraction;
    Var_NoEleMatch_woGwGSF_Barrel[3] = Tau_HadrHoP;
    Var_NoEleMatch_woGwGSF_Barrel[4] = Tau_HadrEoP;
    Var_NoEleMatch_woGwGSF_Barrel[5] = Tau_VisMass;
    Var_NoEleMatch_woGwGSF_Barrel[6] = Tau_HadrMva;
    Var_NoEleMatch_woGwGSF_Barrel[7] = Tau_GSFChi2;
    Var_NoEleMatch_woGwGSF_Barrel[8] = Tau_NumHitsVariable;
    Var_NoEleMatch_woGwGSF_Barrel[9] = Tau_GSFTrackResol;
    Var_NoEleMatch_woGwGSF_Barrel[10] = Tau_GSFTracklnPt;
    Var_NoEleMatch_woGwGSF_Barrel[11] = Tau_GSFTrackEta;
    Var_NoEleMatch_woGwGSF_Barrel[12] = Tau_dCrackEta;
    Var_NoEleMatch_woGwGSF_Barrel[13] = Tau_dCrackPhi;
		
    Float_t *Var_NoEleMatch_wGwoGSF_Barrel = new Float_t[12];
    Var_NoEleMatch_wGwoGSF_Barrel[0] = Tau_EtaAtEcalEntrance;
    Var_NoEleMatch_wGwoGSF_Barrel[1] = Tau_Pt;
    Var_NoEleMatch_wGwoGSF_Barrel[2] = Tau_EmFraction;
    Var_NoEleMatch_wGwoGSF_Barrel[3] = Tau_NumGammaCands;
    Var_NoEleMatch_wGwoGSF_Barrel[4] = Tau_HadrHoP;
    Var_NoEleMatch_wGwoGSF_Barrel[5] = Tau_HadrEoP;
    Var_NoEleMatch_wGwoGSF_Barrel[6] = Tau_VisMass;
    Var_NoEleMatch_wGwoGSF_Barrel[7] = Tau_GammaEtaMom;
    Var_NoEleMatch_wGwoGSF_Barrel[8] = Tau_GammaPhiMom;
    Var_NoEleMatch_wGwoGSF_Barrel[9] = Tau_GammaEnFrac;
    Var_NoEleMatch_wGwoGSF_Barrel[10] = Tau_dCrackEta;
    Var_NoEleMatch_wGwoGSF_Barrel[11] = Tau_dCrackPhi;
		
    Float_t *Var_NoEleMatch_wGwGSF_Barrel = new Float_t[18];
    Var_NoEleMatch_wGwGSF_Barrel[0] = Tau_EtaAtEcalEntrance;
    Var_NoEleMatch_wGwGSF_Barrel[1] = Tau_Pt;
    Var_NoEleMatch_wGwGSF_Barrel[2] = Tau_EmFraction;
    Var_NoEleMatch_wGwGSF_Barrel[3] = Tau_NumGammaCands;
    Var_NoEleMatch_wGwGSF_Barrel[4] = Tau_HadrHoP;
    Var_NoEleMatch_wGwGSF_Barrel[5] = Tau_HadrEoP;
    Var_NoEleMatch_wGwGSF_Barrel[6] = Tau_VisMass;
    Var_NoEleMatch_wGwGSF_Barrel[7] = Tau_HadrMva;
    Var_NoEleMatch_wGwGSF_Barrel[8] = Tau_GammaEtaMom;
    Var_NoEleMatch_wGwGSF_Barrel[9] = Tau_GammaPhiMom;
    Var_NoEleMatch_wGwGSF_Barrel[10] = Tau_GammaEnFrac;
    Var_NoEleMatch_wGwGSF_Barrel[11] = Tau_GSFChi2;
    Var_NoEleMatch_wGwGSF_Barrel[12] = Tau_NumHitsVariable;
    Var_NoEleMatch_wGwGSF_Barrel[13] = Tau_GSFTrackResol;
    Var_NoEleMatch_wGwGSF_Barrel[14] = Tau_GSFTracklnPt;
    Var_NoEleMatch_wGwGSF_Barrel[15] = Tau_GSFTrackEta;
    Var_NoEleMatch_wGwGSF_Barrel[16] = Tau_dCrackEta;
    Var_NoEleMatch_wGwGSF_Barrel[17] = Tau_dCrackPhi;
	
    Float_t *Var_woGwoGSF_Barrel = new Float_t[16];
    Var_woGwoGSF_Barrel[0] = Elec_EtotOverPin;
    Var_woGwoGSF_Barrel[1] = Elec_EgammaOverPdif;
    Var_woGwoGSF_Barrel[2] = Elec_Fbrem;
    Var_woGwoGSF_Barrel[3] = Elec_Chi2GSF;
    Var_woGwoGSF_Barrel[4] = Elec_GSFNumHits;
    Var_woGwoGSF_Barrel[5] = Elec_GSFTrackResol;
    Var_woGwoGSF_Barrel[6] = Elec_GSFTracklnPt;
    Var_woGwoGSF_Barrel[7] = Elec_GSFTrackEta;
    Var_woGwoGSF_Barrel[8] = Tau_EtaAtEcalEntrance;
    Var_woGwoGSF_Barrel[9] = Tau_Pt;
    Var_woGwoGSF_Barrel[10] = Tau_EmFraction;
    Var_woGwoGSF_Barrel[11] = Tau_HadrHoP;
    Var_woGwoGSF_Barrel[12] = Tau_HadrEoP;
    Var_woGwoGSF_Barrel[13] = Tau_VisMass;
    Var_woGwoGSF_Barrel[14] = Tau_dCrackEta;
    Var_woGwoGSF_Barrel[15] = Tau_dCrackPhi;

    Float_t *Var_woGwGSF_Barrel = new Float_t[22];
    Var_woGwGSF_Barrel[0] = Elec_EtotOverPin;
    Var_woGwGSF_Barrel[1] = Elec_EgammaOverPdif;
    Var_woGwGSF_Barrel[2] = Elec_Fbrem;
    Var_woGwGSF_Barrel[3] = Elec_Chi2GSF;
    Var_woGwGSF_Barrel[4] = Elec_GSFNumHits;
    Var_woGwGSF_Barrel[5] = Elec_GSFTrackResol;
    Var_woGwGSF_Barrel[6] = Elec_GSFTracklnPt;
    Var_woGwGSF_Barrel[7] = Elec_GSFTrackEta;
    Var_woGwGSF_Barrel[8] = Tau_EtaAtEcalEntrance;
    Var_woGwGSF_Barrel[9] = Tau_Pt;
    Var_woGwGSF_Barrel[10] = Tau_EmFraction;
    Var_woGwGSF_Barrel[11] = Tau_HadrHoP;
    Var_woGwGSF_Barrel[12] = Tau_HadrEoP;
    Var_woGwGSF_Barrel[13] = Tau_VisMass;
    Var_woGwGSF_Barrel[14] = Tau_HadrMva;
    Var_woGwGSF_Barrel[15] = Tau_GSFChi2;
    Var_woGwGSF_Barrel[16] = Tau_NumHitsVariable;
    Var_woGwGSF_Barrel[17] = Tau_GSFTrackResol;
    Var_woGwGSF_Barrel[18] = Tau_GSFTracklnPt;
    Var_woGwGSF_Barrel[19] = Tau_GSFTrackEta;
    Var_woGwGSF_Barrel[20] = Tau_dCrackEta;
    Var_woGwGSF_Barrel[21] = Tau_dCrackPhi;
		
    Float_t *Var_wGwoGSF_Barrel = new Float_t[20];
    Var_wGwoGSF_Barrel[0] = Elec_EtotOverPin;
    Var_wGwoGSF_Barrel[1] = Elec_EgammaOverPdif;
    Var_wGwoGSF_Barrel[2] = Elec_Fbrem;
    Var_wGwoGSF_Barrel[3] = Elec_Chi2GSF;
    Var_wGwoGSF_Barrel[4] = Elec_GSFNumHits;
    Var_wGwoGSF_Barrel[5] = Elec_GSFTrackResol;
    Var_wGwoGSF_Barrel[6] = Elec_GSFTracklnPt;
    Var_wGwoGSF_Barrel[7] = Elec_GSFTrackEta;
    Var_wGwoGSF_Barrel[8] = Tau_EtaAtEcalEntrance;
    Var_wGwoGSF_Barrel[9] = Tau_Pt;
    Var_wGwoGSF_Barrel[10] = Tau_EmFraction;
    Var_wGwoGSF_Barrel[11] = Tau_NumGammaCands;
    Var_wGwoGSF_Barrel[12] = Tau_HadrHoP;
    Var_wGwoGSF_Barrel[13] = Tau_HadrEoP;
    Var_wGwoGSF_Barrel[14] = Tau_VisMass;
    Var_wGwoGSF_Barrel[15] = Tau_GammaEtaMom;
    Var_wGwoGSF_Barrel[16] = Tau_GammaPhiMom;
    Var_wGwoGSF_Barrel[17] = Tau_GammaEnFrac;
    Var_wGwoGSF_Barrel[18] = Tau_dCrackEta;
    Var_wGwoGSF_Barrel[19] = Tau_dCrackPhi;
		
    Float_t *Var_wGwGSF_Barrel = new Float_t[26];
    Var_wGwGSF_Barrel[0] = Elec_EtotOverPin;
    Var_wGwGSF_Barrel[1] = Elec_EgammaOverPdif;
    Var_wGwGSF_Barrel[2] = Elec_Fbrem;
    Var_wGwGSF_Barrel[3] = Elec_Chi2GSF;
    Var_wGwGSF_Barrel[4] = Elec_GSFNumHits;
    Var_wGwGSF_Barrel[5] = Elec_GSFTrackResol;
    Var_wGwGSF_Barrel[6] = Elec_GSFTracklnPt;
    Var_wGwGSF_Barrel[7] = Elec_GSFTrackEta;
    Var_wGwGSF_Barrel[8] = Tau_EtaAtEcalEntrance;
    Var_wGwGSF_Barrel[9] = Tau_Pt;
    Var_wGwGSF_Barrel[10] = Tau_EmFraction;
    Var_wGwGSF_Barrel[11] = Tau_NumGammaCands;
    Var_wGwGSF_Barrel[12] = Tau_HadrHoP;
    Var_wGwGSF_Barrel[13] = Tau_HadrEoP;
    Var_wGwGSF_Barrel[14] = Tau_VisMass;
    Var_wGwGSF_Barrel[15] = Tau_HadrMva;
    Var_wGwGSF_Barrel[16] = Tau_GammaEtaMom;
    Var_wGwGSF_Barrel[17] = Tau_GammaPhiMom;
    Var_wGwGSF_Barrel[18] = Tau_GammaEnFrac;
    Var_wGwGSF_Barrel[19] = Tau_GSFChi2;
    Var_wGwGSF_Barrel[20] = Tau_NumHitsVariable;
    Var_wGwGSF_Barrel[21] = Tau_GSFTrackResol;
    Var_wGwGSF_Barrel[22] = Tau_GSFTracklnPt;
    Var_wGwGSF_Barrel[23] = Tau_GSFTrackEta;
    Var_wGwGSF_Barrel[24] = Tau_dCrackEta;
    Var_wGwGSF_Barrel[25] = Tau_dCrackPhi;
		
    ////
										      
    Float_t *Var_NoEleMatch_woGwoGSF_Endcap = new Float_t[7];
    Var_NoEleMatch_woGwoGSF_Endcap[0] = Tau_EtaAtEcalEntrance;
    Var_NoEleMatch_woGwoGSF_Endcap[1] = Tau_Pt;
    Var_NoEleMatch_woGwoGSF_Endcap[2] = Tau_EmFraction;
    Var_NoEleMatch_woGwoGSF_Endcap[3] = Tau_HadrHoP;
    Var_NoEleMatch_woGwoGSF_Endcap[4] = Tau_HadrEoP;
    Var_NoEleMatch_woGwoGSF_Endcap[5] = Tau_VisMass;
    Var_NoEleMatch_woGwoGSF_Endcap[6] = Tau_dCrackEta;

    Float_t *Var_NoEleMatch_woGwGSF_Endcap = new Float_t[13];
    Var_NoEleMatch_woGwGSF_Endcap[0] = Tau_EtaAtEcalEntrance;
    Var_NoEleMatch_woGwGSF_Endcap[1] = Tau_Pt;
    Var_NoEleMatch_woGwGSF_Endcap[2] = Tau_EmFraction;
    Var_NoEleMatch_woGwGSF_Endcap[3] = Tau_HadrHoP;
    Var_NoEleMatch_woGwGSF_Endcap[4] = Tau_HadrEoP;
    Var_NoEleMatch_woGwGSF_Endcap[5] = Tau_VisMass;
    Var_NoEleMatch_woGwGSF_Endcap[6] = Tau_HadrMva;
    Var_NoEleMatch_woGwGSF_Endcap[7] = Tau_GSFChi2;
    Var_NoEleMatch_woGwGSF_Endcap[8] = Tau_NumHitsVariable;
    Var_NoEleMatch_woGwGSF_Endcap[9] = Tau_GSFTrackResol;
    Var_NoEleMatch_woGwGSF_Endcap[10] = Tau_GSFTracklnPt;
    Var_NoEleMatch_woGwGSF_Endcap[11] = Tau_GSFTrackEta;
    Var_NoEleMatch_woGwGSF_Endcap[12] = Tau_dCrackEta;
    	
    Float_t *Var_NoEleMatch_wGwoGSF_Endcap = new Float_t[11];
    Var_NoEleMatch_wGwoGSF_Endcap[0] = Tau_EtaAtEcalEntrance;
    Var_NoEleMatch_wGwoGSF_Endcap[1] = Tau_Pt;
    Var_NoEleMatch_wGwoGSF_Endcap[2] = Tau_EmFraction;
    Var_NoEleMatch_wGwoGSF_Endcap[3] = Tau_NumGammaCands;
    Var_NoEleMatch_wGwoGSF_Endcap[4] = Tau_HadrHoP;
    Var_NoEleMatch_wGwoGSF_Endcap[5] = Tau_HadrEoP;
    Var_NoEleMatch_wGwoGSF_Endcap[6] = Tau_VisMass;
    Var_NoEleMatch_wGwoGSF_Endcap[7] = Tau_GammaEtaMom;
    Var_NoEleMatch_wGwoGSF_Endcap[8] = Tau_GammaPhiMom;
    Var_NoEleMatch_wGwoGSF_Endcap[9] = Tau_GammaEnFrac;
    Var_NoEleMatch_wGwoGSF_Endcap[10] = Tau_dCrackEta;
		
    Float_t *Var_NoEleMatch_wGwGSF_Endcap = new Float_t[17];
    Var_NoEleMatch_wGwGSF_Endcap[0] = Tau_EtaAtEcalEntrance;
    Var_NoEleMatch_wGwGSF_Endcap[1] = Tau_Pt;
    Var_NoEleMatch_wGwGSF_Endcap[2] = Tau_EmFraction;
    Var_NoEleMatch_wGwGSF_Endcap[3] = Tau_NumGammaCands;
    Var_NoEleMatch_wGwGSF_Endcap[4] = Tau_HadrHoP;
    Var_NoEleMatch_wGwGSF_Endcap[5] = Tau_HadrEoP;
    Var_NoEleMatch_wGwGSF_Endcap[6] = Tau_VisMass;
    Var_NoEleMatch_wGwGSF_Endcap[7] = Tau_HadrMva;
    Var_NoEleMatch_wGwGSF_Endcap[8] = Tau_GammaEtaMom;
    Var_NoEleMatch_wGwGSF_Endcap[9] = Tau_GammaPhiMom;
    Var_NoEleMatch_wGwGSF_Endcap[10] = Tau_GammaEnFrac;
    Var_NoEleMatch_wGwGSF_Endcap[11] = Tau_GSFChi2;
    Var_NoEleMatch_wGwGSF_Endcap[12] = Tau_NumHitsVariable;
    Var_NoEleMatch_wGwGSF_Endcap[13] = Tau_GSFTrackResol;
    Var_NoEleMatch_wGwGSF_Endcap[14] = Tau_GSFTracklnPt;
    Var_NoEleMatch_wGwGSF_Endcap[15] = Tau_GSFTrackEta;
    Var_NoEleMatch_wGwGSF_Endcap[16] = Tau_dCrackEta;
	
    Float_t *Var_woGwoGSF_Endcap = new Float_t[15];
    Var_woGwoGSF_Endcap[0] = Elec_EtotOverPin;
    Var_woGwoGSF_Endcap[1] = Elec_EgammaOverPdif;
    Var_woGwoGSF_Endcap[2] = Elec_Fbrem;
    Var_woGwoGSF_Endcap[3] = Elec_Chi2GSF;
    Var_woGwoGSF_Endcap[4] = Elec_GSFNumHits;
    Var_woGwoGSF_Endcap[5] = Elec_GSFTrackResol;
    Var_woGwoGSF_Endcap[6] = Elec_GSFTracklnPt;
    Var_woGwoGSF_Endcap[7] = Elec_GSFTrackEta;
    Var_woGwoGSF_Endcap[8] = Tau_EtaAtEcalEntrance;
    Var_woGwoGSF_Endcap[9] = Tau_Pt;
    Var_woGwoGSF_Endcap[10] = Tau_EmFraction;
    Var_woGwoGSF_Endcap[11] = Tau_HadrHoP;
    Var_woGwoGSF_Endcap[12] = Tau_HadrEoP;
    Var_woGwoGSF_Endcap[13] = Tau_VisMass;
    Var_woGwoGSF_Endcap[14] = Tau_dCrackEta;

    Float_t *Var_woGwGSF_Endcap = new Float_t[21];
    Var_woGwGSF_Endcap[0] = Elec_EtotOverPin;
    Var_woGwGSF_Endcap[1] = Elec_EgammaOverPdif;
    Var_woGwGSF_Endcap[2] = Elec_Fbrem;
    Var_woGwGSF_Endcap[3] = Elec_Chi2GSF;
    Var_woGwGSF_Endcap[4] = Elec_GSFNumHits;
    Var_woGwGSF_Endcap[5] = Elec_GSFTrackResol;
    Var_woGwGSF_Endcap[6] = Elec_GSFTracklnPt;
    Var_woGwGSF_Endcap[7] = Elec_GSFTrackEta;
    Var_woGwGSF_Endcap[8] = Tau_EtaAtEcalEntrance;
    Var_woGwGSF_Endcap[9] = Tau_Pt;
    Var_woGwGSF_Endcap[10] = Tau_EmFraction;
    Var_woGwGSF_Endcap[11] = Tau_HadrHoP;
    Var_woGwGSF_Endcap[12] = Tau_HadrEoP;
    Var_woGwGSF_Endcap[13] = Tau_VisMass;
    Var_woGwGSF_Endcap[14] = Tau_HadrMva;
    Var_woGwGSF_Endcap[15] = Tau_GSFChi2;
    Var_woGwGSF_Endcap[16] = Tau_NumHitsVariable;
    Var_woGwGSF_Endcap[17] = Tau_GSFTrackResol;
    Var_woGwGSF_Endcap[18] = Tau_GSFTracklnPt;
    Var_woGwGSF_Endcap[19] = Tau_GSFTrackEta;
    Var_woGwGSF_Endcap[20] = Tau_dCrackEta;
		
    Float_t *Var_wGwoGSF_Endcap = new Float_t[19];
    Var_wGwoGSF_Endcap[0] = Elec_EtotOverPin;
    Var_wGwoGSF_Endcap[1] = Elec_EgammaOverPdif;
    Var_wGwoGSF_Endcap[2] = Elec_Fbrem;
    Var_wGwoGSF_Endcap[3] = Elec_Chi2GSF;
    Var_wGwoGSF_Endcap[4] = Elec_GSFNumHits;
    Var_wGwoGSF_Endcap[5] = Elec_GSFTrackResol;
    Var_wGwoGSF_Endcap[6] = Elec_GSFTracklnPt;
    Var_wGwoGSF_Endcap[7] = Elec_GSFTrackEta;
    Var_wGwoGSF_Endcap[8] = Tau_EtaAtEcalEntrance;
    Var_wGwoGSF_Endcap[9] = Tau_Pt;
    Var_wGwoGSF_Endcap[10] = Tau_EmFraction;
    Var_wGwoGSF_Endcap[11] = Tau_NumGammaCands;
    Var_wGwoGSF_Endcap[12] = Tau_HadrHoP;
    Var_wGwoGSF_Endcap[13] = Tau_HadrEoP;
    Var_wGwoGSF_Endcap[14] = Tau_VisMass;
    Var_wGwoGSF_Endcap[15] = Tau_GammaEtaMom;
    Var_wGwoGSF_Endcap[16] = Tau_GammaPhiMom;
    Var_wGwoGSF_Endcap[17] = Tau_GammaEnFrac;
    Var_wGwoGSF_Endcap[18] = Tau_dCrackEta;
		
    Float_t *Var_wGwGSF_Endcap = new Float_t[25];
    Var_wGwGSF_Endcap[0] = Elec_EtotOverPin;
    Var_wGwGSF_Endcap[1] = Elec_EgammaOverPdif;
    Var_wGwGSF_Endcap[2] = Elec_Fbrem;
    Var_wGwGSF_Endcap[3] = Elec_Chi2GSF;
    Var_wGwGSF_Endcap[4] = Elec_GSFNumHits;
    Var_wGwGSF_Endcap[5] = Elec_GSFTrackResol;
    Var_wGwGSF_Endcap[6] = Elec_GSFTracklnPt;
    Var_wGwGSF_Endcap[7] = Elec_GSFTrackEta;
    Var_wGwGSF_Endcap[8] = Tau_EtaAtEcalEntrance;
    Var_wGwGSF_Endcap[9] = Tau_Pt;
    Var_wGwGSF_Endcap[10] = Tau_EmFraction;
    Var_wGwGSF_Endcap[11] = Tau_NumGammaCands;
    Var_wGwGSF_Endcap[12] = Tau_HadrHoP;
    Var_wGwGSF_Endcap[13] = Tau_HadrEoP;
    Var_wGwGSF_Endcap[14] = Tau_VisMass;
    Var_wGwGSF_Endcap[15] = Tau_HadrMva;
    Var_wGwGSF_Endcap[16] = Tau_GammaEtaMom;
    Var_wGwGSF_Endcap[17] = Tau_GammaPhiMom;
    Var_wGwGSF_Endcap[18] = Tau_GammaEnFrac;
    Var_wGwGSF_Endcap[19] = Tau_GSFChi2;
    Var_wGwGSF_Endcap[20] = Tau_NumHitsVariable;
    Var_wGwGSF_Endcap[21] = Tau_GSFTrackResol;
    Var_wGwGSF_Endcap[22] = Tau_GSFTracklnPt;
    Var_wGwGSF_Endcap[23] = Tau_GSFTrackEta;
    Var_wGwGSF_Endcap[24] = Tau_dCrackEta;
		
    
    t_Elec_GenEleMatch = Elec_GenEleMatch;
    t_Elec_GenHadMatch = Elec_GenHadMatch;
    t_Tau_GenEleMatch = Tau_GenEleMatch;
    t_Tau_GenHadMatch = Tau_GenHadMatch;

    t_Tau_IsoMVALoose = Tau_IsoMVALoose;
    t_Tau_Eta = Tau_Eta;
    t_Tau_Pt = Tau_Pt;
    t_Tau_AntiELoose = Tau_AntiELoose;
    t_Tau_AntiEMedium = Tau_AntiEMedium;
    t_Tau_AntiETight = Tau_AntiETight;
    t_Tau_AntiEMVA = Tau_AntiEMVA;
    if(ElecVeto_Pt > -99) t_Tau_MatchElePassVeto = 1.;
    else t_Tau_MatchElePassVeto = 0.;
//     t_Tau_MatchElePassVeto = Tau_MatchElePassVeto;
    t_Tau_isInEcalCrack = isInEcalCrack(Tau_EtaAtEcalEntrance);
    t_Tau_isInEcalCrack2 = isInEcalCrack2(Tau_EtaAtEcalEntrance);

    Tau_AbsEta = TMath::Abs(Tau_EtaAtEcalEntrance);
    if(Tau_AbsEta<1.479){
      if(Tau_GsfEleMatch<0.5 && Tau_NumGammaCands<0.5 && Tau_HasGsf<0.5) {
	t_NoEleMatch_woGwoGSF_Barrel = gbr_NoEleMatch_woGwoGSF_BL->GetClassifier(Var_NoEleMatch_woGwoGSF_Barrel);
	t_NoEleMatch_woGwoGSF_BarrelXML = reader_NoEleMatch_woGwoGSF_BL->EvaluateMVA("BDTG");
	t_Category = 0;
	t_rawMva = t_NoEleMatch_woGwoGSF_Barrel;
	t_rawMvaXML = t_NoEleMatch_woGwoGSF_BarrelXML;
      }
      else if(Tau_GsfEleMatch<0.5 && Tau_NumGammaCands<0.5 && Tau_HasGsf>0.5){
	t_NoEleMatch_woGwGSF_Barrel = gbr_NoEleMatch_woGwGSF_BL->GetClassifier(Var_NoEleMatch_woGwGSF_Barrel);
	t_NoEleMatch_woGwGSF_BarrelXML = reader_NoEleMatch_woGwGSF_BL->EvaluateMVA("BDTG");
 	t_Category = 1;
	t_rawMva = t_NoEleMatch_woGwGSF_Barrel;
	t_rawMvaXML = t_NoEleMatch_woGwGSF_BarrelXML;
      }
      else if(Tau_GsfEleMatch<0.5 && Tau_NumGammaCands>0.5 && Tau_HasGsf<0.5){
	t_NoEleMatch_wGwoGSF_Barrel = gbr_NoEleMatch_wGwoGSF_BL->GetClassifier(Var_NoEleMatch_wGwoGSF_Barrel);
	t_NoEleMatch_wGwoGSF_BarrelXML = reader_NoEleMatch_wGwoGSF_BL->EvaluateMVA("BDTG");
	t_Category = 2;
	t_rawMva = t_NoEleMatch_wGwoGSF_Barrel;
	t_rawMvaXML = t_NoEleMatch_wGwoGSF_BarrelXML;
      }
      else if(Tau_GsfEleMatch<0.5 && Tau_NumGammaCands>0.5 && Tau_HasGsf>0.5){
	t_NoEleMatch_wGwGSF_Barrel = gbr_NoEleMatch_wGwGSF_BL->GetClassifier(Var_NoEleMatch_wGwGSF_Barrel);
	t_NoEleMatch_wGwGSF_BarrelXML = reader_NoEleMatch_wGwGSF_BL->EvaluateMVA("BDTG");
	t_Category = 3;
	t_rawMva = t_NoEleMatch_wGwGSF_Barrel;
	t_rawMvaXML = t_NoEleMatch_wGwGSF_BarrelXML;
      }
      else if(Tau_GsfEleMatch>0.5 && Tau_NumGammaCands<0.5 && Tau_HasGsf<0.5){
	t_woGwoGSF_Barrel = gbr_woGwoGSF_BL->GetClassifier(Var_woGwoGSF_Barrel);
	t_woGwoGSF_BarrelXML = reader_woGwoGSF_BL->EvaluateMVA("BDTG");
	t_Category = 4;
	t_rawMva = t_woGwoGSF_Barrel;
	t_rawMvaXML = t_woGwoGSF_BarrelXML;
      }
      else if(Tau_GsfEleMatch>0.5 && Tau_NumGammaCands<0.5 && Tau_HasGsf>0.5){
	t_woGwGSF_Barrel = gbr_woGwGSF_BL->GetClassifier(Var_woGwGSF_Barrel);
	t_woGwGSF_BarrelXML = reader_woGwGSF_BL->EvaluateMVA("BDTG");
	t_Category = 5;
	t_rawMva = t_woGwGSF_Barrel;
	t_rawMvaXML = t_woGwGSF_BarrelXML;
      }
      else if(Tau_GsfEleMatch>0.5 && Tau_NumGammaCands>0.5 && Tau_HasGsf<0.5){
	t_wGwoGSF_Barrel = gbr_wGwoGSF_BL->GetClassifier(Var_wGwoGSF_Barrel);
	t_wGwoGSF_BarrelXML = reader_wGwoGSF_BL->EvaluateMVA("BDTG");
	t_Category = 6;
	t_rawMva = t_wGwoGSF_Barrel;
	t_rawMvaXML = t_wGwoGSF_BarrelXML;
      }
      else if(Tau_GsfEleMatch>0.5 && Tau_NumGammaCands>0.5 && Tau_HasGsf>0.5){
	t_wGwGSF_Barrel = gbr_wGwGSF_BL->GetClassifier(Var_wGwGSF_Barrel);
	t_wGwGSF_BarrelXML = reader_wGwGSF_BL->EvaluateMVA("BDTG");
	t_Category = 7;
	t_rawMva = t_wGwGSF_Barrel;
	t_rawMvaXML = t_wGwGSF_BarrelXML;
      }
    }//For barrel
    else{
      if(Tau_GsfEleMatch<0.5 && Tau_NumGammaCands<0.5 && Tau_HasGsf<0.5){
	t_NoEleMatch_woGwoGSF_Endcap = gbr_NoEleMatch_woGwoGSF_EC->GetClassifier(Var_NoEleMatch_woGwoGSF_Endcap);
	t_NoEleMatch_woGwoGSF_EndcapXML = reader_NoEleMatch_woGwoGSF_EC->EvaluateMVA("BDTG");
	t_Category = 8;
	t_rawMva = t_NoEleMatch_woGwoGSF_Endcap;
	t_rawMvaXML = t_NoEleMatch_woGwoGSF_EndcapXML;
      }
      else if(Tau_GsfEleMatch<0.5 && Tau_NumGammaCands<0.5 && Tau_HasGsf>0.5){
	t_NoEleMatch_woGwGSF_Endcap = gbr_NoEleMatch_woGwGSF_EC->GetClassifier(Var_NoEleMatch_woGwGSF_Endcap);
	t_NoEleMatch_woGwGSF_EndcapXML = reader_NoEleMatch_woGwGSF_EC->EvaluateMVA("BDTG");
	t_Category = 9;
	t_rawMva = t_NoEleMatch_woGwGSF_Endcap;
	t_rawMvaXML = t_NoEleMatch_woGwGSF_EndcapXML;
      }
      else if(Tau_GsfEleMatch<0.5 && Tau_NumGammaCands>0.5 && Tau_HasGsf<0.5){
	t_NoEleMatch_wGwoGSF_Endcap = gbr_NoEleMatch_wGwoGSF_EC->GetClassifier(Var_NoEleMatch_wGwoGSF_Endcap);
	t_NoEleMatch_wGwoGSF_EndcapXML = reader_NoEleMatch_wGwoGSF_EC->EvaluateMVA("BDTG");
 	t_Category = 10;
	t_rawMva = t_NoEleMatch_wGwoGSF_Endcap;
	t_rawMvaXML = t_NoEleMatch_wGwoGSF_EndcapXML;
      }
      else if(Tau_GsfEleMatch<0.5 && Tau_NumGammaCands>0.5 && Tau_HasGsf>0.5){
	t_NoEleMatch_wGwGSF_Endcap = gbr_NoEleMatch_wGwGSF_EC->GetClassifier(Var_NoEleMatch_wGwGSF_Endcap);
 	t_NoEleMatch_wGwGSF_EndcapXML = reader_NoEleMatch_wGwGSF_EC->EvaluateMVA("BDTG");
	t_Category = 11;
	t_rawMva = t_NoEleMatch_wGwGSF_Endcap;
	t_rawMvaXML = t_NoEleMatch_wGwGSF_EndcapXML;
      }
      else if(Tau_GsfEleMatch>0.5 && Tau_NumGammaCands<0.5 && Tau_HasGsf<0.5){
	t_woGwoGSF_Endcap = gbr_woGwoGSF_EC->GetClassifier(Var_woGwoGSF_Endcap);
 	t_woGwoGSF_EndcapXML = reader_woGwoGSF_EC->EvaluateMVA("BDTG");
	t_Category = 12;
	t_rawMva = t_woGwoGSF_Endcap;
	t_rawMvaXML = t_woGwoGSF_EndcapXML;
      }
      else if(Tau_GsfEleMatch>0.5 && Tau_NumGammaCands<0.5 && Tau_HasGsf>0.5){
	t_woGwGSF_Endcap = gbr_woGwGSF_EC->GetClassifier(Var_woGwGSF_Endcap);
	t_woGwGSF_EndcapXML = reader_woGwGSF_EC->EvaluateMVA("BDTG");
	t_Category = 13;
	t_rawMva = t_woGwGSF_Endcap;
	t_rawMvaXML = t_woGwGSF_EndcapXML;
      }
      else if(Tau_GsfEleMatch>0.5 && Tau_NumGammaCands>0.5 && Tau_HasGsf<0.5){
	t_wGwoGSF_Endcap = gbr_wGwoGSF_EC->GetClassifier(Var_wGwoGSF_Endcap);
 	t_wGwoGSF_EndcapXML = reader_wGwoGSF_EC->EvaluateMVA("BDTG");
	t_Category = 14;
	t_rawMva = t_wGwoGSF_Endcap;
	t_rawMvaXML = t_wGwoGSF_EndcapXML;
      }
      else if(Tau_GsfEleMatch>0.5 && Tau_NumGammaCands>0.5 && Tau_HasGsf>0.5){
	t_wGwGSF_Endcap = gbr_wGwGSF_EC->GetClassifier(Var_wGwGSF_Endcap);
	t_wGwGSF_EndcapXML = reader_wGwGSF_EC->EvaluateMVA("BDTG");
	t_Category = 15;
	t_rawMva = t_wGwGSF_Endcap;
	t_rawMvaXML = t_wGwGSF_EndcapXML;
      }
    }//For Endcap

    
//     cout<<endl;
//     cout<<endl;
//     cout<<"Category  mvaOutput  mvaOutputXML"<<endl;
//     cout<<t_Category<<"   "<<t_rawMva<<"   "<<t_rawMvaXML<<endl;
// //     cout<<t_Tau_IsoMVALoose<<endl;

//     cout<<"output : "<<endl;
//     cout<<t_NoEleMatch_woGwoGSF_Barrel<<endl;
//     cout<<t_NoEleMatch_woGwGSF_Barrel<<endl;
//     cout<<t_NoEleMatch_wGwoGSF_Barrel<<endl;
//     cout<<t_NoEleMatch_wGwGSF_Barrel<<endl;
//     cout<<t_woGwoGSF_Barrel<<endl;
//     cout<<t_woGwGSF_Barrel<<endl;
//     cout<<t_wGwoGSF_Barrel<<endl;
//     cout<<t_wGwGSF_Barrel<<endl;
//     cout<<t_NoEleMatch_woGwoGSF_Endcap<<endl;
//     cout<<t_NoEleMatch_woGwGSF_Endcap<<endl;
//     cout<<t_NoEleMatch_wGwoGSF_Endcap<<endl;
//     cout<<t_NoEleMatch_wGwGSF_Endcap<<endl;
//     cout<<t_woGwoGSF_Endcap<<endl;
//     cout<<t_woGwGSF_Endcap<<endl;
//     cout<<t_wGwoGSF_Endcap<<endl;
//     cout<<t_wGwGSF_Endcap<<endl;

//     cout<<"output XML: "<<endl;
//     cout<<t_NoEleMatch_woGwoGSF_BarrelXML<<endl;
//     cout<<t_NoEleMatch_woGwGSF_BarrelXML<<endl;
//     cout<<t_NoEleMatch_wGwoGSF_BarrelXML<<endl;
//     cout<<t_NoEleMatch_wGwGSF_BarrelXML<<endl;
//     cout<<t_woGwoGSF_BarrelXML<<endl;
//     cout<<t_woGwGSF_BarrelXML<<endl;
//     cout<<t_wGwoGSF_BarrelXML<<endl;
//     cout<<t_wGwGSF_BarrelXML<<endl;
//     cout<<t_NoEleMatch_woGwoGSF_EndcapXML<<endl;
//     cout<<t_NoEleMatch_woGwGSF_EndcapXML<<endl;
//     cout<<t_NoEleMatch_wGwoGSF_EndcapXML<<endl;
//     cout<<t_NoEleMatch_wGwGSF_EndcapXML<<endl;
//     cout<<t_woGwoGSF_EndcapXML<<endl;
//     cout<<t_woGwGSF_EndcapXML<<endl;
//     cout<<t_wGwoGSF_EndcapXML<<endl;
//     cout<<t_wGwGSF_EndcapXML<<endl;


    if (t_rawMva>(t_rawMvaXML+0.01))hOver->Fill(t_Category);
    if (t_rawMva<(t_rawMvaXML-0.01))hBelow->Fill(t_Category);

    mytree->Fill();

  }

  mytree->Write();
  hOver->Write();
  hBelow->Write();

  cout<<"Creating file : "<<outputFileName.data()<<endl;
  fin->Close();
  inputFile->Close();
  outputFile->Close();
  return;
}

// void getAllMVAOutput(){
//   MVAOutput("","Signal");
//   MVAOutput("","Backgrd");
// //   MVAOutput("","");
// }

int main(int argc, char* argv[]) 
{
  MVAOutput("","Signal");
//   MVAOutput("","Backgrd");
//   MVAOutput("","");
  return 0;

}
