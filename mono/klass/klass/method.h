class CMonoMethod : CMonoObject {
public:
	MonoMethod* m_pMethod = nullptr;
	MonoObject* m_pKlassInstance = nullptr;

	CMonoMethod(
		MonoMethod* pMethod,
		MonoObject* pKlassInstance
	) {
		m_pMethod = pMethod;
		m_pKlassInstance = pKlassInstance;
	}

	template<typename T>
	T Invoke(
		void** pArgs = nullptr
	) {
		MonoObject* oErr = nullptr;

		auto res = MonoRuntimeInvoke(
			m_pMethod,
			m_pKlassInstance,
			pArgs,
			&oErr
		);

		if (!res)
			return nullptr;

		return CAST(res, T);
	}

	MonoObject* Invoke(
		void** pArgs = nullptr
	) {
		MonoThreadAttach(MonoGetRootDomain());

		MonoObject* oErr;
		MonoObject* oRes = MonoRuntimeInvoke(
			m_pMethod,
			m_pKlassInstance,
			pArgs,
			&oErr
		);

		if (!oRes)
			return nullptr;

		return oRes;
	}

	void* GetPtr() {
		return MonoCompileMethod(m_pMethod);
	}

private:
	IMPORT(MonoRuntimeInvoke, tMonoRuntimeInvoke, MONO_DLL, "mono_runtime_invoke");

	IMPORT(MonoThreadAttach, tMonoThreadAttach, MONO_DLL, "mono_thread_attach");
	IMPORT(MonoGetRootDomain, tMonoGetRootDomain, MONO_DLL, "mono_get_root_domain");

	IMPORT(MonoCompileMethod, tMonoCompileMethod, MONO_DLL, "mono_compile_method");
};