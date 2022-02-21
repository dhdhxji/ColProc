#ifndef VARIABLE_DECLARATION_H
#define VARIABLE_DECLARATION_H

#include <string>

#define MAKE_VAR_DECL(type, name)\
    VariableDeclaration( typeid( type ), (#name) )


class VariableDeclaration 
{
public:
    VariableDeclaration(const std::type_info& type, std::string name)
    : _type(type), _name(name) {}

    const std::type_info& type() const {
        return _type;
    }

    const std::string& name() const {
        return _name;
    }

protected: 
    const std::type_info& _type;
    const std::string _name;
};

#endif // VARIABLE_DECLARATION_H
