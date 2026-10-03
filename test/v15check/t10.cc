#include "eventBuffer.h"
// reads c_bad.root: entries 200-299 of Jet_pt are in a corrupted basket.
// unpatched treestream: prints stale values and exits 0; patched: stops at entry 200 (exit 1).
int main(int argc,char**argv){ std::vector<std::string> fs={argv[1]}; itreestream s(fs,"Events"); eventBuffer ev(s);
 int bad=0, last=-1;
 for(int i=0;i<ev.size();++i){ ev.read(i); float want=100.0f+i;
   if(ev.Jet_pt.size()!=5 || ev.Jet_pt[0]!=want){ if(bad<2) printf("entry %d: Jet_pt[0]=%g (want %g)\n", i, ev.Jet_pt.size()?ev.Jet_pt[0]:-1., want); ++bad; last=i; } }
 printf("RESULT bad entries: %d (last %d); exit 0\n", bad, last); return 0; }
