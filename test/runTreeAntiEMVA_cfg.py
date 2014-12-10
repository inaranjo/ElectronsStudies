from PhysicsTools.PatAlgos.patTemplate_cfg import *

process.load('Configuration.StandardSequences.Services_cff')
process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_cff')
process.load('JetMETCorrections.Configuration.DefaultJEC_cff')

postfix           =  "PFlow"
runOnMC           =  True

if runOnMC:
    process.GlobalTag.globaltag = cms.string('START53_V23::All')

else:
    process.GlobalTag.globaltag = cms.string('FT_53_V21_AN4::All')


process.options   = cms.untracked.PSet( wantSummary = cms.untracked.bool(True))
process.MessageLogger.cerr.FwkReport.reportEvery = 10

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )

process.source.fileNames = cms.untracked.vstring(
    'file:/data_CMS/cms/ivo/RootFiles/DYJetsToLL_M-50_TuneZ2Star_8TeV-madgraph-tarball_START53_V7A/FE414F4B-F6D2-E111-A4E9-003048674048.root'
)
process.source.dropDescendantsOfDroppedBranches = cms.untracked.bool(False)
process.source.inputCommands = cms.untracked.vstring( 'keep *', 'drop recoPFTaus_*_*_*' )

################### vertex sequence ####################
#--------------------------------------------------------------------------------
# Select candidates for "the" event vertex.
#
# Selection based on PhysicsTools/PatAlogos/plugins/PATSingleVertexSelector.
# See https://twiki.cern.ch/twiki/bin/view/CMS/SWGuidePhysicsCutParser
# on how to use the cut-string
#
# NOTE: offlinePrimaryVerticesWithBS collection is sorted
#       in order of decreasing sum of Pt of tracks fitted to each vertex
#--------------------------------------------------------------------------------

# CV: ndof >= 4 if using 'offlinePrimaryVertices',
#     ndof >= 7 if using 'offlinePrimaryVerticesWithBS' as input
process.selectedPrimaryVertexQuality = cms.EDFilter("VertexSelector",
                                                    src = cms.InputTag('offlinePrimaryVertices'),
                                                    cut = cms.string("isValid & ndof >= 4 & chi2 > 0 & tracksSize > 0"), # CV: cut >= 4 if using 'offlinePrimaryVertices',
                                                    #         >= 7 if using 'offlinePrimaryVerticesWithBS' as input
                                                    filter = cms.bool(False)                                          
                                                    )

process.selectedPrimaryVertexPosition = cms.EDFilter("VertexSelector",
                                                     src = cms.InputTag('selectedPrimaryVertexQuality'),
                                                     cut = cms.string("abs(z) < 24 & abs(position.Rho) < 2."),
                                                     filter = cms.bool(False)                                           
                                                     )

process.selectedPrimaryVertexHighestPtTrackSum = cms.EDFilter("PATSingleVertexSelector",
                                                              mode = cms.string('firstVertex'),
                                                              vertices = cms.InputTag('selectedPrimaryVertexPosition'),
                                                              filter = cms.bool(False)                                                    
                                                              )
process.selectPrimaryVertex = cms.Sequence(
    process.selectedPrimaryVertexQuality
    * process.selectedPrimaryVertexPosition
    * process.selectedPrimaryVertexHighestPtTrackSum
    )

################### pat specific ####################
from PhysicsTools.PatAlgos.tools.helpers import massSearchReplaceAnyInputTag
from PhysicsTools.PatAlgos.tools.coreTools import *
if not runOnMC:
    removeMCMatching(process,["All"])

removeAllPATObjectsBut(process, ['Taus'])

removeCleaning(process,
               outputInProcess=False)
## #################### tau sequence #######################
process.load("RecoTauTag/Configuration/RecoPFTauTag_cff")
## process.PFTau.remove(process.recoTauClassicShrinkingConeSequence)
## process.PFTau.remove(process.recoTauClassicShrinkingConeMVASequence)
## process.PFTau.remove(process.recoTauHPSTancSequence)
process.produceTauIdMVATrainingNtupleSequence += process.PFTau

# switch to HPS PFTaus (and disable all "cleaning" cuts) 
from PhysicsTools.PatAlgos.tools.tauTools import * 
switchToPFTauHPS(process) 

import PhysicsTools.PatAlgos.tools.helpers as patutils 
removeMCMatching(process, ["All"], outputModules = [])

process.selectedPatTaus.cut = "pt>15 && abs(eta)<2.3 && tauID('decayModeFinding')>0.5 "

########################## path ###############################

process.run = cms.Sequence(
    process.PFTau*
    process.selectPrimaryVertex*
    process.patDefaultSequence   
    )


process.p = cms.Path(process.run)

########################## output ###############################

from PhysicsTools.PatAlgos.patEventContent_cff import patEventContentNoCleaning
process.out.outputCommands = cms.untracked.vstring('drop *',
                                                   *patEventContentNoCleaning ) 
process.TFileService = cms.Service(
    "TFileService",
    fileName = cms.string("AntiEMVA.root")
    )

process.out.SelectEvents = cms.untracked.PSet(
    SelectEvents = cms.vstring('p')
    )

process.out.fileName = cms.untracked.string('patTuplesAntiEMVA.root')

process.outpath = cms.EndPath()

## processDumpFile = open('python.dump', 'w')
## print >> processDumpFile, process.dumpPython()
