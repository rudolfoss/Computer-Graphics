# Phong Shading

1. diffuse color, light 위치, shininess, light 색상, ambient light 색상의 물성 및 조명 조건은 Cpp 프로그램에서 uniform으로 전달합니다. <br>
2. specular 계산에 사용되는 색은 흰색으로 합니다. <br>
3. ambient 계산에 사용되는 색은 diffuse color로 합니다. <br>
4. 반드시 depth test는 켜야 합니다. <br>