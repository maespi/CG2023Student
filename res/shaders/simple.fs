// This variables comes from the vertex shader
// They are baricentric interpolated by pixel according to the distance to every vertex
varying vec3 v_world_normal;
uniform vec2 v_uv;
uniform int opt;
uniform sampler2D texture;


void main()
{
    
        vec3 color = normalize(v_world_normal);
        
        gl_FragColor = vec4( texture_color );

}
