#ifndef CAMERA_2D_H_
#define CAMERA_2D_H_

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

class Camera_2D
{
public:
    Camera_2D();
    Camera_2D (const Camera_2D&) = delete;
    Camera_2D& operator = ( const Camera_2D& ) = delete;
    ~Camera_2D();

public:
    void init( const int sw, const int sh );
    void update();

    float get_scale() const noexcept;
    void  set_scale( const float& scale );

    glm::vec2 get_position() const noexcept;
    void      set_position( const glm::vec2& pos );

    glm::mat4 get_cam_matrix() const noexcept;
    
private:
    int   screen_width;
    int   screen_height;
    bool  update_required;
    float scale;
    glm::vec2 position;
    glm::mat4 cam_mat;
    glm::mat4 ortho_mat;
};




#endif /* CAMERA_2D_H_ */