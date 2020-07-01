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
	constexpr
		unsigned int hash(const char* str, int h = 0)
	{
		return !str[h] ? 5381 : (hash(str, h + 1) * 33) ^ str[h];
	}
	class Instance {
	public:

		sf::RectangleShape _body;
		virtual void Render(float dt, sf::RenderTexture* target) = 0;
		virtual void Tick(float dt) = 0;
		void AddChild(Instance* child)
		{
			if (child->Type != "Frame")
			{
				child->_body.setSize(this->_body.getSize());
				child->_body.setPosition(this->_body.getPosition());
			}
			this->children.emplace(this->children.size() + 1, child);
			child->Parent = this;
		};

		auto* FindFirstChild(std::string childname)
		{
			for (auto& x : this->children) {
				if (x.second->Name == childname)
					return x.second;
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
		};

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