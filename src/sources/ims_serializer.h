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
	private:
		static int SaveBaseObject(YAML::Emitter& out, BaseObject& obj);
		static int SaveObject(YAML::Emitter& out, Object& obj);
		static int SaveBuffer(YAML::Emitter& out, BufferWindow& bw);
		static int SaveGUI(YAML::Emitter& out, GUI& gui);

		static int LoadBaseObject(YAML::detail::iterator_value& it, Object& obj);
		static int LoadObject(YAML::detail::iterator_value& it, Object& obj);
		static int LoadBuffer(YAML::Node& node, ImStudio::BufferWindow& bw);
		static int LoadGUI(YAML::Node& node, GUI& gui);
	public:
		static int SaveProjectAs(GUI& gui);
		static int SaveProject(GUI& gui);
		static int LoadProjectDlg();
		static int LoadProject(GUI& gui);
	};
}
