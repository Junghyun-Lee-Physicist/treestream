// Do NOT change. Changes will be lost next time file is generated

#define R__DICTIONARY_FILENAME srcdItreestream_dict
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
#include "include/treestream.h"

// Header files passed via #pragma extra_include

// The generated code does not explicitly qualify STL entities
namespace std {} using namespace std;

namespace ROOT {
   static TClass *itreestream_Dictionary();
   static void itreestream_TClassManip(TClass*);
   static void *new_itreestream(void *p = nullptr);
   static void *newArray_itreestream(Long_t size, void *p);
   static void delete_itreestream(void *p);
   static void deleteArray_itreestream(void *p);
   static void destruct_itreestream(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::itreestream*)
   {
      ::itreestream *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(::itreestream));
      static ::ROOT::TGenericClassInfo 
         instance("itreestream", "treestream.h", 159,
                  typeid(::itreestream), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &itreestream_Dictionary, isa_proxy, 4,
                  sizeof(::itreestream) );
      instance.SetNew(&new_itreestream);
      instance.SetNewArray(&newArray_itreestream);
      instance.SetDelete(&delete_itreestream);
      instance.SetDeleteArray(&deleteArray_itreestream);
      instance.SetDestructor(&destruct_itreestream);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::itreestream*)
   {
      return GenerateInitInstanceLocal(static_cast<::itreestream*>(nullptr));
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const ::itreestream*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *itreestream_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal(static_cast<const ::itreestream*>(nullptr))->GetClass();
      itreestream_TClassManip(theClass);
   return theClass;
   }

   static void itreestream_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   static TClass *otreestream_Dictionary();
   static void otreestream_TClassManip(TClass*);
   static void *new_otreestream(void *p = nullptr);
   static void *newArray_otreestream(Long_t size, void *p);
   static void delete_otreestream(void *p);
   static void deleteArray_otreestream(void *p);
   static void destruct_otreestream(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::otreestream*)
   {
      ::otreestream *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(::otreestream));
      static ::ROOT::TGenericClassInfo 
         instance("otreestream", "treestream.h", 404,
                  typeid(::otreestream), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &otreestream_Dictionary, isa_proxy, 4,
                  sizeof(::otreestream) );
      instance.SetNew(&new_otreestream);
      instance.SetNewArray(&newArray_otreestream);
      instance.SetDelete(&delete_otreestream);
      instance.SetDeleteArray(&deleteArray_otreestream);
      instance.SetDestructor(&destruct_otreestream);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::otreestream*)
   {
      return GenerateInitInstanceLocal(static_cast<::otreestream*>(nullptr));
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const ::otreestream*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *otreestream_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal(static_cast<const ::otreestream*>(nullptr))->GetClass();
      otreestream_TClassManip(theClass);
   return theClass;
   }

   static void otreestream_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_itreestream(void *p) {
      return  p ? new(p) ::itreestream : new ::itreestream;
   }
   static void *newArray_itreestream(Long_t nElements, void *p) {
      return p ? new(p) ::itreestream[nElements] : new ::itreestream[nElements];
   }
   // Wrapper around operator delete
   static void delete_itreestream(void *p) {
      delete (static_cast<::itreestream*>(p));
   }
   static void deleteArray_itreestream(void *p) {
      delete [] (static_cast<::itreestream*>(p));
   }
   static void destruct_itreestream(void *p) {
      typedef ::itreestream current_t;
      (static_cast<current_t*>(p))->~current_t();
   }
} // end of namespace ROOT for class ::itreestream

namespace ROOT {
   // Wrappers around operator new
   static void *new_otreestream(void *p) {
      return  p ? new(p) ::otreestream : new ::otreestream;
   }
   static void *newArray_otreestream(Long_t nElements, void *p) {
      return p ? new(p) ::otreestream[nElements] : new ::otreestream[nElements];
   }
   // Wrapper around operator delete
   static void delete_otreestream(void *p) {
      delete (static_cast<::otreestream*>(p));
   }
   static void deleteArray_otreestream(void *p) {
      delete [] (static_cast<::otreestream*>(p));
   }
   static void destruct_otreestream(void *p) {
      typedef ::otreestream current_t;
      (static_cast<current_t*>(p))->~current_t();
   }
} // end of namespace ROOT for class ::otreestream

namespace ROOT {
   static TClass *vectorlEvectorlEunsignedsPlonggRsPgR_Dictionary();
   static void vectorlEvectorlEunsignedsPlonggRsPgR_TClassManip(TClass*);
   static void *new_vectorlEvectorlEunsignedsPlonggRsPgR(void *p = nullptr);
   static void *newArray_vectorlEvectorlEunsignedsPlonggRsPgR(Long_t size, void *p);
   static void delete_vectorlEvectorlEunsignedsPlonggRsPgR(void *p);
   static void deleteArray_vectorlEvectorlEunsignedsPlonggRsPgR(void *p);
   static void destruct_vectorlEvectorlEunsignedsPlonggRsPgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const vector<vector<unsigned long> >*)
   {
      vector<vector<unsigned long> > *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(vector<vector<unsigned long> >));
      static ::ROOT::TGenericClassInfo 
         instance("vector<vector<unsigned long> >", -2, "vector", 389,
                  typeid(vector<vector<unsigned long> >), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &vectorlEvectorlEunsignedsPlonggRsPgR_Dictionary, isa_proxy, 4,
                  sizeof(vector<vector<unsigned long> >) );
      instance.SetNew(&new_vectorlEvectorlEunsignedsPlonggRsPgR);
      instance.SetNewArray(&newArray_vectorlEvectorlEunsignedsPlonggRsPgR);
      instance.SetDelete(&delete_vectorlEvectorlEunsignedsPlonggRsPgR);
      instance.SetDeleteArray(&deleteArray_vectorlEvectorlEunsignedsPlonggRsPgR);
      instance.SetDestructor(&destruct_vectorlEvectorlEunsignedsPlonggRsPgR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::Pushback< vector<vector<unsigned long> > >()));

      instance.AdoptAlternate(::ROOT::AddClassAlternate("vector<vector<unsigned long> >","std::__1::vector<std::__1::vector<unsigned long, std::__1::allocator<unsigned long>>, std::__1::allocator<std::__1::vector<unsigned long, std::__1::allocator<unsigned long>>>>"));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const vector<vector<unsigned long> >*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *vectorlEvectorlEunsignedsPlonggRsPgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal(static_cast<const vector<vector<unsigned long> >*>(nullptr))->GetClass();
      vectorlEvectorlEunsignedsPlonggRsPgR_TClassManip(theClass);
   return theClass;
   }

   static void vectorlEvectorlEunsignedsPlonggRsPgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_vectorlEvectorlEunsignedsPlonggRsPgR(void *p) {
      return  p ? ::new(static_cast<::ROOT::Internal::TOperatorNewHelper*>(p)) vector<vector<unsigned long> > : new vector<vector<unsigned long> >;
   }
   static void *newArray_vectorlEvectorlEunsignedsPlonggRsPgR(Long_t nElements, void *p) {
      return p ? ::new(static_cast<::ROOT::Internal::TOperatorNewHelper*>(p)) vector<vector<unsigned long> >[nElements] : new vector<vector<unsigned long> >[nElements];
   }
   // Wrapper around operator delete
   static void delete_vectorlEvectorlEunsignedsPlonggRsPgR(void *p) {
      delete (static_cast<vector<vector<unsigned long> >*>(p));
   }
   static void deleteArray_vectorlEvectorlEunsignedsPlonggRsPgR(void *p) {
      delete [] (static_cast<vector<vector<unsigned long> >*>(p));
   }
   static void destruct_vectorlEvectorlEunsignedsPlonggRsPgR(void *p) {
      typedef vector<vector<unsigned long> > current_t;
      (static_cast<current_t*>(p))->~current_t();
   }
} // end of namespace ROOT for class vector<vector<unsigned long> >

