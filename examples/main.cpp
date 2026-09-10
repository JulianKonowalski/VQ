#include <core/Event.hpp>
#include <core/Resource.hpp>
#include <glad/glad.h>
#include <graphics/core/Geometry.hpp>
#include <graphics/core/Shader.hpp>
#include <graphics/texture/Texture2D.hpp>
#include <graphics/texture/TextureCubeMap.hpp>
#include <graphics/transform/ProjectionTransform.hpp>
#include <graphics/transform/RotateTransform.hpp>
#include <graphics/transform/ScaleTransform.hpp>
#include <graphics/transform/TranslateTransform.hpp>
#include <graphics/transform/ViewTransform.hpp>
#include <io/Window.hpp>

/*----------------------------------------------------------------------------*/

static const std::string s_base_resource_path = RESOURCE_PATH;

static vq::graphics::transform::RotateTransform view_rotation;
static vq::graphics::transform::TranslateTransform view_translation;
static vq::graphics::transform::ViewTransform view_transform(view_rotation,
                                                             view_translation);

/*----------------------------------------------------------------------------*/

class WindowKeyHandler : public vq::core::EventHandler<vq::io::KeyEvent> {
  public:
    void handle(vq::io::KeyEvent& event) noexcept override {
        if (event.key == 256) { // GLFW KEY ESC
            event.window.close();
            event.set_handled();
        } else if (event.key == 87) { // GLFW KEY W
            view_translation.translate_on_axis(
                0.1f, view_transform.get_front_vector());
            event.set_handled();
        } else if (event.key == 65) { // GLFW KEY A
            view_translation.translate_on_axis(
                -0.1f, view_transform.get_right_vector());
            event.set_handled();
        } else if (event.key == 83) { // GLFW KEY S
            view_translation.translate_on_axis(
                -0.1f, view_transform.get_front_vector());
            event.set_handled();
        } else if (event.key == 68) { // GLFW KEY D
            view_translation.translate_on_axis(
                0.1f, view_transform.get_right_vector());
            event.set_handled();
        } else if (event.key == 82) { // GLFW KEY R
            auto& resource_manager = vq::core::ResourceManager::get_instance();
            auto shader_handle =
                resource_manager.get_resource<vq::graphics::core::Shader>(
                    "test_shader");
            if (shader_handle.is_valid()) {
                shader_handle.get().reload();
                event.set_handled();
            }
        }
    }
};

class WindowMouseHandler
    : public vq::core::EventHandler<vq::io::MouseDragEvent> {
  public:
    void handle(vq::io::MouseDragEvent& event) noexcept override {
        view_rotation.rotate_on_axis_degrees(0.05f * event.y_position_delta,
                                             view_transform.get_right_vector());
        view_rotation.rotate_on_axis_degrees(
            0.05f * event.x_position_delta,
            vq::graphics::transform::TransformBase::s_world_up);
        event.set_handled();
    }
};

/*----------------------------------------------------------------------------*/

