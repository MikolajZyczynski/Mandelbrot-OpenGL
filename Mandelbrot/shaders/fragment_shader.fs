// fragment shader
#version 430 core

layout(location = 0) uniform float rect_width;
layout(location = 1) uniform float rect_height;
layout(location = 2) uniform vec2 area_w;
layout(location = 3) uniform vec2 area_h;
layout(location = 4) uniform int max_iterations;

out vec4 pixel_color;

const vec3 color_map[] = {
    {0.0,  0.0,  0.0},
    {0.26, 0.18, 0.06},
    {0.1,  0.03, 0.1},
    {0.04, 0.0,  0.18},
    {0.02, 0.02, 0.29},
    {0.0,  0.03, 0.39},
    {0.05, 0.17, 0.54},
    {0.09, 0.32, 0.69},
    {0.22, 0.49, 0.82},
    {0.52, 0.71, 0.9},
    {0.82, 0.92, 0.97},
    {0.94, 0.91, 0.75},
    {0.97, 0.79, 0.37},
    {1.0,  0.67, 0.0},
    {0.8,  0.5,  0.0},
    {0.6,  0.34, 0.0},
    {0.41, 0.2,  0.01}
};

//const vec3 color_map[] = {
//    {0.66, 0.30, 0.15}, // brown 3
//    {0.25,  0.07, 0.26}, // dark violett
//    {0.09,  0.01, 0.47}, // darkest blue
//    {0.04,  0.4, 0.73},// blue 5
//    {0.0,  0.7, 0.100}, // blue 4
//    {0.12, 0.44, 0.138}, // blue 3
//    {0.24, 0.82, 0.177}, // blue 2
//    {0.57, 0.125, 0.209}, // blue 1
//    {0.134, 0.181, 0.229}, // blue 0
//    {0.211, 0.236, 0.248}, // lightest blue
//    {0.241, 0.233, 0.191}, // lightest yellow
//    {0.248, 0.201, 0.95}, // light yellow
//    {0.255, 0.170,  0.0}, // dirty yellow
//    {0.204, 0.128,  0.0}, // brown 0
//    {0.153, 0.87,  0.0}, // brown 1
//    {0.06, 0.52,  0.03}
//};

void main()
{
    const vec2 C = vec2(gl_FragCoord.x * (area_w.y - area_w.x) / rect_width  + area_w.x,
                        gl_FragCoord.y * (area_h.y - area_h.x) / rect_height + area_h.x);
    vec2 Z = vec2(0.0);
    uint iteration = 0;

    while (iteration < max_iterations)
    {
        const float x = Z.x * Z.x - Z.y * Z.y + C.x;
        const float y = 2.0 * Z.x * Z.y       + C.y;

        if (x * x + y * y > 4.0)
            break;

        Z.x = x;
        Z.y = y;

        ++iteration;
    }

    const uint row_index = (iteration * 100 / max_iterations % 16); //*100
    pixel_color = vec4((iteration == max_iterations ? vec3(0.0) : color_map[row_index]), 1.0);
}