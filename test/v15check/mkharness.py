#!/usr/bin/env python3
"""Generate a C++ harness that dumps EVERY member of a generated eventBuffer.h per event.
Usage: mkharness.py eventBuffer.h harness.cc"""
import re, sys
src = open(sys.argv[1]).read().split('\n')
i0 = next(i for i, l in enumerate(src) if '// --- Declare variables' in l)
i1 = next(i for i, l in enumerate(src) if '// --- Structs can be filled' in l)
decl = []
for l in src[i0:i1]:
    m = re.match(r'^  (std::vector<.+>|[A-Za-z_][A-Za-z_0-9 ]*)\t(\w+);$', l)
    if m: decl.append((m.group(1).strip(), m.group(2)))
fills = []
for l in src:
    m = re.match(r'^\s+(\w+)\[i\]\.(\w+)\t= \((\w+)\.size\(\) > i\) \? (?:\(bool\))?(\w+)\[i\] : 0;$', l)
    if m: fills.append((m.group(1), m.group(2), m.group(3)))
objs = sorted(set(o for o, _, _ in fills))
counters = [n for t, n in decl if t == 'int' and re.match(r'^n[A-Z]', n)]
out = []
w = out.append
w('#include "eventBuffer.h"')
w('#include <cstdio>\n#include <cstring>\n#include <cstdlib>\n#include <new>\n#include <type_traits>')
w('template<class T> std::string S(const T& v){ char b[64];')
w('  if constexpr (std::is_same<T,bool>::value) snprintf(b,64,"%d",(int)v);')
w('  else if constexpr (std::is_floating_point<T>::value) snprintf(b,64,"%.17g",(double)v);')
w('  else if constexpr (std::is_signed<T>::value) snprintf(b,64,"%lld",(long long)v);')
w('  else snprintf(b,64,"%llu",(unsigned long long)v); return b; }')
w('template<class T> void D(FILE* f, const char* n, const std::vector<T>& v){ fprintf(f,"%s [",n);')
w('  for(size_t i=0;i<v.size();++i) fprintf(f,"%s%s", i?" ":"", S((T)v[i]).c_str()); fprintf(f,"]\\n"); }')
w('int main(int argc, char** argv){')
w('  if(argc<3){fprintf(stderr,"usage: harness dump.txt file1 [file2 ...]\\n"); return 2;}')
w('  std::vector<std::string> files(argv+2, argv+argc);')
w('  itreestream stream(files, "Events");')
w('  void* mem = malloc(sizeof(eventBuffer)); memset(mem, 0xA5, sizeof(eventBuffer));  // make never-set members visible')
w('  eventBuffer& ev = *new (mem) eventBuffer(stream);')
w('  FILE* f = fopen(argv[1], "w");')
for o in objs: w('  fprintf(f, "PRE_STRUCT %s %%zu\\n", ev.%s.size());' % (o, o))
for c in counters: w('  fprintf(f, "PRE_COUNTER %s %%d\\n", ev.%s);' % (c, c))
w('  int n = ev.size();')
w('  if (getenv("NMAX") && atoi(getenv("NMAX")) < n) n = atoi(getenv("NMAX"));   // first NMAX entries')
w('  for(int e=0; e<n; ++e){')
w('    ev.read(e);')
w('    fprintf(f, "EV %d %d\\n", e, stream.number());')
for t, n in decl:
    if n in counters: continue
    if t.startswith('std::vector<'): w('    D(f, "%s", ev.%s);' % (n, n))
    else: w('    fprintf(f, "%s %%s\\n", S(ev.%s).c_str());' % (n, n))
for c in counters: w('    fprintf(f, "COUNTER %s %%d\\n", ev.%s);' % (c, c))
w('    ev.fillObjects();')
for o in objs:
    w('    { size_t bad=0; for(size_t i=0;i<ev.%s.size();++i){' % o)
    for oo, fld, flat in fills:
        if oo != o: continue
        w('        if(!(ev.%s[i].%s == ((ev.%s.size()>i) ? ev.%s[i] : 0))) ++bad;' % (o, fld, flat, flat))
    w('      } fprintf(f, "STRUCT %s %%zu %%zu\\n", ev.%s.size(), bad); }' % (o, o))
w('  }')
w('  fclose(f); return 0; }')
open(sys.argv[2], 'w').write('\n'.join(out) + '\n')
print('harness: %d members, %d counters, %d struct fields in %d structs' % (len(decl), len(counters), len(fills), len(objs)))
