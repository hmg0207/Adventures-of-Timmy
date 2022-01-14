#include "Camera_2D.h"

#include "Kerror.h"

Camera_2D::Camera_2D()
    :
    screen_width(800),
    screen_height(600),
    update_required(true),
    scale(1.0f),
    position( { 0.0f, 0.0f } ),
    cam_mat( 1.0f ),
    ortho_mat( 1.0f )
{
    KNOTICE( "Camera Created." );
}


Camera_2D::~Camera_2D()
{
    KNOTICE( "Camera Destroyed." );
}

void Camera_2D::init( const int sw, const int sh )
{
    this->screen_width = sw;
    this->screen_height = sh;
    this->ortho_mat = glm::ortho( 0.0f, (float)this->screen_width, 0.0f, (float)this->screen_height );
}


void Camera_2D::update()
{
    if ( update_required )
    {                       
        this->cam_mat = glm::translate( this->ortho_mat, glm::vec3( -this->position.x + this->screen_width / 2,
                                                                    -this->position.y + this->screen_height / 2,
                                                                    0.0f ) );
        this->cam_mat *= glm::scale( glm::mat4(1.0f), glm::vec3( this->scale, this->scale, 0.0f ) );
        this->update_required = false;
    }
}

float Camera_2D::get_scale() const noexcept
{
    return this->scale;
}

void Camera_2D::set_scale( const float& scale )
{
    this->scale = scale;
    this->update_required = true;
}

glm::vec2 Camera_2D::get_position() const noexcept
{
    return this->position;
}

void Camera_2D::set_position( const glm::vec2& pos )
{
    this->position = pos;
    this->update_required = true;
}

glm::mat4 Camera_2D::get_cam_matrix() const noexcept
{
    return this->cam_mat;
}