namespace ROOT {
   static TClass *vectorlEvectorlEunsignedsPintgRsPgR_Dictionary();
   static void vectorlEvectorlEunsignedsPintgRsPgR_TClassManip(TClass*);
   static void *new_vectorlEvectorlEunsignedsPintgRsPgR(void *p = nullptr);
   static void *newArray_vectorlEvectorlEunsignedsPintgRsPgR(Long_t size, void *p);
   static void delete_vectorlEvectorlEunsignedsPintgRsPgR(void *p);
   static void deleteArray_vectorlEvectorlEunsignedsPintgRsPgR(void *p);
   static void destruct_vectorlEvectorlEunsignedsPintgRsPgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const vector<vector<unsigned int> >*)
   {
      vector<vector<unsigned int> > *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(vector<vector<unsigned int> >));
      static ::ROOT::TGenericClassInfo 
         instance("vector<vector<unsigned int> >", -2, "vector", 389,
                  typeid(vector<vector<unsigned int> >), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &vectorlEvectorlEunsignedsPintgRsPgR_Dictionary, isa_proxy, 4,
                  sizeof(vector<vector<unsigned int> >) );
      instance.SetNew(&new_vectorlEvectorlEunsignedsPintgRsPgR);
      instance.SetNewArray(&newArray_vectorlEvectorlEunsignedsPintgRsPgR);
      instance.SetDelete(&delete_vectorlEvectorlEunsignedsPintgRsPgR);
      instance.SetDeleteArray(&deleteArray_vectorlEvectorlEunsignedsPintgRsPgR);
      instance.SetDestructor(&destruct_vectorlEvectorlEunsignedsPintgRsPgR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::Pushback< vector<vector<unsigned int> > >()));

      instance.AdoptAlternate(::ROOT::AddClassAlternate("vector<vector<unsigned int> >","std::__1::vector<std::__1::vector<unsigned int, std::__1::allocator<unsigned int>>, std::__1::allocator<std::__1::vector<unsigned int, std::__1::allocator<unsigned int>>>>"));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const vector<vector<unsigned int> >*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *vectorlEvectorlEunsignedsPintgRsPgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal(static_cast<const vector<vector<unsigned int> >*>(nullptr))->GetClass();
      vectorlEvectorlEunsignedsPintgRsPgR_TClassManip(theClass);
   return theClass;
   }

   static void vectorlEvectorlEunsignedsPintgRsPgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_vectorlEvectorlEunsignedsPintgRsPgR(void *p) {
      return  p ? ::new(static_cast<::ROOT::Internal::TOperatorNewHelper*>(p)) vector<vector<unsigned int> > : new vector<vector<unsigned int> >;
   }
   static void *newArray_vectorlEvectorlEunsignedsPintgRsPgR(Long_t nElements, void *p) {
      return p ? ::new(static_cast<::ROOT::Internal::TOperatorNewHelper*>(p)) vector<vector<unsigned int> >[nElements] : new vector<vector<unsigned int> >[nElements];
   }
   // Wrapper around operator delete
   static void delete_vectorlEvectorlEunsignedsPintgRsPgR(void *p) {
      delete (static_cast<vector<vector<unsigned int> >*>(p));
   }
   static void deleteArray_vectorlEvectorlEunsignedsPintgRsPgR(void *p) {
      delete [] (static_cast<vector<vector<unsigned int> >*>(p));
   }
   static void destruct_vectorlEvectorlEunsignedsPintgRsPgR(void *p) {
      typedef vector<vector<unsigned int> > current_t;
      (static_cast<current_t*>(p))->~current_t();
   }
} // end of namespace ROOT for class vector<vector<unsigned int> >

namespace ROOT {
   static TClass *vectorlEvectorlElonggRsPgR_Dictionary();
   static void vectorlEvectorlElonggRsPgR_TClassManip(TClass*);
   static void *new_vectorlEvectorlElonggRsPgR(void *p = nullptr);
   static void *newArray_vectorlEvectorlElonggRsPgR(Long_t size, void *p);
   static void delete_vectorlEvectorlElonggRsPgR(void *p);
   static void deleteArray_vectorlEvectorlElonggRsPgR(void *p);
   static void destruct_vectorlEvectorlElonggRsPgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const vector<vector<long> >*)
   {
      vector<vector<long> > *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(vector<vector<long> >));
      static ::ROOT::TGenericClassInfo 
         instance("vector<vector<long> >", -2, "vector", 389,
                  typeid(vector<vector<long> >), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &vectorlEvectorlElonggRsPgR_Dictionary, isa_proxy, 4,
                  sizeof(vector<vector<long> >) );
      instance.SetNew(&new_vectorlEvectorlElonggRsPgR);
      instance.SetNewArray(&newArray_vectorlEvectorlElonggRsPgR);
      instance.SetDelete(&delete_vectorlEvectorlElonggRsPgR);
      instance.SetDeleteArray(&deleteArray_vectorlEvectorlElonggRsPgR);
      instance.SetDestructor(&destruct_vectorlEvectorlElonggRsPgR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::Pushback< vector<vector<long> > >()));

      instance.AdoptAlternate(::ROOT::AddClassAlternate("vector<vector<long> >","std::__1::vector<std::__1::vector<long, std::__1::allocator<long>>, std::__1::allocator<std::__1::vector<long, std::__1::allocator<long>>>>"));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const vector<vector<long> >*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *vectorlEvectorlElonggRsPgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal(static_cast<const vector<vector<long> >*>(nullptr))->GetClass();
      vectorlEvectorlElonggRsPgR_TClassManip(theClass);
   return theClass;
   }

   static void vectorlEvectorlElonggRsPgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_vectorlEvectorlElonggRsPgR(void *p) {
      return  p ? ::new(static_cast<::ROOT::Internal::TOperatorNewHelper*>(p)) vector<vector<long> > : new vector<vector<long> >;
   }
   static void *newArray_vectorlEvectorlElonggRsPgR(Long_t nElements, void *p) {
      return p ? ::new(static_cast<::ROOT::Internal::TOperatorNewHelper*>(p)) vector<vector<long> >[nElements] : new vector<vector<long> >[nElements];
   }
   // Wrapper around operator delete
   static void delete_vectorlEvectorlElonggRsPgR(void *p) {
      delete (static_cast<vector<vector<long> >*>(p));
   }
   static void deleteArray_vectorlEvectorlElonggRsPgR(void *p) {
      delete [] (static_cast<vector<vector<long> >*>(p));
   }
   static void destruct_vectorlEvectorlElonggRsPgR(void *p) {
      typedef vector<vector<long> > current_t;
      (static_cast<current_t*>(p))->~current_t();
   }
} // end of namespace ROOT for class vector<vector<long> >

namespace ROOT {
   static TClass *vectorlEvectorlEintgRsPgR_Dictionary();
   static void vectorlEvectorlEintgRsPgR_TClassManip(TClass*);
   static void *new_vectorlEvectorlEintgRsPgR(void *p = nullptr);
   static void *newArray_vectorlEvectorlEintgRsPgR(Long_t size, void *p);
   static void delete_vectorlEvectorlEintgRsPgR(void *p);
   static void deleteArray_vectorlEvectorlEintgRsPgR(void *p);
   static void destruct_vectorlEvectorlEintgRsPgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const vector<vector<int> >*)
   {
      vector<vector<int> > *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(vector<vector<int> >));
      static ::ROOT::TGenericClassInfo 
         instance("vector<vector<int> >", -2, "vector", 389,
                  typeid(vector<vector<int> >), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &vectorlEvectorlEintgRsPgR_Dictionary, isa_proxy, 4,
                  sizeof(vector<vector<int> >) );
      instance.SetNew(&new_vectorlEvectorlEintgRsPgR);
      instance.SetNewArray(&newArray_vectorlEvectorlEintgRsPgR);
      instance.SetDelete(&delete_vectorlEvectorlEintgRsPgR);
      instance.SetDeleteArray(&deleteArray_vectorlEvectorlEintgRsPgR);
      instance.SetDestructor(&destruct_vectorlEvectorlEintgRsPgR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::Pushback< vector<vector<int> > >()));

      instance.AdoptAlternate(::ROOT::AddClassAlternate("vector<vector<int> >","std::__1::vector<std::__1::vector<int, std::__1::allocator<int>>, std::__1::allocator<std::__1::vector<int, std::__1::allocator<int>>>>"));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const vector<vector<int> >*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *vectorlEvectorlEintgRsPgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal(static_cast<const vector<vector<int> >*>(nullptr))->GetClass();
      vectorlEvectorlEintgRsPgR_TClassManip(theClass);
   return theClass;
   }

   static void vectorlEvectorlEintgRsPgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_vectorlEvectorlEintgRsPgR(void *p) {
      return  p ? ::new(static_cast<::ROOT::Internal::TOperatorNewHelper*>(p)) vector<vector<int> > : new vector<vector<int> >;
   }
   static void *newArray_vectorlEvectorlEintgRsPgR(Long_t nElements, void *p) {
      return p ? ::new(static_cast<::ROOT::Internal::TOperatorNewHelper*>(p)) vector<vector<int> >[nElements] : new vector<vector<int> >[nElements];
   }
   // Wrapper around operator delete
   static void delete_vectorlEvectorlEintgRsPgR(void *p) {
      delete (static_cast<vector<vector<int> >*>(p));
   }
   static void deleteArray_vectorlEvectorlEintgRsPgR(void *p) {
      delete [] (static_cast<vector<vector<int> >*>(p));
   }
   static void destruct_vectorlEvectorlEintgRsPgR(void *p) {
      typedef vector<vector<int> > current_t;
      (static_cast<current_t*>(p))->~current_t();
   }
} // end of namespace ROOT for class vector<vector<int> >

