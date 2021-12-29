#version 330 core
out vec4 color;
uniform vec3 lightPos;
uniform float lightPow;
uniform vec3 viewPos;
in vec3 Normal;
in vec3 FragPos;



void main(){
    float specularStrength = 0.0f;
    vec3 light_color = vec3(1.0f,1.0f,1.0f);
    vec3 color_obj = vec3(1.0f, 0.9f, 1.0f);
    float ambient_strenght = 0.2f;
    vec3 ambient = ambient_strenght*light_color;
    vec3 LightDir = lightPos - FragPos;
    vec3 Lightsize = lightPos - FragPos;
    LightDir = normalize(LightDir);
    float LightDis = sqrt(dot(Lightsize,Lightsize));
    float diff = max(dot(LightDir,Normal),0.0f);
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-LightDir, Normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    vec3 specular = specularStrength * spec * light_color;
    vec3 result = (ambient + diff*light_color + specular)*color_obj;
    //vec3 result = Normal;
    
    color = vec4(result,1.0f);
    //color = vec4(Normal,1.0f);
}