#!/usr/bin/env python
# ----------------------------------------------------------------------------
#  File:        MyAnalyzer.py
#  Description: Analyzer for simple ROOT ntuples
#  Created:     Tue Dec 16 02:48:44 2025 by mkanalyzer.py v2.0.3 14-Oct-2020
#  Author:      Shakespeare's ghost
# ----------------------------------------------------------------------------
import os, sys, re
import tnm
import ROOT
# ----------------------------------------------------------------------------
# -- Constants, procedures and functions
# ----------------------------------------------------------------------------


# ----------------------------------------------------------------------------
def main():

    cl = ROOT.commandLine()
    
    # Get names of ntuple files to be processed
    filenames = ROOT.fileNames(cl.filelist)

    # Create tree reader
    stream = ROOT.itreestream(filenames, " LuminosityBlocks Runs MetaData ParameterSets")
    if not stream.good():
        error("can't read input files")

    # Create a buffer to receive events from the stream
    # The default is to select all branches.
    # Use second argument to select specific branches
    # Example:
    #   varlist = 'Jet_PT Jet_Eta Jet_Phi'
    #   ev = ROOT.eventBuffer(stream, varlist)
    #
    ev = ROOT.eventBuffer(stream)

    nevents = ev.size()
    print("number of events:", nevents)

    # Create file to store histograms
    of = ROOT.outputFile(cl.outputfilename)

    # ------------------------------------------------------------------------
    # Define histograms
    # ------------------------------------------------------------------------
    ROOT.setStyle()

    # ------------------------------------------------------------------------
    # Loop over events
    # ------------------------------------------------------------------------
    for entry in range(nevents):
        ev.read(entry)
        
    ev.close()
    of.close()
# ----------------------------------------------------------------------------
try:
   main()
except KeyboardInterrupt:
   print("bye!")