namespace ROOT {
   static TClass *vectorlEvectorlEfloatgRsPgR_Dictionary();
   static void vectorlEvectorlEfloatgRsPgR_TClassManip(TClass*);
   static void *new_vectorlEvectorlEfloatgRsPgR(void *p = nullptr);
   static void *newArray_vectorlEvectorlEfloatgRsPgR(Long_t size, void *p);
   static void delete_vectorlEvectorlEfloatgRsPgR(void *p);
   static void deleteArray_vectorlEvectorlEfloatgRsPgR(void *p);
   static void destruct_vectorlEvectorlEfloatgRsPgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const vector<vector<float> >*)
   {
      vector<vector<float> > *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(vector<vector<float> >));
      static ::ROOT::TGenericClassInfo 
         instance("vector<vector<float> >", -2, "vector", 389,
                  typeid(vector<vector<float> >), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &vectorlEvectorlEfloatgRsPgR_Dictionary, isa_proxy, 4,
                  sizeof(vector<vector<float> >) );
      instance.SetNew(&new_vectorlEvectorlEfloatgRsPgR);
      instance.SetNewArray(&newArray_vectorlEvectorlEfloatgRsPgR);
      instance.SetDelete(&delete_vectorlEvectorlEfloatgRsPgR);
      instance.SetDeleteArray(&deleteArray_vectorlEvectorlEfloatgRsPgR);
      instance.SetDestructor(&destruct_vectorlEvectorlEfloatgRsPgR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::Pushback< vector<vector<float> > >()));

      instance.AdoptAlternate(::ROOT::AddClassAlternate("vector<vector<float> >","std::__1::vector<std::__1::vector<float, std::__1::allocator<float>>, std::__1::allocator<std::__1::vector<float, std::__1::allocator<float>>>>"));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const vector<vector<float> >*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *vectorlEvectorlEfloatgRsPgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal(static_cast<const vector<vector<float> >*>(nullptr))->GetClass();
      vectorlEvectorlEfloatgRsPgR_TClassManip(theClass);
   return theClass;
   }

   static void vectorlEvectorlEfloatgRsPgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_vectorlEvectorlEfloatgRsPgR(void *p) {
      return  p ? ::new(static_cast<::ROOT::Internal::TOperatorNewHelper*>(p)) vector<vector<float> > : new vector<vector<float> >;
   }
   static void *newArray_vectorlEvectorlEfloatgRsPgR(Long_t nElements, void *p) {
      return p ? ::new(static_cast<::ROOT::Internal::TOperatorNewHelper*>(p)) vector<vector<float> >[nElements] : new vector<vector<float> >[nElements];
   }
   // Wrapper around operator delete
   static void delete_vectorlEvectorlEfloatgRsPgR(void *p) {
      delete (static_cast<vector<vector<float> >*>(p));
   }
   static void deleteArray_vectorlEvectorlEfloatgRsPgR(void *p) {
      delete [] (static_cast<vector<vector<float> >*>(p));
   }
   static void destruct_vectorlEvectorlEfloatgRsPgR(void *p) {
      typedef vector<vector<float> > current_t;
      (static_cast<current_t*>(p))->~current_t();
   }
} // end of namespace ROOT for class vector<vector<float> >

namespace ROOT {
   static TClass *vectorlEvectorlEdoublegRsPgR_Dictionary();
   static void vectorlEvectorlEdoublegRsPgR_TClassManip(TClass*);
   static void *new_vectorlEvectorlEdoublegRsPgR(void *p = nullptr);
   static void *newArray_vectorlEvectorlEdoublegRsPgR(Long_t size, void *p);
   static void delete_vectorlEvectorlEdoublegRsPgR(void *p);
   static void deleteArray_vectorlEvectorlEdoublegRsPgR(void *p);
   static void destruct_vectorlEvectorlEdoublegRsPgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const vector<vector<double> >*)
   {
      vector<vector<double> > *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(vector<vector<double> >));
      static ::ROOT::TGenericClassInfo 
         instance("vector<vector<double> >", -2, "vector", 389,
                  typeid(vector<vector<double> >), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &vectorlEvectorlEdoublegRsPgR_Dictionary, isa_proxy, 4,
                  sizeof(vector<vector<double> >) );
      instance.SetNew(&new_vectorlEvectorlEdoublegRsPgR);
      instance.SetNewArray(&newArray_vectorlEvectorlEdoublegRsPgR);
      instance.SetDelete(&delete_vectorlEvectorlEdoublegRsPgR);
      instance.SetDeleteArray(&deleteArray_vectorlEvectorlEdoublegRsPgR);
      instance.SetDestructor(&destruct_vectorlEvectorlEdoublegRsPgR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::Pushback< vector<vector<double> > >()));

      instance.AdoptAlternate(::ROOT::AddClassAlternate("vector<vector<double> >","std::__1::vector<std::__1::vector<double, std::__1::allocator<double>>, std::__1::allocator<std::__1::vector<double, std::__1::allocator<double>>>>"));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const vector<vector<double> >*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *vectorlEvectorlEdoublegRsPgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal(static_cast<const vector<vector<double> >*>(nullptr))->GetClass();
      vectorlEvectorlEdoublegRsPgR_TClassManip(theClass);
   return theClass;
   }

   static void vectorlEvectorlEdoublegRsPgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_vectorlEvectorlEdoublegRsPgR(void *p) {
      return  p ? ::new(static_cast<::ROOT::Internal::TOperatorNewHelper*>(p)) vector<vector<double> > : new vector<vector<double> >;
   }
   static void *newArray_vectorlEvectorlEdoublegRsPgR(Long_t nElements, void *p) {
      return p ? ::new(static_cast<::ROOT::Internal::TOperatorNewHelper*>(p)) vector<vector<double> >[nElements] : new vector<vector<double> >[nElements];
   }
   // Wrapper around operator delete
   static void delete_vectorlEvectorlEdoublegRsPgR(void *p) {
      delete (static_cast<vector<vector<double> >*>(p));
   }
   static void deleteArray_vectorlEvectorlEdoublegRsPgR(void *p) {
      delete [] (static_cast<vector<vector<double> >*>(p));
   }
   static void destruct_vectorlEvectorlEdoublegRsPgR(void *p) {
      typedef vector<vector<double> > current_t;
      (static_cast<current_t*>(p))->~current_t();
   }
} // end of namespace ROOT for class vector<vector<double> >

