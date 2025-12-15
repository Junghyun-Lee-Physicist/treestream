// Do NOT change. Changes will be lost next time file is generated

#define R__DICTIONARY_FILENAME srcdItestme_dict
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
#include "include/testme.h"

// Header files passed via #pragma extra_include

// The generated code does not explicitly qualify STL entities
namespace std {} using namespace std;

namespace ROOT {
   static TClass *testme_Dictionary();
   static void testme_TClassManip(TClass*);
   static void *new_testme(void *p = nullptr);
   static void *newArray_testme(Long_t size, void *p);
   static void delete_testme(void *p);
   static void deleteArray_testme(void *p);
   static void destruct_testme(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::testme*)
   {
      ::testme *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(::testme));
      static ::ROOT::TGenericClassInfo 
         instance("testme", "testme.h", 11,
                  typeid(::testme), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &testme_Dictionary, isa_proxy, 4,
                  sizeof(::testme) );
      instance.SetNew(&new_testme);
      instance.SetNewArray(&newArray_testme);
      instance.SetDelete(&delete_testme);
      instance.SetDeleteArray(&deleteArray_testme);
      instance.SetDestructor(&destruct_testme);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::testme*)
   {
      return GenerateInitInstanceLocal(static_cast<::testme*>(nullptr));
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const ::testme*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *testme_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal(static_cast<const ::testme*>(nullptr))->GetClass();
      testme_TClassManip(theClass);
   return theClass;
   }

   static void testme_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_testme(void *p) {
      return  p ? new(p) ::testme : new ::testme;
   }
   static void *newArray_testme(Long_t nElements, void *p) {
      return p ? new(p) ::testme[nElements] : new ::testme[nElements];
   }
   // Wrapper around operator delete
   static void delete_testme(void *p) {
      delete (static_cast<::testme*>(p));
   }
   static void deleteArray_testme(void *p) {
      delete [] (static_cast<::testme*>(p));
   }
   static void destruct_testme(void *p) {
      typedef ::testme current_t;
      (static_cast<current_t*>(p))->~current_t();
   }
} // end of namespace ROOT for class ::testme

namespace {
  void TriggerDictionaryInitialization_testme_dict_Impl() {
    static const char* headers[] = {
"include/testme.h",
nullptr
    };
    static const char* includePaths[] = {
"/opt/homebrew/Cellar/root/6.34.08_1/include/root",
"/Users/jhlee/treestream/",
nullptr
    };
    static const char* fwdDeclCode = R"DICTFWDDCLS(
#line 1 "testme_dict dictionary forward declarations' payload"
#pragma clang diagnostic ignored "-Wkeyword-compat"
#pragma clang diagnostic ignored "-Wignored-attributes"
#pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
extern int __Cling_AutoLoading_Map;
struct __attribute__((annotate("$clingAutoload$include/testme.h")))  testme;
)DICTFWDDCLS";
    static const char* payloadCode = R"DICTPAYLOAD(
#line 1 "testme_dict dictionary payload"


#define _BACKWARD_BACKWARD_WARNING_H
// Inline headers
#include "include/testme.h"

#undef  _BACKWARD_BACKWARD_WARNING_H
)DICTPAYLOAD";
    static const char* classesHeaders[] = {
"testme", payloadCode, "@",
nullptr
};
    static bool isInitialized = false;
    if (!isInitialized) {
      TROOT::RegisterModule("testme_dict",
        headers, includePaths, payloadCode, fwdDeclCode,
        TriggerDictionaryInitialization_testme_dict_Impl, {}, classesHeaders, /*hasCxxModule*/false);
      isInitialized = true;
    }
  }
  static struct DictInit {
    DictInit() {
      TriggerDictionaryInitialization_testme_dict_Impl();
    }
  } __TheDictionaryInitializer;
}
void TriggerDictionaryInitialization_testme_dict() {
  TriggerDictionaryInitialization_testme_dict_Impl();
}
