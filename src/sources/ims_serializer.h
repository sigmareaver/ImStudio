
namespace ImStudio
{
	struct GUI;
	struct BufferWindow;
	struct Object;

	class Serializer
	{
	public:
		static int SaveGUI(GUI& gui);
		static int SaveBuffer(ImStudio::BufferWindow& bw);
		static int SaveObject(Object& obj);
		static int SaveProject(GUI& gui);
	};
}
