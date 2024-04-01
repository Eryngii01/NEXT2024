#ifndef _COMPONENT_H
#define _COMPONENT_H

#include <string>
#include <vector>
#include "GameManager.h"

//*******************************************************************************************
// Component
//*******************************************************************************************
/* Interface of a component to be implemented by all component classes. Stores data
 * concerning the enabled status of the component and exposes methods to get/set it.
 * Also provides public methods to package data and send it to the component through
 * the GameObject to support Object Pooling.
 */

class Component {

public:
	explicit Component(int newID, bool isActive) : ID(newID), isEnabled(isActive) {}

	virtual ~Component() = default;

	//===========================================================================================
	// Getters/Setters
	//===========================================================================================
#pragma region Getters/Setters

	bool IsEnabled() const {
		return this->isEnabled;
	}

	void SetActivity(const bool status) {
		this->isEnabled = status;
	}

#pragma endregion

	//===========================================================================================
	// Object Pooling
	//===========================================================================================
#pragma region Object Pooling

	// -> Really gross, there are definitely better ways of handling this
	// Use polymorphism to handle setting the data of a component freshly taken out of a pool; multiple overloads
	virtual void SetData(GameManager& gameManager, std::vector<float>& args) {}
	virtual void SetData(std::vector<int>& args) {}
	virtual void SetData(GameManager& gameManager, std::vector<int>& args) {}
	virtual void SetData(GameManager& gameManager, std::vector<int>& intArgs, std::vector<float>& floatArgs) {}
	virtual void SetData(GameManager& gameManager, std::vector<std::string>& args) {}
	virtual void SetData(std::vector<Vector2>& args) {}
	virtual void SetData(GameManager& gameManager) {}

#pragma endregion

	int ID;

protected:
	// Override this in a child component class to specify a specific behaviour when enabling the component
	virtual void OnEnable() {}

	bool isEnabled;
};
#endif

