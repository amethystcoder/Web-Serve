#pragma once
#include <unordered_map>
#include <memory>
#include <functional>
#include "ast.h"


// Factory class
class ASTNodeFactory {
public:
    using CreatorFunc = std::function<std::shared_ptr<ASTreeNode>()>;


    static ASTNodeFactory& getInstance() {
        static ASTNodeFactory instance;
        return instance;
    }

    void registerClass(const std::string& name, CreatorFunc creator) {
        registry[name] = std::move(creator);
    }


    std::shared_ptr<ASTreeNode> create(const std::string& name) {
        auto it = registry.find(name);
        if (it != registry.end()) {
            return it->second();
        }
        return nullptr; // Return nullptr if the class name is not found
    }


private:
    std::unordered_map<std::string, CreatorFunc> registry;
    ASTNodeFactory() = default; // Private constructor for singleton pattern
};