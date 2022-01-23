#ifndef INPUT_MANAGER_H_
#define INPUT_MANAGER_H_

#include <unordered_map>

class Input_Manager
{
public:    
    Input_Manager();
    Input_Manager ( const Input_Manager& ) = delete;
    Input_Manager& operator = ( const Input_Manager& ) = delete;
    ~Input_Manager();

public:
    void key_pressed( const unsigned id );
    void key_released( const unsigned id );

    bool is_key_pressed( const unsigned id ) const noexcept;

private:
    std::unordered_map<unsigned, bool> key_map;

};




#endif /* INPUT_MANAGER_H_ */