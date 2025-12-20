#!/usr/bin/env python3
import ROOT
import array
import os

def create_ntuple(filename, scenario):
    """
    Scenarios:
    1. 'full_mc': Has nElectron, pt, eta, genPartIdx
    2. 'data_missing': Has nElectron, pt, eta. MISSING genPartIdx
    3. 'empty': Has branches but 0 events have objects
    """
    print(f"Generating {filename} [{scenario}]...")
    f = ROOT.TFile(filename, "RECREATE")
    tree = ROOT.TTree("Events", "Test Tree")

    # Arrays for branches
    maxn = 50
    nElectron = array.array('i', [0])
    
    # Vectors (Using standard vectors for simplicity in generation)
    # Note: treestream reads them fine whether they are arrays or vectors
    # We will use std::vector to match modern standards
    v_pt = ROOT.std.vector('float')()
    v_eta = ROOT.std.vector('float')()
    v_gen = ROOT.std.vector('float')() # Treating index as float for simplicity or int

    tree.Branch("nElectron", nElectron, "nElectron/I")
    tree.Branch("Electron_pt", v_pt)
    tree.Branch("Electron_eta", v_eta)

    # Only add genPartIdx for MC scenario
    if scenario == 'full_mc':
        tree.Branch("Electron_genPartIdx", v_gen)

    # Fill Events
    for i in range(5):
        nElectron[0] = 0
        v_pt.clear()
        v_eta.clear()
        v_gen.clear()

        # Create objects (except for 'empty' scenario)
        if scenario != 'empty':
            num_objs = i + 1 # 1, 2, 3... objects
            nElectron[0] = num_objs
            
            for j in range(num_objs):
                v_pt.push_back(10.0 + j)
                v_eta.push_back(0.5 * j)
                if scenario == 'full_mc':
                    v_gen.push_back(j + 100) # Dummy Index

        tree.Fill()

    tree.Write()
    f.Close()

if __name__ == "__main__":
    create_ntuple("test_mc.root", "full_mc")
    create_ntuple("test_data.root", "data_missing")
    print("Done. Now run your analyzer on these files.")