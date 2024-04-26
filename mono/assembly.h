class CMonoAssembly : CMonoObject {
public:
	CMonoAssembly(MonoAssembly* pAssembly) {
		m_pAssembly = pAssembly;
	}

	const char* GetName() {
		return MonoAssemblyGetName(m_pAssembly)->name;
	}

private:
	MonoAssembly* m_pAssembly = nullptr;

	IMPORT(MonoAssemblyGetName, tMonoAssemblyGetName, MONO_DLL, "mono_assembly_get_name");
};