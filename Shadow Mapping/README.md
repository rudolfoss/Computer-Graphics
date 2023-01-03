# Shadow Mapping

1. Main code의 초기화 부분에서 FBO를 생성합니다. FBO의 크기는 1024x1024 이상으로 하고, channel 깊이는 float로 지정하여 생성하여야 합니다. <br>
2. Shadow map을 만들기 위한 shader program을 작성합니다. vertex shader에서는 조명의 view, projection matrix를 받아서, transform한 결과를 보내고, <br>
fragment shader에서는 rgb 모든 channel에 gl_fragCoord의 z값이 저장되도록 합니다. <br>
3. Main code의 render 부분에서 조명을 시점으로 한 view matrix, projection matrix를 계산하고 shadow map을 만들기 위한 프로그램을 사용하여 <br>
FBO에 shadow map을 render 합니다. <br>
4. 최종 rendering을 위한 vertex shader에서는 역시 조명을 시점으로 하는 view, projection matrix를 받아서, 각 정점의 조명 입장에서의 normalized coordinate를 계산하고, fragment shader로 전달합니다. <br>
5. fragment shader에서는 얻은 normalized coordinate를 이용하여 shadow map 좌표 및 조명과의 거리를 계산하고, 거리가 shadow map에 저장된 거리보다 멀면 밝기를 줄입니다. <br>
6. main code에서는 최종 rendering을 위한 shader program에 조명을 시점으로 한 view, projection matrix를 uniform으로 전달하고, shadow map을 texture로 전달합니다. <br>
7. 보다 아름다운 shadow mapping을 위해 bias를 적용합니다. <br>
8. shadow의 경계선을 아름답게 보이기 위해 poisson sample을 이용하여 shadow map을 multisampling합니다. <br>
