class CMonoStaticField : CMonoObject {
public:
	CMonoField* m_cField;
	MonoClass* m_pKlass;
	MonoDomain* m_pAppDomain;

	CMonoStaticField(
		CMonoField* cField,
		MonoClass* pKlass,
		MonoDomain* pAppDomain
	) {
		m_cField = cField;
		m_pKlass = pKlass;
		m_pAppDomain = pAppDomain;
	}

	void Set(void* vValue) {
		uintptr_t nAddress = (uintptr_t)MonoVTableGetStaticFieldData(
			m_pAppDomain,
			m_pKlass
		);
		uintptr_t nOffset = m_cField->GetOffset();

		void* v = (void*)(nAddress + nOffset);
		v = vValue;
	}

	template<typename T>
	T Get() {
		uintptr_t nAddress = (uintptr_t)MonoVTableGetStaticFieldData(
			m_pAppDomain,
			m_pKlass
		);
		uintptr_t nOffset = m_cField->GetOffset();

		void* ptr = (void*)(nAddress + nOffset);

		return (T)ptr;
	}

private:
	IMPORT(MonoVTableGetStaticFieldData, tMonoVTableGetStaticFieldData, MONO_DLL, "mono_vtable_get_static_field_data");
};