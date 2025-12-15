// Do NOT change. Changes will be lost next time file is generated

#define R__DICTIONARY_FILENAME srcdIpdg_dict
#define R__NO_DEPRECATION

/*******************************************************************/
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#define G__DICTIONARY
#include "ROOT/RConfig.hxx"
#include "TClass.h"
#include "TDictAttributeMap.h"
#include "TInterpreter.h"
#include "TROOT.h"
#include "TBuffer.h"
#include "TMemberInspector.h"
#include "TInterpreter.h"
#include "TVirtualMutex.h"
#include "TError.h"

#ifndef G__ROOT
#define G__ROOT
#endif

#include "RtypesImp.h"
#include "TIsAProxy.h"
#include "TFileMergeInfo.h"
#include <algorithm>
#include "TCollectionProxyInfo.h"
/*******************************************************************/

#include "TDataMember.h"

// Header files passed as explicit arguments
#include "include/pdg.h"

// Header files passed via #pragma extra_include

// The generated code does not explicitly qualify STL entities
namespace std {} using namespace std;

namespace ROOT {
   static TClass *pdg_Dictionary();
   static void pdg_TClassManip(TClass*);
   static void *new_pdg(void *p = nullptr);
   static void *newArray_pdg(Long_t size, void *p);
   static void delete_pdg(void *p);
   static void deleteArray_pdg(void *p);
   static void destruct_pdg(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::pdg*)
   {
      ::pdg *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(::pdg));
      static ::ROOT::TGenericClassInfo 
         instance("pdg", "pdg.h", 25,
                  typeid(::pdg), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &pdg_Dictionary, isa_proxy, 4,
                  sizeof(::pdg) );
      instance.SetNew(&new_pdg);
      instance.SetNewArray(&newArray_pdg);
      instance.SetDelete(&delete_pdg);
      instance.SetDeleteArray(&deleteArray_pdg);
      instance.SetDestructor(&destruct_pdg);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::pdg*)
   {
      return GenerateInitInstanceLocal(static_cast<::pdg*>(nullptr));
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const ::pdg*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *pdg_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal(static_cast<const ::pdg*>(nullptr))->GetClass();
      pdg_TClassManip(theClass);
   return theClass;
   }

   static void pdg_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_pdg(void *p) {
      return  p ? new(p) ::pdg : new ::pdg;
   }
   static void *newArray_pdg(Long_t nElements, void *p) {
      return p ? new(p) ::pdg[nElements] : new ::pdg[nElements];
   }
   // Wrapper around operator delete
   static void delete_pdg(void *p) {
      delete (static_cast<::pdg*>(p));
   }
   static void deleteArray_pdg(void *p) {
      delete [] (static_cast<::pdg*>(p));
   }
   static void destruct_pdg(void *p) {
      typedef ::pdg current_t;
      (static_cast<current_t*>(p))->~current_t();
   }
} // end of namespace ROOT for class ::pdg

namespace {
  void TriggerDictionaryInitialization_pdg_dict_Impl() {
    static const char* headers[] = {
"include/pdg.h",
nullptr
    };
    static const char* includePaths[] = {
"/opt/homebrew/Cellar/root/6.34.08_1/include/root",
"/Users/jhlee/treestream/",
nullptr
    };
    static const char* fwdDeclCode = R"DICTFWDDCLS(
#line 1 "pdg_dict dictionary forward declarations' payload"
#pragma clang diagnostic ignored "-Wkeyword-compat"
#pragma clang diagnostic ignored "-Wignored-attributes"
#pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
extern int __Cling_AutoLoading_Map;
struct __attribute__((annotate("$clingAutoload$include/pdg.h")))  pdg;
)DICTFWDDCLS";
    static const char* payloadCode = R"DICTPAYLOAD(
#line 1 "pdg_dict dictionary payload"


#define _BACKWARD_BACKWARD_WARNING_H
// Inline headers
#include "include/pdg.h"

#undef  _BACKWARD_BACKWARD_WARNING_H
)DICTPAYLOAD";
    static const char* classesHeaders[] = {
"pdg", payloadCode, "@",
nullptr
};
    static bool isInitialized = false;
    if (!isInitialized) {
      TROOT::RegisterModule("pdg_dict",
        headers, includePaths, payloadCode, fwdDeclCode,
        TriggerDictionaryInitialization_pdg_dict_Impl, {}, classesHeaders, /*hasCxxModule*/false);
      isInitialized = true;
    }
  }
  static struct DictInit {
    DictInit() {
      TriggerDictionaryInitialization_pdg_dict_Impl();
    }
  } __TheDictionaryInitializer;
}
void TriggerDictionaryInitialization_pdg_dict() {
  TriggerDictionaryInitialization_pdg_dict_Impl();
}
