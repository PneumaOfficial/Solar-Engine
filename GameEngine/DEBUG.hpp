#pragma once
#include "DataTypes.hpp"
#include "Folder.hpp"
#include "Frame.hpp"
namespace Solar
{
	struct DEBUG
	{
	public:
		void Init();
		void HandleEvents();
		void Tick(float dt);
		void Render(float dt);
		void Pause();
		void Play();
		bool getStatus();
	private:
		bool _Active = true;
		bool _Visible = true;
	};
}

