//--------------------------------------------------------------------------------------------------
// tmvaAntiElectron 
//
// Macro training and testing an MVA AntiElectronID for Taus.
// It takes as input a PFTau-(GsfElectron) pair matched to a Tau Hadron (Signal), and matched with a Gen Electron
// for the background tree.
//
// Authors: I.Naranjo
//--------------------------------------------------------------------------------------------------
#include <cstdlib>
#include <iostream> 
#include <map>
#include <string>
#include <exception>

#include "TChain.h"
#include "TMath.h"
#include "TFile.h"
#include "TTree.h"
#include "TString.h"
#include "TObjString.h"
#include "TSystem.h"
#include "TROOT.h"
#include "TPluginManager.h"
#include "TH1F.h"
#include "TFile.h"

// #include "TMVAGui.C"

#if not defined(__CINT__) || defined(__MAKECINT__)

#include "TMVA/Factory.h"
#include "TMVA/Reader.h"
#include "TMVA/Tools.h"
#endif


void TMVAClassification(std::string Cat_ = "_All",
			std::string Sel_ = "Barrel",
			std::string Discr_ = ""	,
			std::string Cut_ = "" ,		
			std::string CutName_ = "" 		
			)
{

  TMVA::Tools::Instance();

//   TString outfileName( "tmvaRoot/TMVA_v4"+Discr_+Cat_+"_"+Sel_+".root" );
//   TString outfileName( "tmvaRoot/TMVA_v5"+Discr_+Cat_+"_"+Sel_+".root" );
//   TString outfileName( "tmvaRoot/TMVA_v4_EtaAtEcal"+Discr_+Cat_+"_"+Sel_+".root" );
//   TString outfileName( "tmvaRoot/TMVA_v6"+Discr_+Cat_+"_"+Sel_+".root" );
//   TString outfileName( "tmvaRoot/TMVA_v6MVAIso"+Discr_+Cat_+"_"+Sel_+".root" );
//   TString outfileName( "tmvaRoot/TMVA_v7"+Discr_+Cat_+"_"+Sel_+".root" );
//   TString outfileName( "tmvaRoot/TMVA_v7-NoEleVeto"+Discr_+Cat_+"_"+Sel_+".root" );
//   TString outfileName( "tmvaRoot/TMVA_v7-MVAIso"+Discr_+Cat_+"_"+Sel_+".root" );
//   TString outfileName( "tmvaRoot/TMVA_v7-NoEleVeto-MVAIso"+Discr_+Cat_+"_"+Sel_+".root" );
//   TString outfileName( "tmvaRoot/TMVA_v8Bis"+Discr_+Cat_+"_"+Sel_+".root" );
//   TString outfileName( "tmvaRoot/TMVA_v8"+Discr_+Cat_+"_"+Sel_+".root" );
//   TString outfileName( "tmvaRoot/TMVA_v9EleVetoBis"+CutName_+Discr_+Cat_+"_"+Sel_+".root" );
//   TString outfileName( "tmvaRoot/TMVA_v11DYEleVeto"+CutName_+Discr_+Cat_+"_"+Sel_+".root" );
//   TString outfileName( "tmvaRoot/TMVA_v12EleVeto"+CutName_+Discr_+Cat_+"_"+Sel_+".root" );
//   TString outfileName( "tmvaRoot/TMVA_v13EleVeto"+CutName_+Discr_+Cat_+"_"+Sel_+".root" );
//   TString outfileName( "tmvaRoot/TMVA_v14EleVeto"+CutName_+Discr_+Cat_+"_"+Sel_+".root" );
//   TString outfileName( "tmvaRoot/TMVA_v15EleVeto1Prong"+CutName_+Discr_+Cat_+"_"+Sel_+".root" );
//   TString outfileName( "tmvaRoot/TMVA_v16EleVeto"+CutName_+Discr_+Cat_+"_"+Sel_+".root" );
  TString outfileName( "tmvaRoot/TMVA_v17EleVetoDM"+CutName_+Discr_+Cat_+"_"+Sel_+".root" );
  TFile* outputFile = TFile::Open( outfileName, "RECREATE" );

//   TMVA::Factory *factory = new TMVA::Factory( "TMVAClassification_v4"+Discr_+Cat_+"_"+Sel_, outputFile, 
// 					      "!V:!Silent:Color:DrawProgressBar" );
//   TMVA::Factory *factory = new TMVA::Factory( "TMVAClassification_v4_EtaAtEcal"+Discr_+Cat_+"_"+Sel_, outputFile, 
// 					      "!V:!Silent:Color:DrawProgressBar" );
//   TMVA::Factory *factory = new TMVA::Factory( "TMVAClassification_v5"+Discr_+Cat_+"_"+Sel_, outputFile, 
// 					      "!V:!Silent:Color:DrawProgressBar" );
//   TMVA::Factory *factory = new TMVA::Factory( "TMVAClassification_v6"+Discr_+Cat_+"_"+Sel_, outputFile, 
// 					      "!V:!Silent:Color:DrawProgressBar" ); 
//   TMVA::Factory *factory = new TMVA::Factory( "TMVAClassification_v6MVAIso"+Discr_+Cat_+"_"+Sel_, outputFile, 
// 					      "!V:!Silent:Color:DrawProgressBar" ); 
//   TMVA::Factory *factory = new TMVA::Factory( "TMVAClassification_v7"+Discr_+Cat_+"_"+Sel_, outputFile, 
// 					      "!V:!Silent:Color:DrawProgressBar" ); 
//   TMVA::Factory *factory = new TMVA::Factory( "TMVAClassification_v7-NoEleVeto"+Discr_+Cat_+"_"+Sel_, outputFile, 
// 					      "!V:!Silent:Color:DrawProgressBar" ); 
  
//   TMVA::Factory *factory = new TMVA::Factory( "TMVAClassification_v7-MVAIso"+Discr_+Cat_+"_"+Sel_, outputFile, 
// 					      "!V:!Silent:Color:DrawProgressBar" ); 
//   TMVA::Factory *factory = new TMVA::Factory( "TMVAClassification_v7-NoEleVeto-MVAIso"+Discr_+Cat_+"_"+Sel_, outputFile, 
// 					      "!V:!Silent:Color:DrawProgressBar" ); 

//   TMVA::Factory *factory = new TMVA::Factory( "TMVAClassification_v8Bis"+Discr_+Cat_+"_"+Sel_, outputFile, 
// 					      "!V:!Silent:Color:DrawProgressBar" ); //CombIso
//   TMVA::Factory *factory = new TMVA::Factory( "TMVAClassification_v8"+Discr_+Cat_+"_"+Sel_, outputFile, 
// 					      "!V:!Silent:Color:DrawProgressBar" ); //MVAIso

//   TMVA::Factory *factory = new TMVA::Factory( "TMVAClassification_v9EleVeto"+CutName_+Discr_+Cat_+"_"+Sel_, outputFile, 
// 					      "!V:!Silent:Color:DrawProgressBar" ); //MVAIso

//   TMVA::Factory *factory = new TMVA::Factory( "TMVAClassification_v11DYEleVeto"+CutName_+Discr_+Cat_+"_"+Sel_, outputFile, 
// 					      "!V:!Silent:Color:DrawProgressBar" ); //MVAIso

//   TMVA::Factory *factory = new TMVA::Factory( "TMVAClassification_v12EleVeto"+CutName_+Discr_+Cat_+"_"+Sel_, outputFile, 
// 					      "!V:!Silent:Color:DrawProgressBar" ); //MVAIso

//   TMVA::Factory *factory = new TMVA::Factory( "TMVAClassification_v13EleVeto"+CutName_+Discr_+Cat_+"_"+Sel_, outputFile, 
// 					      "!V:!Silent:Color:DrawProgressBar" ); //MVAIso

//   TMVA::Factory *factory = new TMVA::Factory( "TMVAClassification_v14EleVeto"+CutName_+Discr_+Cat_+"_"+Sel_, outputFile, 
// 					      "!V:!Silent:Color:DrawProgressBar" ); //Comb3HitsIso
//   TMVA::Factory *factory = new TMVA::Factory( "TMVAClassification_v15EleVeto1Prong"+CutName_+Discr_+Cat_+"_"+Sel_, outputFile, 
// 					      "!V:!Silent:Color:DrawProgressBar" ); //Comb3HitsIso
//   TMVA::Factory *factory = new TMVA::Factory( "TMVAClassification_v16EleVeto"+CutName_+Discr_+Cat_+"_"+Sel_, outputFile, 
// 					      "!V:!Silent:Color:DrawProgressBar" ); //Comb3HitsIso
  TMVA::Factory *factory = new TMVA::Factory( "TMVAClassification_v17EleVetoDM"+CutName_+Discr_+Cat_+"_"+Sel_, outputFile, 
					      "!V:!Silent:Color:DrawProgressBar" ); //Comb3HitsIso

//  if(Cat_.find("_All")!=string::npos){    
//    factory->AddVariable( "Elec_Pt","Elec_Pt","     ", 'F'  );   
//    factory->AddVariable( "Elec_AbsEta","ElecAbsEta","     ", 'F'  );
//    factory->AddVariable( "Elec_EtotOverPin","EtotOverPin","     ", 'F'  );
//    factory->AddVariable( "Elec_EeOverPout","EeOverPout","     ", 'F'  );
//    factory->AddVariable( "Elec_EgammaOverPdif","EgammaOverPdif","     ", 'F'  );
//    factory->AddVariable( "Elec_EarlyBrem","EarlyBrem","     ", 'I'  );
//    factory->AddVariable( "Elec_LateBrem","LateBrem","     ", 'I'  );
// // //    factory->AddVariable( "Elec_Logsihih","Elec_Logsihih","     ", 'F'  );
// // //    factory->AddVariable( "Elec_DeltaEta","Elec_DeltaEta","     ", 'F'  );
//    factory->AddVariable( "Elec_Fbrem", "Fbrem","     ", 'F'  );
//    factory->AddVariable( "Elec_Chi2KF", "Chi2KF","     ", 'F'  );
//    factory->AddVariable( "Elec_Chi2GSF","Elec_Chi2GSF","     ", 'F'  ); 
//    factory->AddVariable( "Elec_NumHits","NumHits","     ", 'I'  );
//    factory->AddVariable( "Elec_GSFTrackResol","Elec_GSFTrackResol","     ", 'F'  );
//    factory->AddVariable( "Elec_GSFTracklnPt","Elec_GSFTracklnPt","     ", 'F'  ); 
//    factory->AddVariable( "Elec_GSFTrackEta","Elec_GSFTrackEta","     ", 'F'  );  
   
//    factory->AddVariable( "Tau_AbsEta","PFTauEta","     ", 'F'  );
//    factory->AddVariable( "Tau_Pt","TauPt","     ", 'F'  );            
//    factory->AddVariable( "Tau_HasGsf","TauHasGsf","     ", 'I'  );
//    factory->AddVariable( "Tau_EmFraction","TauEmFraction","     ", 'F'  );
//    factory->AddVariable( "Tau_NumChargedCands","Tau_NumChargedCands","     ", 'I'  );
//    factory->AddVariable( "Tau_NumGammaCands","TauNumGammaCands","     ", 'I'  );
//    factory->AddVariable( "Tau_HadrHoP","TauHadrHoP","     ", 'F'  );
//    factory->AddVariable( "Tau_HadrEoP","TauHadrEoP","     ", 'F'  );
//    factory->AddVariable( "Tau_VisMass","TauVisMass","     ", 'F'  );
//    factory->AddVariable( "Tau_GammaEtaMom","Tau_GammaEtaMom","     ", 'F'  );    
//    factory->AddVariable( "Tau_GammaPhiMom","Tau_GammaPhiMom","     ", 'F'  ); 
//    factory->AddVariable( "Tau_GammaEnFrac","GammaEnFrac","     ", 'F'  );
//    factory->AddVariable( "Tau_HadrMva","HadrMva","     ", 'F'  );//for v8
//  }

 if(Cat_.find("_NoEleMatch_woGwoGSF")!=string::npos){    
   factory->AddVariable( "Tau_EtaAtEcalEntrance","PFTauEtaAtEcalEntrance","     ", 'F'  );
   factory->AddVariable( "Tau_Pt","TauPt","     ", 'F'  );            
   factory->AddVariable( "Tau_EmFraction","TauEmFraction","     ", 'F'  );
   factory->AddVariable( "Tau_HadrHoP","TauHadrHoP","     ", 'F'  );
   factory->AddVariable( "Tau_HadrEoP","TauHadrEoP","     ", 'F'  );
//    factory->AddVariable( "Tau_VisMass","TauVisMass","     ", 'F'  );//comment for separatesdecaymodes
   factory->AddVariable( "Tau_dCrackEta","TaudCrackEta","     ", 'F'  );
//    factory->AddVariable( "Tau_dCrackPhi","TaudCrackPhi","     ", 'F'  );
   factory->AddVariable( "Tau_DecayMode","TauDecayMode","     ", 'F'  );//comment for separatesdecaymodes
 }
 if(Cat_.find("_NoEleMatch_woGwGSF")!=string::npos){    
   factory->AddVariable( "Tau_EtaAtEcalEntrance","PFTauEtaAtEcalEntrance","     ", 'F'  );
   factory->AddVariable( "Tau_Pt","TauPt","     ", 'F'  );            
   factory->AddVariable( "Tau_EmFraction","TauEmFraction","     ", 'F'  );
   factory->AddVariable( "Tau_HadrHoP","TauHadrHoP","     ", 'F'  );
   factory->AddVariable( "Tau_HadrEoP","TauHadrEoP","     ", 'F'  );
//    factory->AddVariable( "Tau_VisMass","TauVisMass","     ", 'F'  );//comment for separatesdecaymodes
   factory->AddVariable( "Tau_HadrMva","HadrMva","     ", 'F'  );
   factory->AddVariable( "Tau_GSFChi2","Tau_GSFChi2","     ", 'F'  );
   factory->AddVariable( "(Tau_GSFNumHits - Tau_KFNumHits)/(Tau_GSFNumHits + Tau_KFNumHits)","Tau_NumHitsVariable","     ", 'F'  );
   factory->AddVariable( "Tau_GSFTrackResol","Tau_GSFTrackResol","     ", 'F'  );
   factory->AddVariable( "Tau_GSFTracklnPt","Tau_GSFTracklnPt","     ", 'F'  );
   factory->AddVariable( "Tau_GSFTrackEta","Tau_GSFTrackEta","     ", 'F'  );
   factory->AddVariable( "Tau_dCrackEta","TaudCrackEta","     ", 'F'  );
//    factory->AddVariable( "Tau_dCrackPhi","TaudCrackPhi","     ", 'F'  );
   factory->AddVariable( "Tau_DecayMode","TauDecayMode","     ", 'F'  );//comment for separatesdecaymodes
 }
 if(Cat_.find("_NoEleMatch_wGwoGSF")!=string::npos){    
   factory->AddVariable( "Tau_EtaAtEcalEntrance","PFTauEtaAtEcalEntrance","     ", 'F'  );
   factory->AddVariable( "Tau_Pt","TauPt","     ", 'F'  );            
   factory->AddVariable( "Tau_EmFraction","TauEmFraction","     ", 'F'  );
   factory->AddVariable( "Tau_NumGammaCands","TauNumGammaCands","     ", 'I'  );
   factory->AddVariable( "Tau_HadrHoP","TauHadrHoP","     ", 'F'  );
   factory->AddVariable( "Tau_HadrEoP","TauHadrEoP","     ", 'F'  );
//    factory->AddVariable( "Tau_VisMass","TauVisMass","     ", 'F'  );//comment for separatesdecaymodes
   factory->AddVariable( "Tau_GammaEtaMom","Tau_GammaEtaMom","     ", 'F'  );    
   factory->AddVariable( "Tau_GammaPhiMom","Tau_GammaPhiMom","     ", 'F'  ); 
   factory->AddVariable( "Tau_GammaEnFrac","GammaEnFrac","     ", 'F'  );
   factory->AddVariable( "Tau_dCrackEta","TaudCrackEta","     ", 'F'  );
//    factory->AddVariable( "Tau_dCrackPhi","TaudCrackPhi","     ", 'F'  );
   factory->AddVariable( "Tau_DecayMode","TauDecayMode","     ", 'F'  );//comment for separatesdecaymodes
 }
 if(Cat_.find("_NoEleMatch_wGwGSF")!=string::npos){    
   factory->AddVariable( "Tau_EtaAtEcalEntrance","PFTauEtaAtEcalEntrance","     ", 'F'  );
   factory->AddVariable( "Tau_Pt","TauPt","     ", 'F'  );            
   factory->AddVariable( "Tau_EmFraction","TauEmFraction","     ", 'F'  );
   factory->AddVariable( "Tau_NumGammaCands","TauNumGammaCands","     ", 'I'  );
   factory->AddVariable( "Tau_HadrHoP","TauHadrHoP","     ", 'F'  );
   factory->AddVariable( "Tau_HadrEoP","TauHadrEoP","     ", 'F'  );
//    factory->AddVariable( "Tau_VisMass","TauVisMass","     ", 'F'  );//comment for separatesdecaymodes
   factory->AddVariable( "Tau_HadrMva","HadrMva","     ", 'F'  );
   factory->AddVariable( "Tau_GammaEtaMom","Tau_GammaEtaMom","     ", 'F'  );    
   factory->AddVariable( "Tau_GammaPhiMom","Tau_GammaPhiMom","     ", 'F'  ); 
   factory->AddVariable( "Tau_GammaEnFrac","GammaEnFrac","     ", 'F'  );
   factory->AddVariable( "Tau_GSFChi2","Tau_GSFChi2","     ", 'F'  );
   factory->AddVariable( "(Tau_GSFNumHits - Tau_KFNumHits)/(Tau_GSFNumHits + Tau_KFNumHits)","Tau_NumHitsVariable","     ", 'F'  );
   factory->AddVariable( "Tau_GSFTrackResol","Tau_GSFTrackResol","     ", 'F'  );
   factory->AddVariable( "Tau_GSFTracklnPt","Tau_GSFTracklnPt","     ", 'F'  );
   factory->AddVariable( "Tau_GSFTrackEta","Tau_GSFTrackEta","     ", 'F'  );
   factory->AddVariable( "Tau_dCrackEta","TaudCrackEta","     ", 'F'  );
//    factory->AddVariable( "Tau_dCrackPhi","TaudCrackPhi","     ", 'F'  );
   factory->AddVariable( "Tau_DecayMode","TauDecayMode","     ", 'F'  );//comment for separatesdecaymodes
 }

 if(Cat_.find("_woGwoGSF")!=string::npos && Cat_.find("_NoEleMatch")==string::npos){
   factory->AddVariable( "Elec_EtotOverPin","EtotOverPin","     ", 'F'  );
   factory->AddVariable( "Elec_EgammaOverPdif","EgammaOverPdif","     ", 'F'  );
   factory->AddVariable( "Elec_Fbrem", "Fbrem","     ", 'F'  );
   factory->AddVariable( "Elec_Chi2GSF", "Chi2GSF","     ", 'F'  );
   factory->AddVariable( "Elec_GSFNumHits","Elec_GSFNumHits","     ", 'I'  );
   factory->AddVariable( "Elec_GSFTrackResol","Elec_GSFTrackResol","     ", 'F'  );
   factory->AddVariable( "Elec_GSFTracklnPt","Elec_GSFTracklnPt","     ", 'F'  ); 
   factory->AddVariable( "Elec_GSFTrackEta","Elec_GSFTrackEta","     ", 'F'  ); 
 
// //    factory->AddVariable( "Elec_EeOverPout","Elec_EeOverPout","     ", 'F'  );
// //    factory->AddVariable( "Elec_EarlyBrem","Elec_EarlyBrem","     ", 'F'  );
// //    factory->AddVariable( "Elec_LateBrem","Elec_LateBrem","     ", 'F'  );
// //    factory->AddVariable( "Elec_Logsihih","Elec_Logsihih","     ", 'F'  );
// //    factory->AddVariable( "Elec_DeltaEta","Elec_DeltaEta","     ", 'F'  );

   factory->AddVariable( "Tau_EtaAtEcalEntrance","PFTauEtaAtEcalEntrance","     ", 'F'  );
   factory->AddVariable( "Tau_Pt","TauPt","     ", 'F'  );            
   factory->AddVariable( "Tau_EmFraction","TauEmFraction","     ", 'F'  );
   factory->AddVariable( "Tau_HadrHoP","TauHadrHoP","     ", 'F'  );
   factory->AddVariable( "Tau_HadrEoP","TauHadrEoP","     ", 'F'  );
//    factory->AddVariable( "Tau_VisMass","TauVisMass","     ", 'F'  );//comment for separatesdecaymodes
   factory->AddVariable( "Tau_dCrackEta","TaudCrackEta","     ", 'F'  );
//    factory->AddVariable( "Tau_dCrackPhi","TaudCrackPhi","     ", 'F'  );
   factory->AddVariable( "Tau_DecayMode","TauDecayMode","     ", 'F'  );//comment for separatesdecaymodes
}
 if(Cat_.find("_woGwGSF")!=string::npos && Cat_.find("_NoEleMatch")==string::npos){
   factory->AddVariable( "Elec_EtotOverPin","EtotOverPin","     ", 'F'  );
   factory->AddVariable( "Elec_EgammaOverPdif","EgammaOverPdif","     ", 'F'  );
   factory->AddVariable( "Elec_Fbrem", "Fbrem","     ", 'F'  );
   factory->AddVariable( "Elec_Chi2GSF","Elec_Chi2GSF","     ", 'F'  ); 
   factory->AddVariable( "Elec_GSFNumHits","Elec_GSFNumHits","     ", 'I'  );
   factory->AddVariable( "Elec_GSFTrackResol","Elec_GSFTrackResol","     ", 'F'  );
   factory->AddVariable( "Elec_GSFTracklnPt","Elec_GSFTracklnPt","     ", 'F'  ); 
   factory->AddVariable( "Elec_GSFTrackEta","Elec_GSFTrackEta","     ", 'F'  );  
   
// //    factory->AddVariable( "Elec_EeOverPout","Elec_EeOverPout","     ", 'F'  );
// //    factory->AddVariable( "Elec_EarlyBrem","Elec_EarlyBrem","     ", 'F'  );
// //    factory->AddVariable( "Elec_LateBrem","Elec_LateBrem","     ", 'F'  );
// //    factory->AddVariable( "Elec_Logsihih","Elec_Logsihih","     ", 'F'  );
// //    factory->AddVariable( "Elec_DeltaEta","Elec_DeltaEta","     ", 'F'  );

   factory->AddVariable( "Tau_EtaAtEcalEntrance","PFTauEtaAtEcalEntrance","     ", 'F'  );
   factory->AddVariable( "Tau_Pt","TauPt","     ", 'F'  );            
   factory->AddVariable( "Tau_EmFraction","TauEmFraction","     ", 'F'  );
   factory->AddVariable( "Tau_HadrHoP","TauHadrHoP","     ", 'F'  );
   factory->AddVariable( "Tau_HadrEoP","TauHadrEoP","     ", 'F'  );
//    factory->AddVariable( "Tau_VisMass","TauVisMass","     ", 'F'  );//comment for separatesdecaymodes
   factory->AddVariable( "Tau_HadrMva","HadrMva","     ", 'F'  );
   factory->AddVariable( "Tau_GSFChi2","Tau_GSFChi2","     ", 'F'  );
   factory->AddVariable( "(Tau_GSFNumHits - Tau_KFNumHits)/(Tau_GSFNumHits + Tau_KFNumHits)","Tau_NumHitsVariable","     ", 'F'  );
   factory->AddVariable( "Tau_GSFTrackResol","Tau_GSFTrackResol","     ", 'F'  );
   factory->AddVariable( "Tau_GSFTracklnPt","Tau_GSFTracklnPt","     ", 'F'  );
   factory->AddVariable( "Tau_GSFTrackEta","Tau_GSFTrackEta","     ", 'F'  );
   factory->AddVariable( "Tau_dCrackEta","TaudCrackEta","     ", 'F'  );
//    factory->AddVariable( "Tau_dCrackPhi","TaudCrackPhi","     ", 'F'  );
   factory->AddVariable( "Tau_DecayMode","TauDecayMode","     ", 'F'  );//comment for separatesdecaymodes
 }
 if(Cat_.find("_wGwoGSF")!=string::npos && Cat_.find("_NoEleMatch")==string::npos){
   factory->AddVariable( "Elec_EtotOverPin","EtotOverPin","     ", 'F'  );
   factory->AddVariable( "Elec_EgammaOverPdif","EgammaOverPdif","     ", 'F'  );
   factory->AddVariable( "Elec_Fbrem", "Fbrem","     ", 'F'  );
   factory->AddVariable( "Elec_Chi2GSF","Elec_Chi2GSF","     ", 'F'  ); 
   factory->AddVariable( "Elec_GSFNumHits","Elec_GSFNumHits","     ", 'I'  );
   factory->AddVariable( "Elec_GSFTrackResol","Elec_GSFTrackResol","     ", 'F'  );
   factory->AddVariable( "Elec_GSFTracklnPt","Elec_GSFTracklnPt","     ", 'F'  ); 
   factory->AddVariable( "Elec_GSFTrackEta","Elec_GSFTrackEta","     ", 'F'  );  
   
//   //  factory->AddVariable( "Elec_EeOverPout","Elec_EeOverPout","     ", 'F'  );
// //    factory->AddVariable( "Elec_EarlyBrem","Elec_EarlyBrem","     ", 'F'  );
// //    factory->AddVariable( "Elec_LateBrem","Elec_LateBrem","     ", 'F'  );
// //    factory->AddVariable( "Elec_Logsihih","Elec_Logsihih","     ", 'F'  );
// //    factory->AddVariable( "Elec_DeltaEta","Elec_DeltaEta","     ", 'F'  );

   factory->AddVariable( "Tau_EtaAtEcalEntrance","PFTauEtaAtEcalEntrance","     ", 'F'  );
   factory->AddVariable( "Tau_Pt","TauPt","     ", 'F'  );            
   factory->AddVariable( "Tau_EmFraction","TauEmFraction","     ", 'F'  );
   factory->AddVariable( "Tau_NumGammaCands","TauNumGammaCands","     ", 'I'  );
   factory->AddVariable( "Tau_HadrHoP","TauHadrHoP","     ", 'F'  );
   factory->AddVariable( "Tau_HadrEoP","TauHadrEoP","     ", 'F'  );
//    factory->AddVariable( "Tau_VisMass","TauVisMass","     ", 'F'  );//comment for separatesdecaymodes
   factory->AddVariable( "Tau_GammaEtaMom","Tau_GammaEtaMom","     ", 'F'  );    
   factory->AddVariable( "Tau_GammaPhiMom","Tau_GammaPhiMom","     ", 'F'  ); 
   factory->AddVariable( "Tau_GammaEnFrac","GammaEnFrac","     ", 'F'  );
   factory->AddVariable( "Tau_dCrackEta","TaudCrackEta","     ", 'F'  );
//    factory->AddVariable( "Tau_dCrackPhi","TaudCrackPhi","     ", 'F'  );
   factory->AddVariable( "Tau_DecayMode","TauDecayMode","     ", 'F'  );//comment for separatesdecaymodes
 }
 if(Cat_.find("_wGwGSF")!=string::npos && Cat_.find("_NoEleMatch")==string::npos){
   factory->AddVariable( "Elec_EtotOverPin","EtotOverPin","     ", 'F'  );
   factory->AddVariable( "Elec_EgammaOverPdif","EgammaOverPdif","     ", 'F'  );
   factory->AddVariable( "Elec_Fbrem", "Fbrem","     ", 'F'  );
   factory->AddVariable( "Elec_Chi2GSF","Elec_Chi2GSF","     ", 'F'  ); 
   factory->AddVariable( "Elec_GSFNumHits","Elec_GSFNumHits","     ", 'I'  );
   factory->AddVariable( "Elec_GSFTrackResol","Elec_GSFTrackResol","     ", 'F'  );
   factory->AddVariable( "Elec_GSFTracklnPt","Elec_GSFTracklnPt","     ", 'F'  ); 
   factory->AddVariable( "Elec_GSFTrackEta","Elec_GSFTrackEta","     ", 'F'  );  
   
// //    factory->AddVariable( "Elec_EeOverPout","Elec_EeOverPout","     ", 'F'  );
// //    factory->AddVariable( "Elec_EarlyBrem","Elec_EarlyBrem","     ", 'F'  );
// //    factory->AddVariable( "Elec_LateBrem","Elec_LateBrem","     ", 'F'  );
// //    factory->AddVariable( "Elec_Logsihih","Elec_Logsihih","     ", 'F'  );
// //    factory->AddVariable( "Elec_DeltaEta","Elec_DeltaEta","     ", 'F'  );

   factory->AddVariable( "Tau_EtaAtEcalEntrance","PFTauEtaAtEcalEntrance","     ", 'F'  );
   factory->AddVariable( "Tau_Pt","TauPt","     ", 'F'  );            
   factory->AddVariable( "Tau_EmFraction","TauEmFraction","     ", 'F'  );
   factory->AddVariable( "Tau_NumGammaCands","TauNumGammaCands","     ", 'I'  );
   factory->AddVariable( "Tau_HadrHoP","TauHadrHoP","     ", 'F'  );
   factory->AddVariable( "Tau_HadrEoP","TauHadrEoP","     ", 'F'  );
//    factory->AddVariable( "Tau_VisMass","TauVisMass","     ", 'F'  );//comment for separatesdecaymodes
   factory->AddVariable( "Tau_HadrMva","HadrMva","     ", 'F'  );
   factory->AddVariable( "Tau_GammaEtaMom","Tau_GammaEtaMom","     ", 'F'  );    
   factory->AddVariable( "Tau_GammaPhiMom","Tau_GammaPhiMom","     ", 'F'  ); 
   factory->AddVariable( "Tau_GammaEnFrac","GammaEnFrac","     ", 'F'  );
   factory->AddVariable( "Tau_GSFChi2","Tau_GSFChi2","     ", 'F'  );
   factory->AddVariable( "(Tau_GSFNumHits - Tau_KFNumHits)/(Tau_GSFNumHits + Tau_KFNumHits)","Tau_NumHitsVariable","     ", 'F'  );
   factory->AddVariable( "Tau_GSFTrackResol","Tau_GSFTrackResol","     ", 'F'  );
   factory->AddVariable( "Tau_GSFTracklnPt","Tau_GSFTracklnPt","     ", 'F'  );
   factory->AddVariable( "Tau_GSFTrackEta","Tau_GSFTrackEta","     ", 'F'  );
   factory->AddVariable( "Tau_dCrackEta","TaudCrackEta","     ", 'F'  );
//    factory->AddVariable( "Tau_dCrackPhi","TaudCrackPhi","     ", 'F'  );
   factory->AddVariable( "Tau_DecayMode","TauDecayMode","     ", 'F'  );//comment for separatesdecaymodes
 }


//   TFile *fTau = new TFile(Form("/data_CMS/cms/ivo/AntiEMVA/Trees/root/V11DY/tree_AntiEMVA-DYEleVetoMVAIso%s%s_Tau.root",Discr_.data(),Cat_.data()),"READ"); 
//   TFile *fEle = new TFile(Form("/data_CMS/cms/ivo/AntiEMVA/Trees/root/V11DY/tree_AntiEMVA-DYEleVetoMVAIso%s%s_Elec.root",Discr_.data(),Cat_.data()),"READ");
//   TFile *fTau = new TFile(Form("/data_CMS/cms/ivo/AntiEMVA/Trees/root/V12/tree_AntiEMVA-EleVetoMVAIso%s%s_Tau.root",Discr_.data(),Cat_.data()),"READ"); 
//   TFile *fEle = new TFile(Form("/data_CMS/cms/ivo/AntiEMVA/Trees/root/V12/tree_AntiEMVA-EleVetoMVAIso%s%s_Elec.root",Discr_.data(),Cat_.data()),"READ");
//   TFile *fTau = new TFile(Form("/data_CMS/cms/ivo/AntiEMVA/Trees/root/V13/tree_AntiEMVA-EleVetoMVAIso%s%s_Tau.root",Discr_.data(),Cat_.data()),"READ"); 
//   TFile *fEle = new TFile(Form("/data_CMS/cms/ivo/AntiEMVA/Trees/root/V13/tree_AntiEMVA-EleVetoMVAIso%s%s_Elec.root",Discr_.data(),Cat_.data()),"READ");
//   TFile *fTau = new TFile(Form("/data_CMS/cms/ivo/AntiEMVANewTraining/root/V1415/tree_AntiEMVA-All%s%s_Tau.root",Discr_.data(),Cat_.data()),"READ"); 
//   TFile *fEle = new TFile(Form("/data_CMS/cms/ivo/AntiEMVANewTraining/root/V1415/tree_AntiEMVA-All%s%s_Elec.root",Discr_.data(),Cat_.data()),"READ");
  TFile *fTau = new TFile(Form("/data_CMS/cms/ivo/AntiEMVANewTraining/root/V17/tree_AntiEMVA-All%s%s_Tau.root",Discr_.data(),Cat_.data()),"READ"); 
  TFile *fEle = new TFile(Form("/data_CMS/cms/ivo/AntiEMVANewTraining/root/V17/tree_AntiEMVA-All%s%s_Elec.root",Discr_.data(),Cat_.data()),"READ");

  TTree *tTau = (TTree*)fTau->Get("tree");
  TTree *tEle = (TTree*)fEle->Get("tree");
 
//   TCut myCut = "Tau_MatchElePassVeto>0.5";
  TCut myCut = Form("%s",Cut_.data());
//   Avoid Crack regions
//   myCut = myCut && TCut("(abs(Tau_EtaAtEcalEntrance)>0.018 && abs(Tau_EtaAtEcalEntrance)<0.423) || (abs(Tau_EtaAtEcalEntrance)>0.461 &&  abs(Tau_EtaAtEcalEntrance)<0.770) || (abs(Tau_EtaAtEcalEntrance)>0.806 &&  abs(Tau_EtaAtEcalEntrance)<1.127) || (abs(Tau_EtaAtEcalEntrance)>1.163 &&  abs(Tau_EtaAtEcalEntrance)<1.460) || (abs(Tau_EtaAtEcalEntrance)>1.558)");

//   if( Sel_.find("Barrel") !=string::npos)  myCut = myCut && TCut("Elec_AbsEta<1.479 && Tau_EtaAtEcalEntrance<1.479 && Tau_EtaAtEcalEntrance>-1.479");
//   if(Sel_.find("Endcap") !=string::npos)  myCut = myCut && TCut("Elec_AbsEta>1.479 && Elec_AbsEta<3.0 && (Tau_EtaAtEcalEntrance>1.479 && Tau_EtaAtEcalEntrance<2.3) || (Tau_EtaAtEcalEntrance>-2.3 && Tau_EtaAtEcalEntrance<-1.479)");
//   if( Sel_.find("Barrel") !=string::npos)  myCut = myCut && TCut("Elec_AbsEta<1.479 && Tau_Eta<1.479 && Tau_Eta>-1.479");
//   if(Sel_.find("Endcap") !=string::npos)  myCut = myCut && TCut("Elec_AbsEta>1.479 && Elec_AbsEta<3.0 && (Tau_Eta>1.479 && Tau_Eta<2.3) || (Tau_Eta>-2.3 && Tau_Eta<-1.479)");

  if(Sel_.find("Barrel") !=string::npos)  myCut = myCut && TCut("Tau_EtaAtEcalEntrance<1.479 && Tau_EtaAtEcalEntrance>-1.479");
  if(Sel_.find("Endcap") !=string::npos)  myCut = myCut && TCut("(Tau_EtaAtEcalEntrance>1.479 && Tau_EtaAtEcalEntrance<2.3) || (Tau_EtaAtEcalEntrance>-2.3 && Tau_EtaAtEcalEntrance<-1.479)");

  ////////////////// compute the weights

  factory->AddSignalTree( tTau );
  factory->AddBackgroundTree( tEle );
//   factory->SetWeightExpression("puWeight");

  factory->PrepareTrainingAndTestTree( myCut,myCut,
				       "nTrain_Signal=0:nTrain_Background=0:nTest_Signal=0:nTest_Background=0:SplitMode=Random:NormMode=NumEvents:!V" );
  
  
//   factory->BookMethod( TMVA::Types::kBDT, "BDT", 
// 		       "!H:!V:NTrees=400:BoostType=AdaBoost:SeparationType=GiniIndex:nCuts=20:PruneMethod=NoPruning" );
  
// Boosted Decision Trees with gradient boosting
  factory->BookMethod( TMVA::Types::kBDT, "BDTG","!H:!V:NTrees=600:BoostType=Grad:Shrinkage=0.30:UseBaggedGrad:GradBaggingFraction=0.6:SeparationType=GiniIndex:nCuts=20:PruneMethod=CostComplexity:PruneStrength=50:NNodesMax=5" );

  factory->TrainAllMethods();
  cout<<"Trained all methods"<<endl;

  factory->TestAllMethods();
  cout<<"Tested all methods"<<endl;

  factory->EvaluateAllMethods();  
  cout<<"Evaluated all methods"<<endl;

  outputFile->Close();

  std::cout << "==> Wrote root file: " << outputFile->GetName() << std::endl;
  std::cout << "==> TMVAClassification is done!" << std::endl;      
  
  delete factory;

}

