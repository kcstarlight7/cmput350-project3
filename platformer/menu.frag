#version 120

uniform vec2 resolution;
uniform float time;

void main() {

	float normalized = gl_FragCoord.y / resolution.y;

	float t = (mod(time, 3000.0)) / 3000.0;

	// range from (155, 116, 179) to (66, 116, 179)
	// one complete cycle, go from color1 to color2 back to color1
	// color / 255
	float color1 = 0.608;
	float color2 = 0.259;

	float mixValue = 0.5 + 0.5*sin(normalized * 3.14159 - t * 6.28318);

	float mixColor = mix(color1, color2, mixValue);

	gl_FragColor = vec4(mixColor, 0.455, 0.702, 1.0);
}