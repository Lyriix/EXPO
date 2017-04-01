// Fragment shader for multiple lights selecting what material to shade

#version 120

varying vec4 position_3d_original;
varying vec4 position_3d_modelview;
varying vec3 normal;
varying vec4 color;

uniform sampler2D texture;

uniform vec3 light=vec3(1.0f,1.0f,1.0f);

struct MaterialProperties {
    vec3 emission; //Ke
    vec3 ambient; //Ka
    vec3 diffuse; //Kd
    vec3 specular; //Ks
    float shininess; //Ns
    float transparency; //d
};
const int NumMaterials = 15;
uniform int index_mat;
//flat in int MatIndex;
uniform MaterialProperties material[NumMaterials];


void main (void)
{
    vec3 n=normalize(normal);

    vec3 p=position_3d_modelview.xyz;
    vec3 vertex_to_light=normalize(light-p);
    vec3 reflected_light=reflect(-vertex_to_light,n);
    vec3 user_to_vertex=normalize(-p);

    float diffuse_term=clamp(abs(dot(n,vertex_to_light)),0.0f,1.0f);//*0.8f
    float specular_term=pow(clamp(dot(reflected_light,user_to_vertex),0.0f,1.0f),128.0f);//*0.2f
    float ambiant_term=1.0f; //0.4f


    vec3 scatteredLight = vec3(0.0);
    vec3 reflectedLight = vec3(0.0);

    vec3 em = material[index_mat].emission;
    scatteredLight =
                ambiant_term * material[index_mat].ambient
                +  diffuse_term *material[index_mat].diffuse * light ;
    reflectedLight =
                material[index_mat].specular * specular_term * light;



   vec3 rgb = min(material[index_mat].emission + color.rgb *scatteredLight + reflectedLight, vec3(1.0f,1.0f,1.0f));
   vec2 tex_coord=gl_TexCoord[0].xy;
   vec4 color_texture = texture2D(texture,tex_coord);
   vec4 color = vec4(rgb, material[index_mat].transparency) * color_texture;
    gl_FragColor = color;
}



/*

//a set of materials to select between, per shader invocation
const int NumMaterials = 15;
uniform MaterialProperties Material[NumMaterials];

in int MatIndex; //input material index from vertex shader


uniform vec3 light=vec3(0.5f,0.3f,5.0f);

//in vec4 Position;

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
*/
