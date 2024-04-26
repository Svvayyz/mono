class CMonoField : CMonoObject {
public:
	MonoObject* m_pKlassInstance = nullptr;
	MonoClassField* m_pField = nullptr;

	CMonoField(
		MonoObject* pKlassInstance,
		MonoClassField* pField
	) {
		m_pKlassInstance = pKlassInstance;
		m_pField = pField;
	}

	template<typename T>
	T Get() {
		T pOut;
		MonoFieldGetValue(
			m_pKlassInstance,
			m_pField,
			&pOut
		);

		return pOut;
	}

	void Set(MonoObject* vVar, void* pValue) {
		return MonoFieldSetValue(
			m_pKlassInstance,
			m_pField,
			pValue
		);
	}

	uintptr_t GetOffset() {
		return MonoFieldGetOffset(m_pField);
	}

	const char* GetName() {
		return MonoFieldGetName(m_pField);
	}

private:
	IMPORT(MonoFieldGetName, tMonoFieldGetName, MONO_DLL, "mono_field_get_name");

	IMPORT(MonoFieldGetValue, tMonoFieldGetValue, MONO_DLL, "mono_field_get_value");
	IMPORT(MonoFieldSetValue, tMonoFieldSetValue, MONO_DLL, "mono_field_set_value");
	IMPORT(MonoFieldGetOffset, tMonoFieldGetOffset, MONO_DLL, "mono_field_get_offset");
};