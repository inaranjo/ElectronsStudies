import FWCore.ParameterSet.Config as cms

process = cms.Process("producePFTauIdEffNtuple2")

process.load('FWCore/MessageService/MessageLogger_cfi')
process.MessageLogger.cerr.FwkReport.reportEvery = 10
process.MessageLogger.cerr.threshold = cms.untracked.string('INFO')
#process.load('Configuration.StandardSequences.Geometry_cff')
process.load('Configuration.Geometry.GeometryIdeal_cff')
process.load('Configuration.StandardSequences.MagneticField_cff')
process.load('Configuration/StandardSequences/FrontierConditions_GlobalTag_cff')
process.GlobalTag.globaltag = cms.string('START53_V10::All')

process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(-1)
)
process.source = cms.Source("PoolSource",
    fileNames = cms.untracked.vstring(
    #'file:/data_CMS/cms/anayak/HTauTauSynchronization/8TeV/53X/VBF_HToTauTau_M-125_8TeV-powheg-pythia6-Summer12_DR53X-PU_S10_START53_V7A-v1-1200542B-D9ED-E111-B708-00237DA1A548.root'
    #'rfio:/dpm/in2p3.fr/home/cms/trivcat/store/mc/Summer12_DR53X/DYJetsToLL_M-50_TuneZ2Star_8TeV-madgraph-tarball/AODSIM/PU_S10_START53_V7A-v1/0000/EC9F2399-CFD1-E111-88ED-001E67396D10.root'
    #'rfio:/dpm/in2p3.fr/home/cms/trivcat/store/mc/Summer12_DR53X/DYJetsToLL_M-50_TuneZ2Star_8TeV-madgraph-tarball/AODSIM/PU_S10_START53_V7A-v1/0000/FE414F4B-F6D2-E111-A4E9-003048674048.root'
    #'file:/data_CMS/cms/ivo/RootFiles/DYJetsToLL_M-50_TuneZ2Star_8TeV-madgraph-tarball_START53_V7A/FE414F4B-F6D2-E111-A4E9-003048674048.root'
    'file:/data_CMS/cms/ivo/RootFiles/DYJetsToLL_M-50_TuneZ2Star_8TeV-madgraph-tarball_START53_V7A/E47D50D9-1DD2-E111-97AD-002481E15522.root'

    #'file:/data1/veelken/CMSSW_5_2_x/skims/simZplusJets_AOD_1_1_ZkM.root'
    #'rfio:/castor/cern.ch/user/v/veelken/CMSSW_5_2_x/skims/ZplusJets/simZplusJets_AOD_1_1_ZkM.root'                        
    )
)

