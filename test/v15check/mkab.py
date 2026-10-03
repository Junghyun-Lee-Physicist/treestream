#!/usr/bin/env python3
"""a.root: Jet (nJet) + Foo (nFoo) + run; b.root: Jet + run only. Jet_pt[0] = 1000*file + entry."""
import ROOT, numpy as np
for fi, name, foo in [(1, 'a.root', True), (2, 'b.root', False)]:
    f = ROOT.TFile(name, 'RECREATE'); t = ROOT.TTree('Events', 'Events')
    run = np.zeros(1, np.uint32); nj = np.zeros(1, np.int32); pt = np.zeros(8, np.float32)
    nf = np.zeros(1, np.int32); fx = np.zeros(8, np.float32)
    t.Branch('run', run, 'run/i'); t.Branch('nJet', nj, 'nJet/I'); t.Branch('Jet_pt', pt, 'Jet_pt[nJet]/F'); t.Branch('Jet_eta', pt, 'Jet_eta[nJet]/F')
    if foo: t.Branch('nFoo', nf, 'nFoo/I'); t.Branch('Foo_x', fx, 'Foo_x[nFoo]/F'); t.Branch('Foo_y', fx, 'Foo_y[nFoo]/F')
    for i in range(20):
        run[0] = fi; nj[0] = 3; nf[0] = 2
        for j in range(3): pt[j] = 1000 * fi + i
        t.Fill()
    t.Write(); f.Close()