namespace ROOT {
   static TClass *vectorlEunsignedsPlonggR_Dictionary();
   static void vectorlEunsignedsPlonggR_TClassManip(TClass*);
   static void *new_vectorlEunsignedsPlonggR(void *p = nullptr);
   static void *newArray_vectorlEunsignedsPlonggR(Long_t size, void *p);
   static void delete_vectorlEunsignedsPlonggR(void *p);
   static void deleteArray_vectorlEunsignedsPlonggR(void *p);
   static void destruct_vectorlEunsignedsPlonggR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const vector<unsigned long>*)
   {
      vector<unsigned long> *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(vector<unsigned long>));
      static ::ROOT::TGenericClassInfo 
         instance("vector<unsigned long>", -2, "vector", 389,
                  typeid(vector<unsigned long>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &vectorlEunsignedsPlonggR_Dictionary, isa_proxy, 4,
                  sizeof(vector<unsigned long>) );
      instance.SetNew(&new_vectorlEunsignedsPlonggR);
      instance.SetNewArray(&newArray_vectorlEunsignedsPlonggR);
      instance.SetDelete(&delete_vectorlEunsignedsPlonggR);
      instance.SetDeleteArray(&deleteArray_vectorlEunsignedsPlonggR);
      instance.SetDestructor(&destruct_vectorlEunsignedsPlonggR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::Pushback< vector<unsigned long> >()));

      instance.AdoptAlternate(::ROOT::AddClassAlternate("vector<unsigned long>","std::__1::vector<unsigned long, std::__1::allocator<unsigned long>>"));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const vector<unsigned long>*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *vectorlEunsignedsPlonggR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal(static_cast<const vector<unsigned long>*>(nullptr))->GetClass();
      vectorlEunsignedsPlonggR_TClassManip(theClass);
   return theClass;
   }

   static void vectorlEunsignedsPlonggR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_vectorlEunsignedsPlonggR(void *p) {
      return  p ? ::new(static_cast<::ROOT::Internal::TOperatorNewHelper*>(p)) vector<unsigned long> : new vector<unsigned long>;
   }
   static void *newArray_vectorlEunsignedsPlonggR(Long_t nElements, void *p) {
      return p ? ::new(static_cast<::ROOT::Internal::TOperatorNewHelper*>(p)) vector<unsigned long>[nElements] : new vector<unsigned long>[nElements];
   }
   // Wrapper around operator delete
   static void delete_vectorlEunsignedsPlonggR(void *p) {
      delete (static_cast<vector<unsigned long>*>(p));
   }
   static void deleteArray_vectorlEunsignedsPlonggR(void *p) {
      delete [] (static_cast<vector<unsigned long>*>(p));
   }
   static void destruct_vectorlEunsignedsPlonggR(void *p) {
      typedef vector<unsigned long> current_t;
      (static_cast<current_t*>(p))->~current_t();
   }
} // end of namespace ROOT for class vector<unsigned long>

namespace ROOT {
   static TClass *vectorlEunsignedsPintgR_Dictionary();
   static void vectorlEunsignedsPintgR_TClassManip(TClass*);
   static void *new_vectorlEunsignedsPintgR(void *p = nullptr);
   static void *newArray_vectorlEunsignedsPintgR(Long_t size, void *p);
   static void delete_vectorlEunsignedsPintgR(void *p);
   static void deleteArray_vectorlEunsignedsPintgR(void *p);
   static void destruct_vectorlEunsignedsPintgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const vector<unsigned int>*)
   {
      vector<unsigned int> *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(vector<unsigned int>));
      static ::ROOT::TGenericClassInfo 
         instance("vector<unsigned int>", -2, "vector", 389,
                  typeid(vector<unsigned int>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &vectorlEunsignedsPintgR_Dictionary, isa_proxy, 4,
                  sizeof(vector<unsigned int>) );
      instance.SetNew(&new_vectorlEunsignedsPintgR);
      instance.SetNewArray(&newArray_vectorlEunsignedsPintgR);
      instance.SetDelete(&delete_vectorlEunsignedsPintgR);
      instance.SetDeleteArray(&deleteArray_vectorlEunsignedsPintgR);
      instance.SetDestructor(&destruct_vectorlEunsignedsPintgR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::Pushback< vector<unsigned int> >()));

      instance.AdoptAlternate(::ROOT::AddClassAlternate("vector<unsigned int>","std::__1::vector<unsigned int, std::__1::allocator<unsigned int>>"));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const vector<unsigned int>*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *vectorlEunsignedsPintgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal(static_cast<const vector<unsigned int>*>(nullptr))->GetClass();
      vectorlEunsignedsPintgR_TClassManip(theClass);
   return theClass;
   }

   static void vectorlEunsignedsPintgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_vectorlEunsignedsPintgR(void *p) {
      return  p ? ::new(static_cast<::ROOT::Internal::TOperatorNewHelper*>(p)) vector<unsigned int> : new vector<unsigned int>;
   }
   static void *newArray_vectorlEunsignedsPintgR(Long_t nElements, void *p) {
      return p ? ::new(static_cast<::ROOT::Internal::TOperatorNewHelper*>(p)) vector<unsigned int>[nElements] : new vector<unsigned int>[nElements];
   }
   // Wrapper around operator delete
   static void delete_vectorlEunsignedsPintgR(void *p) {
      delete (static_cast<vector<unsigned int>*>(p));
   }
   static void deleteArray_vectorlEunsignedsPintgR(void *p) {
      delete [] (static_cast<vector<unsigned int>*>(p));
   }
   static void destruct_vectorlEunsignedsPintgR(void *p) {
      typedef vector<unsigned int> current_t;
      (static_cast<current_t*>(p))->~current_t();
   }
} // end of namespace ROOT for class vector<unsigned int>

namespace ROOT {
   static TClass *vectorlEstringgR_Dictionary();
   static void vectorlEstringgR_TClassManip(TClass*);
   static void *new_vectorlEstringgR(void *p = nullptr);
   static void *newArray_vectorlEstringgR(Long_t size, void *p);
   static void delete_vectorlEstringgR(void *p);
   static void deleteArray_vectorlEstringgR(void *p);
   static void destruct_vectorlEstringgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const vector<string>*)
   {
      vector<string> *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(vector<string>));
      static ::ROOT::TGenericClassInfo 
         instance("vector<string>", -2, "vector", 389,
                  typeid(vector<string>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &vectorlEstringgR_Dictionary, isa_proxy, 0,
                  sizeof(vector<string>) );
      instance.SetNew(&new_vectorlEstringgR);
      instance.SetNewArray(&newArray_vectorlEstringgR);
      instance.SetDelete(&delete_vectorlEstringgR);
      instance.SetDeleteArray(&deleteArray_vectorlEstringgR);
      instance.SetDestructor(&destruct_vectorlEstringgR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::Pushback< vector<string> >()));

      instance.AdoptAlternate(::ROOT::AddClassAlternate("vector<string>","std::__1::vector<std::__1::basic_string<char, std::__1::char_traits<char>, std::__1::allocator<char>>, std::__1::allocator<std::__1::basic_string<char, std::__1::char_traits<char>, std::__1::allocator<char>>>>"));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const vector<string>*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *vectorlEstringgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal(static_cast<const vector<string>*>(nullptr))->GetClass();
      vectorlEstringgR_TClassManip(theClass);
   return theClass;
   }

   static void vectorlEstringgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_vectorlEstringgR(void *p) {
      return  p ? ::new(static_cast<::ROOT::Internal::TOperatorNewHelper*>(p)) vector<string> : new vector<string>;
   }
   static void *newArray_vectorlEstringgR(Long_t nElements, void *p) {
      return p ? ::new(static_cast<::ROOT::Internal::TOperatorNewHelper*>(p)) vector<string>[nElements] : new vector<string>[nElements];
   }
   // Wrapper around operator delete
   static void delete_vectorlEstringgR(void *p) {
      delete (static_cast<vector<string>*>(p));
   }
   static void deleteArray_vectorlEstringgR(void *p) {
      delete [] (static_cast<vector<string>*>(p));
   }
   static void destruct_vectorlEstringgR(void *p) {
      typedef vector<string> current_t;
      (static_cast<current_t*>(p))->~current_t();
   }
} // end of namespace ROOT for class vector<string>