eventsToProcess = cms.untracked.VEventRange(
'1:32648:13048540',
'1:32648:13048543',
'1:32648:13048714',
'1:32810:13113263',
'1:32810:13113286',
'1:105380:42118028',
'1:105380:42118059',
'1:105380:42118072',
'1:105380:42118233',
'1:105380:42118276',
'1:105380:42118288',
'1:105380:42118316',
'1:105380:42118352',
'1:119495:47759639',
'1:119495:47759882',
'1:119495:47759980',
'1:119564:47787215',
'1:33558:13412501',
'1:33558:13412610',
'1:33568:13416418',
'1:33568:13416432',
'1:33568:13416503',
'1:33568:13416518',
'1:33568:13416620',
'1:33568:13416710',
'1:40476:16177243',
'1:40476:16177281',
'1:40476:16177473',
'1:40476:16177509',
'1:40476:16177562',
'1:80069:32001641',
'1:80069:32001702',
'1:80069:32001771',
'1:80069:32001836',
'1:80069:32001964',
'1:80071:32002745',
'1:49057:19606851',
'1:49057:19606999',
'1:49057:19607118',
'1:49686:19858555',
'1:49686:19858564',
'1:49686:19858718',
'1:49686:19858768',
'1:49686:19858775',
'1:97592:39005382',
'1:97592:39005419',
'1:97592:39005513',
'1:97773:39077620',
'1:97773:39077652',
'1:97773:39077677',
'1:97773:39077780',
'1:97802:39089231',
'1:97802:39089377',
'1:97802:39089461',
'1:97802:39089535',
'1:97802:39089546',
'1:80075:32004064',
'1:80077:32004809',
'1:80077:32004847',
'1:80077:32004904',
'1:80082:32006846',
'1:80082:32006918',
'1:80082:32006968',
'1:80082:32007100',
'1:80082:32007197',
'1:80098:32013212',
'1:80098:32013284',
'1:80098:32013519',
'1:80098:32013586',
'1:80098:32013596',
'1:97967:39155356',
'1:97967:39155591',
'1:98011:39172944',
'1:98011:39173114',
'1:98016:39175037',
'1:98181:39240985',
'1:98181:39241007',
'1:98181:39241164',
'1:98231:39260912',
'1:98231:39260971',
'1:98231:39261195',
'1:98210:39252411',
'1:98210:39252492',
'1:98210:39252495',
'1:98210:39252532',
'1:98349:39308287',
'1:98349:39308324',
'1:98394:39326039',
'1:98394:39326055',
'1:98394:39326097',
'1:98394:39326255',
'1:98394:39326256',
'1:98408:39331636',
'1:98408:39331657'
)

   
process.producePFTauIdEffNtuple2Sequence = cms.Sequence()

#--------------------------------------------------------------------------------
# print-out of generator level information
##process.load("SimGeneral.HepPDTESSource.pythiapdt_cfi")
##process.printGenParticleList = cms.EDAnalyzer("ParticleListDrawer",
##    src = cms.InputTag("genParticles"),
##    maxEventsToPrint = cms.untracked.int32(10)
##)
##process.producePFTauIdEffNtuple2Sequence += process.printGenParticleList
#--------------------------------------------------------------------------------


#--------------------------------------------------------------------------------
# rerun tau reconstruction with latest tags

process.load("RecoTauTag/Configuration/RecoPFTauTag_cff")
process.producePFTauIdEffNtuple2Sequence += process.PFTau
#--------------------------------------------------------------------------------


####Testing
## process.selectedTaus = cms.EDFilter("PFTauSelector",
##    src = cms.InputTag('hpsPFTauProducer'),
##    discriminators = cms.VPSet(
##        cms.PSet(
##            discriminator = cms.InputTag('hpsPFTauDiscriminationByDecayModeFinding'),
##            selectionCut = cms.double(0.5)
##        ),
##        cms.PSet(
##            discriminator = cms.InputTag('hpsPFTauDiscriminationByLooseIsolationMVA'),
##            selectionCut = cms.double(0.5)
##        )                        
##    ),
##    cut = cms.string("pt > 20. & abs(eta) < 2.3 && signalPFChargedHadrCands().size()==3")                        
## )
## process.producePFTauIdEffNtuple2Sequence += process.selectedTaus
## #--------------------------------------------------------------------------------
## # run antiemva3 discriminator on selected taus
## from RecoTauTag.RecoTau.PFRecoTauDiscriminationAgainstElectronMVA3_cfi import *
## process.AntiElectronMVA3 = pfRecoTauDiscriminationAgainstElectronMVA3.clone(
##     PFTauProducer = cms.InputTag('selectedTaus'),
##     Prediscriminants = cms.PSet(
##     BooleanOperator = cms.string('and')
##     )
##     )
## #delattr(process.AntiElectronMVA3,"Prediscriminants")
## process.producePFTauIdEffNtuple2Sequence += process.AntiElectronMVA3
####Testing



#--------------------------------------------------------------------------------
# select "good" reconstructed vertices
process.load("TauAnalysis/RecoTools/recoVertexSelection_cff")

process.producePFTauIdEffNtuple2Sequence += process.selectPrimaryVertex
#--------------------------------------------------------------------------------


#--------------------------------------------------------------------------------
# compute event weights for pile-up reweighting
# (Summer'12 MC to 2012 run A data)

