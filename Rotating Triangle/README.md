# Rotating Triangle

1. (0,0.7,0), (-0.7,-0.7,0), (0.7,-0.7,0) 의 정점을 가지는 삼각형을 만듭니다. <br>
    삼각형의 정점은 ARRAY_BUFFER로 GPU에 전달되어야 하고, <br>
    vertex array로 shader에 전달 되어야 합니다.
    삼각형은 ELEMENT_ARRAY_BUFFER를 이용하여 index를 GPU에 전달해야 합니다. <br>
2. Vertex shader code를 수정하여 삼각형을 transform 할 수 있도록 변경합니다. <br>
   강의 자료를 참고하여 transformation matrix (3x3)을 uniform variable로 받도록 하고 <br>
   입력된 2차원 좌표를 transform하여 fragment shader에 전달합니다. (gl_Position) <br>
3. main에서 각의 프레임 마다 삼각형이 회전 할 각도를 증가시키기 위한 코드를 작성합니다. <br>
   회전의 속도는 5도 (5/180.0*PI radian)이 적당하오. <br>
4. 각도에 따른 2차원 회전 행렬을 만듭니다. <br>
   mat[0][0] = cos(theta); <br>
   mat[0][1] = sin(theta); <br>
   mat[0][2] = 0; <br>
   ... 
   과 같은 방법으로 행렬의 각각의 원소 값을 지정합니다. <br>
5. 이렇게 구성한 행렬을 shader uniform variable로 전달합니다. <br>