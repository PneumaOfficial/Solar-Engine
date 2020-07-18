#pragma once
#include <SFML/Graphics.hpp>
#include "DataTypes.hpp"
#include <functional>
#include <iostream>
#include <string>
#include <unordered_map>

#define nil NULL

namespace Solar {
	class Instance;

	struct EventStruct
	{
		std::string EventName;
		std::function<void()> StoredFunction;
	};

	constexpr unsigned int hashstring(const char* str, int h = 0)
	{
		return !str[h] ? 5381 : (hashstring(str, h + 1) * 33) ^ str[h];
	}

	class Instance {
		friend Instance;
		int ID;
		int childrenMemory = 0;
	public:

		void setParent(std::unique_ptr<Instance> Parent)
		{
			this->Parent->children.erase(this->ID);
			Parent->childrenMemory++;
			this->ID = Parent->childrenMemory;
			Parent->children[Parent->childrenMemory] = std::make_unique<Instance>(this);
			this->Parent = std::make_unique<Instance>(Parent);
		}

		sf::RectangleShape _body;
		virtual void Render(float dt, sf::RenderTexture* target) = 0;
		virtual void Tick(float dt) = 0;

		auto FindFirstChild(std::string childname)
		{
			for (auto& x : this->children) {
				if (x.second->Name == childname)
					return &x.second;
			}
		}
		//Events

		virtual void HandleEvents() = 0;
		
		void FireEvent(std::string Event)
		{
			for (auto& x : this->EventQueue)
				if (x.second.EventName == Event)
					x.second.StoredFunction();
		};

		void HookEvent(std::string Event, std::function<void()> function)
		{
			EventStruct fun;
			fun.StoredFunction = function;
			fun.EventName = Event;
			this->EventQueue.emplace(this->EventQueue.size() + 1, fun);
		}

		std::map<int, EventStruct> EventQueue;
		
		std::string Name;
		std::string Type;
		bool Enabled = true;
		std::unique_ptr<Instance> Parent;
		std::unordered_map<int, std::unique_ptr<Instance>> children;

		bool Locked; //Determines if instance can be destroyed by normal means

	};
};