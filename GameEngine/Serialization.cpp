#include "Serialization.hpp" 
namespace Solar
{
	/*
	TODO : Begin working on the Deserializer
	auto* Deserialize(std::string Serial)
	{
		
	}
	*/
	std::string Serialize(Frame* obj)
	{
		std::string os = "\"Type\": \"Folder\" {";
		//Position
		os.append("\"Position\": {");
		os.append(std::to_string(obj->Position.x.scale) + ",");
		os.append(std::to_string(obj->Position.x.offset) + ",");
		os.append(std::to_string(obj->Position.y.scale) + ",");
		os.append(std::to_string(obj->Position.y.offset) + "}");

		//Size
		os.append("\"Size\": {");
		os.append(std::to_string(obj->Size.x.scale) + ",");
		os.append(std::to_string(obj->Size.x.offset) + ",");
		os.append(std::to_string(obj->Size.y.scale) + ",");
		os.append(std::to_string(obj->Size.y.offset) + "}");

		//Background Transparency
		os.append("\"BackgroundTransparency\": ");
		os.append(std::to_string(obj->Transparency) + ",");

		//Background Color
		os.append("\"BackgroundColor\": {");
		os.append(std::to_string(obj->BackgroundColor.getRed()) + ",");
		os.append(std::to_string(obj->BackgroundColor.getGreen()) + ",");
		os.append(std::to_string(obj->BackgroundColor.getBlue()) + "}");

		//Border Size
		os.append("\"BorderSize\": ");
		os.append(std::to_string(obj->BorderSize) + ",");


		os.append("}");
		return os;
	}
}
