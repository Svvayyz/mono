#pragma once
#include "includes.h"

#define MONO_DLL "mono-2.0-bdwgc.dll"

#define LOG(szText) std::cout << szText << std::endl; 

#define CAST(vVariable, tType) reinterpret_cast<tType>(vVariable)
#define IMPORT(vVariable, tType, szName, szFunctionName) tType vVariable = CAST(GetProcAddr(GetModule(szName), szFunctionName), tType)
#define LOOP(nIterations, szVariableName) for (int szVariableName = 0; szVariableName < nIterations; szVariableName++)

struct _MonoAssemblyName {
	const char* name;
};

#pragma region Domain
typedef MonoDomain* (*tMonoGetRootDomain)();
typedef void(*tMonoDomainAssemblyFunc)(MonoAssembly* assembly, void* user_data);
typedef void(*tMonoDomainAssemblyForeach)(MonoDomain*, tMonoDomainAssemblyFunc, void*);

typedef const char* (*tMonoDomainGetFriendlyName)(MonoDomain*);
typedef int(*tMonoDomainGetId)(MonoDomain*);
#pragma endregion
#pragma region Assembly
typedef MonoImage* (*tMonoAssemblyGetImage)(MonoAssembly*);

typedef MonoAssembly* (*tMonoDomainAssemblyOpen)(MonoDomain*, const char*);
typedef MonoAssembly* (*tMonoAssemblyLoaded)(MonoAssemblyName*);
typedef MonoAssemblyName* (*tMonoAssemblyGetName)(MonoAssembly*);
#pragma endregion
#pragma region Image
typedef MonoImage* (*tMonoImageLoaded)(const char*);

typedef MonoTableInfo* (*tMonoImageGetTableInfo)(MonoImage* pImage, int nTableId);
typedef int(*tMonoImageGetTableRows)(MonoImage* pImage, int nTableId);

typedef MonoClass* (*tMonoClassFromName)(MonoImage*, const char*, const char*);
#pragma endregion
#pragma region Thread 
typedef MonoThread* (*tMonoThreadAttach)(MonoDomain*);
#pragma endregion
#pragma region Object 
typedef MonoObject* (*tMonoObjectNew)(MonoDomain*, MonoClass*);
typedef void* (*tMonoObjectUnbox)(MonoObject*);

typedef void (*tMonoRuntimeObjectInit)(MonoObject*);
#pragma endregion 

#pragma region Error 
typedef bool (*tMonoErrorOK)(MonoError*);

typedef unsigned short (*tMonoErrorGetErrorCode)(MonoError*);
typedef const char* (*tMonoErrorGetMessage)(MonoError*);

typedef void (*tMonoErrorCleanup)(MonoError*);
#pragma endregion

#pragma region String
typedef char* (*tMonoStringToUTF8Checked)(MonoString*, MonoError*);
typedef int (*tMonoStringLength)(MonoString*);

typedef void (*tMonoFree)(void*);
#pragma endregion
#pragma region Type
typedef MonoReflectionType* (*tMonoTypeGetObject)(MonoDomain*, MonoType*);
#pragma endregion

#pragma region Class
typedef const char* (*tMonoClassGetName)(MonoClass*);
typedef const char* (*tMonoClassGetNamespace)(MonoClass*);

typedef int(*tMonoClassNumEvents)(MonoClass*);
typedef int(*tMonoClassNumFields)(MonoClass*);
typedef int(*tMonoClassNumMethods)(MonoClass*);
typedef int(*tMonoClassNumProperties)(MonoClass*);

typedef MonoVTable* (*tMonoClassVTable)(MonoDomain*, MonoClass*);
typedef void* (*tMonoVTableGetStaticFieldData)(MonoDomain*, MonoClass*);
typedef MonoMethod* (*tMonoClassGetMethodFromName)(MonoClass*, const char*, int);

typedef MonoType* (*tMonoClassGetType)(MonoClass*);
#pragma endregion
#pragma region Field
typedef MonoClassField* (*tMonoClassGetFieldFromName)(MonoClass*, const char*);
typedef MonoClassField* (*tMonoClassGetFields)(MonoClass*, void**);

typedef const char* (*tMonoFieldGetName)(MonoClassField*);
typedef void*(*tMonoFieldGetValue)(void*, MonoClassField*, void*);
typedef void(*tMonoFieldSetValue)(MonoObject*, MonoClassField*, void*);
typedef uintptr_t(*tMonoFieldGetOffset)(MonoClassField*);
#pragma endregion
#pragma region Property 
typedef MonoProperty* (*tMonoClassGetProperties)(MonoClass*, void**);
typedef MonoProperty* (*tMonoClassGetPropertyFromName)(MonoClass*, const char*);

typedef const char* (*tMonoPropertyGetName)(MonoProperty*);

typedef void (*tMonoPropertySetValue)(MonoProperty*, void*, void**, MonoObject**);
typedef MonoObject* (*tMonoPropertyGetValue)(MonoProperty*, void*, void**, MonoObject**);
#pragma endregion

#pragma region Method
typedef MonoObject* (*tMonoRuntimeInvoke)(MonoMethod*, void*, void**, MonoObject**);

typedef void* (*tMonoCompileMethod)(MonoMethod*);
#pragma endregion
