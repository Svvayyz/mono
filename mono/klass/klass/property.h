class CMonoProperty : CMonoObject {
public:
	MonoProperty* m_pProperty;
	MonoObject* m_pKlassInstance;

	CMonoProperty(
		MonoProperty* pProperty,
		MonoObject* pKlassInstance
	) {
		m_pProperty = pProperty;
		m_pKlassInstance = pKlassInstance;
	}

	const char* GetName() {
		return MonoPropertyGetName(m_pProperty);
	}

	void* GetPtr(void** args = nullptr) {
		MonoObject* oOut = MonoPropertyGetValue(
			m_pProperty,
			m_pKlassInstance,
			args,
			nullptr
		);
		void* pOut = MonoObjectUnbox(oOut);

		return pOut;
	}

	template<typename T>
	T Get(void** args = nullptr) {
		return CAST(GetPtr(), T);
	}
	void Set(void** args) {
		MonoPropertySetValue(
			m_pProperty,
			m_pKlassInstance,
			args,
			nullptr
		);
	}

private:
	IMPORT(MonoPropertyGetName, tMonoPropertyGetName, MONO_DLL, "mono_property_get_name");

	IMPORT(MonoPropertyGetValue, tMonoPropertyGetValue, MONO_DLL, "mono_property_get_value");
	IMPORT(MonoPropertySetValue, tMonoPropertySetValue, MONO_DLL, "mono_property_set_value");

	IMPORT(MonoObjectNew, tMonoObjectNew, MONO_DLL, "mono_object_new");
	IMPORT(MonoObjectUnbox, tMonoObjectUnbox, MONO_DLL, "mono_object_unbox");
};
