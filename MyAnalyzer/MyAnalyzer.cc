//---------------------------------------------------------------------------
// File:        MyAnalyzer.cc
// Description: Analyzer for simple ntuples, such as those created by
//              TheNtupleMaker
// Created:     Tue Dec 16 02:48:44 2025 by mkanalyzer.py v2.0.3 14-Oct-2020
// Author:      Shakespeare's ghost
//----------------------------------------------------------------------------
#include "tnm.h"
using namespace std;
//----------------------------------------------------------------------------
int main(int argc, char** argv)
{
  // If you want canvases to be visible during program execution, just
  // uncomment the line below
  //TApplication app("MyAnalyzer", &argc, argv);

  // Get command line arguments
  commandLine cl(argc, argv);
    
  // Get names of ntuple files to be processed
  vector<string> filenames = fileNames(cl.filelist);

  // Create tree reader
  itreestream stream(filenames, " LuminosityBlocks Runs MetaData ParameterSets");
  if ( !stream.good() ) error("can't read root input files");

  // Create a buffer to receive events from the stream
  // The default is to select all branches
  // Use second argument to select specific branches
  // Example:
  //   varlist = 'Jet_PT Jet_Eta Jet_Phi'
  //   ev = eventBuffer(stream, varlist)

  eventBuffer ev(stream);
  
  int nevents = ev.size();
  cout << "number of events: " << nevents << endl;

  // Create output file for histograms; see notes in header 
  outputFile of(cl.outputfilename);

  // -------------------------------------------------------------------------
  // Define histograms
  // -------------------------------------------------------------------------
  //setStyle();

  // -------------------------------------------------------------------------
  // Loop over events
  // -------------------------------------------------------------------------
  
  for(int entry=0; entry < nevents; entry++)
    {
      // read an event into event buffer
      ev.read(entry);

    }
    
  ev.close();
  of.close();
  return 0;
}
