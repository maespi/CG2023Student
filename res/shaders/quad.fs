varying vec2 v_uv;
uniform float time;
uniform int opt;
uniform sampler2D u_texture;
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
    
    vec4 texture_basic = texture2D(u_texture, v_uv);
    //ex 3.1.a
    if (opt == 1) {//1
        vec3 ex1_1 = (v_uv.x*navy) + ((1.0-v_uv.x)*beige) + sin(time);
        gl_FragColor = vec4(ex1_1,1.0);
        
    }//ex 3.1.b
    else if (opt == 2){//2
        float radius;
        radius = sqrt(pow((v_uv.x - 0.5), 2.0) + pow((height * (v_uv.y - 0.5) / width), 2.0));
        float sin_value = sin(radius * 3.0 - time*5.0);
        vec3 ex1_2 = vec3(sin_value, sin_value,sin_value);
        
        gl_FragColor = vec4(ex1_2, 1.0);
        
    }//ex 3.1.c
    else if (opt == 3){//3
        vec3 red_mod = sin(v_uv.x*aspect_ratio*10.0*time*0.9+1000.0)*red;
        vec3 blue_mod = sin(v_uv.y*10.0*time*0.9+1000.0)*blue;
        gl_FragColor = vec4(red_mod+blue_mod, 1.0);
        
    }//ex 3.1.d
    else if (opt == 4) {//4
        float time_factor = time * 0.2;
        float x_mod = mod(cos(time_factor) + v_uv.x, 0.1);
        float y_mod = mod(sin(time_factor) + v_uv.y, 0.1);
        float x_coord = v_uv.x - x_mod;
        float y_coord = v_uv.y - y_mod;
        vec3 color = x_coord * aspect_ratio * red;
        
        float aspect_ratio_10 = 10.0 * aspect_ratio;
        float y_floor = floor(10.0 * v_uv.y) / 10.0;
        float x_floor = floor(v_uv.x * aspect_ratio_10) / aspect_ratio_10;
        vec3 color1 = mix((1.0 - y_floor) * beige, x_floor * magenta, 0.9);
        vec3 color2 = mix((1.0 - x_floor) * white, y_floor * green, 0.9);
        
        vec3 final_color = color1 + color2 + color;
        gl_FragColor = vec4(final_color, 1.0);
    
    }//ex 3.1.e
    else if (opt == 5){//5
        
        float curve = 0.1 * sin((9.25 * v_uv.x) + (2.0 * time));
        
        float lineAShape = smoothstep(1.0 - clamp(distance(curve + v_uv.y, 0.5) * 1.0, 0.0, 1.0), 1.0, 0.9999);
        
        float c = min(mix(1.0-v_uv.y, v_uv.y, lineAShape),mix(1.0-v_uv.y, lineAShape-v_uv.y, lineAShape));
        
        vec3 final_color = vec3(0,c,0);
        
        gl_FragColor = vec4(final_color, 1.0);
        
    }//ex 3.1.f
    else if (opt == 6){//6
        
        
        float a = floor(aspect_ratio * 20.0 * v_uv.x);
        float b = floor(20.0 * v_uv.y);
        float c = mod(a, 2.0);
        float d = mod(b, 2.0);
        float e = mod(c+d,2.0);
        
        vec4 newColor = vec4(e,e,e,e);

        gl_FragColor = newColor;
        
    }//ex 3.2 - original photo
    else if(opt == 7){//q
        gl_FragColor = texture_basic;
        
    }//ex 3.2.a - grayscale
    else if (opt == 8){//w
        vec4 color = vec4(texture_basic.gggg);
        
        gl_FragColor = color;
        
    }//ex 3.2.b - invert color
    else if(opt == 9) {//e
        
        vec4 color = vec4(1.0-texture_basic.x, 1.0-texture_basic.y, 1.0-texture_basic.z, 1.0-texture_basic.w);
        gl_FragColor = color;
        
    }//ex 3.2.c - channel manipulation
    else if(opt == 10) {//r
        vec4 color = vec4(texture_basic.y, 1.0-texture_basic.z, 1.0-texture_basic.x, 1.0-texture_basic.w);
        gl_FragColor = color;
    }//ex 3.2.d - threshold
    else if(opt == 11) {//t
        
        float avg_brightness = (texture_basic.x + texture_basic.y + texture_basic.z) / 5.0;
        float threshold = step(0.2 + 0.01, avg_brightness);
        vec4 color = vec4(threshold, threshold, threshold, threshold);

        gl_FragColor = color;
        
    }//ex 3.2.e - blur
    else if(opt == 12){//y
    
        float factor_h = 0.001;
        float factor_v = factor_h * width / height;

        float main_factor_pixel = max(abs(0.1), 0.001);
        
        float sec_factor_pixel = (1.0 - main_factor_pixel) / 5.0;
        float ter_factor_pixel = (1.0 - main_factor_pixel - sec_factor_pixel * 4.0) / 8.0;

        for (int x_index = -2; x_index <= 2; x_index++) {
            for (int y_index = -2; y_index <= 2; y_index++) {
                float x_offset = float(x_index) * factor_h;
                float y_offset = float(y_index) * factor_v;
                float sin_x = sin(3.0 * (v_uv.x + x_offset));
                float sin_y = sin(3.0 * (v_uv.y + y_offset));
                vec3 color = texture2D(u_texture, v_uv + vec2(x_offset, y_offset)).xyz;
                if (x_index == 0 && y_index == 0) {
                    texture_basic.xyz = color * main_factor_pixel;
                } else if (x_index == 1 && y_index == 1) {
                    texture_basic.xyz += color * ter_factor_pixel * sin_x * sin_y;
                } else {
                    texture_basic.xyz += color * sec_factor_pixel * sin_x * sin_y;
                }
            }
        }

        gl_FragColor = texture_basic;
        
    }//ex 3.2.f - vignneting
    else if (opt == 13) {//u
        vec2 uv = v_uv;
        float sinX = sin(4.0 * uv.x);
        float sinY = sin(4.0 * uv.y);
        vec3 color = (sinX * white + (1.0 - sinX) * black) / 3.0 + (sinY * white + (1.0 - sinY) * black) / 3.0;
        vec4 diff = vec4(color, 1.0);
        
        gl_FragColor = texture_basic * diff;
        
    }//ex 3.3.a - rotate and move unidirectional
    else if (opt == 14){//a
        
        float rotationAngle = 180.0;

        // Get the original texture coordinates
        vec2 textureCoords = v_uv;

        // Rotation transformation
        mat2 rotationMatrix = mat2(cos(rotationAngle), -sin(rotationAngle) - time * 0.00009,-sin(rotationAngle), cos(rotationAngle) + time * 0.00001);
        textureCoords = rotationMatrix * (textureCoords - vec2(center_x, center_y)) + vec2(center_x, center_y);

        // Wrap the texture coordinates using the fract function
        textureCoords = fract(textureCoords);

        // Sample the texture using clamp_to_edge wrap mode
        vec4 textureColor = texture2D(u_texture, textureCoords);

        gl_FragColor = textureColor;



        
    }//ex 3.3.b - pixelation
    else if (opt == 15) { // Pixelation transformation
        int pixelSize = 50;

        // Calculate the size of each pixel block
        vec2 blockSize = vec2(1.0 / float (pixelSize));

        // Calculate the pixelated texture coordinates by rounding to the nearest pixel block
        vec2 pixelatedCoords = floor(v_uv.xy / blockSize) * blockSize;

        // Sample the texture using clamp_to_edge wrap mode
        vec4 color = texture2D(u_texture, pixelatedCoords);
        gl_FragColor = color;
        
        }
    
}
