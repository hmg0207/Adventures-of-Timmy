#include "Input_Manager.h"

Input_Manager::Input_Manager()
{}

Input_Manager::~Input_Manager()
{}

void Input_Manager::key_pressed( const unsigned id )
{
    this->key_map[id] = true;
}

void Input_Manager::key_released( const unsigned id )
{
    this->key_map[id] = false;
}

bool Input_Manager::is_key_pressed( const unsigned id ) const noexcept
{
    auto idx = this->key_map.find(id);
    if ( idx != this->key_map.end() )
    {
        return idx->second;
    }
    else
    {
        return false;
    }
}