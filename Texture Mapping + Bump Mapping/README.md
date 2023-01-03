# Texture Mapping + Bump Mapping


1. 초기화 부분에서 j3a 파일을 읽은 결과를 이용하여 각각 texture map image 및 bump map image를 buffer에 load 하고, OpenGL texture를 생성하고, 속성을 지정한 후 buffer를 upload 합니다. <br>
2. Rendering 부분에서 texture map과 bump map을 각각 다른 slot에 binding하고, slot 번호를 shader에 uniform으로 보내줍니다. <br>
3. shader에서 uniform sampler2d 로 texture map과 bump map을 받아 옵니다. <br>
4. shader에서 texture map과 texCoord를 이용하여 색상을 결정하고, 쉐이딩 과정에 diffuse color로 사용합니다. <br>
5. 강의 자료를 참고하여 bump map을 적용한 normal을 새로 계산하고 쉐이딩에 적용합니다. <br>