namespace ROOT {
   static TClass *vectorlElonggR_Dictionary();
   static void vectorlElonggR_TClassManip(TClass*);
   static void *new_vectorlElonggR(void *p = nullptr);
   static void *newArray_vectorlElonggR(Long_t size, void *p);
   static void delete_vectorlElonggR(void *p);
   static void deleteArray_vectorlElonggR(void *p);
   static void destruct_vectorlElonggR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const vector<long>*)
   {
      vector<long> *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(vector<long>));
      static ::ROOT::TGenericClassInfo 
         instance("vector<long>", -2, "vector", 389,
                  typeid(vector<long>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &vectorlElonggR_Dictionary, isa_proxy, 4,
                  sizeof(vector<long>) );
      instance.SetNew(&new_vectorlElonggR);
      instance.SetNewArray(&newArray_vectorlElonggR);
      instance.SetDelete(&delete_vectorlElonggR);
      instance.SetDeleteArray(&deleteArray_vectorlElonggR);
      instance.SetDestructor(&destruct_vectorlElonggR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::Pushback< vector<long> >()));

      instance.AdoptAlternate(::ROOT::AddClassAlternate("vector<long>","std::__1::vector<long, std::__1::allocator<long>>"));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const vector<long>*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *vectorlElonggR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal(static_cast<const vector<long>*>(nullptr))->GetClass();
      vectorlElonggR_TClassManip(theClass);
   return theClass;
   }

   static void vectorlElonggR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_vectorlElonggR(void *p) {
      return  p ? ::new(static_cast<::ROOT::Internal::TOperatorNewHelper*>(p)) vector<long> : new vector<long>;
   }
   static void *newArray_vectorlElonggR(Long_t nElements, void *p) {
      return p ? ::new(static_cast<::ROOT::Internal::TOperatorNewHelper*>(p)) vector<long>[nElements] : new vector<long>[nElements];
   }
   // Wrapper around operator delete
   static void delete_vectorlElonggR(void *p) {
      delete (static_cast<vector<long>*>(p));
   }
   static void deleteArray_vectorlElonggR(void *p) {
      delete [] (static_cast<vector<long>*>(p));
   }
   static void destruct_vectorlElonggR(void *p) {
      typedef vector<long> current_t;
      (static_cast<current_t*>(p))->~current_t();
   }
} // end of namespace ROOT for class vector<long>

namespace ROOT {
   static TClass *vectorlElongmUgR_Dictionary();
   static void vectorlElongmUgR_TClassManip(TClass*);
   static void *new_vectorlElongmUgR(void *p = nullptr);
   static void *newArray_vectorlElongmUgR(Long_t size, void *p);
   static void delete_vectorlElongmUgR(void *p);
   static void deleteArray_vectorlElongmUgR(void *p);
   static void destruct_vectorlElongmUgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const vector<long*>*)
   {
      vector<long*> *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(vector<long*>));
      static ::ROOT::TGenericClassInfo 
         instance("vector<long*>", -2, "vector", 389,
                  typeid(vector<long*>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &vectorlElongmUgR_Dictionary, isa_proxy, 4,
                  sizeof(vector<long*>) );
      instance.SetNew(&new_vectorlElongmUgR);
      instance.SetNewArray(&newArray_vectorlElongmUgR);
      instance.SetDelete(&delete_vectorlElongmUgR);
      instance.SetDeleteArray(&deleteArray_vectorlElongmUgR);
      instance.SetDestructor(&destruct_vectorlElongmUgR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::Pushback< vector<long*> >()));

      instance.AdoptAlternate(::ROOT::AddClassAlternate("vector<long*>","std::__1::vector<long*, std::__1::allocator<long*>>"));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const vector<long*>*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *vectorlElongmUgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal(static_cast<const vector<long*>*>(nullptr))->GetClass();
      vectorlElongmUgR_TClassManip(theClass);
   return theClass;
   }

   static void vectorlElongmUgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_vectorlElongmUgR(void *p) {
      return  p ? ::new(static_cast<::ROOT::Internal::TOperatorNewHelper*>(p)) vector<long*> : new vector<long*>;
   }
   static void *newArray_vectorlElongmUgR(Long_t nElements, void *p) {
      return p ? ::new(static_cast<::ROOT::Internal::TOperatorNewHelper*>(p)) vector<long*>[nElements] : new vector<long*>[nElements];
   }
   // Wrapper around operator delete
   static void delete_vectorlElongmUgR(void *p) {
      delete (static_cast<vector<long*>*>(p));
   }
   static void deleteArray_vectorlElongmUgR(void *p) {
      delete [] (static_cast<vector<long*>*>(p));
   }
   static void destruct_vectorlElongmUgR(void *p) {
      typedef vector<long*> current_t;
      (static_cast<current_t*>(p))->~current_t();
   }
} // end of namespace ROOT for class vector<long*>

namespace ROOT {
   static TClass *vectorlEintgR_Dictionary();
   static void vectorlEintgR_TClassManip(TClass*);
   static void *new_vectorlEintgR(void *p = nullptr);
   static void *newArray_vectorlEintgR(Long_t size, void *p);
   static void delete_vectorlEintgR(void *p);
   static void deleteArray_vectorlEintgR(void *p);
   static void destruct_vectorlEintgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const vector<int>*)
   {
      vector<int> *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(vector<int>));
      static ::ROOT::TGenericClassInfo 
         instance("vector<int>", -2, "vector", 389,
                  typeid(vector<int>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &vectorlEintgR_Dictionary, isa_proxy, 4,
                  sizeof(vector<int>) );
      instance.SetNew(&new_vectorlEintgR);
      instance.SetNewArray(&newArray_vectorlEintgR);
      instance.SetDelete(&delete_vectorlEintgR);
      instance.SetDeleteArray(&deleteArray_vectorlEintgR);
      instance.SetDestructor(&destruct_vectorlEintgR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::Pushback< vector<int> >()));

      instance.AdoptAlternate(::ROOT::AddClassAlternate("vector<int>","std::__1::vector<int, std::__1::allocator<int>>"));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const vector<int>*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *vectorlEintgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal(static_cast<const vector<int>*>(nullptr))->GetClass();
      vectorlEintgR_TClassManip(theClass);
   return theClass;
   }

   static void vectorlEintgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_vectorlEintgR(void *p) {
      return  p ? ::new(static_cast<::ROOT::Internal::TOperatorNewHelper*>(p)) vector<int> : new vector<int>;
   }
   static void *newArray_vectorlEintgR(Long_t nElements, void *p) {
      return p ? ::new(static_cast<::ROOT::Internal::TOperatorNewHelper*>(p)) vector<int>[nElements] : new vector<int>[nElements];
   }
   // Wrapper around operator delete
   static void delete_vectorlEintgR(void *p) {
      delete (static_cast<vector<int>*>(p));
   }
   static void deleteArray_vectorlEintgR(void *p) {
      delete [] (static_cast<vector<int>*>(p));
   }
   static void destruct_vectorlEintgR(void *p) {
      typedef vector<int> current_t;
      (static_cast<current_t*>(p))->~current_t();
   }
} // end of namespace ROOT for class vector<int>

namespace ROOT {
   static TClass *vectorlEintmUgR_Dictionary();
   static void vectorlEintmUgR_TClassManip(TClass*);
   static void *new_vectorlEintmUgR(void *p = nullptr);
   static void *newArray_vectorlEintmUgR(Long_t size, void *p);
   static void delete_vectorlEintmUgR(void *p);
   static void deleteArray_vectorlEintmUgR(void *p);
   static void destruct_vectorlEintmUgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const vector<int*>*)
   {
      vector<int*> *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(vector<int*>));
      static ::ROOT::TGenericClassInfo 
         instance("vector<int*>", -2, "vector", 389,
                  typeid(vector<int*>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &vectorlEintmUgR_Dictionary, isa_proxy, 4,
                  sizeof(vector<int*>) );
      instance.SetNew(&new_vectorlEintmUgR);
      instance.SetNewArray(&newArray_vectorlEintmUgR);
      instance.SetDelete(&delete_vectorlEintmUgR);
      instance.SetDeleteArray(&deleteArray_vectorlEintmUgR);
      instance.SetDestructor(&destruct_vectorlEintmUgR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::Pushback< vector<int*> >()));

      instance.AdoptAlternate(::ROOT::AddClassAlternate("vector<int*>","std::__1::vector<int*, std::__1::allocator<int*>>"));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const vector<int*>*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *vectorlEintmUgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal(static_cast<const vector<int*>*>(nullptr))->GetClass();
      vectorlEintmUgR_TClassManip(theClass);
   return theClass;
   }

   static void vectorlEintmUgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_vectorlEintmUgR(void *p) {
      return  p ? ::new(static_cast<::ROOT::Internal::TOperatorNewHelper*>(p)) vector<int*> : new vector<int*>;
   }
   static void *newArray_vectorlEintmUgR(Long_t nElements, void *p) {
      return p ? ::new(static_cast<::ROOT::Internal::TOperatorNewHelper*>(p)) vector<int*>[nElements] : new vector<int*>[nElements];
   }
   // Wrapper around operator delete
   static void delete_vectorlEintmUgR(void *p) {
      delete (static_cast<vector<int*>*>(p));
   }
   static void deleteArray_vectorlEintmUgR(void *p) {
      delete [] (static_cast<vector<int*>*>(p));
   }
   static void destruct_vectorlEintmUgR(void *p) {
      typedef vector<int*> current_t;
      (static_cast<current_t*>(p))->~current_t();
   }
} // end of namespace ROOT for class vector<int*>

