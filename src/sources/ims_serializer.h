#include <yaml-cpp/yaml.h>

#define KEY(o, a, b)		(o) << YAML::Key << (a) << YAML::Value << (b)
#define BEGIN_FSEQ(o, a)	(o) << YAML::Key << (a) << YAML::Value << YAML::Flow << YAML::BeginSeq
#define BEGIN_BSEQ(o, a)	(o) << YAML::Key << (a) << YAML::Value << YAML::Block << YAML::BeginSeq
#define SEQ_VALUE(o, a)		(o) << (a)
#define END_SEQ(o)			(o) << YAML::EndSeq
#define BEGIN_MAP(o, a)		(o) << YAML::Key << (a) << YAML::Value << YAML::BeginMap
#define END_MAP(o)			(o) << YAML::EndMap
#define REGION(o, a, b)		(o) << YAML::Key << ("$" a "$") << YAML::Value << (b)
#define REGION_VER(o, a, b)	((o)[("$" a "$")] && ((o)[("$" a "$")].as<int>() == (b)))


namespace ImStudio
{
	struct GUI;
	class BufferWindow;
	class Object;
	class BaseObject;

	class Serializer
	{
	public:
		static int SaveBaseObject(YAML::Emitter& out, BaseObject& obj);
		static int SaveObject(YAML::Emitter& out, Object& obj);
		static int SaveBuffer(YAML::Emitter& out, BufferWindow& bw);
		static int SaveGUI(YAML::Emitter& out, GUI& gui);
		static int SaveProject(GUI& gui);
	};
}