void TMVAAllClassification(){
//   std::string Cut_ = "Tau_DecayMode>-1 && Tau_DecayMode<5";
//   std::string CutName_ = "OneProng";
 
  std::string Cut_ = "";
  std::string CutName_ = "";

//   TMVAClassification("_NoEleMatch_woGwoGSF","Barrel","",Cut_,CutName_);
//   TMVAClassification("_NoEleMatch_woGwGSF","Barrel","",Cut_,CutName_);
//   TMVAClassification("_NoEleMatch_wGwoGSF","Barrel","",Cut_,CutName_);
//   TMVAClassification("_NoEleMatch_wGwGSF","Barrel","",Cut_,CutName_);
  TMVAClassification("_NoEleMatch_woGwoGSF","Endcap","",Cut_,CutName_);
  TMVAClassification("_NoEleMatch_woGwGSF","Endcap","",Cut_,CutName_);
  TMVAClassification("_NoEleMatch_wGwoGSF","Endcap","",Cut_,CutName_);
  TMVAClassification("_NoEleMatch_wGwGSF","Endcap","",Cut_,CutName_);


//   TMVAClassification("_woGwoGSF","Barrel","",Cut_,CutName_);
//   TMVAClassification("_woGwGSF","Barrel","",Cut_,CutName_);
//   TMVAClassification("_wGwoGSF","Barrel","",Cut_,CutName_);
//   TMVAClassification("_wGwGSF","Barrel","",Cut_,CutName_);
  TMVAClassification("_woGwoGSF","Endcap","",Cut_,CutName_);
  TMVAClassification("_woGwGSF","Endcap","",Cut_,CutName_);
  TMVAClassification("_wGwoGSF","Endcap","",Cut_,CutName_);
  TMVAClassification("_wGwGSF","Endcap","",Cut_,CutName_);

}
