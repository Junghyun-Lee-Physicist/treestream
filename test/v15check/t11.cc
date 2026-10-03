#include "eventBuffer.h"
int main(int argc, char** argv){ std::vector<std::string> files = {argv[1]}; itreestream stream(files, "Events");
  eventBuffer ev(stream, argv[2]); ev.read(0);
  printf("RESULT varlist='%s' Jet_pt.size()=%zu PuppiMET_pt=%g run=%u\n", argv[2], ev.Jet_pt.size(), ev.PuppiMET_pt, ev.run); return 0; }
