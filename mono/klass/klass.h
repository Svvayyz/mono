#include "klass/method.h"
#include "klass/field.h"
#include "klass/static_field.h"
#include "klass/property.h"

class CMonoKlass : CMonoObject {
public:
	MonoClass* m_pKlass = nullptr;
	MonoObject* m_pKlassInstance = nullptr;
	MonoDomain* m_pAppDomain = nullptr;

	CMonoKlass(
		MonoClass* pKlass,
		MonoDomain* pAppDomain,
		MonoObject* pKlassInstance = nullptr
	) {
		m_pKlass = pKlass;
		m_pAppDomain = pAppDomain;

		if (pKlassInstance == nullptr) {
			//m_pKlassInstance = MonoObjectNew(
			//	m_pAppDomain,
			//	m_pKlass
			//);

			//MonoRuntimeObjectInit(
			//	m_pKlassInstance
			//);
		}
		else {
			m_pKlassInstance = pKlassInstance;
		}
	}

	int GetEventsCount() {
		return MonoClassNumEvents(m_pKlass);
	}
	int GetFieldsCount() {
		return MonoClassNumFields(m_pKlass);
	}
	int GetMethodsCount() {
		return MonoClassNumMethods(m_pKlass);
	}
	int GetPropertiesCount() {
		return MonoClassNumProperties(m_pKlass);
	}

	const char* GetName() {
		return MonoClassGetName(m_pKlass);
	}
	const char* GetNamespace() {
		return MonoClassGetNamespace(m_pKlass);
	}

	CMonoMethod* GetMethod(std::string szMethodName, int nParamCount = 0) {
		MonoMethod* pMethod = MonoClassGetMethodFromName(m_pKlass, szMethodName.c_str(), nParamCount);

		return new CMonoMethod(pMethod, m_pKlassInstance);
	}
	MonoVTable* GetVTable() {
		return MonoClassVTable(m_pAppDomain, m_pKlass);
	}

	CMonoField* GetField(const char* szFieldName) {
		MonoClassField* pField = MonoClassGetFieldFromName(m_pKlass, szFieldName);

		CMonoField* cField =
			new CMonoField(
				pField,
				m_pKlassInstance
			);
		return cField;
	}
	CMonoStaticField* GetStaticField(const char* szFieldName) {
		return new CMonoStaticField(
			m_pAppDomain,
			m_pKlass,
			GetField(szFieldName)
		);
	}

	std::vector<CMonoField*> GetFields() {
		std::vector<CMonoField*> vecFields;

		if (GetFieldsCount() < 1)
			return vecFields;

		void* iter;

		while (MonoClassField* pField = MonoClassGetFields(m_pKlass, &iter)) {
			CMonoField* field = new CMonoField(
				pField,
				m_pKlassInstance
			);

			const char* xd = field->GetName();
			printf("%s", xd);

			vecFields.push_back(field);
		}

		return vecFields;
	}

	CMonoProperty* GetProperty(const char* szName) {
		MonoProperty* property = MonoClassPropertyGetFromName(m_pKlass, szName);

		return new CMonoProperty(
			property,
			m_pKlassInstance
		);
	}
	std::vector<CMonoProperty*> GetProperties() {
		std::vector<CMonoProperty*> vecProperties;

		if (GetPropertiesCount() < 1)
			return vecProperties;

		void* iter = NULL;

		MonoProperty* pProperty;
		while ((pProperty = MonoClassGetProperties(m_pKlass, &iter))) {
			CMonoProperty* property = new CMonoProperty(
				pProperty,
				m_pKlassInstance
			);

			const char* xd = property->GetName();
			printf("%s", xd);

			vecProperties.push_back(property);
		}

		return vecProperties;
	}

	MonoType* GetType() {
		return MonoClassGetType(m_pKlass);
	}
	void* GetObjectType() {
		return MonoTypeGetObject(m_pAppDomain, GetType());
	}

private:
	IMPORT(MonoObjectNew, tMonoObjectNew, MONO_DLL, "mono_object_new");
	IMPORT(MonoRuntimeObjectInit, tMonoRuntimeObjectInit, MONO_DLL, "mono_runtime_object_init");

	IMPORT(MonoClassGetName, tMonoClassGetName, MONO_DLL, "mono_class_get_name");
	IMPORT(MonoClassGetNamespace, tMonoClassGetNamespace, MONO_DLL, "mono_class_get_namespace");

	IMPORT(MonoClassNumEvents, tMonoClassNumEvents, MONO_DLL, "mono_class_num_events");
	IMPORT(MonoClassNumFields, tMonoClassNumFields, MONO_DLL, "mono_class_num_fields");
	IMPORT(MonoClassNumMethods, tMonoClassNumMethods, MONO_DLL, "mono_class_num_methods");
	IMPORT(MonoClassNumProperties, tMonoClassNumProperties, MONO_DLL, "mono_class_num_properties");

	IMPORT(MonoClassGetFields, tMonoClassGetFields, MONO_DLL, "mono_class_get_fields");
	IMPORT(MonoClassGetFieldFromName, tMonoClassGetFieldFromName, MONO_DLL, "mono_class_get_field_from_name");

	IMPORT(MonoClassGetProperties, tMonoClassGetProperties, MONO_DLL, "mono_class_get_properties");
	IMPORT(MonoClassPropertyGetFromName, tMonoClassGetPropertyFromName, MONO_DLL, "mono_class_get_property_from_name");

	IMPORT(MonoClassGetMethodFromName, tMonoClassGetMethodFromName, MONO_DLL, "mono_class_get_method_from_name");
	IMPORT(MonoClassVTable, tMonoClassVTable, MONO_DLL, "mono_class_vtable");

	IMPORT(MonoClassGetType, tMonoClassGetType, MONO_DLL, "mono_class_get_type");
	IMPORT(MonoTypeGetObject, tMonoTypeGetObject, MONO_DLL, "mono_type_get_object");
};