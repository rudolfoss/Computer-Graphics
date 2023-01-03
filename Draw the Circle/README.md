# Draw the Circle

1. 원의 중심은 (0,0,0)이고, 반지름 (r)은 0.8로 합니다. <br>
2. 원 기하 정보 준비 과정: 초기화 부분에서 <br>
   2-1. std::vector<glm::vec3>으로 정의된 정점 배열에 중점과 원의 가장자리에 있는 점들을 순서대로 추가합니다.<br>
       이때 각 점의 좌표는 r*glm::vec3(cos(theta), sin(theta),0) 이고, theta의 범위는 0=<theta<2*PI 까지 입니다. (PI 값은 직접 정의해 주어야 합니다.)<br>
   2-2. 만든 정점들을 번호를 이용하여 std::vector<glm::u32vec3> 형식의 삼각형 list를 만듭니다. 각각의 원소에는 원을 구성하기 위한 각 삼각형에 대항되는 정점의 번호를 넣습니다. <br>
이때 마지막 삼각형의 경우, 원 가장자리 점 중 마지막 점, 처음점과 중점을 사용하여 구성합니다. <br>
   2-3. 이와 같이 만든 정점들과 삼각형들에 대해 각각 ARRAY_BUFFER, ELEMENT_ARRAY_BUFFER를 만들고 데이터를 전송합니다. <br>
   2-4. vertexArray를 만들고, 정점을 표현하는 Buffer를 0번 자리에 연결시켜 줍니다. <br>
3. Rendering을 위해 <br>
   3-1. 전역 변수로 Program 변수를 만들고 (toys.h) <br>
   3-2. 초기화 과정에서 program.loadShaders("shader.vert","shader.frag"); 의 방법으로 shader code를 읽고 컴파일 합니다.<br>
   3-3. 렌더링 과정에서는 glUseProgram( program.programID );의 방법으로 shader를 작동시키고<br>
   3-4. 미리 만든 vertexArray와 ELEMENT_ARRAY_BUFFER를 이용하여 원을 그립니다.<br>