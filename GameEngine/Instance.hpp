#pragma once
#include <SFML/Graphics.hpp>
#include "DataTypes.hpp"
#include <functional>
#include <iostream>
#include <any>
#include <string>
#define nil NULL

namespace Solar {
	class Instance;
	struct EventStruct
	{
		std::string EventName;
		std::function<void()> StoredFunction;
	};
	class Instance {
	public:

		sf::RectangleShape _body;
		virtual void Render(float dt, sf::RenderTexture* target) = 0;
		virtual void Tick(float dt) = 0;
		virtual void AddChild(Instance* child) = 0;
		Instance* FindFirstChild(std::string childname)
		{
			for (auto& x : this->children) {
				if(x.second->Name == childname)
					return x.second;
			}
		}
		//Events
		virtual void HandleEvents() = 0;
		virtual void FireEvent(std::string Event) = 0;
		virtual void HookEvent(std::string Event, std::function<void()> function) = 0;

		std::map<int, EventStruct> EventQueue;

		std::string Name;
		std::string Type;
		bool Enabled = true;
		int LastID;
		int ID;
		Instance* PreviousParent = nil;
		Instance* Parent = nil;
		std::map <int, Instance*> children;

	};
};