namespace ROOT {
   static TClass *vectorlEfloatgR_Dictionary();
   static void vectorlEfloatgR_TClassManip(TClass*);
   static void *new_vectorlEfloatgR(void *p = nullptr);
   static void *newArray_vectorlEfloatgR(Long_t size, void *p);
   static void delete_vectorlEfloatgR(void *p);
   static void deleteArray_vectorlEfloatgR(void *p);
   static void destruct_vectorlEfloatgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const vector<float>*)
   {
      vector<float> *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(vector<float>));
      static ::ROOT::TGenericClassInfo 
         instance("vector<float>", -2, "vector", 389,
                  typeid(vector<float>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &vectorlEfloatgR_Dictionary, isa_proxy, 4,
                  sizeof(vector<float>) );
      instance.SetNew(&new_vectorlEfloatgR);
      instance.SetNewArray(&newArray_vectorlEfloatgR);
      instance.SetDelete(&delete_vectorlEfloatgR);
      instance.SetDeleteArray(&deleteArray_vectorlEfloatgR);
      instance.SetDestructor(&destruct_vectorlEfloatgR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::Pushback< vector<float> >()));

      instance.AdoptAlternate(::ROOT::AddClassAlternate("vector<float>","std::__1::vector<float, std::__1::allocator<float>>"));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const vector<float>*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *vectorlEfloatgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal(static_cast<const vector<float>*>(nullptr))->GetClass();
      vectorlEfloatgR_TClassManip(theClass);
   return theClass;
   }

   static void vectorlEfloatgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_vectorlEfloatgR(void *p) {
      return  p ? ::new(static_cast<::ROOT::Internal::TOperatorNewHelper*>(p)) vector<float> : new vector<float>;
   }
   static void *newArray_vectorlEfloatgR(Long_t nElements, void *p) {
      return p ? ::new(static_cast<::ROOT::Internal::TOperatorNewHelper*>(p)) vector<float>[nElements] : new vector<float>[nElements];
   }
   // Wrapper around operator delete
   static void delete_vectorlEfloatgR(void *p) {
      delete (static_cast<vector<float>*>(p));
   }
   static void deleteArray_vectorlEfloatgR(void *p) {
      delete [] (static_cast<vector<float>*>(p));
   }
   static void destruct_vectorlEfloatgR(void *p) {
      typedef vector<float> current_t;
      (static_cast<current_t*>(p))->~current_t();
   }
} // end of namespace ROOT for class vector<float>

namespace ROOT {
   static TClass *vectorlEfloatmUgR_Dictionary();
   static void vectorlEfloatmUgR_TClassManip(TClass*);
   static void *new_vectorlEfloatmUgR(void *p = nullptr);
   static void *newArray_vectorlEfloatmUgR(Long_t size, void *p);
   static void delete_vectorlEfloatmUgR(void *p);
   static void deleteArray_vectorlEfloatmUgR(void *p);
   static void destruct_vectorlEfloatmUgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const vector<float*>*)
   {
      vector<float*> *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(vector<float*>));
      static ::ROOT::TGenericClassInfo 
         instance("vector<float*>", -2, "vector", 389,
                  typeid(vector<float*>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &vectorlEfloatmUgR_Dictionary, isa_proxy, 4,
                  sizeof(vector<float*>) );
      instance.SetNew(&new_vectorlEfloatmUgR);
      instance.SetNewArray(&newArray_vectorlEfloatmUgR);
      instance.SetDelete(&delete_vectorlEfloatmUgR);
      instance.SetDeleteArray(&deleteArray_vectorlEfloatmUgR);
      instance.SetDestructor(&destruct_vectorlEfloatmUgR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::Pushback< vector<float*> >()));

      instance.AdoptAlternate(::ROOT::AddClassAlternate("vector<float*>","std::__1::vector<float*, std::__1::allocator<float*>>"));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const vector<float*>*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *vectorlEfloatmUgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal(static_cast<const vector<float*>*>(nullptr))->GetClass();
      vectorlEfloatmUgR_TClassManip(theClass);
   return theClass;
   }

   static void vectorlEfloatmUgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_vectorlEfloatmUgR(void *p) {
      return  p ? ::new(static_cast<::ROOT::Internal::TOperatorNewHelper*>(p)) vector<float*> : new vector<float*>;
   }
   static void *newArray_vectorlEfloatmUgR(Long_t nElements, void *p) {
      return p ? ::new(static_cast<::ROOT::Internal::TOperatorNewHelper*>(p)) vector<float*>[nElements] : new vector<float*>[nElements];
   }
   // Wrapper around operator delete
   static void delete_vectorlEfloatmUgR(void *p) {
      delete (static_cast<vector<float*>*>(p));
   }
   static void deleteArray_vectorlEfloatmUgR(void *p) {
      delete [] (static_cast<vector<float*>*>(p));
   }
   static void destruct_vectorlEfloatmUgR(void *p) {
      typedef vector<float*> current_t;
      (static_cast<current_t*>(p))->~current_t();
   }
} // end of namespace ROOT for class vector<float*>

namespace ROOT {
   static TClass *vectorlEdoublegR_Dictionary();
   static void vectorlEdoublegR_TClassManip(TClass*);
   static void *new_vectorlEdoublegR(void *p = nullptr);
   static void *newArray_vectorlEdoublegR(Long_t size, void *p);
   static void delete_vectorlEdoublegR(void *p);
   static void deleteArray_vectorlEdoublegR(void *p);
   static void destruct_vectorlEdoublegR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const vector<double>*)
   {
      vector<double> *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(vector<double>));
      static ::ROOT::TGenericClassInfo 
         instance("vector<double>", -2, "vector", 389,
                  typeid(vector<double>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &vectorlEdoublegR_Dictionary, isa_proxy, 4,
                  sizeof(vector<double>) );
      instance.SetNew(&new_vectorlEdoublegR);
      instance.SetNewArray(&newArray_vectorlEdoublegR);
      instance.SetDelete(&delete_vectorlEdoublegR);
      instance.SetDeleteArray(&deleteArray_vectorlEdoublegR);
      instance.SetDestructor(&destruct_vectorlEdoublegR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::Pushback< vector<double> >()));

      instance.AdoptAlternate(::ROOT::AddClassAlternate("vector<double>","std::__1::vector<double, std::__1::allocator<double>>"));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const vector<double>*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *vectorlEdoublegR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal(static_cast<const vector<double>*>(nullptr))->GetClass();
      vectorlEdoublegR_TClassManip(theClass);
   return theClass;
   }

   static void vectorlEdoublegR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_vectorlEdoublegR(void *p) {
      return  p ? ::new(static_cast<::ROOT::Internal::TOperatorNewHelper*>(p)) vector<double> : new vector<double>;
   }
   static void *newArray_vectorlEdoublegR(Long_t nElements, void *p) {
      return p ? ::new(static_cast<::ROOT::Internal::TOperatorNewHelper*>(p)) vector<double>[nElements] : new vector<double>[nElements];
   }
   // Wrapper around operator delete
   static void delete_vectorlEdoublegR(void *p) {
      delete (static_cast<vector<double>*>(p));
   }
   static void deleteArray_vectorlEdoublegR(void *p) {
      delete [] (static_cast<vector<double>*>(p));
   }
   static void destruct_vectorlEdoublegR(void *p) {
      typedef vector<double> current_t;
      (static_cast<current_t*>(p))->~current_t();
   }
} // end of namespace ROOT for class vector<double>

