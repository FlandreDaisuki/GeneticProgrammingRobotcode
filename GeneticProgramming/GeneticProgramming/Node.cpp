#include "Node.h"
#include "RandomRange.h"
#include <map>
#include <iostream>

Node::Node(const std::string &type) : type_(type)
{
	Ruleset syntax = Node::GrowthRule(type);
	const std::size_t index = RandomRange::random<int>(0, syntax.size() - 1);
	for (const std::string i : syntax[index])
	{
		child_.push_back(i);
	}
}

const Ruleset &Node::GrowthRule(const std::string &type)
{
	static std::map<std::string, Ruleset> Rule;
	Rule["ifstatement"] = Ruleset { {"boolexpression", "statements", "statements"} };
	Rule["boolexpression"] = Ruleset { {"null"} };
	Rule["statements"] = Ruleset { { "null" } };
	Rule["null"] = Ruleset { {} };
	
	return Rule[type];
}

const std::size_t Node::numberOfChildren() const 
{ 
	return child_.size(); 
}

void Node::addChild(const Node &child) 
{ 
	child_.push_back(child); 
}

void Node::addChild(const std::string &child)
{
	child_.push_back(Node(child));
}

const Node *Node::child(const std::size_t index) const 
{ 
	return &child_[index]; 
}

Node *Node::child(const std::size_t index) 
{ 
	return &child_[index]; 
}

const std::string &Node::getData() const 
{ 
	return data_; 
}

const std::string &Node::getType() const
{
	return type_;
}