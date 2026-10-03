#!/usr/bin/env python3
"""c.root: 500 entries, Jet_pt[nJet] = 100+entry (compressible); c_bad.root: basket 2 of Jet_pt (entries 200-299) corrupted."""
import ROOT, numpy as np
f = ROOT.TFile('c.root', 'RECREATE'); t = ROOT.TTree('Events', 'Events'); t.SetAutoFlush(100)
n = np.zeros(1, np.int32); pt = np.zeros(20, np.float32); ev = np.zeros(1, np.uint64)
t.Branch('event', ev, 'event/l'); t.Branch('nJet', n, 'nJet/I'); t.Branch('Jet_pt', pt, 'Jet_pt[nJet]/F'); t.Branch('Jet_eta', pt, 'Jet_eta[nJet]/F')
for i in range(500):
    ev[0] = i; n[0] = 5
    for j in range(5): pt[j] = 100.0 + i
    t.Fill()
t.Write(); f.Close()
f = ROOT.TFile('c.root'); br = f.Get('Events').GetBranch('Jet_pt')
seek = br.GetBasketSeek(2); nb = br.GetBasketBytes()[2]; f.Close()
raw = bytearray(open('c.root', 'rb').read())
for i in range(seek + nb - 40, seek + nb - 8): raw[i] ^= 0x5A
open('c_bad.root', 'wb').write(raw)