namespace ROOT {
   static TClass *vectorlEdoublemUgR_Dictionary();
   static void vectorlEdoublemUgR_TClassManip(TClass*);
   static void *new_vectorlEdoublemUgR(void *p = nullptr);
   static void *newArray_vectorlEdoublemUgR(Long_t size, void *p);
   static void delete_vectorlEdoublemUgR(void *p);
   static void deleteArray_vectorlEdoublemUgR(void *p);
   static void destruct_vectorlEdoublemUgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const vector<double*>*)
   {
      vector<double*> *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(vector<double*>));
      static ::ROOT::TGenericClassInfo 
         instance("vector<double*>", -2, "vector", 389,
                  typeid(vector<double*>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &vectorlEdoublemUgR_Dictionary, isa_proxy, 4,
                  sizeof(vector<double*>) );
      instance.SetNew(&new_vectorlEdoublemUgR);
      instance.SetNewArray(&newArray_vectorlEdoublemUgR);
      instance.SetDelete(&delete_vectorlEdoublemUgR);
      instance.SetDeleteArray(&deleteArray_vectorlEdoublemUgR);
      instance.SetDestructor(&destruct_vectorlEdoublemUgR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::Pushback< vector<double*> >()));

      instance.AdoptAlternate(::ROOT::AddClassAlternate("vector<double*>","std::__1::vector<double*, std::__1::allocator<double*>>"));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const vector<double*>*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *vectorlEdoublemUgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal(static_cast<const vector<double*>*>(nullptr))->GetClass();
      vectorlEdoublemUgR_TClassManip(theClass);
   return theClass;
   }

   static void vectorlEdoublemUgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_vectorlEdoublemUgR(void *p) {
      return  p ? ::new(static_cast<::ROOT::Internal::TOperatorNewHelper*>(p)) vector<double*> : new vector<double*>;
   }
   static void *newArray_vectorlEdoublemUgR(Long_t nElements, void *p) {
      return p ? ::new(static_cast<::ROOT::Internal::TOperatorNewHelper*>(p)) vector<double*>[nElements] : new vector<double*>[nElements];
   }
   // Wrapper around operator delete
   static void delete_vectorlEdoublemUgR(void *p) {
      delete (static_cast<vector<double*>*>(p));
   }
   static void deleteArray_vectorlEdoublemUgR(void *p) {
      delete [] (static_cast<vector<double*>*>(p));
   }
   static void destruct_vectorlEdoublemUgR(void *p) {
      typedef vector<double*> current_t;
      (static_cast<current_t*>(p))->~current_t();
   }
} // end of namespace ROOT for class vector<double*>

namespace ROOT {
   static TClass *maplEstringcOintgR_Dictionary();
   static void maplEstringcOintgR_TClassManip(TClass*);
   static void *new_maplEstringcOintgR(void *p = nullptr);
   static void *newArray_maplEstringcOintgR(Long_t size, void *p);
   static void delete_maplEstringcOintgR(void *p);
   static void deleteArray_maplEstringcOintgR(void *p);
   static void destruct_maplEstringcOintgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const map<string,int>*)
   {
      map<string,int> *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(map<string,int>));
      static ::ROOT::TGenericClassInfo 
         instance("map<string,int>", -2, "map", 964,
                  typeid(map<string,int>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &maplEstringcOintgR_Dictionary, isa_proxy, 0,
                  sizeof(map<string,int>) );
      instance.SetNew(&new_maplEstringcOintgR);
      instance.SetNewArray(&newArray_maplEstringcOintgR);
      instance.SetDelete(&delete_maplEstringcOintgR);
      instance.SetDeleteArray(&deleteArray_maplEstringcOintgR);
      instance.SetDestructor(&destruct_maplEstringcOintgR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::MapInsert< map<string,int> >()));

      instance.AdoptAlternate(::ROOT::AddClassAlternate("map<string,int>","std::__1::map<std::__1::basic_string<char, std::__1::char_traits<char>, std::__1::allocator<char>>, int, std::__1::less<std::__1::basic_string<char, std::__1::char_traits<char>, std::__1::allocator<char>>>, std::__1::allocator<std::__1::pair<std::__1::basic_string<char, std::__1::char_traits<char>, std::__1::allocator<char>> const, int>>>"));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const map<string,int>*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *maplEstringcOintgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal(static_cast<const map<string,int>*>(nullptr))->GetClass();
      maplEstringcOintgR_TClassManip(theClass);
   return theClass;
   }

   static void maplEstringcOintgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_maplEstringcOintgR(void *p) {
      return  p ? ::new(static_cast<::ROOT::Internal::TOperatorNewHelper*>(p)) map<string,int> : new map<string,int>;
   }
   static void *newArray_maplEstringcOintgR(Long_t nElements, void *p) {
      return p ? ::new(static_cast<::ROOT::Internal::TOperatorNewHelper*>(p)) map<string,int>[nElements] : new map<string,int>[nElements];
   }
   // Wrapper around operator delete
   static void delete_maplEstringcOintgR(void *p) {
      delete (static_cast<map<string,int>*>(p));
   }
   static void deleteArray_maplEstringcOintgR(void *p) {
      delete [] (static_cast<map<string,int>*>(p));
   }
   static void destruct_maplEstringcOintgR(void *p) {
      typedef map<string,int> current_t;
      (static_cast<current_t*>(p))->~current_t();
   }
} // end of namespace ROOT for class map<string,int>

namespace ROOT {
   static TClass *maplEstringcOTChainmUgR_Dictionary();
   static void maplEstringcOTChainmUgR_TClassManip(TClass*);
   static void *new_maplEstringcOTChainmUgR(void *p = nullptr);
   static void *newArray_maplEstringcOTChainmUgR(Long_t size, void *p);
   static void delete_maplEstringcOTChainmUgR(void *p);
   static void deleteArray_maplEstringcOTChainmUgR(void *p);
   static void destruct_maplEstringcOTChainmUgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const map<string,TChain*>*)
   {
      map<string,TChain*> *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(map<string,TChain*>));
      static ::ROOT::TGenericClassInfo 
         instance("map<string,TChain*>", -2, "map", 964,
                  typeid(map<string,TChain*>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &maplEstringcOTChainmUgR_Dictionary, isa_proxy, 0,
                  sizeof(map<string,TChain*>) );
      instance.SetNew(&new_maplEstringcOTChainmUgR);
      instance.SetNewArray(&newArray_maplEstringcOTChainmUgR);
      instance.SetDelete(&delete_maplEstringcOTChainmUgR);
      instance.SetDeleteArray(&deleteArray_maplEstringcOTChainmUgR);
      instance.SetDestructor(&destruct_maplEstringcOTChainmUgR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::MapInsert< map<string,TChain*> >()));

      instance.AdoptAlternate(::ROOT::AddClassAlternate("map<string,TChain*>","std::__1::map<std::__1::basic_string<char, std::__1::char_traits<char>, std::__1::allocator<char>>, TChain*, std::__1::less<std::__1::basic_string<char, std::__1::char_traits<char>, std::__1::allocator<char>>>, std::__1::allocator<std::__1::pair<std::__1::basic_string<char, std::__1::char_traits<char>, std::__1::allocator<char>> const, TChain*>>>"));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const map<string,TChain*>*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *maplEstringcOTChainmUgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal(static_cast<const map<string,TChain*>*>(nullptr))->GetClass();
      maplEstringcOTChainmUgR_TClassManip(theClass);
   return theClass;
   }

   static void maplEstringcOTChainmUgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_maplEstringcOTChainmUgR(void *p) {
      return  p ? ::new(static_cast<::ROOT::Internal::TOperatorNewHelper*>(p)) map<string,TChain*> : new map<string,TChain*>;
   }
   static void *newArray_maplEstringcOTChainmUgR(Long_t nElements, void *p) {
      return p ? ::new(static_cast<::ROOT::Internal::TOperatorNewHelper*>(p)) map<string,TChain*>[nElements] : new map<string,TChain*>[nElements];
   }
   // Wrapper around operator delete
   static void delete_maplEstringcOTChainmUgR(void *p) {
      delete (static_cast<map<string,TChain*>*>(p));
   }
   static void deleteArray_maplEstringcOTChainmUgR(void *p) {
      delete [] (static_cast<map<string,TChain*>*>(p));
   }
   static void destruct_maplEstringcOTChainmUgR(void *p) {
      typedef map<string,TChain*> current_t;
      (static_cast<current_t*>(p))->~current_t();
   }
} // end of namespace ROOT for class map<string,TChain*>

