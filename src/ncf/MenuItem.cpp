#include "ncf/MenuItem.hpp"

MenuItem::MenuItem()
{
}

MenuItem::MenuItem(
        std::string name,
        std::string description
        ) :
    m_name(name),
    m_description(description)
{
    m_handle = new_item(m_name.c_str(), m_description.c_str());
    if (m_handle == NULL) {
        onError(E_SYSTEM_ERROR);
    }
}

MenuItem::MenuItem(const MenuItem& item) :
    m_name(item.m_name),
    m_description(item.m_description)
{
    m_handle = new_item(m_name.c_str(), m_description.c_str());
    if (m_handle == NULL) {
        throw std::runtime_error("menu item failed");
    }
}

MenuItem::~MenuItem()
{
    free_item(m_handle);
}

MenuItem& MenuItem::operator=(const MenuItem& other)
{
    if (this != &other) {
        m_name = other.m_name;
        m_description = other.m_description;
        m_handle = new_item(m_name.c_str(), m_description.c_str());
        if (m_handle == NULL) {
            throw NCMenuException("Menu item failed: ", E_SYSTEM_ERROR);
        }
    }
    return *this;
}
