class CMonoStaticField : CMonoObject {
public:
	MonoDomain* m_pDomain;
	MonoClass* m_pKlass;
	CMonoField* m_cField;

	CMonoStaticField(
		MonoDomain* pDomain,
		MonoClass* pKlass,
		CMonoField* cField
	) {
		m_pDomain = pDomain;
		m_pKlass = pKlass;
		m_cField = cField;
	}

	void Set(void* vValue) {
		uintptr_t nAddress = (uintptr_t)MonoVTableGetStaticFieldData(
			m_pDomain,
			m_pKlass
		);
		uintptr_t nOffset = m_cField->GetOffset();

		void* v = (void*)(nAddress + nOffset);
		v = vValue;
	}

	template<typename T>
	T Get() {
		uintptr_t nAddress = (uintptr_t)MonoVTableGetStaticFieldData(
			m_pDomain,
			m_pKlass
		);
		uintptr_t nOffset = m_cField->GetOffset();

		void* ptr = (void*)(nAddress + nOffset);

		return (T)ptr;
	}

private:
	IMPORT(MonoVTableGetStaticFieldData, tMonoVTableGetStaticFieldData, MONO_DLL, "mono_vtable_get_static_field_data");
};