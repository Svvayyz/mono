#pragma once

#include "defines.h"

#include "mono/types/object.h"
#include "mono/types/error.h"
#include "mono/types/string.h"

#include "mono/klass/klass.h"

#include "mono/thread.h"

#include "mono/image.h"
#include "mono/assembly.h"
#include "mono/domain.h"

class CMono : CMonoObject {
public:
	CMono() {
		this->Initialize();
	}

	CMonoDomain* RootDomain = nullptr;

	CMonoKlass* GetClass(
		const char* szClassName,
		const char* szNameSpace = "",
		const char* szAssemblyName = "Assembly-CSharp"
	) {
		auto image = this->GetImage(szAssemblyName);

		return image->GetKlass(
			szNameSpace,
			szClassName
		);
	}

	MonoAssembly* GetAssembly(
		const char* szAssemblyName
	) {
		return RootDomain->OpenAssembly(szAssemblyName);
	}
	CMonoImage* GetImage(
		const char* szAssemblyName
	) {
		auto pImage = MonoImageLoaded(szAssemblyName);
		if (!pImage)
			pImage = MonoAssemblyGetImage(
				this->GetAssembly(szAssemblyName)
			);

		return new CMonoImage(
			pImage,
			RootDomain->m_pDomain
		);
	}

private:
	void Initialize() {
		RootDomain = new CMonoDomain();
	}

	IMPORT(MonoAssemblyGetImage, tMonoAssemblyGetImage, MONO_DLL, "mono_assembly_get_image");
	IMPORT(MonoImageLoaded, tMonoImageLoaded, MONO_DLL, "mono_image_loaded");

	IMPORT(MonoImageGetTableInfo, tMonoImageGetTableInfo, MONO_DLL, "mono_image_get_table_info");
	IMPORT(MonoImageGetTableRows, tMonoImageGetTableRows, MONO_DLL, "mono_image_get_table_rows");
};