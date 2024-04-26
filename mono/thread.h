class CMonoThread : CMonoObject {
public:
	MonoDomain* m_pAppDomain = nullptr;

	CMonoThread(MonoDomain* pAppDomain) {
		m_pAppDomain = pAppDomain;
	}

	void Attach() {
		MonoThreadAttach(m_pAppDomain);
	}

private:
	IMPORT(MonoThreadAttach, tMonoThreadAttach, MONO_DLL, "mono_thread_attach");
};