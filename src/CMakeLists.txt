add_executable(craftmine    main.cpp

                            Game/Block.cpp
                            Game/Chunk.cpp
                            Game/Game.cpp
                            Game/GameRenderer.cpp
                            Game/Player.cpp
                            Game/Input.cpp
                            Game/TextureManager.cpp

                            Graphics/IndexBuffer.cpp
                            Graphics/Renderer.cpp
                            Graphics/Shader.cpp
                            Graphics/Texture.cpp
                            Graphics/VertexArray.cpp
                            Graphics/VertexBuffer.cpp
                            
                            External/stb_image.cpp
                            External/stb_image_write.cpp)

target_include_directories(craftmine PUBLIC     ${PROJECT_SOURCE_DIR}/include)

target_link_libraries(craftmine     headers
                                    glfw
                                    ${PROJECT_SOURCE_DIR}/lib/glew/lib/libglew32.a
                                    ${PROJECT_SOURCE_DIR}/lib/glew/lib/libglew32mx.a
                                    glm::glm
                                    opengl32
                                    gdi32
                                    user32
                                    kernel32)