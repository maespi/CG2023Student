varying vec2 v_uv;
uniform float time;
uniform int opt;
uniform float center_x;
uniform float center_y;
uniform float aspect_ratio;
uniform float width;
uniform float height;



void main()
{
    vec3 red = vec3(1.0, 0.0, 0.0);
    vec3 green = vec3(0.1, 0.6, 1.0);
    vec3 blue = vec3(0.0, 0.0, 1.0);
    vec3 white = vec3(1.0, 1.0, 1.0);
    vec3 black = vec3(0.0, 0.0, 0.0);
    vec3 yellow = vec3(1.0, 1.0, 0.0);
    vec3 magenta = vec3(1.0, 0.0, 1.0);
    vec3 cyan = vec3(0.0, 1.0, 1.0);
    vec3 orange = vec3(1.0, 0.5, 0.0);
    vec3 gray = vec3(0.5, 0.5, 0.5);
    vec3 purple = vec3(0.5, 0.0, 1.0);
    vec3 brown = vec3(0.6, 0.3, 0.0);
    vec3 pink = vec3(1.0, 0.7, 0.8);
    vec3 olive = vec3(0.5, 0.5, 0.0);
    vec3 navy = vec3(0.0, 0.0, 0.5);
    vec3 maroon = vec3(0.5, 0.0, 0.0);
    vec3 beige = vec3(0.9, 0.9, 0.6);
    vec3 turquoise = vec3(0.1, 0.8, 0.8);
    vec3 salmon = vec3(1.0, 0.5, 0.5);
    vec3 gold = vec3(1.0, 0.84, 0.0);

    
    if (opt == 1) {
        vec3 ex1_1 = (v_uv.x*navy) + ((1.0-v_uv.x)*beige) + sin(time);
        gl_FragColor = vec4(ex1_1,1);
        
        
    }else if (opt == 2){
        float radius;
        radius = sqrt(pow((v_uv.x - 0.5), 2.0) + pow((height * (v_uv.y - 0.5) / width), 2.0));
        float sin_value = sin(radius * 3.0 - time*5.0);
        vec3 ex1_2 = vec3(sin_value, sin_value,sin_value);
        
        gl_FragColor = vec4(ex1_2, 1.0);
        
    }else if (opt == 3){
        vec3 red_mod = sin(v_uv.x*aspect_ratio*10.0*time*0.9+1000.0)*red;
        vec3 blue_mod = sin(v_uv.y*10.0*time*0.9+1000.0)*blue;
        gl_FragColor = vec4(red_mod+blue_mod, 1.0);
        
    }else if (opt == 4){
        // Calculate modulation values for x and y
        float x_mod = mod(cos(time * 0.2) + v_uv.x, 0.1);
        float y_mod = mod(sin(time * 0.2) + v_uv.y, 0.1);

        // Adjust the x and y coordinates by the modulation values
        float x_coord = v_uv.x - x_mod;
        float y_coord = v_uv.y - y_mod;

        // Calculate the color based on the adjusted x coordinate and aspect ratio
        vec3 color = x_coord * aspect_ratio * red;

        // Calculate color1 and color2 using the floor and mix functions
        float x_floor = floor(10.0 * v_uv.x * aspect_ratio) / (10.0 * aspect_ratio);
        float y_floor = floor(10.0 * v_uv.y) / 10.0;
        vec3 color1 = mix((1.0 - y_floor) * beige, x_floor * magenta, 0.9);
        vec3 color2 = mix((1.0 - x_floor) * white, y_floor * green, 0.9);

        // Combine color1 and color2 to get the final output color
        vec3 final_color = color1 + color2 + color;

        gl_FragColor = vec4(final_color, 1.0);

    }
}
