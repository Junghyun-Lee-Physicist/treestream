#include "eventBuffer.h"
#include <cstdio>
// argv[1]: varlist ("" = all). Chain a.root (has Foo) + b.root (no Foo).
// argv[2] = "gone": make b.root unreadable after the buffer is built.
int main(int argc, char** argv){ std::vector<std::string> fs = {"a.root", "b.root"}; itreestream s(fs, "Events");
  eventBuffer ev(s, argv[1]);
  if (argc > 2 && std::string(argv[2]) == "gone") std::rename("b.root", "b_gone.root");
  int stale = 0;
  for (int i = 0; i < ev.size(); ++i) { ev.read(i); float want = (i < 20) ? 1000 + i : 2000 + (i - 20);
    if (ev.Jet_pt.size() != 3 || ev.Jet_pt[0] != want) ++stale; }
  if (argc > 2) std::rename("b_gone.root", "b.root");
  printf("RESULT varlist='%s' entries=%d wrong=%d nJet(last)=%d; exit 0\n", argv[1], ev.size(), stale, ev.nJet); return 0; }
