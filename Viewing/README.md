# Viewing

1. 3차원 물체 (J3A 형식)을 읽고, 각종 Buffer를 만들고 rendering 합니다. (j3a.hpp 중 comment 참고) <br>
2. vertex shader를 수정하여 Model, Viewing, projection transform 을 uniform으로 받고, 이에 따라 입력된 vertex의 normalized coordinate를 계산하여 gl_Position에 저장합니다. <br>
3. glfw 의 mouse position callback 과 scroll callback 기능을 활용하여 마우스 입력에 따라 가상 카메라의 방향, fov 값을 변화시킬 수 있도록 합니다. <br>
4. 입력에 따라 변화된 카메라의 방향에 따라 카메라의 위치를 계산하고, 이에 따른 View matrix를 계산하여 vertex shader에 전달합니다. (glm::rotate 및 glm::lookAt 활용) <br>
5. 입력에 따라 변화된 fov 값을 기반으로 projection matrix를 계산하여 vertex shader에 전달합니다. (glm::perspective 활용) <br>
이때 카메라의 pitch는 -90도에서 90도 사이로 유지되도록 하고, fov는 10도에서 170도 사이로 유지되도록 합니다. <br>
