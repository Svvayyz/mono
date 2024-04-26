class CMonoDomain : CMonoObject {
public:
	MonoDomain* m_pDomain = nullptr;
	CMonoThread* m_pThread = nullptr;

	CMonoDomain() {
		m_pDomain = MonoGetRootDomain();
		m_pThread = new CMonoThread(
			m_pDomain
		);

		Attach();
	}
	CMonoDomain(MonoDomain* pDomain) {
		m_pDomain = pDomain;
		m_pThread = new CMonoThread(
			m_pDomain
		);

		Attach();
	}

	void Attach() {
		m_pThread->Attach();
	}

	const char* GetFriendlyName() {
		return MonoDomainGetFriendlyName(m_pDomain);
	}

	int GetId() {
		return MonoDomainGetId(m_pDomain);
	}

	MonoAssembly* OpenAssembly(const char* szAssemblyName = "Assembly-CSharp") {
		return MonoDomainAssemblyOpen(m_pDomain, szAssemblyName);
	}

	class CMonoAssemblyListResponse {
	public:
		std::vector<MonoAssembly*> m_vecAssemblies;
	};

	static void Processor(MonoAssembly* pAssembly, void* pData) {
		CMonoAssemblyListResponse* response = reinterpret_cast<CMonoAssemblyListResponse*>(pData);
		response->m_vecAssemblies.push_back(pAssembly);

		CMonoAssembly* monoasm = new CMonoAssembly(pAssembly);
		std::cout << monoasm->GetName() << std::endl;
	}

	void GetAssemblies() {
		CMonoAssemblyListResponse response;
		MonoDomainAssemblyForeach(m_pDomain, Processor, &response);

		std::cout << "[+] Found " << response.m_vecAssemblies.size() << " assemblies " << std::endl;
	}

private:
	IMPORT(MonoGetRootDomain, tMonoGetRootDomain, MONO_DLL, "mono_get_root_domain");

	IMPORT(MonoDomainGetFriendlyName, tMonoDomainGetFriendlyName, MONO_DLL, "mono_domain_get_friendly_name");
	IMPORT(MonoDomainGetId, tMonoDomainGetId, MONO_DLL, "mono_domain_get_id");

	IMPORT(MonoDomainAssemblyOpen, tMonoDomainAssemblyOpen, MONO_DLL, "mono_domain_assembly_open");
	IMPORT(MonoDomainAssemblyForeach, tMonoDomainAssemblyForeach, MONO_DLL, "mono_domain_assembly_foreach");
};