namespace ROOT {
   static TClass *maplEstringcOFieldgR_Dictionary();
   static void maplEstringcOFieldgR_TClassManip(TClass*);
   static void *new_maplEstringcOFieldgR(void *p = nullptr);
   static void *newArray_maplEstringcOFieldgR(Long_t size, void *p);
   static void delete_maplEstringcOFieldgR(void *p);
   static void deleteArray_maplEstringcOFieldgR(void *p);
   static void destruct_maplEstringcOFieldgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const map<string,Field>*)
   {
      map<string,Field> *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(map<string,Field>));
      static ::ROOT::TGenericClassInfo 
         instance("map<string,Field>", -2, "map", 964,
                  typeid(map<string,Field>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &maplEstringcOFieldgR_Dictionary, isa_proxy, 0,
                  sizeof(map<string,Field>) );
      instance.SetNew(&new_maplEstringcOFieldgR);
      instance.SetNewArray(&newArray_maplEstringcOFieldgR);
      instance.SetDelete(&delete_maplEstringcOFieldgR);
      instance.SetDeleteArray(&deleteArray_maplEstringcOFieldgR);
      instance.SetDestructor(&destruct_maplEstringcOFieldgR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::MapInsert< map<string,Field> >()));

      instance.AdoptAlternate(::ROOT::AddClassAlternate("map<string,Field>","std::__1::map<std::__1::basic_string<char, std::__1::char_traits<char>, std::__1::allocator<char>>, Field, std::__1::less<std::__1::basic_string<char, std::__1::char_traits<char>, std::__1::allocator<char>>>, std::__1::allocator<std::__1::pair<std::__1::basic_string<char, std::__1::char_traits<char>, std::__1::allocator<char>> const, Field>>>"));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const map<string,Field>*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *maplEstringcOFieldgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal(static_cast<const map<string,Field>*>(nullptr))->GetClass();
      maplEstringcOFieldgR_TClassManip(theClass);
   return theClass;
   }

   static void maplEstringcOFieldgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_maplEstringcOFieldgR(void *p) {
      return  p ? ::new(static_cast<::ROOT::Internal::TOperatorNewHelper*>(p)) map<string,Field> : new map<string,Field>;
   }
   static void *newArray_maplEstringcOFieldgR(Long_t nElements, void *p) {
      return p ? ::new(static_cast<::ROOT::Internal::TOperatorNewHelper*>(p)) map<string,Field>[nElements] : new map<string,Field>[nElements];
   }
   // Wrapper around operator delete
   static void delete_maplEstringcOFieldgR(void *p) {
      delete (static_cast<map<string,Field>*>(p));
   }
   static void deleteArray_maplEstringcOFieldgR(void *p) {
      delete [] (static_cast<map<string,Field>*>(p));
   }
   static void destruct_maplEstringcOFieldgR(void *p) {
      typedef map<string,Field> current_t;
      (static_cast<current_t*>(p))->~current_t();
   }
} // end of namespace ROOT for class map<string,Field>

namespace ROOT {
   static TClass *maplEstringcOFieldmUgR_Dictionary();
   static void maplEstringcOFieldmUgR_TClassManip(TClass*);
   static void *new_maplEstringcOFieldmUgR(void *p = nullptr);
   static void *newArray_maplEstringcOFieldmUgR(Long_t size, void *p);
   static void delete_maplEstringcOFieldmUgR(void *p);
   static void deleteArray_maplEstringcOFieldmUgR(void *p);
   static void destruct_maplEstringcOFieldmUgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const map<string,Field*>*)
   {
      map<string,Field*> *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(map<string,Field*>));
      static ::ROOT::TGenericClassInfo 
         instance("map<string,Field*>", -2, "map", 964,
                  typeid(map<string,Field*>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &maplEstringcOFieldmUgR_Dictionary, isa_proxy, 0,
                  sizeof(map<string,Field*>) );
      instance.SetNew(&new_maplEstringcOFieldmUgR);
      instance.SetNewArray(&newArray_maplEstringcOFieldmUgR);
      instance.SetDelete(&delete_maplEstringcOFieldmUgR);
      instance.SetDeleteArray(&deleteArray_maplEstringcOFieldmUgR);
      instance.SetDestructor(&destruct_maplEstringcOFieldmUgR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::MapInsert< map<string,Field*> >()));

      instance.AdoptAlternate(::ROOT::AddClassAlternate("map<string,Field*>","std::__1::map<std::__1::basic_string<char, std::__1::char_traits<char>, std::__1::allocator<char>>, Field*, std::__1::less<std::__1::basic_string<char, std::__1::char_traits<char>, std::__1::allocator<char>>>, std::__1::allocator<std::__1::pair<std::__1::basic_string<char, std::__1::char_traits<char>, std::__1::allocator<char>> const, Field*>>>"));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const map<string,Field*>*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *maplEstringcOFieldmUgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal(static_cast<const map<string,Field*>*>(nullptr))->GetClass();
      maplEstringcOFieldmUgR_TClassManip(theClass);
   return theClass;
   }

   static void maplEstringcOFieldmUgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_maplEstringcOFieldmUgR(void *p) {
      return  p ? ::new(static_cast<::ROOT::Internal::TOperatorNewHelper*>(p)) map<string,Field*> : new map<string,Field*>;
   }
   static void *newArray_maplEstringcOFieldmUgR(Long_t nElements, void *p) {
      return p ? ::new(static_cast<::ROOT::Internal::TOperatorNewHelper*>(p)) map<string,Field*>[nElements] : new map<string,Field*>[nElements];
   }
   // Wrapper around operator delete
   static void delete_maplEstringcOFieldmUgR(void *p) {
      delete (static_cast<map<string,Field*>*>(p));
   }
   static void deleteArray_maplEstringcOFieldmUgR(void *p) {
      delete [] (static_cast<map<string,Field*>*>(p));
   }
   static void destruct_maplEstringcOFieldmUgR(void *p) {
      typedef map<string,Field*> current_t;
      (static_cast<current_t*>(p))->~current_t();
   }
} // end of namespace ROOT for class map<string,Field*>

namespace {
  void TriggerDictionaryInitialization_treestream_dict_Impl() {
    static const char* headers[] = {
"include/treestream.h",
nullptr
    };
    static const char* includePaths[] = {
"/opt/homebrew/Cellar/root/6.34.08_1/include/root",
"/Users/jhlee/treestream/",
nullptr
    };
    static const char* fwdDeclCode = R"DICTFWDDCLS(
#line 1 "treestream_dict dictionary forward declarations' payload"
#pragma clang diagnostic ignored "-Wkeyword-compat"
#pragma clang diagnostic ignored "-Wignored-attributes"
#pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
extern int __Cling_AutoLoading_Map;
namespace std{inline namespace __1{template <class _Tp> class __attribute__((annotate("$clingAutoload$__memory/allocator.h")))  __attribute__((annotate("$clingAutoload$string")))  allocator;
}}
class __attribute__((annotate("$clingAutoload$include/treestream.h")))  itreestream;
class __attribute__((annotate("$clingAutoload$include/treestream.h")))  otreestream;
)DICTFWDDCLS";
    static const char* payloadCode = R"DICTPAYLOAD(
#line 1 "treestream_dict dictionary payload"


#define _BACKWARD_BACKWARD_WARNING_H
// Inline headers
#include "include/treestream.h"

#undef  _BACKWARD_BACKWARD_WARNING_H
)DICTPAYLOAD";
    static const char* classesHeaders[] = {
"itreestream", payloadCode, "@",
"otreestream", payloadCode, "@",
nullptr
};
    static bool isInitialized = false;
    if (!isInitialized) {
      TROOT::RegisterModule("treestream_dict",
        headers, includePaths, payloadCode, fwdDeclCode,
        TriggerDictionaryInitialization_treestream_dict_Impl, {}, classesHeaders, /*hasCxxModule*/false);
      isInitialized = true;
    }
  }
  static struct DictInit {
    DictInit() {
      TriggerDictionaryInitialization_treestream_dict_Impl();
    }
  } __TheDictionaryInitializer;
}
void TriggerDictionaryInitialization_treestream_dict() {
  TriggerDictionaryInitialization_treestream_dict_Impl();
}
