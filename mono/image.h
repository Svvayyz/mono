class CMonoImage : CMonoObject {
public:
	MonoImage* m_pImage = nullptr;
	MonoDomain* m_pAppDomain = nullptr;

	CMonoImage(
		MonoImage* pImage,
		MonoDomain* pDomain
	) {
		m_pImage = pImage;
		m_pAppDomain = pDomain;
	}

	CMonoKlass* GetKlass(
		const char* szClassName,
		const char* szNameSpace = ""
	) {
		MonoClass* klass = MonoClassFromName(
			m_pImage,
			szNameSpace,
			szClassName
		);

		return new CMonoKlass(
			klass,
			m_pAppDomain
		);
	}

private:
	IMPORT(MonoClassFromName, tMonoClassFromName, MONO_DLL, "mono_class_from_name");
};