#pragma once

#include <memory>
#include <stack>

#include "State.hpp"

namespace Solar {
	typedef std::unique_ptr<State> StateRef;

	class StateMachine {
	public:
		StateMachine() 
		{
			this->_isRemoving = false;
			this->_isAdding = false;
			this->_isReplacing = false;
		}
		~StateMachine() {}

		void AddState(StateRef newState, bool isReplacing = true);
		void RemoveState();
		void ProcessStateChanges();

		StateRef& GetActiveState();

	private:
		std::stack<StateRef> _states;
		StateRef _newState;

		bool _isRemoving;
		bool _isAdding;
		bool _isReplacing;
	};
}