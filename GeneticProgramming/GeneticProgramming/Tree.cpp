#include "Tree.h"
#include <iostream>
#include <fstream>

Tree::Tree(const std::string &type, const int level) : root_(type, level)
{
}

void Tree::exportTo(const char *filename) const
{
	std::ofstream fout;
	fout.open(filename);
	fprint(fout, this->root());
	fout.close();
}

void Tree::fprint(std::ofstream &fout, const Node *node) const
{
	fout << node->getLevel() << " "
	     << node->getType() << " "
	     << node->getData() << " "
	     << node->numberOfChildren() << " "
	     << node->willExpand() << std::endl;

	for (std::size_t i = 0; i < node->numberOfChildren(); i += 1)
	{
		fprint(fout, node->child(i));
	}
}

void Tree::importFrom(const char *filename)
{
	std::ifstream fin;
	fin.open(filename);
	fscan(fin, root());
	fin.close();
}

void Tree::fscan(std::ifstream &fin, Node *node)
{
	int lv, nchild, toexp;
	std::string type, data;
	fin >> lv >> type >> data >> nchild >> toexp;
	node->reset(lv, type, data, (toexp > 0));

	for (std::size_t i = 0; i < nchild; i += 1)
	{
		Node x;
		node->getChildrenNodes().push_back(x);
		fscan(fin, node->child(i));
	}
}

void Tree::print() const
{
	std::cout << "[Root " << root_.getLevel() << "] " << root_.getType() << " " << root_.willExpand() << std::endl;
	for (std::size_t i = 0; i < root_.numberOfChildren(); i += 1)
	{
		print(root_.child(i));
	}
}

void Tree::print(const Node *node) const
{
	const std::string space = "  ";
	for (std::size_t i = 0; i < node->getLevel(); i += 1)
	{
		std::cout << space;
	}
	std::cout << "[Node " << node->getLevel() << "] " << node->getType() << " " << node->willExpand() << std::endl;
	for (std::size_t i = 0; i < node->numberOfChildren(); i += 1)
	{
		print(node->child(i));
	}
}

void Tree::parse() const
{
	if (root_.willExpand())
	{
		std::cout << root_.getType() << std::endl;
	}
	for (std::size_t i = 0; i < root_.numberOfChildren(); i += 1)
	{
		parse(root_.child(i));
	}
}

void Tree::parse(const Node *node, const bool withNewLine, int indent) const
{
	if (node->willExpand())
	{
		for (std::size_t i = 0; i < indent; i += 1)
		{
			std::cout << " ";
		}
		if (node->getType() == "whileStatement" && node->numberOfChildren() == 2)
		{
			std::cout << "while ( ";
			parse(node->child(0), false, 0);
			std::cout << " ) {" << std::endl;
			indent += 4;
			parse(node->child(1), true, indent);
			indent -= 4;
			for (std::size_t i = 0; i < indent; i += 1)
			{
				std::cout << " ";
			}
			std::cout << "}" << std::endl;
		}
		else if (node->getType() == "ifStatement" && node->numberOfChildren() == 2)
		{
			std::cout << "if ( ";
			parse(node->child(0), false, 0);
			std::cout << " ) {" << std::endl;
			indent += 4;
			parse(node->child(1), true, indent);
			indent -= 4;
			for (std::size_t i = 0; i < indent; i += 1)
			{
				std::cout << " ";
			}
			std::cout << "}" << std::endl;
		}
		else if (node->getType() == "elseIfStatement" && node->numberOfChildren() == 2)
		{
			std::cout << "else if ( ";
			parse(node->child(0), false, 0);
			std::cout << " ) {" << std::endl;
			indent += 4;
			parse(node->child(1), true, indent);
			indent -= 4;
			for (std::size_t i = 0; i < indent; i += 1)
			{
				std::cout << " ";
			}
			std::cout << "}" << std::endl;
		}
		else if (node->getType() == "elseStatement" && node->numberOfChildren() == 1)
		{
			std::cout << "else {" << std::endl;
			indent += 4;
			parse(node->child(0), true, indent);
			indent -= 4;
			for (std::size_t i = 0; i < indent; i += 1)
			{
				std::cout << " ";
			}
			std::cout << "}" << std::endl;
		}
		else
		{
			if (withNewLine)
			{
				std::cout << node->getType() << std::endl;
			}
			else
			{
				std::cout << node->getType();
			}
			for (std::size_t i = 0; i < node->numberOfChildren(); i += 1)
			{
				parse(node->child(i), withNewLine, indent);
			}
		}
	}
	else
	{
		for (std::size_t i = 0; i < node->numberOfChildren(); i += 1)
		{
			parse(node->child(i), withNewLine, indent);
		}
	}
}

