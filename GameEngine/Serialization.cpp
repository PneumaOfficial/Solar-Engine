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
		std::string os = "\"Type\": \"Frame\" {";
		//Position
		os.append("\"Position\": {");
		os.append(std::to_string(obj->Position.x.scale) + ",");
		os.append(std::to_string(obj->Position.x.offset) + ",");
		os.append(std::to_string(obj->Position.y.scale) + ",");
		os.append(std::to_string(obj->Position.y.offset) + "},");

		//Size
		os.append("\"Size\": {");
		os.append(std::to_string(obj->Size.x.scale) + ",");
		os.append(std::to_string(obj->Size.x.offset) + ",");
		os.append(std::to_string(obj->Size.y.scale) + ",");
		os.append(std::to_string(obj->Size.y.offset) + "},");

		//Background Transparency
		os.append("\"BackgroundTransparency\": ");
		os.append(std::to_string(obj->BackgroundTransparency) + ",");

		//Background Color
		os.append("\"BackgroundColor\": {");
		os.append(std::to_string(obj->BackgroundColor.getRed()) + ",");
		os.append(std::to_string(obj->BackgroundColor.getGreen()) + ",");
		os.append(std::to_string(obj->BackgroundColor.getBlue()) + "},");

		//Border Size
		os.append("\"BorderSize\": ");
		os.append(std::to_string(obj->BorderSize) + ",");

		os.append("\"Children\": {");
		for (auto& x : obj->children) {
			if (x.second->Type == "Frame")
				os.append(Serialize((Frame*)x.second));
			if (x.second->Type == "Folder")
				os.append(Serialize((Folder*)x.second));
		}

		os.append("}");
		return os;
	}

	std::string Serialize(Folder* obj)
	{
		std::string os = "\"Type\": \"Folder\" {";
		//Children
		os.append("\"Children\": {");
		for (auto& x : obj->children) {
			if(x.second->Type == "Frame")
				os.append(Serialize((Frame*)x.second));
			if(x.second->Type == "Folder")
				os.append(Serialize((Folder*)x.second));
		}
		os.append("}");

		os.append("}");
		return os;
	}
}
