add_executable(craftmine    main.cpp

                            Block.cpp
                            Chunk.cpp
                            Game.cpp
                            GameRenderer.cpp
                            IndexBuffer.cpp
                            Input.cpp
                            Player.cpp
                            Renderer.cpp
                            Shader.cpp
                            Texture.cpp
                            TextureManager.cpp
                            VertexArray.cpp
                            VertexBuffer.cpp
                            
                            stb_image.cpp)

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