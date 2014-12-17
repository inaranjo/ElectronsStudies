#!/bin/env python

import sys
from ROOT import TFile, TTree


def readFile(fileName):
    file = open(fileName)
    entries = []
    runs = []
    lumis = []
    events = []
    runevents = []
    nentries = None
    for l in file:
        spl = l.split('*')
        if len(spl)>1:
            try:
                entry = int( spl[1] )
                run = int( spl[2] )
                lumi = int( spl[3] )
                event = int( spl[4] )
                entries.append(entry)
                runs.append( run )
                lumis.append( lumi )
                events.append( event )
                runstr = '%s' % run
                lumistr = '%s' % lumi
                evstr = '%s' % event
                runevents.append( runstr + ':' + lumistr + ':' + evstr  )
            except IndexError:
                pass
            except ValueError:
                pass
        else:
            spl = l.split()
            if len(spl)==4 and spl[0]=='==>':
                nentries = int(spl[1])
    assert(nentries==len(entries))
    return entries, runs, lumis, events, runevents
            
from optparse import OptionParser

parser = OptionParser()

## parser.add_option("-c", "--cut", dest="cut",
##                   default='1',
##                   help='cut to define passing events')

## parser.add_option("-t", "--tree", dest="tree",
##                   default='H2TauTauTreeProducerTauMuXCheck',
##                   help='name of the tree')

(options,args) = parser.parse_args()
if len(args)!=2:
    print 'provide 2 input text files'
    sys.exit(1)
file1 = args[0]
file2 = args[1]
en1, run1, lumi1, ev1, runev1 = readFile( file1 )
en2, run2, lumi2, ev2, runev2 = readFile( file2 )

#print runev1
#print runev2


sev1 = set(runev1)
sev2 = set(runev2)

sep_line = '-'*100
import pprint

print file1, '-', file2
print sep_line
pprint.pprint( sev1 - sev2 )


print file2, '-', file1
print sep_line
pprint.pprint( sev2 - sev1 )



