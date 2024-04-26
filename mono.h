#pragma once

#include "defines.h"

#include "mono/types/object.h"
#include "mono/types/error.h"
#include "mono/types/string.h"

#include "mono/image.h"
#include "mono/assembly.h"
#include "mono/domain.h"

#include "mono/klass/klass.h"

class CMono : CMonoObject {
public:
	CMono() {
		this->Initialize();
	}

	CMonoKlass* GetClass(
		const char* szClassName,
		const char* szNameSpace = "",
		const char* szAssemblyName = "Assembly-CSharp"
	) {
		auto pImage = this->GetImage(szAssemblyName);

		auto pClass =
			MonoClassFromName(
				pImage,
				szNameSpace,
				szClassName
			);

		std::cout << "[+] Found " << szAssemblyName << "'s class " << szClassName << " at 0x" << (uintptr_t)pClass << std::endl;

		CMonoKlass* klass = new CMonoKlass(
			pClass,
			MonoGetRootDomain()
		);
		return klass;
	}

private:
	MonoAssembly* GetAssembly(
		const char* szAssemblyName
	) {
		auto pDomain = std::make_unique<CMonoDomain>();

		std::cout << "[+] Found " << pDomain->GetFriendlyName() << " (" << pDomain->GetId() << ")" << std::endl;

		return pDomain->OpenAssembly(szAssemblyName);
	}
	MonoImage* GetImage(
		const char* szAssemblyName
	) {
		auto pImage = MonoImageLoaded(szAssemblyName);
		if (!pImage)
			pImage = MonoAssemblyGetImage(
				this->GetAssembly(szAssemblyName)
			);

		return pImage;
	}

	void Initialize() {
		MonoThreadAttach(MonoGetRootDomain());

		std::cout << "[+] Attached!" << std::endl;
	}

	IMPORT(MonoAssemblyGetImage, tMonoAssemblyGetImage, MONO_DLL, "mono_assembly_get_image");
	IMPORT(MonoImageLoaded, tMonoImageLoaded, MONO_DLL, "mono_image_loaded");

	IMPORT(MonoClassFromName, tMonoClassFromName, MONO_DLL, "mono_class_from_name");

	IMPORT(MonoThreadAttach, tMonoThreadAttach, MONO_DLL, "mono_thread_attach");
	IMPORT(MonoGetRootDomain, tMonoGetRootDomain, MONO_DLL, "mono_get_root_domain");

	IMPORT(MonoImageGetTableInfo, tMonoImageGetTableInfo, MONO_DLL, "mono_image_get_table_info");
	IMPORT(MonoImageGetTableRows, tMonoImageGetTableRows, MONO_DLL, "mono_image_get_table_rows");
};