int main(void) {
    vq::io::Window window(
        vq::io::Window::WindowSpecification("VQ Example", 800, 600));
    WindowKeyHandler key_handler;
    WindowMouseHandler mouse_handler;

    window.make_current();
    window.attach_event_handler(key_handler);
    window.attach_event_handler(mouse_handler);

    auto& resource_manager = vq::core::ResourceManager::get_instance();

    resource_manager.load_resource<vq::graphics::core::Geometry>(
        "test_geometry");
    resource_manager.load_resource<vq::graphics::core::Geometry>(
        "skybox_geometry");
    resource_manager.load_resource<vq::graphics::core::Shader>(
        "test_shader",
        std::vector<vq::graphics::core::Shader::ShaderSourceFile>({
            {s_base_resource_path + "shaders/passthrough.vert.glsl",
             vq::graphics::core::Shader::ShaderSourceType::VERTEX},
            {s_base_resource_path + "shaders/passthrough.frag.glsl",
             vq::graphics::core::Shader::ShaderSourceType::FRAGMENT},
        }));
    resource_manager.load_resource<vq::graphics::core::Shader>(
        "skybox_shader",
        std::vector<vq::graphics::core::Shader::ShaderSourceFile>(
            {{s_base_resource_path + "shaders/skybox.vert.glsl",
              vq::graphics::core::Shader::ShaderSourceType::VERTEX},
             {s_base_resource_path + "shaders/skybox.frag.glsl",
              vq::graphics::core::Shader::ShaderSourceType::FRAGMENT}}));
    resource_manager.load_resource<vq::graphics::texture::Texture2D>(
        "test_texture", s_base_resource_path + "textures/uv_test.png");
    resource_manager.load_resource<vq::graphics::texture::TextureCubeMap>(
        "skybox_texture", s_base_resource_path + "textures/skybox/right.jpg",
        s_base_resource_path + "textures/skybox/left.jpg",
        s_base_resource_path + "textures/skybox/top.jpg",
        s_base_resource_path + "textures/skybox/bottom.jpg",
        s_base_resource_path + "textures/skybox/front.jpg",
        s_base_resource_path + "textures/skybox/back.jpg");

    auto test_geometry_handle =
        resource_manager.get_resource<vq::graphics::core::Geometry>(
            "test_geometry");
    auto skybox_geometry_handle =
        resource_manager.get_resource<vq::graphics::core::Geometry>(
            "skybox_geometry");
    auto test_shader_handle =
        resource_manager.get_resource<vq::graphics::core::Shader>(
            "test_shader");
    auto skybox_shader_handle =
        resource_manager.get_resource<vq::graphics::core::Shader>(
            "skybox_shader");
    auto test_texture_handle =
        resource_manager.get_resource<vq::graphics::texture::Texture2D>(
            "test_texture");
    auto skybox_texture_handle =
        resource_manager.get_resource<vq::graphics::texture::TextureCubeMap>(
            "skybox_texture");

    test_geometry_handle.get()
        .set_attribute<vq::graphics::core::Geometry::Attribute::POSITION>(
            {-0.5, -0.5, 0.0, //
             0.5, -0.5, 0.0,  //
             0.0, 0.5, 0.0});
    test_geometry_handle.get()
        .set_attribute<vq::graphics::core::Geometry::Attribute::NORMAL>(
            {0.0, 0.0, 1.0, //
             0.0, 0.0, 1.0, //
             0.0, 0.0, 1.0});
    test_geometry_handle.get()
        .set_attribute<
            vq::graphics::core::Geometry::Attribute::TEXTURE_COORDINATE>(
            {0.0, 0.0, //
             1.0, 0.0, //
             0.5, 1.0});
    test_geometry_handle.get().set_indices({0, 1, 2});

    skybox_geometry_handle.get()
        .set_attribute<vq::graphics::core::Geometry::Attribute::POSITION>(
            {-1.0f, 1.0f,  -1.0f, //
             -1.0f, -1.0f, -1.0f, //
             1.0f,  -1.0f, -1.0f, //
             1.0f,  -1.0f, -1.0f, //
             1.0f,  1.0f,  -1.0f, //
             -1.0f, 1.0f,  -1.0f, //

             -1.0f, -1.0f, 1.0f,  //
             -1.0f, -1.0f, -1.0f, //
             -1.0f, 1.0f,  -1.0f, //
             -1.0f, 1.0f,  -1.0f, //
             -1.0f, 1.0f,  1.0f,  //
             -1.0f, -1.0f, 1.0f,  //

             1.0f,  -1.0f, -1.0f, //
             1.0f,  -1.0f, 1.0f,  //
             1.0f,  1.0f,  1.0f,  //
             1.0f,  1.0f,  1.0f,  //
             1.0f,  1.0f,  -1.0f, //
             1.0f,  -1.0f, -1.0f, //

             -1.0f, -1.0f, 1.0f, //
             -1.0f, 1.0f,  1.0f, //
             1.0f,  1.0f,  1.0f, //
             1.0f,  1.0f,  1.0f, //
             1.0f,  -1.0f, 1.0f, //
             -1.0f, -1.0f, 1.0f, //

             -1.0f, 1.0f,  -1.0f, //
             1.0f,  1.0f,  -1.0f, //
             1.0f,  1.0f,  1.0f,  //
             1.0f,  1.0f,  1.0f,  //
             -1.0f, 1.0f,  1.0f,  //
             -1.0f, 1.0f,  -1.0f, //

             -1.0f, -1.0f, -1.0f, //
             -1.0f, -1.0f, 1.0f,  //
             1.0f,  -1.0f, -1.0f, //
             1.0f,  -1.0f, -1.0f, //
             -1.0f, -1.0f, 1.0f,  //
             1.0f,  -1.0f, 1.0f});

    unsigned int model_matrix_uniform_location =
        test_shader_handle.get().get_uniform_location("u_model_matrix");

    unsigned int view_matrix_uniform_location =
        skybox_shader_handle.get().get_uniform_location("u_view_matrix");
    unsigned int projection_matrix_uniform_location =
        skybox_shader_handle.get().get_uniform_location("u_projection_matrix");

    vq::graphics::transform::RotateTransform rotate_transform;
    vq::graphics::transform::TranslateTransform translate_transform;
    vq::graphics::transform::PerspectiveProjection projection_transform(
        40.0f, 100.0f, 0.01f,
        window.get_specification().width /
            static_cast<float>(window.get_specification().height));

    translate_transform.translate_on_axis(
        10.0f, vq::graphics::transform::TransformBase::s_world_front);

    while (!window.should_close()) {
        window.update();

        glClearColor(0.0, 0.0, 0.0, 1.0);
        glClear(GL_COLOR_BUFFER_BIT);

        skybox_shader_handle.get().bind();
        skybox_shader_handle.get().set_uniform_mat4(
            view_matrix_uniform_location,
            glm::mat4(glm::mat3(view_transform.get_transform_matrix())));
        skybox_shader_handle.get().set_uniform_mat4(
            projection_matrix_uniform_location,
            projection_transform.get_transform_matrix());
        skybox_texture_handle.get().bind();
        skybox_geometry_handle.get().bind();

        glDrawArrays(GL_TRIANGLES, 0, 36);

        rotate_transform.rotate_euler_degrees(
            glm::vec3(0.005f, 0.005f, 0.005f));

        test_shader_handle.get().bind();
        test_shader_handle.get().set_uniform_mat4(
            model_matrix_uniform_location,
            projection_transform.get_transform_matrix() *
                view_transform.get_transform_matrix() *
                translate_transform.get_transform_matrix() *
                rotate_transform.get_transform_matrix());

        glActiveTexture(GL_TEXTURE0);
        test_texture_handle.get().bind();
        test_geometry_handle.get().bind();

        glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, nullptr);

        vq::graphics::core::Geometry::unbind_all();
        vq::graphics::texture::Texture2D::unbind_all();
        vq::graphics::core::Shader::unbind_all();
    }
}

/*----------------------------------------------------------------------------*/
