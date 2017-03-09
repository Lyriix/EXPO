// Fragment shader for multiple lights selecting what material to shade

#version 330 core

struct MaterialProperties {
    vec3 emission;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
};

//a set of materials to select between, per shader invocation
const int NumMaterials = 15;
uniform MaterialProperties Material[NumMaterials];

flat in int MatIndex; //input material index from vertex shader


varying vec4 position_3d_original;
varying vec4 position_3d_modelview;
varying vec3 normal;
varying vec4 color;

uniform vec3 light=vec3(0.5f,0.3f,5.0f);

in vec4 Position;

out vec4 FragColor;



void main(void)
{
    vec3 scatteredLight = vec3(0.0);
    vec3 reflectedLight = vec3(0.0);
    vec3 n=normalize(normal);

    vec3 p=position_3d_modelview.xyz;
    vec3 vertex_to_light=normalize(light-p);
    vec3 reflected_light=reflect(-vertex_to_light,n);
    vec3 user_to_vertex=normalize(-p);

    float diffuse_term=0.8f*clamp(abs(dot(n,vertex_to_light)),0.0f,1.0f);
    float specular_term=0.2f*pow(clamp(dot(reflected_light,user_to_vertex),0.0f,1.0f),128.0f);
    float ambiant_term=0.4f;
    scatteredLight =
                ambiant_term * Material[MatIndex].ambient
                + light * diffuse_term *Material[MatIndex].diffuse ;
    reflectedLight =
                light * Material[MatIndex].specular * specular_term;


    vec3 rgb = min(Material[MatIndex].emission + color.rgb *scatteredLight + reflectedLight, vec3(1.0));

    gl_FragColor = vec4(rgb, color.a);
}