from TauAnalysis.RecoTools.vertexMultiplicityReweight_cfi import vertexMultiplicityReweight
process.vertexMultiplicityReweight3d2012RunABCD = vertexMultiplicityReweight.clone(
    #inputFileName = cms.FileInPath("TauAnalysis/RecoTools/data/expPUpoissonMean_runs190456to193557_Mu17_Mu8_v16.root"),
    #inputFileName = cms.FileInPath("TauAnalysis/RecoTools/data/expPUpoissonMean_runs190456to202016_Mu17_Mu8.root"),
    inputFileName = cms.FileInPath("TauAnalysis/RecoTools/data/expPUpoissonDist_runs190456to208686_Mu17_Mu8.root"),
    type = cms.string("gen3d"),
    mcPeriod = cms.string("Summer12_S10")
)
process.producePFTauIdEffNtuple2Sequence += process.vertexMultiplicityReweight3d2012RunABCD
#--------------------------------------------------------------------------------

#--------------------------------------------------------------------------------
# produce PAT-tuple
process.load("PhysicsTools/PatAlgos/patSequences_cff")

# configure pat::Jet production
# (enable L2L3Residual corrections in case running on Data)
jetCorrections = [ 'L1FastJet', 'L2Relative', 'L3Absolute', 'L2L3Residual' ]
from PhysicsTools.PatAlgos.tools.jetTools import *
switchJetCollection(
   process,
   cms.InputTag('ak5PFJets'),
   doJTA = True,
   doBTagging = True,
   jetCorrLabel = ( 'AK5PF', cms.vstring(jetCorrections) ),
   doType1MET = False,
   doJetID = True,
   jetIdLabel = "ak5",
   outputModules = []
)

# switch to HPS PFTaus (and disable all "cleaning" cuts)
from PhysicsTools.PatAlgos.tools.tauTools import *
switchToPFTauHPS(process)
   
process.producePFTauIdEffNtuple2Sequence += process.patDefaultSequence
#--------------------------------------------------------------------------------
simpleCutsWP95 = "(userFloat('nHits')<=999 "+\
                 "&& ( (isEB && userFloat('sihih')<0.01 && userFloat('dPhi')<0.8 "+\
                 "&&            userFloat('dEta')<0.007 && userFloat('HoE')<0.15) "+\
                 "||   "+\
                 "     (isEE && userFloat('sihih')<0.03 && userFloat('dPhi')<0.7 "+\
                 "&&            userFloat('dEta')<0.01 && userFloat('HoE')<999) ))"

process.elecVeto  = cms.EDFilter(
   "PATElectronSelector",
   src = cms.InputTag("selectedPatElectrons"),
   cut = cms.string(simpleCutsWP95+" && pt>15 && abs(eta)<2.5 && userFloat('PFRelIsoDB04v3')<0.3 && abs(userFloat('dzWrtPV'))<0.2"),
   filter = cms.bool(False)
   )
process.producePFTauIdEffNtuple2Sequence += process.elecVeto


process.pfTauIdEffNtuple2Producer = cms.EDProducer("PFTauIdEffNtupleProducer2",
   srcGenParticles = cms.InputTag('genParticles'),
   srcRecTaus = cms.InputTag('patTaus'),
   srcRecVetoElectrons = cms.InputTag("elecVeto"),
   srcVertices = cms.InputTag('selectedPrimaryVertexPosition'),
   srcWeights = cms.VInputTag('vertexMultiplicityReweight3d2012RunABCD')                                                  
)
process.producePFTauIdEffNtuple2Sequence += process.pfTauIdEffNtuple2Producer

process.p = cms.Path(process.producePFTauIdEffNtuple2Sequence)

process.TFileService = cms.Service("TFileService",
   fileName = cms.string("pfTauIdEffNtuple2.root")
)

#processDumpFile = open('producePFTauIdEffNtuple2.dump', 'w')
#print >> processDumpFile, process.dumpPython()




