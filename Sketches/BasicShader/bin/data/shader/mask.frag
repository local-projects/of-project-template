#extension GL_EXT_gpu_shader4 : require

uniform sampler2D img; //texture inputs
uniform sampler2D mask;

varying vec2 vTexCoord; //get current fragment text coords from the vertex shader

void main(void){

	vec4 imgPixel = texture2D(img, vTexCoord);
	vec4 maskPixel = texture2D(mask, vTexCoord);
	vec4 finalPixel = vec4(imgPixel.rgb, maskPixel.r); //using mask red chanel for simplicity
	gl_FragColor = finalPixel * gl_Color;
}